/* Style.hpp
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

#ifndef BSTYLES_STYLE_HPP_
#define BSTYLES_STYLE_HPP_

#include "StyleProperty.hpp"
#include "Types/Border.hpp"
#include "Types/Fill.hpp"
#include "Types/Font.hpp"
#include "Types/ColorMap.hpp"
#include "../BUtilities/Urid.hpp"
#include <initializer_list>

#define BSTYLES_STYLE_URI "https://github.com/sjaehn/BWidgets/BStyles/Style.hpp"

namespace BStyles
{

/**
 *  @brief  Styles recursive containers for StyleProperty data.
 *
 *  A %Style is a std::map container for StyleProperties. Thus, each element
 *  has got an identifier (URID) and a data block.
 *  The data block contains either:
 *  *  a %Style, or
 *  *  Property data of Any type.
 *
 *  The result is a tree of styles with their properties.
 *
 *  Example:
 *  @code 
 *  ┌───────────────────────────────────────────────────────┐
 *  │TEXTBUTTONSTYLE                                        │
 *  │┌────────────────────────────────┐                     │
 *  ││LABELSTYLE                      │                     │
 *  ││┌──────────┐┌───────┐┌─────────┐│                     │
 *  │││FONT      ││TXCOLOR││BGCOLOR  ││┌─────────┐┌────────┐│  
 *  │││sans, 12pt││white  ││invisible│││FGCOLOR  ││BGCOLOR ││ 
 *  ││╰──────────┘╰───────┘╰─────────┘││lightgrey││darkgrey││
 *  │╰────────────────────────────────┘╰─────────┘╰────────┘│
 *  ╰───────────────────────────────────────────────────────┘
 *  @endcode
 */
class Style : public std::map<uint32_t, BUtilities::Any>
{
public:


    typedef std::map<uint32_t, BUtilities::Any>::iterator iterator;
    typedef std::map<uint32_t, BUtilities::Any>::const_iterator const_iterator;
    typedef std::map<uint32_t, BUtilities::Any>::reverse_iterator reverse_iterator;
    typedef std::map<uint32_t, BUtilities::Any>::const_reverse_iterator const_reverse_iterator;
    typedef std::map<uint32_t, BUtilities::Any>::reference reference;
    typedef std::map<uint32_t, BUtilities::Any>::const_reference const_reference;
    typedef std::map<uint32_t, BUtilities::Any>::key_type key_type;
    typedef std::map<uint32_t, BUtilities::Any>::value_type value_type;
    typedef std::map<uint32_t, BUtilities::Any>::mapped_type mapped_type;


    
    Style () = default;

    /**
     *  @brief  Constructs a %Style with its @a urid and @a data of Any type.
     *  @param urid  URID.
     *  @param data  Data of Any type.
     */
    Style (const uint32_t urid, BUtilities::Any data);

    /**
     *  @brief  Constructs a %Style from a single StyleProperty.
     *  @param property  StyleProperty.
     */
    Style (const StyleProperty& property);

    /**
     *  @brief  Constructs a %Style from a Property vector and an @a urid.
     *  @param urid  URID.
     *  @param properties Initializer list of properties.
     */
    Style (const std::initializer_list<StyleProperty>& properties);

    /**
     *  @brief  Checks if an included element with the provided @a urid exists
     *  at the base level of the tree.
     *  @param urid  Property URID.
     *  @return  True if the @a urid exists, otherwise false.
     *
     *  Search for an included element with the provided @a urid. Use this
     *  method to check for a missing @a urid prior element access using
     *  operator[], if you don't want to create a new (sub-)style with
     *  operator[].
     */
    bool contains (const uint32_t urid) const;

    /**
     *  @brief  Tests if an element is a %Style too.
     *  @param it  Iterator for the element.
     *  @return  True, if the element is a %Style, otherwise false.
     *
     *  %isStyle shall be called to test if the element is a %Style element
     *  of the tree or if it is a data end point.
     */
    bool isStyle (const_iterator it) const;

    /**
     *  @brief  Tests if an element is a %Style too.
     *  @param urid  URID.
     *  @return  True, if the element is a %Style, otherwise false.
     *
     *  %isStyle shall be called to test if the element is a %Style element
     *  of the tree or if it is a data end point.
     */
    bool isStyle (const uint32_t urid) const;


    using std::map<uint32_t, BUtilities::Any>::begin;
    using std::map<uint32_t, BUtilities::Any>::cbegin;
    using std::map<uint32_t, BUtilities::Any>::end;
    using std::map<uint32_t, BUtilities::Any>::cend;
    using std::map<uint32_t, BUtilities::Any>::rbegin;
    using std::map<uint32_t, BUtilities::Any>::crbegin;
    using std::map<uint32_t, BUtilities::Any>::rend;
    using std::map<uint32_t, BUtilities::Any>::crend;
    using std::map<uint32_t, BUtilities::Any>::empty;
    using std::map<uint32_t, BUtilities::Any>::size;
    using std::map<uint32_t, BUtilities::Any>::find;
    using std::map<uint32_t, BUtilities::Any>::operator[];
    using std::map<uint32_t, BUtilities::Any>::insert;
    using std::map<uint32_t, BUtilities::Any>::erase;


    /**
     *  @brief  Gets the border Property from the base level.
     *  @return  Border.
     *
     *  Gets the base level border Property using the default border URID.
     *  Returns noBorder if the default border URID is not set.
     */
    Border getBorder() const;

    /**
     *  @brief  Sets the border Property at the base level.
     *  @param border  Border.
     *
     *  Sets the base level border Property using the default border URID.
     */
    void setBorder(const Border& border);

    /**
     *  @brief  Gets the background Property from the base level.
     *  @return  Background.
     *
     *  Gets the base level background Property using the default background 
     *  URID. Returns noFill if the default background URID is not set.
     */
    Fill getBackground() const;

    /**
     *  @brief  Sets the background Property at the base level.
     *  @param fill  Background.
     *
     *  Sets the base level background Property using the default background 
     *  URID.
     */
    void setBackground (const Fill& fill);

    /**
     *  @brief  Gets the font Property from the base level.
     *  @return  Font.
     *
     *  Gets the base level font property using the default font URID.
     *  Returns sans12pt if the default font URID is not set.
     */
    Font getFont() const;

    /**
     *  @brief  Sets the font property at the base level.
     *  @param font  Font.
     *
     *  Sets the base level font Property using the default font URID.
     */
    void setFont (const Font& font);

    /**
     *  @brief  Gets the foreground colors Property from the base level.
     *  @return  Foreground ColorMap.
     *
     *  Gets the base level foreground colors Property using the default 
     *  foreground colors URID. Returns whites if the default foreground 
     *  colors URID is not set.
     */
    ColorMap getFgColors() const;

    /**
     *  @brief  Sets the foreground colors Property at the base level.
     *  @param colors  Foreground ColorMap.
     *
     *  Sets the base level foreground colors Property using the default 
     *  foreground colors URID.
     */
    void setFgColors (const ColorMap& colors);

    /**
     *  @brief  Gets the background colors Property from the base level.
     *  @return  Background ColorMap.
     *
     *  Gets the base level background colors Property using the default 
     *  background colors URID. Returns darks if the default background colors
     *  URID is not set.
     */
    ColorMap getBgColors() const;

    /**
     *  @brief  Sets the background colors Property at the base level.
     *  @param colors  Background ColorMap.
     *
     *  Sets the base level background colors Property using the default 
     *  background colors URID.
     */
    void setBgColors (const ColorMap& colors);

    /**
     *  @brief  Gets the text colors Property from the base level.
     *  @return  Text ColorMap.
     *
     *  Gets the base level text colors Property using the default text colors
     *  URID. Returns whites if the default text colors URID is not set.
     */
    ColorMap getTxColors() const;

    /**
     *  @brief  Sets the text colors Property at the base level.
     *  @param colors  Text ColorMap.
     *
     *  Sets the base level text colors Property using the default text
     *  colors URID.
     */
    void setTxColors (const ColorMap& colors);

};

inline Style::Style (const uint32_t urid, BUtilities::Any data) :  
    std::map<uint32_t, BUtilities::Any> ()
{
    insert (value_type (urid, data));
}

inline Style::Style (const StyleProperty& property) :
    std::map<uint32_t, BUtilities::Any> ()
{
    insert (property);
}

inline Style::Style (const std::initializer_list<StyleProperty>& properties) :  
    std::map<uint32_t, BUtilities::Any> ()
{
    for (const StyleProperty& s : properties) insert (s);
}

inline bool Style::contains (const uint32_t urid) const
{
    return (find (urid) != end());
}

inline bool Style::isStyle (const_iterator it) const
{
    return (it->second.dataTypeHash() == typeid(Style).hash_code());
}

inline bool Style::isStyle (const uint32_t urid) const
{
    const_iterator it = find (urid);
    return ((it != end()) && isStyle (it));
}

inline Border Style::getBorder() const
{
    const_iterator it = find (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI));
    if ((it == end()) || isStyle (it)) return noBorder;
    else return it->second.get<Border>();
}

inline void Style::setBorder(const Border& border)
{
    operator[] (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_BORDER_URI)) = BUtilities::makeAny<Border> (border);
}

inline Fill Style::getBackground() const
{
    const_iterator it = find (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI));
    if ((it == end()) || isStyle (it)) return noFill;
    else return it->second.get<Fill>();
}

inline void Style::setBackground(const Fill& fill)
{
    operator[] (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_BACKGROUND_URI)) = BUtilities::makeAny<Fill> (fill);
}

inline Font Style::getFont() const
{
    const_iterator it = find (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI));
    if ((it == end()) || isStyle (it)) return sans12pt;
    else return it->second.get<Font>();
}

inline void Style::setFont(const Font& font)
{
    operator[] (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_FONT_URI)) = BUtilities::makeAny<Font> (font);
}

inline ColorMap Style::getFgColors() const
{
    const_iterator it = find (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI));
    if ((it == end()) || isStyle (it)) return greens;
    else return it->second.get<ColorMap>();
}

inline void Style::setFgColors (const ColorMap& colors)
{
    operator[] (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_FGCOLORS_URI)) = BUtilities::makeAny<ColorMap> (colors);
}

inline ColorMap Style::getBgColors() const
{
    const_iterator it = find (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI));
    if ((it == end()) || isStyle (it)) return darks;
    else return it->second.get<ColorMap>();
}

inline void Style::setBgColors (const ColorMap& colors)
{
    operator[] (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_BGCOLORS_URI)) = BUtilities::makeAny<ColorMap> (colors);
}

inline ColorMap Style::getTxColors() const
{
    const_iterator it = find (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI));
    if ((it == end()) || isStyle (it)) return whites;
    else return it->second.get<ColorMap>();
}

inline void Style::setTxColors (const ColorMap& colors)
{
    operator[] (BUtilities::Urid::urid (BSTYLES_STYLEPROPERTY_TXCOLORS_URI)) = BUtilities::makeAny<ColorMap> (colors);
}



}

#endif /* BSTYLES_STYLE_HPP_ */