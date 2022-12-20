/* StyleProperty.hpp
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

#ifndef BSTYLES_STYLEPROPERTY_HPP_
#define BSTYLES_STYLEPROPERTY_HPP_

#include <cstdint>
#include "../BUtilities/Property.hpp"
#include "../BUtilities/Any.hpp"

#define BSTYLES_STYLEPROPERTY_URI "https://github.com/sjaehn/BWidgets/BStyles/StyleProperty.hpp"
#define BSTYLES_STYLEPROPERTY_BACKGROUND_URI BSTYLES_STYLEPROPERTY_URI "#Backgound"
#define BSTYLES_STYLEPROPERTY_BORDER_URI BSTYLES_STYLEPROPERTY_URI "#Border"
#define BSTYLES_STYLEPROPERTY_FONT_URI BSTYLES_STYLEPROPERTY_URI "#Font"
#define BSTYLES_STYLEPROPERTY_FGCOLORS_URI BSTYLES_STYLEPROPERTY_URI "#FgColors"
#define BSTYLES_STYLEPROPERTY_BGCOLORS_URI BSTYLES_STYLEPROPERTY_URI "#BgColors"
#define BSTYLES_STYLEPROPERTY_TXCOLORS_URI BSTYLES_STYLEPROPERTY_URI "#TxColors"

namespace BStyles
{

/**
 *  @brief  %StyleProperty objects are data assigned to an URID. 
 *
 *  A StyleProperty is a Property that consists of a constant @a URID and the
 *  assigned @a data of Any type. It can only be set upon construction. No 
 *  change, no assignment of the object. Only its member @a data.
 */
class StyleProperty : public BUtilities::Property<uint32_t, BUtilities::Any>
{
public:
    /**
     *  @brief  Constructs a %StyleProperty based on its URID and its data. 
     *  @param urid  Unique identifier value.
     *  @param data  %StyleProperty @a data of Any type.
     *
     *  Note: There's NO default constructor for StyleProperty!
     */
    StyleProperty (const uint32_t urid, const BUtilities::Any& data) :
        BUtilities::Property<uint32_t, BUtilities::Any> (urid, data)
    {

    }

    StyleProperty& operator= (const StyleProperty&) = delete;
};

}
#endif /* BSTYLES_STYLEPROPERTY_HPP_ */