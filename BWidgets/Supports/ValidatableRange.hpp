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

/**
 *  @brief  Validatable interface class to keep a value within a range.
 *  Specialization for std::pair.
 *  @tparam T1  First value type.
 *  @tparam T2  Second value type.
 *
 *  %ValidatableRange<std::pair<T1, T2>> keeps each element of a 
 *  std::pair<T1, T2> value within a range by independent comparison 
 *  operations.
 *
 *  @a T1 and @a T2 MUST support the standard comparison operators and the
 *  standard arithmetic operators. 
 *
 *  @todo Inverse range, negative step.
 */
template <class T1, class T2>
class ValidatableRange<std::pair<T1, T2>> : public Validatable<std::pair<T1, T2>>
{
protected:
    std::pair<T1, T2> min_;
    std::pair<T1, T2> max_;
    std::pair<T1, T2> step_;

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
    ValidatableRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max);

    /**
     *  @brief  Constructs a ValidatableRange object.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     *  @param step  Step.
     */
    ValidatableRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max, const std::pair<T1, T2>& step);

    /**
     *  @brief  Sets the range lower limit.
     *  @param min  Lower limit.
     */
    virtual void setMin (const std::pair<T1, T2>& min);

    /**
     *  @brief  Gets the range lower limit.
     *  @return  Lower limit.
     * 
     */
    virtual std::pair<T1, T2> getMin () const;

    /**
     *  @brief  Sets the range upper limit.
     *  @param min  Upper limit.
     */
    virtual void setMax (const std::pair<T1, T2>& max);

    /**
     *  @brief  Gets the range upper limit.
     *  @return  Upper limit.
     * 
     */
    virtual std::pair<T1, T2> getMax () const;

    /**
     *  @brief  Sets the range step size.
     *  @param min  Step size.
     */
    virtual void setStep (const std::pair<T1, T2>& step);

    /**
     *  @brief  Gets the range step size.
     *  @return  Step size.
     * 
     */
    virtual std::pair<T1, T2> getStep () const;

    /**
     *  @brief  Sets the value range.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     */
    virtual void setRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max);

    /**
     *  @brief  Sets the value range.
     *  @param min  Lower limit.
     *  @param max  Upper limit.
     *  @param step  Step.
     */
    virtual void setRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max, const std::pair<T1, T2>& step);

    /**
     *  @brief  Validates a value.
     *  @param value  Value to be validated.
     *  @return T  Validated value.
     */
    virtual std::pair<T1, T2> validate (const std::pair<T1, T2>& value);

    /**
     *  @brief  Gets the range position [0..1] from a value.
     *  @param value  Value.
     *  @param func  Optional, transfer function.
     *  @return  Ratio.
     */
    virtual std::pair<double, double> getRatioFromValue (const std::pair<T1, T2>& value, 
                                                         std::function<std::pair<T1, T2> (const std::pair<T1, T2>& x)> func = [] (const std::pair<T1, T2>& x) {return x;});

    /**
     *  @brief  Gets the value from a range position.
     *  @param ratio  Ratio.
     *  @param func  Optional, transfer function.
     *  @param revfunc  Optional, re-transfer function.
     *  @return  Value.
     */
    virtual std::pair<T1, T2> getValueFromRatio (const std::pair<double, double>& ratio, 
                                                 std::function<std::pair<T1, T2> (const std::pair<T1, T2>& x)> func = [] (const std::pair<T1, T2>& x) {return x;},
                                                 std::function<std::pair<T1, T2> (const std::pair<T1, T2>& x)> revfunc = [] (const std::pair<T1, T2>& x) {return x;});

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

template <class T1, class T2>
ValidatableRange<std::pair<T1, T2>>::ValidatableRange () :
    min_ (std::pair<T1, T2>()),
    max_ (std::pair<T1, T2>(T1() + 1.0, T2() + 1.0)),
    step_ (std::pair<T1, T2>())
{

}

template <class T1, class T2>
ValidatableRange<std::pair<T1, T2>>::ValidatableRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max) :
    min_ (min),
    max_ (max),
    step_ (std::pair<T1, T2>())
{

}

template <class T1, class T2>
ValidatableRange<std::pair<T1, T2>>::ValidatableRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max, const std::pair<T1, T2>& step) :
    min_ (min),
    max_ (max),
    step_ (step)
{
    
}

template <class T1, class T2>
void ValidatableRange<std::pair<T1, T2>>::setMin (const std::pair<T1, T2>& min)
{
    if (min_ != min)
    {
        // Change limits
        min_ = min;
        
        // Re-calculate value
        ValueableTyped<std::pair<T1, T2>>* v = dynamic_cast<ValueableTyped<std::pair<T1, T2>>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T1, class T2>
std::pair<T1, T2> ValidatableRange<std::pair<T1, T2>>::getMin () const
{
    return min_;
}

template <class T1, class T2>
void ValidatableRange<std::pair<T1, T2>>::setMax (const std::pair<T1, T2>& max)
{
    if (max_ != max)
    {
        // Change limits
        max_ = max;

        // Re-calculate value
        ValueableTyped<std::pair<T1, T2>>* v = dynamic_cast<ValueableTyped<std::pair<T1, T2>>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T1, class T2>
std::pair<T1, T2> ValidatableRange<std::pair<T1, T2>>::getMax () const
{
    return max_;
}

template <class T1, class T2>
void ValidatableRange<std::pair<T1, T2>>::setStep (const std::pair<T1, T2>& step)
{
    if (step_ != step)
    {
        // Change limits
        step_ = step;

        // Re-calculate value
        ValueableTyped<std::pair<T1, T2>>* v = dynamic_cast<ValueableTyped<std::pair<T1, T2>>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T1, class T2>
std::pair<T1, T2> ValidatableRange<std::pair<T1, T2>>::getStep () const
{
    return step_;
}

template <class T1, class T2>
void ValidatableRange<std::pair<T1, T2>>::setRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max)
{
    setRange (min, max, std::pair<T1, T2>());
}

template <class T1, class T2>
void ValidatableRange<std::pair<T1, T2>>::setRange (const std::pair<T1, T2>& min, const std::pair<T1, T2>& max, const std::pair<T1, T2>& step)
{
    if ((min_ != min) || (max_ != max) || (step_ != step))
    {
        // Change limits
        min_ = min;
        max_ = max;
        step_ = step;

        // Re-calculate value
        ValueableTyped<std::pair<T1, T2>>* v = dynamic_cast<ValueableTyped<std::pair<T1, T2>>*>(this);
        if (v) v->setValue (v->getValue()); 

        // Update
        Visualizable* w = dynamic_cast<Visualizable*>(this);
        if (w) w->update();
    }
}

template <class T1, class T2>
std::pair<T1, T2> ValidatableRange<std::pair<T1, T2>>::validate (const std::pair<T1, T2>& value) 
{
    if (!Validatable<std::pair<T1, T2>>::isValidatable()) return value;

    std::pair<T1, T2> result = value;
    
    if (getStep().first && (getMax().first >= getMin().first))
    {
        if (getStep().first > 0) result.first = getMin().first + round ((value.first - getMin().first) / getStep().first) * getStep().first;
        else result.first =  getMax().first - round ((getMax().first - value.first) / getStep().first) * getStep().first;
    }

    if (getStep().second && (getMax().second >= getMin().second))
    {
        if (getStep().second > 0) result.second = getMin().second + round ((value.second - getMin().second) / getStep().second) * getStep().second;
        else result.second =  getMax().second - round ((getMax().second - value.second) / getStep().second) * getStep().second;
    }

    return std::pair<T1, T2> (LIMIT (result.first, getMin().first, getMax().first), LIMIT (result.second, getMin().second, getMax().second));
}

template <class T1, class T2>
std::pair <double, double> ValidatableRange<std::pair<T1, T2>>::getRatioFromValue   (const std::pair<T1, T2>& value, 
                                                                                     std::function<std::pair<T1, T2> (const std::pair<T1, T2>& x)> func)
{
    const std::pair<T1, T2> min (func (getMin()));
	const std::pair<T1, T2> max (func (getMax()));
	return std::pair<T1, T2>    ((min.first != max.first ? (func (value).first - min.first) / (max.first - min.first) : 0.0),
                                 (min.second != max.second ? (func (value).second - min.second) / (max.second - min.second) : 0.0));
}

template <class T1, class T2>
std::pair<T1, T2> ValidatableRange<std::pair<T1, T2>>::getValueFromRatio    (const std::pair<double, double>& ratio, 
                                                                             std::function<std::pair<T1, T2> (const std::pair<T1, T2>& x)> func, 
                                                                             std::function<std::pair<T1, T2> (const std::pair<T1, T2>& x)> revfunc)
{
    const std::pair<T1, T2> min (func (getMin()));
	const std::pair<T1, T2> max (func (getMax()));
	return std::pair<double, double>    (revfunc (std::pair<T1, T2> (ratio.first * (max.first - min.first) + min.first, 
                                                                     ratio.second * (max.second - min.second) + min.second)));
}


}
#endif /* BWIDGETS_VALIDATABLERANGE_HPP_ */