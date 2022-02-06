/* WheelEvent.hpp
 * Copyright (C) 2018 - 2021  Sven Jähnichen
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

#ifndef BEVENTS_WHEELEVENT_HPP_
#define BEVENTS_WHEELEVENT_HPP_

#include "Event.hpp"
#include "../BUtilities/Point.hpp"

namespace BEvents
{

/**
 *  @brief  Mouse wheel scrolling event.
 *
 *  Wheel events are emitted by the system (via pugl and the main window) if
 *  a (mouse) wheel is turned.
 * 
 *  The wheel event contains data about the relative change of the wheel and
 *  about the pointer position (relative to the respective widget.
 *  Wheel events will be handled by the respective widget and can be
 *  redirected to external callback functions.
 */
class WheelEvent : public Event
{
protected:
	BUtilities::Point<> point_;
	BUtilities::Point<> delta_;

public:

    /**
     *  @brief  Creates an empty %WheelEvent.
     */
	WheelEvent () :
		WheelEvent (nullptr, NO_EVENT, 0, 0, 0, 0) 
    {

    }

    /**
     *  @brief  Creates a %WheelEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param x  Pointer x coordinate relative to the widget origin.
     *  @param y  Pointer y coordinate relative to the widget origin.
     *  @param deltaX  Wheel x coordinate scroll.
     *  @param deltaY  Wheel y coordinate scroll.
     */
	WheelEvent  (BWidgets::Widget* widget, const EventType type, 
                 const double x, const double y, const double deltaX, const double deltaY) :
		WheelEvent (widget, type, BUtilities::Point<> (x, y), BUtilities::Point<> (deltaX, deltaY))
    {

    }

    /**
     *  @brief  Creates a %WheelEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param point  Pointer coordinates relative to the widget origin.
     *  @param delta  Wheel scroll coordinates.
     */
	WheelEvent  (BWidgets::Widget* widget, const EventType type, 
                 const BUtilities::Point<>& point, const BUtilities::Point<> delta) :
		Event (widget, type), 
        point_ (point), delta_ (delta) 
    {

    }

	/**
	 *  @brief  Redefines the pointers coordinate.
	 *  @param coords  Pointer coordinate relative to the widgets origin.
	 */
	void setPosition (const BUtilities::Point<>& coords)
  	{
        point_ = coords;
    }

	/**
	 *  @brief  Gets the pointers coordinate of the wheel event.
	 *  @return Pointer coordinate relative to the widgets origin.
	 */
	BUtilities::Point<> getPosition () const
 	{
        return point_;
    }

	/**
	 *  @brief  Redefines the wheels movement
	 *  @param delta  Movement of the wheel.
	 */
	void setDelta (const BUtilities::Point<>& coords)
 	{
        delta_ = coords;
    }

	/**
	 *  @brief  Gets the movement of the wheel.
	 *  @return  Movement of the wheel.
	 */
	BUtilities::Point<> getDelta () const
 	{
        return delta_;
    }
};

}

#endif /* BEVENTS_WHEELEVENT_HPP_ */
