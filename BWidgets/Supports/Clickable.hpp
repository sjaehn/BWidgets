/* Clickable.hpp
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

#ifndef BWIDGETS_CLICKABLE_HPP_
#define BWIDGETS_CLICKABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Pointer button click (incl. press and release) support.
 */
class Clickable : virtual public Callback, public Support
{
public:
    /**
     *  @brief  Switch pointer button click support on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether the widget may emit a BUTTON_XXX_EVENT if the main 
     *  window event handler received a (mouse) button press or release
     *  event from the host system. In this case, a PointerEvent with the 
     *  type POINTER_XXX_EVENT (with XXX is PRESS, RELEASE, or CLICK) will 
     *  be scheduled by the main window and send to the widget.
     */
    virtual void setClickable (const bool status) {setSupport (status);}

    /**
     *  @brief  Information pointer button click support.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is clickable, the main window event handler let the widget
     *  emit a PointerEvent of the type POINER_XXX_EVENT (with XXX is PRESS, 
     *  RELEASE, or CLICK) if the main window event handler received a pointer
     *  button press or release event from the host system.
     */
    bool isClickable () const {return getSupport();}

    /**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonPressed (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::BUTTON_PRESS_EVENT) (event);
    }

    /**
     *  @brief  Method called when pointer button released.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button released. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonReleased (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::BUTTON_RELEASE_EVENT) (event);
    }

    /**
     *  @brief  Method called when pointer button clicked (pressed and 
     *  released).
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button cklicked. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonClicked (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::BUTTON_CLICK_EVENT) (event);
    }

};
}
#endif /* BWIDGETS_CLICKABLE_HPP_ */