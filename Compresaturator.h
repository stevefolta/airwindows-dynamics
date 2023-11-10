#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Compresaturator : public AirwindowsCompressorUIPlugin {
	public:
		Compresaturator(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		int dCount;

		float dL[11000];
		int lastWidthL;
		double padFactorL;

		float dR[11000];
		int lastWidthR;
		double padFactorR;

		float A;
		float B;
		float C;
		float D;
		float E; //parameters. Always 0-1, and we scale/alter them elsewhere.
	};

