/* MessageEvent.hpp
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

#ifndef BEVENTS_MESSAGEEVENT_HPP_
#define BEVENTS_MESSAGEEVENT_HPP_

#include "../BUtilities/Any.hpp"
#include <string>
#include "Event.hpp"

namespace BEvents
{
 /**
  *  @brief  Ubiquitous event type.
  */
class MessageEvent : public Event
{
protected:
	std::string messageName_;
	BUtilities::Any messageContent_;

public:

    /**
     *  @brief  Creates an empty %MessageEvent.
     */
	MessageEvent () :
		MessageEvent (nullptr, "", BUtilities::Any ()) 
    {

    }

    /**
     *  @brief  Creates a %MessageEvent
     *  @param widget  Pointer to the widget which caused the %MessageEvent.
     *  @param name  Name or identifier (e.g., an URI) for the message.
     *  @param content  Message content.
     */
	MessageEvent (BWidgets::Widget* widget, const std::string& name, const BUtilities::Any& content) :
		Event (widget, MESSAGE_EVENT), 
        messageName_ (name), 
        messageContent_ (content) 
    {

    }

    /**
     *  @brief  Changes the name of the message.
     *  @param name  Name or identifier (e.g., an URI) for the message.
     */
	virtual void setName (const std::string& name)
	{
        messageName_ = name;
    }

    /**
     *  @brief  Gets the name of the message.
     *  @return  Name or identifier (e.g., an URI) for the message.
     */
	std::string getName () const
	{
        return messageName_;
    }

    /**
     *  @brief  Replaces the message content.
     *  @param content  Message content.
     */
	virtual void setContent (const BUtilities::Any& content)
	{
        messageContent_ = content;
    }

    /**
     *  @brief  Gets the message content.
     *  @return  Copy of the message content.
     */
	BUtilities::Any getContent () const
	{
        return messageContent_;
    }
};

}

#endif /* BEVENTS_MESSAGEEVENT_HPP_ */
