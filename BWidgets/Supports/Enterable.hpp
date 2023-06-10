/* Enterable.hpp
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

#ifndef BWIDGETS_ENTERABLE_HPP_
#define BWIDGETS_ENTERABLE_HPP_

#include "Clickable.hpp"
#include "EventQueueable.hpp"
#include "../Widget.hpp"
#include "../../BEvents/PointerEvent.hpp"

namespace BWidgets
{

/**
 *  @brief  Interface class for Support to enter a widget.
 */
class Enterable : public Support
{
public:

    /**
     *  @brief  Constructs a default %Enterable object.
     */
    Enterable ();

    /**
     *  @brief  Constructs a %Enterable object with a provided support 
     *  status.
     *  @param status  Support status. 
     */
    Enterable (const bool status);

    /**
     *  @brief  Switch the support to enter a Widget on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setEnterable (const bool status);

    /**
     *  @brief  Information about the support to enter a Widget.
     *  @return  True if on, otherwise false.
     */
    bool isEnterable () const;
    
    /**
     *  @brief  Enters this object
     *
     *  Overridable virtual method. By default, it simulates clicking into
     *  the middle of this object by emitting the respective events, if this
     *  object is Clickable.
     */
    virtual void enter ();

};

inline Enterable::Enterable () : Enterable (true) {}

inline Enterable::Enterable (const bool status) : 
    Support (status)
{}

inline void Enterable::setEnterable (const bool status)
{
    setSupport(status);
}

inline bool Enterable::isEnterable () const
{
    return getSupport();
}

inline void Enterable::enter () 
{
    Clickable* c = dynamic_cast<Clickable*>(this);
    if (!c) return;
    if (!c->isClickable()) return;
    Widget* w = dynamic_cast<Widget*> (this);
    if (!w) return;
    Linkable* m = w->getMain();
    if (!m) return;
    EventQueueable* q = dynamic_cast<EventQueueable*>(m);

    // Press
    BEvents::PointerEvent* press = new BEvents::PointerEvent
                                   (
                                        w,
                                        BEvents::Event::EventType::buttonPressEvent,
                                        w->getPosition() * 0.5,
                                        w->getPosition() * 0.5,
                                        BUtilities::Point<> (),
                                        BDevices::MouseButton::ButtonType::left
                                   );
	q->addEventToQueue (press);

    // Release
     BEvents::PointerEvent* release = new BEvents::PointerEvent
                                      (
                                        w,
                                        BEvents::Event::EventType::buttonReleaseEvent,
                                        w->getPosition() * 0.5,
                                        w->getPosition() * 0.5,
                                        BUtilities::Point<> (),
                                        BDevices::MouseButton::ButtonType::left
                                      );
	q->addEventToQueue (release);

    // Click
     BEvents::PointerEvent* click = new BEvents::PointerEvent
                                    (
                                        w,
                                        BEvents::Event::EventType::buttonClickEvent,
                                        w->getPosition() * 0.5,
                                        w->getPosition() * 0.5,
                                        BUtilities::Point<> (),
                                        BDevices::MouseButton::ButtonType::left
                                    );
	q->addEventToQueue (click);
}

}
#endif /* BWIDGETS_ENTERABLE_HPP_ */