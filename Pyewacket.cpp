#include "Pyewacket.h"


Pyewacket::Pyewacket(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Input Gain", "Release", "Output Gain" };
	meter_max_db = 30.0;

	A = 0.5;
	B = 0.5;
	C = 0.5;
	chase = 1.0;
	lastrectifierL = 0.0;
	lastrectifierR = 0.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


double Pyewacket::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		}
	return 0.0;
}

void Pyewacket::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		}
}


