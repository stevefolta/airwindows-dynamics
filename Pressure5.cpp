#include "Pressure5.h"
#include "CompressionMeter.h"


Pressure5::Pressure5(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Pressure", "Speed", "Mewiness", "PawClaw", "Output", "Dry/Wet" };
	meter_max_db = 40.0;

	A = 0.0;
	B = 0.25;
	C = 1.0;
	D = 0.5;
	E = 0.5;
	F = 1.0;

	muSpeedA = 10000;
	muSpeedB = 10000;
	muCoefficientA = 1;
	muCoefficientB = 1;
	muVary = 1;
	flip = false;
	for (int x = 0; x < fix_total; x++) {fixA[x] = 0.0; fixB[x] = 0.0;}
	lastSampleL = 0.0;
	wasPosClipL = false;
	wasNegClipL = false;
	lastSampleR = 0.0;
	wasPosClipR = false;
	wasNegClipR = false;
	for (int x = 0; x < 16; x++) {intermediateL[x] = 0.0; intermediateR[x] = 0.0;}
	slewMax = 0.0;

	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double Pressure5::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		case 3: return D;
		case 4: return E;
		case 5: return F;
		}
	return 0.0;
}

void Pressure5::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		case 3: D = value; break;
		case 4: E = value; break;
		case 5: F = value; break;
		}
}


