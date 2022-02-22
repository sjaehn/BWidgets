/* Border.hpp
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

#ifndef BSTYLES_BORDER_HPP_
#define BSTYLES_BORDER_HPP_

#include "Line.hpp"

namespace BStyles
{

/**
 *  @brief  A %Border, defined by a line style, padding, margin, and corner 
 *  radius.
 *  and its width.
 */
struct Border
{
	Line line;
	double margin;
	double padding;
	double radius;

    /**
     *  @brief  Creates an "empty" (= invisible, 0pt) %Border.
     */
	constexpr Border () :Border (Line ()) {}

    /**
     *  @brief  Creates a %Border from the passed parameters.
     *  @param line  Line style.
     *  @param margin  Optional, in pts.
     *  @param padding  Optional, in pts.
     *  @param radius  Optional, corner radius in pts.
     */
	constexpr Border (const Line& line, double margin = 0.0, double padding = 0.0, double radius = 0.0) :
        line (line), margin (margin), padding (padding), radius (radius) {}

    bool operator== (const Border& that) const 
    {
        return (line == that.line) && (margin == that.margin) && (padding == that.padding) && (radius == that.radius);
    }

	bool operator!= (const Border& that) const {return !operator== (that);}
};

constexpr Border blackBorder1pt = Border (blackLine1pt);
constexpr Border whiteBorder1pt = Border (whiteLine1pt);
constexpr Border greyBorder1pt = Border (greyLine1pt);
constexpr Border lightgreyBorder1pt = Border (lightgreyLine1pt);
constexpr Border noBorder = Border (noLine);
constexpr Border shadow80Border2pt = Border (shadow80Line2pt);
constexpr Border shadow50Border2pt = Border (shadow50Line2pt);
constexpr Border shadow20Border2pt = Border (shadow20Line2pt);

}

#endif /* BSTYLES_BORDER_HPP_ */
