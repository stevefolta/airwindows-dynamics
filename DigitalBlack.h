#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class DigitalBlack : public AirwindowsCompressorUIPlugin {
	public:
		DigitalBlack(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		bool WasNegativeL;
		int ZeroCrossL;
		double gaterollerL;
		bool WasNegativeR;
		int ZeroCrossR;
		double gaterollerR;
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
	};

