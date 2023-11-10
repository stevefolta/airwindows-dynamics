#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pressure4Plugin : public AirwindowsCompressorUIPlugin {
	public:
		Pressure4Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

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
		uint32_t fpdL;
		uint32_t fpdR;
		bool flip;
	};

