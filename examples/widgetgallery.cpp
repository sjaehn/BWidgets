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

#include <string>
#define MINIMP3_IMPLEMENTATION

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
#include "../BWidgets/Pattern.hpp"
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
#include "../BWidgets/HRangeScrollBar.hpp"
#include "../BWidgets/VRangeScrollBar.hpp"
#include "../BWidgets/FileChooser.hpp"
#include "../BWidgets/SampleChooser.hpp"
#include "../BWidgets/ConditionalImage.hpp"
#include "../BWidgets/ImageRadialMeter.hpp"
#include "../BWidgets/ImageHMeter.hpp"
#include "../BWidgets/ImageVMeter.hpp"
#include "../BWidgets/ImageDial.hpp"
#include "../BWidgets/ImageHSlider.hpp"
#include "../BWidgets/ImageVSlider.hpp"
#include "../BEvents/ExposeEvent.hpp"
#include <cairo/cairo.h>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

using namespace BWidgets;
using namespace BStyles;

Font labelFont ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE);
const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid ex ea commodi consequat. Quis aute iure reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

static void configureCallback (BEvents::Event* event)
{
    BEvents::ExposeEvent* ev = dynamic_cast<BEvents::ExposeEvent*>(event);
    if (!ev) return;
    Window* w = dynamic_cast<Window*>(ev->getWidget());
    if (!w) return;

	const double sz = (ev->getArea().getWidth() / 1500 > ev->getArea().getHeight() / 820 ? ev->getArea().getHeight() / 820 : ev->getArea().getWidth() / 1500);
	w->setZoom (sz);
}

int main ()
{
    // Window
    Window window (1500, 820, 0, URID_UNKNOWN_URID, "Window", true);
    window.setCallbackFunction(BEvents::Event::CONFIGURE_REQUEST_EVENT, configureCallback);

    // Widget
    Widget widget (10, 10, 80, 60, URID_UNKNOWN_URID, "Widget");
    widget.setTitle ("Widget");
    widget.setBorder (lightgreyBorder1pt);
    Label widgetLabel (10, 80, 80, 20, "Widget");
    widgetLabel.setFont (labelFont);
    window.add (&widget);
    window.add (&widgetLabel);

    // Frame
    Frame frame (110, 10, 80, 60);
    frame.setTitle ("Frame");
    frame.setBackground(darkgreyFill);
    frame.setBorder (lightgreyBorder1pt);
    Label frameDragLabel ("Drag me");
    frameDragLabel.setFocusable(false);
    frameDragLabel.setEventPassable(BEvents::Event::BUTTON_PRESS_EVENT, true);
    frameDragLabel.setEventPassable(BEvents::Event::POINTER_DRAG_EVENT, true);
    frameDragLabel.setEventPassable(BEvents::Event::FOCUS_IN_EVENT, true);
    frameDragLabel.setEventPassable(BEvents::Event::FOCUS_OUT_EVENT, true);
    frame.add (&frameDragLabel);
    frameDragLabel.moveTo(frameDragLabel.center(), frameDragLabel.middle());
    Label frameLabel (110, 80, 80, 20, "Frame");
    frameLabel.setFont (labelFont);
    window.add (&frame);
    window.add (&frameLabel);

    // Label
    Label label (10, 130, 80, 60, "Text");
    label.setTitle ("Label");
    label.setFont(Font ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD, 18.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE));
    Label labelLabel (10, 200, 80, 20, "Label");
    labelLabel.setFont (labelFont);
    window.add (&label);
    window.add (&labelLabel);

    // LabelEdit
    LabelEdit labelEdit (110, 130, 80, 60, "Edit me");
    labelEdit.setTitle("LabelEdit");
    labelEdit.setFont(Font ("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD, 18.0, BStyles::Font::TEXT_ALIGN_CENTER, BStyles::Font::TEXT_VALIGN_MIDDLE));
    Label labelEditLabel (110, 200, 80, 20, "LabelEdit");
    labelEditLabel.setFont (labelFont);
    window.add (&labelEdit);
    window.add (&labelEditLabel);

    // Text
    Text text (10, 250, 180, 60, loremipsum);
    text.setTitle("Text");
    Label textLabel (60, 320, 80, 20, "Text");
    textLabel.setFont (labelFont);
    window.add (&text);
    window.add (&textLabel);

    // Symbols
    std::array<std::unique_ptr<Symbol>, Symbol::NEW_FOLDER_SYMBOL + 1> symbols;
    for (int i = 0; i <= Symbol::NEW_FOLDER_SYMBOL; ++i)
    {
        symbols[i] = std::unique_ptr<Symbol> (new Symbol (410 + 18 * (i % 16), 10 + 18 * int (i / 16), 12, 12, Symbol::SymbolType(i)));
        symbols[i]->setTitle ("Symbol " + std::to_string(i));
        window.add (symbols[i].get());
    }
    Label symbolLabel (510, 80, 80, 20, "Symbol");
    symbolLabel.setFont (labelFont);
    window.add (&symbolLabel);

    // Button
    Button button (710, 30, 80, 20);
    button.setTitle ("Button");
    Label buttonLabel (710, 80, 80, 20, "Button");
    buttonLabel.setFont (labelFont);
    window.add (&button);
    window.add (&buttonLabel);

    // TextButton
    TextButton textButton (810, 30, 80, 20, "Text", false, false, URID_UNKNOWN_URID, "TextButton");
    textButton.setTitle("TextButton");
    Label textButtonLabel (810, 80, 80, 20, "TextButton");
    textButtonLabel.setFont (labelFont);
    window.add (&textButton);
    window.add (&textButtonLabel);

    // SymbolButton
    SymbolButton symbolButton (910, 30, 80, 20, Symbol::ADD_SYMBOL, false, false, URID_UNKNOWN_URID, "SymbolButton");
    symbolButton.setTitle("SymbolButton");
    Label symbolButtonLabel (900, 80, 100, 20, "SymbolButton");
    symbolButtonLabel.setFont (labelFont);
    window.add (&symbolButton);
    window.add (&symbolButtonLabel);

    // Pad
    Pad<> pad (1010, 20, 80, 40, 0.7, 0.0, 1.0, 0.0);
    pad.setTitle ("Pad");
    pad.setFgColors(BStyles::reds);
    Label padLabel (1000, 80, 100, 20, "Pad");
    padLabel.setFont (labelFont);
    window.add (&pad);
    window.add (&padLabel);

    // SymbolPad
    SymbolPad<> symbolPad (1110, 20, 80, 40, Symbol::PLAY_SYMBOL, 0.7, 0.0, 1.0, 0.0);
    symbolPad.setTitle ("Symbolpad");
    symbolPad.setFgColors(BStyles::blues);
    Label symbolPadLabel (1100, 80, 100, 20, "SymbolPad");
    symbolPadLabel.setFont (labelFont);
    window.add (&symbolPad);
    window.add (&symbolPadLabel);

    // SpinButton
    SpinButton spinButton (740, 150, 20, 20);
    spinButton.setTitle("SpinButton");
    Label spinButtonLabel (710, 200, 80, 20, "SpinButton");
    spinButtonLabel.setFont (labelFont);
    window.add (&spinButton);
    window.add (&spinButtonLabel);

    // CheckBox
    CheckBox checkBox (840, 150, 20, 20, true);
    checkBox.setTitle("CheckBox");
    Label checkBoxLabel (810, 200, 80, 20, "CheckBox");
    checkBoxLabel.setFont (labelFont);
    window.add (&checkBox);
    window.add (&checkBoxLabel);

    // RadioButton
    RadioButton radioButton (940, 150, 20, 20, true);
    radioButton.setTitle("RadioButton");
    Label radioButtonLabel (910, 200, 80, 20, "RadioButton");
    radioButtonLabel.setFont (labelFont);
    window.add (&radioButton);
    window.add (&radioButtonLabel);

    // HSwitch
    HSwitch hSwitch (1030, 150, 40, 20);
    hSwitch.setTitle("HSwitch");
    Label hSwitchLabel (1010, 200, 80, 20, "HSwitch");
    hSwitchLabel.setFont (labelFont);
    window.add (&hSwitch);
    window.add (&hSwitchLabel);

    // VSwitch
    VSwitch vSwitch (1140, 140, 20, 40);
    vSwitch.setTitle("VSwitch");
    Label vSwitchLabel (1110, 200, 80, 20, "VSwitch");
    vSwitchLabel.setFont (labelFont);
    window.add (&vSwitch);
    window.add (&vSwitchLabel);

    // HScrollBar
    HScrollBar hScrollBar (710, 275, 80, 10, 0.2, 0, 1, 0, 0.3);
    hScrollBar.setTitle("HScrollBar");
    Label hScrollBarLabel (710, 320, 80, 20, "HScrollBar");
    hScrollBarLabel.setFont (labelFont);
    window.add (&hScrollBar);
    window.add (&hScrollBarLabel);

    // VScrollBar
    VScrollBar vScrollBar (845, 250, 10, 60, 0.2, 0, 1, 0, 0.3);
    vScrollBar.setTitle("VScrollBar");
    Label vScrollBarLabel (810, 320, 80, 20, "VScrollBar");
    vScrollBarLabel.setFont (labelFont);
    window.add (&vScrollBar);
    window.add (&vScrollBarLabel);

    // HRangeScrollBar
    HRangeScrollBar hRangeScrollBar (710, 395, 80, 10, 0.2, 0.5, 0, 1, 0);
    hRangeScrollBar.setTitle("HRangeScrollBar");
    Label hRangeScrollBarLabel (700, 440, 100, 20, "HRangeScrollBar");
    hRangeScrollBarLabel.setFont (labelFont);
    window.add (&hRangeScrollBar);
    window.add (&hRangeScrollBarLabel);

    // VRangeScrollBar
    VRangeScrollBar vRangeScrollBar (845, 370, 10, 60, 0.2, 0.5, 0, 1, 0);
    vRangeScrollBar.setTitle("VRangeScrollBar");
    Label vRangeScrollBarLabel (800, 440, 100, 20, "VRangeScrollBar");
    vRangeScrollBarLabel.setFont (labelFont);
    window.add (&vRangeScrollBar);
    window.add (&vRangeScrollBarLabel);

    // SpinBox
    SpinBox spinBox (700, 490, 100, 20, {"Beethoven", "Bach", "Chopin", "Dvořák", "Händel", "Haydn", "Liszt", "Mozart", "Verdi", "Vivaldi"});
    spinBox.setTitle("SpinBox");
    spinBox.setValue (1);
    Label spinBoxLabel (710, 520, 80, 20, "SpinBox");
    spinBoxLabel.setFont (labelFont);
    window.add (&spinBox);
    window.add (&spinBoxLabel);

    // ComboBox
    ComboBox comboBox (700, 560, 100, 20, 0, 20, 100, 90, {"Avicii", "Daft Punk", "M. Garrix", "D. Guetta", "Kygo", "Marshmello", "R. Schulz", "DJ Spooky", "Tiësto", "A. van Buren", "P. van Dyke", "S. Väth", "A. Walker"});
    comboBox.setTitle("ComboBox");
    comboBox.setValue (1);
    Label comboBoxLabel (710, 680, 80, 20, "ComboBox");
    comboBoxLabel.setFont (labelFont);
    window.add (&comboBox);
    window.add (&comboBoxLabel);

    // ListBox
    ListBox listBox (810, 490, 80, 180, {"AC/DC", "Bon Jovi", "Helloween", "Iron Maiden", "KISS", "Metallica", "Manowar", "Pantera", "Scorpions", "Sepultura", "Slayer", "Van Halen"});
    listBox.setTitle("ListBox");
    listBox.setValue (1);
    listBox.setTop (1);
    Label listBoxLabel (810, 680, 80, 20, "ListBox");
    listBoxLabel.setFont (labelFont);
    window.add (&listBox);
    window.add (&listBoxLabel);

     // Knob
    Knob knob (930, 260, 40, 40, 2);
    knob.setTitle("Knob");
    Label knobLabel (910, 320, 80, 20, "Knob");
    knobLabel.setFont (labelFont);
    window.add (&knob);
    window.add (&knobLabel);

    // HScale
    HScale hScale (1010, 275, 80, 10, 0.3, 0.0, 1.0, 0.0);
    hScale.setTitle("HScale");
    hScale.setClickable (false);
    Label hScaleLabel (1010, 320, 80, 20, "HScale");
    hScaleLabel.setFont (labelFont);
    window.add (&hScale);
    window.add (&hScaleLabel);

    // VScale
    VScale vScale (1145, 250, 10, 60, 0.3, 0.0, 1.0, 0.0);
    vScale.setTitle ("VScale");
    vScale.setClickable (false);
    Label vScaleLabel (1110, 320, 80, 20, "VScale");
    vScaleLabel.setFont (labelFont);
    window.add (&vScale);
    window.add (&vScaleLabel);

    // Dial
    Dial dial (920, 370, 60, 60, 0.3, 0.0, 1.0, 0.0);
    dial.setTitle("Dial");
    dial.setClickable (false);
    Label dialLabel (910, 440, 80, 20, "Dial");
    dialLabel.setFont (labelFont);
    window.add (&dial);
    window.add (&dialLabel);

    // HSlider
    HSlider hSlider (1000, 390, 100, 20, 0.3, 0.0, 1.0, 0.0);
    hSlider.setTitle ("HSlider");
    hSlider.setClickable (false);
    Label hSliderLabel (1010, 440, 80, 20, "HSlider");
    hSliderLabel.setFont (labelFont);
    window.add (&hSlider);
    window.add (&hSliderLabel);

    // VSlider
    VSlider vSlider (1140, 360, 20, 80, 0.3, 0.0, 1.0, 0.0);
    vSlider.setTitle("VSlider");
    vSlider.setClickable (false);
    Label vSliderLabel (1110, 440, 80, 20, "VSlider");
    vSliderLabel.setFont (labelFont);
    window.add (&vSlider);
    window.add (&vSliderLabel);

    // ValueDial
    ValueDial valueDial (920, 480, 60, 75, 0.3, 0.0, 1.0, 0.0);
    valueDial.setTitle ("ValueDial");
    valueDial.setClickable (false);
    Label valueDialLabel (900, 560, 100, 20, "ValueDial");
    valueDialLabel.setFont (labelFont);
    window.add (&valueDial);
    window.add (&valueDialLabel);

    // ValueHSlider
    ValueHSlider valueHSlider (1000, 500, 100, 40, 0.3, 0.0, 1.0, 0.0);
    valueHSlider.setTitle ("ValueHSlider");
    valueHSlider.setClickable (false);
    Label valueHSliderLabel (1000, 560, 100, 20, "ValueHSlider");
    valueHSliderLabel.setFont (labelFont);
    window.add (&valueHSlider);
    window.add (&valueHSliderLabel);

    // ValueVSlider
    ValueVSlider valueVSlider (1130, 480, 40, 80, 0.3, 0.0, 1.0, 0.0);
    valueVSlider.setTitle("ValueVSlider");
    valueVSlider.setClickable (false);
    Label valueVSliderLabel (1100, 560, 100, 20, "ValueVSlider");
    valueVSliderLabel.setFont (labelFont);
    window.add (&valueVSlider);
    window.add (&valueVSliderLabel);

    // HPianoRoll
    HPianoRoll hPianoRoll (10, 740, 580, 40);
    hPianoRoll.setTitle("HPianoRoll");
    hPianoRoll.activate (36, 95, true);
    Label hPianoRollLabel (250, 800, 100, 20, "HPianoRoll");
    hPianoRollLabel.setFont (labelFont);
    window.add (&hPianoRoll);
    window.add (&hPianoRollLabel);

    // RadialMeter
    RadialMeter radialMeter (920, 610, 60, 60, 0.9, 0.0, 1.0, 0.05);
    radialMeter.setTitle("RadialMeter");
    radialMeter.setHiColors (reds);
    radialMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label radialMeterLabel (910, 680, 80, 20, "RadialMeter");
    radialMeterLabel.setFont (labelFont);
    window.add (&radialMeter);
    window.add (&radialMeterLabel);

    // HMeter
    HMeter hMeter (1010, 630, 80, 20, 0.9, 0.0, 1.0, 0.05);
    hMeter.setTitle("HMeter");
    hMeter.setHiColors (reds);
    hMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label hMeterLabel (1010, 680, 80, 20, "HMeter");
    hMeterLabel.setFont (labelFont);
    window.add (&hMeter);
    window.add (&hMeterLabel);

    // VMeter
    VMeter vMeter (1140, 610, 20, 60, 0.9, 0.0, 1.0, 0.1);
    vMeter.setTitle("VMeter");
    vMeter.setHiColors (reds);
    vMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label vMeterLabel (1110, 680, 80, 20, "VMeter");
    vMeterLabel.setFont (labelFont);
    window.add (&vMeter);
    window.add (&vMeterLabel);
    
    // ValueRadialMeter
    ValueRadialMeter valueRadialMeter (920, 720, 60, 75, 0.9, 0.0, 1.0, 0.05);
    valueRadialMeter.setTitle("ValueRadialMeter");
    valueRadialMeter.setHiColors (reds);
    valueRadialMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label valueRadialMeterLabel (900, 800, 100, 20, "ValueRadialMeter");
    valueRadialMeterLabel.setFont (labelFont);
    window.add (&valueRadialMeter);
    window.add (&valueRadialMeterLabel);

    // ValueHMeter
    ValueHMeter valueHMeter (1000, 750, 100, 20, 0.9, 0.0, 1.0, 0.1);
    valueHMeter.setTitle("ValueHMeter");
    valueHMeter.setHiColors (reds);
    valueHMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label valueHMeterLabel (1010, 800, 80, 20, "ValueHMeter");
    valueHMeterLabel.setFont (labelFont);
    window.add (&valueHMeter);
    window.add (&valueHMeterLabel);

    // ValueVMeter
    ValueVMeter valueVMeter (1130, 720, 40, 70, 0.9, 0.0, 1.0, 0.1);
    valueVMeter.setTitle("ValueVMeter");
    valueVMeter.setHiColors (reds);
    valueVMeter.setGradientFunction([] (const double& x) {return x * x;});
    Label valueVMeterLabel (1110, 800, 80, 20, "ValueVMeter");
    valueVMeterLabel.setFont (labelFont);
    window.add (&valueVMeter);
    window.add (&valueVMeterLabel);

    // Box
    Box box (210, 10, 180, 60, {BUtilities::Dictionary::get("Cancel"), BUtilities::Dictionary::get("OK")});
    box.setTitle ("Box");
    Label boxLabel (210, 80, 180, 20, "Box");
    boxLabel.setFont (labelFont);
    window.add (&box);
    window.add (&boxLabel);

    // TextBox
    TextBox textBox (210, 130, 180, 170, loremipsum, {"Etiam"});
    textBox.setTitle("TextBox");
    Label textBoxLabel (210, 320, 180, 20, "TextBox");
    textBoxLabel.setFont (labelFont);
    window.add (&textBox);
    window.add (&textBoxLabel);

    // MessageBox
    MessageBox messageBox   (410, 130, 280, 180, Symbol::INFO_SYMBOL, 
                             "Hello world is sooo easy:", "Window window;\nLabel label (\"Hello World\");\nwindow.add (&label);\nwindow.run ();", 
                             {BUtilities::Dictionary::get("Close")});
    messageBox.setTitle("MessageBox");
    Label messageBoxLabel (410, 320, 280, 20, "MessageBox");
    messageBoxLabel.setFont (labelFont);
    window.add (&messageBox);
    window.add (&messageBoxLabel);

    // FileChooser
    std::initializer_list<FileChooser::Filter> fileFilter =
    {
        FileChooser::Filter {BUtilities::Dictionary::get ("All files"), std::regex (".*")},
        FileChooser::Filter {BUtilities::Dictionary::get ("C/C++ files"), std::regex (".*\\.((c)|(cc)|(cxx)|(cpp)|(h)|(hh)|(hpp)|(hxx))$", std::regex_constants::icase)},
        FileChooser::Filter {BUtilities::Dictionary::get ("Image files"), std::regex (".*\\.((png)|(bmp)|(jpg)|(jpeg)|(tif)|(tiff))$", std::regex_constants::icase)},
        FileChooser::Filter {BUtilities::Dictionary::get ("Sound files"), std::regex (".*\\.((wav)|(wave)|(aif)|(aiff)|(au)|(sd2)|(flac)|(caf)|(ogg)|(mp3))$", std::regex_constants::icase)}
    };
    FileChooser fileChooser (10, 370, 280, 290, ".", fileFilter);
    fileChooser.setTitle("FileChooser");
    Label fileChooserLabel (100, 680, 100, 20, "FileChooser");
    fileChooserLabel.setFont (labelFont);
    window.add (&fileChooserLabel);
    window.add (&fileChooser);

    // SampleChooser
    SampleChooser sampleChooser (310, 370, 380, 290);
    sampleChooser.setTitle("SampleChooser");
    Label sampleChooserLabel (450, 680, 100, 20, "SampleChooser");
    sampleChooserLabel.setFont (labelFont);
    window.add (&sampleChooserLabel);
    window.add (&sampleChooser);

    // Pattern
    Pattern<> pattern (1210, 10, 280, 180, 4, 4);
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
    Label patternLabel (1310, 200, 80, 20, "Pattern");
    patternLabel.setFont (labelFont);
    window.add (&pattern);
    window.add (&patternLabel);

    // Image
    Image image (1210, 250, 80, 60, "examples/inc/music-guitar-acoustic-guitar-instrument-electric-guitar-musical-instrument-stringed-instrument-bass-fender-strings-bass-guitar-e-bass-jazzbass-string-instrument-plucked-string-instruments-slide-guitar-acoustic-electric-guitar-699195.png");
    image.setTitle("Image");
    Label imageLabel (1210, 320, 80, 20, "Image");
    imageLabel.setFont (labelFont);
    window.add (&image);
    window.add (&imageLabel);

    // ImageButton
    ImageButton imageButton (1320, 250, 60, 60, {"examples/inc/imgbut01.png", "examples/inc/imgbut02.png"}, true);
    imageButton.setTitle("ImageButton");
    imageButton.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    imageButton.setBgColors(BStyles::ColorMap ({BStyles::invisible}));
    Label imageButtonLabel (1310, 320, 80, 20, "ImageButton");
    imageButtonLabel.setFont (labelFont);
    window.add (&imageButton);
    window.add (&imageButtonLabel);
    
    // ConditionalImage
    ConditionalImage conditionalImage   (1410, 250, 80, 60, 
                                         {{0.0, "examples/inc/ConditionalImage0.png"}, 
                                          {1.0, "examples/inc/ConditionalImage1.png"},
                                          {2.0, "examples/inc/ConditionalImage2.png"},
                                          {3.0, "examples/inc/ConditionalImage3.png"}},
                                         0.0, 0.0, 3.0, 0.0);
    conditionalImage.setTitle("ConditionalImage");
    conditionalImage.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    Label conditionalImageLabel (1390, 320, 120, 20, "ConditionalImage");
    conditionalImageLabel.setFont (labelFont);
    window.add (&conditionalImage);
    window.add (&conditionalImageLabel);

    // ImageRadialMeter
    ImageRadialMeter imageRadialMeter (1210, 370, 80, 60, 
                             "examples/inc/ImageRadialMeter_s.png", {132.0, 264.0}, 1.35 * M_PI, 1.65 * M_PI,
                             "", {0.0, 0.0},
                             "examples/inc/ImageRadialMeter_d.png", {132.0, 264.0},
                             0.5);
    imageRadialMeter.setTitle("ImageRadialMeter");
    imageRadialMeter.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    Label imageRadialMeterLabel (1190, 440, 120, 20, "ImageRadialMeter");
    imageRadialMeterLabel.setFont (labelFont);
    window.add (&imageRadialMeter);
    window.add (&imageRadialMeterLabel);

    // ImageHMeter
    ImageHMeter imageHMeter (1310, 380, 80, 40, 
                             "examples/inc/ImageHMeter_s.png", {{35.0, 55.0}, {230.0, 55.0}},
                             "examples/inc/ImageHMeter_a.png", {35.0, 55.0},
                             "", {0.0, 0.0},
                             0.5, 0.0, 1.0, 1.0 / 15.0);
    imageHMeter.setTitle("ImageHMeter");
    imageHMeter.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    Label imageHMeterLabel (1310, 440, 80, 20, "ImageHMeter");
    imageHMeterLabel.setFont (labelFont);
    window.add (&imageHMeter);
    window.add (&imageHMeterLabel);
    
    // ImageVMeter
    ImageVMeter imageVMeter (1430, 360, 40, 80, 
                             "examples/inc/ImageVMeter_s.png", {{55.0, 228.0}, {55.0, 32.0}},
                             "examples/inc/ImageVMeter_a.png", {55.0, 228.0},
                             "", {0.0, 0.0},
                             0.5, 0.0, 1.0, 1.0 / 15.0);
    imageVMeter.setTitle("ImageVMeter");
    imageVMeter.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    Label imageVMeterLabel (1410, 440, 80, 20, "ImageVMeter");
    imageVMeterLabel.setFont (labelFont);
    window.add (&imageVMeter);
    window.add (&imageVMeterLabel);

    // ImageDial
    ImageDial imageDial (1210, 490, 80, 60, 
                             "examples/inc/ImageDial_s.png", {150.0, 150.0}, 0.75 * M_PI, 2.25 * M_PI,
                             "examples/inc/ImageDial_a.png", {150.0, 150.0},
                             "examples/inc/ImageDial_d.png", {150.0, 150.0},
                             0.5);
    imageDial.setTitle("ImageDial");
    imageDial.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    imageDial.setClickable (false);
    Label imageDialLabel (1210, 560, 80, 20, "ImageDial");
    imageDialLabel.setFont (labelFont);
    window.add (&imageDial);
    window.add (&imageDialLabel);

    // ImageHSlider
    ImageHSlider imageHSlider (1310, 500, 80, 40, 
                             "examples/inc/ImageHSlider_s.png", {{21.0, 22.0}, {112.0, 22.0}},
                             "examples/inc/ImageHSlider_a.png", {21.0, 22.0},
                             "examples/inc/ImageHSlider_d.png", {21.0, 10.0},
                             0.5);
    imageHSlider.setTitle("ImageHSlider");
    imageHSlider.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    imageHSlider.setClickable (false);
    Label imageHSliderLabel (1310, 560, 80, 20, "ImageHSlider");
    imageHSliderLabel.setFont (labelFont);
    window.add (&imageHSlider);
    window.add (&imageHSliderLabel);
    
    // ImageVSlider
    ImageVSlider imageVSlider (1430, 480, 40, 80, 
                             "examples/inc/ImageVSlider_s.png", {{24.0, 113.0}, {24.0, 22.0}},
                             "examples/inc/ImageVSlider_a.png", {24.0, 113.0},
                             "examples/inc/ImageVSlider_d.png", {10.0, 21.0},
                             0.5);
    imageVSlider.setTitle("ImageVSlider");
    imageVSlider.setBackground(BStyles::Fill ("examples/inc/ImageVSliderBg.png"));
    imageVSlider.setClickable (false);
    Label imageVSliderLabel (1410, 560, 80, 20, "ImageVSlider");
    imageVSliderLabel.setFont (labelFont);
    window.add (&imageVSlider);
    window.add (&imageVSliderLabel);

    const std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();

    while (!window.isQuit())
    {
        const std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        const std::chrono::duration<double> dt = t - t0;
        radialMeter.setValue (0.5 + 0.5 * sin (1.2 * dt.count()));
        hMeter.setValue (0.5 + 0.5 * sin (dt.count()));
        vMeter.setValue (0.5 + 0.5 * sin (2.0 * dt.count()));
        valueRadialMeter.setValue (0.5 + 0.5 * cos (0.5 * dt.count()));
        valueHMeter.setValue (0.5 + 0.5 * sin (1.4 * dt.count()));
        valueVMeter.setValue (0.5 + 0.5 * cos (0.7 * dt.count()));
        imageRadialMeter.setValue (0.5 + 0.5 * sin (0.6 * dt.count()));
        imageHMeter.setValue (0.5 + 0.5 * cos (0.8 * dt.count()));
        imageVMeter.setValue (0.5 + 0.5 * sin (1.3 * dt.count()));
        window.handleEvents();
    }
}