/* drawHBar.hpp
 * Copyright (C) 2018 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_DRAWHBAR_HPP_
#define BWIDGETS_DRAWHBAR_HPP_

#include <cairo/cairo.h>
#include "../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws a horizontal pseudo 3d bar in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param x0  X position.
 *  @param y0  Y position.
 *  @param width  Bar width.
 *  @param height  Bar height.
 *  @param min  Start of activated (highlighted) part of the bar. Relative
 *  value [0..1].
 *  @param max  End of activated (highlighted) part of the bar. Relative
 *  value [0..1].
 *  @param fgColor  RGBA color for the activated part.
 *  @param bgColor  Bar RGBA color.
 */
inline void drawHBar    (cairo_t* cr, const double x0, const double y0, const double width, const double height, 
                         const double min, const double max, 
                         const BStyles::Color fgColor, const BStyles::Color bgColor)
{
    const double x2 = x0 + min * width;
    const double x3 = x0 + max * width;

    cairo_save (cr);

    // Frame
    cairo_set_line_width (cr, 1.0);
    cairo_rectangle (cr, x0, y0, width, height);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor));
    cairo_stroke (cr);

    // Foreground
    cairo_rectangle (cr, x0 + 1, y0 + 1, width - 2, height - 2);
    cairo_clip (cr);
    cairo_rectangle (cr, x2, y0, x3 - x2, height);
    cairo_set_source_rgba (cr, CAIRO_RGBA(fgColor));
    cairo_fill (cr);

    cairo_restore (cr);
}

#endif /*  BWIDGETS_DRAWHBAR_HPP_ */