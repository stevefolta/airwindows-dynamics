#include "Compresaturator.h"


Compresaturator::Compresaturator(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Drive", "Clamp", "Expand", "Output", "Dry/Wet" };

	A = 0.5; //-12 to +12 dB
	B = 0.5; //0 to 100%
	C = 0.5; //50 to 5000 samples, default 500
	D = 1.0;
	E = 1.0;

	for(int count = 0; count < 10990; count++) {dL[count] = 0.0; dR[count] = 0.0;}
	dCount = 0;
	lastWidthL = 500;
	padFactorL = 0;
	lastWidthR = 500;
	padFactorR = 0;

	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


