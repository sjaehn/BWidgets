/* Theme.hpp
 * Copyright (C) 2022 Sven Jähnichen
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

#ifndef BSTYLES_THEME_HPP_
#define BSTYLES_THEME_HPP_

#include "Style.hpp"

#define THEME_URI "https://github.com/sjaehn/BWidgets/BStyles/Theme.hpp"

namespace BStyles
{

/**
 *  @brief  Themes containers for Style data.
 *
 *  A %Theme is a std::map container for Styles with the widget 
 *  URID as th key and the Style as value.
 */
class Theme : public std::map<uint32_t, Style>
{
public:


    typedef std::map<uint32_t, Style>::iterator iterator;
    typedef std::map<uint32_t, Style>::const_iterator const_iterator;
    typedef std::map<uint32_t, Style>::reverse_iterator reverse_iterator;
    typedef std::map<uint32_t, Style>::const_reverse_iterator const_reverse_iterator;
    typedef std::map<uint32_t, Style>::reference reference;
    typedef std::map<uint32_t, Style>::const_reference const_reference;
    typedef std::map<uint32_t, Style>::key_type key_type;
    typedef std::map<uint32_t, Style>::value_type value_type;
    typedef std::map<uint32_t, Style>::mapped_type mapped_type;

    
    Theme () = default;

    /**
     *  @brief  Constructs a %Theme from an initializer list of URIDs and 
     *  Styles.
     *  @param list Initializer list of URIDs and Styles.
     */
    Theme (const std::initializer_list<std::pair<const uint32_t, Style>>& list);

    /**
     *  @brief  Checks if a URID exists within the Theme.
     *  @param urid  Property URID.
     *  @return  True if the @a urid exists, otherwise false.
     */
    bool contains (const uint32_t urid) const;


    using std::map<uint32_t, Style>::begin;
    using std::map<uint32_t, Style>::cbegin;
    using std::map<uint32_t, Style>::end;
    using std::map<uint32_t, Style>::cend;
    using std::map<uint32_t, Style>::rbegin;
    using std::map<uint32_t, Style>::crbegin;
    using std::map<uint32_t, Style>::rend;
    using std::map<uint32_t, Style>::crend;
    using std::map<uint32_t, Style>::empty;
    using std::map<uint32_t, Style>::size;
    using std::map<uint32_t, Style>::find;
    using std::map<uint32_t, Style>::operator[];
    using std::map<uint32_t, Style>::insert;
    using std::map<uint32_t, Style>::erase;

};

inline Theme::Theme (const std::initializer_list<std::pair<const uint32_t, Style>>& list) :  
    std::map<uint32_t, Style> ()
{
    for (const std::pair<const uint32_t, Style> l : list) operator[](l.first) = l.second;
}

inline bool Theme::contains (const uint32_t urid) const
{
    return (find (urid) != end());
}

}

#endif /* BSTYLES_THEME_HPP_ */