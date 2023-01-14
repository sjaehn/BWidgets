/* Pointable.hpp
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

#ifndef BWIDGETS_POINTABLE_HPP_
#define BWIDGETS_POINTABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Supports pointer tracking by pointer motion events.
 */
class Pointable : virtual public Callback, public Support
{
public:

    /**
     *  @brief  Switch the support for pointer motion events on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether a widget may emit a PointerEvent with 
     *  PointerMotionEvent if the main window event handler received a 
     *  pointer move event from the host and the pointer moves over the 
     *  widget. In this case, a PointerEvent with the type 
     *  PointerMotionEvent will be scheduled and send to the widget.
     */
    virtual void setPointable (const bool status) {setSupport (status);}

    /**
     *  @brief  Information about the support for value changed events.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is pointable, the main window event handler let the widget
     *  emit a PointerEvent with the type PointerMotionEvent if the pointer
     *  is moved over the widget.
     */
    bool isPointable () const {return getSupport();}

    /**
     *  @brief  Method when a PointerEvent with the type PointerMotionEvent
     *  is received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a pointer motion over the widget. By default, it calls its static
     *  callback function.
     */
    virtual void onPointerMotion (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::ValueChangedEvent) (event);
    }

};

}
#endif /* BWIDGETS_POINTABLE_HPP_ */