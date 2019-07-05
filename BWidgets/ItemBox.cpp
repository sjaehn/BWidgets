/* ItemBox.cpp
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

#include "ItemBox.hpp"

namespace BWidgets
{
ItemBox::ItemBox () :
	ItemBox (0.0, 0.0, 0.0, 0.0, "itembox", Item {UNSELECTED, nullptr}) {}

ItemBox::ItemBox (const double x, const double y, const double width,
		  const double height, const std::string& name, const Item item) :
	ValueWidget (x, y, width, height, name, item.value)

{
	background_ = BWIDGETS_DEFAULT_MENU_BACKGROUND;
	border_ = BWIDGETS_DEFAULT_MENU_BORDER;

	if (item.widget)
	{
		widget = item.widget;

		widget -> getBorder () -> setPadding (BWIDGETS_DEFAULT_ITEMBOX_ITEM_PADDING);
		widget -> setClickable (false);

		add (*widget);
	}
}

ItemBox::ItemBox (const ItemBox& that) :
	ValueWidget (that), widget (that.widget)
{
	add (*widget);
}

ItemBox::~ItemBox () {}

ItemBox& ItemBox::operator= (const ItemBox& that)
{
	widget = that.widget;

	ValueWidget::operator= (that);
	return *this;
}

Widget* ItemBox::clone () const {return new ItemBox (*this);}

void ItemBox::setItem (const Item item)
{
	bool wasClickable = false;

	if (widget)
	{
		widget -> isClickable ();
		release (widget);
	}

	// Set widget
	setValue (item.value);
	widget = item.widget;

	// Configure widget
	if (widget)
	{
		widget -> getBorder () -> setPadding (BWIDGETS_DEFAULT_ITEMBOX_ITEM_PADDING);
		widget -> setClickable (wasClickable);
		add (*widget);
	}

	update ();
}

Item ItemBox::getItem () const {return {getValue (), widget};}

void ItemBox::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}

void ItemBox::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	Widget::applyTheme (theme, name);
	if (widget) widget -> applyTheme (theme, name + BWIDGETS_DEFAULT_ITEMBOX_ITEM_NAME);

	update ();
}

void ItemBox::update ()
{
	// Update super widget first
	Widget::update ();

	if (widget)
	{
		// Set position of label
		double x0 = getXOffset ();
		double y0 = getYOffset ();
		double w = getEffectiveWidth ();
		double h = getEffectiveHeight ();

		widget -> moveTo (x0 + BWIDGETS_DEFAULT_ITEMBOX_PADDING, y0);
		widget -> setWidth (w - 2 * BWIDGETS_DEFAULT_ITEMBOX_PADDING > 0 ?
				    w - 2 * BWIDGETS_DEFAULT_ITEMBOX_PADDING : 0);
		widget -> setHeight (h);
	}
}

}
