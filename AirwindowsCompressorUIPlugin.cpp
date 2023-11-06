#include "AirwindowsCompressorUIPlugin.h"


AirwindowsCompressorUIPlugin::AirwindowsCompressorUIPlugin(
	const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: CLAPPlugin(descriptor, host), cairo_gui(this)
{
	/***/
}


bool AirwindowsCompressorUIPlugin::init()
{
	/***/
}


AirwindowsCompressorUIPlugin::~AirwindowsCompressorUIPlugin()
{
	/***/
}


uint32_t AirwindowsCompressorUIPlugin::num_audio_ports(bool is_input)
{
	/***/
}

bool AirwindowsCompressorUIPlugin::get_audio_port_info(uint32_t index, bool is_input, clap_audio_port_info_t* info_out)
{
	/***/
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
	/***/
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



