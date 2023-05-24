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
#include <cmath>
#include "../../../BStyles/Types/Color.hpp"

#ifndef BWIDGETS_DEFAULT_DRAWARC_START
#define BWIDGETS_DEFAULT_DRAWARC_START (M_PI * 0.55)
#endif

#ifndef BWIDGETS_DEFAULT_DRAWARC_END
#define BWIDGETS_DEFAULT_DRAWARC_END (M_PI * 2.45)
#endif

#ifndef BWIDGETS_DEFAULT_DRAWARC_SIZE
#define BWIDGETS_DEFAULT_DRAWARC_SIZE (BWIDGETS_DEFAULT_DRAWARC_END - BWIDGETS_DEFAULT_DRAWARC_START)
#endif

/**
 *  @brief  Draws an arc in a Cairo context. 
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
    cairo_save(cr);

    cairo_set_line_width (cr, 0.0);
    
    // Arc
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor));
    cairo_arc (cr, xc, yc, 0.96 * radius, BWIDGETS_DEFAULT_DRAWARC_START, BWIDGETS_DEFAULT_DRAWARC_END);
    cairo_arc_negative (cr, xc, yc, 0.70 * radius, BWIDGETS_DEFAULT_DRAWARC_END, BWIDGETS_DEFAULT_DRAWARC_START);
    cairo_close_path (cr);
    cairo_fill (cr);

    // Center
    cairo_set_source_rgba (cr, CAIRO_RGBA(fgColor));
    cairo_arc (cr, xc, yc, 0.1 * radius, 0, 2 * M_PI);
    cairo_close_path (cr);
    cairo_fill (cr);

    // Fill
    cairo_arc (cr, xc, yc,  0.96 * radius - 0.2, BWIDGETS_DEFAULT_DRAWARC_START + min * BWIDGETS_DEFAULT_DRAWARC_SIZE, BWIDGETS_DEFAULT_DRAWARC_START + max * BWIDGETS_DEFAULT_DRAWARC_SIZE);
    cairo_arc_negative (cr, xc, yc,  0.7 * radius - 0.2, BWIDGETS_DEFAULT_DRAWARC_START + max * BWIDGETS_DEFAULT_DRAWARC_SIZE, BWIDGETS_DEFAULT_DRAWARC_START + min * BWIDGETS_DEFAULT_DRAWARC_SIZE);
    cairo_close_path (cr);
    cairo_fill (cr);

    cairo_restore(cr);
}

#endif /*  BWIDGETS_DRAWARC_HPP_ */