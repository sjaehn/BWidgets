/* Node.hpp
 *
 * Copyright (C) 2019 - 2023 by Sven Jähnichen
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

#ifndef BUTILITIES_NODE_HPP_
#define BUTILITIES_NODE_HPP_

#include "Point.hpp"

namespace BUtilities
{

/**
 *  @brief  Template class describing a node as a point with up to two handles. 
 *  @tparam T  Coordinate value type.
 *
 *  A node is described by its NodeType, a point coordinate for the node, and
 *  up to two point coordinates for the handles (depending on the node type).
 */
template<class T = double>
struct Node
{
	typedef T value_type;
	
	/**
	 *  @brief  Type of the node.  
	 */
	enum class NodeType
	{
		end,				// End positions, only point data are used
		point,				// Only point data are used
		autosmooth,			// Uses two handles, both are calculated automatically
		symmetric,		 	// Uses two handles, the second handle is set to be symmetric to the first one
		smooth,				// Uses two handles, the second handle points to the opposite direction of the first one
		corner				// Uses two independent handles
	};

	NodeType nodeType;
	Point<T> point;
	Point<T> handle1;
	Point<T> handle2;

	/**
	 *  @brief Constructs a default Node object.
	 */
	Node () : Node (NodeType::end, {T(), T()}, {T(), T()}, {T(),T()}) {}

	/**
	 *  @brief  Constructs a Node object.
	 *  @param nodeType  Node type.
	 *  @param point  Node point coordinate.
	 *  @param handle1  First handle coordinate.
	 *  @param handle2  Second handle coordinate.
	 */
	Node (NodeType nodeType, BUtilities::Point<> point, BUtilities::Point<> handle1, BUtilities::Point<> handle2) :
		nodeType (nodeType), point (point), handle1 (handle1), handle2 (handle2) {}

	friend bool operator== (const Node& lhs, const Node& rhs)
	{
		return ((lhs.nodeType == rhs.nodeType) && (lhs.point == rhs.point) && (lhs.handle1 == rhs.handle1) && (lhs.handle2 == rhs.handle2));
	}

	friend bool operator!= (const Node& lhs, const Node& rhs) 
	{
		return !(lhs == rhs);
	}
};

}

#endif /* BUTILITIES_NODE_HPP_ */
