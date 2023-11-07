#pragma once

#include "CLAPPlugin.h"
#include "CairoGUI.h"
#include "CLAPCairoGUIExtension.h"
#include "MessageQueue.h"
#include <string>
#include <stdint.h>
#include <math.h>

class ParameterWidget;
class CompressionMeter;
class Widget;

typedef int32_t VstInt32;


class AirwindowsCompressorUIPlugin : public CLAPPlugin {
	public:
		AirwindowsCompressorUIPlugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);
		bool init();
		~AirwindowsCompressorUIPlugin();

		uint32_t num_audio_ports(bool is_input);
		bool get_audio_port_info(uint32_t index, bool is_input, clap_audio_port_info_t* info_out);

		bool activate(double sample_rate, uint32_t min_frames, uint32_t max_frames);
		void deactivate();
		void reset();
		clap_process_status process(const clap_process_t* process);
		const void* get_extension(const char* id);

		void on_fd(int fd, clap_posix_fd_flags_t flags);
		bool get_gui_size(uint32_t* width_out, uint32_t* height_out);
		bool can_resize_gui() { return true; }
		bool resize_gui(uint32_t width, uint32_t height);
		void paint_gui();
		void mouse_pressed(int32_t x, int32_t y, int button);
		void mouse_released(int32_t x, int32_t y, int button);
		void mouse_moved(int32_t x, int32_t y);
		void main_thread_tick();

		uint32_t num_params();
		bool get_param_info(uint32_t param_index, clap_param_info_t* param_info_out);
		bool get_param_value(clap_id param_id, double* value_out);
		bool param_value_to_text(clap_id param_id, double value, char* out_buffer, uint32_t out_buffer_capacity);
		bool param_text_to_value(clap_id param_id, const char* param_value_text, double* value_out);
		void flush_params(const clap_input_events_t* in, const clap_output_events_t* out);

		bool save_state(const clap_ostream_t* stream);
		bool load_state(const clap_istream_t* stream);

		virtual void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames) = 0;
		virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames) = 0;
		virtual const std::vector<std::string>& parameter_names() = 0;
		virtual double get_parameter(clap_id param_id) = 0;
		virtual void set_parameter(clap_id param_id, double value) = 0;

		double getSampleRate() { return sample_rate; }

	protected:
		enum {
			default_gui_width = 500,
			default_gui_height = 300,
			};

		double sample_rate;
		MessageQueue main_to_audio_queue, audio_to_main_queue;
		uint32_t gui_width = default_gui_width, gui_height = default_gui_height;
		std::vector<clap_param_info_t> parameter_infos;
		std::vector<double> param_values, param_mods;

		std::vector<ParameterWidget*> parameter_widgets;
		CompressionMeter* compression_meter = nullptr;
		Widget* tracking_widget = nullptr;

		int32_t samples_left_until_meter_update = 0;
		double min_gain = 1.0;

		class CairoGUI : public ::CairoGUI {
			public:
				CairoGUI(AirwindowsCompressorUIPlugin* plugin_in)
					: plugin(plugin_in) {}

				cairo_t* cairo() {
					if (plugin->cairo_gui_extension == nullptr)
						return nullptr;
					return plugin->cairo_gui_extension->cairo;
					}
				void refresh() { plugin->cairo_gui_extension->refresh(); }

				AirwindowsCompressorUIPlugin* plugin;
			};
		CairoGUI cairo_gui;

		void process_event(const clap_event_header_t* event);
		void layout();

		void set_min_gain(double gain, uint32_t num_samples);
	};

