/* drawArc.hpp
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

#ifndef BWIDGETS_DRAWARC_HPP_
#define BWIDGETS_DRAWARC_HPP_

#include <cairo/cairo.h>
#include "../../../BUtilities/cairoplus.h"
#include <cmath>
#include "../../../BStyles/Types/Color.hpp"

#ifndef BWIDGETS_DEFAULT_DRAWARC_START
#define BWIDGETS_DEFAULT_DRAWARC_START (M_PI * 0.75)
#endif

#ifndef BWIDGETS_DEFAULT_DRAWARC_END
#define BWIDGETS_DEFAULT_DRAWARC_END (M_PI * 2.25)
#endif

#ifndef BWIDGETS_DEFAULT_DRAWARC_SIZE
#define BWIDGETS_DEFAULT_DRAWARC_SIZE (BWIDGETS_DEFAULT_DRAWARC_END - BWIDGETS_DEFAULT_DRAWARC_START)
#endif

/**
 *  @brief  Draws a pseudo 3d arc in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param xc  X center position.
 *  @param y0  Y center position.
 *  @param radius  Arc radius.
 *  @param min  Start of activated (highlighted) part of the arc. Relative
 *  value [0..1].
 *  @param max  End of activated (highlighted) part of the arc. Relative
 *  value [0..1].
 *  @param fgColor  RGBA color for the activated part.
 *  @param bgColor  Bar RGBA color.
 */
inline void drawArc     (cairo_t* cr, const double xc, const double yc, const double radius,
                         const double min, const double max, 
                         const BStyles::Color fgColor, const BStyles::Color bgColor)
{
    cairo_save (cr);
    cairo_set_line_width (cr, 0.0);
    
    // Colors used
    const BStyles::Color fgHi = fgColor.illuminate (BStyles::Color::illuminated);
    //const BStyles::Color fgMid = fgColor.illuminate (0.5 * BStyles::Color::illuminated);
    const BStyles::Color fgLo = fgColor;
    //const BStyles::Color bgLo = bgColor;
    const BStyles::Color bgHi = bgColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color bgSh = bgColor.illuminate (BStyles::Color::shadowed);

    // Arc
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgSh));
    cairo_arc (cr, xc, yc, 0.96 * radius, BWIDGETS_DEFAULT_DRAWARC_START, BWIDGETS_DEFAULT_DRAWARC_END);
    cairo_arc_negative (cr, xc, yc, 0.70 * radius, BWIDGETS_DEFAULT_DRAWARC_END, BWIDGETS_DEFAULT_DRAWARC_START);
    cairo_close_path (cr);
    cairo_fill (cr);

    // Illumination arc top left
    cairo_pattern_t* pat = cairo_pattern_create_linear (xc + radius, yc + radius, xc - radius, yc - radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgSh));
        cairo_arc (cr, xc, yc, 0.96 * radius, BWIDGETS_DEFAULT_DRAWARC_START, M_PI * 1.75);
        cairo_arc_negative (cr, xc + 1.0, yc + 1.0,  0.96 * radius, M_PI * 1.75, BWIDGETS_DEFAULT_DRAWARC_START);
        cairo_close_path (cr);
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }

    // Illumination arc bottom right
    pat = cairo_pattern_create_linear (xc + radius, yc + radius, xc - radius, yc - radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgSh));
        cairo_arc_negative (cr, xc, yc, 0.70 * radius, BWIDGETS_DEFAULT_DRAWARC_END, M_PI * 1.75);
        cairo_arc (cr, xc + 1.0, yc + 1.0,  0.70 * radius, M_PI * 1.75, BWIDGETS_DEFAULT_DRAWARC_END);
        cairo_close_path (cr);
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }

    // Fill
    pat = cairo_pattern_create_linear (xc - radius, yc - radius, xc + radius, yc + radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 0.0, CAIRO_RGBA(fgHi));
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(fgLo));
        cairo_arc (cr, xc, yc,  0.96 * radius - 0.2, BWIDGETS_DEFAULT_DRAWARC_START + min * BWIDGETS_DEFAULT_DRAWARC_SIZE, BWIDGETS_DEFAULT_DRAWARC_START + max * BWIDGETS_DEFAULT_DRAWARC_SIZE);
        cairo_arc_negative (cr, xc, yc,  0.7 * radius - 0.2, BWIDGETS_DEFAULT_DRAWARC_START + max * BWIDGETS_DEFAULT_DRAWARC_SIZE, BWIDGETS_DEFAULT_DRAWARC_START + min * BWIDGETS_DEFAULT_DRAWARC_SIZE);
        cairo_close_path (cr);
        cairo_set_source (cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }


    // Edges of the arc

    pat = cairo_pattern_create_linear (xc + radius, yc + radius, xc - radius, yc - radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgSh));
        cairo_set_line_width (cr, 0.2);

        cairo_arc_negative (cr, xc, yc ,  0.70 * radius, BWIDGETS_DEFAULT_DRAWARC_END, BWIDGETS_DEFAULT_DRAWARC_START);
        cairo_line_to (cr, xc + 0.96 * radius * cos (BWIDGETS_DEFAULT_DRAWARC_START), yc + 0.96 * radius * sin (BWIDGETS_DEFAULT_DRAWARC_START));
        cairo_set_source (cr, pat);
        cairo_stroke (cr);
        cairo_pattern_destroy (pat);
    }

    pat = cairo_pattern_create_linear (xc + radius, yc + radius, xc - radius, yc - radius);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgSh));
        cairo_set_line_width (cr, 0.2);

        cairo_arc (cr, xc, yc,  0.96 * radius, BWIDGETS_DEFAULT_DRAWARC_START, BWIDGETS_DEFAULT_DRAWARC_END);
        cairo_line_to (cr, xc + 0.70 * radius * cos (BWIDGETS_DEFAULT_DRAWARC_END), yc + 0.70 * radius * sin (BWIDGETS_DEFAULT_DRAWARC_END));
        cairo_set_source (cr, pat);
        cairo_stroke (cr);
        cairo_pattern_destroy (pat);
    }

    cairo_restore(cr);
}

#endif /*  BWIDGETS_DRAWARC_HPP_ */