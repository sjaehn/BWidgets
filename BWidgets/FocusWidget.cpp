/* FocusWidget.cpp
 * Copyright (C) 2018, 2019  Sven Jähnichen
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

#include "FocusWidget.hpp"

namespace BWidgets
{
FocusWidget::FocusWidget () : FocusWidget ("focus") {}

FocusWidget::FocusWidget (const std::string& name) :
		Widget (0, 0, 100, 20, name), focusInMs (BWIDGETS_DEFAULT_FOCUS_IN_TIME), focusOutMs (BWIDGETS_DEFAULT_FOCUS_OUT_TIME),
		focusEntered (false) {}

// TODO override/ shadow add method to resize container

void FocusWidget::setFocusInMilliseconds (const std::chrono::milliseconds ms) {focusInMs = ms;}

std::chrono::milliseconds FocusWidget::getFocusInMilliseconds () const {return focusInMs;}

void FocusWidget::setFocusOutMilliseconds (const std::chrono::milliseconds ms) {focusOutMs = ms;}

std::chrono::milliseconds FocusWidget::getFocusOutMilliseconds () const {return focusOutMs;}

void FocusWidget::setFocused (const bool status) {focusEntered = status;}

bool FocusWidget::isFocused () const {return focusEntered;}

}
