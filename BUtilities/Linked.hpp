/* Linked.hpp
 * Copyright (C) 2021  Sven Jähnichen
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
 
#ifndef LINKED_HPP_
#define LINKED_HPP_

#include <list>

namespace BUtilities
{

class LinkedParent;     // Forward declaration

/**
 *  @brief A children interface class double linked to LinkedParent. 
 *
 *  Part of the pair LinkedParent - LinkedChild.
 *  
 *               LinkedParent
 *       ┌────────────┼────────────┬──────...
 *  LinkedChild  LinkedChild  LinkedChild
 *
 *  A LinkedChild object is either linked to exactly one %LinkedParent object 
 *  or t is waised. LinkedParent objects however may be linked to multiple 
 *  different LinkedChild objects.
 */
class LinkedChild
{
protected:
    LinkedParent* parent_;

public:

    /**
     *  @brief  Creates a waised default %LinkedChild.
     */
    LinkedChild ();

    /**
     *  @brief  Creates a %LinkedChild and links it to its @a parent.
     *  @param parent  Parent LinkedParent.
     */
    LinkedChild (LinkedParent* parent);

    virtual ~LinkedChild ();
    LinkedChild (const LinkedChild& that) = delete;
    LinkedChild (LinkedChild&& that) = delete;
    LinkedChild& operator= (LinkedChild& that) = delete;
    LinkedChild& operator= (const LinkedChild& that) = delete;
    LinkedChild& operator= (LinkedChild&& that) = delete;

    /**
     *  @brief Links to a @a parent object of LinkedParent. 
     *  @param parent  Pointer to a @a parent object or nullptr.
     *
     *  Links to a @a parent object if @a parent is different from nullptr. 
     *  Only one @a parent is allowed. Unlinks the old @a parent object first
     *  if it already has got a @a parent object.
     *
     *  @a parent nullptr only unlinks it from its @a parent.
     */
    virtual void linkParent (LinkedParent* parent);

    /**
     *  @brief Unlinks from a @a parent object of %LinkedParent. 
     *
     *  Unlinked LinkedParent objects remain waised and the allocated memory is
     *  NOT freed by this method.
     */
    virtual void unlinkParent ();
};

/**
 *  @brief A parent interface class double linked to LinkedChild. 
 *
 *  Part of the pair LinkedParent - LinkedChild.
 *  
 *               LinkedParent
 *       ┌────────────┼────────────┬──────...
 *  LinkedChild  LinkedChild  LinkedChild
 *  
 *  A %LinkedParent object is either linked to an arbitary number of LinkedChild
 *  objects. LinkedChild objects however may be linked to one %LinkedParent
 *  object, respectively.
 */
class LinkedParent
{
protected:
    std::list<LinkedChild*> children_;

public:

    /**
     *  @brief  Creates a non-linked default %LinkedParent.
     */
    LinkedParent () = default;
    
    virtual ~LinkedParent ();
    LinkedParent (const LinkedParent& that) = delete;
    LinkedParent (LinkedParent&& that) = delete;
    LinkedParent& operator= (LinkedParent& that) = delete;
    LinkedParent& operator= (const LinkedParent& that) = delete;
    LinkedParent& operator= (LinkedParent&& that) = delete;

    /**
     *  @brief Links to a @a child object of LinkedChild.
     *  @param child  Pointer to a @achild object.
     *
     *  Links to a @a child object. Multiple children are allowed, but not the
     *  same @a child multiple times. 
     */
    virtual void linkChild (LinkedChild* child);

    /**
     *  @brief Unlinks from a @achild object of LinkedChild. 
     *  @param child  Pointer to a @a child object. 
     *
     *  Unlinked LinkedChild objects remain waised and the allocated memory is
     *  NOT freed by this method.
     */
    virtual void unlinkChild (LinkedChild* child);

};


/**** Begin of class LinkedChild definitions ****/

inline LinkedChild::LinkedChild () : parent_ (nullptr) {}

inline LinkedChild::LinkedChild (LinkedParent* parent) : parent_ (parent) 
{
    if (parent) parent->linkChild (this);
}

inline LinkedChild::~LinkedChild ()
{
    unlinkParent();
}

inline void LinkedChild::linkParent (LinkedParent* parent)
{
    if (parent_ != parent) 
    {
        unlinkParent ();
        parent_ = parent;
        if (parent) parent->linkChild (this);
    }
}

inline void LinkedChild::unlinkParent () 
{
    if (parent_)
    {
        LinkedParent* p = parent_;
        parent_ = nullptr;
        p->unlinkChild (this);
    }
}


/**** Begin of class LinkedParent definitions ****/

inline LinkedParent::~LinkedParent ()
{
    while (!children_.empty()) unlinkChild (children_.front());
}

inline void LinkedParent::linkChild (LinkedChild* child)
{
    if (child)
    {
        for (LinkedChild* c : children_)
        {
            if (c == child) return;
        }

        children_.push_back (child);
        child->linkParent (this); 
    }
}

inline void LinkedParent::unlinkChild (LinkedChild* child)
{
    if (child)
    {
        for (std::list<LinkedChild*>::iterator it = children_.begin(); it != children_.end(); ++it)
        {
            LinkedChild* c = *it;
            if (c == child) 
            {
                children_.erase (it);
                c->unlinkParent();
                return;
            }
        }
    }
}

}


#endif /* LINKED_HPP_ */
