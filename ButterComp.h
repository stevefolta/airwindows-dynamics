#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class ButterComp : public AirwindowsCompressorUIPlugin {
	public:
		ButterComp(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double controlAposL;
		double controlAnegL;
		double controlBposL;
		double controlBnegL;
		double targetposL;
		double targetnegL;
		double controlAposR;
		double controlAnegR;
		double controlBposR;
		double controlBnegR;
		double targetposR;
		double targetnegR;
		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
	};

