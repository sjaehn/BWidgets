/* Button.hpp
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

#ifndef BWIDGETS_BUTTON_HPP_
#define BWIDGETS_BUTTON_HPP_

#include "Widget.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/Toggleable.hpp"
#include "../BEvents/Event.hpp"
#include <iostream>

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
 *  %Button is a Clickable Valueable Widget. The value represents its two
 *  possible conditions: on (true) or off (false). The visualble content of
 *  the %Button is represented by its background and its border. The border
 *  color itself is represented by the BgColor and is changed upon changing
 *  the %Button condition (on: highLighted, off: darkened).
 */
class Button : public Widget, public Clickable, public ValueableTyped<bool>, public Toggleable
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
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Button	(bool toggleable, bool clicked = false, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Button.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Button	(const double x, const double y, const double width, const double height, 
			 bool toggleable = false, bool clicked = false,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

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
};

inline Button::Button () : Button (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, false, false, URID_UNKNOWN_URID, "") {}

inline Button::Button	(const uint32_t urid, const std::string& title) : 
	Button (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, false, false, urid, title) {}

inline Button::Button	(bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, toggleable, clicked, urid, title) {}

inline Button::Button	(const double x, const double y, const double width, const double height, 
			 	 bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	Clickable (),
	ValueableTyped<bool> (clicked),
	Toggleable ()
{
	setToggleable (toggleable);
	setBackground (BStyles::Fill(getBgColors()[BStyles::Status::STATUS_NORMAL]));
	setBorder	(BStyles::Border 
				 (BStyles::Line (getBgColors()[BStyles::Status::STATUS_NORMAL].illuminate (clicked ? BStyles::Color::highLighted : BStyles::Color::darkened), 1.0), 
				 0.0, 0.0, 0.15 * std::min (width, height)));
}

inline Widget* Button::clone () const 
{
	Widget* f = new Button (urid_, title_);
	f->copy (this);
	return f;
}

inline void Button::copy (const Button* that)
{
	Clickable::operator= (*that);
	ValueableTyped<bool>::operator= (*that);
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
	BStyles::Border border = getBorder();
	border.line.color = getBgColors()[getStatus()].illuminate (getValue() ? BStyles::Color::highLighted : BStyles::Color::darkened);
	setBorder (border);
	Widget::update();
}

}

#endif /* BWIDGETS_BUTTON_HPP_ */
