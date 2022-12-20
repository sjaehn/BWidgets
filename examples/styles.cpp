/* styles.cpp
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
#include <cairo/cairo.h>

#define URI "https://github.com/sjaehn/BWidgets/styles.cpp"

using namespace BWidgets;
using namespace BStyles;
using namespace BUtilities;

// Definition of a style with two substyles
Style style = Style
{
    /* Default style - don't need to be declared */
    /*
    {Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI), makeAny<Border>(noBorder)},
    {Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI), makeAny<Fill>(noFill)},
    {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(sans12pt)},
    {Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI), makeAny<ColorMap>(darks)},
    {Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI), makeAny<ColorMap>(greens)},
    {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(whites)},
    */

    /* Alternative style 1 for widgets with the URID: URI "/ua" */
    {
        Urid::urid (URI "/ua"), 
        makeAny<Style>
        ( 
            Style
            {
                {Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI), makeAny<ColorMap>(yellows)},
                {Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI), makeAny<ColorMap>(blues)},
                {
                    Urid::urid (URI "/ua/label"), 
                    makeAny<Style>
                    ( 
                        Style
                        {
                            {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(Font ("cursive", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0))},
                            {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(yellows)},
                        }
                    )
                }
            }
        )
    },

    /* Alternative style 2 for widgets with the URID: URI "/bw" */
    {
        Urid::urid (URI "/bw"), 
        makeAny<Style>
        (
            Style
            {
                {Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI), makeAny<ColorMap>(whites)},
                {Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI), makeAny<ColorMap>( ColorMap{darkdarkgrey, darkgrey, black, black})},
                {
                    Urid::urid (URI "/bw/label"), 
                    makeAny<Style>
                    (
                        Style
                        {
                            {Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI), makeAny<Font>(Font ("fantasy", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0))},
                            {Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI), makeAny<ColorMap>(whites)},
                        }
                    )
                }
            }
        )
    }
};

int main ()
{
    // Window
    Window window (300, 360, 0, BUTILITIES_URID_UNKNOWN_URID, "Styles", true);
    window.setStyle(style);

    // Widgets in default style with URID: URI "/default"
    Label defaultLabel (10, 10, 280, 20, "Default style");
    window.add (&defaultLabel);
    ValueDial defaultValueDial  (10, 30, 60, 75, 0.3, 0.0, 1.0, 0.0, 
                                 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                 ValueDial::valueToString, ValueDial::stringToValue, 
                                 Urid::urid (URI "/default"));
    window.add (&defaultValueDial);
    ValueHSlider defaultValueHSlider    (110, 50, 100, 40, 0.3, 0.0, 1.0, 0.0, 
                                         ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                         ValueHSlider::valueToString, ValueHSlider::stringToValue, 
                                         Urid::urid (URI "/default"));
    window.add (&defaultValueHSlider);
    ValueVSlider defaultValueVSlider    (210, 30, 40, 80, 0.3, 0.0, 1.0, 0.0, 
                                         ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                         ValueVSlider::valueToString, ValueVSlider::stringToValue, 
                                         Urid::urid (URI "/default"));
    window.add (&defaultValueVSlider);

    // Widgets in the alternative style 1 with URID: URI "/ua"
    Label uaLabel (10, 130, 280, 20, "Alternative style 1");
    window.add (&uaLabel);
    ValueDial uaValueDial   (10, 150, 60, 75, 0.3, 0.0, 1.0, 0.0, 
                             ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                             ValueDial::valueToString, ValueDial::stringToValue, 
                             Urid::urid (URI "/ua"));
    window.add (&uaValueDial);
    ValueHSlider uaValueHSlider (110, 170, 100, 40, 0.3, 0.0, 1.0, 0.0, 
                                 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                 ValueHSlider::valueToString, ValueHSlider::stringToValue, 
                                 Urid::urid (URI "/ua"));
    window.add (&uaValueHSlider);
    ValueVSlider uaValueVSlider (210, 150, 40, 80, 0.3, 0.0, 1.0, 0.0, 
                                 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                 ValueVSlider::valueToString, ValueVSlider::stringToValue, 
                                 Urid::urid (URI "/ua"));
    window.add (&uaValueVSlider);

    // Widgets in alternaltive style 2 with URID: URI "/bw"
    Label bwLabel (10, 250, 280, 20, "Alternative style 2");
    window.add (&bwLabel);
    ValueDial bwValueDial   (10, 270, 60, 75, 0.3, 0.0, 1.0, 0.0, 
                             ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                             ValueDial::valueToString, ValueDial::stringToValue, 
                             Urid::urid (URI "/bw"));
    window.add (&bwValueDial);
    ValueHSlider bwValueHSlider (110, 290, 100, 40, 0.3, 0.0, 1.0, 0.0, 
                                 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                 ValueHSlider::valueToString, ValueHSlider::stringToValue, 
                                 Urid::urid (URI "/bw"));
    window.add (&bwValueHSlider);
    ValueVSlider bwValueVSlider (210, 270, 40, 80, 0.3, 0.0, 1.0, 0.0, 
                                 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
                                 ValueVSlider::valueToString, ValueVSlider::stringToValue, 
                                 Urid::urid (URI "/bw"));
    window.add (&bwValueVSlider);

    window.run();
}