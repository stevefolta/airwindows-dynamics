#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class ButterComp2Plugin : public AirwindowsCompressorUIPlugin {
	public:
		ButterComp2Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);
		bool param_value_to_text(clap_id param_id, double value, char* out_buffer, uint32_t out_buffer_capacity);
		bool param_text_to_value(clap_id param_id, const char* param_value_text, double* value_out);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double controlAposL;
		double controlAnegL;
		double controlBposL;
		double controlBnegL;
		double targetposL;
		double targetnegL;
		double lastOutputL;
		double controlAposR;
		double controlAnegR;
		double controlBposR;
		double controlBnegR;
		double targetposR;
		double targetnegR;
		double lastOutputR;
		bool flip;
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		float A;
		float B;
		float C;
	};

