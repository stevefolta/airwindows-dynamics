#include "BlockParty.h"


BlockParty::BlockParty(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Pound", "Dry/Wet" };
	meter_max_db = 10.0;

	A = 0.0;
	B = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;

	muSpeedAL = 10000;
	muSpeedBL = 10000;
	muSpeedCL = 10000;
	muSpeedDL = 10000;
	muSpeedEL = 10000;
	muCoefficientAL = 1;
	muCoefficientBL = 1;
	muCoefficientCL = 1;
	muCoefficientDL = 1;
	muCoefficientEL = 1;
	lastCoefficientAL = 1;
	lastCoefficientBL = 1;
	lastCoefficientCL = 1;
	lastCoefficientDL = 1;
	mergedCoefficientsL = 1;
	thresholdL = 1.0;
	thresholdBL = 1.0;
	muVaryL = 1;

	muSpeedAR = 10000;
	muSpeedBR = 10000;
	muSpeedCR = 10000;
	muSpeedDR = 10000;
	muSpeedER = 10000;
	muCoefficientAR = 1;
	muCoefficientBR = 1;
	muCoefficientCR = 1;
	muCoefficientDR = 1;
	muCoefficientER = 1;
	lastCoefficientAR = 1;
	lastCoefficientBR = 1;
	lastCoefficientCR = 1;
	lastCoefficientDR = 1;
	mergedCoefficientsR = 1;
	thresholdR = 1.0;
	thresholdBR = 1.0;
	muVaryR = 1;

	count = 1;
	fpFlip = true;

	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double BlockParty::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		}
	return 0.0;
}

void BlockParty::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		}
}


