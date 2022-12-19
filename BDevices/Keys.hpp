/* Keys.hpp
 * Copyright (C) 2022  Sven Jähnichen
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

#ifndef BWIDGETS_KEYS_HPP_
#define BWIDGETS_KEYS_HPP_

#include "Device.hpp"

namespace BDevices 
{

/**
 * @brief  Keyboard support
 *
 */
class Keys : public Device
{
public:
	/**
	 * Enumeration of commonly used keys
	 */
	enum KeyType
	{
		KEY_ANY 	= 0,
		KEY_F1		= 0xE000,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_LEFT,
		KEY_UP,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_INSERT,
		KEY_SHIFT,
		KEY_CTRL,
		KEY_ALT,
		KEY_SUPER
	};

public:
    /**
     * @brief  Construct a new Keys device object.
     */
	Keys () : Keys (KEY_ANY) {}

	/**
     * @brief  Construct a new Keys device object for a specified key.
	 *
	 * @param key  Key type (code)
     */
	Keys (const KeyType key) : Device(DEVICE_KEYS, key) {}

	/**
     * @brief  Creates a clone of this object.
     * 
     * @return  Pointer to the clone.
     */
    virtual Device* clone() const override {return new Keys(*this);}
};

}

#endif /* BWIDGETS_KEYS_HPP_ */
