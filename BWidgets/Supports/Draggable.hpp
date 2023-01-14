/* Draggable.hpp
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

#ifndef BWIDGETS_DRAGGABLE_HPP_
#define BWIDGETS_DRAGGABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"
#include "../../BEvents/PointerEvent.hpp"

namespace BWidgets
{

/**
 *  @brief  Pointer drag support.
 */
class Draggable : virtual public Callback, public Support
{
public:
    /**
     *  @brief  Switch pointer drag support on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether the widget may emit a POINER_DRAG_EVENT if the main 
     *  window event handler received a pointer move event with pressed
     *  buttons from the host system. In this case, a PointerEvent with the 
     *  type pointerDragEvent will be scheduled and send to the widget.
     */
    virtual void setDraggable (const bool status) {setSupport (status);}

    /**
     *  @brief  Information pointer drag support.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is draggable, the main window event handler let the widget
     *  emit a PointerEvent of the type POINER_DRAG_EVENT if the main window
     *  event handler received a pointer move event with pressed buttons from 
     *  the host system.
     */
    bool isDraggable () const {return getSupport();}

    /**
     *  @brief  Method called upon pointer drag.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a pointer drag. By default, it calls its static callback function.
     */
    virtual void onPointerDragged (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::pointerDragEvent) (event);
    }
};

}
#endif /* BWIDGETS_DRAGGABLE_HPP_ */