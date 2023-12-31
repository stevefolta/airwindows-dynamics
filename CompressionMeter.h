#pragma once

#include "Widget.h"


class CompressionMeter : public Widget {
	public:
		CompressionMeter(CairoGUI* gui_in, Rect rect_in = {})
			: Widget(gui_in, rect_in) {}

		double gain = 1.0;
		double max_decibels = 20.0;

		void paint();

		static Color background_color, meter_color, border_color, tick_color;
		static double border_width, tick_width, tick_5_width, tick_line_width;

	protected:
	};

