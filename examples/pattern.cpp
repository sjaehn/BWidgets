/* pattern.cpp
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
#include "../BWidgets/SymbolButton.hpp"
#include "../BWidgets/Pattern.hpp"
#include <array>
#include <memory>

using namespace BWidgets;

#define NR_EDIT_BUTTONS 8

constexpr std::array<Symbol::SymbolType, NR_EDIT_BUTTONS> buttonSymbols =
{{
    Symbol::NO_SYMBOL,
    Symbol::PICK_SYMBOL,
    Symbol::CUT_SYMBOL,
    Symbol::COPY_SYMBOL,
    Symbol::PASTE_SYMBOL,
    Symbol::DELETE_SYMBOL,
    Symbol::XFLIP_SYMBOL,
    Symbol::YFLIP_SYMBOL
}};

constexpr std::array<Pattern<>::EditMode, NR_EDIT_BUTTONS> editModes =
{{
    Pattern<>::MODE_EDIT,
    Pattern<>::MODE_PICK,
    Pattern<>::MODE_CUT,
    Pattern<>::MODE_COPY,
    Pattern<>::MODE_PASTE,
    Pattern<>::MODE_DELETE,
    Pattern<>::MODE_XFLIP,
    Pattern<>::MODE_YFLIP
}};

std::array<std::unique_ptr<SymbolButton>, NR_EDIT_BUTTONS> buttons;
size_t mode = 0;
std::unique_ptr<Pattern<>> pattern;

// Callback function for clicks on the edit mode buttons
static void buttonChangedCallback (BEvents::Event* event)
{
    // Boiler plate
    SymbolButton* w = dynamic_cast<SymbolButton*>(event->getWidget());
    if (!w) return;

    // Only pressed buttons will change the mode
    if (w->getValue())
    {
        // Find pressed button
        for (size_t i = 0; i < NR_EDIT_BUTTONS; ++i)
        {
            if (buttons[i].get() == w) mode = i;
        }
    }

    // Exactly ONE pressed button
    for (size_t i = 0; i < NR_EDIT_BUTTONS; ++i)
    {
        if (i == mode) buttons[i]->setValue (true);
        else buttons[i]->setValue (false);
    }

    if (pattern) pattern->setEditMode (editModes[mode]);
}

// Main:
int main ()
{
    // Create a window
    Window window (720, 420, 0, URID_UNKNOWN_URID, "B.Widgets Symbols");

    // Create a Pattern 8x8
    pattern = std::unique_ptr<Pattern<>>(new Pattern<> (70, 10, 640, 400, 8, 8));
    std::array<BStyles::ColorMap, 4> patternColors = {{BStyles::reds, BStyles::yellows, BStyles::greens, BStyles::blues}};

    // Create the 8 SymbolButtons
    for (int i = 0; i < NR_EDIT_BUTTONS; ++i)
    {
        buttons[i] = std::unique_ptr<SymbolButton> (new SymbolButton (10, 10 + i * 40, 40, 30, buttonSymbols[i], true, (i == 0)));
        buttons[i]->setCallbackFunction (BEvents::Event::VALUE_CHANGED_EVENT, buttonChangedCallback);
        window.add (buttons[i].get());
    }

    // Add the pattern to the main window and run. That's all.
    window.add (pattern.get());
    window.run();
}