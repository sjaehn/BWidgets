/* themes.cpp
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
#include "../BWidgets/ValueDial.hpp"
#include "../BWidgets/ValueHSlider.hpp"
#include "../BWidgets/ValueVSlider.hpp"
#include "../BWidgets/TextButton.hpp"
#include <cairo/cairo.h>

#define URI "https://github.com/sjaehn/BWidgets/themes.cpp"

using namespace BWidgets;
using namespace BStyles;
using namespace BUtilities;
using namespace BEvents;

// Definition of th widgets
Window window (400, 160, 0, Urid::urid (URI "/window"), "Themes", true);
Label dialLabel (10, 10, 100, 20, "ValueDial");
ValueDial dial  
(
    10, 30, 60, 75, 0.3, 0.0, 1.0, 0.0, 
    ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
    ValueDial::valueToString, ValueDial::stringToValue, 
    Urid::urid (URI "/dial")
);
Label hSliderLabel (110, 10, 100, 20, "ValueHSlider");
ValueHSlider hSlider    
(
    110, 50, 100, 40, 0.3, 0.0, 1.0, 0.0, 
    ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
    ValueHSlider::valueToString, ValueHSlider::stringToValue, 
    Urid::urid (URI "/dial")
);
Label vSliderLabel (210, 10, 100, 20, "ValueHSlider");
ValueVSlider vSlider    
(
    210, 30, 40, 80, 0.3, 0.0, 1.0, 0.0, 
    ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
    ValueVSlider::valueToString, ValueVSlider::stringToValue, 
    Urid::urid (URI "/dial")
);
Label buttonLabel (310, 10, 100, 20, "TextButton");
TextButton button (310, 60, 80, 20, "Text", false, false, Urid::urid (URI "/button")); 
TextButton b1 (60, 130, 80, 20, "Theme1"); 
TextButton b2 (160, 130, 80, 20, "Theme2"); 
TextButton b3 (260, 130, 80, 20, "Theme3");

// Definition of themes
Theme theme1 = Theme
{
    {
        Urid::urid (URI "/window"),
        Style
        ({
            {Urid::urid(BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(blackFill)}
        })
    },

    {
        Urid::urid (URI "/dial"),
        Style
        ({
            {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(noBorder)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(noFill)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI), makeAny<ColorMap>(darks)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI), makeAny<ColorMap>(greens)},
            {
                Urid::urid (URI "/dial/label"), makeAny<Style>  // Nested styles are allowed too
                (
                    Style
                    {
                        {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(sans12pt)},
                        {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(whites)},
                    }
                )
            }
        })
    },

    {
        Urid::urid (URI "/button"),
        Style
        ({
            {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(whiteBorder1pt)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(Fill(darkgreen))},
            {
                Urid::urid (URI "/button/label"), makeAny<Style>  // Nested styles are allowed too
                (
                    Style
                    {
                        {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(sans12pt)},
                        {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(whites)},
                    }
                )
            }
        })
    }
};

Theme theme2 = Theme
{
    {
        Urid::urid (URI "/window"),
        Style
        ({
            {Urid::urid(BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(Fill(Color(0.333, 0.167, 0.0, 1.0)))}
        })
    },

    {
        Urid::urid (URI "/dial"),
        Style
        ({
            {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(noBorder)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(noFill)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI), makeAny<ColorMap>(yellows)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI), makeAny<ColorMap>(blues)},
            {
                Urid::urid (URI "/dial/label"), makeAny<Style>  // Nested styles are allowed too
                (
                    Style
                    {
                        {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(Font ("cursive", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, Font::TEXT_ALIGN_CENTER, Font::TEXT_VALIGN_MIDDLE))},
                        {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(yellows)},
                    }
                )
            }
        })
    },

    {
        Urid::urid (URI "/button"),
        Style
        ({
            {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(whiteBorder1pt)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(blueFill)},
            {
                Urid::urid (URI "/button/label"), makeAny<Style>  // Nested styles are allowed too
                (
                    Style
                    {
                        {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(Font ("cursive", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, Font::TEXT_ALIGN_CENTER, Font::TEXT_VALIGN_MIDDLE))},
                        {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(yellows)},
                    }
                )
            }
        })
    }
};

Theme theme3 = Theme
{
    {
        Urid::urid (URI "/window"),
        Style
        ({
            {Urid::urid(BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(Fill(Color(0.167, 0.167, 0.167, 1.0)))}
        })
    },

    {
        Urid::urid (URI "/dial"),
        Style
        ({
            {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(noBorder)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(noFill)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI), makeAny<ColorMap>(whites)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI), makeAny<ColorMap>(ColorMap{darkdarkgrey, darkgrey, black, black})},
            {
                Urid::urid (URI "/dial/label"), makeAny<Style>  // Nested styles are allowed too
                (
                    Style
                    {
                        {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(Font ("fantasy", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, Font::TEXT_ALIGN_CENTER, Font::TEXT_VALIGN_MIDDLE))},
                        {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(whites)},
                    }
                )
            }
        })
    },

    {
        Urid::urid (URI "/button"),
        Style
        ({
            {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(whiteBorder1pt)},
            {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(Fill(darkdarkgrey))},
            {
                Urid::urid (URI "/button/label"), makeAny<Style>  // Nested styles are allowed too
                (
                    Style
                    {
                        {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(Font ("fantasy", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, Font::TEXT_ALIGN_CENTER, Font::TEXT_VALIGN_MIDDLE))},
                        {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(whites)},
                    }
                )
            }
        })
    }
};

// Callback function for button events
void valueChangedCallback (BEvents::Event* event)
{
    ValueChangeTypedEvent<bool>* e = dynamic_cast<ValueChangeTypedEvent<bool>*>(event);

    if (e && e->getValue())
    {
        if (e->getWidget() == &b1) window.setTheme(theme1);            
        else if (e->getWidget() == &b2) window.setTheme(theme2);
        else if (e->getWidget() == &b3) window.setTheme(theme3);                               
    }
   
}

int main ()
{
    window.setTheme (theme3);

    // Pack all widgets into window
    window.add (&dialLabel);
    window.add (&dial);
    window.add (&hSliderLabel);
    window.add (&hSlider);
    window.add (&vSliderLabel);
    window.add (&vSlider);
    window.add (&buttonLabel);
    window.add (&button);
    window.add (&b1);
    window.add (&b2);
    window.add (&b3);

    // Set callbacks for the buttons 
    b1.setCallbackFunction (Event::VALUE_CHANGED_EVENT, valueChangedCallback); 
    b2.setCallbackFunction (Event::VALUE_CHANGED_EVENT, valueChangedCallback); 
    b3.setCallbackFunction (Event::VALUE_CHANGED_EVENT, valueChangedCallback); 

    window.run();
}