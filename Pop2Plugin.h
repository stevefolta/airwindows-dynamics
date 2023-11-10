#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pop2Plugin : public AirwindowsCompressorUIPlugin {
	public:
		Pop2Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		double muVaryL;
		double muAttackL;
		double muNewSpeedL;
		double muSpeedAL;
		double muSpeedBL;
		double muCoefficientAL;
		double muCoefficientBL;

		double muVaryR;
		double muAttackR;
		double muNewSpeedR;
		double muSpeedAR;
		double muSpeedBR;
		double muCoefficientAR;
		double muCoefficientBR;

		bool flip;	

		double lastSampleL;
		double intermediateL[16];
		bool wasPosClipL;
		bool wasNegClipL;
		double lastSampleR;
		double intermediateR[16];
		bool wasPosClipR;
		bool wasNegClipR; //Stereo ClipOnly2
	};

