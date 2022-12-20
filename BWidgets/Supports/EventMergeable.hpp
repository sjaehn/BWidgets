/* EventMergeable.hpp
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

#ifndef BWIDGETS_EVENTMERGEABLE_HPP_
#define BWIDGETS_EVENTMERGEABLE_HPP_

#include <cstdint>
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

    std::map<uint8_t, bool> eventMergeable_;

public:

    virtual ~EventMergeable() {};

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
    virtual void setEventMergeable (const uint32_t eventType, const bool status) 
    {
        for (uint32_t i = 0; i < 32; ++i)
        {
            if ((1 << i) & eventType) eventMergeable_[i] = status;
        }
    }

    /**
     *  @brief  Information about event merging support.
     *  @param eventType  EventType.
     *  @return  True if on, otherwise false.
     *
     *  If an event type of a widget is mergeable, the main window event 
     *  handler may merge events of this type.
     *
     *  If multiple event types are passed, then only the callback function
     *  for the first match is returned.
     */
    bool isEventMergeable (const uint32_t eventType) const
    {
        for (uint32_t i = 0; i < 32; ++i)
        {
            if ((1 << i) & eventType)
            {
                std::map<uint8_t, bool>::const_iterator it = eventMergeable_.find (i);
                if (it == eventMergeable_.end()) return false;
                return it->second;
            }
        }

        return false;
    }

};

}
#endif /* BWIDGETS_EVENTMERGEABLE_HPP_ */