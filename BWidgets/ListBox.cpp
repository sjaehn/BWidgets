/* ListBox.cpp
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

#include "ListBox.hpp"

namespace BWidgets
{
ListBox::ListBox () :
	ListBox (0.0, 0.0, 0.0, 0.0, "listbox") {}

ListBox::ListBox (const double x, const double y, const double width, const double height,
	 	  const std::string& name) :
	 ChoiceBox (x, y, width, height, name),
	 listTop (0)
 {
	upButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
 	downButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
 }

ListBox::ListBox (const double x, const double y, const double width, const double height,
		  const std::string& name, const std::vector<std::string>& strings, double preselection) :
	ChoiceBox (x, y, width, height, name, strings, preselection),
	listTop (0)
{
	if (!items.empty ()) listTop = 1;

	upButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
 	downButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
}

ListBox::ListBox (const double x, const double y, const double width, const double height,
		  const std::string& name, const std::vector<stringItem>& strItems, double preselection) :
	ChoiceBox (x, y, width, height, name, strItems, preselection),
	listTop (0)
{
	if (!items.empty ()) listTop = 1;

	upButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
 	downButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
}

ListBox::ListBox (const double x, const double y, const double width, const double height,
		  const std::string& name, const std::vector<Item>& items, double preselection) :
	ChoiceBox (x, y, width, height, name, items, preselection),
	listTop (0)
{
	if (!items.empty ()) listTop = 1;

	upButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
	downButton.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, ListBox::handleButtonClicked);
}

ListBox::ListBox (const ListBox& that) : ChoiceBox (that), listTop (that.listTop) {}

ListBox::~ListBox () {}

ListBox& ListBox::operator= (const ListBox& that)
{
	listTop = that.listTop;

	ChoiceBox::operator= (that);
	return *this;
}

void ListBox::setTop (const int top)
{
	double oldtop = listTop;

	if (items.empty ()) listTop = 0;

	else
	{
		size_t size = items.size ();
		if (top <= 0) listTop = 1;
		else if (uint (top) <= size) listTop = top;
		else listTop = size;

		int lines = getLines ();
		if ((uint (getBottom ()) > size) && (size - lines >= 1)) listTop = size - lines + 1;
	}

	if (oldtop != listTop) update ();
}

int ListBox::getTop () const {return listTop;}

void ListBox::onWheelScrolled (BEvents::WheelEvent* event)
{
	setTop (getTop() - event->getDeltaY ());
}

void ListBox::handleButtonClicked (BEvents::Event* event)
{
	if (event && (event->getEventType () == BEvents::EventType::BUTTON_PRESS_EVENT) && event->getWidget ())
	{
		BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
		Button* w = (Button*) ev->getWidget ();
		if (w->getParent ())
		{
			ListBox* p = (ListBox*) w->getParent ();
			if (p->getParent ())
			{
				if (w == (Button*) &(p->upButton)) p->setTop (p->getTop () - 1);
				if (w == (Button*) &(p->downButton)) p->setTop (p->getTop () + 1);
			}
		}
	}
}

void ListBox::updateItems ()
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
	double listHeight = (height >= 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
			     height - 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT : 0);
	double upButtonHeight = (height >= BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
				 BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT : height);
	double itemHeight = items[0].widget->getHeight ();
	double lineHeight = ((items.empty () || (itemHeight == 0)) ? 20 : itemHeight);
	uint lines = ceil (listHeight / lineHeight);

	for (uint i = 0; i < items.size (); ++i)
	{
		Widget* w = items[i].widget;

		if ((i + 1 >= uint (listTop)) && (i + 1 < listTop + lines))
		{
			w->moveTo (x0 + BWIDGETS_DEFAULT_CHOICEBOX_PADDING,
				   y0 + upButtonHeight + (i + 1 - listTop) * lineHeight);
			w->setWidth (width > 2 * BWIDGETS_DEFAULT_CHOICEBOX_PADDING ?
				     width - 2 * BWIDGETS_DEFAULT_CHOICEBOX_PADDING : 0);
			w->setHeight (lineHeight);

			if (i + 1 == uint (activeNr)) w->setState (BColors::ACTIVE);
			else w->setState (BColors::NORMAL);

			w->show ();
		}
		else
		{
			w->hide ();
		}

	}
}

int ListBox::getLines ()
{
	double height = getEffectiveHeight ();
	double listHeight = (height >= 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT ?
			     height - 2 * BWIDGETS_DEFAULT_CHOICEBOX_BUTTON_HEIGHT : 0);
	double lineHeight = (labels.empty () ? 20 : items[0].widget->getHeight ());
	int lines = (listHeight > lineHeight ? listHeight / lineHeight : 1);
	return lines;
}

}
