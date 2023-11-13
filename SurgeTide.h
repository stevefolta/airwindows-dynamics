#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class SurgeTide : public AirwindowsCompressorUIPlugin {
	public:
		SurgeTide(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		bool flip;
		double chaseA;
		double chaseB;
		double chaseC;
	};

