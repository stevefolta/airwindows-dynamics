#include "Compresaturator.h"


Compresaturator::Compresaturator(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Drive", "Clamp", "Expand", "Output", "Dry/Wet" };

	A = 0.5; //-12 to +12 dB
	B = 0.5; //0 to 100%
	C = 0.5; //50 to 5000 samples, default 500
	D = 1.0;
	E = 1.0;

	for(int count = 0; count < 10990; count++) {dL[count] = 0.0; dR[count] = 0.0;}
	dCount = 0;
	lastWidthL = 500;
	padFactorL = 0;
	lastWidthR = 500;
	padFactorR = 0;

	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double Compresaturator::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		case 3: return D;
		case 4: return E;
		}
	return 0.0;
}

void Compresaturator::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		case 3: D = value; break;
		case 4: E = value; break;
		}
}


