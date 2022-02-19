/* Point<T>.hpp
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

#ifndef BUTILITIES_POINT_HPP_
#define BUTILITIES_POINT_HPP_

namespace BUtilities
{

/**
 *  @brief  2D %Point coordinates.
 *  @tparam T  Data type of the coordinates.
 */
template <class T = double>
struct Point
{
	T x, y;

	/**
	 *  @brief  Constructs a new %Point object with default (origin) 
	 *  coordinates.
	 */
	Point () : Point<T> (T(), T()) {}

	/**
	 *  @brief  Constructs a new %Point object from provided coordinates.
	 *  @param x  X coordninate.
	 *  @param y  Y coordninate.
	 */
	Point (const T x, const T y) : x (x), y (y) {}

	/**
	 *  @brief  2D Vector addition of %Point coordinates.
	 *  @param rhs  Other point.
	 *  @return  Result of 2D vector addition. 
	 */
	Point& operator+= (const Point& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	/**
	 *  @brief  2D Vector subtraction of %Point coordinates.
	 *  @param rhs  Other point.
	 *  @return  Result of 2D vector subtraction. 
	 */
	Point<T>& operator-= (const Point& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	/**
	 *  @brief  Scalar multiplication of %Point coordinates.
	 *  @param rhs  Factor.
	 *  @return  Result of scalar multiplication. 
	 */
	Point<T>& operator*= (const T rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	/**
	 *  @brief  Scalar division of %Point coordinates.
	 *  @param rhs  Divisor.
	 *  @return  Result of scalar division. 
	 */
	Point<T>& operator/= (const T rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}

	friend bool operator== (const Point& lhs, const Point& rhs) {return ((lhs.x == rhs.x) && (lhs.y == rhs.y));}
	friend bool operator!= (const Point& lhs, const Point& rhs) {return !(lhs == rhs);}
	friend Point<T> operator+ (Point lhs, const Point& rhs) {return (lhs += rhs);}
	friend Point<T> operator- (Point lhs, const Point& rhs) {return (lhs -= rhs);}
	friend Point<T> operator* (Point lhs, const T rhs) {return (lhs *= rhs);}
	friend Point<T> operator* (const T lhs, Point rhs) {return (rhs *= lhs);}
	friend Point<T> operator/ (Point lhs, const T rhs) {return (lhs /= rhs);}

};

}

#endif /* BUTILITIES_POINT_HPP_ */
