/* ValueChangedEvent.hpp
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

#ifndef BEVENTS_VALUECHANGEDEVENT_HPP_
#define BEVENTS_VALUECHANGEDEVENT_HPP_

#include "Event.hpp"

namespace BEvents
{

/**
 *  @brief  Event to communicate a changed value of ValueWidgets.
 *
 *  A %ValueChangedEvent is emitted by widgets if their respective
 *  @c setValue() method is called. 
 *
 *  %ValueChangedEvents can be handled internally (e.g., by composite widgets)
 *  and can also be redirected to external callback functions.
 *
 *  %ValueChangedEvent shoud be specialized by ValueChangeTypedEvent.
 */
class ValueChangedEvent : public Event
{
protected:

public:

    /**
     *  @brief  Creates an empty %ValueChangedEvent.
     */
	ValueChangedEvent () :
		ValueChangedEvent (nullptr) 
    {

    }

    /**
     *  @brief  Creates a %ValueChangedEvent.
     *  @param widget  Pointer to the widget which caused the %Event.
     */
	ValueChangedEvent (BWidgets::Widget* widget) :
		Event (widget, VALUE_CHANGED_EVENT)
    {
    
    }

	/**
	 *  @brief  Redefines the value exposed by the event by the value from
     *  another event. 
	 *  @param that  Other event.
     *
     *  Note: This method doesn't change the value within a widget!
	 */
	virtual void setValue (Event* that)
    {

    }
};

}

#endif /* BEVENTS_VALUECHANGEDEVENT_HPP_ */
