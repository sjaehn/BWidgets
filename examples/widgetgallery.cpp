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
#include "../BWidgets/Pad.hpp"
#include "../BWidgets/SymbolPad.hpp"
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
#include "../BWidgets/ComboBox.hpp"
#include "../BWidgets/HScrollBar.hpp"
#include "../BWidgets/VScrollBar.hpp"
#include "../BWidgets/FileChooser.hpp"
#include "../BWidgets/Pattern.hpp"
#include <cairo/cairo.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

using namespace BWidgets;
using namespace BStyles;

Font labelFont ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE);

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

int main ()
{
    BUtilities::Dictionary::setLanguage ("en");

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
    Label label (10, 130, 80, 60, "Text");
    label.setFont(Font ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD, 18.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE));
    Label labelLabel (10, 200, 80, 20, "Label");
    labelLabel.setFont (labelFont);
    window.add (&label);
    window.add (&labelLabel);

    // LabelEdit
    LabelEdit labelEdit (110, 130, 80, 60, "Edit me");
    labelEdit.setFont(Font ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD, 18.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE));
    Label labelEditLabel (110, 200, 80, 20, "LabelEdit");
    labelEditLabel.setFont (labelFont);
    window.add (&labelEdit);
    window.add (&labelEditLabel);

    // Text
    Text text (10, 250, 180, 60, loremipsum);
    Label textLabel (60, 320, 80, 20, "Text");
    textLabel.setFont (labelFont);
    window.add (&text);
    window.add (&textLabel);

    // Symbols
    std::array<std::unique_ptr<Symbol>, Symbol::NEW_FOLDER_SYMBOL + 1> symbols;
    for (int i = 0; i <= Symbol::NEW_FOLDER_SYMBOL; ++i)
    {
        symbols[i] = std::unique_ptr<Symbol> (new Symbol (410 + 16 * (i % 5), 10 + 16 * int (i / 5), 12, 12, Symbol::SymbolType(i)));
        window.add (symbols[i].get());
    }
    Label symbolLabel (410, 80, 80, 20, "Symbol");
    symbolLabel.setFont (labelFont);
    window.add (&symbolLabel);

    // Image
    Image image (510, 10, 80, 60, "example-romedalen.png");
    Label imageLabel (510, 80, 80, 20, "Image");
    imageLabel.setFont (labelFont);
    window.add (&image);
    window.add (&imageLabel);

    // ImageButton
    ImageButton imageButton (610, 30, 80, 20, {"imgbut01.png", "imgbut02.png"});
    Label imageButtonLabel (610, 80, 80, 20, "ImageButton");
    imageButtonLabel.setFont (labelFont);
    window.add (&imageButton);
    window.add (&imageButtonLabel);

    // Button
    Button button (710, 30, 80, 20);
    Label buttonLabel (710, 80, 80, 20, "Button");
    buttonLabel.setFont (labelFont);
    window.add (&button);
    window.add (&buttonLabel);

    // TextButton
    TextButton textButton (810, 30, 80, 20, "Text");
    Label textButtonLabel (810, 80, 80, 20, "TextButton");
    textButtonLabel.setFont (labelFont);
    window.add (&textButton);
    window.add (&textButtonLabel);

    // SymbolButton
    SymbolButton symbolButton (910, 30, 80, 20, Symbol::ADD_SYMBOL);
    Label symbolButtonLabel (900, 80, 100, 20, "SymbolButton");
    symbolButtonLabel.setFont (labelFont);
    window.add (&symbolButton);
    window.add (&symbolButtonLabel);

    // Pad
    Pad<> pad (1010, 20, 80, 40, 0.7, 0.0, 1.0, 0.0);
    pad.setFgColors(BStyles::reds);
    Label padLabel (1000, 80, 100, 20, "Pad");
    padLabel.setFont (labelFont);
    window.add (&pad);
    window.add (&padLabel);

    // SymbolPad
    SymbolPad<> symbolPad (1110, 20, 80, 40, Symbol::PLAY_SYMBOL, 0.7, 0.0, 1.0, 0.0);
    symbolPad.setFgColors(BStyles::blues);
    Label symbolPadLabel (1100, 80, 100, 20, "SymbolPad");
    symbolPadLabel.setFont (labelFont);
    window.add (&symbolPad);
    window.add (&symbolPadLabel);

    // SpinButton
    SpinButton spinButton (740, 150, 20, 20);
    Label spinButtonLabel (710, 200, 80, 20, "SpinButton");
    spinButtonLabel.setFont (labelFont);
    window.add (&spinButton);
    window.add (&spinButtonLabel);

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

    // HScrollBar
    HScrollBar hScrollBar (710, 275, 80, 10, 0.2, 0, 1, 0, 0.3);
    Label hScrollBarLabel (710, 320, 80, 20, "HScrollBar");
    hScrollBarLabel.setFont (labelFont);
    window.add (&hScrollBar);
    window.add (&hScrollBarLabel);

    // VScrollBar
    VScrollBar vScrollBar (845, 250, 10, 60, 0.2, 0, 1, 0, 0.3);
    Label vScrollBarLabel (810, 320, 80, 20, "VScrollBar");
    vScrollBarLabel.setFont (labelFont);
    window.add (&vScrollBar);
    window.add (&vScrollBarLabel);

    // SpinBox
    SpinBox spinBox (700, 390, 100, 20, {"Beethoven", "Bach", "Chopin", "Dvořák", "Händel", "Haydn", "Liszt", "Mozart", "Verdi", "Vivaldi"});
    spinBox.setValue (1);
    Label spinBoxLabel (710, 440, 80, 20, "SpinBox");
    spinBoxLabel.setFont (labelFont);
    window.add (&spinBox);
    window.add (&spinBoxLabel);

    // ComboBox
    ComboBox comboBox (700, 510, 100, 20, {"Avicii", "Daft Punk", "M. Garrix", "D. Guetta", "Kygo", "Marshmello", "R. Schulz", "DJ Spooky", "Tiësto", "A. van Buren", "P. van Dyke", "S. Väth", "A. Walker"});
    comboBox.setValue (1);
    Label comboBoxLabel (710, 560, 80, 20, "ComboBox");
    comboBoxLabel.setFont (labelFont);
    window.add (&comboBox);
    window.add (&comboBoxLabel);

    // ListBox
    ListBox listBox (810, 370, 80, 180, {"AC/DC", "Bon Jovi", "Helloween", "Iron Maiden", "KISS", "Metallica", "Manowar", "Pantera", "Scorpions", "Sepultura", "Slayer", "Van Halen"});
    listBox.setValue (1);
    listBox.setTop (1);
    Label listBoxLabel (810, 560, 80, 20, "ListBox");
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
    HPianoRoll hPianoRoll (10, 740, 580, 40);
    hPianoRoll.activate (36, 95, true);
    Label hPianoRollLabel (250, 800, 100, 20, "HPianoRoll");
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
    Box box (210, 10, 180, 60, {BUtilities::Dictionary::get("Cancel"), BUtilities::Dictionary::get("OK")});
    Label boxLabel (210, 80, 180, 20, "Box");
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
    MessageBox messageBox   (410, 130, 280, 180, Symbol::INFO_SYMBOL, 
                             "Hello world is sooo easy:", "Window window;\nLabel label (\"Hello World\");\nwindow.add (&label);\nwindow.run ();", 
                             {BUtilities::Dictionary::get("Close")});
    Label messageBoxLabel (410, 320, 280, 20, "MessageBox");
    messageBoxLabel.setFont (labelFont);
    window.add (&messageBox);
    window.add (&messageBoxLabel);

    // FileChooser
    FileChooser fileChooser (10, 370, 280, 290);
    Label fileChooserLabel (100, 680, 100, 20, "FileChooser");
    fileChooserLabel.setFont (labelFont);
    window.add (&fileChooser);
    window.add (&fileChooserLabel);

    // Pattern
    Pattern<> pattern (710, 610, 180, 180, 4, 4);
    std::array<BStyles::ColorMap, 4> patternColors = {{BStyles::reds, BStyles::yellows, BStyles::greens, BStyles::blues}};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Pad<>* w = dynamic_cast<Pad<>*>(pattern.getPad (2 * (i % 2) + (j % 2), 2 * int (i / 2) + int (j / 2)));
            if (w) 
            {
                w->setFgColors(patternColors[i]);
                w->setValue (double (std::rand())/ RAND_MAX);
            }
        }
    }
    Label patternLabel (760, 800, 80, 20, "Pattern");
    patternLabel.setFont (labelFont);
    window.add (&pattern);
    window.add (&patternLabel);

    window.run();
}