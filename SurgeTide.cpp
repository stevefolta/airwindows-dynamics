#include "SurgeTide.h"


SurgeTide::SurgeTide(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "SurgeNode", "SurgeRate", "Dry/Wet" };

	A = 0.5;
	B = 0.3;
	C = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	flip = true;
	chaseA = 0.0;
	chaseB = 0.0;
	chaseC = 0.0;	
	//this is reset: values being initialized only once. Startup values, whatever they are.
}



