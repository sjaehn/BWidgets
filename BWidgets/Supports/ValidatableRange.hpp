/* ValidatableRange.hpp
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

#ifndef BWIDGETS_VALIDATABLERANGE_HPP_
#define BWIDGETS_VALIDATABLERANGE_HPP_

#include <functional>
#include "ValueableTyped.hpp"
#include "Validatable.hpp"
#include "Visualizable.hpp"

#ifndef LIMIT
#define LIMIT(val, min, max) (val < min ? min : (val > max ? max : val))
#endif /* LIMIT */

namespace BWidgets
{

/**
 *  @brief  Validatable interface class to keep a value within a range.
 *  @tparam T  Value type.
 *
 *  @a T MUST support the comparison operators and MUST be comparable with 0.0
 *  and 1.0. 
 *
 *  @todo Inverse range, negative step.
 */
template <class T>
class ValidatableRange : public Validatable<T>
{
protected:
    T min_;
    T max_;
    T step_;

public:

    /**
     *  @brief  Constructs a default ValidatableRange object.
     */
    ValidatableRange ();

    /**
     *  @brief  Constructs a ValidatableRange object.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     */
    ValidatableRange (const T& min, const T& max);

    /**
     *  @brief  Constructs a ValidatableRange object.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     *  @param step  Step.
     */
    ValidatableRange (const T& min, const T& max, const T& step);

    /**
     *  @brief  Sets the range lower limit.
     *  @param min  Lower limit.
     */
    virtual void setMin (const T& min);

    /**
     *  @brief  Gets the range lower limit.
     *  @return  Lower limit.
     * 
     */
    virtual T getMin () const;

    /**
     *  @brief  Sets the range upper limit.
     *  @param min  Upper limit.
     */
    virtual void setMax (const T& max);

    /**
     *  @brief  Gets the range upper limit.
     *  @return  Upper limit.
     * 
     */
    virtual T getMax () const;

    /**
     *  @brief  Sets the range step size.
     *  @param min  Step size.
     */
    virtual void setStep (const T& step);

    /**
     *  @brief  Gets the range step size.
     *  @return  Step size.
     * 
     */
    virtual T getStep () const;

    /**
     *  @brief  Sets the value range.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     */
    virtual void setRange (const T& min, const T& max);

    /**
     *  @brief  Sets the value range.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     *  @param step  Step.
     */
    virtual void setRange (const T& min, const T& max, const T& step);

    /**
     *  @brief  Validates a value.
     *  @param value  Value to be validated.
     *  @return T  Validated value.
     */
    virtual T validate (const T& value);

    /**
     *  @brief  Gets the range position [0..1] from a value.
     *  @param value  Value.
     *  @param func  Optional, transfer function.
     *  @return  Ratio.
     */
    virtual double getRatioFromValue (const T& value, std::function<T (const T& x)> func = [] (const T& x) {return x;});

    /**
     *  @brief  Gets the value from a range position.
     *  @param ratio  Ratio.
     *  @param func  Optional, transfer function.
     *  @param revfunc  Optional, re-transfer function.
     *  @return  Value.
     */
    virtual T getValueFromRatio (const double ratio, 
                                 std::function<T (const T& x)> func = [] (const T& x) {return x;},
                                 std::function<T (const T& x)> revfunc = [] (const T& x) {return x;});

};

template <class T>
ValidatableRange<T>::ValidatableRange () :
    min_ (T()),
    max_ (T() + 1.0),
    step_ (T())
{

}

template <class T>
ValidatableRange<T>::ValidatableRange (const T& min, const T& max) :
    min_ (min),
    max_ (max),
    step_ (T())
{

}

template <class T>
ValidatableRange<T>::ValidatableRange (const T& min, const T& max, const T& step) :
    min_ (min),
    max_ (max),
    step_ (step)
{
    
}

template <class T>
void ValidatableRange<T>::setMin (const T& min)
{
    if (min_ != min)
    {
        // Change limits
        min_ = min;
        
        // Re-calculate value
        ValueableTyped<T>* v = dynamic_cast<ValueableTyped<T>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T>
T ValidatableRange<T>::getMin () const
{
    return min_;
}

template <class T>
void ValidatableRange<T>::setMax (const T& max)
{
    if (max_ != max)
    {
        // Change limits
        max_ = max;

        // Re-calculate value
        ValueableTyped<T>* v = dynamic_cast<ValueableTyped<T>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T>
T ValidatableRange<T>::getMax () const
{
    return max_;
}

template <class T>
void ValidatableRange<T>::setStep (const T& step)
{
    if (step_ != step)
    {
        // Change limits
        step_ = step;

        // Re-calculate value
        ValueableTyped<T>* v = dynamic_cast<ValueableTyped<T>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T>
T ValidatableRange<T>::getStep () const
{
    return step_;
}

template <class T>
void ValidatableRange<T>::setRange (const T& min, const T& max)
{
    setRange (min, max, T());
}

template <class T>
void ValidatableRange<T>::setRange (const T& min, const T& max, const T& step)
{
    if ((min_ != min) || (max_ != max) || (step_ != step))
    {
        // Change limits
        min_ = min;
        max_ = max;
        step_ = step;

        // Re-calculate value
        ValueableTyped<T>* v = dynamic_cast<ValueableTyped<T>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T>
T ValidatableRange<T>::validate (const T& value) 
{
    if (!Validatable<T>::isValidatable()) return value;
    
    if (getStep() && (getMax() >= getMin()))
    {
        if (getStep() > 0) return LIMIT (getMin() + round ((value - getMin()) / getStep()) * getStep(), getMin(), getMax());
        return LIMIT (getMax() - round ((getMax() - value) / getStep()) * getStep(), getMin(), getMax());
    }

    return LIMIT (value, getMin(), getMax());
}

template <class T>
double ValidatableRange<T>::getRatioFromValue (const T& value, std::function<T (const T& x)> func)
{
    const T min = func (getMin());
	const T max = func (getMax());
	return (min != max ? (func (value) - min) / (max - min) : 0.0);
}

template <class T>
T ValidatableRange<T>::getValueFromRatio (const double ratio, std::function<T (const T& x)> func, std::function<T (const T& x)> revfunc)
{
    const T min = func (getMin());
	const T max = func (getMax());
	return revfunc (ratio * (max - min) + min);
}

}
#endif /* BWIDGETS_VALIDATABLERANGE_HPP_ */