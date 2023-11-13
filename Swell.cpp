#include "Swell.h"


Swell::Swell(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Threshold", "Swell", "Dry/Wet" };
	meter_max_db = 60.0;

	A = 0.9;
	B = 0.5;
	C = 1.0;

	swellL = 0.0;
	swellR = 0.0;
	louderL = false;
	louderR = false;
	
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}



