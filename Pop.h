#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pop : public AirwindowsCompressorUIPlugin {
	public:
		Pop(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

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
		double thickenL;
		double previousL;
		double previous2L;
		double previous3L;
		double previous4L;
		double previous5L;
		double dL[10001];

		double muVaryR;
		double muAttackR;
		double muNewSpeedR;
		double muSpeedAR;
		double muSpeedBR;
		double muCoefficientAR;
		double muCoefficientBR;
		double thickenR;
		double previousR;
		double previous2R;
		double previous3R;
		double previous4R;
		double previous5R;
		double dR[10001];

		int delay;
		bool flip;	

		float A;
		float B;
		float C;
	};

