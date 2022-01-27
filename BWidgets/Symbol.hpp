/* Symbol.hpp
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

#ifndef BWIDGETS_SYMBOL_HPP_
#define BWIDGETS_SYMBOL_HPP_

#include "Widget.hpp"

#define BWIDGETS_DEFAULT_SYMBOL_SIZE 12

namespace BWidgets
{

/**
 *  @brief  Widget containing a symbol.
 *
 *  %Symbol is a Widget that displays a %symbol. It can be decorated by setting
 *  a TxColor in addtion to the StyleProperty settings supported by Widget. 
 */
class Symbol : public Widget
{
public:

	/**
	 *  @brief  Enumaration of symbols. 
	 * 
	 */
	enum SymbolType
	{
		NO_SYMBOL		= 0,
        ADD_SYMBOL,
        MINUS_SYMBOL,
        LEFT_SYMBOL,
        RIGHT_SYMBOL,
        UP_SYMBOL, 
        DOWN_SYMBOL,
        PLAY_SYMBOL
	};

protected:
	SymbolType symbol_;

public:

	/**
	 * @brief Constructs an empty %Symbol object.
	 */
	Symbol ();

	/**
	 *  @brief  Constructs a %Symbol object at the origin with optimized extends.
	 *  @param symbol  SymbolType index.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Symbol title (default = "").
	 */
	Symbol (SymbolType symbol, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a %Symbol object at the origin with optimized extends.
	 *  @param x  %Symbol X origin coordinate.
	 *  @param y  %Symbol Y origin coordinate.
	 *  @param width  %Symbol width.
	 *  @param height  %Symbol height.
	 *  @param symbol  SymbolType index.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Symbol title (default = "").
	 */
	Symbol	(const double x, const double y, const double width, const double height, 
			 SymbolType symbol, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Symbol. 
	 *  @return  Pointer to the new %Symbol.
	 *
	 *  Creates a clone of this %Symbol by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Symbol. 
	 *  @param that  Other %Symbol.
	 *
	 *  Copies all properties from another %Symbol. But NOT its linkage.
	 */
	void copy (const Symbol* that);

	/**
	 *  @brief  Sets the SymbolType index.
	 *  @param text  SymbolType index.
	 */
	void setSymbol (const SymbolType symbol);

	/**
	 *  @brief  Gets the SymbolType index.
	 *  @return   SymbolType index.
	 */
	SymbolType getSymbol () const;

protected:
	/**
     *  @brief  Unclipped draw to the surface (if is visualizable).
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea& area) override;
};

inline Symbol::Symbol () : 
	Symbol (0.0, 0.0, 0.0, 0.0, NO_SYMBOL, URID_UNKNOWN_URID, "") 
{

}

inline Symbol::Symbol (SymbolType symbol, uint32_t urid, std::string title) :
	Symbol (0.0, 0.0, BWIDGETS_DEFAULT_SYMBOL_SIZE, BWIDGETS_DEFAULT_SYMBOL_SIZE, symbol, urid, title)
{
}

inline Symbol::Symbol (const double x, const double y, const double width, const double height, SymbolType symbol, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	symbol_ (symbol)
{
	
}

inline Widget* Symbol::clone () const 
{
	Widget* f = new Symbol ();
	f->copy (this);
	return f;
}

inline void Symbol::copy (const Symbol* that)
{
	symbol_ = that->symbol_;
    Widget::copy (that);
}

inline void Symbol::setSymbol (const SymbolType symbol)
{
	if (symbol != symbol_)
	{
		symbol_ = symbol;
		update ();
	}
}

inline Symbol::SymbolType Symbol::getSymbol () const 
{
	return symbol_;
}

inline void Symbol::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Symbol::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea (x0, y0, width, height));
}

inline void Symbol::draw (const BUtilities::RectArea& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	cairo_t* cr = cairo_create (surface_);

	if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
	{
		// Limit cairo-drawing area
		cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
		cairo_clip (cr);

		const double x0 = getXOffset ();
		const double y0 = getYOffset ();
		const double w = getEffectiveWidth ();
		const double h = getEffectiveHeight ();
		const double ext = (w < h ? w : h);

		cairo_set_source_rgba (cr, CAIRO_RGBA (getTxColors()[getStatus()]));

		switch (symbol_)
        {
                case ADD_SYMBOL:        cairo_move_to (cr, x0 + w / 2 - ext / 2, y0 + h / 2);
                                        cairo_line_to (cr, x0 + w / 2 + ext / 2, y0 + h / 2);
                                        cairo_move_to (cr, x0 + w / 2, y0 + h / 2 - ext / 2);
                                        cairo_line_to (cr, x0 + w / 2, y0 + h / 2 + ext / 2);
                                        cairo_set_line_width (cr, 2.0);
                                        cairo_stroke (cr);
                                        break;

                case MINUS_SYMBOL:      cairo_move_to (cr, x0 + w / 2 - ext / 2, y0 + h / 2);
                                        cairo_line_to (cr, x0 + w / 2 + ext / 2, y0 + h / 2);
                                        cairo_set_line_width (cr, 2.0);
                                        cairo_stroke (cr);
                                        break;

                case LEFT_SYMBOL:       cairo_move_to (cr, x0 + w / 2 + 0.25 * ext, y0 + h / 2 - ext / 2);
                                        cairo_line_to (cr, x0 + w / 2 - 0.25 * ext, y0 + h / 2);
                                        cairo_line_to (cr, x0 + w / 2 + 0.25 * ext, y0 + h / 2 + ext / 2);
                                        cairo_set_line_width (cr, 2.0);
                                        cairo_stroke (cr);
                                        break;

                case RIGHT_SYMBOL:      cairo_move_to (cr, x0 + w / 2 - 0.25 * ext, y0 + h / 2 - ext / 2);
                                        cairo_line_to (cr, x0 + w / 2 + 0.25 * ext, y0 + h / 2);
                                        cairo_line_to (cr, x0 + w / 2 - 0.25 * ext, y0 + h / 2 + ext / 2);
                                        cairo_set_line_width (cr, 2.0);
                                        cairo_stroke (cr);
                                        break;

                case UP_SYMBOL:         cairo_move_to (cr, x0 + w / 2 - 0.5 * ext, y0 + h / 2 + 0.25 * ext);
                                        cairo_line_to (cr, x0 + w / 2, y0 + h / 2 - 0.25 * ext);
                                        cairo_line_to (cr, x0 + w / 2 + 0.5 * ext, y0 + h / 2 + 0.25 * ext);
                                        cairo_set_line_width (cr, 2.0);
                                        cairo_stroke (cr);
                                        break;

                case DOWN_SYMBOL:       cairo_move_to (cr, x0 + w / 2 - 0.5 * ext, y0 + h / 2 - 0.25 * ext);
                                        cairo_line_to (cr, x0 + w / 2, y0 + h / 2 + 0.25 * ext);
                                        cairo_line_to (cr, x0 + w / 2 + 0.5 * ext, y0 + h / 2 - 0.25 * ext);
                                        cairo_set_line_width (cr, 2.0);
                                        cairo_stroke (cr);
                                        break;

                case PLAY_SYMBOL:       cairo_move_to (cr, x0 + w / 2 - 0.5 * ext, y0 + h / 2 - 0.5 * ext);
                                        cairo_line_to (cr, x0 + w / 2 + 0.5 * ext, y0 + h / 2);
                                        cairo_line_to (cr, x0 + w / 2 - 0.5 * ext, y0 + h / 2 + 0.5 * ext);
                                        cairo_close_path (cr);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
                                        break;

                default:                break;
		}
	}

	cairo_destroy (cr);
}

}

#endif /* BWIDGETS_SYMBOL_HPP_ */
