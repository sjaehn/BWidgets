/* Toggleable.hpp
 * Copyright (C) 2018 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_TOGGLEABLE_HPP_
#define BWIDGETS_TOGGLEABLE_HPP_

#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Base Interface class for Support of Button toggling.
 */
class Toggleable : public Support
{
public:

    /**
     *  @brief  Switch the support for button toggling on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setToggleable (const bool status) {setSupport(status);}

    /**
     *  @brief  Information about the support for button toggling.
     *  @return  True if on, otherwise false.
     */
    bool isToggleable () const {return getSupport();}

};

}
#endif /* BWIDGETS_TOGGLEABLE_HPP_ */