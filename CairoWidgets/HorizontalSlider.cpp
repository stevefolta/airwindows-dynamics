#include "HorizontalSlider.h"
#include "CairoGUI.h"
#include <cairo/cairo.h>


void HorizontalSlider::paint()
{
	auto cairo = gui->cairo();
	cairo_save(cairo);

	// Track.
	cairo_rectangle(cairo, rect.x, rect.y + (rect.height - track_height) / 2, rect.width, track_height);
	cairo_set_source_rgb(cairo, track_color.red, track_color.green, track_color.blue);
	cairo_fill(cairo);

	// Thumb.
	double thumb_x = (value - min_value) * (rect.width - thumb_width) / (max_value - min_value);
	Rect thumb_rect = { rect.x + thumb_x, rect.y, thumb_width, rect.height };
	rounded_rect(thumb_rect, thumb_width / 4.0);
	cairo_set_source_rgb(cairo, thumb_fill_color.red, thumb_fill_color.green, thumb_fill_color.blue);
	cairo_fill_preserve(cairo);
	cairo_set_source_rgb(cairo, thumb_stroke_color.red, thumb_stroke_color.green, thumb_stroke_color.blue);
	cairo_set_line_width(cairo, thumb_line_width);
	cairo_stroke(cairo);

	cairo_restore(cairo);
}


void HorizontalSlider::mouse_pressed(int x, int y)
{
	/***/
}

bool HorizontalSlider::mouse_released(int x, int y)
{
	/***/
	return contains(x, y);
}

void HorizontalSlider::mouse_moved(int x, int y)
{
	/***/
}


