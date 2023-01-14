/* MessageBox.hpp
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

#ifndef BWIDGETS_MESSAGEBOX_HPP_
#define BWIDGETS_MESSAGEBOX_HPP_

#include "TextBox.hpp"
#include "Symbol.hpp"
#include <cairo/cairo.h>

#ifndef BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH
#define BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH (BWIDGETS_DEFAULT_TEXTBOX_WIDTH + 100.0)
#endif

#ifndef BWIDGETS_DEFAULT_MESSAGEBOX_HEIGHT
#define BWIDGETS_DEFAULT_MESSAGEBOX_HEIGHT (BWIDGETS_DEFAULT_TEXTBOX_HEIGHT + 40.0)
#endif

namespace BWidgets
{

/**
 *  @brief  Composite widget with a symbol, a headline, a text and buttons.
 *
 *  %MessageBox is a composite Widget based on TextBox and additionally 
 *  contains a symbol and a headline.
 */
class MessageBox : public TextBox
{
public:

	Symbol symbol;
	Text headline;

	/**
	 *  @brief  Constructs an empty default %MessageBox object.
	 */
	MessageBox ();

	/**
	 *  @brief  Constructs an empty default %MessageBox object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	MessageBox (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Construct a %MessageBox object with default size.
	 *  @param symbol  Symbol index.
	 *  @param headline  Headline sting.
	 *  @param text  Optional, text string.
	 *  @param buttonlabels  Optional, initializer list with butten label 
	 *  strings.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  The box only hosts an OK button if no button labels are provided.
	 */
	MessageBox	(const Symbol::SymbolType symbol, const std::string& headline, std::string text = "", 
				 std::initializer_list<std::string> buttonlabels = {}, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Construct a %MessageBox object.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param symbol  Symbol index.
	 *  @param headline  Headline sting.
	 *  @param text  Optional, text string.
	 *  @param buttonlabels  Optional, initializer list with button label 
	 *  strings.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  The box only hosts an OK button if no button labels are provided.
	 */
	MessageBox	(const double x, const double y, const double width, const double height,
				 const Symbol::SymbolType symbol, const std::string& headline, std::string text = "", 
				 std::initializer_list<std::string> buttons = {}, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %MessageBox. 
	 *  @return  Pointer to the new %MessageBox.
	 *
	 *  Creates a clone of this %MessageBox by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %MessageBox. 
	 *  @param that  Other %MessageBox.
	 *
	 *  Copies all properties from another %MessageBox. But NOT its linkage.
	 */
	void copy (const MessageBox* that);

	/**
     *  @brief  Optimizes the %MessageBox widget extends.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the object.
	 *  @param width  New object width.
	 *  @param height  New object height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the object.
	 *  @param extends  New object extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;
};

inline MessageBox::MessageBox () : 
	MessageBox (0.0, 0.0, BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH, BWIDGETS_DEFAULT_MESSAGEBOX_HEIGHT, Symbol::SymbolType::none, "", "", {}, BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

inline MessageBox::MessageBox	(const uint32_t urid, const std::string& title) :
	MessageBox (0, 0, BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH, BWIDGETS_DEFAULT_MESSAGEBOX_HEIGHT, Symbol::SymbolType::none, "", "", {}, urid, title) 
{

}

inline MessageBox::MessageBox	(const Symbol::SymbolType symbol, const std::string& headline, std::string text, 
								 std::initializer_list<std::string> buttonlabels, uint32_t urid, std::string title) :
	MessageBox (0, 0, BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH, BWIDGETS_DEFAULT_MESSAGEBOX_HEIGHT, symbol, headline, text, buttonlabels, urid, title) 
{

}

inline MessageBox::MessageBox	(const double x, const double y, const double width, const double height,
								 const Symbol::SymbolType symbol, const std::string& headline, std::string text, 
								 std::initializer_list<std::string> buttonlabels, uint32_t urid, std::string title) :
	TextBox (x, y, width, height, text, buttonlabels, urid, title),
	symbol (symbol, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/symbol")),
	headline (headline, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/title"))
{
	BStyles::Font hFont = this->headline.getFont();
	hFont.weight = CAIRO_FONT_WEIGHT_BOLD;
	this->headline.setFont (hFont);
	this->symbol.setEventPassable(BEvents::Event::EventType::ButtonPressEvent | BEvents::Event::EventType::PointerDragEvent);
	this->headline.setEventPassable(BEvents::Event::EventType::ButtonPressEvent | BEvents::Event::EventType::PointerDragEvent);
	add (&this->symbol);
	add (&this->headline);
}

inline Widget* MessageBox::clone () const 
{
	Widget* f = new MessageBox (urid_, title_);
	f->copy (this);
	return f;
}

inline void MessageBox::copy (const MessageBox* that)
{
	symbol.copy (&that->symbol);
	headline.copy (&that->headline);
	TextBox::copy (that);
}

inline void MessageBox::resize ()
{
	// Symbol
	if (symbol.getSymbol() == Symbol::SymbolType::none)
	{
		symbol.moveTo (getXOffset(), getYOffset());
		symbol.resize (0, 0);
	}
	else 
	{
		symbol.moveTo (getXOffset() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset() + BWIDGETS_DEFAULT_MENU_PADDING);
		symbol.resize (4.0 * text.getFont().size, 4.0 * text.getFont().size);
	}

	// Headline
	if (headline.getText() == "")
	{
		headline.moveTo (symbol.getPosition().x + symbol.getWidth() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset());
		headline.resize (0, 0);
	}
	else 
	{
		headline.moveTo (symbol.getPosition().x + symbol.getWidth() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset() + BWIDGETS_DEFAULT_MENU_PADDING);
		headline.resize	(BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH - symbol.getPosition().x - symbol.getWidth() - 2.0 * BWIDGETS_DEFAULT_MENU_PADDING - getXOffset(), 
						 getEffectiveHeight() - 3.0 * BWIDGETS_DEFAULT_MENU_PADDING - BWIDGETS_DEFAULT_BUTTON_HEIGHT);	// Set width
		headline.resize ();		// Optimize Height
	}

	// Text
	text.moveTo	(headline.getPosition().x, headline.getPosition().y + headline.getHeight() + BWIDGETS_DEFAULT_MENU_PADDING);
	text.resize	(BWIDGETS_DEFAULT_MESSAGEBOX_WIDTH - symbol.getPosition().x - symbol.getWidth() - 2.0 * BWIDGETS_DEFAULT_MENU_PADDING - getXOffset(), 
				 getHeight() - headline.getPosition().y - headline.getHeight() - 4.0 * BWIDGETS_DEFAULT_MENU_PADDING - getYOffset()); // Set width
	text.resize (); // Optimize Height

	Box::resize();
}

inline void MessageBox::resize (const double width, const double height)
{
	resize (BUtilities::Point<> (width, height));
}

inline void MessageBox::resize (const BUtilities::Point<> extends)
{
	Box::resize (extends);
}

inline void MessageBox::update ()
{
	// Symbol
	if (symbol.getSymbol() == Symbol::SymbolType::none)
	{
		symbol.moveTo (getXOffset(), getYOffset());
		symbol.resize (0, 0);
	}
	else 
	{
		symbol.moveTo (getXOffset() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset() + BWIDGETS_DEFAULT_MENU_PADDING);
		symbol.resize (4.0 * text.getFont().size, 4.0 * text.getFont().size);
	}

	// Headline
	if (headline.getText() == "")
	{
		headline.moveTo (symbol.getPosition().x + symbol.getWidth() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset());
		headline.resize (0, 0);
	}
	else 
	{
		headline.moveTo (symbol.getPosition().x + symbol.getWidth() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset() + BWIDGETS_DEFAULT_MENU_PADDING);
		headline.resize	(getWidth() - symbol.getPosition().x - symbol.getWidth() - 2.0 * BWIDGETS_DEFAULT_MENU_PADDING - getXOffset(), 
						 getEffectiveHeight() - 3.0 * BWIDGETS_DEFAULT_MENU_PADDING - BWIDGETS_DEFAULT_BUTTON_HEIGHT);	// Set width
		headline.resize ();		// Optimize Height
	}

	// Text
	text.moveTo	(headline.getPosition().x, headline.getPosition().y + headline.getHeight() + BWIDGETS_DEFAULT_MENU_PADDING);
	text.resize	(getWidth() - symbol.getPosition().x - symbol.getWidth() - 2.0 * BWIDGETS_DEFAULT_MENU_PADDING - getXOffset(), 
				 getHeight() - headline.getPosition().y - headline.getHeight() - 4.0 * BWIDGETS_DEFAULT_MENU_PADDING - getYOffset());

	// Buttons
	Box::update ();
}

}

#endif /* BWIDGETS_MESSAGEBOX_HPP_ */
