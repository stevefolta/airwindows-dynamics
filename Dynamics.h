#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Dynamics : public AirwindowsCompressorUIPlugin {
	public:
		Dynamics(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		//begin Gate
		bool WasNegativeL;
		int ZeroCrossL;
		double gaterollerL;
		double gateL;

		bool WasNegativeR;
		int ZeroCrossR;
		double gaterollerR;
		double gateR;
		//end Gate

		//begin ButterComp
		double controlAposL;
		double controlAnegL;
		double controlBposL;
		double controlBnegL;
		double targetposL;
		double targetnegL;
		double avgLA;
		double avgLB;
		double nvgLA;
		double nvgLB;

		double controlAposR;
		double controlAnegR;
		double controlBposR;
		double controlBnegR;
		double targetposR;
		double targetnegR;
		double avgRA;
		double avgRB;
		double nvgRA;
		double nvgRB;
		bool flip;
		//end ButterComp

		uint32_t fpdL;
		uint32_t fpdR;
		//default stuff
	};

