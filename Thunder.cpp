#include "Thunder.h"


Thunder::Thunder(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Thunder", "Output Trim" };

	A = 0.0;
	B = 1.0;

	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	muSpeedA = 10000;
	muSpeedB = 10000;
	muCoefficientA = 1;
	muCoefficientB = 1;
	muVary = 1;
	gateL = 0.0;
	gateR = 0.0;
	iirSampleAL = 0.0;
	iirSampleBL = 0.0;
	iirSampleAR = 0.0;
	iirSampleBR = 0.0;
	iirSampleAM = 0.0;
	iirSampleBM = 0.0;
	iirSampleCM = 0.0;
	flip = false;	
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double Thunder::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		}
	return 0.0;
}

void Thunder::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		}
}


