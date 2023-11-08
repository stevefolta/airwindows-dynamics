#include "ButterComp2Plugin.h"


ButterComp2Plugin::ButterComp2Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	controlAposL = 1.0;
	controlAnegL = 1.0;
	controlBposL = 1.0;
	controlBnegL = 1.0;
	targetposL = 1.0;
	targetnegL = 1.0;
	lastOutputL = 0.0;

	controlAposR = 1.0;
	controlAnegR = 1.0;
	controlBposR = 1.0;
	controlBnegR = 1.0;
	targetposR = 1.0;
	targetnegR = 1.0;
	lastOutputR = 0.0;

	flip = false;
	A = 0.0;
	B = 0.5;
	C = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


const std::vector<std::string> parameter_names = {
	"Compress", "Output", "Dry/Wet",
	};

const std::vector<std::string>& ButterComp2Plugin::parameter_names()
{
	return ::parameter_names;
}

double ButterComp2Plugin::get_parameter(clap_id param_id)
{
	switch (param_id) {
		case 0: return A;
		case 1: return B;
		case 2: return C;
		}
	return 0.0;
}

void ButterComp2Plugin::set_parameter(clap_id param_id, double value)
{
	switch (param_id) {
		case 0: A = value; break;
		case 1: B = value; break;
		case 2: C = value; break;
		}
}

bool ButterComp2Plugin::param_value_to_text(clap_id param_id, double value, char* out_buffer, uint32_t out_buffer_capacity)
{
	if (param_id == 1)
		value *= 2.0;
	return AirwindowsCompressorUIPlugin::param_value_to_text(param_id, value, out_buffer, out_buffer_capacity);
}

bool ButterComp2Plugin::param_text_to_value(clap_id param_id, const char* param_value_text, double* value_out)
{
	bool ok = AirwindowsCompressorUIPlugin::param_text_to_value(param_id, param_value_text, value_out);
	if (ok && param_id == 1)
		*value_out /= 2.0;
	return ok;
}




