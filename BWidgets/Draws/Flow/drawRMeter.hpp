/* drawRMeter.hpp
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

#ifndef BWIDGETS_DRAWRMETER_HPP_
#define BWIDGETS_DRAWRMETER_HPP_

#include <cairo/cairo.h>
#include "../../../BUtilities/cairoplus.h"
#include <cmath>
#include <functional>
#include "../../../BStyles/Types/Color.hpp"

#ifndef BWIDGETS_DEFAULT_DRAWRMETER_START
#define BWIDGETS_DEFAULT_DRAWRMETER_START (M_PI * 0.75)
#endif

#ifndef BWIDGETS_DEFAULT_DRAWRMETER_END
#define BWIDGETS_DEFAULT_DRAWRMETER_END (M_PI * 2.25)
#endif

#ifndef BWIDGETS_DEFAULT_DRAWRMETER_SIZE
#define BWIDGETS_DEFAULT_DRAWRMETER_SIZE (BWIDGETS_DEFAULT_DRAWRMETER_END - BWIDGETS_DEFAULT_DRAWRMETER_START)
#endif

/**
 *  @brief  Draws a segmented two colors pseudo 3d arc in a Cairo context. 
 *  @param cr  Cairo context.
 *  @param xc  X center position.
 *  @param y0  Y center position.
 *  @param radius  Arc radius.
 *  @param min  Start of activated (highlighted) part of the arc. Relative
 *  value [0..1].
 *  @param max  End of activated (highlighted) part of the arc. Relative
 *  value [0..1].
 *  @param step  Size of each segment.
 *  @param loColor  RGBA color for the low values of the activated part.
 *  @param hiColor  RGBA color for the high values of the activated part.
 *  @param gradient  Color gradient function.
 *  @param bgColor  Bar RGBA color.
 */
inline void drawRMeter    (cairo_t* cr, const double xc, const double yc, const double radius,
                             const double min, const double max, const double step,
                             const BStyles::Color loColor, const BStyles::Color hiColor, std::function<double(const double &)> gradient, 
                             const BStyles::Color bgColor)
{
    // Colors used
    const int nrSteps = (step > 0 ? std::ceil (1.0 / step) : 10);
    const double da = (1.5 * M_PI) * step;
    const double sa = 1.0 / radius;
    const BStyles::Color fgHi = loColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color fgLo = loColor;
    const BStyles::Color hiHi = hiColor.illuminate (BStyles::Color::illuminated);
    const BStyles::Color hiLo = hiColor;
    const BStyles::Color bgLo = bgColor.illuminate (BStyles::Color::shadowed);
    const BStyles::Color bgHi = bgColor;
    //const BStyles::Color bgDk = bgColor.illuminate (-0.75);

    cairo_save (cr);

    // Fill
    cairo_set_line_width (cr, 0.0);
    cairo_pattern_t* fgPat = cairo_pattern_create_linear (xc - radius, yc - radius, xc + radius, yc + radius);
    cairo_pattern_t* bgPat = cairo_pattern_create_linear (xc - radius, yc - radius, xc + radius, yc + radius);
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
                    fgPat = cairo_pattern_create_linear (xc - radius, yc - radius, xc + radius, yc + radius);
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

            const double a = BWIDGETS_DEFAULT_DRAWRMETER_START + v * BWIDGETS_DEFAULT_DRAWRMETER_SIZE;

            cairo_arc (cr, xc, yc, 0.91 * radius, a, a + da + 0.5 * sa);
            cairo_arc_negative (cr, xc, yc, 0.5 * radius, a + da + 0.5 * sa, a);
            cairo_fill (cr);
        }

        cairo_pattern_destroy (bgPat);
        cairo_pattern_destroy (fgPat);
    }

    // Scale
    cairo_set_line_width (cr, 1.0);
    cairo_set_source_rgba (cr, CAIRO_RGBA(bgColor));
    for (int i = 0; i < nrSteps; ++i)
    {
        const double v = static_cast<double>(i) / static_cast<double>(nrSteps);
        const double a = BWIDGETS_DEFAULT_DRAWRMETER_START + v * BWIDGETS_DEFAULT_DRAWRMETER_SIZE;
        cairo_move_to (cr, xc + 0.91 * cos(a) * radius, yc + 0.91 * sin(a) * radius);
        cairo_line_to (cr, xc + 0.5 * cos(a) * radius, yc + 0.5 * sin(a) * radius);
        cairo_stroke(cr);
    }

    cairo_restore (cr);
}

#endif /*  BWIDGETS_DRAWRMETER_HPP_ */