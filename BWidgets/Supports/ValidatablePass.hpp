/* ValidatablePass.hpp
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

#ifndef BWIDGETS_VALIDATABLEPASS_HPP_
#define BWIDGETS_VALIDATABLEPASS_HPP_

#include "Validatable.hpp"

namespace BWidgets
{

/**
 *  @brief  Validatable interface class that assumes that all values to be
 *  valid.
 *  @tparam T  Value type.
 */
template <class T>
class ValidatablePass : public Validatable<T>
{
public:
    /**
     *  @brief  Validates a value.
     *  @param value  Value to be validated.
     *  @return T  Validated value.
     */
    virtual T validate (const T& value) {return value;}

};

}
#endif /* BWIDGETS_VALIDATABLEPASS_HPP_ */