/* drawButton.hpp
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

#ifndef BWIDGETS_DRAWBUTTON_HPP_
#define BWIDGETS_DRAWBUTTON_HPP_

#include <cairo/cairo.h>
#include "../../../BStyles/Types/Color.hpp"
#include "../../../BUtilities/cairoplus.h"

/**
 *  @brief  Draws a  button in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param x0  X position.
 *  @param y0  Y position.
 *  @param width  Bar width.
 *  @param height  Bar height.
 *  @param clicked  True, if button clicked. Otherwise false.
 *  @param fgColor  RGBA color for the activated elements.
 *  @param bgColor  Bar RGBA color.
 */
inline void drawButton  (cairo_t* cr, const double x0, const double y0, const double width, const double height,
                         const bool clicked,  
                         const BStyles::Color fgColor, const BStyles::Color bgColor)
{
    const BStyles::Color frameColor = bgColor.illuminate (clicked ? BStyles::Color::highLighted : BStyles::Color::darkened);

    cairo_save (cr);

    cairoplus_rectangle_rounded(cr, x0 + 0.5, y0 + 0.5, width - 1.0, height - 1.0, 0.15 * std::min (width, height), 0b1111);
    cairo_set_source_rgba(cr, CAIRO_RGBA(bgColor));
    cairo_fill_preserve(cr);
    cairo_set_line_width(cr, 1.0);
    cairo_set_source_rgba(cr, CAIRO_RGBA(frameColor));
    cairo_stroke (cr);

    cairo_restore (cr);
}

#endif /*  BWIDGETS_DRAWBUTTON_HPP_ */