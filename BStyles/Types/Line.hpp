/* Line.hpp
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

#ifndef BSTYLES_LINE_HPP_
#define BSTYLES_LINE_HPP_

#include "Color.hpp"

namespace BStyles
{

/**
 *  @brief A %Line, defined by its color and its width.
 *
 *  Line styles are used for borders, tables, ...
 */
struct Line
{
	Color color;
	int width;

    /**
     *  @brief  Creates an "empty" (= invisible, 0pt) %Line.
     */
	constexpr Line () : Line (Color(), 0.0) {}

    /**
     *  @brief  Creates a %Line from the passed @a color and @a width.
     *  @param color  Color of the %Line.
     *  @param width  Width of the %Line in pts.
     */
	constexpr Line (const Color& color, const double width) :
        color (color), width (width) {}

    bool operator== (const Line& that) const 
    {
        return (color == that.color) && (width == that.width);
    }

	bool operator!= (const Line& that) const {return !operator== (that);}
};

constexpr Line blackLine1pt = Line (black, 1.0);
constexpr Line whiteLine1pt = Line (white, 1.0);
constexpr Line greyLine1pt = Line (grey, 1.0);
constexpr Line lightgreyLine1pt = Line (lightgrey, 1.0);
constexpr Line noLine = Line (invisible, 0.0);
constexpr Line shadow80Line2pt = Line (Color (0.0, 0.0, 0.0, 0.8), 2.0);
constexpr Line shadow50Line2pt = Line (Color (0.0, 0.0, 0.0, 0.5), 2.0);
constexpr Line shadow20Line2pt = Line (Color (0.0, 0.0, 0.0, 0.2), 2.0);

}

#endif /* BSTYLES_LINE_HPP_ */
