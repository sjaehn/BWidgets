/* RadioButton.hpp
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

#ifndef BWIDGETS_RADIOBUTTON_HPP_
#define BWIDGETS_RADIOBUTTON_HPP_

#include "Button.hpp"
#include <cairo/cairo.h>
#include <cmath>

#ifndef BWIDGETS_DEFAULT_RADIOBUTTON_WIDTH
#define BWIDGETS_DEFAULT_RADIOBUTTON_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_RADIOBUTTON_HEIGHT
#define BWIDGETS_DEFAULT_RADIOBUTTON_HEIGHT BWIDGETS_DEFAULT_RADIOBUTTON_WIDTH
#endif

namespace BWidgets
{

/**
 *  @brief  %RadioButton Button widget.
 *
 *  %RadioButton is a Button Widget. Its appearance is defined by the BgColors
 *  parameter (frame) and by the FgColors parameter (active state, fill).
 */
class RadioButton : public Button
{
protected:

public:

	/**
	 *  @brief  Constructs a default %RadioButton object.
	 */
	RadioButton ();

	/**
	 *  @brief  Constructs a default %RadioButton object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	RadioButton (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %RadioButton with default size.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	RadioButton	(bool toggleable, bool clicked = false, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %RadioButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	RadioButton	(const double x, const double y, const double width, const double height, 
			 	 bool toggleable = false, bool clicked = false,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %RadioButton. 
	 *  @return  Pointer to the new %RadioButton.
	 *
	 *  Creates a clone of this %RadioButton by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %RadioButton. 
	 *  @param that  Other %RadioButton.
	 *
	 *  Copies all properties from another %RadioButton. But NOT its linkage.
	 */
	void copy (const RadioButton* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:
	/**
     *  @brief  Unclipped draw a %RadioButton to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %RadioButton to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %RadioButton to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline RadioButton::RadioButton () :
	RadioButton (0.0, 0.0, BWIDGETS_DEFAULT_RADIOBUTTON_WIDTH, BWIDGETS_DEFAULT_RADIOBUTTON_HEIGHT, false, false, URID_UNKNOWN_URID, "")
{

}

inline RadioButton::RadioButton (const uint32_t urid, const std::string& title) : 
	RadioButton (0.0, 0.0, BWIDGETS_DEFAULT_RADIOBUTTON_WIDTH, BWIDGETS_DEFAULT_RADIOBUTTON_HEIGHT, false, false, urid, title) 
{

}

inline RadioButton::RadioButton (bool toggleable, bool clicked, uint32_t urid, std::string title) : 
	RadioButton (0.0, 0.0, BWIDGETS_DEFAULT_RADIOBUTTON_WIDTH, BWIDGETS_DEFAULT_RADIOBUTTON_HEIGHT, toggleable, clicked, urid, title) 
{

}

inline RadioButton::RadioButton (const double  x, const double y, const double width, const double height, bool toggleable, bool clicked, uint32_t urid, std::string title) :
		Button (x, y, width, height, toggleable, clicked, urid, title)
{
	setBackground (BStyles::noFill);
	setBorder (BStyles::noBorder);
}

inline Widget* RadioButton::clone () const 
{
	Widget* f = new RadioButton (urid_, title_);
	f->copy (this);
	return f;
}

inline void RadioButton::copy (const RadioButton* that)
{
	Widget::copy (that);
}

inline void RadioButton::update()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + BUtilities::Dictionary::get ((getValue() ? "on" : "off")));
		f->resize();
	}
	Widget::update();	// Bypass Button::update()
}

inline void RadioButton::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void RadioButton::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void RadioButton::draw (const BUtilities::Area<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	const double x0 = getXOffset();
	const double y0 = getYOffset();
	const double heff = getEffectiveHeight ();
	const double weff = getEffectiveWidth ();

	// Draw knob
	// only if minimum requirements satisfied
	if ((heff >= 1) && (weff >= 1))
	{
		cairo_t* cr = cairo_create (surface_);

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			// Calculate aspect ratios first
			const double size = (heff < weff ? heff : weff) - 1;
			const double xc = x0 + 0.5 * weff;
			const double yc = y0 + 0.5 * heff;

			// Frame
			const BStyles::Color bg = getBgColors() [getStatus()];
			cairo_set_line_width (cr, 2.0);
			cairo_set_source_rgba (cr, CAIRO_RGBA (bg));
			cairo_arc(cr, xc, yc, 0.5 * size, 0, 2.0 * M_PI);
			cairo_stroke (cr);

			// Fill
			if (getValue())
			{
				const BStyles::Color fg = getFgColors() [getStatus()];
				cairo_set_line_width (cr, 0.0);
				cairo_set_source_rgba (cr, CAIRO_RGBA (fg));
				cairo_arc(cr, xc, yc, 0.25 * size, 0, 2.0 * M_PI);
				cairo_fill (cr);
			}
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_RADIOBUTTON_HPP_ */
