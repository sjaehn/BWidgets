/* Label.hpp
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

#ifndef BWIDGETS_LABEL_HPP_
#define BWIDGETS_LABEL_HPP_

#include <string>



#include "Widget.hpp"

#ifndef BWIDGETS_DEFAULT_LABEL_WIDTH
#define BWIDGETS_DEFAULT_LABEL_WIDTH 80
#endif

#ifndef BWIDGETS_DEFAULT_LABEL_HEIGHT
#define BWIDGETS_DEFAULT_LABEL_HEIGHT 20
#endif

#ifndef BWIDGETS_DEFAULT_LABEL_ALIGN
#define BWIDGETS_DEFAULT_LABEL_ALIGN BStyles::Font::TEXT_ALIGN_CENTER
#endif

#ifndef BWIDGETS_DEFAULT_LABEL_VALIGN
#define BWIDGETS_DEFAULT_LABEL_VALIGN BStyles::Font::TEXT_VALIGN_MIDDLE
#endif

namespace BWidgets
{

/**
 *  @brief  Simple single line text widget.
 *
 *  Label widgets can be decorated by setting a font and a text color in 
 *  addtion to the StyleProperty settings supported by Widget. 
 */
class Label : public Widget
{
protected:
	std::string text_;
public:
	/**
	 *  @brief  Constructs an empty default %Label object.
	 */
	Label ();

	/**
	 *  @brief  Constructs an empty default %Label object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Label (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Constructs a %Label object at the origin with optimized extends.
	 *  @param text  Text.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Label title (default = "").
	 */
	Label (const std::string& text, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a %Label object at the origin.
	 *  @param x  %Label X origin coordinate.
	 *  @param y  %Label Y origin coordinate.
	 *  @param width  %Label width.
	 *  @param height  %Label height.
	 *  @param text  Text.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Label title (default = "").
	 */
	Label (const double x, const double y, const double width, const double height, const std::string& text, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Label. 
	 *  @return  Pointer to the new %Label.
	 *
	 *  Creates a clone of this %Label by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Label. 
	 *  @param that  Other %Label.
	 *
	 *  Copies all properties from another %Label. But NOT its linkage.
	 */
	void copy (const Label* that);

	/**
	 *  @brief  Sets the %Label text.
	 *  @param text  %Label text.
	 */
	virtual void setText (const std::string& text);

	/**
	 *  @brief  Gets the %Label text.
	 *  @return   %Label text.
	 */
	virtual std::string getText () const;

	/**
	 *  @brief  Calculates the width of a text.
	 *  @param text   Text string.
	 *  @param return  Text extends.
	 */
	BUtilities::Point<> getTextExtends (std::string& text) const;

	/**
     *  @brief  Optimizes the %Label widget extends.
     *
     *  Resizes the %Label widget to the size of the text extends and all 
	 *  direct children.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the object.
	 *  @param width  New object width.
	 *  @param height  New object height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the object.
	 *  @param extends  New object extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

protected:
	/**
     *  @brief  Unclipped draw to the surface (if is visualizable).
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
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
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline Label::Label () : 
	Label (0.0, 0.0, BWIDGETS_DEFAULT_LABEL_WIDTH, BWIDGETS_DEFAULT_LABEL_HEIGHT, "", URID_UNKNOWN_URID, "") 
{

}

inline Label::Label (const uint32_t urid, const std::string& title) :
	Label (0.0, 0.0, BWIDGETS_DEFAULT_LABEL_WIDTH, BWIDGETS_DEFAULT_LABEL_HEIGHT, "", urid, title)
{
	
}

inline Label::Label (const std::string& text, uint32_t urid, std::string title) :
	Label (0.0, 0.0, BWIDGETS_DEFAULT_LABEL_WIDTH, BWIDGETS_DEFAULT_LABEL_HEIGHT, text, urid, title)
{
	Label::resize();
}

inline Label::Label (const double x, const double y, const double width, const double height, const std::string& text, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	text_ (text)
{
	
}

inline Widget* Label::clone () const 
{
	Widget* f = new Label (urid_, title_);
	f->copy (this);
	return f;
}

inline void Label::copy (const Label* that)
{
	text_ = that->text_;
    Widget::copy (that);
}

inline void Label::setText (const std::string& text)
{
	if (text != text_)
	{
		text_ = text;
		update ();
	}
}

inline std::string Label::getText () const 
{
	return text_;
}

inline BUtilities::Point<> Label::getTextExtends (std::string& text) const
{
	cairo_t* cr = cairo_create (surface_);
	cairo_text_extents_t ext = getFont().getCairoTextExtents(cr, text.c_str ());
	cairo_destroy (cr);
	return BUtilities::Point<> (ext.width, ext.height);
}

inline void Label::resize ()
{
	// Get label text size
	cairo_t* cr = cairo_create (surface_);
	BStyles::Font font = getFont();
	cairo_text_extents_t ext = font.getCairoTextExtents(cr, text_.c_str ());
	double w = ext.width;
	double h = (ext.height > font.size ? ext.height : font.size);
	BUtilities::Point<> contExt = BUtilities::Point<> (w + 2 * getXOffset () + 2, h + 2 * getYOffset () + 2);
	cairo_destroy (cr);

	// Or use embedded widgets size, if bigger
	for (Linkable* l : children_)
	{
		Widget* w = dynamic_cast<Widget*>(l);
		if (!w) continue;
		if (w->getPosition ().x + w->getWidth () > contExt.x) contExt.x = w->getPosition ().x + w->getWidth();
		if (w->getPosition ().y + w->getHeight () > contExt.y) contExt.y = w->getPosition ().y + w->getHeight();
	}

	resize (contExt);
}

inline void Label::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void Label::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void Label::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Label::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void Label::draw (const BUtilities::Area<>& area)
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

		double xoff = getXOffset ();
		double yoff = getYOffset ();
		double w = getEffectiveWidth ();
		double h = getEffectiveHeight ();
		BStyles::Font font = getFont();

		cairo_text_extents_t ext = font.getCairoTextExtents(cr, text_);
		cairo_select_font_face (cr, font.family.c_str (), font.slant, font.weight);
		cairo_set_font_size (cr, font.size);

		double x0, y0;

		switch (font.align)
		{
			case BStyles::Font::TEXT_ALIGN_LEFT:	x0 = 0;
													break;

			case BStyles::Font::TEXT_ALIGN_CENTER:	x0 = w / 2 - ext.width / 2;
													break;

			case BStyles::Font::TEXT_ALIGN_RIGHT:	x0 = w - ext.width;
													break;
													
			default:								x0 = 0;
		}

		switch (font.valign)
		{
			case BStyles::Font::TEXT_VALIGN_TOP:		y0 = - ext.y_bearing;
														break;

			case BStyles::Font::TEXT_VALIGN_MIDDLE:		y0 = h / 2 - ext.height / 2 - ext.y_bearing;
														break;

			case BStyles::Font::TEXT_VALIGN_BOTTOM:		y0 = h - ext.height - ext.y_bearing;
														break;

			default:									y0 = 0;
		}
			BStyles::Color color = getTxColors()[getStatus()];
			cairo_set_source_rgba (cr, CAIRO_RGBA (color));
			cairo_move_to (cr, xoff + x0, yoff + y0);
			cairo_show_text (cr, text_.c_str ());
	}

	cairo_destroy (cr);
}

}

#endif /* BWIDGETS_LABEL_HPP_ */
