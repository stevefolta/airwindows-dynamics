#pragma once

#include "Widget.h"


class HorizontalSlider : public Widget {
	public:
		HorizontalSlider(CairoGUI* gui_in, Rect rect_in = {})
			: Widget(gui_in, rect_in) {}

		double value = 0.0;
		double min_value = 0.0, max_value = 1.0;

		double track_height = 2.0, thumb_width = 10.0, thumb_line_width = 2.0;
		Color track_color = { 0.5, 0.5, 0.5 };
		Color thumb_stroke_color = { 0.0, 0.0, 0.0 };
		Color thumb_fill_color = { 1.0, 1.0, 1.0 };

		void paint();
		void mouse_pressed(int x, int y);
		bool mouse_released(int x, int y);
		void mouse_moved(int x, int y);

	protected:
		bool pressed = false;
	};
