/* VSwitch.hpp
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

#ifndef BWIDGETS_VSWITCH_HPP_
#define BWIDGETS_VSWITCH_HPP_

#include "Button.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Scrollable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "Draws/drawVBar.hpp"
#include "Draws/drawKnob.hpp"
#include "Widget.hpp"

#ifndef BWIDGETS_DEFAULT_VSWITCH_WIDTH
#define BWIDGETS_DEFAULT_VSWITCH_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_VSWITCH_HEIGHT
#define BWIDGETS_DEFAULT_VSWITCH_HEIGHT 40.0
#endif

namespace BWidgets
{

/**
 *  @brief  %VSwitch Button widget.
 *
 *  %VSwitch is a Button Widget. It displays its status (represented by its 
 *  bool value) as a vertical switch. It supports user interaction via 
 *  Clickable, Draggable, and Scrollable. Its appearance is defined by the 
 *  BgColors parameter (static elements, false) and by the FgColors parameter
 *  (active elements, true).
 */
class VSwitch : public Button, public Draggable, public Scrollable
{
public:

	/**
	 * @brief  Constructs a default %VSwitch object.
	 * 
	 */
	VSwitch ();

	/**
	 *  @brief  Constructs a default %VSwitch object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	VSwitch (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %VSwitch with default size.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	VSwitch	(bool toggleable, bool clicked = false, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %VSwitch.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	VSwitch	(const double x, const double y, const double width, const double height, 
			 bool toggleable = true, bool clicked = false,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %VSwitch. 
	 *  @return  Pointer to the new %VSwitch.
	 *
	 *  Creates a clone of this %VSwitch by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %VSwitch. 
	 *  @param that  Other %VSwitch.
	 *
	 *  Copies all properties from another %VSwitch. But NOT its linkage.
	 */
	void copy (const VSwitch* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

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
     *  @brief  Unclipped draw a %VSwitch to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %VSwitch to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %VSwitch to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline VSwitch::VSwitch () :
	VSwitch (0.0, 0.0, BWIDGETS_DEFAULT_VSWITCH_WIDTH, BWIDGETS_DEFAULT_VSWITCH_HEIGHT, true, false, URID_UNKNOWN_URID, "")
{

}

inline VSwitch::VSwitch (const uint32_t urid, const std::string& title) : 
	VSwitch (0.0, 0.0, BWIDGETS_DEFAULT_VSWITCH_WIDTH, BWIDGETS_DEFAULT_VSWITCH_HEIGHT, true, false, urid, title) 
{

}

inline VSwitch::VSwitch (bool toggleable, bool clicked, uint32_t urid, std::string title) : 
	VSwitch (0.0, 0.0, BWIDGETS_DEFAULT_VSWITCH_WIDTH, BWIDGETS_DEFAULT_VSWITCH_HEIGHT, toggleable, clicked, urid, title) 
{

}

inline VSwitch::VSwitch (const double  x, const double y, const double width, const double height, bool toggleable, bool clicked, uint32_t urid, std::string title) :
		Button (x, y, width, height, toggleable, clicked, urid, title),
		Draggable(),
		Scrollable()
{
	setBackground (BStyles::noFill);
	setBorder (BStyles::noBorder);
}

inline Widget* VSwitch::clone () const 
{
	Widget* f = new VSwitch (urid_, title_);
	f->copy (this);
	return f;
}

inline void VSwitch::copy (const VSwitch* that)
{
	Scrollable::operator= (*that);
	Draggable::operator= (*that);
	Widget::copy (that);
}

inline void VSwitch::update()
{
	Widget::update();
}

inline void VSwitch::onButtonClicked (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (isToggleable() && (pev->getPosition() == pev->getOrigin())) setValue (!getValue());
	Clickable::onButtonClicked (event);
}

inline void VSwitch::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	setValue (pev->getPosition().y < 0.5 * getHeight());
	Draggable::onPointerDragged (event);
}

inline void VSwitch::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (wev->getDelta().y != 0) setValue (wev->getDelta().y < 0);
	Scrollable::onWheelScrolled (event);
}

inline void VSwitch::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void VSwitch::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void VSwitch::draw (const BUtilities::Area<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	const double x0 = getXOffset();
	const double y0 = getYOffset();
	const double heff = getEffectiveHeight ();
	const double weff = getEffectiveWidth ();

	// Draw only if minimum requirements satisfied
	if ((heff >= 1) && (weff >= 1))
	{
		cairo_t* cr = cairo_create (surface_);

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			// Calculate aspect ratios first
			const double radius = 0.5 * weff - 1.0;
			const double max = (getValue() ? 1.0 : 0.0);
			const double xc = x0 + 0.5 * weff + 1.0;
			const double yc = y0 + heff - radius - max * (heff - 1.0 - 2.0 * radius);

			const BStyles::Color fgColor = getFgColors()[getStatus()];
			const BStyles::Color bgColor = getBgColors()[getStatus()];
			drawVBar(cr, x0, y0, weff, heff, 1.0, 1.0 - max, fgColor, bgColor);
			drawKnob(cr, xc, yc, radius, 1.0, bgColor, bgColor);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_VSWITCH_HPP_ */
