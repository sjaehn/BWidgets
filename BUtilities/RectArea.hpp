/* RectArea.hpp
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

#ifndef BUTILITIES_RECTAREA_HPP_
#define BUTILITIES_RECTAREA_HPP_

#include "Point.hpp"

namespace BUtilities
{

template <class T = double>
class RectArea
{
protected:
	Point<T> p1, p2;

public:
	RectArea () : RectArea (Point<T> (), Point<T> ()) {}
	RectArea (const T x1, const T y1, const T width, const T height) :
		RectArea (Point<T> (x1, y1), Point<T> (x1 + width, y1 + height)) {}
	RectArea (const Point<T>& p1, const Point<T>& p2) :
		p1 (Point<T> ((p1.x < p2.x ? p1.x : p2.x), (p1.y < p2.y ? p1.y : p2.y))),
		p2 (Point<T> ((p1.x > p2.x ? p1.x : p2.x), (p1.y > p2.y ? p1.y : p2.y)))
	{}

	Point<T> getPosition () const {return p1;}
	T getX () const {return p1.x;}
	T getY () const {return p1.y;}

	Point<T> getExtends () const {return Point<T> (p2.x - p1.x, p2.y - p1.y);}
	T getWidth () const {return (p2.x - p1.x);}
	T getHeight () const {return (p2.y - p1.y);}

	void setX (const T x) {moveTo (x, getY());}
	void setY (const T y) {moveTo (getX(), y);}
	void moveTo (const T x, const T y) {moveTo (Point<T> (x, y));}
	void moveTo (const Point<T>& position)
	{
		p2 = p2 - p1 + position;
		p1 = position;
	}

	void setWidth (const T width) {resize (width, getHeight());}
	void setHeight (const T height) {resize (getWidth(), height);}
	void resize (const T width, const T height) {resize (Point<T> (width, height));}
	void resize (const Point<T>& extends) {p2 = p1 + extends;}

	bool contains (const Point<T>& p) const
	{
		return ((p.x >= p1.x) && (p.x <= p2.x) && (p.y >= p1.y) && (p.y <= p2.y));
	}

	bool includes (const RectArea& ra) const
	{
		return ((ra.p1.x >= p1.x) && (ra.p1.y >= p1.y) && (ra.p2.x <= p2.x) && (ra.p2.y <= p2.y));
	}

	bool overlaps (const RectArea& ra) const
	{
		return !((ra.p2.x < p1.x) || (ra.p2.y < p1.y) || (ra.p1.x > p2.x) || (ra.p1.y > p2.y));
	}

	void extend (const RectArea& ra)
	{
		if (*this == RectArea ()) *this = ra;
		else if (ra != RectArea ())
		{
			p1 = Point<T> ((p1.x < ra.p1.x ? p1.x : ra.p1.x), (p1.y < ra.p1.y ? p1.y : ra.p1.y));
			p2 = Point<T> ((p2.x > ra.p2.x ? p2.x : ra.p2.x), (p2.y > ra.p2.y ? p2.y : ra.p2.y));
		}
	}

	void intersect (const RectArea& ra)
	{
		if ((*this == RectArea ()) || (ra == RectArea ()) || (!overlaps (ra))) *this = RectArea ();

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

	RectArea& operator+= (const RectArea& rhs)
	{
		this->extend (rhs);
		return *this;
	}

	RectArea& operator*= (const RectArea& rhs)
	{
		this->intersect (rhs);
		return *this;
	}

	friend bool operator== (const RectArea& lhs, const RectArea& rhs)
	{
		return ((lhs.p1 == rhs.p1) && (lhs.p2 == rhs.p2));
	}

	friend bool operator!= (const RectArea& lhs, const RectArea& rhs) {return !(lhs == rhs);}
	friend RectArea operator+ (RectArea lhs, const RectArea& rhs) {return (lhs += rhs);}
	friend RectArea operator* (RectArea lhs, const RectArea& rhs) {return (lhs *= rhs);}

};

}

#endif /* BUTILITIES_RECTAREA_HPP_ */
