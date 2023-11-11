#include "PodcastDeluxe.h"

PodcastDeluxe::PodcastDeluxe(const clap_plugin_descriptor_t* descriptor, const clap_host_t* host)
	: AirwindowsCompressorUIPlugin(descriptor, host)
{
	parameter_names = { "Boost" };

	A = 0.5;
	
	for(int count = 0; count < 502; count++) {
		d1L[count] = 0.0;
		d2L[count] = 0.0;
		d3L[count] = 0.0;
		d4L[count] = 0.0;
		d5L[count] = 0.0;
		d1R[count] = 0.0;
		d2R[count] = 0.0;
		d3R[count] = 0.0;
		d4R[count] = 0.0;
		d5R[count] = 0.0;
	}
	c1L = 2.0; c2L = 2.0; c3L = 2.0; c4L = 2.0; c5L = 2.0; //startup comp gains	
	lastSampleL = lastOutSampleL = lastSampleR = lastOutSampleR = 0.0;
	tap1 = 1; tap2 = 1; tap3 = 1; tap4 = 1; tap5 = 1;
	maxdelay1 = 9001; maxdelay2 = 9001; maxdelay3 = 9001; maxdelay4 = 9001; maxdelay5 = 9001;
	c1R = 2.0; c2R = 2.0; c3R = 2.0; c4R = 2.0; c5R = 2.0; //startup comp gains	
	
	fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
	fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
	//this is reset: values being initialized only once. Startup values, whatever they are.
}



