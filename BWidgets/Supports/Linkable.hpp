/* Linkable.hpp
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

#ifndef BWIDGETS_LINKABLE_HPP_
#define BWIDGETS_LINKABLE_HPP_

#include <list>
#include <functional>
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Support for linking to parent and child objects.
 *
 *  Note: The class %Linkable is devoid of any copy constructor or assignment
 *  operator.
 */
class Linkable : public Support
{
protected:
    Linkable* parent_;
	Linkable* main_;
    std::list<Linkable*> children_;

public:
	Linkable ();
    virtual ~Linkable ();
    Linkable (const Linkable& that) = delete;
    Linkable& operator= (const Linkable& that) = delete;

    /**
     *  @brief  Switch linking ability to child objects on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether a Linkable object may take up child objects.
     *  Note:  Status off releases all children!
     */
    void setLinkable (const bool status);

    /**
     *  @brief  Information about linking ability to child objects.
     *  @return  True if on, otherwise false.
     *
     *  If an is linkable, then it may take up child objects.
     */
    bool isLinkable () const;

    /**
	 *  @brief  Adds a child object.
	 *  @param child  Pointer to the child object.
	 *  @param addfunc  Optional, function to be executed once a child object
	 *  is added.
	 *  @return  Iterator for the inserted child.
	 *
	 *  New child objects are appended to the end of list of children objects
	 *  (see @c getChildren() ).
	 *
	 *  Returns @c getChildren().end() if noting inserted (e.g, trying to add
	 *  a @c nullptr or linking is switched off).
	 */
	virtual std::list<Linkable*>::iterator 
	add	(Linkable* child, std::function<void (Linkable* obj)> addfunc = [] (Linkable* obj) {});

	/**
	 *  @brief  Releases (but not deletes) ALL child objects.
	 *  @param releasefunc  Optional, function to be executed once a child
	 *  object is released.
	 */
	virtual void release (std::function<void (Linkable* obj)> addfunc = [] (Linkable* obj) {});

	/**
	 *  @brief  Releases (but not deletes) a child object.
	 *  @param child Pointer to the child object.
	 *  @param releasefunc  Optional, function to be executed once a child
	 *  object is released.
	 */
	virtual void release (Linkable* child, std::function<void (Linkable* obj)> releasefunc = [] (Linkable* obj) {});

	/**
	 *  @brief  Access to the parent object.
	 *  @return  Pointer to the parent widget.
     *
     *  Returns nullptr if this object doesn't have any parents.
	 */
	Linkable* getParent () const;

	/**
	 *  @brief  Access to the root (parent) object.
	 *  @return  Pointer to the root (parent) widget. 
     *
     *  Performs a recursive search through the parent (and its parent and ...)
	 *  to find the root / main widget. Returns @c this if the object doesn't
	 *  have any parents and thus @c this is the root object. 
	 */
	Linkable* getMain () const;

	/**
	 *  @brief  Tests whether the object has got children or not.
	 *  @return  True if the object has got children, otherwise false.
	 */
	bool hasChildren () const;

	/**
	 *  @brief  Tests whether child is one of the children of this object.
	 *  @param child  Pointer to a child object.
	 *  @return  True if @a child is one of the children, otherwise false.
	 */
	bool contains (Linkable* child);

	/**
	 *  @brief  Read-only access to the list of children pointers. 
	 *  @return  Reference to the children list.
	 */
	const std::list<Linkable*>& getChildren () const;

	/**
	 *  @brief  Access to the list of children pointers. 
	 *  @return  Reference to the children list.
	 */
	std::list<Linkable*>& getChildren ();

	/**
	 *  @brief  (Recursive) iteration over all child objects.
	 *  @param func  Function to check if recursive iteration will be 
	 *  performed. Returns true for recursion, otherwise false.
	 */
	void forEachChild	(std::function<bool (Linkable* obj)> func = [] (Linkable* obj) {return true;});

	/**
	 *  @brief  (Recursive) read-only iteration over all child objects.
	 *  @param func  Function to check if recursive iteration will be 
	 *  performed. Returns true for recursion, otherwise false.
	 */
	void forEachChild	(std::function<bool (Linkable* obj)> func = [] (Linkable* obj) {return true;}) const;
	
	/**
	 *  @brief  (Recursive) iteration over a selected section of child objects.
	 *  @param first  Iterator for the first element.
	 *  @param last  Iterator for the past last element.
	 *  @param func  Function to check if recursive iteration will be 
	 *  performed. Returns true for recursion, otherwise false.
	 */
	void forEachChild	(std::list<Linkable*>::iterator first, 
						 std::list<Linkable*>::iterator last,
						 std::function<bool (Linkable* obj)> func = [] (Linkable* obj) {return true;});

	/**
	 *  @brief  (Recursive) read-only iteration over a selected section of 
	 *  child objects.
	 *  @param first  Iterator for the first element.
	 *  @param last  Iterator for the past last element.
	 *  @param func  Function to check if recursive iteration will be 
	 *  performed. Returns true for recursion, otherwise false.
	 */
	void forEachChild	(std::list<Linkable*>::const_iterator first, 
						 std::list<Linkable*>::const_iterator last,
						 std::function<bool (Linkable* obj)> func = [] (Linkable* obj) {return true;}) const;

};
}
#endif /* BWIDGETS_LINKABLE_HPP_ */