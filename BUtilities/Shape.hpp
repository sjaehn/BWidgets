/* Shape.hpp
 *
 * Copyright (C) 2019 - 2022 by Sven Jähnichen
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

#ifndef BUTILITIES_SHAPE_HPP_
#define BUTILITIES_SHAPE_HPP_

#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <array>
#include <functional>
#include <iterator>
#include "Node.hpp"
#include "Point.hpp"
#include "mix.hpp"

#ifndef BUTILITIES_DEFAULT_SHAPE_RESOLUTION
#define BUTILITIES_DEFAULT_SHAPE_RESOLUTION 1024
#endif

namespace BUtilities
{

/**
 *  @brief  Node-based 2D graph %shape.
 *  @tparam T  Container type for Nodes (e. g., @c std::vector<Node<double>> ).
 *  @tparam res  X resolution (= number of elements) of the rendered %Shape
 *  map.
 *
 *  A %Shape is a container of transferred nodes to interpolate any point 
 *  between the nodes and thus to create a 2D graph. There are some rules 
 *  about shapes:
 *
 *  * Iteratable: The container MUST support iterators which meet the  
 *    requirements of @a LegacyBidirectionalIterator .
 *  * Uniqueness: There MUST be exactly one Y coordinate value for each X
 *    coordninate value.
 *  * Both, the X and the Y coordinate values can be transferred from an
 *    external context to an internal context using transfer functions and
 *	  vice versa using re-transfer functions. The transfer and re-transfer
 *	  functions MUST support uniqueness too.
 *	* All nodes are automatically sorted from the lowest to the highest 
 *	  (transferred) X coordinate. Thus the X coordinate value type MUST 
 *	  support the standard comparison operators.
 *	* The node with the lowest (transferred) X coordinate value and the node 
 *	  with the highest (transferred) X coordinate are always interpret as end
 *	  nodes. End nodes between the nodes with the lowest and the highest
 *	  (transferred) X coordinate value are interpret as corner nodes.
 *  * A %Shape should always have got at least its two end nodes for meaningful 
 *    interpolation. If the %Shape contains only one node, then the node Y
 *    coordinate represents the whole shape. And if there's no node at all,
 *    then default constructed Y coordinate represents the whole shape.
 *  * A %Shape map with the provided resolution is rendered if all 
 *    prerequisites are fulfilled. The X and the Y coordinates value type 
 *    MUST therefore also support the standard arithmetic operators.
 *
 *  @todo  Specialization for static containers which do not support
 *  @c insert(), @c erase(), @c clear(), ... (e. g. std::array). 
 */
template<class T, size_t res = BUTILITIES_DEFAULT_SHAPE_RESOLUTION>
class Shape : protected T
{

public:
	typedef typename T::value_type value_type;
	typedef typename T::pointer pointer;
	typedef typename T::const_pointer const_pointer;
	typedef typename T::reference reference;
	typedef typename T::const_reference const_reference;
	typedef typename T::iterator iterator;
	typedef typename T::const_iterator const_iterator;
	typedef typename T::size_type size_type;
	typedef typename T::difference_type difference_type;
	typedef typename T::reverse_iterator reverse_iterator;
	typedef typename T::const_reverse_iterator const_reverse_iterator;
	typedef typename T::value_type::value_type Tv;

	static Tv noTransfer (const Tv& x);

protected:

	T defaultNodes_;
	std::array<Tv, res> map_;
	std::function<Tv (const Tv& x)> xTransferFunc_;
	std::function<Tv (const Tv& x)> xReTransferFunc_;
	std::function<Tv (const Tv& x)> yTransferFunc_;
	std::function<Tv (const Tv& x)> yReTransferFunc_;

public:

	/**
	 *  @brief  Constructs an empty %Shape.
	 */
	Shape ();

	/**
	 *  @brief  Constructs a %Shape.
	 *  @param nodes  Container of nodes to be transferred into the %Shape.
	 *  @param xTransferFunc  Optional, transfer function for X coordiates 
	 *  from external to internal context.
	 *  @param xReTransferFunc  Optional, re-transfer function for X coordiates 
	 *  from inernal to external context.
	 *  @param yTransferFunc  Optional, transfer function for Y coordiates 
	 *  from external to internal context.
	 *  @param yReTransferFunc  Optional, re-transfer function for Y coordiates 
	 *  from inernal to external context.
	 */
	Shape	(const T& nodes,
			 std::function<Tv (const Tv& x)> xTransferFunc = noTransfer,
			 std::function<Tv (const Tv& x)> xReTransferFunc = noTransfer,
			 std::function<Tv (const Tv& x)> yTransferFunc = noTransfer,
			 std::function<Tv (const Tv& x)> yReTransferFunc = noTransfer);

	bool operator== (const Shape<T, res>& rhs);
	bool operator!= (const Shape<T, res>& rhs);

	/**
	 *  @brief  Defines the default %Shape nodes for @c reset().
	 *  @param defaultNodes  Container with the default nodes.
	 *
	 *  @a defaultNodes should contain at least the left and the right end
	 *  nodes. But can also be empty.
	 */
	void defineDefault (const T& defaultNodes);

	// Iterators
	using T::begin;
	using T::cbegin;
	using T::end;
	using T::cend;
	using T::rbegin;
	using T::crbegin;
	using T::rend;
	using T::crend;

protected:
	// Member access
	/**
	 *  @brief  Gets a validated transferred node from an iterator.
	 *  @param it  Iterator.
	 *  @return  Validated transferred node.
	 *
	 *  In contrast to the iterator deref @c *it , @c node() additionally
	 *  validates the nodes:
	 	* The first and the last node are always retruned as END_NODEs.
	 *  * END_NODEs which are not the first and not the last nodes are always
	 *    returned as CORNER_NODEs.
	 *
	 *  Note: The @c node_() method completely runs in the internal context.
	 */
	value_type node_ (const_iterator it) const;

public:
	/**
	 *  @brief  Gets a validated and re-transferred node from an iterator.
	 *  @param it  Iterator.
	 *  @return  Validated node (external context).
	 *
	 *  In contrast to the iterator deref @c *it , @c node() additionally
	 *  re-transfers and validates the nodes:
	 	* The re-transfer function is called for the point and its handles.
	 *  * The first and the last node are always retruned as END_NODEs.
	 *  * END_NODEs which are not the first and not the last nodes are always
	 *    returned as CORNER_NODEs.
	 *
	 *  Note: The node type is only interpreted in the internal context. Thus,
	 *  calling @c node() may return symmetric nodes with asymmetric handles
	 *  if non-linear transfer and re-transfer functions are used.
	 */
	value_type node (const_iterator it) const;

	// Value access
protected:
	/**
	 *  @brief  Gets the Y value for any X position covered by the shape 
	 *  via map access. 
	 *  @param x  Transferred X position.
	 *  @return  TransferredY value.
	 *
	 *  Gets the Y value for the X position via fast two point linear 
	 *  interpolation from to the internal map. Returns the respective end
	 *  node Y value if @a x exceeds the range between both end nodes.
	 *  @c interpolate_() completely uses the internal context.
	 *  
	 */
	Tv interpolate_ (const Tv& x) const;

public:
	/**
	 *  @brief  Gets the Y value for any X position covered by the shape 
	 *  via map access.
	 *  @param x  Raw X position.
	 *  @return  Raw (re-transferred) Y value.
	 *
	 *  Gets the Y value for the X position via fast two point linear 
	 *  interpolation from to the internal map. X position is transformed and
	 *  the resulting Y value is re-transformed to translate from internal to 
	 *  external context (and vice versa) if transfer functions were defined.
	 *  Returns the respective end node Y value if @a x exceeds the range 
	 *  between both end nodes.
	 *  
	 */
	Tv interpolate (const Tv& x) const;
	
	// Capacity
	using T::empty;
	using T::size;

	/**
	 *  @brief  Checks if the present %Shape nodes equals the pre-defined
	 *  default nodes.
	 *  @return  True if the present %Shape nodes equals the pre-defined
	 *  default nodes, otherwise false.
	 */
	bool isDefault () const;

	// Modifiers
	/**
	 *  @brief  Clears all nodes and sets all map points to transferred default
	 *  value.
	 *
	 *  The resulting %Shape will be empty. Thus @c clear() doesn't reset to
	 *  pre-defined default nodes.
	 */
	void clear();

	/**
	 *  @brief  Clears all nodes and sets the default nodes. 
	 */
	void reset ();

protected:
	/**
	 *  @brief  Inserts an already transferred node into the shape at the 
	 *  provided position. Also tries to validate this and the neighbor nodes
	 *  and their handles to prevent overlaps and thus possibly breaking the
	 *  rule of uniqueness.
	 *  @param pos  Iterator before which the content will be inserted. 
	 *  @a pos may be the @c end() iterator.
	 *  @param node  New (transferred) node to be inserted.
	 *  @return iterator  Iterator to the inserted node or @c end() if invalid.
	 *
	 *  @note  In contrast to @c insert() , @c insert_() uses internal context
	 *  arguments.
	 *  @note  @c insert_() doesn't update the map!
	 */
	iterator insert_ (const_iterator pos, const value_type& node);

	/**
	 *  @brief  Transfers a node from the external context to the internal
	 *  context. 
	 *  @param node  Raw node from the external context.
	 *  @return  Transferred node for the use in the internal context. 
	 */
	value_type transfer (const value_type& node);

	/**
	 *  @brief  Re-transfers a node from the internal context to the external
	 *  context. 
	 *  @param node  Transferred node from the internal context.
	 *  @return  Raw node for the use in the external context. 
	 */
	value_type retransfer (const value_type& node);

public:
	/**
	 *  @brief  Transfers and inserts a node into the shape at the right
	 *  position. Also validates this and the neighbor nodes and their handles
	 *  to prevent overlaps and thus possibly breaking the rule of uniqueness.
	 *  @param node  New (raw) node to be inserted.
	 *  @return iterator  Iterator to the inserted node.
	 *
	 *  @note  @c insert() doesn't allow the insertion of identical nodes!
	 */
	iterator insert (const value_type& node);

	/**
	 *  @brief  Transfers and inserts multiple nodes into the shape at their
	 *  right positions. Also validates the nodes and the neighbor nodes and
	 *  their handles to prevent overlaps and thus possibly breaking the rule
	 *  of uniqueness.
	 *  @param nodes  Container with new (raw) nodes to be inserted.
	 *
	 *  @note  @c insert() doesn't allow the insertion of identical nodes!
	 */
	void insert (const T& nodes);

	/**
	 *  @brief  Removes a node from the shape.
	 *  @param pos  Iterator to the node to be removed.
	 *  @return  Iterator following the removed element. 
	 */
	iterator erase (const_iterator pos);

	/**
	 *  @brief  Removes a series of nodes from the shape.
	 *  @param first  Iterator to the first node to be removed.
	 *  @param last  Iterator to the past-last node to be removed.
	 *  @return  Iterator following the last removed element. 
	 */
	iterator erase (const_iterator first, const_iterator last);

	/**
	 *  @brief  Removes a node from the shape.
	 *  @param node  Raw node to be removed.
	 *  @return  Number of nodes removed (0 or 1). 
	 */
	size_type erase (const value_type& node);

	/**
	 *  @brief  Removes a node from the shape.
	 *  @param x  Raw point X coordinate of the node to be removed.
	 *  @return  Number of nodes removed. 
	 */
	size_type erase (const Tv& x);

	/**
	 *  @brief  Changes / moves a node.
	 *  @param from  Raw node to be changed.
	 *  @param to  New raw node data.
	 *  @return iterator  Iterator to the new node.
	 *
	 *  @c change() techincally calls @c find() and @c erase() for the node
	 *  to be changed and then @c insert() to insert a new node.
	 */
	iterator change (value_type& from, const value_type& to);

	/**
	 *  @brief  Changes / moves a node.
	 *  @param fromX  Raw X coordinate of the node to be changed.
	 *  @param to  New raw node data.
	 *  @return iterator  Iterator to the new node.
	 *
	 *  @c change() techincally calls @c find() and @c erase() for the node
	 *  to be changed and then @c insert() to insert a new node.
	 */
	iterator change (Tv& fromX, const value_type& to);

	// Lookup
	/**
	 *  @brief  Returns the number of nodes which compares equivalent to the
	 *  specified argument. Either 1 or 0 since %Shape does not allow
	 *  duplicates.
	 *  @param node  Raw node to be counted. 
	 *  @return  Number of nodes which compares equivalent to @a node . Either
	 *  0 or 1. 
	 */
	size_type count (const value_type& node) const;

	/**
	 *  @brief  Returns the number of nodes with the same X coordinate as the
	 *  specified argument.
	 *  @param x  Raw X coordinate. 
	 *  @return  Number of nodes with the same X coordinate like x. 
	 */
	size_type count (const Tv& x) const;

	/**
	 *  @brief  Gets the first occurance of the specified node in the %Shape.
	 *  @param node  Raw node to find.
	 *  @return  Iterator to the node found or @c end() if not present.
	 */
	iterator find (const value_type& node);

	/**
	 *  @brief  Gets the first occurance of a node with the specified X
	 *  coordinate in the %Shape.
	 *  @param x  Raw X coordinate of the node to find.
	 *  @return  Iterator to the node found or @c end() if not present.
	 */
	iterator find (const Tv& x);

	/**
	 *  @brief  Gets the first occurance of the specified node in the %Shape.
	 *  @param node  Raw node to find.
	 *  @return  Iterator to the node found or @c end() if not present.
	 */
	const_iterator find (const value_type& node) const;

	/**
	 *  @brief  Gets the first occurance of a node with the specified X
	 *  coordinate in the %Shape.
	 *  @param x  Raw X coordinate of the node to find.
	 *  @return  Iterator to the node found or @c end() if not present.
	 */
	const_iterator find (const Tv& x) const;

	/**
	 *  @brief  Checks if there is a node equivalent to @a node in the %Shape. 
	 *  @param node  Raw node to search for.
	 *  @return  True if there's a node equivalent to @a node in the %Shape,
	 *  otherwise false.
	 */
	bool contains (const value_type& node) const;

	/**
	 *  @brief  Checks if there is a node with a specified X coordinate in 
	 *  the %Shape. 
	 *  @param x  Raw sX coordinate to search for.
	 *  @return  True if there's a node with the X coordinate @a x in the
	 *  %Shape, otherwise false.
	 */
	bool contains (const Tv& x) const;

protected:
	// Map operations
	/**
	 *  @brief  Validates all nodes from @c begin() to @c end(). 
	 */
	void validate ();

	/**
	 *  @brief  Validates a single node.
	 *  @param it  Iterator to the node to be validated.
	 *
	 *  Validation includes:
	 *  * Keep nodes in the right order from low to high X coordinates.
	 *  * Keep handles in the right order.
	 *  * Prevent handles to overlap with neighbor points.
	 */
	void validate (iterator it);

	/**
	 *  @brief  Validates nodes from @a first to @a last.
	 *  @param first  Iterator to the first node.
	 *  @param last  Iterator to the past last node. 
	 */
	void validate (iterator first, iterator last);

	/**
	 *  @brief  Renders all nodes to the internal map. 
	 */
	void render();

	/**
	 *  @brief  Renders a specified range to the internal map.
	 *  @param first  Iterator to the first node to be rendered.
	 *  @param last  Iterator to the past last node to be rendered.
	 */
	void render (const_iterator first, const_iterator last);

protected:

	// Map operations
	/**
	*  @brief  Draws a range of data defined by points to the internal map in
	*  a linear way (internal context).
	*  @param p1  Left point.
	*  @param p2  Right point.
	*/
	void drawLineOnMap_ (const Point<Tv> p1, const Point<Tv> p2);

public:
	/**
	 *  @brief Gets a copy of the internal map.
	 *  @return  Copy of the internal map. 
	 */
	std::array<Tv, res> getMap () const;

};

template<class T, size_t res> 
Shape<T, res>::Shape () : Shape (T()) {}

template<class T, size_t res> 
Shape<T, res>::Shape	(const T& nodes,
						 std::function<Tv (const Tv& x)> xTransferFunc,
						 std::function<Tv (const Tv& x)> xReTransferFunc,
						 std::function<Tv (const Tv& x)> yTransferFunc,
						 std::function<Tv (const Tv& x)> yReTransferFunc) :
	T (),
	defaultNodes_ (),
	map_ (),
	xTransferFunc_(xTransferFunc),
	xReTransferFunc_(xReTransferFunc),
	yTransferFunc_(yTransferFunc),
	yReTransferFunc_(yReTransferFunc)
{
	map_.fill (yTransferFunc_(Tv()));
	insert (nodes);
}

template<class T, size_t res> 
bool Shape<T, res>::operator== (const Shape<T, res>& rhs)
{
	if (size () != rhs.size ()) return false;
	
	for (const_iterator lit = this->begin(), rit = rhs.begin(); (lit != this->end()) && (rit != rhs.end()); ++lit, ++rit)
	{
		if (*lit != *rit) return false;
	}

	return true;
}

template<class T, size_t res> 
bool Shape<T, res>::operator!= (const Shape<T, res>& rhs) 
{
	return !(*this == rhs);
}

template<class T, size_t res> 
void Shape<T, res>::defineDefault (const T& defaultNodes)
{
	defaultNodes_ = defaultNodes;
}

template<class T, size_t res>
typename Shape<T, res>::value_type Shape<T, res>::node_ (const_iterator it) const
{
	if ((it == this->begin()) || (std::next(it) == this->end())) return Node<Tv> (Node<Tv>::END_NODE, it->point, it->handle1, it->handle2);
	if (it->nodeType == Node<Tv>::END_NODE) return Node<Tv> (Node<Tv>::CORNER_NODE, it->point, it->handle1, it->handle2);
	return *it;
}

template<class T, size_t res>
typename Shape<T, res>::value_type Shape<T, res>::node (const_iterator it) const
{
	return retransfer (node_ (it));
}

template<class T, size_t res>
typename Shape<T, res>::Tv Shape<T, res>::interpolate_ (const typename Shape<T, res>::Tv& x) const
{
	// Empty shape or only one node: return any map_ value
	if ((this->begin() == this->end()) || (std::next (this->begin()) == this->end())) return map_[0];

	const Tv minx = this->begin().point.x;
	const Tv maxx = std::prev (this->end()).point.x;

	// At or outside the limits: return the limit Y values
	if (x <= minx) return this->begin().point.y;
	if (x >= maxx) return std::prev (this->end()).point.y;

	// Linear interpolation between two map_ points
	const double mapx = static_cast<double>(res) * (x - minx) / (maxx - minx);
	double xmod = mapx - std::floor (mapx);
	return mix (map_[static_cast<int>(mapx) % res], map_[static_cast<int>(mapx + 1) % res], xmod);
}

template<class T, size_t res>
typename Shape<T, res>::Tv Shape<T, res>::interpolate (const typename Shape<T, res>::Tv& x) const
{
	return this->yReTransferFunc_ (interpolate_ (this->xTransferFunc_ (x)));
}

template<class T, size_t res> 
bool Shape<T, res>::isDefault() const
{
	return defaultNodes_ == *this;
}

template<class T, size_t res> 
void Shape<T, res>::clear () 
{
	T::clear();
	map_.fill (yTransferFunc_(Tv()));
}

template<class T, size_t res> 
void Shape<T, res>::reset () 
{
	clear();
	insert (defaultNodes_);
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::insert_ (const_iterator pos, const value_type& node)
{
	// Don't insert if wrong order
	if 
	(
		((pos != this->end()) && (node.point.x > pos->point.x)) ||
		((pos != this->begin()) && (node.point.x < std::prev (pos)->point.x))
	) return this->end();

	// Don't insert if duplicate
	if (node == *pos) return pos;

	// Insert node
	iterator it = T::insert (pos, node);

	// Validate node and its neighbors
	if (it != this->begin()) validate (std::prev(it));
	if (std::next(it) != this->end()) validate (std::next(it));
	validate (it);
	return (it);
}

template<class T, size_t res>
typename Shape<T, res>::value_type Shape<T, res>::transfer (const value_type& node)
{
	return Node<Tv>	(node.nodeType,
					 {xTransferFunc_ (node.point.x), yTransferFunc_ (node.point.y)},
					 {xTransferFunc_ (node.point.x + node.handle1.x) - xTransferFunc_(node.point.x), 
					  yTransferFunc_ (node.point.y + node.handle1.y) - xTransferFunc_(node.point.y)},
					 {xTransferFunc_ (node.point.x + node.handle2.x) - xTransferFunc_(node.point.x), 
					  yTransferFunc_ (node.point.y + node.handle2.y) - xTransferFunc_(node.point.y)});
}



template<class T, size_t res>
typename Shape<T, res>::value_type Shape<T, res>::retransfer (const value_type& node)
{
	return Node<Tv>	(node.nodeType,
					 {xReTransferFunc_ (node.point.x), yReTransferFunc_ (node.point.y)},
					 {xReTransferFunc_ (node.point.x + node.handle1.x) - xReTransferFunc_(node.point.x), 
					  yReTransferFunc_ (node.point.y + node.handle1.y) - xReTransferFunc_(node.point.y)},
					 {xReTransferFunc_ (node.point.x + node.handle2.x) - xReTransferFunc_(node.point.x), 
					  yReTransferFunc_ (node.point.y + node.handle2.y) - xReTransferFunc_(node.point.y)});
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::insert (const value_type& node)
{
	// Transfer node
	const value_type nt = transfer (node);

	// Find position
	iterator it = this->begin();
	for (/* empty */; (it != this->end()) && (nt.point.x > it->point.x); ++it) {}

	// Insert node
	it = insert_ (it, nt);
	if (it == this->end()) return it;

	// Update map
	if ((it == this->begin()) || (std::next (it) == this->end())) render ();
	else 
	{
		const_iterator it2begin = ((it != this->begin()) && (std::prev(it) != this->begin()) ? std::prev (it, 2) : this->begin());
		const_iterator it2end = ((std::next (it) != this->end()) ? std::next (it, 2) : this->end());
		for	(const_iterator it2 = it2begin; it2 != it2end; ++it2) render (it2, std::next(it2));
	}

	// Return iterator
	return it;
}

template<class T, size_t res>
void Shape<T, res>::insert (const T& nodes)
{
	bool renderAllAtOnce = (4 * nodes.size() > this->size());
	for (const value_type& n : nodes) 
	{
		// Transfer node
		const value_type nt = transfer (n);

		// Find position
		iterator it = this->begin();
		for (/* empty */; (it != this->end()) && (nt.point.x > it->point.x); ++it) {}

		// Insert node
		it = insert_ (it, nt);
		if (it == this->end()) continue;
		if ((it == this->begin()) || (std::next (it) == this->end())) renderAllAtOnce = true;

		// Update map
		if (!renderAllAtOnce)
		{
			const_iterator it2begin = ((it != this->begin()) && (std::prev(it) != this->begin()) ? std::prev (it, 2) : this->begin());
			const_iterator it2end = ((std::next (it) != this->end()) ? std::next (it, 2) : this->end());
			for	(const_iterator it2 = it2begin; it2 != it2end; ++it2) render (it2, std::next(it2));
		}
	}

	if (renderAllAtOnce) render ();
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::erase (const_iterator pos)
{
	iterator it = T::erase (pos);

	// Update map
	if (this->empty()) map_.fill (yTransferFunc_(Tv()));
	else if ((it == this->begin()) || (it == this->end())) render ();
	else render (std::prev (it), it);

	// Return iterator
	return it;
}


template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::erase (const_iterator first, const_iterator last)
{
	bool renderAllAtOnce = ((first == this->begin()) || (last == this->end()));
	for (const_iterator it = first; it != last; /* empty */) 
	{
		it = erase (it);
		if (!renderAllAtOnce) render (std::prev (it), it);
	}

	if (renderAllAtOnce) render();
}

template<class T, size_t res>
typename Shape<T, res>::size_type Shape<T, res>::erase (const value_type& node)
{
	// Transfer node
	const value_type nt = transfer (node);

	size_type count = 0;
	for (const_iterator it = this->find (nt); it != this->end(); it = this->find (nt))
	{
		erase(it);
		++count;
	}

	return count;
}

template<class T, size_t res>
typename Shape<T, res>::size_type Shape<T, res>::erase (const Tv& x)
{
	// Transfer x
	Tv xt = xTransferFunc_ (x);

	size_type count = 0;
	for (const_iterator it = this->find (xt); it != this->end(); it = this->find(xt))
	{
		erase(it);
		++count;
	}

	return count;
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::change (value_type& from, const value_type& to)
{
	iterator it = this->find (from);
	if (it == this->end()) return it;

	erase (from);
	insert (to);
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::change (Tv& fromX, const value_type& to)
{
	iterator it = this->find (fromX);
	if (it == this->end()) return it;

	it = erase (it);
	if ((it == this->begin()) || (it == this->end())) render ();
	else render (std::prev (it), it);
	insert (to);
}

template<class T, size_t res>
typename Shape<T, res>::size_type Shape<T, res>::count (const value_type& node) const
{
	// Transfer node
	const value_type nt = transfer (node);

	for (const value_type& n : *this)
	{
		if (n == nt) return 1;
	}

	return 0;
}
	
template<class T, size_t res>
typename Shape<T, res>::size_type Shape<T, res>::count (const Tv& x) const
{
	// Transfer x
	Tv xt = xTransferFunc_ (x);

	size_type c = 0;
	for (const value_type& n : *this)
	{
		if (n.point.x == xt) ++c;
	}

	return c;
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::find (const value_type& node)
{
	// Transfer node
	const value_type nt = transfer (node);

	for (iterator it = this->begin(); (it != this->end) && (nt.point.x <= it->point.x); ++it)
	{
		if (nt == *it) return it;
	}

	return this->end();
}

template<class T, size_t res>
typename Shape<T, res>::iterator Shape<T, res>::find (const Tv& x)
{
	// Transfer x
	Tv xt = xTransferFunc_ (x);

	for (iterator it = this->begin(); (it != this->end) && (xt <= it->point.x); ++it)
	{
		if (xt == it->point.x) return it;
	}

	return this->end();
}

template<class T, size_t res>
typename Shape<T, res>::const_iterator Shape<T, res>::find (const value_type& node) const
{
	// Transfer node
	const value_type nt = transfer (node);

	for (const_iterator it = this->begin(); (it != this->end) && (nt.point.x <= it->point.x); ++it)
	{
		if (node == *it) return it;
	}

	return this->end();
}

template<class T, size_t res>
typename Shape<T, res>::const_iterator Shape<T, res>::find (const Tv& x) const
{
	// Transfer x
	Tv xt = xTransferFunc_ (x);

	for (const_iterator it = this->begin(); (it != this->end) && (xt <= it->point.x); ++it)
	{
		if (xt == it->point.x) return it;
	}

	return this->end();
}

template<class T, size_t res>
bool Shape<T, res>::contains (const value_type& node) const
{
	return (this->find(node) != this->end());
}

template<class T, size_t res>
bool Shape<T, res>::contains (const Tv& x) const
{
	return (this->find(x) != this->end());
}

template<class T, size_t res>
void Shape<T, res>::validate ()
{
	for (iterator it = this->begin(); it != this->end(); ++it) validate (it);
}

template<class T, size_t res>
void Shape<T, res>::validate (iterator it)
{
	if (it == this->end()) return;

	// Node order
	if ((it != this->begin()) && (std::prev (it)->point.x > it->point.x)) it->point.x = std::prev (it)->point.x;
	if ((std::next(it) != this->end()) && (std::next (it)->point.x < it->point.x)) it->point.x = std::next (it)->point.x;

	// Handles order
	if (it->handle1.x > 0) it->handle1.x = 0;
	if (it->handle2.x < 0) it->handle2.x = 0;

	switch (it->nodeType)
	{
		case value_type::POINT_NODE:			// Point nodes don't have any handles
												it->handle1 = value_type();
												it->handle2 = value_type();
												break;

		case value_type::AUTO_SMOOTH_NODE:		// Symmetric handles with the half size of the distance to the closest neighbor point
												{
													const BUtilities::Point<Tv> pprev = (it != this->begin() ? std::prev(it)->point : it->point);
													const BUtilities::Point<Tv> pnext = (std::next (it) != this->end() ? std::next(it)->point : it->point);
													const double dist =	(it->point.x - pprev.x > pnext.x - it->point.x ?
																		 pnext.x - it->point.x :
																		 it->point.x - pprev.x);
													const double ydist =(pnext.y - pprev.y);
													const double yamp =	(fabs (pprev.y != 0) && fabs (pnext.y != 0) ?
																		 (fabs (pprev.y) < fabs (pnext.y) ?
																		  fabs (pprev.y) / (fabs (pprev.y) + fabs (pnext.y)) :
																		  fabs (pnext.y) / (fabs (pprev.y) + fabs (pnext.y))
																		 ) :
																		 0);
													it->handle1.x = -dist / 2;
													it->handle1.y = -ydist * yamp;
													it->handle2.x = dist / 2;
													it->handle2.y = ydist * yamp;
												}
												break;

		case value_type::SYMMETRIC_SMOOTH_NODE:	//Check if handle1 overlaps left neighbor point
												if ((it != this->begin()) && (it->point.x + it->handle1.x < std::prev (it)->point.x))
												{
													const double f = (std::prev (it)->point.x - it->point.x) / it->handle1.x;
													it->handle1 *= f;
												}

												// Make handele2 symmetric to handle1
												it->handle2 = BUtilities::Point<Tv> () - it->handle1;

												// Check if handle2 overlaps right neighbor point
												if ((std::next (it) != this->end()) && (it->point.x + it->handle2.x > std::next(it)->point.x))
												{
													const double f = (std::next(it)->point.x - it->point.x) / it->handle2.x;
													it->handle2 *= f;
													it->handle1 = BUtilities::Point<Tv> () - it->handle2;
												}
												break;

		case value_type::SMOOTH_NODE:			{
													//Check if handle1 overlaps neighbor point
													if ((it != this->begin()) && (it->point.x + it->handle1.x < std::prev (it)->point.x))
													{
														const double f = (std::prev (it)->point.x - it->point.x) / it->handle1.x;
														it->handle1 *= f;
													}

													// Calculate handle distances
													double dist1 = it->handle1.length();
													double dist2 = it->handle2.length();

													// Recalculate handle2
													if ((dist1 != 0) && (dist2 != 0)) it->handle2 = -(it->handle1 * dist2 / dist1);

													// Check if handle2 overlaps right neighbor point
													if ((std::next (it) != this->end()) && (it->point.x + it->handle2.x > std::next(it)->point.x))
													{
														const double f = (std::next(it)->point.x - it->point.x) / it->handle2.x;
														it->handle2 *= f;
													}
												}
												break;

		case value_type::CORNER_NODE:			// Check if handle1 overlaps left neighbor point
												if ((it != this->begin()) && (it->point.x + it->handle1.x < std::prev (it)->point.x))
												{
													const double f = (std::prev (it)->point.x - it->point.x) / it->handle1.x;
													it->handle1 *= f;
												}

												// Check if handle2 overlaps right neighbor point
												if ((std::next (it) != this->end()) && (it->point.x + it->handle2.x > std::next(it)->point.x))
												{
													const double f = (std::next(it)->point.x - it->point.x) / it->handle2.x;
													it->handle2 *= f;
												}
												break;

		default:								break;
	}
}

template<class T, size_t res>
void Shape<T, res>::validate (iterator first, iterator last)
{
	for (iterator it = first; it != last; ++it) validate (it);
}

template<class T, size_t res>
void Shape<T, res>::render ()
{
	render (this->begin(), this->end());
}

template<class T, size_t res>
void Shape<T, res>::render (const_iterator first, const_iterator last)
{
	// Empty Shape: Fill map with default value
	if (this->empty())
	{
		map_.fill (yTransferFunc_(Tv()));
		return;
	}

	// Empty range: Don't do anything
	if (first == this->end()) return;
	if (first == last) return;

	// Shape with only one node: All the same
	if (std::next (this->begin()) == this->end()) 
	{
		map_.fill (node_(this->begin()).point.y);
		return;
	}
	
	for (const_iterator it = first; std::next (it) != last; ++it)
	{
		const value_type n1 = node_ (it);
		const value_type n2 = node_ (std::next (it));
		
		// Interpolate Bezier curve
		const Point<Tv> p1 = n1.point;
		const Point<Tv> p2 = n1.point + n1.handle2;
		const Point<Tv> p4 = n2.point;
		const Point<Tv> p3 = n2.point + n2.handle1;
		Point<Tv> py = p1;
		const double step = 1.0 / (fabs (n2.point.x - n1.point.x) * res + 1.0);

		for (double t = 0.0; t < 1.0; t += step)
		{
			const Point<Tv> pa = mix<Point<Tv>> (p1, p2, t);
			const Point<Tv> pb = mix<Point<Tv>> (p2, p3, t);
			const Point<Tv> pc = mix<Point<Tv>> (p3, p4, t);
			const Point<Tv> pm = mix<Point<Tv>> (pa, pb, t);
			const Point<Tv> pn = mix<Point<Tv>> (pb, pc, t);
			const Point<Tv> pz = mix<Point<Tv>> (pm, pn, t);

			drawLineOnMap_ (py, pz);
			py = pz;
		}
		drawLineOnMap_ (py,p4);
	}
} 

template<class T, size_t res>
std::array<typename Shape<T, res>::Tv, res> Shape<T, res>::getMap () const
{
	return map_;
}

template<class T, size_t res> 
void Shape<T, res>::drawLineOnMap_ (Point<Tv> p1, Point<Tv> p2)
{
	// Empty shape or only one node: Nothing to do
	if ((this->begin() == this->end()) || (std::next (this->begin()) == this->end())) return;

	const Tv minx = this->begin().point.x;
	const Tv maxx = std::prev (this->end()).point.x;
	if (minx == maxx) return;

	if (p1.x < p2.x)
	{
		for (double x = p1.x; x <= p2.x; x += (1.0 / static_cast<double>(res)))
		{
			const int idx = static_cast<int>(static_cast<double>(res) * (x - minx) / (maxx - minx)) % res;
			map_[idx] = p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
		}
	}

	else
	{
		const int idx = static_cast<int>(static_cast<double>(res) * (p2.x - minx) / (maxx - minx)) % res;
		map_ [idx] = p2.y;
	}
}

}

#endif /* BUTILITIES_SHAPE_HPP_ */
