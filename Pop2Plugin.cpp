#include "Pop2Plugin.h"


Pop2Plugin::Pop2Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Compress", "Attack", "Release", "Drive", "Dry/Wet", };

	A = 0.5;
	B = 0.5;
	C = 0.5;
	D = 0.5;
	E = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;

	lastSampleL = 0.0;
	wasPosClipL = false;
	wasNegClipL = false;
	lastSampleR = 0.0;
	wasPosClipR = false;
	wasNegClipR = false;
	for (int x = 0; x < 16; x++) {intermediateL[x] = 0.0; intermediateR[x] = 0.0;}	

	muVaryL = 0.0;
	muAttackL = 0.0;
	muNewSpeedL = 1000.0;
	muSpeedAL = 1000.0;
	muSpeedBL = 1000.0;
	muCoefficientAL = 1.0;
	muCoefficientBL = 1.0;

	muVaryR = 0.0;
	muAttackR = 0.0;
	muNewSpeedR = 1000.0;
	muSpeedAR = 1000.0;
	muSpeedBR = 1000.0;
	muCoefficientAR = 1.0;
	muCoefficientBR = 1.0;

	flip = false;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}



