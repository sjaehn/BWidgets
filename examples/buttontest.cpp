/* HelloWorld.cpp
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
#include "../BWidgets/TextButton.hpp"

using namespace BWidgets;
using namespace BStyles;
using namespace BEvents;


void valueChangedCallback (BEvents::Event* event)
{
    ValueChangeTypedEvent<bool>* e = dynamic_cast<ValueChangeTypedEvent<bool>*>(event);
    if (e->getValue()) e->getWidget()->getMainWindow()->setBackground (redFill);
    else e->getWidget()->getMainWindow()->setBackground (blackFill);
}

int main ()
{
    Window window;  // Creates an empty window with default size

    Label label ("Button pressed"); // Creates a label with the text
                                    // "Button pressed" and optimized size.

    TextButton button (70, 40, 60, 20, "Press"); // Creates a text Button
                                                 // at position 70, 40 with
                                                 // the size 60 x 20 and
                                                 // the text "Press".

    window.add (&label);     // Adds the label to the window.
    window.add (&button);    // Adds the button to the window. 

    label.setTxColors (ColorMap ({black})); // Black label on ...
    window.setBackground (blackFill);       // black window background
    
    label.moveTo (label.center(), label.bottom ()); // Move label to bottom
                                                    // center.

    button.setCallbackFunction (Event::VALUE_CHANGED_EVENT, valueChangedCallback);

    window.run();
}