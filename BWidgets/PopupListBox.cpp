/* PopupListBox.cpp
 * Copyright (C) 2018  Sven Jähnichen
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

#include "PopupListBox.hpp"

namespace BWidgets
{
PopupListBox::PopupListBox () :
	PopupListBox (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "popuplistbox") {}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listWidth,
			    const double listHeight, const std::string& name) :
	PopupListBox (x, y, width, height, 0.0, 0.0, listWidth, listHeight, name, std::vector<Item> {}, UNSELECTED) {}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listWidth,
			    const double listHeight, const std::string& name,
			    const std::vector<std::string>& strings, double preselection) :
	PopupListBox (x, y, width, height, 0.0, 0.0, listWidth, listHeight, name, strings, preselection) {}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listWidth,
			    const double listHeight, const std::string& name,
			    const std::vector<stringItem>& strItems, double preselection) :
	PopupListBox (x, y, width, height, 0.0, 0.0, listWidth, listHeight, name, strItems, preselection) {} //TODO

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listWidth,
			    const double listHeight, const std::string& name,
			    const std::vector<Item>& items, double preselection) :
	PopupListBox (x, y, width, height, 0.0, 0.0, listWidth, listHeight, name, items, preselection) {}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listXOffset,
			    const double listYOffset, const double listWidth,
			    const double listHeight, const std::string& name) :
	PopupListBox (x, y, width, height, listXOffset, listYOffset, listWidth, listHeight, name, std::vector<Item> {}, UNSELECTED) {}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listXOffset,
			    const double listYOffset, const double listWidth,
			    const double listHeight, const std::string& name,
			    const std::vector<std::string>& strings, double preselection) :
	PopupListBox (x, y, width, height, listXOffset, listYOffset, listWidth, listHeight, name, std::vector<Item> {}, preselection)
{
	try {listBox.addText (strings);}
	catch (std::bad_alloc& ba) {throw ba;}

	if ((preselection >= 1.0) && (preselection <= strings.size ()))
	{
		value = floor (preselection);
		try {widget = new Label (0, 0, 0, 0, name + BWIDGETS_DEFAULT_ITEMBOX_ITEM_NAME, strings[int (value) - 1]);}
		catch (std::bad_alloc& ba) {throw ba;}
		initItem ();
		add (*widget);
	}

	listBox.setValue (value);
	if (!strings.empty()) listBox.setTop (1);
}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listXOffset,
			    const double listYOffset, const double listWidth,
			    const double listHeight, const std::string& name,
			    const std::vector<stringItem>& strItems, double preselection) :
	PopupListBox (x, y, width, height, listXOffset, listYOffset, listWidth, listHeight, name, std::vector<Item> {}, preselection)
{
	try {listBox.addText (strItems);}
	catch (std::bad_alloc& ba) {throw ba;}

	// Set item
	if (preselection != UNSELECTED)
	{
		for (uint i = 0; i < strItems.size (); ++i)
		{
			if (strItems[i].value == preselection)
			{
				value = strItems[i].value;
				try {widget = new Label (0, 0, 0, 0, name + BWIDGETS_DEFAULT_ITEMBOX_ITEM_NAME,
								     strItems[i].string);}
				catch (std::bad_alloc& ba) {throw ba;}
				initItem ();
				add (*widget);
			}
		}
	}

	listBox.setValue (value);
	if (!strItems.empty()) listBox.setTop (1);
}

PopupListBox::PopupListBox (const double x, const double y, const double width,
			    const double height, const double listXOffset,
			    const double listYOffset, const double listWidth,
			    const double listHeight, const std::string& name,
			    const std::vector<Item>& items, double preselection) :
		ItemBox (x, y, width, height, name, {UNSELECTED, nullptr}),
		downButton (0, 0, 0, 0, name + BWIDGETS_DEFAULT_POPUPLISTBOX_BUTTON_NAME, 0.0),
		listBox (0, 0, 0, 0, name + BWIDGETS_DEFAULT_POPUPLISTBOX_LISTBOX_NAME, items, preselection),
		listBoxXOffset (listXOffset), listBoxYOffset (listYOffset), listBoxWidth (listWidth), listBoxHeight (listHeight)

{
	setScrollable (true);

	// Set item
	if (preselection != UNSELECTED)
	{
		for (uint i = 0; i < items.size (); ++i)
		{
			if (items[i].value == preselection)
			{
				value = items[i].value;
				if (items[i].widget)
				{
					try {widget = items[i].widget->clone ();}
					catch (std::bad_alloc& ba) {throw ba;}
					initItem ();
					add (*widget);
				}
				break;
			}
		}
	}

	downButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, PopupListBox::handleDownButtonClicked);
	listBox.extensionData = this;
	listBox.setCallbackFunction (BEvents::EventType::VALUE_CHANGED_EVENT, PopupListBox::handleValueChanged);

	listBox.hide ();

	add (downButton);
}

PopupListBox::PopupListBox (const PopupListBox& that) :
		ItemBox (that), downButton (that.downButton), listBox (that.listBox),
		listBoxXOffset (that.listBoxXOffset),
		listBoxYOffset (that.listBoxYOffset), listBoxWidth (that.listBoxWidth), listBoxHeight (that.listBoxHeight)
{
	if (widget) release (widget);
	try {widget = that.widget->clone ();}
	catch (std::bad_alloc& ba) {throw ba;}
	initItem ();
	add (*widget);
	add (downButton);
}

PopupListBox::~PopupListBox ()
{
	if (widget) delete widget;
}

PopupListBox& PopupListBox::operator= (const PopupListBox& that)
{
	downButton = that.downButton;
	listBox = that.listBox;
	listBoxXOffset = that.listBoxXOffset;
	listBoxYOffset = that.listBoxYOffset;
	listBoxWidth = that.listBoxWidth;
	listBoxHeight = that.listBoxHeight;

	ItemBox::operator= (that);
	if (widget) release (widget);
	try {widget = that.widget->clone ();}
	catch (std::bad_alloc& ba) {throw ba;}
	initItem ();
	add (*widget);

	listBox.extensionData = this;
	return *this;
}

Widget* PopupListBox::clone () const {return new PopupListBox (*this);}

std::vector<Item>* PopupListBox::getItemList () {return listBox.getItemList ();}

ListBox* PopupListBox::getListBox () {return &listBox;}

void PopupListBox::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}

void PopupListBox::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	ItemBox::applyTheme (theme, name);
	downButton.applyTheme (theme, name + BWIDGETS_DEFAULT_POPUPLISTBOX_BUTTON_NAME);
	listBox.applyTheme (theme, name + BWIDGETS_DEFAULT_POPUPLISTBOX_LISTBOX_NAME);
}

void PopupListBox::setValue (const double val)
{
	if (val != listBox.getValue ()) listBox.setValue (val);
	if (value != listBox.getValue ())
	{
		ItemBox::setValue (listBox.getValue ());
		if (widget) delete (widget);
		widget = listBox.getItem (listBox.getValue ()).widget->clone ();
		initItem ();
		add (*widget);
		update ();
	}
}

void PopupListBox::moveListBox (const double xOffset, const double yOffset)
{
	listBoxXOffset = xOffset;
	listBoxYOffset = yOffset;
	if (listBox.isVisible()) update ();
}

void PopupListBox::resizeListBox (const double width, const double height)
{
	listBoxWidth = width;
	listBoxHeight = height;
	if (listBox.isVisible()) update ();
}

void PopupListBox::update ()
{
	// Update super widget first
	ItemBox::update ();

	// Keep button on top
	int cs = children_.size ();
	if ((cs >= 2) && (children_[cs - 1] != (Widget*) &downButton))
	{
		downButton.moveToTop ();
	}

	// Calculate size and position of widget elements
	double x0 = getXOffset ();
	double y0 = getYOffset ();
	double w = getEffectiveWidth ();
	double h = getEffectiveHeight ();

	// Down button
	double dw = (w > BWIDGETS_DEFAULT_POPUPLISTBOX_BUTTON_WIDTH ? BWIDGETS_DEFAULT_POPUPLISTBOX_BUTTON_WIDTH : w);
	downButton.moveTo (x0 + w - dw, y0);
	downButton.setWidth (dw);
	downButton.setHeight (h);

	// List box
	if ((main_) && (!listBox.getMainWindow()))
	{
		main_->add (listBox);
	}
	if ((!main_) && (listBox.getMainWindow())) listBox.getMainWindow()->release (&listBox);
	if ((listBoxXOffset == 0.0) && (listBoxYOffset == 0.0)) listBox.moveTo (getOriginX (), getOriginY () + getHeight ());
	else listBox.moveTo (getOriginX () + listBoxXOffset, getOriginY () + listBoxYOffset);
	listBox.setWidth (listBoxWidth);
	listBox.setHeight (listBoxHeight);
}

void PopupListBox::onButtonPressed (BEvents::PointerEvent* event)
{
	if (listBox.isVisible ()) listBox.hide ();
	else
	{
		update ();
		listBox.show ();
		listBox.moveToTop ();
	}

	//Widget::cbfunction[BEvents::EventType::BUTTON_PRESS_EVENT] (event);
}

void PopupListBox::onWheelScrolled (BEvents::WheelEvent* event)
{
	std::vector<Item>* itemList = listBox.getItemList ();
	double newNr = LIMIT (listBox.getActive () - event->getDeltaY (), 1, itemList->size ());
	setValue ((*itemList)[newNr - 1].value);
}

void PopupListBox::initItem ()
{
	if (widget)
	{
		widget->getBorder ()->setPadding (BWIDGETS_DEFAULT_ITEMBOX_ITEM_PADDING);
		widget->setClickable (false);
		widget->setDraggable (false);
		widget->setScrollable (false);
		widget->setFocusable (false);
		widget->setState (BColors::NORMAL);
		widget->moveTo (0, 0);
		widget->show ();
	}
}

void PopupListBox::handleDownButtonClicked (BEvents::Event* event)
{
	if (event && (event->getEventType () == BEvents::EventType::BUTTON_PRESS_EVENT) && event->getWidget ())
	{
		BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
		Widget* w = ev->getWidget ();
		if (w->getParent ())
		{
			PopupListBox* p = (PopupListBox*) w->getParent ();
			if (p->getParent ())
			{
				if (w == &(p->downButton)) p->onButtonPressed (ev);
			}
		}
	}
}

void PopupListBox::handleValueChanged (BEvents::Event* event)
{
if (event && (event->getEventType () == BEvents::EventType::VALUE_CHANGED_EVENT) && event->getWidget ())
	{
		BEvents::ValueChangedEvent* ev = (BEvents::ValueChangedEvent*) event;
		ValueWidget* w = (ValueWidget*) ev->getWidget ();
		if (w->extensionData)
		{
			PopupListBox* p = (PopupListBox*) w->extensionData;
			if ((p->getParent ()) && (w == (ValueWidget*) &(p->listBox)))
			{
				p->setValue (w->getValue ());
				p->listBox.hide ();
			}
		}
	}

}

}
