/* ValueChangeTypedEvent.hpp
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

#ifndef BEVENTS_VALUECHANGETYPEDEVENT_HPP_
#define BEVENTS_VALUECHANGETYPEDEVENT_HPP_

#include "Event.hpp"
#include "ValueChangedEvent.hpp"

namespace BEvents
{

/**
 *  @brief  Event to communicate a changed value of ValueWidgets.
 *  @tparam  Value type (default = float)
 *
 *  Specialization of ValueChangedEvent. %ValueChangeTypedEvent additionally
 *  contains a copy of the value from the time of emission of the event.
 */
template <typename T = float>
class ValueChangeTypedEvent : public ValueChangedEvent
{
protected:
	T value_;

public:

    /**
     *  @brief  Creates an empty %ValueChangeTypedEvent.
     */
	ValueChangeTypedEvent () :
		ValueChangeTypedEvent (nullptr, 0.0) 
    {

    }

    /**
     *  @brief  Creates a %ValueChangeTypedEvent.
     *  @param widget  Pointer to the widget which caused the %Event.
     *  @param value  Value.
     */
	ValueChangeTypedEvent (BWidgets::Widget* widget, const T value) :
		ValueChangedEvent (widget), 
        value_ (value) 
    {

    }

    /**
	 *  @brief  Redefines the value exposed by the event by the value from
     *  another event. 
	 *  @param that  Other event.
     *
     *  The value is only redefined if @a that is comaptible to @a this .
     *  Note: This method doesn't change the value within a widget!
	 */
    virtual void setValue (Event* that) override
    {
        if (dynamic_cast<ValueChangeTypedEvent<T>*>(that)) setValue (dynamic_cast<ValueChangeTypedEvent<T>*>(that)->value_);
    }

	/**
	 *  @brief  Redefines the value exposed by the event. 
	 *  @param val  New value.
     *
     *  Note: This method doesn't change the value within a widget!
	 */
	virtual void setValue (const T val)
	{
        value_ = val;
    }

	/**
	 *  Gets the value exposed by the event.
	 *  @return Value of the event.
	 */
	T getValue () const
	{
        return value_;
    }
};

}

#endif /* BEVENTS_VALUECHANGETYPEDEVENT_HPP_ */
