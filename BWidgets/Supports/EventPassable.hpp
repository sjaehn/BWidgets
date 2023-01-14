/* EventPassable.hpp
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

#ifndef BWIDGETS_EVENTPASSABLE_HPP_
#define BWIDGETS_EVENTPASSABLE_HPP_

#include <cstdint>
#include <map>
#include "../../BEvents/Event.hpp"

namespace BWidgets
{

/**
 *  @brief  Support for passing events to subjacent widgets.
 *
 *  By default, host events (e. g., PointerEvent, WheelEvent, PointerFocusEvent) are
 *  associated with the most frontward visible widget for the respective
 *  position. The event is then emitted by this widget if this widget actively
 *  supports (is<SupportClass>() == true) the respective event. Otherwise it
 *  blocks this event.
 *
 *  %EventPassable supports passing events to subjacent widgets if the widget
 *  doesn't actively support the respective event type.
 */
class EventPassable
{
protected:

    BEvents::Event::EventType eventPassable_;

public:

    virtual ~EventPassable() {};

    /**
     *  @brief  Switch event passing support on/off.
     *  @param eventType  EventType.
     *  @param status  True if on, otherwise false.
     *
     *  Makes an object transparent or intransparent for the respective 
     *  @a eventType.
     *
     *  @note @a setEventPassable(EventType::NoEvent) doesn't have any effect. 
     */
    virtual void setEventPassable (const BEvents::Event::EventType eventType, bool status = true) 
    {
        eventPassable_ = (eventPassable_ & (~eventType)) | (status ? eventType : BEvents::Event::EventType::none);
    }

    /**
     *  @brief  Information about event passing support.
     *  @param eventType  EventType.
     *  @return  True if on, otherwise false.
     *
     *  Information about the transparency of an object for the respective
     *  @a eventType.
     *
     *  If multiple event types are passed, then true is returned if all
     *  event types are set to be transparent. Otherwise false. 
     *
     *  @note The @a eventType NoEvent always returns true.
     */
    bool isEventPassable (const BEvents::Event::EventType eventType) const
    {
        return (eventPassable_ & eventType) == eventType;
    }

};

}
#endif /* BWIDGETS_EVENTPASSABLE_HPP_ */