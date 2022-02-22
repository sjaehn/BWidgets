/* ComboBox.hpp
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

#ifndef BWIDGETS_COMBOBOX_HPP_
#define BWIDGETS_COMBOBOX_HPP_

#include "SpinBox.hpp"
#include "ListBox.hpp"
#include "Symbol.hpp"
#include "SymbolButton.hpp"
#include "Widget.hpp"
#include <cstddef>

#ifndef BWIDGETS_DEFAULT_COMBOBOX_WIDTH
#define BWIDGETS_DEFAULT_COMBOBOX_WIDTH BWIDGETS_DEFAULT_SPINBOX_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_COMBOBOX_HEIGHT
#define BWIDGETS_DEFAULT_COMBOBOX_HEIGHT BWIDGETS_DEFAULT_SPINBOX_HEIGHT
#endif

#ifndef BWIDGETS_DEFAULT_COMBOBOX_LISTBOX_HEIGHT
#define BWIDGETS_DEFAULT_COMBOBOX_LISTBOX_HEIGHT BWIDGETS_DEFAULT_LISTBOX_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  Widget showing a combo box. 
 *
 *  %ComboBox is Valueable widget derived from SpinBox. It shows a SpinBox
 *  with a single button. It opens a ListBox with the same content upon
 *  clicking on the button.
 *
 *  @todo  Resize()
 *  @todo  Import item widgets.
 */
class ComboBox : public SpinBox
{

protected:
	Widget* listBox_;
	BUtilities::Area<> listBoxArea_;

public:

	/**
	 *  @brief  Constructs a new ComboBox object with default parameters.
	 */
	ComboBox ();

	/**
	 *  @brief  Constructs a new ComboBox object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ComboBox (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ComboBox with default size.
	 *  @param items  Initializer list of item strings.
	 *  @param value  Optional, list index of the selected item starting with
	 *  1 (default = 0 = unselected).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ComboBox	(const std::initializer_list<const std::string> items, size_t value = 0, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ComboBox with default ListBox size.
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
	ComboBox	(const double x, const double y, const double width, const double height,
				 std::initializer_list<const std::string> items = {}, size_t value = 0,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ComboBox.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param listBoxX  ListBox X origin relative to the SpinBox origin.
	 *  @param listBoxY  ListBox Y origin relative to the SpinBox origin.
	 *  @param listBoxWidth  ListBox width.
	 *  @param listBoxHeight  ListBox height.
	 *  @param items  Optional, initializer list of item strings.
	 *  @param value  Optional, list index of the selected item starting with
	 *  1 (default = 0 = unselected).
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ComboBox	(const double x, const double y, const double width, const double height,
				 const double listBoxX, const double listBoxY, const double listBoxWidth, const double listBoxHeight,
				 std::initializer_list<const std::string> items = {}, size_t value = 0,
				 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	virtual ~ComboBox();

	/**
	 *  @brief  Creates a clone of the %ComboBox. 
	 *  @return  Pointer to the new %ComboBox.
	 *
	 *  Creates a clone of this %ComboBox by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ComboBox. 
	 *  @param that  Other %ComboBox.
	 *
	 *  Copies all properties from another %ComboBox. But NOT its linkage.
	 */
	void copy (const ComboBox* that);

	/**
     *  @brief  Changes the value.
     *  @param value  Value.
     *
     *  Also closes the ListBox andemits a ValueChangeTyped<size_t> event.
     */
    virtual void setValue (const size_t& value) override;

	/**
     *  @brief  Changes the value if the item text is part of the items.
     *  @param item  Item text.
     */
    virtual void setValue (const std::string& value) override;

	/**
	 *  @brief  Changes the position of the ListBox.
	 *  @param position  New position.
	 */
	void moveListBox (const BUtilities::Point<> position);

	/**
	 *  @brief  Changes the position of the ListBox.
	 *  @param x  New x coordinate.
	 *  @param y  New y coordinate.
	 */
	void moveListBox (const double x, const double y);

	/**
	 *  @brief  Gets the ListBox position.
	 *  @return  ListBox position. 
	 */
	BUtilities::Point<> getListBoxPosition () const;

	/**
	 *  @brief  Changes the extends of the ListBox.
	 *  @param extends  New extends.
	 */
	void resizeListBox (const BUtilities::Point<> extends);

	/**
	 *  @brief  Changes the extends of the ListBox.
	 *  @param width  New ListBox width.
	 *  @param height  New ListBox height.
	 */
	void resizeListBox (const double width, const double height);

	/**
	 *  @brief  Gets the ListBox extends.
	 *  @return  ListBox extends. 
	 */
	BUtilities::Point<> getListBoxExtends () const;

protected:

	/**
	 *  @brief  Callback function which handles and forwards 
	 *  VALUE_CHANGED_EVENTs from the button.
	 *  @param event  Event of the type ValueChangedEvent .
	 */
	static void buttonChangedCallback (BEvents::Event* event);

	/**
	 *  @brief  Callback function which handles and forwards 
	 *  VALUE_CHANGED_EVENTs from the listBox.
	 *  @param event  Event of the type ValueChangedEvent .
	 */
	static void listBoxChangedCallback (BEvents::Event* event);
};

inline ComboBox::ComboBox () : 
	ComboBox	(0.0, 0.0, BWIDGETS_DEFAULT_COMBOBOX_WIDTH, BWIDGETS_DEFAULT_COMBOBOX_HEIGHT, 
				 0.0, BWIDGETS_DEFAULT_COMBOBOX_HEIGHT, BWIDGETS_DEFAULT_COMBOBOX_WIDTH, BWIDGETS_DEFAULT_COMBOBOX_LISTBOX_HEIGHT, 
				 {}, 0, URID_UNKNOWN_URID, "") {}

inline ComboBox::ComboBox	(const uint32_t urid, const std::string& title) :
	ComboBox	(0.0, 0.0, BWIDGETS_DEFAULT_COMBOBOX_WIDTH, BWIDGETS_DEFAULT_COMBOBOX_HEIGHT, 
				 0.0, BWIDGETS_DEFAULT_COMBOBOX_HEIGHT, BWIDGETS_DEFAULT_COMBOBOX_WIDTH, BWIDGETS_DEFAULT_COMBOBOX_LISTBOX_HEIGHT,
				 {}, 0, urid, title) {}

inline ComboBox::ComboBox	(const std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	ComboBox	(0.0, 0.0, BWIDGETS_DEFAULT_COMBOBOX_WIDTH, BWIDGETS_DEFAULT_COMBOBOX_HEIGHT, 
				 0.0, BWIDGETS_DEFAULT_COMBOBOX_HEIGHT, BWIDGETS_DEFAULT_COMBOBOX_WIDTH, BWIDGETS_DEFAULT_COMBOBOX_LISTBOX_HEIGHT,
				 items, value, urid, title) {}

inline ComboBox::ComboBox	(const double x, const double y, const double width, const double height, 
			 	 			 std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	ComboBox	(x, y, width, height, 
				 0.0, height, width, BWIDGETS_DEFAULT_COMBOBOX_LISTBOX_HEIGHT,
				 items, value, urid, title) {}


inline ComboBox::ComboBox	(const double x, const double y, const double width, const double height,
							 const double listBoxX, const double listBoxY, const double listBoxWidth, const double listBoxHeight,
			 	 			 std::initializer_list<const std::string> items, size_t value, uint32_t urid, std::string title) :
	SpinBox (x, y, width, height, items, value, urid, title),
	listBox_ (nullptr),
	listBoxArea_(listBoxX, listBoxY, listBoxWidth, listBoxHeight)
{
	if (button_) delete button_;
	button_ = new SymbolButton	(x + width - buttonWidth_, y, buttonWidth_, height, Symbol::DOWN_SYMBOL, false, false,
								 BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/button"), "");
	button_->setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, ComboBox::buttonChangedCallback);
	add (button_);
	for (Widget* w : items_) w->setHeight (itemHeight_);
}

inline ComboBox::~ComboBox()
{
	if (listBox_) delete listBox_;
}

inline Widget* ComboBox::clone () const 
{
	Widget* f = new ComboBox (urid_, title_);
	f->copy (this);
	return f;
}

inline void ComboBox::copy (const ComboBox* that)
{
	if (listBox_) delete listBox_;
	listBox_ = that->listBox_->clone();
	if (listBox_) add (listBox_);

	listBoxArea_ = that->listBoxArea_;

	SpinBox::copy (that);
}

inline void ComboBox::setValue (const size_t& value)
{
	if (value == getValue()) return;

	if (listBox_)  
	{
		delete listBox_;
		listBox_ = nullptr;
	}

	SpinBox::setValue (value);
}

inline void ComboBox::setValue (const std::string& item)
{
	SpinBox::setValue (item);
}

inline void ComboBox::moveListBox (const BUtilities::Point<> position)
{
	listBoxArea_.moveTo (position);
	if (listBox_) listBox_->moveTo (position);
}

inline void ComboBox::moveListBox (const double x, const double y)
{
	moveListBox (BUtilities::Point<> (x, y));
}

inline BUtilities::Point<> ComboBox::getListBoxPosition () const
{
	return listBoxArea_.getPosition();
}


inline void ComboBox::resizeListBox (const BUtilities::Point<> extends)
{
	listBoxArea_.resize (extends);
	if (listBox_) listBox_->resize (extends);
}

inline void ComboBox::resizeListBox (const double width, const double height)
{
	resizeListBox (BUtilities::Point<> (width, height));
}

inline BUtilities::Point<> ComboBox::getListBoxExtends () const
{
	return listBoxArea_.getExtends();
}

inline void ComboBox::buttonChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<bool>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<bool>*>(event);
	if (!vev) return;
	SymbolButton* w = dynamic_cast<SymbolButton*>(vev->getWidget());
	if (!w) return;
	ComboBox* p = dynamic_cast<ComboBox*>(w->getParentWidget());
	if (!p) return;
	if (!vev->getValue()) return;
	if	(w != p->button_) return;

	if (p->listBox_)
	{
		delete p->listBox_;
		p->listBox_ = nullptr;
	}

	else 
	{
		p->listBox_ = new ListBox	(p->listBoxArea_.getX(), p->listBoxArea_.getY(), p->listBoxArea_.getWidth(), p->listBoxArea_.getHeight(), 
									 {}, 0, BUtilities::Urid::urid (BUtilities::Urid::uri (p->getUrid()) + "/listbox"), "");

		ListBox* l = dynamic_cast<ListBox*>(p->listBox_);
		if (l)
		{
			if (!p->items_.empty())
			{
				for (std::list<Widget*>::iterator it = std::next (p->items_.begin()); it != p->items_.end(); ++it)
				{
					Label* wl = dynamic_cast<Label*>(*it);
					if (wl)
					{
						l->addItem (wl->getText());
					}
				}
			}
			l->setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, ComboBox::listBoxChangedCallback);
			l->setStacking (STACKING_ESCAPE);
			l->setValue (p->getValue());
			p->raiseToFront();
			p->add (l);
		}
	}
}

inline void ComboBox::listBoxChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<size_t>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<size_t>*>(event);
	if (!vev) return;
	ListBox* w = dynamic_cast<ListBox*>(vev->getWidget());
	if (!w) return;
	ComboBox* p = dynamic_cast<ComboBox*>(w->getParentWidget());
	if (!p) return;
	if (w != p->listBox_) return;

	p->setValue (w->getValue());
	// No furter calls of w or p->listBox_ from here as setValue may delete the listBox_! 
}


}

#endif /* BWIDGETS_COMBOBOX_HPP_ */
