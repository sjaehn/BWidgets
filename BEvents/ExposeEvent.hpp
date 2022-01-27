/* ExposeEvent.hpp
 * Copyright (C) 2018 - 2021  Sven Jähnichen
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

#ifndef BEVENTS_EXPOSEEVENT_HPP_
#define BEVENTS_EXPOSEEVENT_HPP_

#include "WidgetEvent.hpp"
#include "../BUtilities/RectArea.hpp"

namespace BEvents
{

/**
 *  @brief  Event to request (re-)visualization of a widget.
 *
 *  %ExposeEvent is emitted by a parent event widget (or window) if the visual
 *  content of a child (request) widget is requested to be updated. An 
 *  %ExposeEvent additionally contains the coordinates (x, y, width and height)
 *  of the output region (relative to the widgets origin) to be updated.
 */
class ExposeEvent : public WidgetEvent
{
protected:
	BUtilities::RectArea exposeArea_;

public:

    /**
     *  @brief  Creates an empty %ExposeEvent.
     */
	ExposeEvent () :
		ExposeEvent (nullptr, nullptr, NO_EVENT, 0, 0, 0, 0) 
    {

    }

    /**
     *  @brief  Creates an %ExposeEvent.
     *  @param eventWidget  Widget on which the event will be applied.
     *  @param requestWidget  Widget which requests the event for another one.
     *  @param type  EventType.
     *  @param x  Expose area origin x coordinate relative to the widget 
     *  origin.
     *  @param y  Expose area origin y coordinate relative to the widget 
     *  origin.
     *  @param width  Area width.
     *  @param heigth  Area origin height.
     */
	ExposeEvent (BWidgets::Widget* eventWidget, BWidgets::Widget* requestWidget, const EventType type,
		         const double x, const double y, const double width, const double height) :
		ExposeEvent (eventWidget, requestWidget, type, BUtilities::RectArea (x, y, width, height)) 
    {

    }

    /**
     *  @brief  Creates an %ExposeEvent.
     *  @param eventWidget  Widget on which the event will be applied.
     *  @param requestWidget  Widget which requests the event for another one.
     *  @param type  EventType.
     *  @param area  Expose area relative to the widget origin.
     */
	ExposeEvent (BWidgets::Widget* eventWidget, BWidgets::Widget* requestWidget, const EventType type,
		         const BUtilities::RectArea& area) :
		WidgetEvent (eventWidget, requestWidget, type),
		exposeArea_ (area) 
    {

    }

	/**
	 *  @brief  Redefines the area coordinates of the output region.
	 *  @param area  Area coordinates relative to the widgets origin.
	 */
	void setArea (const BUtilities::RectArea& area)
	{
        exposeArea_ = area;
    }

	/**
	 *  @brief  Gets the area coordinates of the output region.
	 *  @return  Area coordinates relative to the widgets origin.
	 */
	BUtilities::RectArea getArea () const
	{
        return exposeArea_;
    }
};

}

#endif /* BEVENTS_EXPOSEEVENT_HPP_ */
