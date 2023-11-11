#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class BrassRider : public AirwindowsCompressorUIPlugin {
	public:
		BrassRider(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double d[80002];
		double e[80002];
		double highIIRL;
		double slewIIRL;
		double highIIR2L;
		double slewIIR2L;
		double highIIRR;
		double slewIIRR;
		double highIIR2R;
		double slewIIR2R;
		double control;
		double clamp;
		double lastSampleL;
		double lastSlewL;
		double lastSampleR;
		double lastSlewR;
		int gcount;
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
	};

