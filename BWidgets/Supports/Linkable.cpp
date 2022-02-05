/* Linkable.cpp
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


#include "Linkable.hpp"
#include "Support.hpp"
#include <algorithm>			// std::find

namespace BWidgets
{

Linkable::Linkable () :
	Support(),
    parent_ (nullptr),
	main_ (this),
    children_ ()
{

}

Linkable::~Linkable ()
{
	// Release from parent (and main) if still linked
	if (parent_) parent_->release (this);

	// Release children
	while (!children_.empty ()) Linkable::release (children_.back ());
}

void Linkable::setLinkable (const bool status) 
{
	setSupport (status);

	if (!isLinkable())
	{
		if (parent_) parent_->release (this);
		release();
	}
}

bool Linkable::isLinkable () const 
{
	return getSupport();
}

std::list<Linkable*>::iterator Linkable::add	(Linkable* child,
												 std::function<void (Linkable* obj)> addfunc)
{
	if (!isLinkable()) return children_.end();
	if (!child) return children_.end();

	// Check if already added? -> Release first
	if (child->parent_) child->parent_->release (child);

	// Connect child and add child to list
	child->parent_ = this;
	children_.push_back (child);

	// Connect child and children of child to main_
	forEachChild 
	(
		std::prev (children_.end()),
		children_.end(),
		[this, addfunc] (Linkable* l)
		{
			l->main_ = this->main_;
			addfunc (l);
			return true;
		}
	);

	return std::prev (children_.end());
}

void Linkable::release (std::function<void (Linkable* obj)> releasefunc)
{
	while (!children_.empty ()) release (children_.back (), releasefunc);
}

void Linkable::release (Linkable* child, std::function<void (Linkable* obj)> releasefunc)
{
	if (child)
	{
		std::list<Linkable*>::iterator it = std::find (children_.begin(), children_.end(), child);

		if (it != children_.end())
		{
			forEachChild 
			(
				it, 
				std::next (it), 
				[child, releasefunc] (Linkable* l)
				{
					releasefunc (l);
					l->main_ = child;
					return true;
				}
			);

			child->parent_ = nullptr;
			children_.erase (it);
		}
	}
}

Linkable* Linkable::getParent () const
{
	return parent_;
}

Linkable* Linkable::getMain () const
{
	return main_;
}

bool Linkable::hasChildren () const
{
	return !children_.empty();
}

bool Linkable::contains (const Linkable* child) const
{
	return std::find (children_.begin(), children_.end(), child) != children_.end();
}

const std::list<Linkable*>& Linkable::getChildren () const
{
	return children_;
}

std::list<Linkable*>& Linkable::getChildren ()
{
	return children_;
}

void Linkable::forEachChild	(std::function<bool (Linkable* obj)> func)
{
	forEachChild (children_.begin(), children_.end(), func);
}

void Linkable::forEachChild	(std::function<bool (Linkable* obj)> func) const
{
	forEachChild (children_.begin(), children_.end(), func);
}
	
void Linkable::forEachChild	(std::list<Linkable*>::iterator first, 
					 		 std::list<Linkable*>::iterator last,
					 		 std::function<bool (Linkable* obj)> func)
{
	for (std::list<Linkable*>::iterator it = first; it != last; ++it)
	{
		Linkable* l = *it;
		if (l && func (l)) l->forEachChild (func);
	}
}

void Linkable::forEachChild	(std::list<Linkable*>::const_iterator first, 
					 		 std::list<Linkable*>::const_iterator last,
					 		 std::function<bool (Linkable* obj)> func) const
{
	for (std::list<Linkable*>::const_iterator it = first; it != last; ++it)
	{
		Linkable* l = *it;
		if (l && func (l)) l->forEachChild (func);
	}
}


}
