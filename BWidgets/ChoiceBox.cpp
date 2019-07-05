/* ChoiceBox.cpp
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

#include "ChoiceBox.hpp"

namespace BWidgets
{
ChoiceBox::ChoiceBox () : ChoiceBox (0.0, 0.0, 0.0, 0.0, "choicebox") {}

ChoiceBox::ChoiceBox (const double x, const double y, const double width,
		      const double height, const std::string& name) :
	ValueWidget (x, y, width, height, name, UNSELECTED),
	upButton (0, 0, 0, 0, name + BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_NAME, 0.0),
	downButton (0, 0, 0, 0, name + BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_NAME, 0.0),
	items ({}), labels ({}),
	activeNr (0)
{
	background_ = BWIDGETS_DEFAULT_MENU_BACKGROUND;
	border_ = BWIDGETS_DEFAULT_MENU_BORDER;

	upButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ChoiceBox::handleButtonClicked);
	downButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ChoiceBox::handleButtonClicked);

	add (upButton);
	add (downButton);

	setScrollable (true);
}


ChoiceBox::ChoiceBox (const double x, const double y, const double width, const double height,
		      const std::string& name, const std::vector<std::string>& strings, double preselection) :
	ChoiceBox (x, y, width, height, name)
{
	// Generate labels and items from strings
	addText (strings);

	// Set value and preselection
	value = preselection;
	if ((preselection >= 1.0) && (preselection <= strings.size ())) activeNr = preselection;
}

ChoiceBox::ChoiceBox (const double x, const double y, const double width, const double height,
	   	      const std::string& name, const std::vector<stringItem>& strItems, double preselection) :
	ChoiceBox (x, y, width, height, name)
{
	addText (strItems);

	// Set value and preselection
	value = preselection;

	for (uint i = 0; i < items.size (); ++ i)
	{
		if (preselection == items[i].value)
		{
			activeNr = i + 1;
			break;
		}
	}
}

ChoiceBox::ChoiceBox (const double x, const double y, const double width, const double height,
		      const std::string& name, const std::vector<Item>& items, double preselection) :
	ChoiceBox (x, y, width, height, name)

{
	addItem (items);

	// Set value and preselection
	value = preselection;

	for (uint i = 0; i < items.size (); ++ i)
	{
		if (preselection == items[i].value)
		{
			activeNr = i + 1;
			break;
		}
	}
}

ChoiceBox::ChoiceBox (const ChoiceBox& that) :
	ValueWidget (that), upButton (that.upButton), downButton (that.downButton),
	items ({}), labels ({}), activeNr (that.activeNr)
{
	copyLabelsAndItemsFrom (that);

	add (upButton);
	add (downButton);
}

ChoiceBox::~ChoiceBox ()
{
	deleteLabels ();
}

ChoiceBox& ChoiceBox::operator= (const ChoiceBox& that)
{
	deleteLabels ();
	copyLabelsAndItemsFrom (that);

	upButton = that.upButton;
	downButton = that.downButton;

	activeNr = that.activeNr;

	ValueWidget::operator= (that);
	return *this;
}

Widget* ChoiceBox::clone () const {return new ChoiceBox (*this);}

void ChoiceBox::copyLabelsAndItemsFrom (const ChoiceBox& that)
{
	// Copy construct labels
	for (uint i = 0; i < that.labels.size (); ++i)
	{
		Label* label;
		try {label = new Label (*that.labels[i]);}
		catch (std::bad_alloc& ba) {throw ba;}
		labels.push_back (label);
	}

	// Copy items
	for (uint i = 0; i < that.items.size (); ++i)
	{
		// Check if it is an internally used label
		size_t lNr = that.labels.size ();
		for (uint j = 0 ; j < that.labels.size (); ++j)
		{
			if (that.items[i].widget == that.labels[j])
			{
				lNr = j;
				break;
			}
		}

		// Internally used label: create new item with link to copied label
		if (lNr < that.labels.size ()) items.push_back ({that.items[i].value, labels[lNr]});

		// Otherwise simply copy item
		else items.push_back (that.items[i]);
	}
}

void ChoiceBox::deleteLabels ()
{
	while  (!labels.empty ())
	{
		Label* l = labels.back ();
		if (l) delete l;
		labels.pop_back ();
	}
}

std::vector<Item>* ChoiceBox::getItemList () {return &items;}

Item ChoiceBox::getItem (const double val) const
{
	for (Item i : items)
	{
		if (i.value == val) return i;
	}
	return Item {UNSELECTED, nullptr};
}

Item ChoiceBox::getActiveItem () const
{
	if ((activeNr >= 1) && (activeNr <= int (items.size ()))) return items[activeNr - 1];
	else return Item {UNSELECTED, nullptr};
}

void ChoiceBox::addItem (const Item newItem)
{
	items.push_back (newItem);
	if (newItem.widget)
	{
		newItem.widget->setClickable (true);
		newItem.widget->setCallbackFunction (BEvents::BUTTON_PRESS_EVENT, ChoiceBox::handleItemClicked);
		add (*newItem.widget);
	}
	if (isVisible ()) update ();
}

void ChoiceBox::addItem (const std::vector<Item>& newItems)
{
	for (Item ni : newItems) items.push_back (ni);
}

void ChoiceBox::addText (const std::string& text)
{
	// Find next value
	double val = 1.0;
	for (Item i : items)
	{
		if (floor (i.value) >= val) val = floor (i.value) + 1.0;
	}

	// Create new label widget
	try {addText (stringItem {val, text});}
	catch (std::bad_alloc& ba) {throw ba;}
}

void ChoiceBox::addText (const std::vector<std::string>& texts)
{
	for (std::string s : texts)
	{
		try {addText (s);}
		catch (std::bad_alloc& ba) {throw ba;}
	}
}

void ChoiceBox::addText (const stringItem& strItem)
{
	// Create new label widget
	Label* label;
	try {label = new Label (0, 0, 0, 0, name_ + BWIDGETS_DEFAULT_CHOICEBOX_ITEM_NAME, strItem.string);}
	catch (std::bad_alloc& ba) {throw ba;}
	labels.push_back (label);

	// Create item from new label and add to items
	addItem ({strItem.value, label});
}

void ChoiceBox::addText (const std::vector<stringItem>& strItems)
{
	for (stringItem s : strItems)
	{
		try {addText (s);}
		catch (std::bad_alloc& ba) {throw ba;}
	}
}

void ChoiceBox::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}

void ChoiceBox::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	Widget::applyTheme (theme, name);
	for (Item i : items)
	{
		if (i.widget) i.widget -> applyTheme (theme, name_ + BWIDGETS_DEFAULT_CHOICEBOX_ITEM_NAME);
	}
	upButton.applyTheme (theme, name + BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_NAME);
	downButton.applyTheme (theme, name + BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_NAME);
	update ();
}

void ChoiceBox::setValue (const double val)
{
	if (items.empty ())
	{
		ValueWidget::setValue (UNSELECTED);
		activeNr = 0;
	}

	else
	{
		for (uint i = 0; i < items.size(); ++i)
		{
			if (val == items[i].value)
			{
				ValueWidget::setValue (val);
				activeNr = i + 1;
				return;
			}
		}
	}
}

int ChoiceBox::getTop () const {return activeNr;}

int ChoiceBox::getActive () const {return activeNr;}

int ChoiceBox::getBottom () {return (getTop () + getLines () - 1);}

int ChoiceBox::getLines () {return 1.0;}

void ChoiceBox::update ()
{
	// Update super widget first
	Widget::update ();

	// Validate value and update activeNr
	setValue (getValue ());

	// Update items
	updateItems ();

	// Set position of buttons and item label
	double x0 = getXOffset ();
	double y0 = getYOffset ();
	double width = getEffectiveWidth ();
	double height = getEffectiveHeight ();

	if (getTop () > 1.0) upButton.show ();
	else upButton.hide ();
	double upButtonHeight = (height >= BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
				 BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT : height);
	upButton.moveTo (x0, y0);
	upButton.setWidth (width);
	upButton.setHeight (upButtonHeight);

	if (height > BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT)
	{
		if (getBottom () < int (items.size ())) downButton.show ();
		else downButton.hide ();
		double downButtonHeight = (height >= 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
					   BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT :
					   height - BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT);
		downButton.moveTo (x0, y0 + height - downButtonHeight);
		downButton.setWidth (width);
		downButton.setHeight (downButtonHeight);
	}
}

void ChoiceBox::updateItems ()
{
	// Keep Buttons on top
	int cs = children_.size ();
	if ((cs >= 2) &&
	    ((children_[cs - 1] != (Widget*) &upButton) ||
	     (children_[cs - 2] != (Widget*) &downButton)))
	{
		downButton.moveToTop ();
		upButton.moveToTop ();
	}

	double x0 = getXOffset ();
	double y0 = getYOffset ();
	double width = getEffectiveWidth ();
	double height = getEffectiveHeight ();
	double itemHeight = (height >= 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
			     height - 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT : 0);
	double upButtonHeight = (height >= BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
				 BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT : height);

	for (uint i = 0; i < items.size (); ++i)
	{
		if (items[i].widget)
		{
			if (i + 1 == uint (activeNr)) items[i].widget->show ();
			else items[i].widget->hide ();

			items[i].widget->moveTo (x0 + BWIDGETS_DEFAULT_CHOICEBOX_PADDING, y0 + upButtonHeight);
			items[i].widget->setWidth (width > 2 * BWIDGETS_DEFAULT_CHOICEBOX_PADDING ?
						   width - 2 * BWIDGETS_DEFAULT_CHOICEBOX_PADDING : 0);
			items[i].widget->setHeight (itemHeight);
		}
	}
}

void ChoiceBox::onWheelScrolled (BEvents::WheelEvent* event)
{
	double newNr = LIMIT (activeNr - event->getDeltaY (), 1, items.size ());
	setValue (items[newNr - 1].value);
}

void ChoiceBox::handleButtonClicked (BEvents::Event* event)
{
	if (event && (event->getEventType () == BEvents::EventType::BUTTON_PRESS_EVENT) && event->getWidget ())
	{
		BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
		Button* w = (Button*) ev->getWidget ();
		if (w->getParent ())
		{
			ChoiceBox* p = (ChoiceBox*) w->getParent ();
			if (p->getParent ())
			{
				double actNr = p->activeNr;
				if ((w == (Button*) &(p->upButton)) && (actNr >= 2))
				{
					p->setValue (p->items[actNr - 1 - 1].value);
				}
				if ((w == (Button*) &(p->downButton)) && (actNr < p->items.size ()))
				{
					p->setValue (p->items[actNr - 1 + 1].value);
				}
			}
		}
	}
}

void ChoiceBox::handleItemClicked (BEvents::Event* event)
{
if (event && (event->getEventType () == BEvents::EventType::BUTTON_PRESS_EVENT) && event->getWidget ())
	{
		BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
		Widget* w = ev->getWidget ();
		if (w->getParent ())
		{
			ChoiceBox* p = (ChoiceBox*) w->getParent ();
			if (p->getParent ())
			{
				for (uint i = 0; i < p->items.size (); ++i)
				{
					if (w == p->items[i].widget) p->setValue (p->items[i].value);
				}
			}
		}
	}

}

}
