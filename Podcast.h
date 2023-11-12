#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Podcast : public AirwindowsCompressorUIPlugin {
	public:
		Podcast(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
		double c1L;
		double c2L;
		double c3L;
		double c4L;
		double c5L;
		//the compressor

		double c1R;
		double c2R;
		double c3R;
		double c4R;
		double c5R;
		//the compressor
	};

