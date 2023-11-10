#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pressure5 : public AirwindowsCompressorUIPlugin {
	public:
		Pressure5(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double muVary;
		double muAttack;
		double muNewSpeed;
		double muSpeedA;
		double muSpeedB;
		double muCoefficientA;
		double muCoefficientB;
		bool flip; //Pressure

		enum {
			fix_freq,
			fix_reso,
			fix_a0,
			fix_a1,
			fix_a2,
			fix_b1,
			fix_b2,
			fix_sL1,
			fix_sL2,
			fix_sR1,
			fix_sR2,
			fix_lastSampleL,
			fix_lastSampleR,
			fix_total
			};
		double fixA[fix_total];
		double fixB[fix_total]; //fixed frequency biquad filter for ultrasonics, stereo

		double lastSampleL;
		double intermediateL[16];
		bool wasPosClipL;
		bool wasNegClipL;
		double lastSampleR;
		double intermediateR[16];
		bool wasPosClipR;
		bool wasNegClipR; //Stereo ClipOnly2

		double slewMax; //to adust mewiness

		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
	};

