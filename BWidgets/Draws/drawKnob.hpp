/* drawKnob.hpp
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

#ifndef BWIDGETS_DRAWKNOB_HPP_
#define BWIDGETS_DRAWKNOB_HPP_

#include <cairo/cairo.h>
#include <cmath>
#include "../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws a pseudo 3D knob in a Cairo context. 
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
    

    const BStyles::Color fgLo = fgColor;
    const BStyles::Color fgHi = fgColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color bgLo = bgColor;
    const BStyles::Color bgHi = bgColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color bgSg = bgColor.illuminate (BStyles::Color::shadowed);

    cairo_set_line_width (cr, 0.0);

    // Knob top
    cairo_pattern_t* pat = cairo_pattern_create_radial (xc - 0.5 * radius - height, yc - 0.5 * radius - height, 0.1 * radius, xc + height, yc + height, 1.5 * radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_arc (cr, xc - height, yc - height, radius, 0, 2 * M_PI);
        cairo_close_path (cr);
        cairo_pattern_add_color_stop_rgba (pat, 0.0, CAIRO_RGBA (fgHi));
        cairo_pattern_add_color_stop_rgba (pat, 1.0, CAIRO_RGBA (fgLo));
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }

    // Knob side
    pat = cairo_pattern_create_linear (xc - radius - height, yc - radius, xc + radius, yc - radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 1.00, CAIRO_RGBA (bgLo));
        cairo_pattern_add_color_stop_rgba (pat, 0.825, CAIRO_RGBA (bgSg));
        cairo_pattern_add_color_stop_rgba (pat, 0.0, CAIRO_RGBA (bgLo));
        cairo_arc (cr,  xc - height, yc - height, radius, -0.25 * M_PI, 0.75 * M_PI);
        cairo_arc_negative (cr, xc, yc, radius, 0.75 * M_PI, -0.25 * M_PI);
        cairo_close_path (cr);
        cairo_set_line_width (cr, 0.5);
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }

    // Knob edge
    pat = cairo_pattern_create_linear
    (
        xc + radius * cos (0.25 * M_PI) - height,
        yc + radius * sin (0.25 * M_PI) - height,
        xc - radius * cos (0.25 * M_PI) - height,
        yc - radius * sin (0.25 * M_PI) - height
    );

    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 1.0, CAIRO_RGBA (bgHi));
        cairo_pattern_add_color_stop_rgba (pat, 0.0, CAIRO_RGBA (bgSg));
        cairo_arc (cr,  xc - height, yc - height, radius, 0, 2 * M_PI);
        cairo_set_line_width (cr, 0.2 * height);
        cairo_set_source (cr, pat);
        cairo_stroke (cr);
        cairo_pattern_destroy (pat);
    }
}

#endif /*  BWIDGETS_DRAWKNOB_HPP_ */