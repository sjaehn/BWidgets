/* Text.hpp
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

#ifndef BWIDGETS_TEXT_HPP_
#define BWIDGETS_TEXT_HPP_

#include "Label.hpp"

namespace BWidgets
{

/**
 *  @brief  Multi-line %text output widget.
 *
 *  The %Text widget inserts line breaks in the following order of priority:
 *  (i) on "\n" or
 *  (ii) on spaces when text length exceed the widget width or
 *  (iii) on any position when text length exceed the widget width.
 */
class Text : public Label
{
public:

	/**
	 * @brief Construct an empty %Text object.
	 */
	Text ();

	/**
	 *  @brief  Constructs a %Text object at the origin with optimized extends.
	 *  @param text  %Text string.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Text title (default = "").
	 */
	Text (const std::string& text, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a %Text object at the origin.
	 *  @param x  %Text X origin coordinate.
	 *  @param y  %Text Y origin coordinate.
	 *  @param width  %Text width.
	 *  @param height  %Text height.
	 *  @param text  %Text string.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Text title (default = "").
	 */
	Text (const double x, const double y, const double width, const double height, const std::string& text, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Text. 
	 *  @return  Pointer to the new %Text.
	 *
	 *  Creates a clone of this %Text by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Text. 
	 *  @param that  Other %Text.
	 *
	 *  Copies all properties from another %Text. But NOT its linkage.
	 */
	void copy (const Text* that);

	/**
     *  @brief  Optimizes the object surface extends.
     *
     *  Creates a new RGBA surface with the new optimized extends, copies the
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the object surface extends.
	 *  @param width  New object width.
	 *  @param height  New object height.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the object surface extends.
	 *  @param extends  New object extends.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const BUtilities::Point extends) override;

	/**
	 * Gets a block (a vector) of text lines that fit into the widget output.
	 * If the widget is not resizable: the text is clipped, when lines exceed
	 * the widget height. If the widget is resizable, the whole text will be
	 * returned as a block of lines.
	 * @return	Vector of text lines
	 */
	std::vector<std::string> getTextBlock ();

	/**
	 * Gets the height of a given text block as calculated using Cairo.
	 * @param textBlock Vector of text lines
	 * @return 			Text block height.
	 */
	double getTextBlockHeight (std::vector<std::string> textBlock);


protected:

	/**
     *  @brief  Unclipped draw to the surface (if is visualizable).
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw to the surface (if is visualizable).
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param area  Clipped area. 
     */
	virtual void draw (const BUtilities::RectArea& area) override;
};

inline Text::Text () : Text (0.0, 0.0, 0.0, 0.0, "", URID_UNKNOWN_URID, "") 
{

}

inline Text::Text (const std::string& text, uint32_t urid, std::string title) :
	Text (0.0, 0.0, BWIDGETS_DEFAULT_WIDTH, BWIDGETS_DEFAULT_HEIGHT, text, urid, title) 
{
	resize();
}

inline Text::Text (const double x, const double y, const double width, const double height, const std::string& text, uint32_t urid, std::string title) :
		Label (x, y, width, height, text, urid, title) 
{

}

inline Widget* Text::clone () const 
{
	Widget* f = new Text ();
	f->copy (this);
	return f;
}

inline void Text::copy (const Text* that)
{
	Label::copy (that);
}

inline void Text::resize () 
{
	const double ySize = getTextBlockHeight (getTextBlock()) + 2 * getYOffset();
	resize (getExtends().x, ySize);
}

inline void Text::resize (const double width, const double height) 
{
	resize (BUtilities::Point (width, height));
}

inline void Text::resize (const BUtilities::Point extends)
{
	Widget::resize (extends);
}

inline std::vector<std::string> Text::getTextBlock ()
{
	std::vector<std::string> textblock;
	const double w = getEffectiveWidth ();
	//const double h = getEffectiveHeight ();
	cairo_t* cr = cairo_create (surface_);
	cairo_text_decorations decorations;
	const BStyles::Font font = getFont();
	strncpy (decorations.family, font.family.c_str (), 63);
	decorations.size = font.size;
	decorations.slant = font.slant;
	decorations.weight = font.weight;

	char* textCString = (char*) malloc (strlen (text_.c_str ()) + 1);
	if (textCString)
	{
		strcpy (textCString, text_.c_str ());

		for (double y = 0; strlen (textCString) > 0; /* empty */)
		{
			char* outputtext = cairo_create_text_fitted (cr, w, decorations, textCString);
			if (outputtext[0] == '\0') break;
			cairo_text_extents_t ext = font.getCairoTextExtents(cr, outputtext);
			textblock.push_back (std::string (outputtext));
			y += (ext.height * font.lineSpacing);
			cairo_text_destroy (outputtext);
		}

		free (textCString);
	}

	cairo_destroy (cr);
	return textblock;
}

inline double Text::getTextBlockHeight (std::vector<std::string> textBlock)
{
	double blockheight = 0.0;
	cairo_t* cr = cairo_create (surface_);
	const BStyles::Font font = getFont();

	for (std::string textline : textBlock)
	{
		//cairo_text_extents_t ext = textFont.getTextExtents(cr, textline.c_str ());
		blockheight += font.size * font.lineSpacing;
	}

	cairo_destroy (cr);
	return blockheight;
}

inline void Text::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Text::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea (x0, y0, width, height));
}

inline void Text::draw (const BUtilities::RectArea& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	cairo_t* cr = cairo_create (surface_);

	if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
	{
		// Limit cairo-drawing area
		cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
		cairo_clip (cr);

		const double xoff = getXOffset ();
		const double yoff = getYOffset ();
		const double w = getEffectiveWidth ();
		const double h = getEffectiveHeight ();
		const BStyles::Font font = getFont();

		// textString -> textblock
		const std::vector<std::string> textblock = getTextBlock ();
		const double blockheight = getTextBlockHeight (textblock);

		// Calculate vertical alignment of the textblock
		double y0 = 0;
		switch (font.valign)
		{
			case BStyles::Font::TEXT_VALIGN_TOP:	y0 = 0;
													break;

			case BStyles::Font::TEXT_VALIGN_MIDDLE:	y0 = h / 2 - blockheight / 2;
													break;

			case BStyles::Font::TEXT_VALIGN_BOTTOM:	y0 = h - blockheight;
													break;

			default:								y0 = 0;
		}


		// Output of textblock
		const BStyles::Color lc = getTxColors () [getStatus()];
		cairo_set_source_rgba (cr, CAIRO_RGBA (lc));
		cairo_select_font_face (cr, font.family.c_str (), font.slant, font.weight);
		cairo_set_font_size (cr, font.size);
		double ycount = 0.0;

		for (std::string textline : textblock)
		{
			const cairo_text_extents_t ext = font.getCairoTextExtents (cr, textline);

			double x0;
			switch (font.align)
			{
				case BStyles::Font::TEXT_ALIGN_LEFT:	x0 = - ext.x_bearing;
														break;

				case BStyles::Font::TEXT_ALIGN_CENTER:	x0 = w / 2 - ext.width / 2 - ext.x_bearing;
														break;

				case BStyles::Font::TEXT_ALIGN_RIGHT:	x0 = w - ext.width - ext.x_bearing;
														break;
														
				default:								x0 = 0;
			}

			cairo_move_to (cr, xoff + x0, yoff + y0 + ycount - ext.y_bearing);
			cairo_show_text (cr, textline.c_str ());
			ycount += font.size * font.lineSpacing;
		}
	}

	cairo_destroy (cr);
}

}

#endif /* BWIDGETS_TEXT_HPP_ */
