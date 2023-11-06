#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pressure4Plugin : public AirwindowsCompressorUIPlugin {
	public:
		Pressure4Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host);

		const std::vector<std::string>& parameter_names();
		bool get_param_value(clap_id param_id, double* value_out);
		void set_param_value(clap_id param_id, double value);

		void processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
		void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

	protected:
		double muVary;
		double muAttack;
		double muNewSpeed;
		double muSpeedA;
		double muSpeedB;
		double muCoefficientA;
		double muCoefficientB;
		uint32_t fpdL;
		uint32_t fpdR;
		bool flip;

		float A;
		float B;
		float C; //parameters. Always 0-1, and we scale/alter them elsewhere.
		float D;
	};

