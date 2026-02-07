/* PointerEvent.hpp
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
	BUtilities::Point<> point_, origin_, delta_, absolutePoint_, absoluteOrigin_;
	BDevices::MouseButton::ButtonType button_;

public:

    /**
     *  @brief  Creates an empty %PointerEvent.
     */
	PointerEvent () :
		PointerEvent (nullptr, EventType::none, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, BDevices::MouseButton::ButtonType::none) 
    {

    }

    /**
     *  @brief  Creates a %PointerEvent.
	 *
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
		PointerEvent	(widget, 
						 type, 
						 BUtilities::Point<> (x, y), 
						 BUtilities::Point<> (xOrigin, yOrigin), 
						 BUtilities::Point<> (deltaX, deltaY), 
						 BUtilities::Point<>(), // TODO Initialize with widget position
                         BUtilities::Point<>(), // TODO Initialize with widget position
						 button) 
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
     *  @param absoluteX  Present pointer absolute x coordinate.
     *  @param absoluteY  Present pointer absolute y coordinate.
     *  @param absoluteXOrigin  Original pointer absolute x coordinate.
     *  @param absoluteYOrigin  Original pointer absolute y coordinate.
     *  @param button  ButtonCode.
     */
	PointerEvent    (BWidgets::Widget* widget, const EventType type,
			         const double x, const double y, 
                     const double xOrigin, const double yOrigin,
			         const double deltaX, const double deltaY,
					 const double absoluteX, const double absoluteY,
                     const double absoluteXOrigin, const double absoluteYOrigin, 
                     const BDevices::MouseButton::ButtonType button) :
		PointerEvent    (widget, 
                         type, 
                         BUtilities::Point<> (x, y), 
                         BUtilities::Point<> (xOrigin, yOrigin), 
                         BUtilities::Point<> (deltaX, deltaY), 
                         BUtilities::Point<>(absoluteX, absoluteY),
                         BUtilities::Point<>(absoluteXOrigin, absoluteYOrigin),
                         button) 
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
		PointerEvent    (widget, 
                         type, 
                         point, 
                         origin, 
                         delta, 
                         BUtilities::Point<>() /* TODO Initialize with widget position */, 
                         BUtilities::Point<>() /* TODO Initialize with widget position */,
                         button)
	{

	}

	/**
     *  @brief  Creates a %PointerEvent.
	 *
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param point  Present pointer coordinates relative to the widget 
     *  origin.
     *  @param origin  Original pointer coordinates relative to the widget
     *  origin.
     *  @param delta  Pointer movement coordinates.
     *  @param absolutePoint  Present pointer absolute position.
     *  @param absoluteOrigin  Original pointer absolute position.
     *  @param button  ButtonCode.
     */
	PointerEvent    (BWidgets::Widget* widget, const EventType type, 
                     const BUtilities::Point<>& point,
			         const BUtilities::Point<>& origin, 
                     const BUtilities::Point<>& delta,
					 const BUtilities::Point<>& absolutePoint,
                     const BUtilities::Point<>& absoluteOrigin,
			         const BDevices::MouseButton::ButtonType button) :
		Event (widget, type), 
        point_ (point), 
        origin_ (origin), 
        delta_ (delta),
		absolutePoint_(absolutePoint),
        absoluteOrigin_(absoluteOrigin),
        button_ (button) 
	{
		
	}

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
	 *  @brief  Redefines the absolute pointer coordinates of the 
     *  %PointerEvent.
	 *  @param point  Absolute pointer coordinate.
	 */
	virtual void setAbsolutePosition (const BUtilities::Point<>& coords)
 	{
        absolutePoint_ = coords;
    }

	/**
	 *  @brief  Gets the absolute pointer coordinates of the %PointerEvent.
	 *  @return  Absolute pointer coordinate relative.
	 */
	BUtilities::Point<> getAbsolutePosition () const
	{
        return absolutePoint_;
    }

    /**
	 *  @brief  Redefines the absolute position where the button was initially
     *  pressed.
	 *  @param origin  Absolute original pointer coordinate.
	 */
	virtual void setAbsoluteOrigin (const BUtilities::Point<>& coords)
	{
        absoluteOrigin_ = coords;
    }

	/**
	 *  @brief  Gets the absolute position where the respective button was 
     *  initially pressed.
	 *  @return  Absolute position coordinate.
	 */
	BUtilities::Point<> getAbsoluteOrigin () const
	{
        return absoluteOrigin_;
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
