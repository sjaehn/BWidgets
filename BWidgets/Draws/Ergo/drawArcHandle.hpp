/* drawArcHandle.hpp
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

#ifndef BWIDGETS_DRAWARCHANDLE_HPP_
#define BWIDGETS_DRAWARCHANDLE_HPP_

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
 *  @brief  Draws a knob spot as a handle for pseudo 3d arc in a Cairo 
 *  context. 
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
inline void drawArcHandle   (cairo_t* cr, const double xc, const double yc, const double radius,
                             const double rval, 
                             const BStyles::Color fgColor, const BStyles::Color bgColor)
{
    cairo_set_source_rgba(cr, CAIRO_RGBA(fgColor));
    cairo_set_line_width(cr, 0.0);
    cairo_arc
    (
        cr, 
        xc + 0.4 * radius * cos (BWIDGETS_DEFAULT_DRAWARC_START + rval * BWIDGETS_DEFAULT_DRAWARC_SIZE), 
        yc + 0.4 * radius * sin (BWIDGETS_DEFAULT_DRAWARC_START + rval * BWIDGETS_DEFAULT_DRAWARC_SIZE), 
        0.075 * radius, 
        0.0,
        2.0 * M_PI
    );
    cairo_fill (cr);
}

#endif /*  BWIDGETS_DRAWARCHANDLE_HPP_ */