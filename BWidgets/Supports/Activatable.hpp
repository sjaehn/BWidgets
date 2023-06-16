/* Activatable.hpp
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

#ifndef BWIDGETS_ACTIVATABLE_HPP_
#define BWIDGETS_ACTIVATABLE_HPP_

#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Interface class for Support of Widget activation.
 *
 *  %Activatable is a hint for a widget to be able to get activated by an
 *  user interaction. Default is false (inactive)! Implementations of
 *  %Activatable shall enable switching the Widget status between
 *  @c BStyles::Status::normal and @c BStyles::Status::active . All other
 *  @c BStyles::Status shall not be touched.
 *  
 *  %Activatable is (not exclusively) used by Navigalatble menu Widgets to
 *  navigate through menu items.
 *
 *  @note: The Widget status can be forced to set at any
 *  time by `Widget::setStatus()` - independent from %Activatable.
 */
class Activatable : public Support
{
protected:
    bool autoDeactivate_;

public:

    /**
     *  @brief  Constructs a default %Activatable object with INACTIVE 
     *  support.
     */
    Activatable ();

    /**
     *  @brief  Constructs a %Activatable object with a provided support 
     *  status.
     *  @param status  Support status. 
     */
    Activatable (const bool status);

    /**
     *  @brief  Switch the support for Widget activation by the user on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setActivatable (const bool status);

    /**
     *  @brief  Information about the support for Widget activation by the 
     *  user.
     *  @return  True if on, otherwise false.
     */
    bool isActivatable () const;
    
    /**
     *  @brief  Activates this object 
     *  @param status  Optional, true for activation, false for de-activation
     *
     *  Abstract method to be overridden.
     */
    virtual void activate (bool status = true) = 0;

    /**
     *  @brief  De-activates this object 
     */
    virtual void deactivate ();
    
    /**
     *  @brief  Sets the autoDeactivate_ flag
     *  @param status  Optional, true for automatic de-activation, otherwise
     *  false
     * 
     *  Enables or disables the automatic de-activation if an other
     *  %Activatable object gets activated
     */
    virtual void setAutoDeactivate (bool status = true);

    /**
     *  @brief  Gets the status of automatic deactivation upon activation of
     *  an other %Activatable object
     */
    bool isAutoDeactivated();

};

inline Activatable::Activatable () : Activatable (false) {}

inline Activatable::Activatable (const bool status) : 
    Support (status),
    autoDeactivate_(true) 
{}

inline void Activatable::setActivatable (const bool status) {setSupport(status);}

inline bool Activatable::isActivatable () const {return getSupport();}

inline void Activatable::deactivate() {activate (false);}

inline void Activatable::setAutoDeactivate (bool status) {autoDeactivate_ = status;}

inline bool Activatable::isAutoDeactivated() {return autoDeactivate_;}

}
#endif /* BWIDGETS_ACTIVATABLE_HPP_ */