/* TextBox.hpp
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

#ifndef BWIDGETS_TEXTBOX_HPP_
#define BWIDGETS_TEXTBOX_HPP_

#include "Box.hpp"
#include "Text.hpp"

#ifndef BWIDGETS_DEFAULT_TEXTBOX_WIDTH
#define BWIDGETS_DEFAULT_TEXTBOX_WIDTH BWIDGETS_DEFAULT_BOX_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_TEXTBOX_HEIGHT
#define BWIDGETS_DEFAULT_TEXTBOX_HEIGHT (BWIDGETS_DEFAULT_BOX_HEIGHT + 80.0)
#endif

namespace BWidgets
{

/**
 *  @brief  Composite widget with text and buttons.
 *
 *  %TextBox is a composite Widget based on Box and additionally contains a
 *  Text.
 */
class TextBox : public Box
{
public:

	Text text;

	/**
	 *  @brief  Constructs an empty default %TextBox object.
	 */
	TextBox ();

	/**
	 *  @brief  Constructs an empty default %TextBox object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	TextBox (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Construct a %TextBox object with default size.
	 *  @param text  Text string.
	 *  @param buttonlabels  Optional, initializer list with butten label 
	 *  strings.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  The box only hosts an OK button if no button labels are provided.
	 */
	TextBox (const std::string& text, std::initializer_list<std::string> buttonlabels = {}, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Construct a %TextBox object.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param text  Text string.
	 *  @param buttonlabels  Optional, initializer list with button label 
	 *  strings.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  The box only hosts an OK button if no button labels are provided.
	 */
	TextBox (const double x, const double y, const double width, const double height,
		 const std::string& text, std::initializer_list<std::string> buttons = {}, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %TextBox. 
	 *  @return  Pointer to the new %TextBox.
	 *
	 *  Creates a clone of this %TextBox by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %TextBox. 
	 *  @param that  Other %TextBox.
	 *
	 *  Copies all properties from another %TextBox. But NOT its linkage.
	 */
	void copy (const TextBox* that);

	/**
     *  @brief  Optimizes the %TextBox widget extends.
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

inline TextBox::TextBox () : TextBox (0.0, 0.0, BWIDGETS_DEFAULT_TEXTBOX_WIDTH, BWIDGETS_DEFAULT_TEXTBOX_HEIGHT, "", {}, BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

inline TextBox::TextBox (const uint32_t urid, const std::string& title) :
	TextBox (0, 0, BWIDGETS_DEFAULT_TEXTBOX_WIDTH, BWIDGETS_DEFAULT_TEXTBOX_HEIGHT, "", {}, urid, title) 
{

}

inline TextBox::TextBox (const std::string& txt, std::initializer_list<std::string> buttonlabels, uint32_t urid, std::string title) :
	TextBox (0, 0, BWIDGETS_DEFAULT_TEXTBOX_WIDTH, BWIDGETS_DEFAULT_TEXTBOX_HEIGHT, txt, buttonlabels, urid, title) 
{

}

inline TextBox::TextBox	(const double x, const double y, const double width, const double height,
				 const std::string& txt, std::initializer_list<std::string> buttonlabels, uint32_t urid, std::string title) :
	Box (x, y, width, height, buttonlabels, urid, title),
	text (txt, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/text"))
{
	text.setEventPassable(BEvents::Event::BUTTON_PRESS_EVENT + BEvents::Event::POINTER_DRAG_EVENT);
	add (&text);
}

inline Widget* TextBox::clone () const 
{
	Widget* f = new TextBox (urid_, title_);
	f->copy (this);
	return f;
}

inline void TextBox::copy (const TextBox* that)
{
	text.copy (&that->text);
	Box::copy (that);
}

inline void TextBox::resize ()
{
	text.resize (BWIDGETS_DEFAULT_TEXTBOX_WIDTH - 2.0 * getXOffset() - 2.0 * BWIDGETS_DEFAULT_MENU_PADDING, text.getHeight());	// Define the text width
	text.resize();	// Optimize the text hight
	text.moveTo (getXOffset() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset() + BWIDGETS_DEFAULT_MENU_PADDING);
	Box::resize();
}

inline void TextBox::resize (const double width, const double height)
{
	resize (BUtilities::Point<> (width, height));
}

inline void TextBox::resize (const BUtilities::Point<> extends)
{
	Box::resize (extends);
}

inline void TextBox::update ()
{
	text.moveTo (getXOffset() + BWIDGETS_DEFAULT_MENU_PADDING, getYOffset() + BWIDGETS_DEFAULT_MENU_PADDING);
	text.resize (getEffectiveWidth() - 2.0 * BWIDGETS_DEFAULT_MENU_PADDING, getEffectiveHeight() - BWIDGETS_DEFAULT_BUTTON_HEIGHT - 3.0 * BWIDGETS_DEFAULT_MENU_PADDING);
	Box::update ();
}

}

#endif /* BWIDGETS_TEXTBOX_HPP_ */
