/* drawVMeter.hpp
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

#ifndef BWIDGETS_DRAWVMETER_HPP_
#define BWIDGETS_DRAWVMETER_HPP_

#include "../../../BUtilities/cairoplus.h"
#include <cmath>
#include <functional>
#include "../../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws a segmented two colors vertical meter bar in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param x0  X position.
 *  @param y0  Y position.
 *  @param width  Bar width.
 *  @param height  Bar height.
 *  @param min  Start of activated (highlighted) part of the meter. Relative
 *  value [0..1].
 *  @param max  End of activated (highlighted) part of the meter. Relative
 *  value [0..1].
 *  @param step  Size of each segment.
 *  @param loColor  RGBA color for the low values of the activated part.
 *  @param hiColor  RGBA color for the high values of the activated part.
 *  @param gradient  Color gradient function.
 *  @param bgColor  Bar RGBA color.
 */
inline void drawVMeter    (cairo_t* cr, const double x0, const double y0, const double width, const double height, 
                             const double min, const double max, const double step,
                             const BStyles::Color loColor, const BStyles::Color hiColor, std::function<double(const double &)> gradient, 
                             const BStyles::Color bgColor)
{
    const int nrSteps = (step > 0 ? std::ceil (1.0 / step) : 10);
    cairo_save (cr);

    // Background
    cairo_set_line_width (cr, 0.0);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor.illuminate(BStyles::Color::shadowed)));
    cairo_rectangle (cr, x0, y0, width, height);
    cairo_fill (cr);


    // Fill
    cairo_set_line_width (cr, 0.0);
    cairo_pattern_t* fgPat = cairo_pattern_create_linear (x0, y0 + height, x0, y0);
    if (fgPat && (cairo_pattern_status (fgPat) == CAIRO_STATUS_SUCCESS))
    {
        for (int i = 0; i <= nrSteps; ++i)
        {
            const double v = static_cast<double>(i) / static_cast<double>(nrSteps);
            BStyles::Color col;
            col.setHSV
            (
                loColor.hue() * (1.0 - gradient (v)) + hiColor.hue() * gradient (v),
                loColor.saturation() * (1.0 - gradient (v)) + hiColor.saturation() * gradient (v),
                loColor.value() * (1.0 - gradient (v)) + hiColor.value() * gradient (v),
                loColor.alpha * (1.0 - gradient (v)) + hiColor.alpha * gradient (v)
            );
            cairo_pattern_add_color_stop_rgba (fgPat, v, CAIRO_RGBA(col));
        }

        cairo_set_source (cr, fgPat);
        cairo_rectangle (cr, x0, y0 + (1.0 - min) * height, width, (min - max) * height);
        cairo_fill (cr);
        cairo_pattern_destroy (fgPat);
    }

    // Scale
    cairo_set_line_width (cr, 1.0);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor));
    
    for (int i = 0; i <= nrSteps; ++i)
    {
        const double v = static_cast<double>(i) / static_cast<double>(nrSteps);
        cairo_move_to (cr, x0, y0 + (1.0 - v) * height);
        cairo_line_to (cr, x0 + width, y0 + (1.0 - v) * height);
    }

    cairo_stroke (cr);

    // Frame
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor.illuminate(BStyles::Color::shadowed)));
    cairo_move_to (cr, x0, y0 + height);
    cairo_line_to (cr, x0, y0);
    cairo_line_to (cr, x0 + width, y0);
    cairo_stroke (cr);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor.illuminate(BStyles::Color::illuminated)));
    cairo_move_to (cr, x0, y0 + height);
    cairo_line_to (cr, x0 + width, y0 + height);
    cairo_line_to (cr, x0 + width, y0);
    cairo_stroke (cr);

    cairo_restore (cr);
}

#endif /*  BWIDGETS_DRAWVMETER_HPP_ */