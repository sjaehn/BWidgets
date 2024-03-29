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


#include "../BWidgets/Window.hpp"
#include "../BWidgets/ValueDial.hpp"
#include "../BWidgets/ValueHSlider.hpp"
#include "../BWidgets/ValueVSlider.hpp"
#include "../BWidgets/ValueRadialMeter.hpp"
#include "../BWidgets/ValueHMeter.hpp"
#include "../BWidgets/ValueVMeter.hpp"

using namespace BWidgets;

int main ()
{
    // Window
    Window window (620, 960, 0, BUTILITIES_URID_UNKNOWN_URID, "ValuePositions", true);

    // Create dials, sliders, and meters for the six value positions (default and ValueVisualizable::ValuePosition)
    const std::array<const std::string, 5> positionStr= {{"top", "right", "bottom", "left", "center"}};
    std::vector<ValueDial*> dials;
    std::vector<ValueHSlider*> hSliders;
    std::vector<ValueVSlider*> vSliders;
    std::vector<ValueRadialMeter*> rMeters;
    std::vector<ValueHMeter*> hMeters;
    std::vector<ValueVMeter*> vMeters;
    std::vector<Widget*> widgets;

    for (int i = 0; i <= 5; ++i)
    {
        double extraHeight = 0.0;
        if ((i == 0 ) || (i - 1 == int (ValueVisualizable::ValuePosition::top)) || (i - 1 == int (ValueVisualizable::ValuePosition::bottom))) extraHeight = 20.0;
        double extraWidth = 0.0;
        if ((i - 1 == int (ValueVisualizable::ValuePosition::left)) || (i - 1 == int (ValueVisualizable::ValuePosition::right))) extraWidth = 18.0;

        // Title
        Label* label;
        if (i) label = new Label (10, 10 + i * 160, 280, 20, "ValueVisualizable::ValuePosition::" + positionStr[i - 1]);
        else label = new Label (10, 10, 280, 20, "default");
        widgets.push_back(label);

        // Widgets
        ValueDial* valueDial = new ValueDial (10, 40 + i * 160, 80, 80, 0.3, 0.0, 1.0, 0.0);
        if (i) valueDial->setValuePosition(ValueVisualizable::ValuePosition(i - 1));
        dials.push_back (valueDial);
        Label* valueDialLabel = new Label (20, 130 + i * 160, 100, 20, "ValueDial");
        widgets.push_back (valueDialLabel);

        ValueHSlider* valueHSlider = new ValueHSlider (110 - 0.5 * extraWidth, 65 + i * 160 - 0.5 * extraHeight, 80 + extraWidth, 20 + extraHeight, 0.3, 0.0, 1.0, 0.0);
        if (i) valueHSlider->setValuePosition(ValueVisualizable::ValuePosition(i - 1));
        hSliders.push_back (valueHSlider);
        Label* valueHSliderLabel = new Label(110, 130 + i * 160, 100, 20, "ValueHSlider");
        widgets.push_back (valueHSliderLabel);

        ValueVSlider* valueVSlider = new ValueVSlider (220 - 0.5 * extraWidth, 40 + i * 160, 40 + extraWidth, 80, 0.3, 0.0, 1.0, 0.0);
        if (i) valueVSlider->setValuePosition(ValueVisualizable::ValuePosition(i - 1));
        vSliders.push_back (valueVSlider);
        Label* valueVSliderLabel = new Label(210, 130 + i * 160, 100, 20, "ValueVSlider");
        widgets.push_back (valueVSliderLabel);

        ValueRadialMeter* valueRadialMeter = new ValueRadialMeter (310, 40 + i * 160, 80, 80, 0.7, 0.0, 1.0, 0.1);
        if (i) valueRadialMeter->setValuePosition(ValueVisualizable::ValuePosition(i - 1));
        valueRadialMeter->setHiColors (BStyles::reds);
        rMeters.push_back (valueRadialMeter);
        Label* valueRadialMeterLabel = new Label(295, 130 + i * 160, 120, 20, "ValueRadialMeter");
        widgets.push_back (valueRadialMeterLabel);

        ValueHMeter* valueHMeter = new ValueHMeter (410 - 0.5 * extraWidth, 60 + i * 160 - 0.5 * extraHeight, 80 + extraWidth, 20 + extraHeight, 0.7, 0.0, 1.0, 0.1);
        if (i) valueHMeter->setValuePosition(ValueVisualizable::ValuePosition(i - 1));
        valueHMeter->setHiColors (BStyles::reds);
        hMeters.push_back (valueHMeter);
        Label* valueHMeterLabel = new Label(415, 130 + i * 160, 100, 20, "ValueHMeter");
        widgets.push_back (valueHMeterLabel);

        ValueVMeter* valueVMeter = new ValueVMeter (530 - 0.5 * extraWidth, 40 + i * 160, 40 + extraWidth, 80, 0.7, 0.0, 1.0, 0.1);
        if (i) valueVMeter->setValuePosition(ValueVisualizable::ValuePosition(i - 1));
        valueVMeter->setHiColors (BStyles::reds);
        vMeters.push_back (valueVMeter);
        Label* valueVMeterLabel = new Label(515, 130 + i * 160, 100, 20, "ValueVMeter");
        widgets.push_back (valueVMeterLabel);
    }

    // Add all dials, sliders, and meters to widgets
    for (ValueDial* d : dials) widgets.push_back(d);
    for (ValueHSlider* h : hSliders) widgets.push_back(h);
    for (ValueVSlider* v : vSliders) widgets.push_back(v);
    for (ValueRadialMeter* r : rMeters) widgets.push_back(r);
    for (ValueHMeter* h : hMeters) widgets.push_back(h);
    for (ValueVMeter* v : vMeters) widgets.push_back(v);

    // ... and into the main window
    for (Widget* w : widgets) window.add (w);
    
    // Main loop
    const std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
    while (!window.isQuit())
    {
        const std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        const std::chrono::duration<double> dt = t - t0;
        for (ValueRadialMeter* r : rMeters) r->setValue (0.5 + 0.5 * cos (0.5 * dt.count()));
        for (ValueHMeter* h : hMeters) h->setValue (0.5 + 0.5 * sin (1.4 * dt.count()));
        for (ValueVMeter* v : vMeters) v->setValue (0.5 + 0.5 * cos (0.7 * dt.count()));
        window.handleEvents();
    }

    // Cleanup
    while (!widgets.empty())
    {
        delete widgets.back();
        widgets.pop_back();
    }
}