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
	 * @brief  Constructs a new %TextButton object with default parameters.
	 */
	TextButton ();

	/**
	 *  @brief  Creates a %TextButton with default size.
	 *  @param text  Label text.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	TextButton	(const std::string& text, bool toggleable = false, bool clicked = false,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %TextButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param text  Label text.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	TextButton	(const double x, const double y, const double width, const double height, 
				 const std::string& text, bool toggleable = false, bool clicked = false,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

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

inline TextButton::TextButton () : TextButton (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, "", false, false, URID_UNKNOWN_URID, "") {}

inline TextButton::TextButton	(const std::string& text, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	TextButton (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, text, toggleable, clicked, urid, title) {}

inline TextButton::TextButton	(const double x, const double y, const double width, const double height, 
			 	 		const std::string& text, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	label (0, 0, width, height, text, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"))
{
	BStyles::Font font = label.getFont();
	font.align = BStyles::Font::TextAlign::TEXT_ALIGN_CENTER;
	font.valign = BStyles::Font::TextVAlign::TEXT_VALIGN_MIDDLE;
	label.setFont (font);
	add (&label);
}

inline Widget* TextButton::clone () const 
{
	Widget* f = new TextButton ();
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
	label.moveTo (0, 0);
	Button::resize ();
}

inline void TextButton::resize (const double width, const double height) 
{
	TextButton::resize (BUtilities::Point (width, height));
}

inline void TextButton::resize (const BUtilities::Point extends)
{
	Button::resize (BUtilities::Point (extends.x, extends.y));
	label.resize (getEffectiveWidth(), getEffectiveHeight());
	label.moveTo (label.center(), label.middle());
}

inline void TextButton::update ()
{
	label.setStatus (getValue() ? BStyles::Status::STATUS_ACTIVE : BStyles::Status::STATUS_NORMAL);
	label.resize (getEffectiveWidth(), getEffectiveHeight());
	label.moveTo (label.center(), label.middle());
	Button::update ();
}

}

#endif /* BWIDGETS_TEXTBUTTON_HPP_ */
