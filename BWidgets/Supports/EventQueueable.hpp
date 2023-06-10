/* EventQueueable.hpp
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

#ifndef BWIDGETS_EVENTQUEUEABLE_HPP_
#define BWIDGETS_EVENTQUEUEABLE_HPP_

#include <algorithm>
#include <list>
#include "../../BEvents/Event.hpp"

namespace BWidgets
{

/**
 *  @brief  Support for queueing events.
 *
 *  Parent class of the (main) BWidgets::Window event queue. By default, all
 *  events are able to be queued to the event queue.
 */
class EventQueueable
{

protected:
    BEvents::Event::EventType eventQueueable_;
    std::list<BEvents::Event*> eventQueue_;
    
public:

    /**
     *  @brief  Constructs a new EventQueueable object.
     * 
     *  By default, all events are able to be queued to the event queue.
     */
    EventQueueable ();

    virtual ~EventQueueable();

    /**
     *  @brief  Switch event queueing support on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setEventQueueable (const BEvents::Event::EventType eventType, const bool status);

    /**
     *  @brief  Information about event queueing support.
     *  @return  True if on, otherwise false.
     */
    bool isEventQueueable (const BEvents::Event::EventType eventType) const;

    /**
	 *  @brief  Queues an event.
	 *  @param event  Pointer to the event.
	 *
	 *  Passes an @a event and adds it to the event queue. From now on, the 
     *  this object controls the @a event object lifetime. If the @a event
     *  lifetime ends, the @a event is destructed by calling @c delete. Thus,
     *  the @a event passed
	 *  1. must be dynamicly allocated before by calling @c new, and
	 *  2. must NOT be deleted outside once it is passed to this object.
	 *
     *  Does not add but deletes the passed event if the passed even is not
     *  queueable. Ensures that the @a event is only present once in the event 
     *  queue.
     *
     *  Virtual implementations of this method also may try to merge events,
     *  if they are marked to be EventMergeable.
	 */
	virtual void addEventToQueue (BEvents::Event* event);

    /**
     *  @brief  Pops the event from the front of the event queue.
     * 
     *  @return  Pointer to the event beeing in front of the event queue or
     *  nullptr if empty.
     */
    virtual BEvents::Event* popEvent ();

    /**
     *  @brief  Pops the event from from somewhere in the event queue.
     *  @param event  Pointer to the event to be popped.
     *  @return  Pointer to the event or nullptr if not present.
     */
    virtual BEvents::Event* popEvent (BEvents::Event* event);

    /**
     *  @brief  Removes an event from the event queue (if present) and calls
     *  @c delete to de-allocate its memory.  
     *  @param event  Pointer to the event.
     */
    virtual void deleteEvent (BEvents::Event* event);

};

inline EventQueueable::EventQueueable() :
    eventQueueable_(BEvents::Event::EventType::all),
    eventQueue_()
{}

inline EventQueueable::~EventQueueable()
{
    while (!eventQueue_.empty())
    {
        BEvents::Event* event = eventQueue_.front();
        eventQueue_.pop_front();
        delete event;
    }
}

inline void EventQueueable::setEventQueueable (const BEvents::Event::EventType eventType, const bool status) 
{
    eventQueueable_ = (eventQueueable_ & (~eventType)) | (status ? eventType : BEvents::Event::EventType::none);
}

inline bool EventQueueable::isEventQueueable (const BEvents::Event::EventType eventType) const
{
    return (eventQueueable_ & eventType) == eventType;
}

inline void EventQueueable::addEventToQueue (BEvents::Event* event)
{
    if (!event) return;

    // Add to the event queue
    if (isEventQueueable (event->getEventType()))
    {
        if (std::find (eventQueue_.begin(), eventQueue_.end(), event) ==  eventQueue_.end()) eventQueue_.push_back (event);
    }

    // Not queueable: discard event
    else delete event;
}

inline BEvents::Event* EventQueueable::popEvent ()
{
    BEvents::Event* event = eventQueue_.front();
    eventQueue_.pop_front();
    return event;
}

inline BEvents::Event* EventQueueable::popEvent (BEvents::Event* event)
{
    std::list<BEvents::Event*>::const_iterator it = std::find (eventQueue_.begin(), eventQueue_.end(), event);
    if (it == eventQueue_.cend()) return nullptr;
    else
    {
        BEvents::Event* e = *it;
        eventQueue_.erase (it);
        return e;
    }
}

inline void EventQueueable::deleteEvent (BEvents::Event* event)
{
    popEvent (event);
    delete event;
}

}
#endif /* BWIDGETS_EVENTQUEUEABLE_HPP_ */