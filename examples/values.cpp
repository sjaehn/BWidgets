/* values.cpp
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

#include "../BWidgets/Window.hpp"
#include "../BWidgets/ValueDial.hpp"
#include <cmath>
#include <math.h>

using namespace BWidgets;
using namespace BStyles;

Font labelFont ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, Font::TextAlign::center, Font::TextVAlign::middle);

int main ()
{
    // Window
    Window window (240, 420, 0, BUTILITIES_URID_UNKNOWN_URID, "Values and transfer functions", false);

    // No transfer: x' = x
    Label title1 (10, 10, 180, 20, "No transfer: x' = x");
    window.add (&title1);
    ValueDial valueDial11 (20, 30, 60, 75, 0.3, 0.0, 1.0, 0.01);
    window.add (&valueDial11);
    Label label11 (0, 110, 100, 20, "Step = 0.01");
    label11.setFont (labelFont);
    window.add (&label11);
    ValueDial valueDial12 (120, 30, 60, 75, 0.3, 0.0, 1.0, -0.01);
    window.add (&valueDial12);
    Label label12 (100, 110, 100, 20, "Step = -0.01");
    label12.setFont (labelFont);
    window.add (&label12);

    // Negative transfer: x' = -x
    Label title2 (10, 150, 180, 20, "Negative transfer: x' = -x");
    window.add (&title2);
    ValueDial valueDial21 (20, 170, 60, 75, -0.3, -1.0, 0.0, 0.01, [] (const double& x) {return -x;}, [] (const double& x) {return -x;});
    window.add (&valueDial21);
    Label label21 (0, 250, 100, 20, "Step = 0.01");
    label21.setFont (labelFont);
    window.add (&label21);
    ValueDial valueDial22 (120, 170, 60, 75, -0.3, -1.0, 0.0, -0.01, [] (const double& x) {return -x;}, [] (const double& x) {return -x;});
    window.add (&valueDial22);
    Label label22 (100, 250, 100, 20, "Step = -0.01");
    label22.setFont (labelFont);
    window.add (&label22);

    // Logarithmic transfer: x' = log10 x
    Label title3 (10, 290, 220, 20, "Logarithmic transfer: x' = log10 x");
    window.add (&title3);
    ValueDial valueDial31 (20, 310, 60, 75, 100.0, 10.0, 10000.0, 10.0, [] (const double& x) {return std::log10 (x);}, [] (const double& x) {return std::pow (10.0, x);});
    window.add (&valueDial31);
    Label label31 (0, 390, 100, 20, "Step = 10.0");
    label31.setFont (labelFont);
    window.add (&label31);
    ValueDial valueDial32 (120, 310, 60, 75, 100.0, 10.0, 10000.0, -10.0, [] (const double& x) {return std::log10 (x);}, [] (const double& x) {return std::pow (10.0, x);});
    window.add (&valueDial32);
    Label label32 (100, 390, 100, 20, "Step = -10.0");
    label32.setFont (labelFont);
    window.add (&label32);

    window.run();
}