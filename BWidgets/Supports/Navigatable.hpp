/* Navigatable.hpp
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

#ifndef BWIDGETS_NAVIGATABLE_HPP_
#define BWIDGETS_NAVIGATABLE_HPP_

#include "../Widget.hpp"
#include "Activatable.hpp"
#include "Linkable.hpp"
#include "Enterable.hpp"

namespace BWidgets
{

/**
 *  @brief  Interface class for Support of navigation between Activatable 
 *  child Widgets within a Widget.
 */
class Navigatable : public Support
{
public:

    /**
     *  @brief  Constructs a default %Navigatable object
     */
    Navigatable ();

    /**
     *  @brief  Constructs a %Navigatable object with a provided support 
     *  status.
     *  @param status  Support status. 
     */
    Navigatable (const bool status);

    /**
     *  @brief  Switch the support for child Widget navigation on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setNavigatable (const bool status);

    /**
     *  @brief  Information about the support for child Widget navigation
     *  @return  True if on, otherwise false.
     */
    bool isNavigatable () const;
    
    
    /**
     *  @brief  Navigates backward 
     *  @return  Pointer to the Activatable object navigated to or @c nullptr
     *  if not possible.
     * 
     *  Activates the previous Activatable child Widget. Activates the first
     *  Activatable child Widget if no Activatable child widget is activated
     *  yet.
     */
    virtual Activatable* navigateBackward ();

    /**
     *  @brief  Navigates forward 
     *  @return  Pointer to the Activatable object navigated to or @c nullptr
     *  if not possible.
     * 
     *  Activates the next Activatable child Widget. Activates the first
     *  Activatable child Widget if no Activatable child widget is activated
     *  yet.
     */
    virtual Activatable* navigateForward ();

    /**
     *  @brief  Navigates to the first Activatable child Widget
     *  @return  Pointer to the Activatable object navigated to or @c nullptr
     *  if not possible.
     */
    virtual Activatable* navigateToStart ();

     /**
     *  @brief  Navigates to an Activatable child Widget
     *  @param act  Pointer to the Activatable child object.
     *  @return  Pointer to the Activatable object navigated to or @c nullptr
     *  if not possible.
     */
    virtual Activatable* navigateTo (Activatable* act);

    /**
     *  @brief  Enters the first activated Activatable child Widget.
     */
    virtual void enterNavigated ();

    /**
     *  @brief  De-activates all Activatable child widgets.
     */
    virtual void resetNavigation ();

    /**
     *  @brief  Checks if navigation has been performed.
     * 
     *  @return  True if this object is navigatable and at least one 
     *  Activatable child Widget is activated. 
     */
    bool isNavigated();


protected:

    /**
     *  @brief  Gets the first activated Activatable child Widget.
     * 
     *  @return  Pointer to the first activated Activatable child Widget
     *  or @c nullptr if no match. 
     */
    Activatable* getFirstActivatedChild () const;
};

inline Navigatable::Navigatable () : Support (true) {}

inline Navigatable::Navigatable (const bool status) : 
    Support (status)
{}

inline void Navigatable::setNavigatable (const bool status) {setSupport(status);}

inline bool Navigatable::isNavigatable () const {return getSupport();}

inline Activatable* Navigatable::navigateBackward() 
{
    if (isNavigatable())
    {
        Linkable* l = dynamic_cast<Linkable*>(this);
        Linkable* present = dynamic_cast<Linkable*>(getFirstActivatedChild());
        if (l && present)
        {
            std::list<Linkable*>::const_iterator presentIt = std::find (l->getChildren().begin(), l->getChildren().end(), present);
            if (presentIt != l->getChildren().end())
            {
                
                for (std::list<Linkable*>::const_iterator it = presentIt ; it != l->getChildren().begin() ; /* empty */)
                {
                    --it;
                    Activatable* a = dynamic_cast<Activatable*>(*it);
                    if (a && (a->isActivatable())) 
                    {
                        a->activate();
                        return a;
                    }
                }
            }

            return dynamic_cast<Activatable*>(present);
        }

        else return navigateToStart();
    }

    return nullptr;
}

inline Activatable* Navigatable::navigateForward () 
{
    if (isNavigatable())
    {
        
        Linkable* l = dynamic_cast<Linkable*>(this);
        Linkable* present = dynamic_cast<Linkable*>(getFirstActivatedChild());
        if (l && present)
        {
            std::list<Linkable*>::const_iterator presentIt = std::find (l->getChildren().begin(), l->getChildren().end(), present);
            if (presentIt != l->getChildren().end())
            {
                for (std::list<Linkable*>::const_iterator it = std::next (presentIt) ; it != l->getChildren().end() ; ++it)
                {
                    Activatable* a = dynamic_cast<Activatable*>(*it);
                    if (a && (a->isActivatable())) 
                    {
                        a->activate();
                        return a;
                    }
                }
            }

            return dynamic_cast<Activatable*>(present);
        }

        else return navigateToStart();
    }

    return nullptr;
}

inline Activatable* Navigatable::navigateToStart () 
{
    if (isNavigatable())
    {
        Linkable* l = dynamic_cast<Linkable*>(this);
        if (l)
        {
            for (std::list<Linkable*>::const_iterator it = l->getChildren().begin() ; it != l->getChildren().end() ; ++it)
            {
                Activatable* a = dynamic_cast<Activatable*>(*it);
                if (a && (a->isActivatable()))
                {
                    a->activate();
                    return a;
                }
            }
        }
    }

    return nullptr;
}

inline Activatable* Navigatable::navigateTo (Activatable* act)
{
    if (isNavigatable())
    {
        if (act && (act->isActivatable())) 
        {
            act->activate();
            return act;
        }
    }
    return getFirstActivatedChild();
}

inline void Navigatable::enterNavigated ()
{
    if (isNavigatable())
    {
        Activatable* a = getFirstActivatedChild();
        if (a)
        {
            Enterable* e = dynamic_cast<Enterable*>(a);
            if (e && e->isEnterable()) e->enter();
        }
    }
}

inline void Navigatable::resetNavigation ()
{
    if (isNavigatable())
    {
        const Linkable* l = dynamic_cast<const Linkable*>(this);
        if (l)
        {
            for (std::list<Linkable*>::const_iterator it = l->getChildren().begin() ; it != l->getChildren().end() ; ++it)
            {
                Activatable* a = dynamic_cast<Activatable*>(*it);
                if (a && a->isActivatable()) a->deactivate();
            }
        }
    }
}

inline bool Navigatable::isNavigated()
{
    return (getFirstActivatedChild() != nullptr);
}

inline Activatable* Navigatable::getFirstActivatedChild () const
{
    if (isNavigatable())
    {
        const Linkable* l = dynamic_cast<const Linkable*>(this);
        if (l)
        {
            for (std::list<Linkable*>::const_iterator it = l->getChildren().begin() ; it != l->getChildren().end() ; ++it)
            {
                Widget* w = dynamic_cast<Widget*>(*it);
                Activatable* a = dynamic_cast<Activatable*>(*it);
                if (w && a && a->isActivatable() && (w->getStatus() == BStyles::Status::active)) return a;
            }
        }
    }
	return nullptr;
}

}
#endif /* BWIDGETS_NAVIGATABLE_HPP_ */