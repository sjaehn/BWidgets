/* Status.hpp
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
#ifndef BSTYLES_STATUS_HPP_
#define BSTYLES_STATUS_HPP_

namespace BStyles 
{

/**
 *  @brief  Enumeration of object states.
 */
enum class Status
{
    normal,
    active,
    inactive,
    off,
    userDefined
};

}

#endif /* BSTYLES_STATUS_HPP_ */