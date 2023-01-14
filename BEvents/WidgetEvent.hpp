/* WidgetEvent.hpp
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

#ifndef BEVENTS_WIDGETEVENT_HPP_
#define BEVENTS_WIDGETEVENT_HPP_

#include "Event.hpp"

namespace BEvents
{

 /**
  *  @brief  Widget action request event.
  *
  *  Widget events are emitted by an (event) widget if the widget is requested
  *  by an other (request) widget. This event class is typically used if 
  *  opening or closing of a window or an request widget is requested.
  */
 class WidgetEvent : public Event
 {
 protected:
 	BWidgets::Widget* requestWidget_;

 public:

    /**
     *  @brief  Creates an empty %WidgetEvent.
     */
 	WidgetEvent () :
 		WidgetEvent (nullptr, nullptr, EventType::None) 
    {

    }

    /**
     *  @brief  Creates a %WidgetEvent.
     *  @param eventWidget  Widget on which the event will be applied.
     *  @param requestWidget  Widget which requests the event for another one.
     *  @param type  EventType.
     */
 	WidgetEvent (BWidgets::Widget* eventWidget, BWidgets::Widget* requestWidget, const EventType type) :
 		Event (eventWidget, type),  
        requestWidget_ (requestWidget) 
    {

    }

 	/**
 	 *  @brief  Access to the widget which request the event.
 	 *  @return Pointer to the widget (read / write).
 	 */
 	BWidgets::Widget* getRequestWidget ()
 	{
         return requestWidget_;
    }

    /**
 	 *  @brief  Access to the widget which request the event.
 	 *  @return Pointer to the widget (read only).
 	 */
 	const BWidgets::Widget* getRequestWidget () const
 	{
         return requestWidget_;
    }

 };

}

#endif /* BEVENTS_WIDGETEVENT_HPP_ */
