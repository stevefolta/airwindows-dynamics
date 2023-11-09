#include "AirwindowsCompressorUIPlugin.h"
#include "Pressure4Plugin.h"
#include "Pressure5.h"
#include "curvePlugin.h"
#include "ButterComp2Plugin.h"
#include "Pop2Plugin.h"
#include "Pop.h"
#include "VariMu.h"
#include "PurestSquish.h"
#include "Dynamics.h"
#include <vector>
#include <string_view>
#include <iostream>


#define ID_PREFIX "airwindows.net.stevefolta.compressors."
static const char* default_features[] = {
	CLAP_PLUGIN_FEATURE_AUDIO_EFFECT,
	CLAP_PLUGIN_FEATURE_COMPRESSOR,
	nullptr,
	};

static const std::vector<clap_plugin_descriptor_t> our_descriptors = {
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "Pressure4",
		.name = "Pressure4 UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "Pressure5",
		.name = "Pressure5 UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "curve",
		.name = "curve UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "ButterComp2",
		.name = "ButterComp2 UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "Pop2",
		.name = "Pop2 UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "Pop",
		.name = "Pop UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "VariMu",
		.name = "VariMu UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "PurestSquish",
		.name = "PurestSquish UI",
		.vendor = "airwindows / Steve Folta",
		.features = default_features,
		},
	{
		.clap_version = CLAP_VERSION_INIT,
		.id = ID_PREFIX "Dynamics",
		.name = "Dynamics UI",
		.vendor = "airwindows / Steve Folta",
		.features = (const char*[]) {
			CLAP_PLUGIN_FEATURE_AUDIO_EFFECT,
			CLAP_PLUGIN_FEATURE_COMPRESSOR,
			CLAP_PLUGIN_FEATURE_GATE,
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
			std::string_view id = descriptor->id;
			if (id == ID_PREFIX "Pressure4")
				return new Pressure4Plugin(descriptor, host);
			else if (id == ID_PREFIX "Pressure5")
				return new Pressure5(descriptor, host);
			else if (id == ID_PREFIX "curve")
				return new curvePlugin(descriptor, host);
			else if (id == ID_PREFIX "ButterComp2")
				return new ButterComp2Plugin(descriptor, host);
			else if (id == ID_PREFIX "Pop2")
				return new Pop2Plugin(descriptor, host);
			else if (id == ID_PREFIX "Pop")
				return new Pop(descriptor, host);
			else if (id == ID_PREFIX "VariMu")
				return new VariMu(descriptor, host);
			else if (id == ID_PREFIX "PurestSquish")
				return new PurestSquish(descriptor, host);
			else if (id == ID_PREFIX "Dynamics")
				return new Dynamics(descriptor, host);
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

