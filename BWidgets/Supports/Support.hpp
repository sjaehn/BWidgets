/* Support.hpp
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

#ifndef BWIDGETS_SUPPORT_HPP_
#define BWIDGETS_SUPPORT_HPP_

namespace BWidgets
{

/**
 * @brief  Base class of all Supports
 * 
 */
class Support
{
protected:
    bool support_ = true; 
public:

    virtual ~Support() {};

    /**
     *  @brief  Switch the support on/off.
     *  @param status  True if on, otherwise false.
     */
    virtual void setSupport (const bool support) {support_ = support;}

    /**
     *  @brief  Information about the support status.
     *  @return  True if on, otherwise false.
     */
    bool getSupport () const {return support_;}
};

}
#endif /* BWIDGETS_SUPPORT_HPP_ */