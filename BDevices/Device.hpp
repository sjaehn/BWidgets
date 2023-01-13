/* Device.hpp
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

#ifndef BWIDGETS_DEVICE_HPP_
#define BWIDGETS_DEVICE_HPP_

#include <chrono>

namespace BDevices 
{

/**
 * @brief  Parent class of all devices. Stores information about the device 
 * type and the time of creation (or action). Device objects (including all
 * objects of child classes) are Comparable by comparison of its device type
 * (and optionally its device parameter type).
 *
 */
class Device
{
public:
	/**
	 * Enumeration of mouse buttons as input device for event handling
	 */
	enum class DeviceType
	{
        KEYS,
        MOUSE
        // TODO WHEEL
	};

protected:
    const DeviceType type_;
	std::chrono::steady_clock::time_point actionTime_;

public:
     /**
     * @brief  Construct a new Device object.
     * 
     * @param dev  Device type code
     * classes.
     */
	explicit Device (const DeviceType dev) : type_(dev), actionTime_ (std::chrono::steady_clock::now()) {}

public:
    virtual ~Device() {}

    Device& operator= (const Device& that) = delete;

    /**
     * @brief  Creates a clone of this object.
     * 
     * @return  Pointer to the clone.
     */
    virtual Device* clone() const {return new Device(*this);}

    /**
     * @brief Get the device type.
     * 
     * @return  Device type 
     */
    DeviceType getDeviceType () const {return type_;}

    /**
     * @brief Set the time point of the last device action manually
     * 
     * @param time  Time of action
     */
    virtual void setActionTime (const std::chrono::steady_clock::time_point& time) {actionTime_ = time;}

    /**
     * @brief Get the time of the last device action
     * 
     * @return std::chrono::steady_clock::time_point 
     */
	std::chrono::steady_clock::time_point getActionTime () const {return actionTime_;}

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
    virtual bool less (const Device& rhs) const {return type_ < rhs.type_;}

    friend inline bool operator< (const Device& lhs, const Device& rhs) {return lhs.less (rhs);}
	friend inline bool operator== (const Device& lhs, const Device& rhs) {return !((lhs < rhs) || (rhs < lhs));}
	friend inline bool operator> (const Device& lhs, const Device& rhs) {return rhs < lhs;}
	friend inline bool operator<=(const Device& lhs, const Device& rhs) {return !(lhs > rhs);}
	friend inline bool operator>=(const Device& lhs, const Device& rhs) {return !(lhs < rhs);}
	friend inline bool operator!=(const Device& lhs, const Device& rhs) {return !(lhs==rhs);}
};

}

#endif /* BWIDGETS_DEVICE_HPP_ */
