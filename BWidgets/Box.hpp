/* Box.hpp
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

#ifndef BWIDGETS_BOX_HPP_
#define BWIDGETS_BOX_HPP_

#include "Frame.hpp"
#include "Supports/ValueableTyped.hpp"
#include "TextButton.hpp"
#include "Supports/Closeable.hpp"
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <vector>

#define BWIDGETS_DEFAULT_BOX_WIDTH 200.0
#define BWIDGETS_DEFAULT_BOX_HEIGHT 60.0

#ifndef BWIDGETS_DEFAULT_MENU_PADDING
#define BWIDGETS_DEFAULT_MENU_PADDING 20.0
#endif

namespace BWidgets
{

/**
 *  @brief  Composite widget with buttons.
 *
 *  %Box is a composite Widget based on Frame and contains TextButtons. It 
 *  also supports Valueable and Closeable. The default value of the Box is 0
 *  and changes upon pressing one of the containing text buttons. On pressing
 *  one of the buttons, the widget value is set to the button index (starting)
 *  with 1 and a CloseRequestEvent is emitted.
 */
class Box : public Frame, public ValueableTyped<size_t>, public Closeable
{
protected:
	TextButton okButton_;
	std::vector<TextButton*> buttons_;

public:
	/**
	 *  @brief  Constructs an empty %Box object.
	 */
	Box ();

	/**
	 *  @brief  Construct a %Box object with default size.
	 *  @param buttonlabels  Initializer list with butten label strings.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  The box only hosts an OK button if no button labels are provided.
	 */
	Box (const std::initializer_list<std::string>& buttonlabels, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Construct a %Box object.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param buttonlabels  Initializer list with butten label strings.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  The box only hosts an OK button if no button labels are provided.
	 */
	Box (const double x, const double y, const double width, const double height,
		 const std::initializer_list<std::string>& buttons = {}, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	~Box ();

	/**
	 *  @brief  Creates a clone of the %Box. 
	 *  @return  Pointer to the new %Box.
	 *
	 *  Creates a clone of this %Box by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Box. 
	 *  @param that  Other %Box.
	 *
	 *  Copies all properties from another %Box. But NOT its linkage.
	 */
	void copy (const Box* that);

	/**
     *  @brief  Optimizes the %Box widget extends.
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
	virtual void resize (const BUtilities::Point extends) override;

	/**
	 *  @brief  Creates and adds a TextButton to the message box.
	 *  @param label  Label text string of the new button.
	 *
	 *  Buttons are added in the order left to right.
	 */
	void addButton (const std::string& label);

	/**
	 *  @brief  Creates and adds a series of TextButtons to the message box.
	 *  @param label  Initializer list with label text strings of the new 
	 *  buttons.
	 *
	 *  Buttons are added in the order left to right.
	 */
	void addButton (std::initializer_list<std::string> labels);

	/**
	 *  @brief  Removes and deletes a button.
	 *  @param label  Label text of the button to be removed.
	 *  
	 *  If there is more than one button with this label text, only the first
	 *  one will be removed and deleted. The internal OK button can only be
	 *  removed but not deleted. Removing may cause renumbering of the buttons.
	 */
	void removeButton (const std::string& label);

	/**
	 *  @brief  Removes and deletes a button.
	 *  @param index  Index of the button to be removed.
	 *  
	 *  The internal OK button can only be removed but not deleted. Removing
	 *  may cause renumbering of the buttons.
	 */
	void removeButton (const size_t index);

	/**
	 *  @brief  Gets the index of the button.
	 *  @param label  Label text string of the button.
	 *  @return  Number of the first button with the same label text string
	 *  as @a label. 
	 *
	 *  The index is the button number from left to right starting with 1. 0 is
	 *  returned, if there is no button with this label text.
	 */
	size_t getButtonIndex  (const std::string& label) const;

	/**
	 *  @brief Gets the text of a button.
	 *  @param index  Index of the button.
	 *  @return  Button label string.
	 *
	 *  The index is the button number from left to right starting with 1.
	 */
	std::string getButtonText (const size_t index) const;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;


protected:
	static void buttonClickCallback (BEvents::Event* event);
};

inline Box::Box () : Box (0.0, 0.0, 0.0, 0.0, {}, URID_UNKNOWN_URID, "") 
{

}

inline Box::Box (const std::initializer_list<std::string>& buttonlabels, uint32_t urid, std::string title) :
	Box (0, 0, BWIDGETS_DEFAULT_BOX_WIDTH, BWIDGETS_DEFAULT_BOX_HEIGHT, buttonlabels, urid, title) 
{

}

inline Box::Box	(const double x, const double y, const double width, const double height,
				 const std::initializer_list<std::string>& buttonlabels, uint32_t urid, std::string title) :
	Frame (x, y, width, height, urid, title),
	ValueableTyped<size_t> (0),
	Closeable(),
	okButton_ ("OK", false, false, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button")),
	buttons_()
{
	if (buttonlabels.begin() != buttonlabels.end()) addButton (buttonlabels);

	// Fallback default OK button
	if (buttons_.empty())
	{
		okButton_.setCallbackFunction (BEvents::Event::VALUE_CHANGED_EVENT, Box::buttonClickCallback);
		buttons_.push_back (&okButton_);
		add (&okButton_);
	}

	// Default decoration
	setBackground (BStyles::Fill(getBgColors()[BStyles::Status::STATUS_NORMAL].illuminate (-0.75)));
	setBorder (BStyles::Border  (BStyles::Line (getBgColors()[BStyles::Status::STATUS_NORMAL].illuminate (BStyles::Color::highLighted), 1.0), 0.0, 0.0));
}

inline Box::~Box ()
{
	while (!buttons_.empty ())
	{
		TextButton* b = buttons_.back ();
		if (b && (b != &okButton_)) delete b;
		else release (b);
		buttons_.pop_back ();
	}
}

inline Widget* Box::clone () const 
{
	Widget* f = new Box ();
	f->copy (this);
	return f;
}

inline void Box::copy (const Box* that)
{
	okButton_.copy (&that->okButton_);

	// Remove / delete buttons
	while (!buttons_.empty ())
	{
		TextButton* b = buttons_.back ();
		if (b && (b != &okButton_)) delete b;
		else release (b);
		buttons_.pop_back ();
	}

	// Copy buttons
	// Fallback default OK button
	if (that->buttons_.empty())
	{
		buttons_.push_back (&okButton_);
		add (&okButton_);
	}

	else 
	{
		for (const TextButton* t : that->buttons_)
		{
			if (t == &that->okButton_)
			{
				buttons_.push_back (&okButton_);
				add (&okButton_);
			}

			else addButton (t->label.getText());
		}
	}

	Closeable::operator= (*that);
	ValueableTyped<size_t>::operator= (*that);
    Frame::copy (that);
}

inline void Box::resize ()
{
	// Cleanup
	for (std::vector<TextButton*>::iterator it = buttons_.begin (); it != buttons_.end (); ++it)
	{
		TextButton* b = static_cast<TextButton*>(*it);
		if (!b) buttons_.erase (it);
	}

	const double nrbuttons = buttons_.size();
	if (!nrbuttons) return;

	// Calculate total width
	double totalbuttonwidth = 0.0;
	for (TextButton* b : buttons_)
	{
		if (b) totalbuttonwidth += b->getWidth ();
	}

	// Other content
	BUtilities::Point contExt = BUtilities::Point (getXOffset(), getYOffset());
	for (Linkable* l : children_)
	{
		Widget* w = dynamic_cast<Widget*>(l);
		if (!w) continue;

		if (std::find (buttons_.begin(), buttons_.end(), dynamic_cast<TextButton*> (w)) != buttons_.end()) continue;

		if (w->getPosition ().x + w->getWidth () > contExt.x) contExt.x = w->getPosition ().x + w->getWidth();
		if (w->getPosition ().y + w->getHeight () > contExt.y) contExt.y = w->getPosition ().y + w->getHeight();
	}

	// Add spaces and offset
	totalbuttonwidth += (nrbuttons + 1) * BWIDGETS_DEFAULT_MENU_PADDING;
	resize	(std::max (totalbuttonwidth + 2.0 * getXOffset(), contExt.x + 2.0 * BWIDGETS_DEFAULT_MENU_PADDING + getXOffset()) , 
			 contExt.y + 2.0 * BWIDGETS_DEFAULT_MENU_PADDING + BWIDGETS_DEFAULT_BUTTON_HEIGHT + getYOffset());
}

inline void Box::resize (const double width, const double height)
{
	resize (BUtilities::Point (width, height));
}

inline void Box::resize (const BUtilities::Point extends)
{
	Frame::resize (extends);
}

inline void Box::addButton (const std::string& label)
{
	TextButton* b = new TextButton (label, false, false, BUtilities::Urid::urid (BUtilities::Urid::uri (getUrid()) + "/button"));
	b->setCallbackFunction (BEvents::Event::BUTTON_CLICK_EVENT, Box::buttonClickCallback);
	buttons_.push_back (b);
	add (b);
}

inline void Box::addButton (std::initializer_list<std::string> labels)
{
	for (std::string label : labels) addButton (label);
}

inline void Box::removeButton  (const std::string& label)
{
	for (std::vector<TextButton*>::iterator it = buttons_.begin (); it != buttons_.end (); ++it)
	{
		TextButton* b = static_cast<TextButton*>(*it);
		if (b && (b->label.getText () == label))
		{
			if (b != &okButton_) delete b;
			buttons_.erase (it);
			update();
			return;
		}
	}
}

inline void Box::removeButton  (const size_t index)
{
	if (buttons_.size() >= index) return;

	std::vector<TextButton*>::iterator it = buttons_.begin() + index;
	TextButton* b = static_cast<TextButton*>(*it);
	if (b != &okButton_) delete b;
	buttons_.erase (it);
	update();
}

inline size_t Box::getButtonIndex  (const std::string& label) const
{
	for (size_t nr = 0; nr < buttons_.size(); ++nr)
	{
		const TextButton* b = buttons_[nr];
		if (b && (b->label.getText () == label)) return nr + 1;
	}

	return 0;
}

inline std::string Box::getButtonText (const size_t index) const
{
	if ((index < 1) || (index > buttons_.size ()) || (!buttons_[index - 1])) return "";
	return buttons_[index - 1]->label.getText ();
}

inline void Box::update ()
{
	// Update super widget first
	Frame::update ();

	// Cleanup
	for (std::vector<TextButton*>::iterator it = buttons_.begin (); it != buttons_.end (); ++it)
	{
		TextButton* b = static_cast<TextButton*>(*it);
		if (!b) buttons_.erase (it);
	}

	const double nrbuttons = buttons_.size();
	if (!nrbuttons) return;

	// Calculate total width
	double totalbuttonwidth = 0.0;
	for (TextButton* b : buttons_)
	{
		if (b) totalbuttonwidth += b->getWidth ();
	}

	// Calculate spaces and offset
	const double buttonspace = std::max ((getEffectiveWidth() - totalbuttonwidth) / (nrbuttons + 1.0), 1.0);
	double buttonxpos = getXOffset() +
	(
		totalbuttonwidth + (nrbuttons + 1) * buttonspace < getEffectiveWidth() ?
		buttonspace :
		getEffectiveWidth() / 2 - (totalbuttonwidth + (nrbuttons - 1) * buttonspace) / 2);

	// Rearrange
	for (TextButton* b : buttons_)
	{
		b->moveTo (buttonxpos, getYOffset() + getEffectiveHeight() - BWIDGETS_DEFAULT_MENU_PADDING - BWIDGETS_DEFAULT_BUTTON_HEIGHT);
		buttonxpos = buttonxpos + buttonspace + b->getWidth ();
	}
}

inline void Box::buttonClickCallback (BEvents::Event* event)
{
	if (event && (event->getEventType () == BEvents::Event::BUTTON_CLICK_EVENT))
	{
		BEvents::PointerEvent* ev = dynamic_cast<BEvents::PointerEvent*> (event);
		if (!ev) return;

		TextButton* w = dynamic_cast<TextButton*> (ev->getWidget ());
		if (!w) return;

		Box* p = dynamic_cast<Box*>(w->getParent ());
		if (!p) return;

		if (w && w->getParent ())
		{
			const std::string label = w->label.getText ();
			if (p->getMainWindow ())
			{
				const size_t v = p->getButtonIndex (label);

				// Emit value changed event and close (hide) message box
				if (v)
				{
					p->setValue (v);
					p->postCloseRequest ();
				}
			}
		}
	}
}

}

#endif /* BWIDGETS_BOX_HPP_ */
