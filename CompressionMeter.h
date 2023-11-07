#pragma once

#include "Widget.h"


class CompressionMeter : public Widget {
	public:
		CompressionMeter(CairoGUI* gui_in, Rect rect_in = {})
			: Widget(gui_in, rect_in) {}

		double gain = 1.0;

		void paint();

		static double max_decibels;
		static Color background_color, meter_color, border_color;
		static double border_width;

	protected:
	};

