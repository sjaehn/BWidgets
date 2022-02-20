/* Area.hpp
 * Beat / envelope shaper LV2 plugin
 *
 * Copyright (C) 2019 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef BUTILITIES_AREA_HPP_
#define BUTILITIES_AREA_HPP_

#include "Point.hpp"

namespace BUtilities
{

/**
 *  @brief  2D coordinates of a rectangular area.
 *  @tparam T  Data type of the coordinates.
 */
template <class T = double>
class Area
{
protected:
	Point<T> p1, p2;

public:
	/**
	 *  @brief  Constructs a new %Area object with default (origin) 
	 *  coordinates.
	 */
	Area () : Area (Point<T> (), Point<T> ()) {}

	/**
	 *  @brief  Constructs a new %Area object from the provided coordinates
	 *  and extends.
	 *  @param x1  X origin.
	 *  @param y1  Y origin.
	 *  @param width  %Area width.
	 *  @param height  %Area height.
	 */
	Area (const T x1, const T y1, const T width, const T height) :
		Area (Point<T> (x1, y1), Point<T> (x1 + width, y1 + height)) {}

	/**
	 *  @brief  Constructs a new %Area object from two provided Point 
	 *  coordinates.
	 *  @param p1  First point.
	 *  @param p2  Second point.
	 */
	Area (const Point<T>& p1, const Point<T>& p2) :
		p1 (Point<T> ((p1.x < p2.x ? p1.x : p2.x), (p1.y < p2.y ? p1.y : p2.y))),
		p2 (Point<T> ((p1.x > p2.x ? p1.x : p2.x), (p1.y > p2.y ? p1.y : p2.y)))
	{}

	/**
	 *  @brief  Gets the position of the %Area.
	 *  @return  Position as Point coordinates.
	 */
	Point<T> getPosition () const {return p1;}
	T getX () const {return p1.x;}
	T getY () const {return p1.y;}

	/**
	 *  @brief  Gets the extends of the %Area.
	 *  @return  Extends as Point extends.
	 */
	Point<T> getExtends () const {return Point<T> (p2.x - p1.x, p2.y - p1.y);}

	/**
	 *  @brief Gets the width of the %Area.
	 *  @return Width. 
	 */
	T getWidth () const {return (p2.x - p1.x);}

	/**
	 *  @brief Gets the height of the %Area.
	 *  @return Height. 
	 */
	T getHeight () const {return (p2.y - p1.y);}

	/**
	 *  @brief  Moves the %Area horizontally. 
	 *  @param x  New X position.
	 */
	void setX (const T x) {moveTo (x, getY());}

	/**
	 *  @brief  Moves the %Area vertically. 
	 *  @param y  New Y position.
	 */
	void setY (const T y) {moveTo (getX(), y);}

	/**
	 *  @brief  Moves the %Area. 
	 *  @param x  New X position.
	 *  @param y  New Y position.
	 */
	void moveTo (const T x, const T y) {moveTo (Point<T> (x, y));}

	/**
	 *  @brief  Moves the %Area. 
	 *  @param position  New position.
	 */
	void moveTo (const Point<T>& position)
	{
		p2 = p2 - p1 + position;
		p1 = position;
	}

	/**
	 *  @brief  Resizes the %Area horizontally.
	 *  @param width  New width.
	 */
	void setWidth (const T width) {resize (width, getHeight());}

	/**
	 *  @brief  Resizes the %Area vertically.
	 *  @param height  New height.
	 */
	void setHeight (const T height) {resize (getWidth(), height);}

	/**
	 *  @brief  Resizes the %Area.
	 *  @param width  New width.
	 *  @param height  New height.
	 */
	void resize (const T width, const T height) {resize (Point<T> (width, height));}

	/**
	 *  @brief  Resizes the %Area.
	 *  @param extends  New extends.
	 */
	void resize (const Point<T>& extends) {p2 = p1 + extends;}

	/**
	 *  @brief  Tests if a Point is inside the %Area. 
	 *  @param p  Point.
	 *  @return  True, if @a p is inside the %Area, otherwise false.
	 */
	bool contains (const Point<T>& p) const
	{
		return ((p.x >= p1.x) && (p.x <= p2.x) && (p.y >= p1.y) && (p.y <= p2.y));
	}

	/**
	 *  @brief  Tests if another %Area is fully included this %Area. 
	 *  @param ra  Other %Area.
	 *  @return  True, if @a ra is included this %Area, otherwise false.
	 */
	bool includes (const Area& ra) const
	{
		return ((ra.p1.x >= p1.x) && (ra.p1.y >= p1.y) && (ra.p2.x <= p2.x) && (ra.p2.y <= p2.y));
	}

	/**
	 *  @brief  Tests if another %Area overlaps this %Area. 
	 *  @param ra  Other %Area.
	 *  @return  True, if @a ra overlaps this %Area, otherwise false.
	 */
	bool overlaps (const Area& ra) const
	{
		return !((ra.p2.x < p1.x) || (ra.p2.y < p1.y) || (ra.p1.x > p2.x) || (ra.p1.y > p2.y));
	}

	/**
	 *  @brief  Resizes this %Area to fully include another %Area.
	 *  @param ra  Other %Area.
	 */
	void extend (const Area& ra)
	{
		if (ra != Area ())
		{
			p1 = Point<T> ((p1.x < ra.p1.x ? p1.x : ra.p1.x), (p1.y < ra.p1.y ? p1.y : ra.p1.y));
			p2 = Point<T> ((p2.x > ra.p2.x ? p2.x : ra.p2.x), (p2.y > ra.p2.y ? p2.y : ra.p2.y));
		}
	}

	/**
	 *  @brief  Changes this %Area to the intersaction of this and another 
	 *  %Area.
	 *  @param ra  Other %Area.
	 */
	void intersect (const Area& ra)
	{
		if ((*this == Area ()) || (ra == Area ()) || (!overlaps (ra))) *this = Area ();

		else
		{
			T x1 = (ra.p1.x < p1.x ? p1.x : ra.p1.x);
			T y1 = (ra.p1.y < p1.y ? p1.y : ra.p1.y);
			T x2 = (ra.p2.x > p2.x ? p2.x : ra.p2.x);
			T y2 = (ra.p2.y > p2.y ? p2.y : ra.p2.y);
			p1 = Point<T> (x1, y1);
			p2 = Point<T> (x2, y2);
		}
	}

	/**
	 *  @brief  Resizes this %Area to fully include another %Area. 
	 *  @param rhs  Other %Area.
	 *  @return  Result of %Area extention.
	 */
	Area& operator+= (const Area& rhs)
	{
		this->extend (rhs);
		return *this;
	}

	/**
	 *  @brief  Changes this %Area to intersect with another %Area. 
	 *  @param rhs  Other %Area.
	 *  @return  Result of %Area intersection.
	 */
	Area& operator*= (const Area& rhs)
	{
		this->intersect (rhs);
		return *this;
	}

	friend bool operator== (const Area& lhs, const Area& rhs)
	{
		return ((lhs.p1 == rhs.p1) && (lhs.p2 == rhs.p2));
	}

	friend bool operator!= (const Area& lhs, const Area& rhs) {return !(lhs == rhs);}
	friend Area operator+ (Area lhs, const Area& rhs) {return (lhs += rhs);}
	friend Area operator* (Area lhs, const Area& rhs) {return (lhs *= rhs);}

};

}

#endif /* BUTILITIES_AREA_HPP_ */
