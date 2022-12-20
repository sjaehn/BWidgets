/* Font.hpp
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

#ifndef BSTYLES_FONT_HPP_
#define BSTYLES_FONT_HPP_

#include <string>
#include <cairo/cairo.h>

namespace BStyles
{

/**
 *  @brief A %Font class, compatible to Cairo.
 */
struct Font
{
    enum  TextAlign
    {
        TEXT_ALIGN_LEFT,
        TEXT_ALIGN_CENTER,
        TEXT_ALIGN_RIGHT,
    };

    enum TextVAlign
    {
        TEXT_VALIGN_TOP,
        TEXT_VALIGN_MIDDLE,
        TEXT_VALIGN_BOTTOM
    };

	std::string family;
	cairo_font_slant_t slant;
	cairo_font_weight_t weight;
	double size;
	TextAlign align;
	TextVAlign valign;
	double lineSpacing;

    /**
     *  @brief  Creates a default %Font (12 pt sans).
     */
    Font () : Font ("Sans") {}

    /**
     *  @brief  Creates a %Font from the passed parameters.
     *  @param family  %Font @a family.
     *  @param slant  Optional, Cairo %Font @a slant.
     *  @param weight  Optional, Cairo %Font @a weight.
     *  @param size  Optional, %Font size in pts.
     *  @param align  Optional, horizontal text alignment.
     *  @param valign  Optional, vertical text alignment.
     *  @param lineSpacing  Optional, line spacing factor.
     */
	Font  (const std::string& family, 
           cairo_font_slant_t slant = CAIRO_FONT_SLANT_NORMAL, 
           cairo_font_weight_t weight = CAIRO_FONT_WEIGHT_NORMAL, 
           double size = 12.0,
           TextAlign align = TEXT_ALIGN_LEFT, 
           TextVAlign valign = TEXT_VALIGN_TOP, 
           double lineSpacing = 1.25) :

        family (family), slant (slant), weight (weight), size (size), align (align), valign (valign), lineSpacing(lineSpacing) {}

    /**
	 *  @brief Calculates the output dimensions of a text by passing to Cairo.
	 *  @param cr  Pointer to a Cairo context.
	 *  @param text  Text to calculate output dimensions for.
	 *  @return  Output dimensions as Cairo text extents.
	 */
	cairo_text_extents_t getCairoTextExtents (cairo_t* cr, const std::string& text) const;

    bool operator== (const Font& that) const 
    {
        return  (family == that.family) && 
                (slant == that.slant) && 
                (weight == that.weight) && 
                (size == that.size) && 
                (align == that.align) && 
                (valign == that.valign) &&
                (lineSpacing == that.lineSpacing);
    }

	bool operator!= (const Font& that) const {return !operator== (that);}
};

const Font sans12pt = Font ("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0);

inline cairo_text_extents_t Font::getCairoTextExtents (cairo_t* cr, const std::string& text) const
{
	if (cr && (! cairo_status (cr)))
	{
		cairo_save (cr);

		cairo_text_extents_t ext;
		cairo_select_font_face (cr, family.c_str (), slant, weight);
		cairo_set_font_size (cr, size);
		cairo_text_extents (cr, text.c_str(), &ext);

		cairo_restore (cr);
		return ext;
	}
	else
	{
		return {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	}
}

}

#endif /* BSTYLES_BORDER_HPP_ */
