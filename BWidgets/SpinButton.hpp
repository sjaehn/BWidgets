/* SpinButton.hpp
 * Copyright (C) 2018 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_SPINBUTTON_HPP_
#define BWIDGETS_SPINBUTTON_HPP_

#include "Symbol.hpp"
#include "SymbolButton.hpp"
#include "Supports/ValueableTyped.hpp"
#include "../BEvents/Event.hpp"

#ifndef BWIDGETS_DEFAULT_SPINBUTTON_WIDTH
#define BWIDGETS_DEFAULT_SPINBUTTON_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_SPINBUTTON_HEIGHT
#define BWIDGETS_DEFAULT_SPINBUTTON_HEIGHT 20.0
#endif

namespace BWidgets
{

/**
 *  @brief  Widget containing an up and a down button. 
 *
 *  %SpinButton is a Valueable composite widget. It contains an up and a down
 *  button. Its value can either be 0 (no button pressed) or -1 (up button
 *  pressed) or 1 (down button pressed). The visualble content of
 *  the %SpinButton is represented by its background and its border.
 */
class SpinButton : public Widget, public ValueableTyped<int>
{
public:
	SymbolButton upButton_;
	SymbolButton downButton_;

	/**
	 *  @brief  Constructs a new SpinButton object with default parameters.
	 */
	SpinButton ();

	/**
	 *  @brief  Constructs a new SpinButton object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	SpinButton (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %SpinButton with default size.
	 *  @param value  Default value (-1 or 0 or 1).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SpinButton	(const int value, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %SpinButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param value  Default value (-1 or 0 or 1).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SpinButton	(const double x, const double y, const double width, const double height, 
				 int value = 0,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %SpinButton. 
	 *  @return  Pointer to the new %SpinButton.
	 *
	 *  Creates a clone of this %SpinButton by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %SpinButton. 
	 *  @param that  Other %SpinButton.
	 *
	 *  Copies all properties from another %SpinButton. But NOT its linkage.
	 */
	void copy (const SpinButton* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:

	/**
	 *  @brief  Callback function which handles and forwards 
	 *  VALUE_CHANGED_EVENTs from the buttons.
	 *  @param event  Event of the type ValueChangedEvent .
	 */
	static void valueChangedCallback (BEvents::Event* event);
};

inline SpinButton::SpinButton () : SpinButton (0.0, 0.0, BWIDGETS_DEFAULT_SPINBUTTON_WIDTH, BWIDGETS_DEFAULT_SPINBUTTON_HEIGHT, 0, URID_UNKNOWN_URID, "") {}

inline SpinButton::SpinButton	(const uint32_t urid, const std::string& title) :
	SpinButton (0.0, 0.0, BWIDGETS_DEFAULT_SPINBUTTON_WIDTH, BWIDGETS_DEFAULT_SPINBUTTON_HEIGHT, 0, urid, title) {}

inline SpinButton::SpinButton	(const int value, uint32_t urid, std::string title) :
	SpinButton (0.0, 0.0, BWIDGETS_DEFAULT_SPINBUTTON_WIDTH, BWIDGETS_DEFAULT_SPINBUTTON_HEIGHT, value, urid, title) {}

inline SpinButton::SpinButton	(const double x, const double y, const double width, const double height, 
			 	 				 const int value, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<int> (value < 0 ? -1 : (value > 0 ? 1 : 0)),
	upButton_ (x, y, width, 0.5 * height, Symbol::UP_SYMBOL, false, value < 0, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button")),
	downButton_ (x, y + 0.5 * height, width, 0.5 * height, Symbol::DOWN_SYMBOL, false, value > 0, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"))
{
	upButton_.setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, valueChangedCallback);
	downButton_.setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, valueChangedCallback);
	add (&upButton_);
	add (&downButton_);
	setBorder (BStyles::Border (BStyles::Line (getBgColors()[BStyles::Status::STATUS_NORMAL], 1.0), 0.0, 0.0, 0.0));
}

inline Widget* SpinButton::clone () const 
{
	Widget* f = new SpinButton (urid_, title_);
	f->copy (this);
	return f;
}

inline void SpinButton::copy (const SpinButton* that)
{
	upButton_.copy (&that->upButton_);
	downButton_.copy (&that->downButton_);
	ValueableTyped<int>::operator= (*that);
    Widget::copy (that);
}

inline void SpinButton::update ()
{
	upButton_.setValue (getValue() < 0);
	downButton_.setValue (getValue() > 0);
	upButton_.moveTo (getXOffset(), getYOffset());
	upButton_.resize (getEffectiveWidth(), 0.5 * getEffectiveHeight());
	downButton_.moveTo (getXOffset(), getYOffset() + 0.5 * getEffectiveHeight());
	downButton_.resize (getEffectiveWidth(), 0.5 * getEffectiveHeight());
	Widget::update();
}

inline void SpinButton::valueChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<bool>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<bool>*>(event);
	if (!vev) return;
	SymbolButton* w = dynamic_cast<SymbolButton*>(vev->getWidget());
	if (!w) return;
	SpinButton* p = dynamic_cast<SpinButton*>(w->getParentWidget());
	if (!p) return;

	if (w == &p->upButton_) p->setValue (w->getValue() * -1);
	else if (w == &p->downButton_) p->setValue (w->getValue() * 1);
}

}

#endif /* BWIDGETS_SPINBUTTON_HPP_ */
