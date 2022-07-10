/* HPianoRoll.hpp
 * Copyright (C) 2019 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_HPIANOROLL_HPP_
#define BWIDGETS_HPIANOROLL_HPP_

#include "Widget.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Toggleable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include <cmath>
#include <cstdint>
#include <vector>
#include <array>

#ifndef BWIDGETS_DEFAULT_HPIANOROLL_WIDTH
#define BWIDGETS_DEFAULT_HPIANOROLL_WIDTH 400.0
#endif

#ifndef BWIDGETS_DEFAULT_HPIANOROLL_HEIGHT
#define BWIDGETS_DEFAULT_HPIANOROLL_HEIGHT 40.0
#endif

namespace BWidgets
{

/*
 *  @brief  Horizontal piano roll widget.
 *
 *  %HPianoRoll is a Valueable Widget displaying a horizontal piano roll.
 *  It supports user interaction via Clickable, Draggable, and Toggleable. Its
 *  appearance is defined by the BgColors parameter (inactive keys) and by the 
 *  FgColors parameter (active keys).
 */
class HPianoRoll : 	public Widget, 
					public ValueableTyped<std::map<uint8_t, uint8_t>>,
					public Clickable,
					public Draggable,
					public Toggleable
{
protected:
	uint8_t startMidiKey_;
	uint8_t endMidiKey_;
	uint8_t defaultVelocity_;

public:

	/**
	 *  @brief  Constructs a default %HPianoRoll object. 
	 */
	HPianoRoll ();

	/**
	 *  @brief  Constructs a default %HPianoRoll object. 
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	HPianoRoll (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %HPianoRoll with default size and initialized key 
	 *  velocities.
	 *  @param startMidiKey  First MIDI key number of the roll.
	 *  @param endMidiKey  Last MIDI key number of the roll.
	 *  @param keys  Map containing active keys (key_value) and their
	 *  respective velocities (mapped_value).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HPianoRoll	(const uint8_t startMidiKey, uint8_t endMidiKey = 127, std::map<uint8_t, uint8_t> keys = {}, 
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HPianoRoll with keys in the default (released) 
	 *  state.
	 *  @param x  %HPianoRoll X origin coordinate.
	 *  @param y  %HPianoRoll Y origin coordinate.
	 *  @param width  %HPianoRoll width.
	 *  @param height  %HPianoRoll height.
	 *  @param startMidiKey  First MIDI key number of the roll.
	 *  @param endMidiKey  Last MIDI key number of the roll.
	 *  @param keys  Vector containing active keys.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HPianoRoll	(const double x, const double y, const double width, const double height, 
				 uint8_t startMidiKey = 0, uint8_t endMidiKey = 127, std::vector<uint8_t> keys = {}, 
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");
	
	/**
	 *  @brief  Creates a %HPianoRoll with initialized key velocities.
	 *  @param x  %HPianoRoll X origin coordinate.
	 *  @param y  %HPianoRoll Y origin coordinate.
	 *  @param width  %HPianoRoll width.
	 *  @param height  %HPianoRoll height.
	 *  @param startMidiKey  First MIDI key number of the roll.
	 *  @param endMidiKey  Last MIDI key number of the roll.
	 *  @param keys  Map containing active keys (key_value) and their
	 *  respective velocities (mapped_value).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HPianoRoll	(const double x, const double y, const double width, const double height, 
				 const uint8_t startMidiKey, const uint8_t endMidiKey, const std::map<uint8_t, uint8_t>& keys, 
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %HPianoRoll. 
	 *  @return  Pointer to the new %HPianoRoll.
	 *
	 *  Creates a clone of this %HPianoRoll by copying all properties. But NOT 
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %HPianoRoll. 
	 *  @param that  Other %HPianoRoll.
	 *
	 *  Copies all properties from another %HPianoRoll. But NOT its linkage.
	 */
	void copy (const HPianoRoll* that);
	
	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area. Resizes the widget to its standard size if this widget doesn't 
	 *  have any children.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the widget extends.
	 *  @param width  New widget width.
	 *  @param height  New widget height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the widget extends.
	 *  @param extends  New widget extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

	/**
	 *  @brief Sets the MIDI key range of the HPianoRoll.
	 *  @param startMidiKey  First MIDI key number of the roll.
	 *  @param endMidiKey  Last MIDI key number of the roll.
	 */
	void setRange (const uint8_t startMidiKey, const uint8_t endMidiKey);

	/**
	 *  @brief  Gets the start of the MIDI key range of the HPianoRoll.
	 *  @return  First MIDI key number of the roll.
	 */
	uint8_t getStart () const;

	/**
	 *  @brief  Gets the end of the MIDI key range of the HPianoRoll.
	 *  @return  Last MIDI key number of the roll.
	 */
	uint8_t getEnd () const;

	/**
	 *  @brief  Activates (or inactivates) all keys. 
	 *  @param active  True if active (default), otherwise false.
	 */
	void activate (bool active = true);

	/**
	 *  @brief  Activates (or inactivates) a single key and keeps the 
	 *  activation status of the remaining keys. 
	 *  @param key  MIDI key number.
	 *  @param active  True if active (default), otherwise false.
	 */
	void activate (const uint8_t key, bool active = true);

	/**
	 *  @brief  Activates (or inactivates) a range of keys and keeps the 
	 *  activation status of the remaining keys. 
	 *  @param from  MIDI key number of the range start.
	 *  @param to  MIDI key number of the range end.
	 *  @param active  True if active (default), otherwise false.
	 */
	void activate (const uint8_t from, const uint8_t to, bool active = true);

	/**
	 *  @brief  Activates all passed keys and inactivates the remaining keys. 
	 *  @param keys  Vector containing the MIDI key numbers of the keys to be
	 *  activated.
	 */
	void activate (const std::vector<uint8_t>& keys);

	/**
	 *  @brief  Checks if the key is active. 
	 *  @param key  MIDI key number.
	 *  @return  True if active, otherwise false.
	 */
	bool isActive (const uint8_t key) const;

	/**
	 *  @brief  Gets a vector of MIDI key numbers for all active keys.
	 *  @return  Vector of MIDI key numbers for all active keys.
	 */
	std::vector<uint8_t> getActive () const;

	/**
	 *  @brief  Presses (or releases) a single key (if active), and keeps the 
	 *  remaining keys. 
	 *  @param key  MIDI key number.
	 *  @param velocity  MIDI velocity of pressed keys. 0 for release.
	 */
	void setKey (const uint8_t key, uint8_t velocity);

	/**
	 *  @brief  Gets the velosity of a single key. 
	 *  @param key  MIDI key number.
	 *  @return  MIDI velocity for pressed keys. 0 for released (or invalid).
	 */
	uint8_t getKey (const uint8_t key) const;

	/**
	 *  @brief  Presses all passed keys, and releases the remaining keys (if 
	 *  active). 
	 *  @param keys  Vector containing keys with std::pairs of key number 
	 *  (first) and velocity (second).
	 *  @param velocity  MIDI velocity of pressed keys. 0 for release.
	 */
	void setKeys (const std::vector<uint8_t>& keys, uint8_t velocity);

	/**
	 *  @brief  Presses all passed keys, and releases the remaining keys (if 
	 *  active). 
	 *  @param keys  Map containing key number (key_value) and velocity 
	 *  (mapped_value).
	 */
	void setKeys (const std::map<uint8_t, uint8_t>& keys);

	/**
	 *  @brief Gets a map for all active keys.
	 *  @return Map containing key number (key_value) and velocity 
	 *  (mapped_value). 
	 */
	std::map<uint8_t, uint8_t> getKeys () const;

	/**
	 *  @brief Sets the velocity to be applied upon clicking on a key.
	 *  @param velocity  MIDI velocity [0,127].
	 */
	void setVelocity (const uint8_t velocity);

	/**
	 *  @brief Gets the velocity which is applied upon clicking on a key.
	 *  @param return  MIDI velocity [0,127].
	 */
	uint8_t getVelocity () const;

	/**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. Sets the key velocity to the default velocity 
	 *  if the key is active. Also sets the widget value to (key number, 
	 *  default velocity) and calls the widget static callback function.
     */
    virtual void onButtonPressed (BEvents::Event* event) override;

	/**
     *  @brief  Method called when pointer button released.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button released. Sets the key velocity to 0 if the key is
	 *  active. Also sets the widget value to (key number, 0) and calls the 
	 *  widget static callback function.
     */
    virtual void onButtonReleased (BEvents::Event* event) override;

	/**
     *  @brief  Method called upon pointer drag.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a pointer drag. Changes the value and calls the widget static callback
	 *  function.
     */
    virtual void onPointerDragged (BEvents::Event* event) override;

protected:
	
	/**
	 *  @brief  Gets the key number for a position within the widget.
	 *  @param position  Position within the widget.
	 *  @return  MIDI key number (or 255 for invalid).
	 */
	virtual uint8_t getKey (const BUtilities::Point<>& position);

	/**
     *  @brief  Unclipped draw a %HPianoRoll to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %HPianoRoll to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %HPianoRoll to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

struct PianoKeyCoords
{
	bool whiteKey;
	double x;
	double dx1;
	double dx2;
	double width;
};

constexpr std::array<PianoKeyCoords, 12> keyCoords=
{{
	{true, 0.0, 0.0, 0.4167, 1.0},
	{false, 0.5833, 0.0, 0.0, 0.6667},
	{true, 1.0, 0.25, 0.25, 1.0},
	{false, 1.75, 0, 0, 0.6667},
	{true, 2, 0.4167, 0, 1},
	{true, 3, 0, 0.5, 1},
	{false, 3.5, 0, 0, 0.6667},
	{true, 4, 0.1667, 0.3333, 1},
	{false, 4.6667, 0, 0, 0.6667},
	{true, 5, 0.3333, 0.1667, 1},
	{false, 5.8333, 0, 0, 0.6667},
	{true, 6, 0.5, 0, 1}
}};


inline HPianoRoll::HPianoRoll () :
	HPianoRoll (0, 0, BWIDGETS_DEFAULT_HPIANOROLL_WIDTH, BWIDGETS_DEFAULT_HPIANOROLL_HEIGHT, 0, 127, std::map<uint8_t, uint8_t>(), URID_UNKNOWN_URID, "")
{

}

inline HPianoRoll::HPianoRoll (const uint32_t urid, const std::string& title) :
	HPianoRoll	(0, 0, BWIDGETS_DEFAULT_HPIANOROLL_WIDTH, BWIDGETS_DEFAULT_HPIANOROLL_HEIGHT, 
				 0, 127, std::map<uint8_t, uint8_t>(),
				 urid, title)
{

}

inline HPianoRoll::HPianoRoll	(const uint8_t startMidiKey, uint8_t endMidiKey, std::map<uint8_t, uint8_t> keys, 
				 				 uint32_t urid, std::string title) :
	HPianoRoll	(0, 0, BWIDGETS_DEFAULT_HPIANOROLL_WIDTH, BWIDGETS_DEFAULT_HPIANOROLL_HEIGHT, 
				 startMidiKey, endMidiKey, keys, 
				 urid, title)
{

}

inline HPianoRoll::HPianoRoll	(const double x, const double y, const double width, const double height, 
								 uint8_t startMidiKey, uint8_t endMidiKey, std::vector<uint8_t> keys, 
								 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<std::map<uint8_t, uint8_t>> (),
	Clickable(),
	Draggable(),
	Toggleable(),
	startMidiKey_(startMidiKey),
	endMidiKey_ (endMidiKey),
	defaultVelocity_ (64)
{
	setToggleable (false);
	activate (keys);
}
	
inline HPianoRoll::HPianoRoll	(const double x, const double y, const double width, const double height, 
								 const uint8_t startMidiKey, const uint8_t endMidiKey, const std::map<uint8_t, uint8_t>& keys, 
								 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<std::map<uint8_t, uint8_t>> (keys),
	Clickable(),
	Draggable(),
	Toggleable(),
	startMidiKey_(startMidiKey),
	endMidiKey_ (endMidiKey),
	defaultVelocity_ (64)
{
	setToggleable (false);
}

inline Widget* HPianoRoll::clone () const
{
	Widget* f = new HPianoRoll (urid_, title_);
	f->copy (this);
	return f;
}

inline void HPianoRoll::copy (const HPianoRoll* that)
{
	startMidiKey_ = that->startMidiKey_;
	endMidiKey_ = that->endMidiKey_;
	defaultVelocity_ = that->defaultVelocity_;
	Toggleable::operator= (*that);
	Draggable::operator= (*that);
	Clickable::operator= (*that);
	ValueableTyped<std::map<uint8_t, uint8_t>>::operator= (*that);
	Widget::copy (that);
}

inline void HPianoRoll::resize ()
{
	BUtilities::Area<> a = (children_.empty()? BUtilities::Area<>(0, 0, BWIDGETS_DEFAULT_HPIANOROLL_WIDTH, BWIDGETS_DEFAULT_HPIANOROLL_HEIGHT) : BUtilities::Area<>());
	for (Linkable* c : children_)
	{
		Widget* w = dynamic_cast<Widget*>(c);
		if (w) a.extend (BUtilities::Area<>(w->getPosition(), w->getPosition() + w->getExtends()));
	}

	resize (a.getExtends());
}

inline void HPianoRoll::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void HPianoRoll::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void HPianoRoll::setRange (const uint8_t startMidiKey, const uint8_t endMidiKey)
{
	if ((startMidiKey != startMidiKey_) || (endMidiKey != endMidiKey_))
	{
		startMidiKey_ = startMidiKey;
		endMidiKey_ = endMidiKey;
		update();
	}
}

inline uint8_t HPianoRoll::getStart () const
{
	return startMidiKey_;
}

inline uint8_t HPianoRoll::getEnd () const
{
	return endMidiKey_;
}

inline void HPianoRoll::activate (bool active)
{
	std::map<uint8_t, uint8_t> keys = getValue();
	for (uint8_t i = startMidiKey_; i <= endMidiKey_; ++i)
	{
		std::map<uint8_t, uint8_t>::iterator it = keys.find (i);
		
		// Add new active keys
		if (active && (it == keys.end())) keys[i] = 0;

		// Remove existing inactive keys
		else if ((!active) && (it != keys.end())) keys.erase (it);
	}

	setValue (keys);
}

inline void HPianoRoll::activate (const uint8_t key, bool active)
{
	if (key > endMidiKey_) return;

	std::map<uint8_t, uint8_t> keys = getValue();
	std::map<uint8_t, uint8_t>::iterator it = keys.find (key);
		
	// Add new active keys
	if (active && (it == keys.end())) 
	{
		keys[key] = 0;
		setValue (keys);
	}

	// Remove existing inactive keys
	else if ((!active) && (it != keys.end())) 
	{
		keys.erase (it);
		setValue (keys);
	}
}

inline void HPianoRoll::activate (const uint8_t from, const uint8_t to, bool active)
{
	std::map<uint8_t, uint8_t> keys = getValue();

	for (uint8_t i = from; i <= to; ++i)
	{
		std::map<uint8_t, uint8_t>::iterator it = keys.find (i);
			
		// Add new active keys
		if (active && (it == keys.end())) keys[i] = 0;

		// Remove existing inactive keys
		else if ((!active) && (it != keys.end())) keys.erase (it);
	}

	setValue (keys);
}

inline void HPianoRoll::activate (const std::vector<uint8_t>& keys)
{
	std::map<uint8_t, uint8_t> k1 = getValue();
	std::vector<uint8_t> k2 = keys;

	// Remove entries from keys_ missing in keys
	for (std::map<uint8_t, uint8_t>::iterator it1 = k1.begin(); it1 != k1.end(); /* empty */)
	{
		std::vector<uint8_t>::const_iterator it2 = std::find (k2.begin(), k2.end(), it1->first);
		if (it2 == k2.cend()) 
		{
			it1 = k1.erase (it1);
			k2.erase (it2);
		}
		else ++it1;
	}

	// Add new entries
	for (const uint8_t k : k2) 
	{
		if (k <= 127) k1[k] = 0;
	}

	setValue (k1);
}

inline bool HPianoRoll::isActive (const uint8_t key) const
{
	return (value_.find(key) != value_.end());
}

inline std::vector<uint8_t> HPianoRoll::getActive () const
{
	std::vector<uint8_t> k2 {};
	for (std::map<uint8_t, uint8_t>::const_reference k : value_) k2.push_back(k.first);
	return k2;
}

inline void HPianoRoll::setKey (const uint8_t key, uint8_t velocity)
{
	std::map<uint8_t, uint8_t> keys = getValue();
	std::map<uint8_t, uint8_t>::iterator it = keys.find(key);
	if ((it != keys.end()) && (it->second != velocity))
	{
		it->second = velocity;
		setValue(keys);
	}
}

inline uint8_t HPianoRoll::getKey (const uint8_t key) const
{
	std::map<uint8_t, uint8_t>::const_iterator it = value_.find(key);
	return (it != value_.end() ? it->second : 0);
}

inline void HPianoRoll::setKeys (const std::vector<uint8_t>& keys, uint8_t velocity)
{
	std::map<uint8_t, uint8_t> k2 = getValue();

	for (const uint8_t k : keys) 
	{
		std::map<uint8_t, uint8_t>::iterator it = k2.find(k);
		if (it != k2.end()) it->second = velocity;
	}

	setValue (k2);
}

inline void HPianoRoll::setKeys (const std::map<uint8_t, uint8_t>& keys)
{
	std::map<uint8_t, uint8_t> k2 = getValue();

	for (std::map<uint8_t, uint8_t>::const_reference k : keys) 
	{
		std::map<uint8_t, uint8_t>::iterator it = k2.find (k.first);
		if (it != k2.end()) it->second = k.second;
	}

	setValue (k2);
}

inline std::map<uint8_t, uint8_t> HPianoRoll::getKeys () const
{
	return value_;
}

inline void HPianoRoll::setVelocity (const uint8_t velocity)
{
	defaultVelocity_ = velocity;
}

inline uint8_t HPianoRoll::getVelocity () const
{
	return defaultVelocity_;
}

inline void HPianoRoll::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (pev)
	{
		const uint8_t keyNr = getKey (pev->getPosition());
		if (isActive (keyNr))
		{
			if (isToggleable()) setKey (keyNr, getKey (keyNr) ? 0 : defaultVelocity_);
			else setKey (keyNr, defaultVelocity_);
		}
	}

	Clickable::onButtonPressed (event);
}

inline void HPianoRoll::onButtonReleased (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (pev)
	{
		const uint8_t keyNr = getKey (pev->getPosition());
		if (isActive (keyNr) && (!isToggleable()))  setKey (keyNr, 0);
	}

	Clickable::onButtonReleased (event);
}

inline void HPianoRoll::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (pev)
	{
		const uint8_t keyNr = getKey (pev->getPosition());
		const uint8_t lastKeyNr = getKey (pev->getPosition() - pev->getDelta());

		// Check if new key entered
		if (keyNr != lastKeyNr)
		{
			// Release last key
			if (isActive (lastKeyNr) && (!isToggleable())) setKey (lastKeyNr, 0);

			// Press new key
			if (isToggleable()) setKey (keyNr, getKey (keyNr) ? 0 : defaultVelocity_);
			else setKey (keyNr, defaultVelocity_);
		}
	}

	Draggable::onPointerDragged (event);
}

inline uint8_t HPianoRoll::getKey (const BUtilities::Point<>& position)
{
	double x0 = getXOffset();
	double y0 = getYOffset();
	double w = getEffectiveWidth();
	double h = getEffectiveHeight();

	if ((w >= 2) && (h >= 2) && (endMidiKey_ >= startMidiKey_))
	{
		uint8_t startKeyNrOffset = startMidiKey_ % 12;
		uint8_t endKeyNrOffset = endMidiKey_ % 12;
		double startKeyX = keyCoords[startKeyNrOffset].x + (int (startMidiKey_ / 12)) * 7;
		double endKeyX = keyCoords[endKeyNrOffset].x + keyCoords[endKeyNrOffset].width + (int(endMidiKey_ / 12)) * 7;
		double xs = w / (endKeyX - startKeyX);

		double keyX = position.x / xs - x0;
		int keyXOctave = keyX / 7;
		double keyXOffset = keyX - keyXOctave * 7;

		// The blacks first
		for (int i = 0; i < 12; ++i)
		{
			if (!keyCoords[i].whiteKey)
			{
				if
				(
					(position.y >= y0) &&
					(position.y <= y0 + 0.6667 * h) &&
					(keyXOffset >= keyCoords[i].x) &&
					(keyXOffset <= keyCoords[i].x + keyCoords[i].width)
				)
				{
					return keyXOctave * 12 + i + startMidiKey_;
				}
			}
		}

		// Then the whites
		for (int i = 0; i < 12; ++i)
		{
			if (keyCoords[i].whiteKey)
			{
				if
				(
					(position.y >= y0) &&
					(position.y <= y0 + h) &&
					(keyXOffset >= keyCoords[i].x)
					&& (keyXOffset <= keyCoords[i].x + keyCoords[i].width)
				)
				{
					return keyXOctave * 12 + i + startMidiKey_;
				}
			}
		}
	}

	return 255;
}

inline void HPianoRoll::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void HPianoRoll::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void HPianoRoll::draw (const BUtilities::Area<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	double x0 = getXOffset();
	double y0 = getYOffset();
	double w = getEffectiveWidth();
	double h = getEffectiveHeight();

	if ((w >= 2) && (h >= 2) && (endMidiKey_ >= startMidiKey_))
	{
		// Draw widget class elements first
		Widget::draw (area);

		cairo_t* cr = cairo_create (surface_);
		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			cairo_set_line_width (cr, 0.0);

			uint8_t startKeyNrOffset = startMidiKey_ % 12;
			uint8_t endKeyNrOffset = endMidiKey_ % 12;
			double startKeyX = keyCoords[startKeyNrOffset].x + (int (startMidiKey_ / 12)) * 7;
			double endKeyX = keyCoords[endKeyNrOffset].x + keyCoords[endKeyNrOffset].width + (int (endMidiKey_ / 12)) * 7;
			double xs = w / (endKeyX - startKeyX);

			for (uint8_t i = 0; i <= endMidiKey_ - startMidiKey_; ++i)
			{
				const uint8_t keyNrOffset = (i + startMidiKey_) % 12;
				const double keyX = keyCoords[keyNrOffset].x + (int ((startMidiKey_ + i) / 12)) * 7 - startKeyX;

				if (keyCoords[keyNrOffset].whiteKey)
				{
					const BStyles::Color color =
					(
						isActive(i) ?
						(
							getKey(i) != 0 ?
							getFgColors()[getStatus()].illuminate (0.333) :
							getBgColors()[getStatus()].illuminate (0.75)
						) :
						getBgColors()[getStatus()].illuminate (0)
					);

					cairo_set_source_rgba (cr, CAIRO_RGBA (color));
					cairo_move_to (cr, x0 + (keyX + keyCoords[keyNrOffset].dx1  + 0.025) * xs, y0);
					cairo_line_to (cr, x0 + (keyX + keyCoords[keyNrOffset].dx1  + 0.025) * xs, y0 + 0.667 * h);
					cairo_line_to (cr, x0 + (keyX + 0.025) * xs, y0 + 0.667 * h);
					cairo_line_to (cr, x0 + (keyX + 0.025) * xs, y0 + h - 0.05 * xs);
					cairo_arc_negative (cr, x0 + (keyX + 0.125) * xs, y0 + h - 0.1 * xs, 0.1 * xs, M_PI, M_PI / 2);
					cairo_line_to (cr, x0 + (keyX + keyCoords[keyNrOffset].width - 0.125) * xs, y0 + h);
					cairo_arc_negative (cr, x0 + (keyX + keyCoords[keyNrOffset].width - 0.125) * xs, y0 + h - 0.1 * xs, 0.1 * xs, M_PI / 2, 0);
					cairo_line_to (cr, x0 + (keyX + keyCoords[keyNrOffset].width - 0.025) * xs, y0 + 0.667 * h);
					cairo_line_to (cr, x0 + (keyX + keyCoords[keyNrOffset].width - keyCoords[keyNrOffset].dx2 - 0.025) * xs, y0 + 0.667 * h);
					cairo_line_to (cr, x0 + (keyX + keyCoords[keyNrOffset].width - keyCoords[keyNrOffset].dx2 - 0.025) * xs, y0);
					cairo_close_path (cr);
					cairo_fill (cr);
				}
				else
				{
					const BStyles::Color color =
					(
						isActive(i) ?
						(
							getKey(i) != 0 ?
							getFgColors()[getStatus()].illuminate (-0.5) :
							getBgColors()[getStatus()].illuminate (-0.75)
						) :
						getBgColors()[getStatus()].illuminate (-0.5)
					);

					cairo_set_source_rgba (cr, CAIRO_RGBA (color));
					cairoplus_rectangle_rounded (cr, x0 + keyX * xs, y0, keyCoords[keyNrOffset].width * xs, 0.6667 * h, 0.1 * xs, 0b1100);
					cairo_fill (cr);
				}

			}
			cairo_destroy (cr);
		}
	}
}


}

#endif /* BWIDGETS_HPIANOROLL_HPP_ */
