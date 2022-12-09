/* Scrollable.hpp
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

#ifndef BWIDGETS_SCROLLABLE_HPP_
#define BWIDGETS_SCROLLABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  (Mouse) wheel scroll support.
 */
class Scrollable : virtual public Callback, public Support
{
public:
    /**
     *  @brief  Switch (mouse) wheel support on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether the widget may emit a WHEEL_SCROLL_EVENT if the main 
     *  window event handler received a (mouse) wheel scroll event from the 
     *  host system. In this case, a WheelEvent with the type 
     *  WHEEL_SCROLL_EVENT will be scheduled and send to the widget.
     */
    virtual void setScrollable (const bool status) {setSupport (status);}

    /**
     *  @brief  Information about the (mouse) wheel support.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is scrollable, the main window event handler let the widget
     *  emit a WheelEvent of the type WHEEL_SCROLL_EVENT if the main window
     *  event handler received a (mouse) wheel event from the host system.
     */
    bool isScrollable () const {return getSupport();}

    /**
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. By default, it calls its static callback
     *  function.
     */
    virtual void onWheelScrolled (BEvents::Event* event)
    {
        callback (BEvents::Event::EventType::WHEEL_SCROLL_EVENT) (event);
    }

};

}
#endif /* BWIDGETS_SCROLLABLE_HPP_ */