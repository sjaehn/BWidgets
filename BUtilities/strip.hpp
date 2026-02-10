/* strip.hpp
 * Copyright (C) 2020 - 2026  Sven Jähnichen
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

#ifndef BUTILITIES_STRIP_HPP_
#define BUTILITIES_STRIP_HPP_

#include <algorithm>
#include <string>

namespace BUtilities 
{

/**
 *  @brief  Strips all leading whitespaces.
 *  @param s  String.
 */
inline void lstrip(std::string& s) 
{
    s.erase     (
                        s.begin(), std::find_if(s.begin(), s.end(), 
                        [](unsigned char ch) {return !std::isspace(ch);
                }));
}

/**
 *  @brief  Strips all tailing whitespaces.
 *  @param s  String.
 */
inline void rstrip(std::string& s) 
{
    s.erase     (
                        std::find_if(s.rbegin(), s.rend(), 
                        [](unsigned char ch) {return !std::isspace(ch);
                }).base(), s.end());
}

/**
 *  @brief  Strips whitespaces from both sides.
 *  @param s  String.
 */
inline void strip(std::string& s)
{
        lstrip(s);
        rstrip(s);
}

}

#endif /* BUTILITIES_STRIP_HPP_ */
