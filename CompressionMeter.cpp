#include "CompressionMeter.h"
#include "CairoGUI.h"
#include "Decibels.h"


double CompressionMeter::max_decibels = 20.0;
Color CompressionMeter::background_color = { 1.0, 1.0, 1.0 };
Color CompressionMeter::meter_color = { 0.0, 1.0, 0.0 };
Color CompressionMeter::border_color = { 0.0, 0.0, 0.0 };
double CompressionMeter::border_width = 1.0;


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

	// Border.
	cairo_rectangle(cairo, rect.x, rect.y, rect.width, rect.height);
	use_color(border_color);
	cairo_set_line_width(cairo, border_width);
	cairo_stroke(cairo);

	cairo_restore(cairo);
}



