/* ColorMap.hpp
 * Copyright (C) 2018 - 2021  Sven Jähnichen
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

#ifndef BSTYLES_COLORMAP_HPP_
#define BSTYLES_COLORMAP_HPP_

#include <initializer_list>
#include <map>
#include "Color.hpp"
#include "../Status.hpp"

namespace BStyles 
{

/**
 *  @brief  Map of BStyles::Color, indexed by BStyles::Status
 *
 *  A %ColorMap is derived from std::map and all its methods can be used here
 *  too. A %ColorMap can additionally be initialized from a 
 *  @c std::vector<BStyles::Color>.
 */
class ColorMap : public std::map<Status, Color>
{
public:

    /**
     *  @brief  Creates a %ColorMap with no elements.
     */
    ColorMap () = default;

    /**
     *  @brief  Creates a %ColorMap from a std::vector of BStyles::Color.
     *  @param colors  Initializer list of BStyles::Color containing a 
     *  continuous dataset of colors starting with BStyles::NORMAL.
     *
     *  Data from the @a colors vector are copy construted.
     */
    ColorMap (const std::initializer_list<const Color>& colors)
    {
        size_t i = 0;
        for (const Color& c : colors)
        {
            operator[](static_cast<Status>(i)) = c;
            ++i;
        }
    }
};

const ColorMap reds = ColorMap ({red, lightred, darkred, black});
const ColorMap greens = ColorMap ({green, lightgreen, darkgreen, black});
const ColorMap blues = ColorMap ({blue, lightblue, darkblue, black});
const ColorMap greys = ColorMap ({grey, lightgrey, darkgrey, black});
const ColorMap whites = ColorMap ({lightlightgrey, white, lightgrey, black});
const ColorMap darks = ColorMap ({darkgrey, grey, darkdarkgrey, black});
const ColorMap lights = ColorMap ({lightgrey, lightlightgrey, grey, darkgrey});

}

#endif /* BSTYLES_COLORMAP_HPP_ */