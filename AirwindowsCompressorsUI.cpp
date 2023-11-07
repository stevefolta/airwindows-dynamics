#include "AirwindowsCompressorUIPlugin.h"
#include "Pressure4Plugin.h"
#include "curvePlugin.h"
#include <vector>
#include <string_view>
#include <iostream>


static const std::vector<clap_plugin_descriptor_t> our_descriptors = {
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = "airwindows.net.stevefolta.Pressure4",
		.name = "Pressure4 UI",
		.vendor = "airwindows / Steve Folta",
		.features = (const char*[]) {
			CLAP_PLUGIN_FEATURE_AUDIO_EFFECT,
			CLAP_PLUGIN_FEATURE_COMPRESSOR,
			nullptr,
			},
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = "airwindows.net.stevefolta.curve",
		.name = "curve UI",
		.vendor = "airwindows / Steve Folta",
		.features = (const char*[]) {
			CLAP_PLUGIN_FEATURE_AUDIO_EFFECT,
			CLAP_PLUGIN_FEATURE_COMPRESSOR,
			nullptr,
			},
		},
	};

class AirwindowsCompressorsPluginFactory: public CLAPPluginFactory {
	public:
		const std::vector<clap_plugin_descriptor_t>& descriptors() {
			return our_descriptors;
			}

		CLAPPlugin* create_plugin(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host) {
			std::string_view name = descriptor->name;
			if (name == "Pressure4 UI")
				return new Pressure4Plugin(descriptor, host);
			else if (name == "curve UI")
				return new curvePlugin(descriptor, host);
			return nullptr;
			}
	};
AirwindowsCompressorsPluginFactory factory;

DECLARE_CLAP_PLUGIN_ENTRY(factory)

#ifdef DEBUG_UNLOADING
extern "C" __attribute__((destructor)) void at_unload()
{
	std::cerr << "- Unloading." << std::endl;
}
#endif

