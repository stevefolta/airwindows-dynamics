#include "ParameterWidget.h"
#include "Label.h"
#include "HorizontalSlider.h"
#include "AirwindowsCompressorUIPlugin.h"

double ParameterWidget::label_size_factor = 0.4;
double ParameterWidget::spacer_factor = 0.1;


ParameterWidget::ParameterWidget(CairoGUI* gui_in, uint32_t id_in, AirwindowsCompressorUIPlugin* plugin_in, Rect rect_in)
	: Widget(gui_in, rect_in), id(id_in), plugin(plugin_in)
{
	name_label = new Label(gui_in, plugin->parameter_names[id]);
	name_label->font_weight = CAIRO_FONT_WEIGHT_NORMAL;
	value_label = new Label(gui_in, "--");
	value_label->font_weight = CAIRO_FONT_WEIGHT_NORMAL;
	value_label->justification = Label::RightJustified;
	slider = new HorizontalSlider(gui_in);
}

ParameterWidget::~ParameterWidget()
{
	delete name_label;
	delete value_label;
	delete slider;
}


void ParameterWidget::paint()
{
	name_label->paint();
	value_label->paint();
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
	auto old_value = slider->value;
	slider->mouse_moved(x, y);
	if (slider->value != old_value)
		set_value(slider->value);
}


void ParameterWidget::layout()
{
	double label_height = rect.height * label_size_factor;
	double value_label_width_factor = 0.25;
	double name_label_width = rect.width * (1 - value_label_width_factor);
	name_label->rect = { rect.x, rect.y, name_label_width, label_height };
	value_label->rect = { rect.x + name_label_width, rect.y, rect.width - name_label_width, label_height };
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
	char value_str[64];
	value_str[0] = 0;
	plugin->param_value_to_text(id, value, value_str, sizeof(value_str));
	value_label->label = value_str;
}



