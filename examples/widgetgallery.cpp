/* WidgetGalery.cpp
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

#include "../BWidgets/Window.hpp"
#include "../BWidgets/Label.hpp"
#include "../BWidgets/Frame.hpp"
#include "../BWidgets/LabelEdit.hpp"
#include "../BWidgets/Text.hpp"
#include "../BWidgets/Symbol.hpp"
#include "../BWidgets/Image.hpp"
#include "../BWidgets/Button.hpp"
#include "../BWidgets/TextButton.hpp"
#include "../BWidgets/SymbolButton.hpp"
#include "../BWidgets/ImageButton.hpp"
#include "../BWidgets/CheckBox.hpp"
#include "../BWidgets/RadioButton.hpp"
#include "../BWidgets/Knob.hpp"
#include "../BWidgets/HSwitch.hpp"
#include "../BWidgets/VSwitch.hpp"
#include "../BWidgets/HScale.hpp"
#include "../BWidgets/VScale.hpp"
#include "../BWidgets/HSlider.hpp"
#include "../BWidgets/VSlider.hpp"
#include "../BWidgets/Dial.hpp"
#include "../BWidgets/ValueDial.hpp"
#include "../BWidgets/ValueHSlider.hpp"
#include "../BWidgets/ValueVSlider.hpp"
#include "../BWidgets/HPianoRoll.hpp"
#include "../BWidgets/RadialMeter.hpp"
#include "../BWidgets/HMeter.hpp"
#include "../BWidgets/VMeter.hpp"
#include "../BWidgets/ValueRadialMeter.hpp"
#include "../BWidgets/ValueHMeter.hpp"
#include "../BWidgets/ValueVMeter.hpp"
#include "../BWidgets/Box.hpp"
#include "../BWidgets/TextBox.hpp"
#include "../BWidgets/MessageBox.hpp"
#include "../BWidgets/SpinButton.hpp"
#include "../BWidgets/SpinBox.hpp"
#include "../BWidgets/ListBox.hpp"
#include <cairo/cairo.h>
#include <iostream>
#include <vector>

using namespace BWidgets;
using namespace BStyles;

Font labelFont ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE);

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

int main ()
{
    Window window (1200, 820, 0, URID_UNKNOWN_URID, "Window");

    // Widget
    Widget widget (10, 10, 80, 60);
    widget.setBorder (lightgreyBorder1pt);
    Label widgetLabel (10, 80, 80, 20, "Widget");
    widgetLabel.setFont (labelFont);
    window.add (&widget);
    window.add (&widgetLabel);

    // Frame
    Frame frame (110, 10, 80, 60);
    frame.setBackground(darkgreyFill);
    frame.setBorder (lightgreyBorder1pt);
    Label frameDragLabel ("Drag me");
    frameDragLabel.setEventPassable(BEvents::Event::BUTTON_PRESS_EVENT, true);
    frameDragLabel.setEventPassable(BEvents::Event::POINTER_DRAG_EVENT, true);
    frame.add (&frameDragLabel);
    frameDragLabel.moveTo(frameDragLabel.center(), frameDragLabel.middle());
    Label frameLabel (110, 80, 80, 20, "Frame");
    frameLabel.setFont (labelFont);
    window.add (&frame);
    window.add (&frameLabel);

    // Label
    Label label (210, 10, 80, 60, "Text");
    label.setFont(Font ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD, 18.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE));
    Label labelLabel (210, 80, 80, 20, "Label");
    labelLabel.setFont (labelFont);
    window.add (&label);
    window.add (&labelLabel);

    // LabelEdit
    LabelEdit labelEdit (310, 10, 80, 60, "Edit me");
    labelEdit.setFont(Font ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD, 18.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE));
    Label labelEditLabel (310, 80, 80, 20, "LabelEdit");
    labelEditLabel.setFont (labelFont);
    window.add (&labelEdit);
    window.add (&labelEditLabel);

    // Text
    Text text (410, 10, 180, 60, loremipsum);
    Label textLabel (460, 80, 80, 20, "Text");
    textLabel.setFont (labelFont);
    window.add (&text);
    window.add (&textLabel);

    // Symbols
    Symbol addSymbol (610, 10, 20, 20, Symbol::ADD_SYMBOL);
    Symbol minusSymbol (640, 10, 20, 20, Symbol::MINUS_SYMBOL);
    Symbol leftSymbol (670, 10, 20, 20, Symbol::LEFT_SYMBOL);
    Symbol rightSymbol (610, 40, 20, 20, Symbol::RIGHT_SYMBOL);
    Symbol upSymbol (640, 40, 20, 20, Symbol::UP_SYMBOL);
    Symbol downSymbol (670, 40, 20, 20, Symbol::DOWN_SYMBOL);
    Symbol playSymbol (700, 10, 20, 20, Symbol::PLAY_SYMBOL);
    Symbol questionSymbol (730, 10, 20, 20, Symbol::QUESTION_SYMBOL);
    Symbol infoSymbol (760, 10, 20, 20, Symbol::INFO_SYMBOL);
    Symbol warnSymbol (700, 40, 20, 20, Symbol::WARN_SYMBOL);
    Symbol errorSymbol (730, 40, 20, 20, Symbol::ERROR_SYMBOL);
    Label symbolLabel (610, 80, 180, 20, "Symbol");
    symbolLabel.setFont (labelFont);
    window.add (&addSymbol);
    window.add (&minusSymbol);
    window.add (&leftSymbol);
    window.add (&rightSymbol);
    window.add (&upSymbol);
    window.add (&downSymbol);
    window.add (&playSymbol);
    window.add (&questionSymbol);
    window.add (&infoSymbol);
    window.add (&warnSymbol);
    window.add (&errorSymbol);
    window.add (&symbolLabel);

    // Image
    Image image (710, 130, 80, 60, "example-romedalen.png");
    Label imageLabel (710, 200, 80, 20, "Image");
    imageLabel.setFont (labelFont);
    window.add (&image);
    window.add (&imageLabel);

    // Button
    Button button (810, 30, 80, 20);
    Label buttonLabel (810, 80, 80, 20, "Button");
    buttonLabel.setFont (labelFont);
    window.add (&button);
    window.add (&buttonLabel);

    // TextButton
    TextButton textButton (910, 30, 80, 20, "Text");
    Label textButtonLabel (910, 80, 80, 20, "TextButton");
    textButtonLabel.setFont (labelFont);
    window.add (&textButton);
    window.add (&textButtonLabel);

    // SymbolButton
    SymbolButton symbolButton (1010, 30, 80, 20, Symbol::ADD_SYMBOL);
    Label symbolButtonLabel (1000, 80, 100, 20, "SymbolButton");
    symbolButtonLabel.setFont (labelFont);
    window.add (&symbolButton);
    window.add (&symbolButtonLabel);

    // ImageButton
    ImageButton imageButton (1110, 30, 80, 20, {"imgbut01.png", "imgbut02.png"});
    Label imageButtonLabel (1110, 80, 80, 20, "ImageButton");
    imageButtonLabel.setFont (labelFont);
    window.add (&imageButton);
    window.add (&imageButtonLabel);

    // CheckBox
    CheckBox checkBox (840, 150, 20, 20, true);
    Label checkBoxLabel (810, 200, 80, 20, "CheckBox");
    checkBoxLabel.setFont (labelFont);
    window.add (&checkBox);
    window.add (&checkBoxLabel);

    // RadioButton
    RadioButton radioButton (940, 150, 20, 20, true);
    Label radioButtonLabel (910, 200, 80, 20, "RadioButton");
    radioButtonLabel.setFont (labelFont);
    window.add (&radioButton);
    window.add (&radioButtonLabel);

    // HSwitch
    HSwitch hSwitch (1030, 150, 40, 20);
    Label hSwitchLabel (1010, 200, 80, 20, "HSwitch");
    hSwitchLabel.setFont (labelFont);
    window.add (&hSwitch);
    window.add (&hSwitchLabel);

    // VSwitch
    VSwitch vSwitch (1140, 140, 20, 40);
    Label vSwitchLabel (1110, 200, 80, 20, "VSwitch");
    vSwitchLabel.setFont (labelFont);
    window.add (&vSwitch);
    window.add (&vSwitchLabel);

    // SpinButton
    SpinButton spinButton (840, 270, 20, 20);
    Label spinButtonLabel (810, 320, 80, 20, "SpinButton");
    spinButtonLabel.setFont (labelFont);
    window.add (&spinButton);
    window.add (&spinButtonLabel);

    // SpinBox
    SpinBox spinBox (700, 270, 100, 20, {"Beethoven", "Bach", "Chopin", "Dvořák", "Händel", "Haydn", "Liszt", "Mozart", "Verdi", "Vivaldi"});
    spinBox.setValue (1);
    Label spinBoxLabel (710, 320, 80, 20, "SpinBox");
    spinBoxLabel.setFont (labelFont);
    window.add (&spinBox);
    window.add (&spinBoxLabel);

    // ListBox
    ListBox listBox (700, 370, 100, 180, {"AC/DC", "Bon Jovi", "Helloween", "Iron Maiden", "KISS", "Metallica", "Manowar", "Pantera", "Scorpions", "Sepultura", "Slayer", "Van Halen"});
    Label listBoxLabel (710, 560, 80, 20, "ListBox");
    listBoxLabel.setFont (labelFont);
    window.add (&listBox);
    window.add (&listBoxLabel);

     // Knob
    Knob knob (930, 260, 40, 40, 2);
    Label knobLabel (910, 320, 80, 20, "Knob");
    knobLabel.setFont (labelFont);
    window.add (&knob);
    window.add (&knobLabel);

    // HScale
    HScale hScale (1010, 275, 80, 10, 0.3, 0.0, 1.0, 0.0);
    hScale.setClickable (false);
    Label hScaleLabel (1010, 320, 80, 20, "HScale");
    hScaleLabel.setFont (labelFont);
    window.add (&hScale);
    window.add (&hScaleLabel);

    // VScale
    VScale vScale (1145, 250, 10, 60, 0.3, 0.0, 1.0, 0.0);
    vScale.setClickable (false);
    Label vScaleLabel (1110, 320, 80, 20, "VScale");
    vScaleLabel.setFont (labelFont);
    window.add (&vScale);
    window.add (&vScaleLabel);

    // Dial
    Dial dial (920, 370, 60, 60, 0.3, 0.0, 1.0, 0.0);
    dial.setClickable (false);
    Label dialLabel (910, 440, 80, 20, "Dial");
    dialLabel.setFont (labelFont);
    window.add (&dial);
    window.add (&dialLabel);

    // HSlider
    HSlider hSlider (1000, 390, 100, 20, 0.3, 0.0, 1.0, 0.0);
    hSlider.setClickable (false);
    Label hSliderLabel (1010, 440, 80, 20, "HSlider");
    hSliderLabel.setFont (labelFont);
    window.add (&hSlider);
    window.add (&hSliderLabel);

    // VSlider
    VSlider vSlider (1140, 360, 20, 80, 0.3, 0.0, 1.0, 0.0);
    vSlider.setClickable (false);
    Label vSliderLabel (1110, 440, 80, 20, "VSlider");
    vSliderLabel.setFont (labelFont);
    window.add (&vSlider);
    window.add (&vSliderLabel);

    // ValueDial
    ValueDial valueDial (920, 480, 60, 75, 0.3, 0.0, 1.0, 0.0);
    valueDial.setClickable (false);
    Label valueDialLabel (900, 560, 100, 20, "ValueDial");
    valueDialLabel.setFont (labelFont);
    window.add (&valueDial);
    window.add (&valueDialLabel);

    // ValueHSlider
    ValueHSlider valueHSlider (1000, 500, 100, 40, 0.3, 0.0, 1.0, 0.0);
    valueHSlider.setClickable (false);
    Label valueHSliderLabel (1000, 560, 100, 20, "ValueHSlider");
    valueHSliderLabel.setFont (labelFont);
    window.add (&valueHSlider);
    window.add (&valueHSliderLabel);

    // ValueVSlider
    ValueVSlider valueVSlider (1130, 480, 40, 80, 0.3, 0.0, 1.0, 0.0);
    valueVSlider.setClickable (false);
    Label valueVSliderLabel (1100, 560, 100, 20, "ValueVSlider");
    valueVSliderLabel.setFont (labelFont);
    window.add (&valueVSlider);
    window.add (&valueVSliderLabel);

    // HPianoRoll
    HPianoRoll hPianoRoll (310, 740, 580, 40);
    hPianoRoll.activate (36, 95, true);
    Label hPianoRollLabel (550, 800, 100, 20, "HPianoRoll");
    hPianoRollLabel.setFont (labelFont);
    window.add (&hPianoRoll);
    window.add (&hPianoRollLabel);

    // RadialMeter
    RadialMeter radialMeter (920, 610, 60, 60, 0.9, 0.0, 1.0, 0.05);
    radialMeter.setHiColors (reds);
    radialMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label radialMeterLabel (910, 680, 80, 20, "RadialMeter");
    radialMeterLabel.setFont (labelFont);
    window.add (&radialMeter);
    window.add (&radialMeterLabel);

    // HMeter
    HMeter hMeter (1010, 630, 80, 20, 0.9, 0.0, 1.0, 0.05);
    hMeter.setHiColors (reds);
    hMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label hMeterLabel (1010, 680, 80, 20, "HMeter");
    hMeterLabel.setFont (labelFont);
    window.add (&hMeter);
    window.add (&hMeterLabel);

    // VMeter
    VMeter vMeter (1140, 610, 20, 60, 0.9, 0.0, 1.0, 0.1);
    vMeter.setHiColors (reds);
    vMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label vMeterLabel (1110, 680, 80, 20, "VMeter");
    vMeterLabel.setFont (labelFont);
    window.add (&vMeter);
    window.add (&vMeterLabel);
    
    // ValueRadialMeter
    ValueRadialMeter valueRadialMeter (920, 720, 60, 75, 0.9, 0.0, 1.0, 0.05);
    valueRadialMeter.setHiColors (reds);
    valueRadialMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label valueRadialMeterLabel (900, 800, 100, 20, "ValueRadialMeter");
    valueRadialMeterLabel.setFont (labelFont);
    window.add (&valueRadialMeter);
    window.add (&valueRadialMeterLabel);

    // ValueHMeter
    ValueHMeter valueHMeter (1000, 750, 100, 20, 0.9, 0.0, 1.0, 0.1);
    valueHMeter.setHiColors (reds);
    valueHMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label valueHMeterLabel (1010, 800, 80, 20, "ValueHMeter");
    valueHMeterLabel.setFont (labelFont);
    window.add (&valueHMeter);
    window.add (&valueHMeterLabel);

    // ValueVMeter
    ValueVMeter valueVMeter (1130, 720, 40, 70, 0.9, 0.0, 1.0, 0.1);
    valueVMeter.setHiColors (reds);
    valueVMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label valueVMeterLabel (1110, 800, 80, 20, "ValueVMeter");
    valueVMeterLabel.setFont (labelFont);
    window.add (&valueVMeter);
    window.add (&valueVMeterLabel);

    // Box
    Box box (10, 130, 180, 60, {"Cancel", "OK"});
    Label boxLabel (10, 200, 180, 20, "Box");
    boxLabel.setFont (labelFont);
    window.add (&box);
    window.add (&boxLabel);

    // TextBox
    TextBox textBox (210, 130, 180, 170, loremipsum, {"Etiam"});
    Label textBoxLabel (210, 320, 180, 20, "TextBox");
    textBoxLabel.setFont (labelFont);
    window.add (&textBox);
    window.add (&textBoxLabel);

    // MessageBox
    MessageBox messageBox (410, 130, 280, 180, Symbol::INFO_SYMBOL, "Hello world is sooo easy:", "Window window;\nLabel label (\"Hello World\");\nwindow.add (&label);\nwindow.run ();", {"Close"});
    Label messageBoxLabel (410, 320, 280, 20, "MessageBox");
    messageBoxLabel.setFont (labelFont);
    window.add (&messageBox);
    window.add (&messageBoxLabel);

    window.run();
}