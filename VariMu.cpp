#include "VariMu.h"


VariMu::VariMu(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Intensity", "Speed", "Output", "Dry/Wet" };

	muSpeedAL = 10000;
	muSpeedBL = 10000;
	muCoefficientAL = 1;
	muCoefficientBL = 1;
	muVaryL = 1;
	previousL = 0.0;

	muSpeedAR = 10000;
	muSpeedBR = 10000;
	muCoefficientAR = 1;
	muCoefficientBR = 1;
	muVaryR = 1;
	previousR = 0.0;
	flip = false;

	A = 0.0;
	B = 0.5;
	C = 1.0;
	D = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double VariMu::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		case 3: return D;
		}
	return 0.0;
}

void VariMu::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		case 3: D = value; break;
		}
}


