/* MouseButton.hpp
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

#ifndef BWIDGETS_MOUSEBUTTON_HPP_
#define BWIDGETS_MOUSEBUTTON_HPP_

#include "../BUtilities/Point.hpp"
#include "Device.hpp"

namespace BDevices 
{

/**
 * @brief  Class to store mouse informations for each button (incl. no button)
 * like position, and time of action.
 * @tparam DEVICE  Device type code for the respective mouse button.
 * 
 */
class MouseButton : public Device
{
public:
    enum class ButtonType
    {
        none    = 0,
		left,
		middle,
		right
    };

protected:
    ButtonType button_;
    BUtilities::Point<> position_;

public:
    /**
     * @brief  Construct a new mouse button device object with default data 
     * (position: 0, 0).
     * 
     * @param but  Button type code
     */
	explicit MouseButton (const ButtonType but);

    /**
     * @brief  Construct a new mouse button device object.
     * 
     * @param but  Button type code
     * @param pos  Position (x, y)
     */
	MouseButton (const ButtonType but, const BUtilities::Point<>& pos);

    /**
     * @brief  Creates a clone of this object.
     * 
     * @return  Pointer to the clone.
     */
    virtual Device* clone() const override;

    /**
	 * @brief  Get the button code for this object.
	 * 
	 * @return ButtonType  Button code.
	 */
    ButtonType getButton() const;

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
    virtual bool less (const Device& rhs) const override; 

    /**
     * @brief  Set the position of the mouse button device and the action time 
     * at now.
     * 
     * @param pos  Position (x, y)
     */
    virtual void setPosition (const BUtilities::Point<>& pos);

    /**
     * @brief  Set the position of the mouse button device and the action time.
     * 
     * @param pos  Position (x, y)
     * @param time  Time of action
     */
    virtual void setPosition (const BUtilities::Point<>& pos, const std::chrono::steady_clock::time_point& time);

    /**
     * @brief  Get the position of the mouse button device
     * 
     * @return  Position (x, y) 
     */
    BUtilities::Point<> getPosition () const;
};

inline MouseButton::MouseButton(const ButtonType but) : 
    MouseButton (but, BUtilities::Point<>(0, 0)) 
{

}

inline MouseButton::MouseButton(const ButtonType but, const BUtilities::Point<>& pos) : 
    Device(DeviceType::mouse),
    button_(but),
    position_(pos) 
{

}

inline Device* MouseButton::clone() const
{
    return new MouseButton(*this);
}

inline MouseButton::ButtonType MouseButton::getButton() const 
{
    return button_;
}

inline bool MouseButton::less (const Device& rhs) const
{
    // lhs.type_ != rhs.type_ ?
    if ((Device::less(rhs) || rhs.Device::less(*this))) return Device::less(rhs);

    // lhs.type_ == rhs.type_ ?
    {
        const MouseButton* r = dynamic_cast<const MouseButton*>(&rhs);

        // Same object type : Compare button_
        if (r) return getButton() < r->getButton();
        // Else
        return false;
    }
}

inline void MouseButton::setPosition (const BUtilities::Point<>& pos) 
{
    setPosition (pos, std::chrono::steady_clock::now());
}

inline void MouseButton::setPosition (const BUtilities::Point<>& pos, const std::chrono::steady_clock::time_point& time)
{
    position_ = pos;
    actionTime_ = time;
}

inline BUtilities::Point<> MouseButton::getPosition () const
{
    return position_;
}

}

#endif /* BWIDGETS_MOUSEBUTTON_HPP_ */
