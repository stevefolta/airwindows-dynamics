#include "PurestSquish.h"
#include "CompressionMeter.h"


PurestSquish::PurestSquish(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Squish", "BassBlm", "Output", "Dry/Wet" };
	meter_max_db = 30.0;

	A = 0.0;
	B = 0.0;
	C = 1.0;
	D = 1.0;

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
	iirSampleAL = 0.0;
	iirSampleBL = 0.0;
	iirSampleCL = 0.0;
	iirSampleDL = 0.0;
	iirSampleEL = 0.0;
	lastCoefficientAL = 1;
	lastCoefficientBL = 1;
	lastCoefficientCL = 1;
	lastCoefficientDL = 1;
	mergedCoefficientsL = 1;
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
	iirSampleAR = 0.0;
	iirSampleBR = 0.0;
	iirSampleCR = 0.0;
	iirSampleDR = 0.0;
	iirSampleER = 0.0;
	lastCoefficientAR = 1;
	lastCoefficientBR = 1;
	lastCoefficientCR = 1;
	lastCoefficientDR = 1;
	mergedCoefficientsR = 1;
	muVaryR = 1;

	count = 1;
	fpFlip = true;

	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


