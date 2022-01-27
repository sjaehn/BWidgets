/* Property.hpp
 * Copyright (C) 2021 - 2022  Sven Jähnichen
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

#ifndef BUTILITIES_PROPERTY_HPP_
#define BUTILITIES_PROPERTY_HPP_

#include <utility>

namespace BUtilities
{

/**
 *  @brief %Properties are data assigned to an identifier. 
 *  @tparam Tid  Type of the identifier.
 *  @tparam Tdata  Type of the assigned @a data.
 *
 *  A property is a data pair and consists of a constant @a ID and the assigned
 *  @a data. It can only be set upon construction. No change, no assignment.
 */
template <class Tid, class Tdata>
class Property : public std::pair<const Tid, Tdata>
{
protected:

public:

    /**
     *  @brief  Creates a %Property.
     *  @param id  Unique identifier for the @a data.
     *  @param data  New @a data to be stored inside the %Property. Data 
     *  MUST be copy assignable.
     *
     *  Properties can only be created. Not assigned. Once a %Property is
     *  created, its @a id can't be changed anymore. 
     */
    constexpr Property (const Tid& id, const Tdata& data) : 
        std::pair<const Tid, Tdata> (id, data) 
    {

    }

    Property<Tid, Tdata>& operator= (const Property<Tid, Tdata>& that) = delete;

    /**
     *  @brief Access to the %Property @a data. 
     *  @return  %Property data.
     */
    virtual Tdata& data () {return std::pair<const Tid, Tdata>::second;}
    virtual const Tdata& data () const {return std::pair<const Tid, Tdata>::second;}

    /**
     *  @brief Returns the %Property identifier. 
     *  @return  %Property identifier.
     */
    virtual Tid getId () const {return std::pair<const Tid, Tdata>::first;}

};

}

#endif /* BUTILITIES_PROPERTY_HPP_ */