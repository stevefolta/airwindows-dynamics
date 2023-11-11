#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class PodcastDeluxe : public AirwindowsCompressorUIPlugin {
	public:
		PodcastDeluxe(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		double d1L[503];
		double d2L[503];
		double d3L[503];
		double d4L[503];
		double d5L[503];
		//the phase rotator

		double c1L;
		double c2L;
		double c3L;
		double c4L;
		double c5L;
		//the compressor

		double lastSampleL;
		double lastOutSampleL;

		double d1R[503];
		double d2R[503];
		double d3R[503];
		double d4R[503];
		double d5R[503];

		int tap1, tap2, tap3, tap4, tap5, maxdelay1, maxdelay2, maxdelay3, maxdelay4, maxdelay5;
		//the phase rotator

		double c1R;
		double c2R;
		double c3R;
		double c4R;
		double c5R;
		//the compressor

		double lastSampleR;
		double lastOutSampleR;
	};

