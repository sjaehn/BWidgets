/* Event.hpp
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

#ifndef BEVENTS_EVENT_HPP_
#define BEVENTS_EVENT_HPP_

namespace BWidgets
{
class Widget;	// Forward declaration
}

namespace BEvents
{

/**
 *  @brief  Main class of events. 
 *
 *  Stores the event type and a pointer to the widget that caused the event. 
 *  All other event classes are derived from this class.
 */
class Event
{
public:

    /**
     *  @brief  Enumeration of %Event types
     */
    enum EventType
    {
        CONFIGURE_REQUEST_EVENT,
        EXPOSE_REQUEST_EVENT,
        CLOSE_REQUEST_EVENT,
        KEY_PRESS_EVENT,
        KEY_RELEASE_EVENT,
        BUTTON_PRESS_EVENT,
        BUTTON_RELEASE_EVENT,
        BUTTON_CLICK_EVENT,
        POINTER_MOTION_EVENT,
        POINTER_DRAG_EVENT,
        WHEEL_SCROLL_EVENT,
        VALUE_CHANGED_EVENT,
        FOCUS_IN_EVENT,
        FOCUS_OUT_EVENT,
        MESSAGE_EVENT,
        NO_EVENT
    };

protected:
	BWidgets::Widget* eventWidget_;
	EventType eventType_;


public:

    /**
	 * @brief  Creates an empty %Event.
	 */
	Event () :
		Event (nullptr, NO_EVENT) 
    {

    }

    /**
	 *  @brief  Creates an %Event.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
	 */
	Event (BWidgets::Widget* widget, const EventType type) :
		eventWidget_ (widget), eventType_ (type) 
    {

    }

	virtual ~Event () 
    {

    }

	/**
	 *  @brief  Gets a pointer to the widget which caused the event.
	 *  @return  Pointer to the widget (read / write).
	 */
	BWidgets::Widget* getWidget ()
	{
        return eventWidget_;
    }

    /**
	 *  @brief  Gets a pointer to the widget which caused the event.
	 *  @return  Pointer to the widget (read only).
	 */
	const BWidgets::Widget* getWidget () const
	{
        return eventWidget_;
    }

	/**
	 *  @brief  Gets the type of the event.
	 *  @return  Event type
	 */
	EventType getEventType () const
	{
        return eventType_;
    }

};

}

#endif /* BEVENTS_EVENT_HPP_ */
