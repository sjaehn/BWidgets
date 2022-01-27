/* KeyEvent.hpp
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

#ifndef BEVENTS_KEYEVENT_HPP_
#define BEVENTS_KEYEVENT_HPP_

#include <cstdint>
#include <string>
#include "Event.hpp"
#include "../BUtilities/Point.hpp"

namespace BEvents
{

/**
 *  @brief  %KeyEvents are emitted by the system if a key is pressed or 
 *  released.
 */
 class KeyEvent : public Event
 {
 protected:
	BUtilities::Point point_;
	uint32_t key_;

 public:
    
    /**
     *  @brief  Creates an empty %KeyEvent.
     */
	KeyEvent () :
	 	KeyEvent (nullptr, NO_EVENT, 0, 0, 0) 
    {

    }

    /**
     *  @brief  Creates a %KeyEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param x  Pointer x coordinate relative to the widget origin.
     *  @param y  Pointer y coordinate relative to the widget origin.
     *  @param unicode  Key as four byte unicode.
     */
	KeyEvent (BWidgets::Widget* widget, const EventType type, const double x, const double y, const uint32_t unicode) :
		KeyEvent (widget, type, BUtilities::Point (x, y), unicode) 
    {

    }

    /**
     *  @brief  Creates a %KeyEvent.
	 *  @param widget  Pointer to the widget which caused the %Event.
     *  @param type  EventType.
     *  @param position  Pointer coordinates relative to the widget origin.
     *  @param unicode  Key as four byte unicode.
     */
	KeyEvent (BWidgets::Widget* widget, const EventType type, const BUtilities::Point& position, const uint32_t unicode) :
		Event (widget, type),
		point_ (position),
		key_ (unicode) 
    {

    }

    /**
    *  @brief  Redefines the pointer coordinates of the %KeyEvent.
    *  @param coords  Pointer coordinates relative to the widgets origin.
    */
    void setPosition (const BUtilities::Point& coords)
    {
        point_ = coords;
    }

    /**
    *  @brief  Gets the pointer coordinates of the %KeyEvent.
    *  @return  Pointer coordinates relative to the widgets origin.
    */
    BUtilities::Point getPosition () const
    {
        return point_;
    }

    /**
    *  @brief  Gets the key  that caused of the %KeyEvent.
    *  @return  Four byte unicode of the key.
    */
    uint32_t getKey () const
    {
        return key_;
    }

    /**
    *  @brief  Gets the key that caused of the %KeyEvent as UTF8.
    *  @return  Key as UTF8 string.
    */
    std::string getKeyUTF8 () const
    {
        // Invalide unicode
        if (key_ > 0x0010ffff) return "";

        std::string s = "";

        // 7 bit ASCII: utf-8 = unicode
        if (key_ < 0x80) s += char (key_);

        // 2/3/4(/5/6) byte utf-8
        else
        {
            uint32_t steps = 2;
            for (uint32_t i = 3; i <= 6; ++i)
            {
                if (key_ >= (uint32_t (2) << (5 * (i - 1)))) steps = i;
            }

            char c = char ((0xFF & (0xFF << (8 - steps))) | (key_ >> (6 * (steps - 1))));
            s += c;

            for (uint32_t i = steps - 1; i >= 1; --i)
            {
                char c = char (0x80 | ((key_ >> (6 * (i - 1))) & 0x3f));
                s += c;
            }
        }

        return s;
    }
 };

}

#endif /* BEVENTS_KEYEVENT_HPP_ */
