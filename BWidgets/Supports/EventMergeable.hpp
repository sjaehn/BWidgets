/* EventMergeable.hpp
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

#ifndef BWIDGETS_EVENTMERGEABLE_HPP_
#define BWIDGETS_EVENTMERGEABLE_HPP_

#include <map>
#include "../../BEvents/Event.hpp"

namespace BWidgets
{

/**
 *  @brief  Event merging support.
 */
class EventMergeable
{
protected:

    std::map<BEvents::Event::EventType, bool> eventMergeable_;

public:

    /**
     *  @brief  Switch event merging support on/off.
     *  @param eventType  EventType.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether events of the same event type emitted by (optional) 
     *  the same widget and (optinal) with the same parameters may
     *  be merged in the main window event queue or not.
     *
     *  Note: %EventMergeable is only a hint. It will be ignored if it doesn't
     *  make any sense (e. g., CLOSE_REQUEST_EVENT).
     */
    void setEventMergeable (const BEvents::Event::EventType eventType, const bool status) 
    {
        eventMergeable_[eventType] = status;
    }

    /**
     *  @brief  Information about event merging support.
     *  @param eventType  EventType.
     *  @return  True if on, otherwise false.
     *
     *  If an event type of a widget is mergeable, the main window event 
     *  handler may merge events of this type.
     */
    bool isEventMergeable (const BEvents::Event::EventType eventType) const
    {
        std::map<BEvents::Event::EventType, bool>::const_iterator it = eventMergeable_.find (eventType);
        if (it == eventMergeable_.end()) return false;
        return it->second;
    }

};

}
#endif /* BWIDGETS_EVENTMERGEABLE_HPP_ */