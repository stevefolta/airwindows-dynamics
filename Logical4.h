#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Logical4 : public AirwindowsCompressorUIPlugin {
	public:
		Logical4(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		//begin ButterComp
		double controlAposL;
		double controlAnegL;
		double controlBposL;
		double controlBnegL;
		double targetposL;
		double targetnegL;
		double controlAposBL;
		double controlAnegBL;
		double controlBposBL;
		double controlBnegBL;
		double targetposBL;
		double targetnegBL;
		double controlAposCL;
		double controlAnegCL;
		double controlBposCL;
		double controlBnegCL;
		double targetposCL;
		double targetnegCL;
		double avgAL;
		double avgBL;
		double avgCL;
		double avgDL;
		double avgEL;
		double avgFL;
		double nvgAL;
		double nvgBL;
		double nvgCL;
		double nvgDL;
		double nvgEL;
		double nvgFL;
		//end ButterComp

		//begin Power Sag
		double dL[1000];
		double controlL;
		double bL[1000];
		double controlBL;
		double cL[1000];
		double controlCL;
		//end Power Sag

		//begin ButterComp
		double controlAposR;
		double controlAnegR;
		double controlBposR;
		double controlBnegR;
		double targetposR;
		double targetnegR;
		double controlAposBR;
		double controlAnegBR;
		double controlBposBR;
		double controlBnegBR;
		double targetposBR;
		double targetnegBR;
		double controlAposCR;
		double controlAnegCR;
		double controlBposCR;
		double controlBnegCR;
		double targetposCR;
		double targetnegCR;
		double avgAR;
		double avgBR;
		double avgCR;
		double avgDR;
		double avgER;
		double avgFR;
		double nvgAR;
		double nvgBR;
		double nvgCR;
		double nvgDR;
		double nvgER;
		double nvgFR;
		//end ButterComp

		//begin Power Sag
		double dR[1000];
		double controlR;
		double bR[1000];
		double controlBR;
		double cR[1000];
		double controlCR;
		//end Power Sag

		int gcount;


		bool fpFlip;
		//default stuff
		uint32_t fpdL;
		uint32_t fpdR;
	};

