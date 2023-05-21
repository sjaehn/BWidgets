/* drawKnob.hpp
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

#ifndef BWIDGETS_DRAWKNOB_HPP_
#define BWIDGETS_DRAWKNOB_HPP_

#include <cairo/cairo.h>
#include <cmath>
#include "../../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws a knob in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param xc  X center position.
 *  @param yc  Y center position.
 *  @param radius  Knob radius.
 *  @param height  Knob pseudo 3D height.
 *  @param fgColor  RGBA color for the knob top.
 *  @param bgColor  Knob body RGBA color.
 */
inline void drawKnob (cairo_t* cr, const double xc, const double yc, const double radius, const double height, const BStyles::Color fgColor, const BStyles::Color bgColor)
{
    cairo_save (cr);

    cairo_set_line_width (cr, 1.0);
    cairo_rectangle (cr, xc - radius, yc - radius, 2.0 * radius, 2.0 * radius);
    cairo_set_source_rgba (cr, CAIRO_RGBA(fgColor.illuminate(0.5 * BStyles::Color::illuminated)));
    cairo_fill_preserve (cr);
    cairo_set_source_rgba (cr, CAIRO_RGBA(fgColor.illuminate(BStyles::Color::darkened)));
    cairo_stroke (cr);

    cairo_restore (cr);  
}

#endif /*  BWIDGETS_DRAWKNOB_HPP_ */