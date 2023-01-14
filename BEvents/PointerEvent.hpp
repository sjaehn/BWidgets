/* PointerEvent.hpp
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

#ifndef BEVENTS_POINTEREVENT_HPP_
#define BEVENTS_POINTEREVENT_HPP_

#include "Event.hpp"
#include "../BDevices/MouseButton.hpp"
#include "../BUtilities/Point.hpp"

namespace BEvents
{
/**
 *  @brief  Pointer movement and button events.
 *  A %PointerEvent is emitted by the system (via pugl and the main window)
 *  if a button is pressed or released and/or the pointer is moved over a 
 *  widget. The %PointerEvent contains data about the position (relative to the
 *  respective widget and the button pressed (or not). %PointerEvents will be 
 *  handled by the respective widget and can be redirected to external callback
 *  functions.
 */
class PointerEvent : public Event
{
protected:
	BUtilities::Point<> point_, origin_, delta_;
	BDevices::MouseButton::ButtonType button_;

public:

    /**
     *  @brief  Creates an empty %PointerEvent.
     */
	PointerEvent () :
		PointerEvent (nullptr, EventType::None, 0, 0, 0, 0, 0, 0, BDevices::MouseButton::ButtonType::NO_BUTTON) 
    {

    }

    /**
     *  @brief  Creates a %PointerEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param x  Present pointer x coordinate relative to the widget origin.
     *  @param y  Present pointer y coordinate relative to the widget origin.
     *  @param xOrigin  Original pointer x coordinate relative to the widget
     *  origin.
     *  @param yOrigin  Original pointer y coordinate relative to the widget 
     *  origin.
     *  @param deltaX  Pointer movement x coordinate.
     *  @param deltaY  Pointer movement y coordinate.
     *  @param button  ButtonCode.
     */
	PointerEvent    (BWidgets::Widget* widget, const EventType type,
			         const double x, const double y, 
                     const double xOrigin, const double yOrigin,
			         const double deltaX, const double deltaY, 
                     const BDevices::MouseButton::ButtonType button) :
		PointerEvent (widget, type, BUtilities::Point<> (x, y), BUtilities::Point<> (xOrigin, yOrigin), BUtilities::Point<> (deltaX, deltaY), button) 
    {

    }

    /**
     *  @brief  Creates a %PointerEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param point  Present pointer coordinates relative to the widget 
     *  origin.
     *  @param origin  Original pointer coordinates relative to the widget
     *  origin.
     *  @param delta  Pointer movement coordinates.
     *  @param button  ButtonCode.
     */
	PointerEvent    (BWidgets::Widget* widget, const EventType type, 
                     const BUtilities::Point<>& point,
			         const BUtilities::Point<>& origin, 
                     const BUtilities::Point<>& delta,
			         const BDevices::MouseButton::ButtonType button) :
		Event (widget, type), 
        point_ (point), 
        origin_ (origin), 
        delta_ (delta), 
        button_ (button) {}

	/**
	 *  @brief  Redefines the pointer coordinates of the %PointerEvent.
	 *  @param point  Pointer coordinate relative to the widgets origin.
	 */
	virtual void setPosition (const BUtilities::Point<>& coords)
 	{
        point_ = coords;
    }

	/**
	 *  @brief  Gets the pointer coordinates of the %PointerEvent.
	 *  @return  Pointer coordinate relative to the widgets origin.
	 */
	BUtilities::Point<> getPosition () const
	{
        return point_;
    }

	/**
	 *  @brief  Redefines the position where the button was initially pressed.
	 *  @param origin  Original pointer coordinates relative to the widgets 
     *  origin.
	 */
	virtual void setOrigin (const BUtilities::Point<>& coords)
	{
        origin_ = coords;
    }

	/**
	 *  @brief  Gets the position where the respective button was initially 
     *  pressed.
	 *  @return  Position coordinates relative to the widgets origin.
     *
     *  The returned value is the same as for getPoint() for 
     *  BUTTON_PRESS_EVENTs, 0.0 for POINTER_MOTION_EVENTs.
	 */
	BUtilities::Point<> getOrigin () const
	{
        return origin_;
    }

	/**
	 *  @brief  Redefines the pointer movement.
	 *  @param delta  Movement coordinates of the pointer.
	 */
	virtual void setDelta (const BUtilities::Point<>& coords)
	{
        delta_ = coords;
    }

	/**
	 *  @brief  Gets the movement (relative to the last %PointerEvent).
	 *  @return Change in coordinates.
	 */
	BUtilities::Point<> getDelta () const
	{
        return delta_;
    }

	/**
	 *  @brief  Redefines the button pressed of the %PointerEvent.
	 *  @param button  Button pressed.
	 */
	virtual void setButton (const BDevices::MouseButton::ButtonType button)
	{
        button_ = button;
    }

	/**
	 *  @brief  Gets the button pressed of the %PointerEvent.
	 *  @return  Button pressed
	 */
	BDevices::MouseButton::ButtonType getButton () const
	{
        return button_;
    }
};

}

#endif /* BEVENTS_POINTEREVENT_HPP_ */
