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
#include <cairo/cairo.h>
#include <cmath>

#ifndef BWIDGETS_DEFAULT_SYMBOL_WIDTH
#define BWIDGETS_DEFAULT_SYMBOL_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_SYMBOL_HEIGHT
#define BWIDGETS_DEFAULT_SYMBOL_HEIGHT BWIDGETS_DEFAULT_SYMBOL_WIDTH
#endif

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
	enum class SymbolType
	{
		none		= 0,
        add,
        minus,
        left,
        right,
        up, 
        down,
        play,
		rewind,
		ffwd,
		pause,
		stop,
		record,
		skip,
		bypass,
		piano,
		question,
		info,
		warn,
		error,
		edit,
		pick,
		cut,
		copy,
		paste,
		del,
		xflip,
		yflip,
		home,
		load,
		save,
		newFolder
	};

protected:
	SymbolType symbol_;

public:

	/**
	 *  @brief  Constructs an empty default %Symbol object.
	 */
	Symbol ();

	/**
	 *  @brief  Constructs an empty default %Symbol object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Symbol (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Constructs a %Symbol object at the origin with optimized extends.
	 *  @param symbol  SymbolType index.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Symbol title (default = "").
	 */
	Symbol (SymbolType symbol, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a %Symbol object at the origin with optimized extends.
	 *  @param x  %Symbol X origin coordinate.
	 *  @param y  %Symbol Y origin coordinate.
	 *  @param width  %Symbol width.
	 *  @param height  %Symbol height.
	 *  @param symbol  SymbolType index.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Symbol title (default = "").
	 */
	Symbol	(const double x, const double y, const double width, const double height, 
			 SymbolType symbol, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

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
	virtual void setSymbol (const SymbolType symbol);

	/**
	 *  @brief  Gets the SymbolType index.
	 *  @return   SymbolType index.
	 */
	SymbolType getSymbol () const;

	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area but at least to the font size defined in its style.
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
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline Symbol::Symbol () : 
	Symbol (0.0, 0.0, BWIDGETS_DEFAULT_SYMBOL_WIDTH, BWIDGETS_DEFAULT_SYMBOL_HEIGHT, SymbolType::none, BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

inline Symbol::Symbol (const uint32_t urid, const std::string& title) :
	Symbol (0.0, 0.0, BWIDGETS_DEFAULT_SYMBOL_WIDTH, BWIDGETS_DEFAULT_SYMBOL_HEIGHT, SymbolType::none, urid, title)
{
}

inline Symbol::Symbol (SymbolType symbol, uint32_t urid, std::string title) :
	Symbol (0.0, 0.0, BWIDGETS_DEFAULT_SYMBOL_WIDTH, BWIDGETS_DEFAULT_SYMBOL_HEIGHT, symbol, urid, title)
{
}

inline Symbol::Symbol (const double x, const double y, const double width, const double height, SymbolType symbol, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	symbol_ (symbol)
{
	
}

inline Widget* Symbol::clone () const 
{
	Widget* f = new Symbol (urid_, title_);
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

inline void Symbol::resize ()
{
	BUtilities::Area<> a = BUtilities::Area<>(0, 0, getFont().size + 2.0 * getXOffset(), getFont().size + 2.0 * getYOffset());
	for (Linkable* c : children_)
	{
		Widget* w = dynamic_cast<Widget*>(c);
		if (w) a.extend (BUtilities::Area<>(w->getPosition(), w->getPosition() + w->getExtends()));
	}

	resize (a.getExtends());
}

inline void Symbol::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void Symbol::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void Symbol::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Symbol::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void Symbol::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	cairo_t* cr = cairo_create (cairoSurface());

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
		const double xc = x0 + 0.5 * w;
		const double yc = y0 + 0.5 * h;

		cairo_set_source_rgba (cr, CAIRO_RGBA (getTxColors()[getStatus()]));

		switch (symbol_)
        {
                case SymbolType::add:        cairo_move_to (cr, xc - ext / 2, yc);
                                        cairo_line_to (cr, xc + ext / 2, yc);
                                        cairo_move_to (cr, xc, yc - ext / 2);
                                        cairo_line_to (cr, xc, yc + ext / 2);
                                        cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
                                        break;

                case SymbolType::minus:      cairo_move_to (cr, xc - ext / 2, yc);
                                        cairo_line_to (cr, xc + ext / 2, yc);
                                        cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
                                        break;

                case SymbolType::left:       cairo_move_to (cr, xc + 0.25 * ext, yc - ext / 2);
                                        cairo_line_to (cr, xc - 0.25 * ext, yc);
                                        cairo_line_to (cr, xc + 0.25 * ext, yc + ext / 2);
                                        cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
                                        break;

                case SymbolType::right:      cairo_move_to (cr, xc - 0.25 * ext, yc - ext / 2);
                                        cairo_line_to (cr, xc + 0.25 * ext, yc);
                                        cairo_line_to (cr, xc - 0.25 * ext, yc + ext / 2);
                                        cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
                                        break;

                case SymbolType::up:         cairo_move_to (cr, xc - 0.5 * ext, yc + 0.25 * ext);
                                        cairo_line_to (cr, xc, yc - 0.25 * ext);
                                        cairo_line_to (cr, xc + 0.5 * ext, yc + 0.25 * ext);
                                        cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
                                        break;

                case SymbolType::down:       cairo_move_to (cr, xc - 0.5 * ext, yc - 0.25 * ext);
                                        cairo_line_to (cr, xc, yc + 0.25 * ext);
                                        cairo_line_to (cr, xc + 0.5 * ext, yc - 0.25 * ext);
                                        cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
                                        break;

                case SymbolType::play:       cairo_move_to (cr, xc - 0.225 * ext, yc - 0.3 * ext);
                                        cairo_line_to (cr, xc + 0.225 * ext, yc);
                                        cairo_line_to (cr, xc - 0.225 * ext, yc + 0.3 * ext);
                                        cairo_close_path (cr);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
                                        break;

                case SymbolType::rewind:     cairo_move_to (cr, xc + 0.45 * ext, yc - 0.3 * ext);
                                        cairo_line_to (cr, xc + 0.05 * ext, yc);
                                        cairo_line_to (cr, xc + 0.45 * ext, yc + 0.3 * ext);
                                        cairo_close_path (cr);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
										cairo_move_to (cr, xc - 0.05 * ext, yc - 0.3 * ext);
                                        cairo_line_to (cr, xc - 0.45 * ext, yc);
                                        cairo_line_to (cr, xc - 0.05 * ext, yc + 0.3 * ext);
                                        cairo_close_path (cr);
                                        cairo_fill (cr);
                                        break;

                case SymbolType::ffwd:   	cairo_move_to (cr, xc - 0.45 * ext, yc - 0.3 * ext);
                                        cairo_line_to (cr, xc - 0.05 * ext, yc);
                                        cairo_line_to (cr, xc - 0.45 * ext, yc + 0.3 * ext);
                                        cairo_close_path (cr);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
										cairo_move_to (cr, xc + 0.05 * ext, yc - 0.3 * ext);
                                        cairo_line_to (cr, xc + 0.45 * ext, yc);
                                        cairo_line_to (cr, xc + 0.05 * ext, yc + 0.3 * ext);
                                        cairo_close_path (cr);
                                        cairo_fill (cr);
                                        break;

                case SymbolType::pause:      cairo_rectangle (cr, xc - 0.3 * ext, yc - 0.3 * ext, 0.2 * ext, 0.6 * ext);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
										cairo_rectangle (cr, xc + 0.1 * ext, yc - 0.3 * ext, 0.2 * ext, 0.6 * ext);
                                        cairo_fill (cr);
                                        break;

                case SymbolType::stop:       cairo_rectangle (cr, xc - 0.3 * ext, yc - 0.3 * ext, 0.6 * ext, 0.6 * ext);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
                                        break;

                case SymbolType::record:     cairo_arc (cr, xc, yc, 0.3 * ext, 0.0, 2.0 * M_PI);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
                                        break;

				case SymbolType::skip:		cairo_move_to (cr, xc - 0.3 * ext, yc - 0.3 * ext);
										cairo_line_to (cr, xc + 0.3 * ext, yc + 0.3 * ext);
										cairo_move_to (cr, xc + 0.3 * ext, yc - 0.3 * ext);
										cairo_line_to (cr, xc - 0.3 * ext, yc + 0.3 * ext);
										cairo_set_line_width (cr, 0.1 * ext);
										cairo_stroke (cr);
										break;

				case SymbolType::bypass:		cairo_arc (cr, xc, yc, 0.45 * ext, 1.1667 * M_PI, 1.8333 * M_PI);
										cairo_set_line_width (cr, 0.1 * ext);
										cairo_stroke (cr);
										cairo_move_to (cr, xc + 0.39 * ext, yc - 0.225 * ext);
										cairo_rel_line_to (cr, 0.0, -0.2 * ext);
										cairo_rel_line_to (cr, -0.2 * ext, 0.2 * ext);
										cairo_close_path (cr);
										cairo_fill (cr);
										cairo_arc (cr, xc, yc, 0.45 * ext, 0.1667 * M_PI, 0.8333 * M_PI);
										cairo_stroke (cr);
										cairo_move_to (cr, xc + 0.39 * ext, yc + 0.225 * ext);
										cairo_rel_line_to (cr, 0.0, 0.2 * ext);
										cairo_rel_line_to (cr, -0.2 * ext, -0.2 * ext);
										cairo_close_path (cr);
										cairo_fill (cr);
										break;

                case SymbolType::piano:      cairo_set_line_width (cr, 0.05 * ext);
                                        for (int i = 0; i < 3; ++i)
                                        {
                                                cairo_rectangle (cr, xc - 0.375 * ext + i * 0.25 * ext, yc - 0.45 * ext, 0.25 * ext, 0.9 * ext);
                                        }
                                        cairo_stroke (cr);
                                        cairo_set_line_width (cr, 0.0);
                                        for (int i = 0; i < 2; ++i)
                                        {
                                                cairo_rectangle (cr, xc - 0.2 * ext + i * 0.25 * ext, yc - 0.45 * ext, 0.15 * ext, 0.6 * ext);
                                                cairo_fill (cr);
                                        }
                                        break;

				case SymbolType::question:	cairo_move_to (cr, xc + 0.45 * ext, yc);
										cairo_arc (cr, xc, yc, 0.45 * ext, 0.0, 2.0 * M_PI);
										cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
										cairo_move_to (cr, xc - 0.15 * ext, yc - 0.15 * ext);
										cairo_arc (cr, xc, yc - 0.15 * ext, 0.15 * ext, M_PI, 2.25 * M_PI);
										cairo_arc_negative (cr, xc + 0.15 * ext, yc + 0.15 * ext, 0.15 * ext, 1.25 * M_PI, M_PI);
										cairo_set_line_width (cr, 0.1 * ext);
										cairo_stroke (cr);
										cairo_arc (cr, xc, yc + 0.3 * ext, 0.075 * ext, 0.0, 2.0 * M_PI);
										cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
										break;

				case SymbolType::warn:		cairo_arc (cr, xc, yc - 0.345 * ext, 0.05 * ext, 1.1667 * M_PI, 1.8333 * M_PI);
										cairo_arc (cr, xc + 0.3984 * ext, yc + 0.345 * ext, 0.05 * ext, 1.8333 * M_PI, 2.5 * M_PI);
										cairo_arc (cr, xc - 0.3984 * ext, yc + 0.345 * ext, 0.05 * ext, 0.5 * M_PI, 1.1667 * M_PI);
										cairo_close_path (cr);
										cairo_set_line_width (cr, 0.1 * ext);
										cairo_stroke (cr);
										cairo_arc (cr, xc, yc - 0.15 * ext, 0.05 * ext, M_PI, 2.0 * M_PI);
										cairo_line_to (cr, xc + 0.025 * ext, yc + 0.1 * ext);
										cairo_line_to (cr, xc - 0.025 * ext, yc + 0.1 * ext);
										cairo_close_path (cr);
										cairo_set_line_width (cr, 0.0);
										cairo_fill (cr);
										cairo_arc (cr, xc, yc + 0.2 * ext, 0.0375 * ext, 0.0, 2.0 * M_PI);
										cairo_fill (cr);
										break;


				case SymbolType::info:		cairo_move_to (cr, xc + 0.1 * ext, yc - 0.3 * ext);
										cairo_arc (cr, xc, yc - 0.3 * ext, 0.1 * ext, 0.0, 2.0 * M_PI);
										cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
										cairo_move_to (cr, xc - 0.2 * ext, yc - 0.1 * ext);
										cairo_line_to (cr, xc + 0.1 * ext, yc - 0.1 * ext);
										cairo_line_to (cr, xc + 0.1 * ext, yc + 0.45 * ext);
										cairo_line_to (cr, xc + 0.2 * ext, yc + 0.45 * ext);
										cairo_line_to (cr, xc + 0.2 * ext, yc + 0.5 * ext);
										cairo_line_to (cr, xc - 0.2 * ext, yc + 0.5 * ext);
										cairo_line_to (cr, xc - 0.2 * ext, yc + 0.45 * ext);
										cairo_line_to (cr, xc - 0.1 * ext, yc + 0.45 * ext);
										cairo_line_to (cr, xc - 0.1 * ext, yc - 0.05 * ext);
										cairo_line_to (cr, xc - 0.2 * ext, yc - 0.05 * ext);
										cairo_close_path (cr);
                                        cairo_set_line_width (cr, 0.0);
                                        cairo_fill (cr);
										break;

				case SymbolType::error:		cairo_move_to (cr, xc + 0.45 * ext, yc);
										cairo_arc (cr, xc, yc, 0.45 * ext, 0.0, 2.0 * M_PI);
										cairo_set_line_width (cr, 0.1 * ext);
                                        cairo_stroke (cr);
										cairo_move_to (cr, xc - 0.2 * ext, yc - 0.2 * ext);
										cairo_line_to (cr, xc + 0.2 * ext, yc + 0.2 * ext);
										cairo_move_to (cr, xc + 0.2 * ext, yc - 0.2 * ext);
										cairo_line_to (cr, xc - 0.2 * ext, yc + 0.2 * ext);
										cairo_set_line_width (cr, 0.1 * ext);
										cairo_stroke (cr);
										break;

				case SymbolType::edit:		cairo_move_to (cr, xc - 0.15 * ext, yc + 0.35 * ext);
										cairo_line_to (cr, xc - 0.45 * ext, yc + 0.45 * ext);
										cairo_line_to (cr, xc - 0.35 * ext, yc + 0.15 * ext);
										cairo_set_line_width (cr, 0.05 * ext);
										cairo_close_path (cr);
										cairo_stroke (cr);
										cairo_move_to (cr, xc - 0.3 * ext, yc + 0.4 * ext);
										cairo_line_to (cr, xc - 0.45 * ext, yc + 0.45 * ext);
										cairo_line_to (cr, xc - 0.4 * ext, yc + 0.3 * ext);
										cairo_set_line_width (cr, 0.0);
										cairo_close_path (cr);
										cairo_fill (cr);
										cairo_set_line_width (cr, 0.05 * ext);
										cairo_move_to (cr, xc - 0.15 * ext, yc + 0.35 * ext);
										cairo_line_to (cr, xc - 0.35 * ext, yc + 0.15 * ext);
										cairo_line_to (cr, xc + 0.1 * ext, yc - 0.3 * ext);
										cairo_line_to (cr, xc + 0.3 * ext, yc - 0.1 * ext);
										cairo_close_path (cr);
										cairo_stroke_preserve (cr);
										cairo_fill (cr);
										cairo_move_to (cr, xc + 0.4 * ext, yc - 0.2 * ext);
										cairo_line_to (cr, xc + 0.2 * ext, yc - 0.4 * ext);
										cairo_arc (cr, xc + 0.3 * ext, yc - 0.3 * ext, 0.1414 * ext, 1.25 * M_PI, 2.25 * M_PI);
										cairo_close_path (cr);
										cairo_stroke_preserve (cr);
										cairo_fill (cr);
										break;

				case SymbolType::pick:		cairo_move_to (cr, xc + 0.07 * ext, yc - 0.17 * ext);
										cairo_line_to (cr, xc + 0.17 * ext, yc - 0.07 * ext);
										cairo_line_to (cr, xc - 0.23 * ext, yc + 0.33 * ext);
										cairo_line_to (cr, xc - 0.33 * ext, yc + 0.35 * ext);
										cairo_line_to (cr, xc - 0.38 * ext, yc + 0.4 * ext);
										cairo_line_to (cr, xc - 0.4 * ext, yc + 0.38 * ext);
										cairo_line_to (cr, xc - 0.35 * ext, yc + 0.33 * ext);
										cairo_line_to (cr, xc - 0.33 * ext, yc + 0.28 * ext);
										cairo_line_to (cr, xc + 0.07 * ext, yc - 0.17 * ext);
										cairo_line_to (cr, xc + 0.02 * ext, yc - 0.22 * ext);
										cairo_line_to (cr, xc + 0.07 * ext, yc - 0.27 * ext);
										cairo_line_to (cr, xc + 0.12 * ext, yc - 0.22 * ext);
										cairo_line_to (cr, xc + 0.27 * ext, yc - 0.37 * ext);
										cairo_line_to (cr, xc + 0.37 * ext, yc - 0.27 * ext);
										cairo_line_to (cr, xc + 0.22 * ext, yc - 0.12 * ext);
										cairo_line_to (cr, xc + 0.27 * ext, yc - 0.07 * ext);
										cairo_line_to (cr, xc + 0.22 * ext, yc - 0.02 * ext);
										cairo_line_to (cr, xc + 0.17 * ext, yc - 0.07 * ext);
										cairo_set_line_width (cr, 0.05 * ext);
										cairo_stroke (cr);
										break;

				case SymbolType::cut:		{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_rectangle (cr, xc - 0.375 * size, yc - 0.25 * size, 0.5 * size, 0.75 * size);
											const double dash[] = {2.0};
											cairo_set_dash (cr, dash, 1, 0);
											cairo_stroke (cr);
											cairo_rectangle (cr, xc - 0.125 * size, yc - 0.5 * size, 0.5 * size, 0.75 * size);
											cairo_fill_preserve (cr);
											cairo_set_source_rgba (cr, 0, 0, 0, 1);
											cairo_set_dash (cr, dash, 0, 0);
											cairo_stroke (cr);
										}
										break;

				case SymbolType::copy:		{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_rectangle (cr, xc - 0.375 * size, yc - 0.25 * size, 0.5 * size, 0.75 * size);
											cairo_fill_preserve (cr);
											const double dash[] = {2.0};
											cairo_set_dash (cr, dash, 1, 0);
											cairo_stroke (cr);
											cairo_rectangle (cr, xc - 0.125 * size, yc - 0.5 * size, 0.5 * size, 0.75 * size);
											cairo_fill_preserve (cr);
											cairo_set_source_rgba (cr, 0, 0, 0, 1);
											cairo_set_dash (cr, dash, 0, 0);
											cairo_stroke (cr);
										}
										break;

				case SymbolType::paste:		{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_rectangle (cr, xc - 0.375 * size, yc - 0.5 * size, 0.5 * size, 0.75 * size);
											cairo_fill_preserve (cr);;
											cairo_stroke (cr);
											cairo_rectangle (cr, xc - 0.125 * size, yc - 0.25 * size, 0.5 * size, 0.75 * size);
											cairo_fill_preserve (cr);
											cairo_set_source_rgba (cr, 0, 0, 0, 1);
											cairo_stroke (cr);
										}
										break;

				case SymbolType::del:		{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_move_to (cr, xc - 0.25 * size, yc + 0.05 * size);
											cairo_line_to (cr, xc, yc + 0.3 * size);
											cairo_move_to (cr, xc, yc + 0.05 * size);
											cairo_line_to (cr, xc - 0.25 * size, yc + 0.3 * size);
											cairo_stroke (cr);
											cairo_rectangle (cr, xc - 0.375 * size, yc - 0.5 * size, 0.75 * size, size);
											const double dash[] = {2.0};
											cairo_set_dash (cr, dash, 1, 0);
											cairo_stroke (cr);
										}
										break;

				case SymbolType::xflip:		{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_rectangle (cr, xc - 0.375 * size, yc - 0.5 * size, 0.75 * size, size);
											cairo_fill_preserve (cr);
											const double dash[] = {2.0};
											cairo_set_dash (cr, dash, 1, 0);
											cairo_stroke (cr);
											cairo_set_dash (cr, dash, 0, 0);
											cairo_set_source_rgba (cr, 0, 0, 0, 1);
											cairo_move_to (cr, xc - 0.3 * size, yc);
											cairo_line_to (cr, xc - 0.15 * size, yc + 0.1 * size);
											cairo_line_to (cr, xc - 0.15 * size, yc - 0.1 * size);
											cairo_line_to (cr, xc - 0.3 * size, yc);
											cairo_line_to (cr, xc + 0.3 * size, yc);
											cairo_line_to (cr, xc + 0.15 * size, yc + 0.1 * size);
											cairo_line_to (cr, xc + 0.15 * size, yc - 0.1 * size);
											cairo_line_to (cr, xc + 0.3 * size, yc);
											cairo_stroke (cr);
										}
										break;

				case SymbolType::yflip:		{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_rectangle (cr, xc - 0.375 * size, yc - 0.5 * size, 0.75 * size, size);
											cairo_fill_preserve (cr);
											const double dash[] = {2.0};
											cairo_set_dash (cr, dash, 1, 0);
											cairo_stroke (cr);
											cairo_set_dash (cr, dash, 0, 0);
											cairo_set_source_rgba (cr, 0, 0, 0, 1);
											cairo_move_to (cr, xc, yc - 0.4 * size);
											cairo_line_to (cr, xc - 0.1 * size, yc - 0.25 * size);
											cairo_line_to (cr, xc + 0.1 * size, yc - 0.25 * size);
											cairo_line_to (cr, xc, yc - 0.4 * size);
											cairo_line_to (cr, xc, yc + 0.4 * size);
											cairo_line_to (cr, xc - 0.1 * size, yc + 0.25 * size);
											cairo_line_to (cr, xc + 0.1 * size, yc + 0.25 * size);
											cairo_line_to (cr, xc, yc + 0.4 * size);
											cairo_stroke (cr);
										}
										break;

				case SymbolType::load:		cairo_move_to (cr, xc, yc - 0.375 * ext);
										cairo_line_to (cr, xc + 0.25 * ext, yc - 0.125 * ext);
										cairo_line_to (cr, xc + 0.15 * ext, yc - 0.125 * ext);
										cairo_line_to (cr, xc + 0.15 * ext, yc + 0.25 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc + 0.25 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc - 0.125 * ext);
										cairo_line_to (cr, xc - 0.25 * ext, yc - 0.125 * ext);
										cairo_close_path (cr);
										cairo_move_to (cr, xc + 0.25 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc + 0.375 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc + 0.375 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc - 0.375 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc - 0.375 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc - 0.25 * ext, yc + 0.125 * ext);
										cairo_set_line_width (cr, 0.05 * ext);
										cairo_stroke (cr);
										break;

				case SymbolType::save:		cairo_move_to (cr, xc, yc + 0.25 * ext);
										cairo_line_to (cr, xc + 0.25 * ext, yc);
										cairo_line_to (cr, xc + 0.15 * ext, yc);
										cairo_line_to (cr, xc + 0.15 * ext, yc - 0.375 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc - 0.375 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc);
										cairo_line_to (cr, xc - 0.25 * ext, yc);
										cairo_close_path (cr);
										cairo_move_to (cr, xc + 0.25 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc + 0.375 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc + 0.375 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc - 0.375 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc - 0.375 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc - 0.25 * ext, yc + 0.125 * ext);
										cairo_set_line_width (cr, 0.05 * ext);
										cairo_stroke (cr);
										break;

				case SymbolType::home:		cairo_move_to (cr, xc, yc - 0.375 * ext);
										cairo_line_to (cr, xc + 0.375 * ext, yc);
										cairo_move_to (cr, xc + 0.3 * ext, yc - 0.075 * ext);
										cairo_line_to (cr, xc + 0.3 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc + 0.3 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc, yc + 0.375 * ext);
										cairo_line_to (cr, xc, yc + 0.125 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc + 0.125 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc - 0.3 * ext, yc + 0.375 * ext);
										cairo_line_to (cr, xc - 0.3 * ext, yc - 0.075 * ext);
										cairo_move_to (cr, xc, yc - 0.375 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc - 0.225 * ext);
										cairo_line_to (cr, xc - 0.15 * ext, yc - 0.375 * ext);
										cairo_line_to (cr, xc - 0.2 * ext, yc - 0.375 * ext);
										cairo_line_to (cr, xc - 0.2 * ext, yc - 0.175 * ext);
										cairo_line_to (cr, xc - 0.375 * ext, yc);
										cairo_set_line_width (cr, 0.05 * ext);
										cairo_stroke (cr);
										break;

				case SymbolType::newFolder:	{
											const double size = ext * 0.9;
											cairo_set_line_width (cr, 0.05 * ext);
											cairo_move_to (cr, x0 + 0.5 * w - 0.45 * size, y0 + 0.5 * h + 0.4 * size);
											cairo_line_to (cr, x0 + 0.5 * w - 0.5 * size, y0 + 0.5 * h + 0.35 * size);
											cairo_line_to (cr, x0 + 0.5 * w - 0.5 * size, y0 + 0.5 * h - 0.35 * size);
											cairo_line_to (cr, x0 + 0.5 * w - 0.45 * size, y0 + 0.5 * h - 0.4 * size);
											cairo_line_to (cr, x0 + 0.5 * w - 0.15 * size, y0 + 0.5 * h - 0.4 * size);
											cairo_line_to (cr, x0 + 0.5 * w - 0.05 * size, y0 + 0.5 * h - 0.3 * size);
											cairo_line_to (cr, x0 + 0.5 * w + 0.45 * size, y0 + 0.5 * h - 0.3 * size);
											cairo_line_to (cr, x0 + 0.5 * w + 0.5 * size, y0 + 0.5 * h - 0.25 * size);
											cairo_line_to (cr, x0 + 0.5 * w + 0.5 * size, y0 + 0.5 * h + 0.35 * size);
											cairo_line_to (cr, x0 + 0.5 * w + 0.45 * size, y0 + 0.5 * h + 0.4 * size);
											cairo_close_path (cr);
											cairo_move_to (cr, x0 + 0.5 * w + 0.1 * size, y0 + 0.5 * h + 0.05 * size);
											cairo_line_to (cr, x0 + 0.5 * w + 0.4 * size, y0 + 0.5 * h + 0.05 * size);
											cairo_move_to (cr, x0 + 0.5 * w + 0.25 * size, y0 + 0.5 * h - 0.1 * size);
											cairo_line_to (cr, x0 + 0.5 * w + 0.25 * size, y0 + 0.5 * h + 0.2 * size);
											cairo_stroke (cr);
										}
										break;

                default:                break;
		}
	}

	cairo_destroy (cr);
}

}

#endif /* BWIDGETS_SYMBOL_HPP_ */
