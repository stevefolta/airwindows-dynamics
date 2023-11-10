#include "DigitalBlack.h"
#include "CompressionMeter.h"


DigitalBlack::DigitalBlack(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Threshold", "Dry/Wet" };
	meter_max_db = 40.0;

	A = 0.0;
	B = 1.0;
	WasNegativeL = false;
	ZeroCrossL = 0;
	gaterollerL = 0.0;
	WasNegativeR = false;
	ZeroCrossR = 0;
	gaterollerR = 0.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


