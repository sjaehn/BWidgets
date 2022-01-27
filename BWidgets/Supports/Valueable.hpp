/* Valueable.hpp
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

#ifndef BWIDGETS_VALUEABLE_HPP_
#define BWIDGETS_VALUEABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Supports a value and value changed events.
 */
class Valueable : virtual public Callback, public Support
{
protected:

public:

    /**
     *  @brief  Switch the support for value changed events on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether a widget may emit a ValueChangedEvent if its internal
     *  value is changed via its setValue() method. In this case, a 
     *  ValueChangedEvent with the type VALUE_CHANGED_EVENT will be scheduled 
     *  and send to the widget.
     */
    void setValueable (const bool status);

    /**
     *  @brief  Information about the support for value changed events.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is valueable, the main window event handler allows 
     *  the widget to emit a ValueChangedEvent of the type VALUE_CHANGED_EVENT 
     *  upon changing its value via setValue.
     */
    bool isValueable () const;

    /**
     *  @brief  Method when a ValueChangedEvent is received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  an emitted ValueChangedEvent. By default, it calls its static callback
     *  function.
     */
    virtual void onValueChanged (BEvents::Event* event);

};

inline void Valueable::setValueable (const bool status) 
{
    setSupport (status);
}

inline bool Valueable::isValueable () const 
{
    return getSupport();
}

inline void Valueable::onValueChanged (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::VALUE_CHANGED_EVENT) (event);
}

}
#endif /* BWIDGETS_VALUEABLE_HPP_ */