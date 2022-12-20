/* to_string.hpp
 * Copyright (C) 2019 - 2022  Sven Jähnichen
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

#ifndef BUTILITIES_TO_STRING_HPP_
#define BUTILITIES_TO_STRING_HPP_

#include <string>
#include <sstream>

namespace BUtilities 
{

/**
 *  @brief  Converts a floaing point number into a string output with a
 *  defined format. 
 *  @param value  Floating point number.
 *  @param format  Format specifier, see printf.
 *  @return  Converted number as a string.
 *
 *  Similar to std::to_string. But the format specifier @a format allows a
 *  formatted value output.
 */
std::string to_string (const double value, std::string format = "%f");

inline std::string to_string (const double value, std::string format)
{
	char c[64];
	snprintf (c, 64, format.c_str (), value);
	std::string str = c;
	return c;
}

}

#endif /* BUTILITIES_TO_STRING_HPP_ */
