/* SymbolPad.hpp
 * Copyright (C) 2018 - 2023  Sven Jähnichen
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
 *  @tparam T  Value type.
 *
 *  %SymbolPad is a Pad containing a Symbol. Its value is represented
 *  by its color from dark to bright. It supports user interaction via
 *  Clickable (switch on / off) and Scrollable (increase / decrease 
 *  value). The visualble content of the %SymbolPad is represented by 
 *  FgColors.
 *
 *  The value type @a T can be used to specialize %Pad (e. g., by writing
 *  specialized @c draw() methods). @a T MUST support the standard comparison
 *  operators and MUST also support the standard arithmetic operators. It
 *  also MUST be compatible with ValueableTyped, ValidatableRange, and
 *  ValueTransferable.
 */
template <class T = double>
class SymbolPad : public Pad<T>
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
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SymbolPad	(const Symbol::SymbolType symbolIdx, const T value, const T min, const T max, T step = 0.0, 
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

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
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SymbolPad	(const double x, const double y, const double width, const double height, 
				 const Symbol::SymbolType symbolIdx, const T value, const T min, const T max, T step = 0.0,
				 std::function<T (const T& x)> transferFunc = ValueTransferable<T>::noTransfer,
				 std::function<T (const T& x)> reTransferFunc = ValueTransferable<T>::noTransfer,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

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
     *  @brief  Optimizes the widget extends.
     *
	 *  Firstly optimizes its symbol size. Then resizes the widget to include
	 *  all direct children (including the symbol) into the widget area.
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
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;
};

template <class T>
inline SymbolPad<T>::SymbolPad () : 
	SymbolPad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
				 Symbol::SymbolType::none, T(), T(), T() + 1.0, T(), 
				 ValueTransferable<T>::noTransfer, ValueTransferable<T>::noTransfer,  
				 BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

template <class T>
inline SymbolPad<T>::SymbolPad	(const uint32_t urid, const std::string& title) :
	SymbolPad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
				 Symbol::SymbolType::none, T(), T(), T() + 1.0, T(), 
				 ValueTransferable<T>::noTransfer, ValueTransferable<T>::noTransfer,  
				 urid, title) 
{

}

template <class T>
inline SymbolPad<T>::SymbolPad	(const Symbol::SymbolType symbolIdx, const T value, const T min, const T max, T step, 
								 uint32_t urid, std::string title) :
	SymbolPad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
				 symbolIdx, value, min, max, step, 
				 ValueTransferable<T>::noTransfer, ValueTransferable<T>::noTransfer,  
				 urid, title) 
{

}

template <class T>
inline SymbolPad<T>::SymbolPad	(const double x, const double y, const double width, const double height, 
						 	 const Symbol::SymbolType symbolIdx, const T value, const T min, const T max, T step, 
							 std::function<T (const T& x)> transferFunc,
			 				 std::function<T (const T& x)> reTransferFunc,
							 uint32_t urid, std::string title) :
	Pad<T> (x, y, width, height,value, min, max, step, transferFunc, reTransferFunc, urid, title),
	symbol (0, 0, width, height, symbolIdx, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/symbol"))
{
	symbol.setFocusable(false);
	symbol.setEventPassable	(BEvents::Event::EventType::buttonPressEvent | 
							 BEvents::Event::EventType::buttonClickEvent | 
							 BEvents::Event::EventType::pointerDragEvent |
							 BEvents::Event::EventType::wheelScrollEvent | 
							 BEvents::Event::EventType::pointerFocusEvents);
	symbol.setTxColors (symbol.getBgColors());
	symbol.setStatus (BStyles::Status::inactive);
	this->add (&symbol);
	symbol.resize (BUtilities::Point<> (0.5 * this->extends_.x, 0.5 * this->extends_.y));
	symbol.moveTo (symbol.center(), symbol.middle());
}

template <class T>
inline Widget* SymbolPad<T>::clone () const 
{
	Widget* f = new SymbolPad (this->urid_, this->title_);
	f->copy (this);
	return f;
}

template <class T>
inline void SymbolPad<T>::copy (const SymbolPad* that)
{
	symbol.copy (&that->symbol);
    Pad<T>::copy (that);
}

template <class T>
inline void SymbolPad<T>::resize ()
{
	symbol.resize ();
	symbol.moveTo (this->getXOffset() + 0.5 * symbol.getHeight(), this->getYOffset() + 0.5 * symbol.getHeight());
	Pad<T>::resize ();
}

template <class T>
inline void SymbolPad<T>::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

template <class T>
inline void SymbolPad<T>::resize (const BUtilities::Point<> extends)
{
	Pad<T>::resize (extends);
}

template <class T>
inline void SymbolPad<T>::update ()
{
	symbol.resize (0.667 * this->getEffectiveWidth(), 0.667 * this->getEffectiveHeight());
	symbol.moveTo (symbol.center(), symbol.middle());
	Pad<T>::update ();
}

}

#endif /* BWIDGETS_SYMBOLPAD_HPP_ */
