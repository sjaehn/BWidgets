/* drawVBar.hpp
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

#ifndef BWIDGETS_DRAWVBAR_HPP_
#define BWIDGETS_DRAWVBAR_HPP_

#include <cairo/cairo.h>
#include "../../BUtilities/cairoplus.h"
#include <cmath>
#include "../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws a vertical pseudo 3d bar in a Cairo context. 
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
inline void drawVBar    (cairo_t* cr, const double x0, const double y0, const double width, const double height, 
                         const double min, const double max, 
                         const BStyles::Color fgColor, const BStyles::Color bgColor)
{
    const double y2 = y0 + min * height;
    const double y3 = y0 + max * height;
    const double x4 = x0 + width;
    //const double y4 = y0 + height;

    // Colors used
    BStyles::Color fgHi = fgColor.illuminate (BStyles::Color::illuminated);
    BStyles::Color fgLo = fgColor;
    BStyles::Color bgLo = bgColor;
    BStyles::Color bgHi = bgColor.illuminate (BStyles::Color::illuminated);
    BStyles::Color bgSh = bgColor.illuminate (BStyles::Color::shadowed);

    // Background
    cairo_set_line_width (cr, 0.0);
    cairo_pattern_t* pat = cairo_pattern_create_linear (x0, y0, x4, y0);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgLo));
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairo_rectangle_rounded (cr, x0, y0, width, height, 0.5 * width, 0b1111);
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }
    cairo_rectangle_rounded (cr, x0, y0, width, height, 0.5 * width, 0b1111);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgSh));
    cairo_fill (cr);

    // Foreground
    pat = cairo_pattern_create_linear (x0, y0, x4, y0);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(fgLo));
        cairo_pattern_add_color_stop_rgba (pat, 0.25, CAIRO_RGBA(fgHi));
        cairo_pattern_add_color_stop_rgba (pat, 1.0, CAIRO_RGBA(fgLo));
        cairo_save (cr);
        cairo_rectangle_rounded (cr, x0 + 1, y0 + 1, width - 1, height - 1, 0.5 * width, 0b1111);
        cairo_clip (cr);
        cairo_rectangle (cr, x0, y2, width, y3 - y2);
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_restore (cr);
        cairo_pattern_destroy (pat);
    }

    //Frame
    pat = cairo_pattern_create_linear (x0, y0, x4, y0);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgLo));
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairo_rectangle_rounded (cr, x0, y0, width, height, 0.5 * width, 0b1111);
        cairo_set_source (cr, pat);
        cairo_set_line_width (cr, 0.2);
        cairo_stroke (cr);
        cairo_pattern_destroy (pat);
    }
}

#endif /*  BWIDGETS_DRAWVBAR_HPP_ */