/* drawPad.hpp
 * Copyright (C) 2018 - 2023  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
 
#ifndef BWIDGETS_DRAWPAD_HPP_
#define BWIDGETS_DRAWPAD_HPP_

#include <cairo/cairo.h>
#include "../../BUtilities/cairoplus.h"
#include <cmath>
#include "../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws someting like an LED pad in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param x0  X position.
 *  @param y0  Y position.
 *  @param width  Pad width.
 *  @param height  Pad height.
 *  @param fgColor  RGBA color.
 */
inline void drawButton (cairo_t* cr, double x, double y, double width, double height, const BStyles::Color fgColor)
{
	if ((width <= 0) || (height <= 0)) return;

	// Draw button
	BStyles::Color illuminated = fgColor.illuminate (0.05);
	BStyles::Color darkened = fgColor.illuminate (-0.33);
	cairo_pattern_t* pat = cairo_pattern_create_radial (x + width / 2, y + height / 2, 0.125 * width, x + width / 2, y + height / 2, 0.5 * width);

	cairo_pattern_add_color_stop_rgba (pat, 0.0, CAIRO_RGBA (illuminated));
	cairo_pattern_add_color_stop_rgba (pat, 1.0, CAIRO_RGBA (darkened));

	double rad = ((width < 20) || (height < 20) ?  (width < height ? width : height) / 4 : 5);
	cairoplus_rectangle_rounded (cr, x, y, width, height, rad, 0b1111);
	cairo_set_source (cr, pat);
	cairo_fill (cr);
	cairo_pattern_destroy (pat);
}

#endif /* BWIDGETS_DRAWPAD_HPP_ */
