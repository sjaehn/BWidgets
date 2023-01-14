/* TextButton.hpp
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

#ifndef BWIDGETS_TEXTBUTTON_HPP_
#define BWIDGETS_TEXTBUTTON_HPP_

#include "Button.hpp"
#include "Label.hpp"

#ifndef BWIDGETS_DEFAULT_TEXTBUTTON_WIDTH
#define BWIDGETS_DEFAULT_TEXTBUTTON_WIDTH BWIDGETS_DEFAULT_BUTTON_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_TEXTBUTTON_HEIGHT
#define BWIDGETS_DEFAULT_TEXTBUTTON_HEIGHT BWIDGETS_DEFAULT_BUTTON_HEIGHT
#endif

namespace BWidgets
{
/**
 *  @brief Composite Button Widget containing a text Label.
 *
 *  %TextButton is a Button containing a label. A %TextButton changes its 
 *  label status (and thus its color) in addition to the change of its Border
 *  Color upon changing the condition.
 */
class TextButton : public Button
{
public:

	Label label;

	/**
	 *  @brief  Constructs a new %TextButton object with default parameters.
	 */
	TextButton ();

	/**
	 *  @brief  Constructs a new %TextButton object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	TextButton (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %TextButton with default size.
	 *  @param text  Label text.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	TextButton	(const std::string& text, bool toggleable = false, bool clicked = false,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %TextButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param text  Label text.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	TextButton	(const double x, const double y, const double width, const double height, 
				 const std::string& text, bool toggleable = false, bool clicked = false,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %TextButton. 
	 *  @return  Pointer to the new %TextButton.
	 *
	 *  Creates a clone of this %TextButton by copying all properties. But NOT
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %TextButton. 
	 *  @param that  Other %TextButton.
	 *
	 *  Copies all properties from another %TextButton. But NOT its linkage.
	 */
	void copy (const TextButton* that);

	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Firstly optimizes its labels size. Then resizes the widget to include
	 *  all direct children (including the label) into the widget area.
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

inline TextButton::TextButton () : TextButton (0.0, 0.0, BWIDGETS_DEFAULT_TEXTBUTTON_WIDTH, BWIDGETS_DEFAULT_TEXTBUTTON_HEIGHT, "", false, false, BUTILITIES_URID_UNKNOWN_URID, "") {}

inline TextButton::TextButton	(const uint32_t urid, const std::string& title) :
	TextButton (0.0, 0.0, BWIDGETS_DEFAULT_TEXTBUTTON_WIDTH, BWIDGETS_DEFAULT_TEXTBUTTON_HEIGHT, "", false, false, urid, title) {}

inline TextButton::TextButton	(const std::string& text, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	TextButton (0.0, 0.0, BWIDGETS_DEFAULT_TEXTBUTTON_WIDTH, BWIDGETS_DEFAULT_TEXTBUTTON_HEIGHT, text, toggleable, clicked, urid, title) {}

inline TextButton::TextButton	(const double x, const double y, const double width, const double height, 
			 	 		const std::string& text, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	label (0, 0, width, height, text, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"))
{
	BStyles::Font font = label.getFont();
	font.align = BStyles::Font::TextAlign::center;
	font.valign = BStyles::Font::TextVAlign::middle;
	label.setFont (font);
	label.setFocusable(false);
	label.setEventPassable (BEvents::Event::EventType::ButtonPressEvent | 
							BEvents::Event::EventType::ButtonClickEvent | 
							BEvents::Event::EventType::PointerFocusEvents);
	add (&label);
}

inline Widget* TextButton::clone () const 
{
	Widget* f = new TextButton (urid_, title_);
	f->copy (this);
	return f;
}

inline void TextButton::copy (const TextButton* that)
{
	label.copy (&that->label);
    Button::copy (that);
}

inline void TextButton::resize ()
{
	label.resize ();
	label.moveTo (getXOffset() + (5.0 / 14.0) * label.getHeight(), getYOffset() + (5.0 / 14.0) * label.getHeight());
	Button::resize();
}

inline void TextButton::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void TextButton::resize (const BUtilities::Point<> extends)
{
	Button::resize (extends);
}

inline void TextButton::update ()
{
	label.setStatus (getValue() ? BStyles::Status::active : BStyles::Status::normal);
	label.resize ();
	label.moveTo (label.center(), label.middle());
	Button::update ();
}

}

#endif /* BWIDGETS_TEXTBUTTON_HPP_ */
