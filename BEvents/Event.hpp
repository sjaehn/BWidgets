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
        NO_EVENT                = 0x0000,
        CONFIGURE_REQUEST_EVENT = 0x0001,
        EXPOSE_REQUEST_EVENT    = 0x0002,
        CLOSE_REQUEST_EVENT     = 0x0004,
        WIDGET_EVENTS           = CONFIGURE_REQUEST_EVENT + EXPOSE_REQUEST_EVENT + CLOSE_REQUEST_EVENT,
        KEY_PRESS_EVENT         = 0x0008,
        KEY_RELEASE_EVENT       = 0x0010,
        KEY_EVENTS              = KEY_PRESS_EVENT + KEY_RELEASE_EVENT,
        BUTTON_PRESS_EVENT      = 0x0020,
        BUTTON_RELEASE_EVENT    = 0x0040,
        BUTTON_CLICK_EVENT      = 0x0080,
        BUTTON_EVENTS           = BUTTON_PRESS_EVENT + BUTTON_RELEASE_EVENT + BUTTON_CLICK_EVENT,
        POINTER_DRAG_EVENT      = 0x0100,
        POINTER_MOTION_EVENT    = 0x0200,
        POINTER_EVENTS          = POINTER_DRAG_EVENT + POINTER_MOTION_EVENT,
        WHEEL_SCROLL_EVENT      = 0x0400,
        MOUSE_EVENTS            = BUTTON_EVENTS + POINTER_EVENTS + WHEEL_SCROLL_EVENT,
        VALUE_CHANGED_EVENT     = 0x0800,
        MESSAGE_EVENT           = 0x1000,
        CONTENT_EVENTS          = VALUE_CHANGED_EVENT + MESSAGE_EVENT,
        POINTER_FOCUS_IN_EVENT  = 0x2000,
        POINTER_FOCUS_OUT_EVENT = 0x4000,
        POINTER_FOCUS_EVENTS    = POINTER_FOCUS_IN_EVENT + POINTER_FOCUS_OUT_EVENT
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
