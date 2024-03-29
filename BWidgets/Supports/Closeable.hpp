/* Closeable.hpp
 * Copyright (C) 2018 - 2023  Sven Jähnichen
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

#ifndef BWIDGETS_CLOSEABLE_HPP_
#define BWIDGETS_CLOSEABLE_HPP_

#include "Callback.hpp"
#include "Support.hpp"
#include "EventQueueable.hpp"
#include "../Widget.hpp"
#include "../../BEvents/WidgetEvent.hpp"

namespace BWidgets
{

class Widget;   // Forward declaration

/**
 *  @brief  Widget close request support.
 */
class Closeable : virtual public Callback, public Support
{
public:
    /**
     *  @brief  Switch the widget close request support on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether a widget may emit a closeRequestEvent. In this case,
     *  a WidgetEvent with the type closeRequestEvent will be scheduled and 
     *  send to the widget.
     */
    virtual void setCloseable (const bool status);

    /**
     *  @brief  Information about the widget close request support.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is closeable, the main window event handler let the 
     *  widget emit a WidgetEvent of the type closeRequestEvent.
     */
    bool isCloseable () const;

    /**
	 *  @brief  Requests widget close with handle from main window.
	 */
	virtual void postCloseRequest ();

     /**
	 *  @brief  Requests widget close.
	 *  @param handle  Widget that will handle the close request event.
	 */
	virtual void postCloseRequest (Widget* handle);

    /**
     *  @brief  Method called upon an close request event.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  an close event from the host. By default, it firstly calls its static 
     *  callback function, then it let the parent Widget release this Widget.
     */
    virtual void onCloseRequest (BEvents::Event* event);

};

inline void Closeable::setCloseable (const bool status) 
{
    setSupport (status);
}

inline bool Closeable::isCloseable () const 
{
    return getSupport();
}

inline void Closeable::postCloseRequest () 
{
    Widget* thisWidget = dynamic_cast<Widget*> (this);
    if (thisWidget)
    {
        Widget* main = dynamic_cast<Widget*>(thisWidget->getMain());
        if (main) postCloseRequest (main);
    }
}

inline void Closeable::postCloseRequest (Widget* handle)
{
    Widget* thisWidget = dynamic_cast<Widget*> (this);
	if (thisWidget && handle)
	{
		BEvents::WidgetEvent* event = new BEvents::WidgetEvent (handle, thisWidget, BEvents::Event::EventType::closeRequestEvent);
        EventQueueable* q = dynamic_cast<EventQueueable*>(thisWidget->getMain());
		if (q && event) q->addEventToQueue (event);
	}
}

inline void Closeable::onCloseRequest (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::closeRequestEvent) (event);

    Widget* thisWidget = dynamic_cast<Widget*> (this);
    BEvents::WidgetEvent* widgetEvent = dynamic_cast<BEvents::WidgetEvent*> (event);

	if ((thisWidget) && (widgetEvent) && (widgetEvent->getWidget () == thisWidget))
	{
		Widget* requestWidget = widgetEvent->getRequestWidget ();
		Widget* parent = dynamic_cast<Widget*>(requestWidget ? requestWidget->getParent () : nullptr);
		if (parent && parent->Linkable::contains (requestWidget)) thisWidget->release (requestWidget);
	}
}

}
#endif /* BWIDGETS_CLOSEABLE_HPP_ */