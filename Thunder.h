#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Thunder : public AirwindowsCompressorUIPlugin {
	public:
		Thunder(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

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
		double gateL;
		double gateR;
		double iirSampleAL;
		double iirSampleBL;
		double iirSampleAR;
		double iirSampleBR;
		double iirSampleAM;
		double iirSampleBM;
		double iirSampleCM;
		uint32_t fpdL;
		uint32_t fpdR;
		bool flip;

		float A;
		float B;
	};

