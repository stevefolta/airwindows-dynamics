#include "Pressure4Plugin.h"
#include <stdlib.h>


Pressure4Plugin::Pressure4Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	A = 0.0;
	B = 0.2;
	C = 1.0;
	D = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	muSpeedA = 10000;
	muSpeedB = 10000;
	muCoefficientA = 1;
	muCoefficientB = 1;
	muVary = 1;
	flip = false;	
}


static const std::vector<std::string> parameter_names = {
	"Pressure", "Speed", "Mewiness", "Output Gain",
	};

const std::vector<std::string>& Pressure4Plugin::parameter_names()
{
	return ::parameter_names;
}

double Pressure4Plugin::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		case 3: return D;
		}
	return 0.0;
}

void Pressure4Plugin::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		case 3: D = value; break;
		}
}



