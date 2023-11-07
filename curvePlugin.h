#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class curvePlugin : public AirwindowsCompressorUIPlugin {
	public:
		curvePlugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		const std::vector<std::string>& parameter_names();
		double get_parameter(clap_id param_id);
		void set_parameter(clap_id param_id, double value);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double gain;
		uint32_t fpdL;
		uint32_t fpdR;
	};

