/* HPianoRoll.hpp
 * Copyright (C) 2019  Sven Jähnichen
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
#include <cmath>

namespace BWidgets
{

#ifndef BWIDGETS_KEYCOORDS_
#define BWIDGETS_KEYCOORDS_
typedef struct {
	bool whiteKey;
	double x;
	double dx1;
	double dx2;
	double width;
} KeyCoords;

const std::array<KeyCoords, 12> keyCoords=
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
#endif /* BWIDGETS_KEYCOORDS_ */

/*
 * Piano roll widget
 */
class HPianoRoll : public Widget
{
public:
	HPianoRoll ();
	HPianoRoll (const double x, const double y, const double width, const double height, const std::string& name);
	HPianoRoll (const double x, const double y, const double width, const double height, const std::string& name,
			const int startMidiKey, const int endMidiKey);

	/*
	 * Sets the press status of the respective keys.
	 * @param keys	Vector of bool with a size that represents the number of
	 * 				keys. The first vector element represents the first key.
	 * 				True = pressed and false = released.
	 */
	void pressKeys (std::vector<bool>& keys);

	/*
	 * Gets the press status of the respective keys.
	 * @param return	Vector of bool with a size that represents the number
	 * 					of keys. The first vector element represents the first
	 * 					key. True = pressed and false = released.
	 */
	std::vector<bool> getPressedKeys () const;

	/*
	 * Sets the activity status of the respective keys. Active keys are
	 * highlighted and respond to pointer events.
	 * @param keys	Vector of bool with a size that represents the number of
	 * 				keys. The first vector element represents the first key.
	 * 				True = active and false = inactive.
	 */
	void activateKeys (std::vector<bool>& keys);

	/*
	 * Gets the activity status of the respective keys. Active keys are
	 * highlighted and respond to pointer events.
	 * @param return	Vector of bool with a size that represents the number
	 * 					of keys. The first vector element represents the first
	 * 					key. True = active and false = inactive.
	 */
	std::vector<bool> getActiveKeys () const;

	/*
	 * Defines how the keys respond upon pointer events.
	 * @param toggle	True, if the key is toggled if button pressed. False,
	 * 					if the key is pressed if button pressed and released,
	 * 					if button released.
	 */
	void setKeysToggleable (const bool toggle);

	/*
	 * Gets how the keys respond upon pointer events.
	 * @param return	True, if the key is toggled if button pressed. False,
	 * 					if the key is pressed if button pressed and released,
	 * 					if button released.
	 */
	bool isKeysToggleable () const;

// TODO key colors
//	virtual void applyTheme (BStyles::Theme& theme, const std::string& name);

	/**
	 * Handles the BEvents::BUTTON_PRESS_EVENT to press the keys.
	 * @param event Pointer to a pointer event emitted by the same widget.
	 */
	virtual void onButtonPressed (BEvents::PointerEvent* event) override;

	/**
	 * Handles the BEvents::BUTTON_RELEASE_EVENT to release the keys. Takes
	 * only effect if keys are NOT toggleable.
	 * @param event Pointer to a pointer event emitted by the same widget.
	 */
	virtual void onButtonReleased (BEvents::PointerEvent* event) override;

	/**
	 * Handles the BEvents::POINTER_DRAGGED_EVENT to press or release the keys.
	 * @param event Pointer to a pointer event emitted by the same widget.
	 */
	virtual void onPointerDragged (BEvents::PointerEvent* event) override;

protected:
	int getKey (const double x, const double y);
	virtual void draw (const double x, const double y, const double width, const double height) override;

	int startMidiKey;
	int endMidiKey;

	bool toggleKeys;
	int actKeyNr;

	std::vector<bool> activeKeys;
	std::vector<bool> pressedKeys;

	BColors::ColorSet blackBgColors;
	BColors::ColorSet whiteBgColors;
};
}

#endif /* BWIDGETS_HPIANOROLL_HPP_ */
