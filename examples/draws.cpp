/* draws.cpp
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


// Define path to alternative draws
#include "../BWidgets/Draws/Oops/definitions.hpp"

#include "../BWidgets/Window.hpp"
#include "../BWidgets/ValueDial.hpp"
#include "../BWidgets/ValueHSlider.hpp"
#include "../BWidgets/ValueVSlider.hpp"
#include "../BWidgets/ValueRadialMeter.hpp"
#include "../BWidgets/ValueHMeter.hpp"
#include "../BWidgets/ValueVMeter.hpp"
#include "../BWidgets/Button.hpp"
#include "../BWidgets/Pad.hpp"

using namespace BWidgets;

int main ()
{
    // Window
    Window window (420, 350, 0, BUTILITIES_URID_UNKNOWN_URID, "Draws", true);

    // Title
    Label label (10, 10, 280, 20, "Using Draws/Oops");
    window.add (&label);

    // Widgets
    ValueDial valueDial (10, 60, 60, 75, 0.3, 0.0, 1.0, 0.0);
    window.add (&valueDial);
    Label valueDialLabel(10, 160, 100, 20, "ValueDial");
    window.add (&valueDialLabel);

    ValueHSlider valueHSlider (100, 70, 100, 40, 0.3, 0.0, 1.0, 0.0);
    window.add (&valueHSlider);
    Label valueHSliderLabel(110, 160, 100, 20, "ValueHSlider");
    window.add (&valueHSliderLabel);

    ValueVSlider valueVSlider (230, 50, 40, 100, 0.3, 0.0, 1.0, 0.0);
    window.add (&valueVSlider);
    Label valueVSliderLabel(210, 160, 100, 20, "ValueVSlider");
    window.add (&valueVSliderLabel);

    Button button (320, 80, 60, 20);
    window.add (&button);
    Label buttonLabel(330, 160, 60, 20, "Button");
    window.add (&buttonLabel);

    ValueRadialMeter valueRadialMeter (10, 210, 60, 75, 0.7, 0.0, 1.0, 0.1);
    window.add (&valueRadialMeter);
    Label valueRadialMeterLabel(0, 310, 110, 20, "ValueRadialMeter");
    window.add (&valueRadialMeterLabel);

    ValueHMeter valueHMeter (100, 240, 100, 30, 0.7, 0.0, 1.0, 0.1);
    window.add (&valueHMeter);
    Label valueHMeterLabel(110, 310, 100, 20, "ValueHMeter");
    window.add (&valueHMeterLabel);

    ValueVMeter valueVMeter (230, 200, 40, 100, 0.7, 0.0, 1.0, 0.1);
    window.add (&valueVMeter);
    Label valueVMeterLabel(210, 310, 100, 20, "ValueVMeter");
    window.add (&valueVMeterLabel);
    
    Pad pad (320, 230, 60, 40, 1.0, 0.0, 1.0, 0.1);
    window.add (&pad);
    Label padLabel(340, 310, 40, 20, "Pad");
    window.add (&padLabel);

    window.run();
}