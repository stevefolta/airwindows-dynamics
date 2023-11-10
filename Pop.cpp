#include "Pop.h"


Pop::Pop(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Intensity", "Output", "Dry/Wet" };
	meter_max_db = 30.0;

	A = 0.3;
	B = 1.0;
	C = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;

	for(int count = 0; count < 10000; count++) {dL[count] = 0; dR[count] = 0;}
	delay = 0;
	flip = false;

	muSpeedAL = 10000;
	muSpeedBL = 10000;
	muCoefficientAL = 1;
	muCoefficientBL = 1;
	thickenL = 1;
	muVaryL = 1;
	previousL = 0.0;
	previous2L = 0.0;
	previous3L = 0.0;
	previous4L = 0.0;
	previous5L = 0.0;

	muSpeedAR = 10000;
	muSpeedBR = 10000;
	muCoefficientAR = 1;
	muCoefficientBR = 1;
	thickenR = 1;
	muVaryR = 1;
	previousR = 0.0;
	previous2R = 0.0;
	previous3R = 0.0;
	previous4R = 0.0;
	previous5R = 0.0;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


