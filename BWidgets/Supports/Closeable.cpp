/* Closeable.cpp
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

#include "Closeable.hpp"
#include "../Window.hpp"
#include "../../BEvents/WidgetEvent.hpp"

namespace BWidgets
{

void Closeable::setCloseable (const bool status) 
{
    setSupport (status);
}

bool Closeable::isCloseable () const 
{
    return getSupport();
}

void Closeable::postCloseRequest () 
{
    Widget* thisWidget = dynamic_cast<Widget*> (this);
    if (thisWidget)
    {
        Window* main = thisWidget->getMainWindow();
        if (main) postCloseRequest (main);
    }
}

void Closeable::postCloseRequest (Widget* handle)
{
    Widget* thisWidget = dynamic_cast<Widget*> (this);
	if (thisWidget && handle)
	{
		BEvents::WidgetEvent* event = new BEvents::WidgetEvent (handle, thisWidget, BEvents::Event::EventType::closeRequestEvent);
        Window* main = thisWidget->getMainWindow();
		if (main && event) main->addEventToQueue (event);
	}
}

void Closeable::onCloseRequest (BEvents::Event* event)
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
