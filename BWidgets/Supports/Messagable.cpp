/* Messagable.cpp
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

#include "Messagable.hpp"
#include "../Window.hpp"
#include "../../BEvents/MessageEvent.hpp"

namespace BWidgets
{

void Messagable::setMessagable (const bool status) {setSupport (status);}

bool Messagable::isMessagable () const {return getSupport();}

void Messagable::postMessage (const std::string& name, const BUtilities::Any content)
{
    Widget* thisWidget = dynamic_cast<Widget*> (this);
    if (!thisWidget) return;

    Window* main = thisWidget->getMainWindow();
    if (!main) return;
	
    BEvents::MessageEvent* event = new BEvents::MessageEvent (thisWidget, name, content);
	main->addEventToQueue (event);
}

void Messagable::onMessage (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::MessageEvent) (event);
}


}