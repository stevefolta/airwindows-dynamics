#pragma once

#include "AirwindowsCompressorUIPlugin.h"


class Pressure4Plugin : public AirwindowsCompressorUIPlugin {
	public:
		Pressure4Plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
			: AirwindowsCompressorUIPlugin(descriptor, host) {}

	protected:
	};

