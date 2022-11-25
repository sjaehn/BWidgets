/* draws.cpp
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


// Define path to alternative draws
#define BWIDGETS_DEFAULT_DRAWARC_PATH "../examples/OopsDraws/drawArc.hpp"
#define BWIDGETS_DEFAULT_DRAWARCHANDLE_PATH "../examples/OopsDraws/drawArcHandle.hpp"
#define BWIDGETS_DEFAULT_DRAWHBAR_PATH "../examples/OopsDraws/drawHBar.hpp"
#define BWIDGETS_DEFAULT_DRAWVBAR_PATH "../examples/OopsDraws/drawVBar.hpp"
#define BWIDGETS_DEFAULT_DRAWKNOB_PATH "../examples/OopsDraws/drawKnob.hpp"

#include "../BWidgets/Window.hpp"
#include "../BWidgets/ValueDial.hpp"
#include "../BWidgets/ValueHSlider.hpp"
#include "../BWidgets/ValueVSlider.hpp"

using namespace BWidgets;

int main ()
{
    // Window
    Window window (300, 120, 0, BUTILITIES_URID_UNKNOWN_URID, "Draws", true);

    // Label
    Label label (10, 10, 280, 20, "Using B.Oops-like Draws");
    window.add (&label);

    // Dial and sliders
    ValueDial valueDial (10, 30, 60, 75, 0.3, 0.0, 1.0, 0.0);
    window.add (&valueDial);
    ValueHSlider valueHSlider (110, 40, 100, 60, 0.3, 0.0, 1.0, 0.0);
    window.add (&valueHSlider);
    ValueVSlider valueVSlider (220, 30, 60, 80, 0.3, 0.0, 1.0, 0.0);
    window.add (&valueVSlider);

    window.run();
}