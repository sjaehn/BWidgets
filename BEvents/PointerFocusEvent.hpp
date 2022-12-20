/* PointerFocusEvent.hpp
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

#ifndef BEVENTS_POINTERFOCUSEVENT_HPP_
#define BEVENTS_POINTERFOCUSEVENT_HPP_

#include "../BUtilities/Point.hpp"
#include "Event.hpp"

namespace BEvents
{

/**
 *  @brief  %FocusEvents are emitted by widgets if the pointer rests for a
 *  predefined time over the widget.
 */
class PointerFocusEvent : public Event
{
protected:
	BUtilities::Point<> point_;

public:

    /**
     *  @brief  Creates an empty %PointerFocusEvent.
     */
	PointerFocusEvent () :
		PointerFocusEvent (nullptr, NO_EVENT, 0, 0) 
    {

    }

    /**
     *  @brief  Creates a %PointerFocusEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param x  Pointer x coordinate relative to the widget origin.
     *  @param y  Pointer y coordinate relative to the widget origin.
     */
	PointerFocusEvent (BWidgets::Widget* widget, const EventType type, const double x, const double y) :
		PointerFocusEvent (widget, type, BUtilities::Point<> (x, y))
    {

    }

    /**
     *  @brief  Creates a %PointerFocusEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param point  Coordinates relative to the widget origin.
     */
	PointerFocusEvent (BWidgets::Widget* widget, const EventType type, const BUtilities::Point<>& point) :
		Event (widget, type), point_ (point) 
    {

    }

	/**
	 *  @brief  Redefines the pointers coordinate.
	 *  @param coords Pointer coordinate relative to the widgets origin.
	 */
	virtual void setPosition (const BUtilities::Point<>& coords)
  	{
        point_ = coords;
    }

	/**
	 *  @brief  Gets the pointer coordinate.
	 *  @return Pointer coordinate relative to the widgets origin.
	 */
	BUtilities::Point<> getPosition () const
 	{
        return point_;
    }
};

}

#endif /* BEVENTS_POINTERFOCUSEVENT_HPP_ */
