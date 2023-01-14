/* Validatable.hpp
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

#ifndef BWIDGETS_VALIDATABLE_HPP_
#define BWIDGETS_VALIDATABLE_HPP_

#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Base Interface class for Support of value validation for Valuable 
 *  objects.
 *  @tparam T  Value type.
 *
 *  This class need to be specialized. Value type MUST be the same type as in
 *  Valuable.
 */
template <class T>
class Validatable : public Support
{
public:

    /**
     *  @brief  Switch the support for value validation on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setValidatable (const bool status);

    /**
     *  @brief  Information about the support for value validation.
     *  @return  True if on, otherwise false.
     */
    bool isValidatable () const;

    /**
     *  @brief  Validates a value.
     *  @param value  Value to be validated.
     *  @return T  Validated value.
     */
    virtual T validate (const T& value) = 0;

};

template <class T>
inline void Validatable<T>::setValidatable (const bool status)
{
    setSupport(status);
}

template <class T>
inline bool Validatable<T>::isValidatable () const 
{
    return getSupport();
}

}
#endif /* BWIDGETS_VALIDATABLE_HPP_ */