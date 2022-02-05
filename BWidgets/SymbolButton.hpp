/* SymbolButton.hpp
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

#ifndef BWIDGETS_SYMBOLBUTTON_HPP_
#define BWIDGETS_SYMBOLBUTTON_HPP_

#include "Button.hpp"
#include "Symbol.hpp"

#ifndef BWIDGETS_DEFAULT_SYMBOLBUTTON_WIDTH
#define BWIDGETS_DEFAULT_SYMBOLBUTTON_WIDTH BWIDGETS_DEFAULT_BUTTON_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_SYMBOLBUTTON_HEIGHT
#define BWIDGETS_DEFAULT_SYMBOLBUTTON_HEIGHT BWIDGETS_DEFAULT_BUTTON_HEIGHT
#endif

namespace BWidgets
{
/**
 *  @brief Composite Button Widget containing a Symbol.
 *
 *  %SymbolButton is a Button containing a Symbol. A %SymbolButton changes its 
 *  Symbol status (and thus its color) in addition to the change of its Border
 *  Color upon changing the condition.
 */
class SymbolButton : public Button
{
public:

	Symbol symbol;

	/**
	 * @brief  Constructs a new %SymbolButton object with default parameters.
	 */
	SymbolButton ();

	/**
	 *  @brief  Creates a %SymbolButton with default size.
	 *  @param symbolIdx  SymbolType index.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SymbolButton	(const Symbol::SymbolType symbolIdx, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %SymbolButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param symbolIdx  SymbolType index.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SymbolButton	(const double x, const double y, const double width, const double height, 
					 const Symbol::SymbolType symbolIdx, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %SymbolButton. 
	 *  @return  Pointer to the new %SymbolButton.
	 *
	 *  Creates a clone of this %SymbolButton by copying all properties. But NOT
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %SymbolButton. 
	 *  @param that  Other %SymbolButton.
	 *
	 *  Copies all properties from another %SymbolButton. But NOT its linkage.
	 */
	void copy (const SymbolButton* that);

	/**
     *  @brief  Optimizes the object surface extends.
     *
     *  Creates a new RGBA surface with the new optimized extends, copies the
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the object surface extends.
	 *  @param width  New object width.
	 *  @param height  New object height.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the object surface extends.
	 *  @param extends  New object extends.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const BUtilities::Point extends) override;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;
};

inline SymbolButton::SymbolButton () : 
	SymbolButton (0.0, 0.0, BWIDGETS_DEFAULT_SYMBOLBUTTON_WIDTH, BWIDGETS_DEFAULT_SYMBOLBUTTON_HEIGHT, Symbol::NO_SYMBOL, false, false, URID_UNKNOWN_URID, "") {}

inline SymbolButton::SymbolButton	(const Symbol::SymbolType symbolIdx, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	SymbolButton (0.0, 0.0, BWIDGETS_DEFAULT_SYMBOLBUTTON_WIDTH, BWIDGETS_DEFAULT_SYMBOLBUTTON_HEIGHT, symbolIdx, toggleable, clicked, urid, title) {}

inline SymbolButton::SymbolButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 const Symbol::SymbolType symbolIdx, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	symbol (0, 0, width, height, symbolIdx, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/symbol"))
{
	symbol.setEventPassable(BEvents::Event::BUTTON_PRESS_EVENT, true);
	symbol.setEventPassable(BEvents::Event::BUTTON_CLICK_EVENT, true);
	add (&symbol);
	symbol.resize (BUtilities::Point (0.75 * extends_.x, 0.75 * extends_.y));
	symbol.moveTo (symbol.center(), symbol.middle());
}

inline Widget* SymbolButton::clone () const 
{
	Widget* f = new SymbolButton ();
	f->copy (this);
	return f;
}

inline void SymbolButton::copy (const SymbolButton* that)
{
	symbol.copy (&that->symbol);
    Button::copy (that);
}

inline void SymbolButton::resize ()
{
	symbol.resize ();
	symbol.moveTo (getXOffset(), getYOffset());
	Button::resize (2.0 * getXOffset() + symbol.getWidth(), 2.0 * getYOffset() + symbol.getHeight());
}

inline void SymbolButton::resize (const double width, const double height) 
{
	SymbolButton::resize (BUtilities::Point (width, height));
}

inline void SymbolButton::resize (const BUtilities::Point extends)
{
	Button::resize (BUtilities::Point (extends.x, extends.y));
	symbol.resize (BUtilities::Point (0.66 * extends.x, 0.66 * extends.y));
	symbol.moveTo (symbol.center(), symbol.middle());
}

inline void SymbolButton::update ()
{
	symbol.setStatus (getValue() ? BStyles::Status::STATUS_ACTIVE : BStyles::Status::STATUS_NORMAL);
	symbol.resize (0.66 * getEffectiveWidth(), 0.66 * getEffectiveHeight());
	symbol.moveTo (symbol.center(), symbol.middle());
	Button::update ();
}

}

#endif /* BWIDGETS_SYMBOLBUTTON_HPP_ */
