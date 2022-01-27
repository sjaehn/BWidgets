/* ValueableTyped.hpp
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

#ifndef BWIDGETS_VALUEABLETYPED_HPP_
#define BWIDGETS_VALUEABLETYPED_HPP_

#include "Valueable.hpp"
#include "ValueTransferable.hpp"
#include "Validatable.hpp"
#include "../Window.hpp"
#include "../../BEvents/ValueChangeTypedEvent.hpp"

namespace BWidgets
{

/**
 *  @brief  Supports a value and value changed events.
 *  @tparam T  Value type.
 */
template <class T>
class ValueableTyped : public Valueable
{
protected:
    T value_;

public:

    /**
     *  @brief  Constructs a default %ValueableTyped object.
     */
    ValueableTyped () = default;

    /**
     *  @brief  Construct a new %ValueableTyped object.
     *  @param value  Value.
     */
    ValueableTyped (const T& value);

    /**
     *  @brief  Copiess the value from another %ValueableTyped object.
     *  @param value  Value.
     *
     *  Also emits a ValueChangeTyped<T> event.
     */
    virtual void setValue (const ValueableTyped<T>& that);

    /**
     *  @brief  Changes the value.
     *  @param value  Value.
     *
     *  Also emits a ValueChangeTyped<T> event.
     */
    virtual void setValue (const T& value);

    /**
     *  @brief  Gets the value.
     *  @return  Value. 
     */
    T getValue ();

    /**
	 *  @brief  Lets a %Widget emit a ValueChangeTypedEvent.
	 *
	 *  Emits a ValueChangeTypedEvent of the type VALUE_CHANGED_EVENT to the 
     *  main Window event queue. 
	 */
    void emitValueChanged ();

};

template<class T>
ValueableTyped<T>::ValueableTyped (const T& value) :
    Valueable (),
    value_ (value)
{

}

template<class T>
void ValueableTyped<T>::setValue (const ValueableTyped<T>& that)
{
    setValue (that.value_);
}

template<class T>
void ValueableTyped<T>::setValue (const T& value)
{
    // Validate
    Validatable<T>* validatable = dynamic_cast<Validatable<T>*>(this);
    T nval = (validatable && validatable->isValidatable() ? validatable->validate (value) : value);

    // Set new value_
    if (value_ != nval)
    {
        value_ = nval;
        emitValueChanged();
        if (dynamic_cast<Widget*>(this)) dynamic_cast<Widget*>(this)->update();
    }
}

template<class T>
T ValueableTyped<T>::getValue ()
{
    return value_;
}

template<class T>
void ValueableTyped<T>::emitValueChanged ()
{
    Widget* thisWidget = dynamic_cast<Widget*>(this);
    if (!thisWidget) return;
    
    if (thisWidget->getMainWindow())
	{
		BEvents::ValueChangeTypedEvent<T>* event = new BEvents::ValueChangeTypedEvent<T> (thisWidget, value_);
		thisWidget->getMainWindow()->addEventToQueue (event);
	}
}

}
#endif /* BWIDGETS_VALUEABLETYPED_HPP_ */