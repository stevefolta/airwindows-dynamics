#include "CompressionMeter.h"
#include "CairoGUI.h"
#include "Decibels.h"


Color CompressionMeter::background_color = { 1.0, 1.0, 1.0 };
Color CompressionMeter::meter_color = { 0.0, 1.0, 0.0 };
Color CompressionMeter::border_color = { 0.0, 0.0, 0.0 };
Color CompressionMeter::tick_color = { 0.0, 0.0, 0.0, 0.4 };
double CompressionMeter::border_width = 1.0;
double CompressionMeter::tick_width = 0.3;
double CompressionMeter::tick_5_width = 0.6;
double CompressionMeter::tick_line_width = 0.5;


void CompressionMeter::paint()
{
	auto cairo = gui->cairo();
	cairo_save(cairo);

	// Background.
	cairo_rectangle(cairo, rect.x, rect.y, rect.width, rect.height);
	use_color(background_color);
	cairo_fill(cairo);

	// Decibel gain reduction.
	if (gain < 0.0)
		gain = -gain;
	if (gain < 1.0) {
		auto decibels = -gain_to_decibels(gain);
		if (decibels > max_decibels)
			decibels = max_decibels;
		Rect meter_rect = rect;
		meter_rect.height *= decibels / max_decibels;
		cairo_rectangle(cairo, meter_rect.x, meter_rect.y, meter_rect.width, meter_rect.height);
		use_color(meter_color);
		cairo_fill(cairo);
		}

	// Ticks.
	int tick_db = 1;
	double tick_spacing = rect.height / max_decibels;
	double tick_y = rect.y + tick_db * tick_spacing;
	double tick_x = rect.x + rect.width * (1 - tick_width) / 2;
	double tick_abs_width = rect.width * tick_width;
	double tick_5_x = rect.x + rect.width * (1 - tick_5_width) / 2;
	double tick_5_abs_width = rect.width * tick_5_width;
	for (; tick_db < max_decibels; tick_db += 1.0) {
		if (tick_db % 5 == 0) {
			cairo_move_to(cairo, tick_5_x, tick_y);
			cairo_rel_line_to(cairo, tick_5_abs_width, 0);
			}
		else {
			cairo_move_to(cairo, tick_x, tick_y);
			cairo_rel_line_to(cairo, tick_abs_width, 0);
			}
		use_color(tick_color);
		cairo_set_line_width(cairo, tick_line_width);
		cairo_stroke(cairo);
		tick_y += tick_spacing;
		}

	// Border.
	cairo_rectangle(cairo, rect.x, rect.y, rect.width, rect.height);
	use_color(border_color);
	cairo_set_line_width(cairo, border_width);
	cairo_stroke(cairo);

	cairo_restore(cairo);
}



