/* ListBox.hpp
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

#ifndef BWIDGETS_LISTBOX_HPP_
#define BWIDGETS_LISTBOX_HPP_

#include "SpinBox.hpp"
#include "Supports/Clickable.hpp"
#include "../BEvents/PointerEvent.hpp"
#include "VScrollBar.hpp"
#include "Widget.hpp"
#include <iterator>

#ifndef BWIDGETS_DEFAULT_LISTBOX_WIDTH
#define BWIDGETS_DEFAULT_LISTBOX_WIDTH 80.0
#endif

#ifndef BWIDGETS_DEFAULT_LISTBOX_HEIGHT
#define BWIDGETS_DEFAULT_LISTBOX_HEIGHT 200.0
#endif

namespace BWidgets
{

/**
 *  @brief  Widget showing a scrollable list content and allows to select an
 *  item. 
 *
 *  %ListBox is Valueable widget derived from SpinBox. In contrast to SpinBox,
 *  it shows its content in multiple lines and allow selection by clicking on
 *  an item by the support of Clickable. The selected item is turned in its
 *  active state.
 *
 *  @todo  Resize()
 *  @todo  Import item widgets.
 */
class ListBox : public SpinBox
{
public:

	/**
	 *  @brief  Constructs a new ListBox object with default parameters.
	 */
	ListBox ();

	/**
	 *  @brief  Constructs a new ListBox object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ListBox (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ListBox with default size.
	 *  @param items  Initializer list of item strings.
	 *  @param value  Optional, list index of the selected item starting with
	 *  1 (default = 0 = unselected).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ListBox	(const std::initializer_list<const std::string> items, size_t value = 0, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ListBox.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param items  Optional, initializer list of item strings.
	 *  @param value  Optional, list index of the selected item starting with
	 *  1 (default = 0 = unselected).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ListBox	(const double x, const double y, const double width, const double height,
			 std::initializer_list<const std::string> items = {}, size_t value = 0,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ListBox. 
	 *  @return  Pointer to the new %ListBox.
	 *
	 *  Creates a clone of this %ListBox by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ListBox. 
	 *  @param that  Other %ListBox.
	 *
	 *  Copies all properties from another %ListBox. But NOT its linkage.
	 */
	void copy (const ListBox* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
	 *  @brief  Scrolls the list and sets the visualized list top index.
	 *  @param pos  Index of the item to be on list top position.
	 */
	virtual void setTop (const size_t pos);

	/**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. Selects an item, sets the widget value and 
	 *  calls the static callback function.
     */
    virtual void onButtonPressed (BEvents::Event* event) override;

	/**
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. Scrolls the list and calls the
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

inline ListBox::ListBox () : ListBox (0.0, 0.0, BWIDGETS_DEFAULT_LISTBOX_WIDTH, BWIDGETS_DEFAULT_LISTBOX_HEIGHT, {}, 0, URID_UNKNOWN_URID, "") {}

inline ListBox::ListBox	(const uint32_t urid, const std::string& title) :
	ListBox (0.0, 0.0, BWIDGETS_DEFAULT_LISTBOX_WIDTH, BWIDGETS_DEFAULT_LISTBOX_HEIGHT, {}, 0, urid, title) {}

inline ListBox::ListBox	(const std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	ListBox (0.0, 0.0, BWIDGETS_DEFAULT_LISTBOX_WIDTH, BWIDGETS_DEFAULT_LISTBOX_HEIGHT, items, value, urid, title) {}

inline ListBox::ListBox	(const double x, const double y, const double width, const double height, 
			 	 		 std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	SpinBox (x, y, width, height, items, value, urid, title)
{
	buttonWidth_ = 0.5 * BWIDGETS_DEFAULT_SPINBOX_BUTTON_WIDTH;
	if (button_) delete button_;
	button_ = new VScrollBar	(x + width - buttonWidth_, y, buttonWidth_, height, 
								 0.3, 0.0, 1.0, 0.0, 0.0,
								 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer,
								 BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"));
	button_->setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, ListBox::valueChangedCallback);
	add (button_);
	itemHeight_ = BWIDGETS_DEFAULT_SPINBOX_ITEM_HEIGHT;
	for (Widget* w : items_) w->setHeight (itemHeight_);
}

inline Widget* ListBox::clone () const 
{
	Widget* f = new ListBox (urid_, title_);
	f->copy (this);
	return f;
}

inline void ListBox::copy (const ListBox* that)
{
	SpinBox::copy (that);
}

inline void ListBox::setTop (const size_t pos)
{
	if (pos != top_)
	{
		top_ = pos;
		update();
	}
}

inline void ListBox::update ()
{
	size_t count = 0;
	double tHeight = 0.0;
	double lHeight = 0.0;
	for (std::list<Widget*>::iterator it = items_.begin(); it != items_.end(); ++it)
	{
		Widget* w = *it;
		if (w)
		{
			// Items before top_
			// Set negative y positions
			if ((count == top_) && (it != items_.begin()))
			{
				double mtHeight = 0.0;
				for (std::list<Widget*>::iterator it2 = std::prev (it); /* empty */; --it2)
				{
					Widget* w2 = *it2;
					mtHeight -= w2->getHeight();
					w2->moveTo (getXOffset(), getYOffset() + mtHeight);
					w2->setWidth(getEffectiveWidth() - buttonWidth_);
					if (it2 == items_.begin()) break;
				}
			}

			// Items from top_ to the end of the ListBox area
			if (count >= top_)
			{
				w->moveTo (getXOffset(), getYOffset() + tHeight);
				w->setWidth(getEffectiveWidth() - buttonWidth_);
				if (tHeight < getEffectiveHeight()) 
				{
					w->show();
					lHeight = w->getPosition().y + w->getHeight();
				}
				else w->hide();
				tHeight += w->getHeight();
			}

			// Items outside the ListBox area
			else w->hide();

			if (getValue() == count) 
			{
				w->setStatus (BStyles::STATUS_ACTIVE);
				w->setBackground (BStyles::Fill (getBgColors()[BStyles::STATUS_NORMAL].illuminate (BStyles::Color::darkened)));
			}
			else 
			{
				w->setStatus (BStyles::STATUS_NORMAL);
				w->setBackground (BStyles::noFill);
			}
		}
		++count;
	}

	button_->moveTo (getEffectiveWidth() + getXOffset() - buttonWidth_, getYOffset());
	button_->resize (buttonWidth_, getEffectiveHeight());
	
	const double y0 = items_.front()->getPosition().y;
	const double ye = items_.back()->getPosition().y + items_.back()->getHeight();
	std::list<Widget*>::iterator it = std::next (items_.begin(), top_);
	const double y = (*it)->getPosition().y + 0.5 * (*it)->getHeight();
	VScrollBar* vs = dynamic_cast<VScrollBar*>(button_);
	if (vs && (ye > y0)) 
	{
		vs->setValue ((y - y0) / (ye - y0));
		vs->setValueSize ((lHeight - y) / (ye - y0));
	};

	Widget::update();
}

inline void ListBox::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;
	if (pev->getWidget() != this) return;

	size_t count = top_;
	for (std::list<Widget*>::iterator it = std::next(items_.begin(), top_); it != items_.end(); ++it)
	{
		Widget* w = *it;
		const double bottom = getYOffset() + w->getPosition().y + w->getHeight();

		if (pev->getPosition().y < bottom) 
		{
			setValue (count);
			break;
		}

		if (bottom > getYOffset() + getEffectiveHeight()) break;
		
		++count;
	}
}

inline void ListBox::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*>(event);
	if (!wev) return;
	if (wev->getWidget() != this) return;

	if	(((top_ > 1) || (wev->getDelta().y < 0)) &&
		 ((top_ + 1 < items_.size()) || (wev->getDelta().y > 0)))
	{
		setTop (top_ - (wev->getDelta().y < 0 ? -1 : (wev->getDelta().y > 0 ? 1 : 0)));
	}

	Scrollable::onWheelScrolled(event);
}

inline void ListBox::valueChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<double>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<double>*>(event);
	if (!vev) return;
	VScrollBar* w = dynamic_cast<VScrollBar*>(vev->getWidget());
	if (!w) return;
	ListBox* p = dynamic_cast<ListBox*>(w->getParentWidget());
	if (!p) return;

	if	(w == p->button_)
	{
		std::list<Widget*>::iterator bit = (p->items_.size() > 1 ? std::next (p->items_.begin()) : p->items_.begin());
		const double y0 = p->items_.front()->getPosition().y;
		const double ye = p->items_.back()->getPosition().y + p->items_.back()->getHeight();
		if (y0 < ye)
		{
			const double y = y0 + w->getValue() * (ye - y0);
			size_t count = (p->items_.size() > 1 ? 1 : 0);
			for (std::list<Widget*>::iterator it = bit; it != p->items_.end(); ++it)
			{
				Widget* w2 = (*it);
				if (y <= w2->getPosition().y + w2->getHeight())
				{
					w->setValueable (false);
					p->setTop (count);
					w->setValueable (true);
					break;
				} 
				++count;
			}
		}
	}
}


}

#endif /* BWIDGETS_LISTBOX_HPP_ */
