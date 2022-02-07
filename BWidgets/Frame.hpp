/* Frame.hpp
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

#ifndef BWIDGETS_FRAME_HPP_
#define BWIDGETS_FRAME_HPP_

#include "Widget.hpp"
#include "Supports/Draggable.hpp"

#ifndef BWIDGETS_DEFAULT_FRAME_WIDTH
#define BWIDGETS_DEFAULT_FRAME_WIDTH BWIDGETS_DEFAULT_WIDGET_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_FRAME_HEIGHT
#define BWIDGETS_DEFAULT_FRAME_HEIGHT BWIDGETS_DEFAULT_WIDGET_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  Widgets with drag & drop support. 
 * 
 */
class Frame : public Widget, public Draggable
{
public:
    /**
	 *  @brief  Creates a %Frame.
	 *
	 *  Creates a Frame with default dimensions 
	 *  (BWIDGETS_DEFAULT_WIDTH, BWIDGETS_DEFAULT_HEIGHT).
	 */
	Frame ();

	/**
	 *  @brief  Creates a %Frame.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Frame (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %Frame.
	 *  @param x  %Frame X origin coordinate.
	 *  @param y  %Frame Y origin coordinate.
	 *  @param width  %Frame width.
	 *  @param height  %Frame height.
     *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Frame title.
	 */
	Frame (const double x, const double y, const double width, const double height, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

    /**
	 *  @brief  Creates a clone of the %Frame. 
	 *  @return  Pointer to the new frame.
	 *
	 *  Creates a clone of this frame by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Frame. 
	 *  @param that  Other %Frame.
	 *
	 *  Copies all properties from another %Frame. But NOT its linkage.
	 */
	void copy (const Frame* that);

    /**
     *  @brief  Method called upon pointer drag.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a pointer drag. Enables drag & drop and calls its static callback 
     *  function.
     */
    virtual void onPointerDragged (BEvents::Event* event) override;
};

inline Frame::Frame () :
    Frame (0.0, 0.0, BWIDGETS_DEFAULT_FRAME_WIDTH, BWIDGETS_DEFAULT_FRAME_HEIGHT)
{

}

inline Frame::Frame (const uint32_t urid, const std::string& title) :
    Widget (0.0, 0.0, BWIDGETS_DEFAULT_FRAME_WIDTH, BWIDGETS_DEFAULT_FRAME_HEIGHT, urid, title),
    Draggable ()
{

}

inline Frame::Frame (const double x, const double y, const double width, const double height, uint32_t urid, std::string title) :
    Widget (x, y, width, height, urid, title),
    Draggable ()
{

}

inline Widget* Frame::clone () const 
{
	Widget* f = new Frame (urid_, title_);
	f->copy (this);
	return f;
}

inline void Frame::copy (const Frame* that)
{
    Draggable::operator= (*that);
    Widget::copy (that);
}

inline void Frame::onPointerDragged (BEvents::Event* event)
{
    Draggable::onPointerDragged (event);

    BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
    if (pev) 
	{
		raiseToFront();
		moveTo (getPosition () + pev->getDelta ());
	}
}

}

#endif /* BWIDGETS_FRAME_HPP_ */