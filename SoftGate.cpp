#include "SoftGate.h"


SoftGate::SoftGate(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Threshold", "Darken", "Silence" };
	meter_max_db = 40.0;

	A = 0.5;
	B = 0.5;
	C = 0.0;
	storedL[0] = storedL[1] = 0.0;
	diffL = 0.0;
	storedR[0] = storedR[1] = 0.0;
	diffR = 0.0;
	gate = 1.1;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double SoftGate::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		}
	return 0.0;
}

void SoftGate::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		}
}


