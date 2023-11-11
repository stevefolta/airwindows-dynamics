#include "Point.h"


Point::Point(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Input Trim", "Point", "Reaction Speed" };

	A = 0.5;
	B = 0.5;
	C = 0.5;
	nibAL = 0.0;
	nobAL = 0.0;
	nibBL = 0.0;
	nobBL = 0.0;
	nibAR = 0.0;
	nobAR = 0.0;
	nibBR = 0.0;
	nobBR = 0.0;
	
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	fpFlip = true;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}


bool Point::param_value_to_text(clap_id param_id, double value, char* out_buffer, uint32_t out_buffer_capacity)
{
	if (param_id == 0) {
		snprintf(out_buffer, out_buffer_capacity, "%g dB", value * 24.0 - 12.0);
		return true;
		}

	if (param_id == 1)
		value = value * 2.0 - 1.0;
	return AirwindowsCompressorUIPlugin::param_value_to_text(param_id, value, out_buffer, out_buffer_capacity);
}

bool Point::param_text_to_value(clap_id param_id, const char* param_value_text, double* value_out)
{
	if (!AirwindowsCompressorUIPlugin::param_text_to_value(param_id, param_value_text, value_out))
		return false;

	if (param_id == 0)
		*value_out = (*value_out + 12.0) / 24.0;
	else if (param_id == 1)
		*value_out = (*value_out + 1.0) / 2.0;
	else if (param_id == 1)
		*value_out = (*value_out + 1.0) / 2.0;
	return true;
}



