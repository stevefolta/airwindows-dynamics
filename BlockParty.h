#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class BlockParty : public AirwindowsCompressorUIPlugin {
	public:
		BlockParty(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		float A;
		float B;

		double muVaryL;
		double muAttackL;
		double muNewSpeedL;
		double muSpeedAL;
		double muSpeedBL;
		double muSpeedCL;
		double muSpeedDL;
		double muSpeedEL;
		double muCoefficientAL;
		double muCoefficientBL;
		double muCoefficientCL;
		double muCoefficientDL;
		double muCoefficientEL;
		double lastCoefficientAL;
		double lastCoefficientBL;
		double lastCoefficientCL;
		double lastCoefficientDL;
		double mergedCoefficientsL;
		double thresholdL;
		double thresholdBL;

		double muVaryR;
		double muAttackR;
		double muNewSpeedR;
		double muSpeedAR;
		double muSpeedBR;
		double muSpeedCR;
		double muSpeedDR;
		double muSpeedER;
		double muCoefficientAR;
		double muCoefficientBR;
		double muCoefficientCR;
		double muCoefficientDR;
		double muCoefficientER;
		double lastCoefficientAR;
		double lastCoefficientBR;
		double lastCoefficientCR;
		double lastCoefficientDR;
		double mergedCoefficientsR;
		double thresholdR;
		double thresholdBR;

		int count;
		bool fpFlip;
	};

