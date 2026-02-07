/* Enterable.hpp
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

#ifndef BWIDGETS_ENTERABLE_HPP_
#define BWIDGETS_ENTERABLE_HPP_

#include "Linkable.hpp"
#include "../../BDevices/Keys.hpp"

namespace BWidgets
{

/**
 *  @brief  Interface class for Support to enter a widget.
 *
 *  %Enterable is a hint for a widget to get in a focus from a bigger
 *  context (the whole user interface). Depending on the implementation,
 *  entered widgets may get activated and/or take over keyboard control.
 */
class Enterable : public Support
{
protected:

    bool entered_;
    std::list<BDevices::Keys::KeyType> enterHotKeys_;

public:

    /**
     *  @brief  Constructs a default %Enterable object with INACTIVE 
     *  support.
     */
    Enterable ();

    /**
     *  @brief  Constructs a %Enterable object with a provided support 
     *  status.
     *  @param status  Support status. 
     */
    Enterable (const bool status);

    /**
     *  @brief  Switch the support to enter a Widget on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setEnterable (const bool status);

    /**
     *  @brief  Information about the support to enter a Widget.
     *  @return  True if on, otherwise false.
     */
    bool isEnterable () const;
    
    /**
     *  @brief  Enters this object
     *
     *  Overridable virtual method. By default, it only calls to leave all 
     *  other objects linked to the same Linkable main object to become the
     *  only entered object.
     */
    virtual void enter ();

    /**
     *  @brief  Leaves this object
     *
     *  Overridable empty virtual method.
     */
    virtual void leave ();

    /**
     *  @brief  Information if the widget has been entered or not. 
     *  @return  True if the widget has been entered otherwise false.
     */
    bool isEntered();

    /**
     *  @brief  Adds a key to the list of hot keys to enter this object.
     *  @param key  Key code
     */
    virtual void addHotKey (const BDevices::Keys::KeyType key);

    /**
     *  @brief  Removes a key from the list of hot keys to enter this object.
     *  @param key  Key code
     */
    virtual void removeHotKey (const BDevices::Keys::KeyType key);

    /**
     *  @brief  Checks if a key in the list of hot keys to enter this object.
     *  @param key  Key code
     */
    bool containsHotKey (const BDevices::Keys::KeyType key);

};

inline Enterable::Enterable () : Enterable (false) {}

inline Enterable::Enterable (const bool status) : 
    Support (status),
    entered_(false)
{}

inline void Enterable::setEnterable (const bool status)
{
    setSupport(status);
}

inline bool Enterable::isEnterable () const
{
    return getSupport();
}

inline void Enterable::enter () 
{
    if (isEnterable()) entered_ = true;

    // But leave all other widgets
    Linkable* l = dynamic_cast<Linkable*>(this);
    if (!l) return;
    Linkable* m = l->getMain();
    if (!m) return;
    m->forEachChild ([this] (Linkable* l)
    {
        Enterable* e = dynamic_cast<Enterable*>(l);
        if (e && e->isEnterable() && (e != this)) e->leave();
        return true;
    });
}

inline void Enterable::leave ()
{
    entered_ = false;
}

inline bool Enterable::isEntered()
{
    return entered_;
}

inline void Enterable::addHotKey (const BDevices::Keys::KeyType key)
{
    if (std::find (enterHotKeys_.begin(), enterHotKeys_.end(), key) == enterHotKeys_.end()) enterHotKeys_.push_back(key);
}

inline void Enterable::removeHotKey (const BDevices::Keys::KeyType key)
{
    std::list<BDevices::Keys::KeyType>::const_iterator it = std::find (enterHotKeys_.begin(), enterHotKeys_.end(), key);
    if (it != enterHotKeys_.cend()) enterHotKeys_.erase(it);
}

inline bool Enterable::containsHotKey (const BDevices::Keys::KeyType key)
{
    return (std::find (enterHotKeys_.begin(), enterHotKeys_.end(), key) != enterHotKeys_.end());
}

}
#endif /* BWIDGETS_ENTERABLE_HPP_ */