/* SpinBox.hpp
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

#ifndef BWIDGETS_SPINBOX_HPP_
#define BWIDGETS_SPINBOX_HPP_

#include "SpinButton.hpp"
#include "Label.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/Scrollable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "Widget.hpp"
#include <cstddef>
#include <initializer_list>
#include <limits>

#ifndef BWIDGETS_DEFAULT_SPINBOX_WIDTH
#define BWIDGETS_DEFAULT_SPINBOX_WIDTH 80.0
#endif

#ifndef BWIDGETS_DEFAULT_SPINBOX_HEIGHT
#define BWIDGETS_DEFAULT_SPINBOX_HEIGHT 20.0
#endif

#ifndef BWIDGETS_DEFAULT_SPINBOX_ITEM_HEIGHT
#define BWIDGETS_DEFAULT_SPINBOX_ITEM_HEIGHT (BWIDGETS_DEFAULT_SPINBOX_HEIGHT - 2.0)
#endif

#ifndef BWIDGETS_DEFAULT_SPINBOX_BUTTON_WIDTH
#define BWIDGETS_DEFAULT_SPINBOX_BUTTON_WIDTH (0.5 * BWIDGETS_DEFAULT_SPINBOX_HEIGHT)
#endif

namespace BWidgets
{

/**
 *  @brief  Widget showing a content and a SpinButton. 
 *
 *  %SpinBox is a Valueable composite widget. It is a container widget. It has
 *  got a list of content widgets representing the items. And it has got a
 *  SpinButton to move between the items.
 *
 *  The value of the %SpinBox is the index of the active item starting with 1. 
 *  A value of 0 is used if no item is selected (default empty item).
 *
 *  The visualble content of the %SpinBox is represented by its background and
 *  its border and by styles of the embedded widgets.
 *
 *  @todo  Resize()
 *  @todo  Import item widgets.
 */
class SpinBox : public Widget, public ValueableTyped<size_t>, public Clickable, public Scrollable
{
protected:
	Widget* button_;
	std::list<Widget*> items_;
	size_t top_;
	double itemHeight_;
	double buttonWidth_;

public:

	/**
	 *  @brief  Constructs a new SpinBox object with default parameters.
	 */
	SpinBox ();

	/**
	 *  @brief  Constructs a new SpinBox object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	SpinBox (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %SpinBox with default size.
	 *  @param items  Initializer list of item strings.
	 *  @param value  Optional, list index of the selected item starting with
	 *  1 (default = 0 = unselected).
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SpinBox	(const std::initializer_list<const std::string> items, size_t value = 0, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %SpinBox.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param items  Optional, initializer list of item strings.
	 *  @param value  Optional, list index of the selected item starting with
	 *  1 (default = 0 = unselected).
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	SpinBox	(const double x, const double y, const double width, const double height, 
			 std::initializer_list<const std::string> items = {}, size_t value = 0,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	~SpinBox();

	/**
	 *  @brief  Creates a clone of the %SpinBox. 
	 *  @return  Pointer to the new %SpinBox.
	 *
	 *  Creates a clone of this %SpinBox by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %SpinBox. 
	 *  @param that  Other %SpinBox.
	 *
	 *  Copies all properties from another %SpinBox. But NOT its linkage.
	 */
	void copy (const SpinBox* that);

	/**
     *  @brief  Changes the value.
     *  @param value  Value.
     */
    virtual void setValue (const size_t& value) override;

	/**
     *  @brief  Changes the value if the item text is part of the items.
     *  @param item  Item text.
     */
    virtual void setValue (const std::string& value);

	/**
	 *  @brief  Adds an item to the %SpinBox. 
	 *  @param item  Item text string.
	 *  @param pos  Optional, index of the position fo the item to be inserted
	 *  before (pos >= 1).
	 *  
	 *  Also increases the widget value if the insertion takes place in front 
	 *  of the currently selected item.
	 */
	void addItem (const std::string item, size_t pos = std::numeric_limits<size_t>::max());

	/**
	 *  @brief  Adds an item to the %SpinBox. 
	 *  @param items  Initializer list of item strings.
	 *  @param pos  Optional, index of the position for the item to be inserted
	 *  before (pos >= 1).
	 *
	 *  Also increases the widget value if the insertion takes place in front 
	 *  of the currently selected item.
	 */
	void addItem (const std::initializer_list<const std::string> items, size_t pos = std::numeric_limits<size_t>::max());

	/**
	 *  @brief  Deletes an item.
	 *  @param pos  Index of the item to delete (pos >= 1).
	 *
	 *  Also decreases the widget value if the deletion takes place in front 
	 *  of the currently selected item.
	 */
	void deleteItem (const size_t pos);

	/**
	 *  @brief  Deletes all items (except the Null item).
	 *
	 *  Also sets the widget value to 0.
	 */
	void deleteItem ();

	/**
	 *  @brief   Access to an item of the %SpinBox
	 *  @param pos  Index of the item.
	 *  @return  Pointer to the widget.
	 */
	Widget* getItem (const size_t pos) const;

	/**
	 *  @brief   Access to an item of the %SpinBox
	 *  @param item  Item text string.
	 *  @return  Pointer to the widget.
	 */
	Widget* getItem (const std::string& item) const;

	/**
	 *  @brief  Sets the width of the button.
	 *  @param width  Button width.
	 */
	void setButtonWidth (const double width);

	/**
	 *  @brief  Gets the width of the button.
	 *  @return  Button width.
	 */
	double getButtonWidth () const;

	/**
	 *  @brief  Sets the height of each item to be added.
	 *  @param height  Item height.
	 *
	 *  The change of the item height only takes effect for items added after
	 *  the call of @c setItemHeight() of after call @c resizeItems() . 
	 */
	void setItemHeight (const double height);

	/**
	 *  @brief  Gets the height of each item to be added.
	 *  @param height  Item height.
	 */
	double getItemHeight () const;

	/**
	 *  @brief  Resizes all items to the same size.
	 * 
	 *  The size is defined by the widgets effective width, the button width,
	 *  and the item height.
	 */
	void resizeItems();

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. Increases or decreases the value and calls the
	 *  widget static callback function.
     */
    virtual void onWheelScrolled (BEvents::Event* event) override;

protected:

	/**
	 *  @brief  Callback function which handles and forwards 
	 *  VALUE_CHANGED_EVENTs from the SpinButton.
	 *  @param event  Event of the type ValueChangedEvent .
	 */
	static void valueChangedCallback (BEvents::Event* event);
};

inline SpinBox::SpinBox () : SpinBox (0.0, 0.0, BWIDGETS_DEFAULT_SPINBOX_WIDTH, BWIDGETS_DEFAULT_SPINBOX_HEIGHT, {}, 0, BUTILITIES_URID_UNKNOWN_URID, "") {}

inline SpinBox::SpinBox	(const uint32_t urid, const std::string& title) :
	SpinBox (0.0, 0.0, BWIDGETS_DEFAULT_SPINBOX_WIDTH, BWIDGETS_DEFAULT_SPINBOX_HEIGHT, {}, 0, urid, title) {}

inline SpinBox::SpinBox	(const std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	SpinBox (0.0, 0.0, BWIDGETS_DEFAULT_SPINBOX_WIDTH, BWIDGETS_DEFAULT_SPINBOX_HEIGHT, items, value, urid, title) {}

inline SpinBox::SpinBox	(const double x, const double y, const double width, const double height, 
			 	 		 std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<size_t> (value),
	Clickable(),
	Scrollable(),
	button_ (new SpinButton (x + width - height, y, height, height, 0, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"))),
	items_ ({new Label (0, 0, getWidth() - getHeight(), getHeight(), "")}),	// Init with Null item
	top_ (0),
	itemHeight_ (std::max (height - 2.0, 0.0)),
	buttonWidth_ (BWIDGETS_DEFAULT_SPINBOX_BUTTON_WIDTH)
{
	items_.front()->setEventPassable(BEvents::Event::WHEEL_SCROLL_EVENT + BEvents::Event::BUTTON_PRESS_EVENT);
	add (items_.front());
	addItem (items);
	if (getValue() >= items_.size()) setValue (0);
	else setValue (value_);
	top_ = value_;
	button_->setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, valueChangedCallback);
	add (button_);
	setBackground(BStyles::blackFill);
	setBorder (BStyles::Border (BStyles::Line (getBgColors()[BStyles::Status::STATUS_NORMAL], 1.0), 0.0, 0.0, 0.0));
}

inline SpinBox::~SpinBox()
{
	deleteItem();

	// Also delete Null item
	while (!items_.empty())
	{
		std::list<Widget*>::iterator it = items_.begin();
		Widget* w = *it;
		items_.erase (it);
		delete w;
	}

	if (button_) delete button_;	
}

inline Widget* SpinBox::clone () const 
{
	Widget* f = new SpinBox (urid_, title_);
	f->copy (this);
	return f;
}

inline void SpinBox::copy (const SpinBox* that)
{
	if (button_) delete button_;
	button_ = that->button_->clone();
	add (button_);

	deleteItem();
	for (Widget* w : that->items_)
	{
		Widget* w2 = w->clone();
		items_.push_back (w2);
		add (w2);
	}

	top_ = that->top_;
	itemHeight_ = that->itemHeight_;
	buttonWidth_ = that->buttonWidth_;

	Scrollable::operator= (*that);
	Clickable::operator= (*that);
	ValueableTyped<size_t>::operator= (*that);
    Widget::copy (that);
}

inline void SpinBox::setValue (const size_t& value)
{
	ValueableTyped<size_t>::setValue (value < items_.size() ? value : (items_.empty() ? 0 : items_.size() - 1));
}

inline void SpinBox::setValue (const std::string& item)
{
	size_t pos = 0;
	for (Widget* w : items_)
	{
		Label* l = dynamic_cast<Label*>(w);
		if (l && l->getText() == item) break;
		++pos;
	}

	if (pos < items_.size()) setValue (pos);
}

inline void SpinBox::addItem (const std::string item, size_t pos)
{
	Label* l = new Label (0, 0, getEffectiveWidth() - buttonWidth_, itemHeight_, item);
	if (pos >= items_.size()) items_.push_back (l);
	else if (pos <= 1) items_.insert(std::next (items_.begin(), 1), l);
	else items_.insert(std::next (items_.begin(), pos), l);
	l->setBorder(BStyles::Border (BStyles::noLine, 3.0));
	l->setEventPassable(BEvents::Event::WHEEL_SCROLL_EVENT + BEvents::Event::BUTTON_PRESS_EVENT);
	add (l);
	if (getValue() >= pos) setValue (getValue() + 1);
	if (top_ >= pos) ++top_;
}

inline void SpinBox::addItem (const std::initializer_list<const std::string> items, size_t pos)
{
	for (const std::string s : items)
	{
		addItem (s, pos);
		if (pos != std::numeric_limits<size_t>::max()) ++pos;
	}
}

inline void SpinBox::deleteItem (const size_t pos)
{
	if ((pos > 0) && (pos < items_.size()))
	{
		std::list<Widget*>::iterator it = std::next (items_.begin(), pos);
		Widget* w = *it;
		items_.erase (it);
		delete w;
	}

	if (top_ == pos) top_ = 0;
	else if (top_ > pos) --top_;
	if (getValue() == pos) setValue (0);
	else if (getValue() > pos) setValue (getValue() - 1);
}

inline void SpinBox::deleteItem ()
{
	while (!items_.empty())
	{
		std::list<Widget*>::iterator it = std::next (items_.begin(), 1);
		if (it == items_.end()) break;		// Don't delete Null item
		Widget* w = *it;
		items_.erase (it);
		delete w;
	}

	top_ = 0;
	setValue (0);
}

inline Widget* SpinBox::getItem (const size_t pos) const
{
	if (pos >= items_.size()) return nullptr;
	return *std::next(items_.begin(), pos);
}

inline Widget* SpinBox::getItem (const std::string& item) const
{
	for (std::list<Widget*>::const_iterator it = items_.begin(); it != items_.end(); ++it)
	{
		Label* l = dynamic_cast<Label*>(*it);
		if (l && (l->getText() == item)) return *it;
	}
	
	return nullptr;
}

inline void SpinBox::setButtonWidth (const double width)
{
	if (buttonWidth_ != width)
	{
		buttonWidth_ = width;
		update();
	}
}

inline double SpinBox::getButtonWidth () const
{

	return buttonWidth_;
}

inline void SpinBox::setItemHeight (const double height)
{
	if (itemHeight_ != height)
	{
		itemHeight_ = height;
		update();
	}
}

inline double SpinBox::getItemHeight () const
{
	return itemHeight_;
}

inline void SpinBox::resizeItems ()
{
	for (Widget* w : items_) w->resize (getEffectiveWidth() - buttonWidth_, itemHeight_);
	update();
}

inline void SpinBox::update ()
{
	size_t count = 0;
	for (Widget* w : items_)
	{
		if (w)
		{
			if (getValue() == count) w->show();
			else w->hide();
			w->moveTo (getXOffset(), getYOffset());
			w->resize (getEffectiveWidth() - buttonWidth_, getEffectiveHeight());
		}
		++count;
	}
	button_->moveTo (getEffectiveWidth() + getXOffset() - buttonWidth_, getYOffset());
	button_->resize (buttonWidth_, getEffectiveHeight());
	Widget::update();
}

inline void SpinBox::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*>(event);
	if (!wev) return;
	if (wev->getWidget() != this) return;

	if	(((getValue() > 1) || (wev->getDelta().y > 0)) &&
		 ((getValue() + 1 < items_.size()) || (wev->getDelta().y < 0)))
	{
		setValue (getValue() + (wev->getDelta().y < 0 ? -1 : (wev->getDelta().y > 0 ? 1 : 0)));
	}

	Scrollable::onWheelScrolled(event);
}

inline void SpinBox::valueChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<int>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<int>*>(event);
	if (!vev) return;
	SpinButton* w = dynamic_cast<SpinButton*>(vev->getWidget());
	if (!w) return;
	SpinBox* p = dynamic_cast<SpinBox*>(w->getParentWidget());
	if (!p) return;

	if	((w == p->button_) &&
		 ((p->getValue() > 1) || (w->getValue() > 0)) &&
		 ((p->getValue() + 1 < p->items_.size()) || (w->getValue() < 0)))
	{
		p->setValue (p->getValue() + w->getValue());
	}
}

}

#endif /* BWIDGETS_SPINBOX_HPP_ */
