#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class VariMu : public AirwindowsCompressorUIPlugin {
	public:
		VariMu(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double muVaryL;
		double muAttackL;
		double muNewSpeedL;
		double muSpeedAL;
		double muSpeedBL;
		double muCoefficientAL;
		double muCoefficientBL;
		double previousL;

		double muVaryR;
		double muAttackR;
		double muNewSpeedR;
		double muSpeedAR;
		double muSpeedBR;
		double muCoefficientAR;
		double muCoefficientBR;
		double previousR;
		bool flip;

		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		float A;
		float B;
		float C;
		float D;
	};

