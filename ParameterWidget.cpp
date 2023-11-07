#include "ParameterWidget.h"
#include "Label.h"
#include "HorizontalSlider.h"

double ParameterWidget::label_size_factor = 0.4;
double ParameterWidget::spacer_factor = 0.1;

ParameterWidget::ParameterWidget(CairoGUI* gui_in, uint32_t id_in, std::string name, Rect rect_in)
	: Widget(gui_in, rect_in), id(id_in)
{
	label = new Label(gui_in, name);
	label->font_weight = CAIRO_FONT_WEIGHT_NORMAL;
	slider = new HorizontalSlider(gui_in);
}

ParameterWidget::~ParameterWidget()
{
	delete label;
	delete slider;
}


void ParameterWidget::paint()
{
	label->paint();
	slider->paint();
}


void ParameterWidget::mouse_pressed(int x, int y)
{
	if (slider->contains(x, y))
		slider->mouse_pressed(x, y);
}

bool ParameterWidget::mouse_released(int x, int y)
{
	return slider->mouse_released(x, y);
}

void ParameterWidget::mouse_moved(int x, int y)
{
	slider->mouse_moved(x, y);
}


void ParameterWidget::layout()
{
	double label_height = rect.height * label_size_factor;
	label->rect = { rect.x, rect.y, rect.width, label_height };
	double height_used = label_height + spacer_factor * rect.height;
	slider->rect = { rect.x, rect.y + height_used, rect.width, rect.height - height_used };
}


double ParameterWidget::value()
{
	return slider->value;
}

void ParameterWidget::set_value(double value)
{
	slider->value = value;
}



