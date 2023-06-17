/* Keys.hpp
 * Copyright (C) 2022 - 2023  Sven Jähnichen
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
	 * @brief Enumeration of commonly used keys
	 *
	 * Also see pugl @a PuglKey.
	 */
	enum class KeyType : uint16_t
	{
		any 		= 0,
		backspace	= 0x08,
		enter		= 0x0D,
		escape		= 0x1B,
		del			= 0x7F,
		f1 			= 0xE000,
 		f2,
		f3,
		f4,
		f5,
		f6,
		f7,
		f8,
		f9,
		f10,
		f11,
		f12,
		left,
		up,
		right,
		down,
		pageUp,
		pageDown,
		home,
		end,
		insert,
		shift,
		shiftL		= shift,
		shiftR,
		ctrl,
		ctrlL		= ctrl,
		ctrlR,
		alt,
		altL		= alt,
		altR,
		super,
		superL		= super,
		superR,
		menu,
		capsLock,
		scrollLock,
		numLock,
		printScreen,
		pause
	};

protected:
	KeyType key_;

public:
    /**
     * @brief  Construct a new Keys device object.
     */
	Keys () : Keys (KeyType::any) {}

	/**s
     * @brief  Construct a new Keys device object for a specified key.
	 *
	 * @param key  Key type (code)
     */
	explicit Keys (const KeyType key) : Device(DeviceType::keys), key_(key) {}

	/**
     * @brief  Creates a clone of this object.
     * 
     * @return  Pointer to the clone.
     */
    virtual Device* clone() const override {return new Keys(*this);}

	/**
	 * @brief  Get the key of the Keys object.
	 * 
	 * @return KeyType  Key code.
	 */
	KeyType getKey() const {return key_;}

	/**
     * @brief Compares this and another device object.
     * 
     * @param rhs  Other object. 
     * @return  True if the device type of this object is less than the
     *          device type of the other object.
     *
     * The virtual method @a less() compares this and another object primarily
     * on the base of their device types. This method can be overridden in 
     * inherriting classes to compare additional parameters. However,
     * comparing additional parameters is only allowed if (i) both objects
     * are from the type (class), and (ii) both objects have got the same
     * device type. 
     */
    virtual bool less (const Device& rhs) const override 
	{
		// lhs.type_ != rhs.type_ ?
		if ((Device::less(rhs) || rhs.Device::less(*this))) return Device::less(rhs);

		// lhs.type_ == rhs.type_ ?
		{
			const Keys* r = dynamic_cast<const Keys*>(&rhs);

			// Same object type : Compare key_
			if (r) return getKey() < r->getKey();
			// Else
			return false;
		}
	}
};

}

#endif /* BWIDGETS_KEYS_HPP_ */
