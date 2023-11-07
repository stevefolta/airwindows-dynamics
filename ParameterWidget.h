#pragma once

#include "Widget.h"
#include <string>

class Label;
class HorizontalSlider;


class ParameterWidget : public Widget {
	public:
		ParameterWidget(CairoGUI* gui_in, uint32_t id, std::string name, Rect rect_in = {});
		~ParameterWidget();

		void paint();
		void mouse_pressed(int x, int y);
		bool mouse_released(int x, int y);
		void mouse_moved(int x, int y);

		void layout();
		double value();
		void set_value(double value);

		uint32_t id;

		static double label_size_factor, spacer_factor;

	protected:
		Label* label;
		HorizontalSlider* slider;
	};

