/* SymbolPad.hpp
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

#ifndef BWIDGETS_SYMBOLPAD_HPP_
#define BWIDGETS_SYMBOLPAD_HPP_

#include "Pad.hpp"
#include "Symbol.hpp"

#ifndef BWIDGETS_DEFAULT_SYMBOLPAD_WIDTH
#define BWIDGETS_DEFAULT_SYMBOLPAD_WIDTH BWIDGETS_DEFAULT_PAD_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_SYMBOLPAD_HEIGHT
#define BWIDGETS_DEFAULT_SYMBOLPAD_HEIGHT BWIDGETS_DEFAULT_PAD_HEIGHT
#endif

namespace BWidgets
{
/**
 *  @brief Composite Pad Widget containing a Symbol.
 *
 *  %SymbolPad is a Pad containing a Symbol. Its value is represented
 *  by its color from dark to bright. It supports user interaction via
 *  Clickable (switch on / off) and Scrollable (increase / decrease 
 *  value). The visualble content of the %SymbolPad is represented by 
 *  FgColors.
 */
class SymbolPad : public Pad
{
public:

	Symbol symbol;

	/**
	 *  @brief  Constructs a new %SymbolPad object with default parameters.
	 */
	SymbolPad ();

	/**
	 *  @brief  Constructs a new %SymbolPad object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	SymbolPad (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %SymbolPad with default size.
	 *  @param symbolIdx  SymbolType index.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SymbolPad	(const Symbol::SymbolType symbolIdx, const double value, const double min, const double max, double step = 0.0, 
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %SymbolPad.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param symbolIdx  SymbolType index.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SymbolPad	(const double x, const double y, const double width, const double height, 
				 const Symbol::SymbolType symbolIdx, const double value, const double min, const double max, double step = 0.0,
				 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
				 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %SymbolPad. 
	 *  @return  Pointer to the new %SymbolPad.
	 *
	 *  Creates a clone of this %SymbolPad by copying all properties. But NOT
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %SymbolPad. 
	 *  @param that  Other %SymbolPad.
	 *
	 *  Copies all properties from another %SymbolPad. But NOT its linkage.
	 */
	void copy (const SymbolPad* that);

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

inline SymbolPad::SymbolPad () : 
	SymbolPad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
				 Symbol::NO_SYMBOL, 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer,  
				 URID_UNKNOWN_URID, "") 
{

}

inline SymbolPad::SymbolPad	(const uint32_t urid, const std::string& title) :
	SymbolPad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
				 Symbol::NO_SYMBOL, 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer,  
				 urid, title) 
{

}

inline SymbolPad::SymbolPad	(const Symbol::SymbolType symbolIdx, double value, const double min, const double max, double step, 
							 uint32_t urid, std::string title) :
	SymbolPad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
				 symbolIdx, value, min, max, step, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer,  
				 urid, title) 
{

}

inline SymbolPad::SymbolPad	(const double x, const double y, const double width, const double height, 
						 	 const Symbol::SymbolType symbolIdx, double value, const double min, const double max, double step, 
							 std::function<double (const double& x)> transferFunc,
			 				 std::function<double (const double& x)> reTransferFunc,
							 uint32_t urid, std::string title) :
	Pad (x, y, width, height,value, min, max, step, transferFunc, reTransferFunc, urid, title),
	symbol (0, 0, width, height, symbolIdx, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/symbol"))
{
	symbol.setEventPassable(BEvents::Event::BUTTON_PRESS_EVENT, true);
	symbol.setEventPassable(BEvents::Event::BUTTON_CLICK_EVENT, true);
	symbol.setEventPassable(BEvents::Event::POINTER_DRAG_EVENT, true);
	symbol.setEventPassable(BEvents::Event::WHEEL_SCROLL_EVENT, true);
	symbol.setTxColors (symbol.getBgColors());
	symbol.setStatus (BStyles::STATUS_INACTIVE);
	add (&symbol);
	symbol.resize (BUtilities::Point (0.4 * extends_.x, 0.4 * extends_.y));
	symbol.moveTo (symbol.center(), symbol.middle());
}

inline Widget* SymbolPad::clone () const 
{
	Widget* f = new SymbolPad ();
	f->copy (this);
	return f;
}

inline void SymbolPad::copy (const SymbolPad* that)
{
	symbol.copy (&that->symbol);
    Pad::copy (that);
}

inline void SymbolPad::resize ()
{
	symbol.resize ();
	Pad::resize (2.5 * symbol.getWidth(), 2.5 * symbol.getHeight());
	symbol.moveTo (symbol.center(), symbol.middle());
}

inline void SymbolPad::resize (const double width, const double height) 
{
	SymbolPad::resize (BUtilities::Point (width, height));
}

inline void SymbolPad::resize (const BUtilities::Point extends)
{
	Pad::resize (BUtilities::Point (extends.x, extends.y));
	symbol.resize (BUtilities::Point (0.4 * extends.x, 0.4 * extends.y));
	symbol.moveTo (symbol.center(), symbol.middle());
}

inline void SymbolPad::update ()
{
	symbol.resize (0.4 * getEffectiveWidth(), 0.4 * getEffectiveHeight());
	symbol.moveTo (symbol.center(), symbol.middle());
	Pad::update ();
}

}

#endif /* BWIDGETS_SYMBOLPAD_HPP_ */
