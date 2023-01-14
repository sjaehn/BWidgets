/* HSwitch.hpp
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

#ifndef BWIDGETS_HSWITCH_HPP_
#define BWIDGETS_HSWITCH_HPP_

#ifndef BWIDGETS_DEFAULT_DRAWHBAR_PATH
#define BWIDGETS_DEFAULT_DRAWHBAR_PATH "Draws/drawHBar.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWKNOB_PATH
#define BWIDGETS_DEFAULT_DRAWKNOB_PATH "Draws/drawKnob.hpp"
#endif

#include "Button.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Scrollable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include BWIDGETS_DEFAULT_DRAWHBAR_PATH
#include BWIDGETS_DEFAULT_DRAWKNOB_PATH
#include "Widget.hpp"

#ifndef BWIDGETS_DEFAULT_HSWITCH_WIDTH
#define BWIDGETS_DEFAULT_HSWITCH_WIDTH 40.0
#endif

#ifndef BWIDGETS_DEFAULT_HSWITCH_HEIGHT
#define BWIDGETS_DEFAULT_HSWITCH_HEIGHT 20.0
#endif

namespace BWidgets
{

/**
 *  @brief  %HSwitch Button widget.
 *
 *  %HSwitch is a Button Widget. It displays its status (represented by its 
 *  bool value) as a horizontal switch. It supports user interaction via 
 *  Clickable, Draggable, and Scrollable. Its appearance is defined by the 
 *  BgColors parameter (static elements, false) and by the FgColors parameter
 *  (active elements, true).
 */
class HSwitch : public Button, public Draggable, public Scrollable
{
public:

	/**
	 *  @brief  Constructs a default %HSwitch object.
	 */
	HSwitch ();

	/**
	 *  @brief  Constructs a default %HSwitch object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	HSwitch (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %HSwitch with default size.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HSwitch	(bool toggleable, bool clicked = false, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HSwitch.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HSwitch	(const double x, const double y, const double width, const double height, 
			 bool toggleable = true, bool clicked = false,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %HSwitch. 
	 *  @return  Pointer to the new %HSwitch.
	 *
	 *  Creates a clone of this %HSwitch by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %HSwitch. 
	 *  @param that  Other %HSwitch.
	 *
	 *  Copies all properties from another %HSwitch. But NOT its linkage.
	 */
	void copy (const HSwitch* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
     *  @brief  Method called when pointer button clicked (pressed and 
     *  released).
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button cklicked. Inverts the %Button value (if 
	 *  @c isToggleable() and the pointer hasn't been dragged) and calls its
	 *  static callback function.
     */
    virtual void onButtonClicked (BEvents::Event* event) override;

	/**
     *  @brief  Method called upon pointer drag.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a pointer drag. Changes the %Button value and calls its static callback
	 *  function.
     */
    virtual void onPointerDragged (BEvents::Event* event) override;
	
	/**
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. Sets or unsets the %Button value and calls its
	 *  static callback function.
     */
    virtual void onWheelScrolled (BEvents::Event* event) override;

protected:
	/**
     *  @brief  Unclipped draw a %HSwitch to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %HSwitch to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %HSwitch to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline HSwitch::HSwitch () :
	HSwitch (0.0, 0.0, BWIDGETS_DEFAULT_HSWITCH_WIDTH, BWIDGETS_DEFAULT_HSWITCH_HEIGHT, true, false, BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline HSwitch::HSwitch (const uint32_t urid, const std::string& title) : 
	HSwitch (0.0, 0.0, BWIDGETS_DEFAULT_HSWITCH_WIDTH, BWIDGETS_DEFAULT_HSWITCH_HEIGHT, true, false, urid, title) 
{

}

inline HSwitch::HSwitch (bool toggleable, bool clicked, uint32_t urid, std::string title) : 
	HSwitch (0.0, 0.0, BWIDGETS_DEFAULT_HSWITCH_WIDTH, BWIDGETS_DEFAULT_HSWITCH_HEIGHT, toggleable, clicked, urid, title) 
{

}

inline HSwitch::HSwitch (const double  x, const double y, const double width, const double height, bool toggleable, bool clicked, uint32_t urid, std::string title) :
		Button (x, y, width, height, toggleable, clicked, urid, title),
		Draggable(),
		Scrollable()
{
	setBackground (BStyles::noFill);
	setBorder (BStyles::noBorder);
}

inline Widget* HSwitch::clone () const 
{
	Widget* f = new HSwitch (urid_, title_);
	f->copy (this);
	return f;
}

inline void HSwitch::copy (const HSwitch* that)
{
	Scrollable::operator= (*that);
	Draggable::operator= (*that);
	Widget::copy (that);
}

inline void HSwitch::update()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + BUtilities::Dictionary::get ((getValue() ? "on" : "off")));
		f->resize();
	}
	Widget::update();	// Bypass Button::update()
}

inline void HSwitch::onButtonClicked (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (isToggleable() && (pev->getPosition() == pev->getOrigin())) setValue (!getValue());
	Clickable::onButtonClicked (event);
}

inline void HSwitch::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	setValue (pev->getPosition().x > 0.5 * getWidth());
	Draggable::onPointerDragged (event);
}

inline void HSwitch::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (wev->getDelta().y != 0) setValue (wev->getDelta().y < 0);
	Scrollable::onWheelScrolled (event);
}

inline void HSwitch::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void HSwitch::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void HSwitch::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	const double x0 = getXOffset();
	const double y0 = getYOffset();
	const double heff = getEffectiveHeight ();
	const double weff = getEffectiveWidth ();

	// Draw only if minimum requirements satisfied
	if ((heff >= 1) && (weff >= 1))
	{
		cairo_t* cr = cairo_create (cairoSurface());

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			// Calculate aspect ratios first
			const double radius = 0.5 * heff - 1.0;
			const double max = (getValue() ? 1.0 : 0.0);
			const double xc = x0 + 1.0 + radius + max * (weff - 1.0 - 2.0 * radius);
			const double yc = y0 + 0.5 * heff + 1.0;

			const BStyles::Color fgColor = getFgColors()[getStatus()];
			const BStyles::Color bgColor = getBgColors()[getStatus()];
			drawHBar(cr, x0, y0, weff, heff, 0.0, max, fgColor, bgColor);
			drawKnob(cr, xc, yc, radius, 1.0, bgColor, bgColor);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_HSWITCH_HPP_ */
