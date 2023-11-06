#include "AirwindowsCompressorUIPlugin.h"
#include "CLAPPosixFDExtension.h"
#include "CLAPCairoGUIExtension.h"
#include "CLAPAudioPortsExtension.h"
#include "CLAPParamsExtension.h"
#include "CLAPStateExtension.h"


AirwindowsCompressorUIPlugin::AirwindowsCompressorUIPlugin(
	const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: CLAPPlugin(descriptor, host), cairo_gui(this)
{
	/***/
}


bool AirwindowsCompressorUIPlugin::init()
{
	posix_fd_extension = new CLAPPosixFDExtension(this);
	cairo_gui_extension = new CLAPCairoGUIExtension(this);
	audio_ports_extension = new CLAPAudioPortsExtension(this);
	params_extension = new CLAPParamsExtension();
	state_extension = new CLAPStateExtension(this);

	return true;
}


AirwindowsCompressorUIPlugin::~AirwindowsCompressorUIPlugin()
{
	/***/

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
	/***/
}


void AirwindowsCompressorUIPlugin::on_fd(int fd, clap_posix_fd_flags_t flags)
{
	/***/
}


bool AirwindowsCompressorUIPlugin::get_gui_size(uint32_t* width_out, uint32_t* height_out)
{
	/***/
}

bool AirwindowsCompressorUIPlugin::resize_gui(uint32_t width, uint32_t height)
{
	/***/
}


void AirwindowsCompressorUIPlugin::paint_gui()
{
	/***/
}


void AirwindowsCompressorUIPlugin::mouse_pressed(int32_t x, int32_t y, int button)
{
	/***/
}

void AirwindowsCompressorUIPlugin::mouse_released(int32_t x, int32_t y, int button)
{
	/***/
}

void AirwindowsCompressorUIPlugin::mouse_moved(int32_t x, int32_t y)
{
	/***/
}


void AirwindowsCompressorUIPlugin::main_thread_tick()
{
	/***/
}


bool AirwindowsCompressorUIPlugin::save_state(const clap_ostream_t* stream)
{
	/***/
}

bool AirwindowsCompressorUIPlugin::load_state(const clap_istream_t* stream)
{
	/***/
}


void AirwindowsCompressorUIPlugin::process_event(const clap_event_header_t* event)
{
	/***/
}


void AirwindowsCompressorUIPlugin::layout()
{
	/***/
}



