#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Point : public AirwindowsCompressorUIPlugin {
	public:
		Point(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

		bool param_value_to_text(clap_id param_id, double value, char* out_buffer, uint32_t out_buffer_capacity);
		bool param_text_to_value(clap_id param_id, const char* param_value_text, double* value_out);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		bool fpFlip;
		//default stuff
		double nibAL;
		double nobAL;
		double nibBL;
		double nobBL;
		double nibAR;
		double nobAR;
		double nibBR;
		double nobBR;
	};

