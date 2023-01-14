/* mix.hpp
 * Copyright (C) 2020 - 2023  Sven Jähnichen
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

#ifndef BUTILITIES_MIX_HPP_
#define BUTILITIES_MIX_HPP_

namespace BUtilities 
{

/**
 *  @brief  Mixes two values in a given ratio.
 *  @tparam T  Value type.
 *  @param t0  First value.
 *  @param t1  Second value.
 *  @param ratio  Ratio.
 *  @return T  Mixed value.
 */
template <class T> 
inline T mix (const T& t0, const T& t1, const double ratio)
{
        return t1 * ratio + t0 * (1.0 - ratio);
}

}

#endif /* BUTILITIES_MIX_HPP_ */
