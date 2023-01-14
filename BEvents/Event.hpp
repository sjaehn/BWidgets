/* Event.hpp
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

#ifndef BEVENTS_EVENT_HPP_
#define BEVENTS_EVENT_HPP_

#include <cstdint>

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
     *
     *  Type safe enumration supporting the bitwise operators | & ^ and ~.
     */
    enum class EventType : uint32_t
    {
        None                    = 0x0000,
        ConfigureRequestEvent   = 0x0001,
        ExposeRequestEvent      = 0x0002,
        CloseRequestEvent       = 0x0004,
        WidgetEvents            = ConfigureRequestEvent + ExposeRequestEvent + CloseRequestEvent,
        KeyPressEvent           = 0x0008,
        KeyReleaseEvent         = 0x0010,
        KeyEvents               = KeyPressEvent + KeyReleaseEvent,
        ButtonPressEvent        = 0x0020,
        ButtonReleaseEvent      = 0x0040,
        ButtonClickEvent        = 0x0080,
        ButtonEvents            = ButtonPressEvent + ButtonReleaseEvent + ButtonClickEvent,
        PointerDragEvent        = 0x0100,
        PointerMotionEvent      = 0x0200,
        PointerEvents           = PointerDragEvent + PointerMotionEvent,
        WheelScrollEvent        = 0x0400,
        WheelEvents             = WheelScrollEvent,
        MouseEvents             = ButtonEvents + PointerEvents + WheelEvents,
        ValueChangedEvent       = 0x0800,
        MessageEvent            = 0x1000,
        ContentEvents           = ValueChangedEvent + MessageEvent,
        PointerFocusInEvent     = 0x2000,
        PointerFocusOutEvent    = 0x4000,
        PointerFocusEvents      = PointerFocusInEvent + PointerFocusOutEvent
    };

protected:
	BWidgets::Widget* eventWidget_;
	EventType eventType_;


public:

    /**
	 * @brief  Creates an empty %Event.
	 */
	Event () :
		Event (nullptr, EventType::None) 
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

inline Event::EventType operator& (const Event::EventType lhs, const Event::EventType rhs)
{
    return static_cast<Event::EventType>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

inline Event::EventType operator| (const Event::EventType lhs, const Event::EventType rhs)
{
    return static_cast<Event::EventType>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

inline Event::EventType operator~ (const Event::EventType lhs)
{
    return static_cast<Event::EventType>(~static_cast<uint32_t>(lhs));
}

inline Event::EventType operator^ (const Event::EventType lhs, const Event::EventType rhs)
{
    return static_cast<Event::EventType>(static_cast<uint32_t>(lhs) ^ static_cast<uint32_t>(rhs));
}

}

#endif /* BEVENTS_EVENT_HPP_ */
