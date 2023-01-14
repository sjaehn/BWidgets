/* CheckBox.hpp
 * Copyright (C) 2018 - 2023  Sven Jähnichen
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

#ifndef BWIDGETS_CHECKBOX_HPP_
#define BWIDGETS_CHECKBOX_HPP_

#include "Button.hpp"

#ifndef BWIDGETS_DEFAULT_CHECKBOX_WIDTH
#define BWIDGETS_DEFAULT_CHECKBOX_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_CHECKBOX_HEIGHT
#define BWIDGETS_DEFAULT_CHECKBOX_HEIGHT BWIDGETS_DEFAULT_CHECKBOX_WIDTH
#endif

namespace BWidgets
{

/**
 *  @brief  %CheckBox Button widget.
 *
 *  %CheckBox is a Button Widget. Its appearance is defined by the BgColors
 *  parameter (frame) and by the FgColors parameter (active state, symbol).
 */
class CheckBox : public Button
{
protected:

public:

	/**
	 *  @brief  Constructs a default %CheckBox object.
	 * 
	 */
	CheckBox ();

	/**
	 *  @brief  Constructs a default %CheckBox object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	CheckBox (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %CheckBox with default size.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	CheckBox	(bool toggleable, bool clicked = false, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %CheckBox.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	CheckBox	(const double x, const double y, const double width, const double height, 
			 	 bool toggleable = false, bool clicked = false,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %CheckBox. 
	 *  @return  Pointer to the new %CheckBox.
	 *
	 *  Creates a clone of this %CheckBox by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %CheckBox. 
	 *  @param that  Other %CheckBox.
	 *
	 *  Copies all properties from another %CheckBox. But NOT its linkage.
	 */
	void copy (const CheckBox* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:
	/**
     *  @brief  Unclipped draw a %CheckBox to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %CheckBox to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %CheckBox to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline CheckBox::CheckBox () :
	CheckBox (0.0, 0.0, BWIDGETS_DEFAULT_CHECKBOX_WIDTH, BWIDGETS_DEFAULT_CHECKBOX_HEIGHT, false, false, BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline CheckBox::CheckBox (const uint32_t urid, const std::string& title) : 
	CheckBox (0.0, 0.0, BWIDGETS_DEFAULT_CHECKBOX_WIDTH, BWIDGETS_DEFAULT_CHECKBOX_HEIGHT, false, false, urid, title) 
{

}

inline CheckBox::CheckBox (bool toggleable, bool clicked, uint32_t urid, std::string title) : 
	CheckBox (0.0, 0.0, BWIDGETS_DEFAULT_CHECKBOX_WIDTH, BWIDGETS_DEFAULT_CHECKBOX_HEIGHT, toggleable, clicked, urid, title) 
{

}

inline CheckBox::CheckBox (const double  x, const double y, const double width, const double height, bool toggleable, bool clicked, uint32_t urid, std::string title) :
		Button (x, y, width, height, toggleable, clicked, urid, title)
{
	setBackground (BStyles::noFill);
	setBorder (BStyles::noBorder);
}

inline Widget* CheckBox::clone () const 
{
	Widget* f = new CheckBox (urid_, title_);
	f->copy (this);
	return f;
}

inline void CheckBox::copy (const CheckBox* that)
{
	Widget::copy (that);
}

inline void CheckBox::update()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + BUtilities::Dictionary::get ((getValue() ? "on" : "off")));
		f->resize();
	}
	Widget::update();	// Bypass Button::update()
}

inline void CheckBox::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void CheckBox::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void CheckBox::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

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
		cairo_t* cr = cairo_create (cairoSurface());

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
			cairo_rectangle (cr, xc - 0.5 * size, yc - 0.5 * size, size, size);
			cairo_stroke (cr);

			// Symbol
			if (getValue())
			{
				const BStyles::Color fg = getFgColors() [getStatus()];
				cairo_set_line_width (cr, 2.0);
				cairo_set_source_rgba (cr, CAIRO_RGBA (fg));
				cairo_move_to (cr, xc - 0.3 * size, yc);
				cairo_line_to (cr, xc - 0.1 * size, yc + 0.3 * size);
				cairo_line_to (cr, xc + 0.3 * size, yc - 0.3 * size);
				cairo_stroke (cr);
			}
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_CHECKBOX_HPP_ */
