/* Button.hpp
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

#ifndef BWIDGETS_BUTTON_HPP_
#define BWIDGETS_BUTTON_HPP_

#include "Widget.hpp"
#include "Label.hpp"
#include "Supports/KeyPressable.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/Toggleable.hpp"
#include "../BEvents/Event.hpp"
#include <cairo/cairo.h>
#include <iostream>
#include BWIDGETS_DEFAULT_DRAWBUTTON_PATH

#ifndef BWIDGETS_DEFAULT_BUTTON_WIDTH
#define BWIDGETS_DEFAULT_BUTTON_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_BUTTON_HEIGHT
#define BWIDGETS_DEFAULT_BUTTON_HEIGHT 20.0
#endif

namespace BWidgets
{

/**
 *  @brief  Base Widget for drawing a %button. 
 *
 *  %Button is a Clickable Valueable Widget. It also supports Toggleable and 
 *  KeyPressable. The value represents its two
 *  possible conditions: on (true) or off (false). The visualble content of
 *  the %Button is represented by its background and its border. The border
 *  color itself is represented by the BgColor and is changed upon changing
 *  the %Button condition (on: highLighted, off: darkened).
 */
class Button : public Widget, public Clickable, public KeyPressable, public ValueableTyped<bool>, public Toggleable
{
public:

	/**
	 * @brief Constructs a new Button object with default parameters.
	 */
	Button ();

	/**
	 *  @brief  Constructs a new Button object with default parameters.
	 *  @param urid  URID.
	 *  @param title  %Widget title.
	 */
	Button	(const uint32_t, const std::string& title);

	/**
	 *  @brief  Creates a %Button with default size.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Button	(bool toggleable, bool clicked = false, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Button.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Button	(const double x, const double y, const double width, const double height, 
			 bool toggleable = false, bool clicked = false,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Button. 
	 *  @return  Pointer to the new %Button.
	 *
	 *  Creates a clone of this %Button by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Button. 
	 *  @param that  Other %Button.
	 *
	 *  Copies all properties from another %Button. But NOT its linkage.
	 */
	void copy (const Button* that);

	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area. Resizes the widget to its standard size if this widget doesn't 
	 *  have any children.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the widget extends.
	 *  @param width  New widget width.
	 *  @param height  New widget height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the widget extends.
	 *  @param extends  New widget extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

	/**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. Sets the %Button value to true (or inverts
	 *  the value if @c isToggleable() ), and calls its static callback 
     *  function.
     */
	virtual void onButtonPressed (BEvents::Event* event) override;

	/**
     *  @brief  Method called when pointer button released.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button released. Sets the %Button value to back to false
	 *  (if not @c isToggleable() ), and calls its static callback function.
     */
	virtual void onButtonReleased (BEvents::Event* event) override;

	/**
     *  @brief  Method called when pointer button clicked (pressed and 
     *  released).
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button cklicked. Inverts the %Button value (if 
	 *  @c isToggleable() ) and calls its static callback function.
     */
    virtual void onButtonClicked (BEvents::Event* event) override;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:
	/**
     *  @brief  Unclipped draw a %Button to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %Button to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %Button to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline Button::Button () : Button (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, false, false, BUTILITIES_URID_UNKNOWN_URID, "") {}

inline Button::Button	(const uint32_t urid, const std::string& title) : 
	Button (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, false, false, urid, title) {}

inline Button::Button	(bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, toggleable, clicked, urid, title) {}

inline Button::Button	(const double x, const double y, const double width, const double height, 
			 	 bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	Clickable (),
	KeyPressable(),
	ValueableTyped<bool> (clicked),
	Toggleable ()
{
	setKeyPressable (false),	// not implemented yet
	setToggleable (toggleable);
}

inline Widget* Button::clone () const 
{
	Widget* f = new Button (urid_, title_);
	f->copy (this);
	return f;
}

inline void Button::copy (const Button* that)
{
	KeyPressable::operator=(*that);
	Clickable::operator= (*that);
	ValueableTyped<bool>::operator= (*that);
	Toggleable::operator= (*that);
    Widget::copy (that);
}

inline void Button::resize ()
{
	BUtilities::Area<> a = (children_.empty()? BUtilities::Area<>(0, 0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT) : BUtilities::Area<>());
	for (Linkable* c : children_)
	{
		Widget* w = dynamic_cast<Widget*>(c);
		if (w) a.extend (BUtilities::Area<>(w->getPosition(), w->getPosition() + w->getExtends()));
	}

	resize (a.getExtends());
}

inline void Button::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void Button::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void Button::onButtonPressed (BEvents::Event* event)
{
	if (!isToggleable()) setValue (true);
	Clickable::onButtonPressed (event);
}

inline void Button::onButtonReleased (BEvents::Event* event)
{
	if (!isToggleable()) setValue (false);
	Clickable::onButtonReleased (event);
}

inline void Button::onButtonClicked (BEvents::Event* event)
{
	if (isToggleable()) setValue (!getValue());
	Clickable::onButtonClicked (event);
}

inline void Button::update ()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + BUtilities::Dictionary::get ((getValue() ? "on" : "off")));
		f->resize();
	}
	Widget::update();
}

inline void Button::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Button::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void Button::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	const double x0 = getXOffset();
	const double y0 = getYOffset();
	const double heff = getEffectiveHeight ();
	const double weff = getEffectiveWidth ();

	// Draw Button
	// only if minimum requirements satisfied
	if ((heff >= 1) && (weff >= 1))
	{
		cairo_t* cr = cairo_create (cairoSurface());

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			drawButton (cr, x0, y0, weff, heff, getValue(), getFgColors()[getStatus()], getBgColors()[getStatus()]);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_BUTTON_HPP_ */
