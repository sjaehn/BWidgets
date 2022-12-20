/* Messagable.hpp
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

#ifndef BWIDGETS_MESSAGABLE_HPP_
#define BWIDGETS_MESSAGABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"
#include <string>
#include "../../BUtilities/Any.hpp"

namespace BWidgets
{

/**
 *  @brief  Custom message event support.
 */
class Messagable : virtual public Callback, public Support
{
public:
    /**
     *  @brief  Switch the support for custom message events on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether the widget may emit a MessagEvent. In this case, 
     *  a MessageEvent with the type MESSAGE_EVENT will be scheduled and 
     *  send to the widget.
     */
    virtual void setMessagable (const bool status);

    /**
     *  @brief  Information about the support for custom message events.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is messagable, the main window event handler let the widget
     *  emit a MessageEvent of the type MESSAGE_EVENT.
     */
    bool isMessagable () const;


    /**
     *  @brief  Emits a MessageEvent. 
     *  @param name  Event name.
     *  @param content  Event data.
     */
    virtual void postMessage (const std::string& name, const BUtilities::Any content);

    /**
     *  @brief  Method when a MessageEvent is received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  an emitted MessageEvent. By default, it calls its static callback
     *  function.
     */
    virtual void onMessage (BEvents::Event* event);

};

}
#endif /* BWIDGETS_MESSAGABLE_HPP_ */