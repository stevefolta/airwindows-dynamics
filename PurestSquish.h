#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class PurestSquish : public AirwindowsCompressorUIPlugin {
	public:
		PurestSquish(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

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
		double muSpeedCL;
		double muSpeedDL;
		double muSpeedEL;
		double muCoefficientAL;
		double muCoefficientBL;
		double muCoefficientCL;
		double muCoefficientDL;
		double muCoefficientEL;
		double iirSampleAL;
		double iirSampleBL;
		double iirSampleCL;
		double iirSampleDL;
		double iirSampleEL;
		double lastCoefficientAL;
		double lastCoefficientBL;
		double lastCoefficientCL;
		double lastCoefficientDL;
		double mergedCoefficientsL;

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
		double iirSampleAR;
		double iirSampleBR;
		double iirSampleCR;
		double iirSampleDR;
		double iirSampleER;
		double lastCoefficientAR;
		double lastCoefficientBR;
		double lastCoefficientCR;
		double lastCoefficientDR;
		double mergedCoefficientsR;

		int count;
		bool fpFlip;
	};

