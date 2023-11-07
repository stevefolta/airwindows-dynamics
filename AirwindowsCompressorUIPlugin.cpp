#include "AirwindowsCompressorUIPlugin.h"
#include "CLAPPosixFDExtension.h"
#include "CLAPCairoGUIExtension.h"
#include "CLAPAudioPortsExtension.h"
#include "CLAPParamsExtension.h"
#include "CLAPStateExtension.h"
#include "ParameterWidget.h"
#include "Messages.h"
#include <sstream>
#include <iostream>
#include <stdio.h>


AirwindowsCompressorUIPlugin::AirwindowsCompressorUIPlugin(
	const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: CLAPPlugin(descriptor, host), cairo_gui(this)
{
}


bool AirwindowsCompressorUIPlugin::init()
{
	posix_fd_extension = new CLAPPosixFDExtension(this);
	cairo_gui_extension = new CLAPCairoGUIExtension(this);
	audio_ports_extension = new CLAPAudioPortsExtension(this);
	params_extension = new CLAPParamsExtension();
	state_extension = new CLAPStateExtension(this);

	// Set up parameters.
	const auto param_names = parameter_names();
	clap_id id = 0;
	for (const auto& name: param_names) {
		double cur_value = get_parameter(id);
		parameter_infos.push_back((clap_param_info_t) {
			.id = id,
			.flags =
				CLAP_PARAM_IS_AUTOMATABLE | CLAP_PARAM_IS_MODULATABLE |
				CLAP_PARAM_REQUIRES_PROCESS,
			.min_value = 0.0,
			.max_value = 1.0,
			.default_value = cur_value,
			});
		strncpy(parameter_infos.back().name, name.c_str(), CLAP_NAME_SIZE - 1);
		param_values.push_back(cur_value);
		param_mods.push_back(0.0);
		id += 1;
		}

	// Create parameter widgets.
	id = 0;
	for (const auto& name: param_names) {
		ParameterWidget* widget = new ParameterWidget(&cairo_gui, id, name);
		widget->set_value(param_values[id]);
		parameter_widgets.push_back(widget);
		id += 1;
		}
	layout();

	return true;
}


AirwindowsCompressorUIPlugin::~AirwindowsCompressorUIPlugin()
{
	for (auto widget: parameter_widgets)
		delete widget;

	delete posix_fd_extension;
	delete cairo_gui_extension;
	delete audio_ports_extension;
	delete params_extension;
	delete state_extension;
}


static const std::vector<clap_audio_port_info_t> audio_in_ports = {
	{
		.id = 0,
		.name = "in",
		.flags = CLAP_AUDIO_PORT_IS_MAIN | CLAP_AUDIO_PORT_SUPPORTS_64BITS,
		.channel_count = 2,
		.port_type = CLAP_PORT_STEREO,
		.in_place_pair = 0,
		},
	};

static const std::vector<clap_audio_port_info_t> audio_out_ports = {
	{
		.id = 0,
		.name = "out",
		.flags = CLAP_AUDIO_PORT_IS_MAIN | CLAP_AUDIO_PORT_SUPPORTS_64BITS,
		.channel_count = 2,
		.port_type = CLAP_PORT_STEREO,
		.in_place_pair = 0,
		},
	};

uint32_t AirwindowsCompressorUIPlugin::num_audio_ports(bool is_input)
{
	return is_input ? audio_in_ports.size() : audio_out_ports.size();
}

bool AirwindowsCompressorUIPlugin::get_audio_port_info(uint32_t index, bool is_input, clap_audio_port_info_t* info_out)
{
	if (is_input && index < audio_in_ports.size()) {
		*info_out = audio_in_ports[index];
		return true;
		}
	else if (!is_input && index < audio_out_ports.size()) {
		*info_out = audio_out_ports[index];
		return true;
		}
	return false;
}


bool AirwindowsCompressorUIPlugin::activate(double sample_rate_in, uint32_t min_frames, uint32_t max_frames)
{
	sample_rate = sample_rate_in;
	return true;
}

void AirwindowsCompressorUIPlugin::deactivate()
{
}

void AirwindowsCompressorUIPlugin::reset()
{
	/***/
}


clap_process_status AirwindowsCompressorUIPlugin::process(const clap_process_t* process)
{
	// Handle messages from the main thread.
	while (true) {
		auto message = main_to_audio_queue.pop_front();
		if (message.id < 0)
			break;
		switch (message.id) {
			case SetParameter:
				{
				auto param_id = message.int_value;
				param_values[param_id] = message.double_value;
				set_parameter(param_id, param_values[param_id] + param_mods[param_id]);
				}
				break;
			}
		}

	// Render and handle events.
	const uint32_t num_frames = process->frames_count;
	const uint32_t num_events = process->in_events->size(process->in_events);
	uint32_t cur_event = 0;
	uint32_t next_event_frame = num_events > 0 ? 0 : num_frames;
	for (uint32_t cur_frame = 0; cur_frame < num_frames; ) {
		// Handle events at this frame (and/or update next_event_frame).
		while (cur_event < num_events && next_event_frame <= cur_frame) {
			const clap_event_header_t* event = process->in_events->get(process->in_events, cur_event);
			if (event->time > cur_frame) {
				next_event_frame = event->time;
				break;
				}

			process_event(event);

			cur_event += 1;
			if (cur_event == num_events) {
				next_event_frame = num_frames;
				break;
				}
			}

		// Process audio.
		if (process->audio_inputs[0].data64 && process->audio_outputs[0].data64) {
			processDoubleReplacing(
				process->audio_inputs[0].data64,
				process->audio_outputs[0].data64,
				num_frames);
			}
		else if (process->audio_inputs[0].data32 && process->audio_outputs[0].data32) {
			processReplacing(
				process->audio_inputs[0].data32,
				process->audio_outputs[0].data32,
				num_frames);
			}
		else {
			// ERROR: input and output don't match, and we don't support that.
			}
		cur_frame = next_event_frame;
		}

	// Send info back to the main thread.
	/***/

	return CLAP_PROCESS_CONTINUE;
}


const void* AirwindowsCompressorUIPlugin::get_extension(const char* id)
{
	const void* extension = nullptr;
	if ((extension = posix_fd_extension->for_name(id))) ;
	else if ((extension = cairo_gui_extension->for_name(id))) ;
	else if ((extension = audio_ports_extension->for_name(id))) ;
	else if ((extension = params_extension->for_name(id))) ;
	else if ((extension = state_extension->for_name(id))) ;
	return extension;
}


void AirwindowsCompressorUIPlugin::on_fd(int fd, clap_posix_fd_flags_t flags)
{
	cairo_gui_extension->on_fd(fd, flags);
}


bool AirwindowsCompressorUIPlugin::get_gui_size(uint32_t* width_out, uint32_t* height_out)
{
	*width_out = gui_width;
	*height_out = gui_height;
	return true;
}

bool AirwindowsCompressorUIPlugin::resize_gui(uint32_t width, uint32_t height)
{
	gui_width = width;
	gui_height = height;
	layout();
	return true;
}


void AirwindowsCompressorUIPlugin::paint_gui()
{
	auto cairo = cairo_gui_extension->cairo;
	cairo_push_group(cairo);

	// Background.
	cairo_set_source_rgb(cairo, 1.0, 1.0, 1.0);
	cairo_paint(cairo);

	for (auto widget: parameter_widgets)
		widget->paint();

	// Blit to screen.
	cairo_pop_group_to_source(cairo);
	cairo_paint(cairo);
}


void AirwindowsCompressorUIPlugin::mouse_pressed(int32_t x, int32_t y, int button)
{
	if (button != Button1)
		return;

	for (auto widget: parameter_widgets) {
		if (widget->contains(x, y)) {
			tracking_widget = widget;
			break;
			}
		}

	if (tracking_widget)
		tracking_widget->mouse_pressed(x, y);
	cairo_gui_extension->refresh();
}

void AirwindowsCompressorUIPlugin::mouse_released(int32_t x, int32_t y, int button)
{
	if (button != Button1)
		return;

	if (tracking_widget && tracking_widget->mouse_released(x, y)) {
		/***/
		}
	tracking_widget = nullptr;
	cairo_gui_extension->refresh();
}

void AirwindowsCompressorUIPlugin::mouse_moved(int32_t x, int32_t y)
{
	if (tracking_widget == nullptr)
		return;

	tracking_widget->mouse_moved(x, y);
	for (auto widget: parameter_widgets) {
		if (widget == tracking_widget) {
			main_to_audio_queue.send(SetParameter, widget->id, widget->value());
			break;
			}
		}
}


void AirwindowsCompressorUIPlugin::main_thread_tick()
{
	/***/
}


uint32_t AirwindowsCompressorUIPlugin::num_params()
{
	return parameter_infos.size();
}

bool AirwindowsCompressorUIPlugin::get_param_info(uint32_t param_index, clap_param_info_t* param_info_out)
{
	if (param_index >= parameter_infos.size())
		return false;
	*param_info_out = parameter_infos[param_index];
	return true;
}

bool AirwindowsCompressorUIPlugin::get_param_value(clap_id param_id, double* value_out)
{
	if (param_id >= parameter_infos.size())
		return false;
	*value_out = get_parameter(param_id);
	return true;
}

bool AirwindowsCompressorUIPlugin::param_value_to_text(clap_id param_id, double value, char* out_buffer, uint32_t out_buffer_capacity)
{
	// Default: just a double.
	snprintf(out_buffer, out_buffer_capacity, "%g", value);
	return true;
}

bool AirwindowsCompressorUIPlugin::param_text_to_value(clap_id param_id, const char* param_value_text, double* value_out)
{
	char* end_ptr = nullptr;
	*value_out = strtod(param_value_text, &end_ptr);
	return end_ptr != param_value_text;
}

void AirwindowsCompressorUIPlugin::flush_params(const clap_input_events_t* in, const clap_output_events_t* out)
{
	auto num_events = in->size(in);
	for (uint32_t which_event = 0; which_event < num_events; ++which_event)
		process_event(in->get(in, which_event));
}


bool AirwindowsCompressorUIPlugin::save_state(const clap_ostream_t* stream)
{
	std::ostringstream data;
	for (clap_id i = 0; i < parameter_infos.size(); ++i) {
		if (i != 0)
			data << ' ';
		data << std::hexfloat << param_values[i];
		}

	auto contents = data.str();
	const char* bytes = contents.data();
	int64_t bytes_left = contents.size();
	while (bytes_left > 0) {
		auto bytes_written = stream->write(stream, bytes, bytes_left);
		if (bytes_written < 0)
			break;
		bytes += bytes_written;
		bytes_left -= bytes_written;
		}

	return bytes_left == 0;
}

bool AirwindowsCompressorUIPlugin::load_state(const clap_istream_t* stream)
{
	// Read the whole state.
	std::vector<char> buffer(256);
	std::vector<char> state;
	while (true) {
		auto bytes_read = stream->read(stream, buffer.data(), buffer.size());
		if (bytes_read == 0)
			break;
		else if (bytes_read < 0)
			return false;
		state.insert(state.end(), buffer.begin(), std::next(buffer.begin(), bytes_read));
		}

	// We can't use istringstream to read hex float values because GCC insists on
	// being broken.  Use strtod() instead.
	std::string contents(state.data(), state.size());
	const char* p = contents.c_str();
	for (clap_id i = 0; i < parameter_infos.size(); ++i) {
		if (*p == 0)
			return false;
		char* end = nullptr;
		param_values[i] = strtod(p, &end);
		p = end;
		set_parameter(i, param_values[i] + param_mods[i]);
		}

	return true;
}


void AirwindowsCompressorUIPlugin::process_event(const clap_event_header_t* event)
{
	if (event->space_id != CLAP_CORE_EVENT_SPACE_ID)
		return;

	if (event->type == CLAP_EVENT_PARAM_VALUE) {
		auto param_event = (const clap_event_param_value_t*) event;
		if (param_event->note_id == -1 && param_event->port_index == -1 && param_event->channel == -1 && param_event->key == -1) {
			auto param_id = param_event->param_id;
			if (param_id < parameter_infos.size()) {
				param_values[param_id] = param_event->value;
				set_parameter(param_id, param_values[param_id] + param_mods[param_id]);
				}
			}
		}
	else if (event->type == CLAP_EVENT_PARAM_MOD) {
		auto mod_event = (const clap_event_param_mod_t*) event;
		if (mod_event->note_id == -1 && mod_event->port_index == -1 && mod_event->channel == -1 && mod_event->key == -1) {
			auto param_id = mod_event->param_id;
			if (param_id < parameter_infos.size()) {
				param_mods[param_id] = mod_event->amount;
				set_parameter(param_id, param_values[param_id] + param_mods[param_id]);
				}
			}
		}
}


void AirwindowsCompressorUIPlugin::layout()
{
	static const double margin = 6.0;
	static const double parameter_height = 40;
	static const double parameter_spacing = 8.0;

	double y = margin;
	double parameter_width = gui_width - 2 * margin;
	for (auto widget: parameter_widgets) {
		widget->rect = { margin, y, parameter_width, parameter_height };
		widget->layout();
		y += parameter_height + parameter_spacing;
		}
}


