/* EditLabel.hpp
 * Copyright (C) 2018, 2019  Sven Jähnichen
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

#ifndef BWIDGETS_EDITLABEL_HPP_
#define BWIDGETS_EDITLABEL_HPP_

#include "Label.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/KeyPressable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "../BEvents/KeyEvent.hpp"
#include "Window.hpp"
#include <locale>
#include <codecvt>

#ifndef BWIDGETS_DEFAULT_EDITLABEL_WIDTH
#define BWIDGETS_DEFAULT_EDITLABEL_WIDTH BWIDGETS_DEFAULT_LABEL_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_EDITLABEL_HEIGHT
#define BWIDGETS_DEFAULT_EDITLABEL_HEIGHT BWIDGETS_DEFAULT_LABEL_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  Single line text edit widget.
 *
 *  %EditLabel allows the user to:
 *  * set the edit cursor by clicking on the text (Clickable),
 *  * select a text region by dragging (Draggable),
 *  * change the text via the keyboard (KeyPressable),
 *  * keep the new text and emit it as a ValueChangedEvent (Valueable) once
 *    the edit is confirmed (<Enter>), or to discard changes (<Esc>).
 */
class EditLabel : public Label, public Clickable, public Draggable, public KeyPressable, public ValueableTyped<std::string>
{
protected:
	bool editMode_;
	size_t cursorFrom_;
	size_t cursorTo_;

public:

	/**
	 *  @brief  Constructs an empty default %EditLabel object.
	 */
	EditLabel ();

	/**
	 *  @brief  Constructs an empty default %EditLabel object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	EditLabel (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Constructs a %EditLabel object at the origin with optimized 
	 *  extends.
	 *  @param text  Text.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %EditLabel title (default = "").
	 */
	EditLabel (const std::string& text, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Constructs a %EditLabel object at the origin.
	 *  @param x  %Label X origin coordinate.
	 *  @param y  %Label Y origin coordinate.
	 *  @param width  %Label width.
	 *  @param height  %Label height.
	 *  @param text  Text.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %EditLabel title (default = "").
	 */
	EditLabel	(const double x, const double y, const double width, const double height, 
				 const std::string& text, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %EditLabel. 
	 *  @return  Pointer to the new %EditLabel.
	 *
	 *  Creates a clone of this %EditLabel by copying all properties. But NOT 
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %EditLabel. 
	 *  @param that  Other %EditLabel.
	 *
	 *  Copies all properties from another %Label. But NOT its linkage.
	 */
	void copy (const EditLabel* that);

	/**
     *  @brief  Sets the label text (= value).
     *  @param value  Label text (= value).
     *
     *  Also emits a ValueChangeTyped<T> event.
     */
    virtual void setValue (const std::string& text) override;

	/**
	 *  @brief  Sets the label text.
	 *  @param text  Label text.
	 *
	 *  Equivalent to setValue().
	 */
	virtual void setText (const std::string& text) override;

	/**
	 *  @brief  Gets the (stored) label text (= value).
	 *  @return  Label text (= value).
	 *
	 *  Equivalent to getValue().
	 *  If the EditLabel is currently edited, then %getText() returns the last
	 *  stored text.
	 */
	virtual std::string getText () const override;

	/**
	 *  @brief  Changes the edit mode.
	 *  @param mode  True for entering the edit mode, otherwise false.
	 *
	 *  The edit mode allows editing the text. The edit mode is entered by
	 *  clicking on the text. And it is leaved by pressing <Enter> or <Esc>. 
	 */
	virtual void setEditMode (const bool mode);

	/**
	 *  @brief  Gets the edit mode.
	 *  @return  True for the edit mode, otherwise false.
	 *
	 *  The edit mode allows editing the text. The edit mode is entered by
	 *  clicking on the text. And it is leaved by pressing <Enter> or <Esc>. 
	 */
	bool getEditMode () const;

	/**
	 *  @brief  Sets the cursor position.
	 *  @param pos  Cursor position starting from 0 (before the first char) to
	 *  text_.size() (behind the last char).
	 */
	virtual void setCursor (const size_t pos);

	/**
	 *  @brief  Sets a selection range between two cursor positions.
	 *  @param from  First cursor position.
	 *  @param to  Second cursor position.
	 *
	 *  Cursor positions start from 0 (before the first char) to text_.size() 
	 *  (behind the last char).
	 */
	virtual void setCursor (const size_t from, const size_t to);

	/**
	 *  @brief  Applies the changes of the text, leaves the edit mode and emits
	 *  a ValueChangedEvent.
	 */
	virtual void applyEdit ();

	/**
	 *  @brief  Discards the changes of the text, restores the previously stored 
	 *  text and leaves the edit mode.
	 */
	virtual void discardEdit ();

	/**
     *  @brief  Method called when pointer button clicked (pressed and 
     *  released).
     *  @param event  Passed Event.
     *
     *  Method called from the main window event scheduler when
     *  pointer button cklicked. By default, it calls its static callback 
     *  function.
     */
	virtual void onButtonClicked (BEvents::Event* event) override;

	/**
     *  @brief  Method called upon pointer drag.
     *  @param event  Passed Event.
     *
     *  Method called from the main window event scheduler upon
     *  a pointer drag. By default, it calls its static callback function.
     */
	virtual void onPointerDragged (BEvents::Event* event) override;

	/**
     *  @brief  Method when a KeyEvent with the type KEY_PRESS_EVENT is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Method called from the main window event scheduler if a
     *  key is pressed. By default, it calls its static callback function.
     */
	virtual void onKeyPressed (BEvents::Event* event) override;

protected:

	/**
	 *  @brief  Calculates the char position (= cursor position) from the
	 *  mouse pointer position.
	 *  @param position  Mouse pointer position.
	 *  @return  Cursor position.
	 */
	size_t getCursorFromCoords (const BUtilities::Point<>& position);

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

inline EditLabel::EditLabel () : 
	EditLabel (0.0, 0.0, BWIDGETS_DEFAULT_EDITLABEL_WIDTH, BWIDGETS_DEFAULT_EDITLABEL_HEIGHT, "", BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

inline EditLabel::EditLabel (const uint32_t urid, const std::string& title) :
	EditLabel (0.0, 0.0, BWIDGETS_DEFAULT_EDITLABEL_WIDTH, BWIDGETS_DEFAULT_EDITLABEL_HEIGHT, "", urid, title)
{
	
}

inline EditLabel::EditLabel (const std::string& text, uint32_t urid, std::string title) :
	EditLabel (0.0, 0.0, BWIDGETS_DEFAULT_EDITLABEL_WIDTH, BWIDGETS_DEFAULT_EDITLABEL_HEIGHT, text, urid, title)
{
	Label::resize();
}

inline EditLabel::EditLabel (const double x, const double y, const double width, const double height, const std::string& text, uint32_t urid, std::string title) :
	Label (x, y, width, height, text, urid, title),
	Clickable(),
	Draggable(),
	KeyPressable(),
	ValueableTyped<std::string> (text),
	editMode_ (false),
	cursorFrom_ (0),
	cursorTo_ (0)
{
	
}

inline Widget* EditLabel::clone () const 
{
	Widget* f = new EditLabel (urid_, title_);
	f->copy (this);
	return f;
}

inline void EditLabel::copy (const EditLabel* that)
{
	Clickable::operator= (*that);
	Draggable::operator= (*that);
	KeyPressable::operator= (*that);
	ValueableTyped<std::string>::operator= (*that);
	editMode_ = that->editMode_;
	cursorFrom_ = that->cursorFrom_;
	cursorTo_ = that->cursorTo_;
    Label::copy (that);
}

inline void EditLabel::setValue (const std::string& text)
{
	// Set displayed text
	if (text != Label::getText())
	{
		setEditMode (false);
		text_ = text;
		setCursor (0);
		update ();
	}

	// Set value too
	ValueableTyped<std::string>::setValue (text);
}

inline void EditLabel::setText (const std::string& text)
{
	setValue (text);
}

inline std::string EditLabel::getText () const
{
	return getValue();
}

inline void EditLabel::setEditMode (const bool mode)
{
	if (mode != editMode_)
	{
		editMode_ = mode;
		update ();
	}
}

inline bool EditLabel::getEditMode () const 
{
	return 
	editMode_;
}

inline void EditLabel::setCursor (const size_t pos) 
{
	setCursor (pos, pos);
}

inline void EditLabel::setCursor (const size_t from, const size_t to)
{
	// Check limits
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
	std::u32string u32labelText = convert.from_bytes (text_);
	const size_t s32 = u32labelText.length ();
	const size_t cf = std::min (from, s32);
	const size_t ct = std::min (to, s32);

	// Apply changes
	if ((cf != cursorFrom_) || (ct != cursorTo_))
	{
		cursorFrom_ = cf;
		cursorTo_ = ct;
		update ();
	}
}

inline void EditLabel::applyEdit ()
{
	if (dynamic_cast<Window*>(main_)) dynamic_cast<Window*>(main_)->getKeyGrabStack()->remove (this);
	setEditMode (false);
	if (text_ != getValue()) setValue (text_);
}

inline void EditLabel::discardEdit ()
{
	if (dynamic_cast<Window*>(main_)) dynamic_cast<Window*>(main_)->getKeyGrabStack()->remove (this);
	setEditMode (false);
	setValue (getValue());
}

inline void EditLabel::onButtonClicked (BEvents::Event* event)
{
	if 
	(
		isValueable() && 
		dynamic_cast<BEvents::PointerEvent*>(event) && 
		(dynamic_cast<BEvents::PointerEvent*>(event)->getWidget () == this) && 
		dynamic_cast<Window*>(main_)
	)
	{
		dynamic_cast<Window*>(main_)->getKeyGrabStack()->add (this);
		setEditMode (true);
		size_t cursor = getCursorFromCoords (dynamic_cast<BEvents::PointerEvent*>(event)->getPosition ());
		setCursor (cursor, cursor);
	}

	Clickable::onButtonClicked (event);
}

inline void EditLabel::onPointerDragged (BEvents::Event* event)
{
	if
	(
		isValueable() &&
		editMode_ &&
		dynamic_cast<BEvents::PointerEvent*>(event) &&
		(dynamic_cast<BEvents::PointerEvent*>(event)->getWidget () == this) &&
		dynamic_cast<Window*>(main_) &&
		(dynamic_cast<Window*>(main_)->getKeyGrabStack()->getGrab(0)->getWidget() == this)
	)
	{
		size_t cursor = getCursorFromCoords (dynamic_cast<BEvents::PointerEvent*>(event)->getPosition ());
		setCursor (cursorFrom_, cursor);
	}

	Draggable::onPointerDragged (event);
}

inline void EditLabel::onKeyPressed (BEvents::Event* event)
{
	if
	(
		dynamic_cast<BEvents::KeyEvent*>(event) &&
		(event->getWidget () == this) &&
		dynamic_cast<Window*>(main_) &&
		(dynamic_cast<Window*>(main_)->getKeyGrabStack()->getGrab(0)->getWidget() == this)
	)
	{
		uint32_t key = dynamic_cast<BEvents::KeyEvent*>(event)->getKey ();

		switch (key)
		{
			// Backspace
			case 8:					{
										std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
										std::u32string u32labelText = convert.from_bytes (text_);
										const size_t s32 = u32labelText.length ();
										size_t cf = std::min (cursorFrom_, s32);
										size_t ct = std::min (cursorTo_, s32);
										if (ct < cf) std::swap (ct, cf);

										if (cf != ct) u32labelText.erase (cf, ct - cf);
										else if (cf > 0)
										{
											u32labelText.erase (cf - 1, 1);
											--cf;
										}

										text_ = convert.to_bytes (u32labelText);
										setCursor (cf);
										// update() done via setCursor()
									}
									break;

			// Enter
			case 13:				applyEdit ();
									break;

			// Escape
			case 27:				discardEdit ();
									break;

			// Delete
			case 127:				{
										std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
										std::u32string u32labelText = convert.from_bytes (text_);
										const size_t s32 = u32labelText.length ();
										size_t cf = std::min (cursorFrom_, s32);
										size_t ct = std::min (cursorTo_, s32);
										if (ct < cf) std::swap (ct, cf);

										if (cf != ct) u32labelText.erase (cf, ct - cf);
										else if (cf < u32labelText.size ()) u32labelText.erase (cf, 1);

										text_ = convert.to_bytes (u32labelText);
										setCursor (cf);
										update ();
									}
									break;

			case PUGL_KEY_LEFT :	if (cursorFrom_ > 0) setCursor (cursorFrom_ - 1);
									break;

			case PUGL_KEY_RIGHT :	setCursor (cursorFrom_ + 1);
									break;

			default:				{
										if ((key >= 0x20) && (key < 0x7F))
										{
											std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
											std::u32string u32labelText = convert.from_bytes (text_);
											const size_t s32 = u32labelText.length ();
											size_t cf = std::min (cursorFrom_, s32);
											size_t ct = std::min (cursorTo_, s32);
											if (ct < cf) std::swap (ct, cf);

											if (cf != ct) u32labelText.erase (cf, ct - cf);
											u32labelText.insert (u32labelText.begin () + cf, key);

											text_ = convert.to_bytes (u32labelText);
											setCursor (cf + 1);
											// update() done via setCursor()
										}
									}
									break;
		}
	}

	KeyPressable::onKeyPressed(event);
}

inline size_t EditLabel::getCursorFromCoords (const BUtilities::Point<>& position)
{
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
	const std::u32string u32labelText = convert.from_bytes (text_);
	size_t cursor = u32labelText.length ();

	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return 0;

	cairo_t* cr = cairo_create (cairoSurface());

	if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
	{
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;

		const double xoff = getXOffset ();
		const double w = getEffectiveWidth ();

		const BStyles::Font font = getFont();
		const cairo_text_extents_t ext = font.getCairoTextExtents (cr, "|" + text_ + "|");
		const cairo_text_extents_t ext0 = font.getCairoTextExtents(cr, "|");

		double x0;

		switch (font.align)
		{
			case BStyles::Font::TEXT_ALIGN_LEFT:	x0 = - ext.x_bearing;
													break;
													
			case BStyles::Font::TEXT_ALIGN_CENTER:	x0 = w / 2 - (ext.width - 2 * ext0.width - 2 * ext0.x_bearing) / 2;
													break;

			case BStyles::Font::TEXT_ALIGN_RIGHT:	x0 = w - (ext.width - 2 * ext0.width - 2 * ext0.x_bearing);
													break;

			default:								x0 = 0;
		}

		std::u32string u32fragment = U"";
		for (size_t i = 0; i < u32labelText.length (); ++i)
		{
			u32fragment += u32labelText[i];
			const std::string fragment = convert.to_bytes (u32fragment);
			const cairo_text_extents_t ext1 = font.getCairoTextExtents(cr, "|" + fragment + "|");

			if (position.x < xoff + x0 + ext1.width - 2 * ext0.width - 2 * ext0.x_bearing)
			{
				cursor = i;
				break;
			}
		}

		cairo_destroy (cr);
	}

	return cursor;
}

inline void EditLabel::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void EditLabel::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void EditLabel::draw (const BUtilities::Area<>& area)
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

		const double xoff = getXOffset ();
		const double yoff = getYOffset ();
		const double w = getEffectiveWidth ();
		const double h = getEffectiveHeight ();

		const BStyles::Font font = getFont();
		const cairo_text_extents_t ext = font.getCairoTextExtents (cr, "|" + text_ + "|");
		const cairo_text_extents_t ext0 = font.getCairoTextExtents(cr, "|");
		cairo_select_font_face (cr, font.family.c_str (), font.slant, font.weight);
		cairo_set_font_size (cr, font.size);

		double x0, y0;

		switch (font.align)
		{
			case BStyles::Font::TEXT_ALIGN_LEFT:	x0 = 0;
													break;

			case BStyles::Font::TEXT_ALIGN_CENTER:	x0 = w / 2 - (ext.width - 2 * ext0.width - 2 * ext0.x_bearing) / 2;
													break;

			case BStyles::Font::TEXT_ALIGN_RIGHT:	x0 = w - (ext.width - 2 * ext0.width - 2 * ext0.x_bearing);
													break;

			default:								x0 = 0;
		}

		switch (font.valign)
		{
			case BStyles::Font::TEXT_VALIGN_TOP:	y0 = - ext.y_bearing;
													break;

			case BStyles::Font::TEXT_VALIGN_MIDDLE:	y0 = h / 2 - ext.height / 2 - ext.y_bearing;
													break;

			case BStyles::Font::TEXT_VALIGN_BOTTOM:	y0 = h - ext.height - ext.y_bearing;
													break;

			default:								y0 = 0;
		}

		if (isValueable() && editMode_)
		{
			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
			std::u32string u32labelText = convert.from_bytes (text_);
			const size_t s32 = u32labelText.length ();
			size_t cf = std::min (cursorFrom_, s32);
			size_t ct = std::min (cursorTo_, s32);
			if (ct < cf) std::swap (ct, cf);

			const std::string s1 = convert.to_bytes (u32labelText.substr (0, cf));
			const std::string s2 = convert.to_bytes (u32labelText.substr (cf, ct - cf));
			const std::string s3 = convert.to_bytes (u32labelText.substr (ct, std::u32string::npos));

			const cairo_text_extents_t ext1 = font.getCairoTextExtents(cr, "|" + s1 + "|");
			const cairo_text_extents_t ext2 = font.getCairoTextExtents(cr, "|" + s2 + "|");

			double w1 = ext1.width - 2 * ext0.width - 2 * ext0.x_bearing;
			double w2 = ext2.width - 2 * ext0.width - 2 * ext0.x_bearing;

			const BStyles::Color lc = getTxColors () [getStatus()].illuminate(BStyles::Color::highLighted);
			cairo_set_source_rgba (cr, CAIRO_RGBA (lc));
			cairo_set_line_width (cr, 1.0);
			cairo_rectangle (cr, xoff + x0 + w1, yoff + y0, w2, -ext0.height);
			cairo_stroke_preserve (cr);
			cairo_fill (cr);

			cairo_set_source_rgba (cr, CAIRO_RGBA (lc));
			cairo_move_to (cr, xoff + x0, yoff + y0);
			cairo_show_text (cr, s1.c_str ());

			cairo_set_source_rgba (cr, 1 - lc.red, 1 - lc.green, 1 - lc.blue, lc.alpha);
			cairo_move_to (cr, xoff + x0 + w1, yoff + y0);
			cairo_show_text (cr, s2.c_str ());

			cairo_set_source_rgba (cr, CAIRO_RGBA (lc));
			cairo_move_to (cr, xoff + x0 + w1 + w2, yoff + y0);
			cairo_show_text (cr, s3.c_str ());
		}

		else
		{

			const BStyles::Color lc = getTxColors () [getStatus()];
			cairo_set_source_rgba (cr, CAIRO_RGBA (lc));
			cairo_move_to (cr, xoff + x0, yoff + y0);
			cairo_show_text (cr, text_.c_str ());
		}
	}

	cairo_destroy (cr);
}

}

#endif /* BWIDGETS_EDITLABEL_HPP_ */
