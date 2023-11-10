#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class SoftGate : public AirwindowsCompressorUIPlugin {
	public:
		SoftGate(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
		double storedL[2];
		double diffL;
		double storedR[2];
		double diffR;
		double gate;
	};

