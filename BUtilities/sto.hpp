/* sto.hpp
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

#ifndef BUTILITIES_STO_HPP_
#define BUTILITIES_STO_HPP_

#include <string>
#include <stdexcept>

namespace BUtilities 
{

/**
 *  @brief  Converts a floating point number-containing string to a
 *  foloating point value of the respective type.
 *  @param str  Floating point number-containing string.
 *  @param idx  Index of the first character after the converted floating
 *  point number.
 *  @return  Converted floating point value.
 *  @throw std::invalid_argument  Throws an exception if @a str doesn't start
 *  with a number.
 *
 *  Similar to std::sto(f/d/...). But this method is tolerant over different
 *  types of decimal signs (point / comma).
 */
template<class T> inline T sto (const std::string& str, size_t* idx = 0);

template<class T> inline T sto (const std::string& str, size_t* idx)
{
        const std::string numbers = "0123456789";
        bool isNumber = false;
        T sign = 1.0f;
        T predec = 0.0f;
        T dec = 0.0f;
        T decfac = 0.1f;
        size_t i = 0;

        // Ignore spaces before
        while (str[i] == ' ') ++i;

        // Check sign
        if ((str[i] == '+') || (str[i] == '-'))
        {
                if (str[i] == '-') sign = -1.0;
                ++i;
        }

        // Interpret pre-decimal digits
        while ((str[i] != 0) && (numbers.find_first_of (str[i]) != std::string::npos))
        {
                predec = predec * 10.0 + str[i] - '0';
                ++i;
                isNumber = true;
        }

        // Check decimal sign
        if ((str[i] == '.') || (str[i] == ','))
        {
                ++i;

                // Interpret decimal digits
                while ((str[i] != 0) && (numbers.find_first_of (str[i]) != std::string::npos))
                {
                        dec += (str[i] - '0') * decfac;
                        decfac *= 0.1;
                        ++i;
                        isNumber = true;
                }
        }

        // Communicate next position
        if (idx != nullptr) *idx = i;

        // Not a number: invalid argument exception
        if (!isNumber) throw std::invalid_argument (str + " is not a number");

        return sign * (predec + dec);
}

}

#endif /* BUTILITIES_STO_HPP_ */
