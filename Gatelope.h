#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Gatelope : public AirwindowsCompressorUIPlugin {
	public:
		Gatelope(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double iirLowpassAR;
		double iirLowpassBR;
		double iirHighpassAR;
		double iirHighpassBR;
		double iirLowpassAL;
		double iirLowpassBL;
		double iirHighpassAL;
		double iirHighpassBL;
		double treblefreq;
		double bassfreq;
		bool flip;
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
	};

