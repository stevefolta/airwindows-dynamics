#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pyewacket : public AirwindowsCompressorUIPlugin {
	public:
		Pyewacket(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
		double chase;
		double lastrectifierL;
		double lastrectifierR;

		float A;
		float B;
		float C;
	};


