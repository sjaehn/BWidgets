/* ValueVisualizable.hpp
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

#ifndef BWIDGETS_VALUEVISUALIZABLE_HPP_
#define BWIDGETS_VALUEVISUALIZABLE_HPP_

#include "Support.hpp"
#include "Visualizable.hpp"

namespace BWidgets
{

/**
 *  @brief  Interface class for value visualization in composite Valueable
 *  widgets.
 */
class ValueVisualizable : public Support
{
public:

    /**
     *  @brief  Enumeration of positions to visualize the widget value in
     *  composite Valueable widgets.
     */
    enum class ValuePosition
    {
        top,
        right,
        bottom,
        left,
        center
    };

protected:

    ValuePosition valuePosition_;

public:

    /**
     *  @brief  Constructs a default %ValueVisualizable object.
     */
    ValueVisualizable ();

    /**
     *  @brief  Constructs a %ValueVisualizable object.
     * 
     *  @param  status True if %ValueVisualizable, otherwise false.
     *  @param  pos  Position.
     */
    ValueVisualizable (const bool status, ValuePosition pos = ValuePosition::top);

    /**
     *  @brief  Switch the support for value visualization on/off. 
     *  @param status  True if on, otherwise false.
     *
     *  Defines if a %ValueVisualizable object should display its value
     *  (e. g., as a Label) or not. Note: It's the objects turn to implement
     *  a method to visualze the value. %setValueVisualizable also calls
     *  `Visualizable::update()` to update the display.
     */
    virtual void setValueVisualizable (const bool status) ;

    /**
     *  @brief  Information about the support for value visualization.
     *  @return  True if on, otherwise false.
     */
    bool isValueVisualizable () const;

    /**
     *  @brief  Sets the position of the visualized value.
     *  @param pos  Position.
     *
     *  Sets the position of the value to be visualized (e. g., as a Label).
     *  Note: It's the objects turn to implement a method to visualze the 
     *  value. %setValueVisualizable also calls `Visualizable::update()` to 
     *  update the display.
     */
    virtual void setValuePosition (ValuePosition pos = ValuePosition::top);

    /**
     *  @brief  Gets the position of the visualized value.
     *  @return Position.
     */
    ValuePosition getValuePosition () const;

};

inline ValueVisualizable::ValueVisualizable () : 
    ValueVisualizable (true)
{

}

inline ValueVisualizable::ValueVisualizable (const bool status, ValuePosition pos) :
    Support (status),
    valuePosition_ (pos)
{

}

inline void ValueVisualizable::setValueVisualizable (const bool status) 
{
    setSupport(status);
    Visualizable* v = dynamic_cast<Visualizable*>(this);
    if (v) v->update();
}

inline bool ValueVisualizable::isValueVisualizable () const {return getSupport();}

inline void ValueVisualizable::setValuePosition (ValuePosition pos)
{
    valuePosition_ = pos;
    Visualizable* v = dynamic_cast<Visualizable*>(this);
    if (v) v->update();
}

inline ValueVisualizable::ValuePosition ValueVisualizable::getValuePosition () const 
{
    return valuePosition_;
}

}
#endif /* BWIDGETS_VALUEVISUALIZABLE_HPP_ */