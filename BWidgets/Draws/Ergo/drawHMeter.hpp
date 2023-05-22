/* drawHMeter.hpp
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

#ifndef BWIDGETS_DRAWHMETER_HPP_
#define BWIDGETS_DRAWHMETER_HPP_

#include "../../../BUtilities/cairoplus.h"
#include <cmath>
#include <functional>
#include "../../../BStyles/Types/Color.hpp"

/**
 *  @brief  Draws a segmented two colors horizontal pseudo 3d meter bar in a
 *  Cairo context. 
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
inline void drawHMeter    (cairo_t* cr, const double x0, const double y0, const double width, const double height, 
                             const double min, const double max, const double step,
                             const BStyles::Color loColor, const BStyles::Color hiColor, std::function<double(const double &)> gradient, 
                             const BStyles::Color bgColor)
{
    const int nrSteps = (step > 0 ? std::ceil (1.0 / step) : 10);
    const double dx = (width - 0.2 * height) * step;
    const BStyles::Color fgHi = loColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color fgLo = loColor;
    const BStyles::Color hiHi = hiColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color hiLo = hiColor;
    const BStyles::Color bgLo = bgColor.illuminate (BStyles::Color::shadowed);
    const BStyles::Color bgHi = bgColor;
    const BStyles::Color bgDk = bgColor.illuminate (-0.75);

    // Background fill
    cairo_set_line_width (cr, 0.0);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgDk));
    cairoplus_rectangle_rounded (cr, x0, y0, width, height, 0.2 * height, 0b1111);
    cairo_fill (cr);

    // Border
    cairo_pattern_t* pat = cairo_pattern_create_linear (x0, y0, x0 + width, y0 + height);
    if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgLo));
        cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
        cairoplus_rectangle_rounded (cr, x0, y0, width, height, 0.2 * height, 0b1111);
        cairo_set_source (cr, pat);
        cairo_set_line_width (cr, 1.0);
        cairo_stroke (cr);
        cairo_pattern_destroy (pat);
    }

    // Fill
    cairo_set_line_width (cr, 0.0);
    cairo_pattern_t* fgPat = cairo_pattern_create_linear (x0, y0, x0 + width, y0 + height);
    cairo_pattern_t* bgPat = cairo_pattern_create_linear (x0, y0, x0 + width, y0 + height);
    if (fgPat && bgPat && (cairo_pattern_status (fgPat) == CAIRO_STATUS_SUCCESS) && (cairo_pattern_status (bgPat) == CAIRO_STATUS_SUCCESS))
    {
        cairo_pattern_add_color_stop_rgba (fgPat, 0, CAIRO_RGBA(fgLo));
        cairo_pattern_add_color_stop_rgba (fgPat, 0.25, CAIRO_RGBA(fgHi));
        cairo_pattern_add_color_stop_rgba (fgPat, 1, CAIRO_RGBA(fgLo));
        cairo_pattern_add_color_stop_rgba (bgPat, 0, CAIRO_RGBA(bgLo));
        cairo_pattern_add_color_stop_rgba (bgPat, 0.25, CAIRO_RGBA(bgHi));
        cairo_pattern_add_color_stop_rgba (bgPat, 1, CAIRO_RGBA(bgLo));

        for (int i = 0; i < nrSteps; ++i)
        {
            const double v = static_cast<double>(i) / static_cast<double>(nrSteps);
            if ((v >= min) && (v < max)) 
            {
                if ((fgHi != hiHi) || (fgLo != hiLo))
                {
                    fgPat = cairo_pattern_create_linear (x0, y0, x0 + width, y0 + height);
                    BStyles::Color cLo; 
                    cLo.setHSV
                    (
                        fgLo.hue() * (1.0 - gradient (v)) + hiLo.hue() * gradient (v),
                        fgLo.saturation() * (1.0 - gradient (v)) + hiLo.saturation() * gradient (v),
                        fgLo.value() * (1.0 - gradient (v)) + hiLo.value() * gradient (v),
                        fgLo.alpha * (1.0 - gradient (v)) + hiLo.alpha * gradient (v)
                    );
                    BStyles::Color cHi;
                    cHi.setHSV
                    (
                        fgHi.hue() * (1.0 - gradient (v)) + hiHi.hue() * gradient (v),
                        fgHi.saturation() * (1.0 - gradient (v)) + hiHi.saturation() * gradient (v),
                        fgHi.value() * (1.0 - gradient (v)) + hiHi.value() * gradient (v),
                        fgHi.alpha * (1.0 - gradient (v)) + hiHi.alpha * gradient (v)
                    );

                    cairo_pattern_add_color_stop_rgba (fgPat, 0, CAIRO_RGBA(cLo));
                    cairo_pattern_add_color_stop_rgba (fgPat, 0.25, CAIRO_RGBA(cHi));
                    cairo_pattern_add_color_stop_rgba (fgPat, 1, CAIRO_RGBA(cLo));
                }
                cairo_set_source (cr, fgPat);
            }

            else cairo_set_source (cr, bgPat);

            const double x = v * (width - 0.2 * height);

            if (dx < 3.0) cairo_rectangle (cr, x0 + 0.1 * height + x, y0 + 0.1 * height, dx, height - 0.2 * height);
            else cairo_rectangle (cr, x0 + 0.1 * height + x + 1.0, y0 + 0.1 * height, dx - 2.0, height - 0.2 * height);
            cairo_fill (cr);
        }

        cairo_pattern_destroy (bgPat);
        cairo_pattern_destroy (fgPat);
    }
}

#endif /*  BWIDGETS_DRAWHMETER_HPP_ */