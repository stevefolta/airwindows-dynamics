#include "curvePlugin.h"
#include <math.h>


curvePlugin::curvePlugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	gain = 1.0;
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
}


double curvePlugin::get_parameter(clap_id param_id)
{
	return 0.0;
}

void curvePlugin::set_parameter(clap_id param_id, double value)
{
}


