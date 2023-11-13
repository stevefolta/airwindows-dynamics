#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Swell : public AirwindowsCompressorUIPlugin {
	public:
		Swell(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff

		double swellL;
		double swellR;
		bool louderL;
		bool louderR;
	};

