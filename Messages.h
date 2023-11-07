#pragma once


enum {
	// Main thread -> audio thread.
	SetParameter, 	// int_value: parameter id, double_value: value.

	// Audio thread -> main thread.
	MostCompression, 	// double_value: minimum gain.
	};
