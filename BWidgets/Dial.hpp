/* Dial.hpp
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

#ifndef BWIDGETS_DIAL_HPP_
#define BWIDGETS_DIAL_HPP_

#include "RadialMeter.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Scrollable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "Draws/drawArc.hpp"
#include "Draws/drawKnob.hpp"
#include <cairo/cairo.h>

#ifndef BWIDGETS_DEFAULT_DIAL_WIDTH
#define BWIDGETS_DEFAULT_DIAL_WIDTH 40.0
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_HEIGHT
#define BWIDGETS_DEFAULT_DIAL_HEIGHT BWIDGETS_DEFAULT_DIAL_WIDTH
#endif

namespace BWidgets
{

/**
 *  @brief  %Dial widget.
 *
 *  %Dial is a Valueable Widget derived from RadialMeter. It displays a pseudo
 *  3D dial consisting of a knob and an arc scale. It supports user
 *  interaction via Clickable, Draggable, and Scrollable. Its appearance is 
 *  defined by the BgColors parameter (static elements) and by the FgColors 
 *  parameter (value). 
 *
 *  @todo Inverse range, negative step.
 */
class Dial :	public RadialMeter,
				public Clickable, 
				public Draggable, 
				public Scrollable
{
protected:
	BUtilities::RectArea<> scale_;

public:

	/**
	 *  @brief  Constructs a default %Dial object.
	 */
	Dial ();

	/**
	 *  @brief  Constructs a default %Dial object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Dial (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %Dial with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Dial	(const double value, const double min, const double max, double step = 0.0, 
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Dial.
	 *  @param x  %Dial X origin coordinate.
	 *  @param y  %Dial Y origin coordinate.
	 *  @param width  %Dial width.
	 *  @param height  %Dial height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Dial title (default = "").
	 */
	Dial	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Dial. 
	 *  @return  Pointer to the new %Dial.
	 *
	 *  Creates a clone of this %Dial by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Dial. 
	 *  @param that  Other %Dial.
	 *
	 *  Copies all properties from another %Dial. But NOT its linkage.
	 */
	void copy (const Dial* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. Sets the value and calls the widget static 
	 *  callback function.
     */
    virtual void onButtonPressed (BEvents::Event* event) override;

	/**
     *  @brief  Method called upon pointer drag.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a pointer drag. Changes the value and calls the widget static callback
	 *  function.
     */
    virtual void onPointerDragged (BEvents::Event* event) override;
	
	/**
     *  @brief  Method called upon (mouse) wheel scroll.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  a (mouse) wheel scroll. Increases or decreases the value and calls the
	 *  widget static callback function.
     */
    virtual void onWheelScrolled (BEvents::Event* event) override;

protected:
	/**
     *  @brief  Unclipped draw a %Dial to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %Dial to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %Dial to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea<>& area) override;
};

inline Dial::Dial () :
	Dial	(0.0, 0.0, BWIDGETS_DEFAULT_DIAL_WIDTH, BWIDGETS_DEFAULT_DIAL_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 URID_UNKNOWN_URID, "")
{

}

inline Dial::Dial (const uint32_t urid, const std::string& title) : 
	Dial	(0.0, 0.0, BWIDGETS_DEFAULT_DIAL_WIDTH, BWIDGETS_DEFAULT_DIAL_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline Dial::Dial (double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	Dial	(0.0, 0.0, BWIDGETS_DEFAULT_DIAL_WIDTH, BWIDGETS_DEFAULT_DIAL_HEIGHT, 
			 value, min, max, step, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline Dial::Dial	(const double  x, const double y, const double width, const double height, 
						 double value, const double min, const double max, double step, 
						 std::function<double (const double& x)> transferFunc,
			 			 std::function<double (const double& x)> reTransferFunc,
						 uint32_t urid, std::string title) :
		RadialMeter	(x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
		Clickable(),
		Draggable(),
		Scrollable(),
		scale_ (0, 0, width, height)
{

}

inline Widget* Dial::clone () const 
{
	Widget* f = new Dial (urid_, title_);
	f->copy (this);
	return f;
}

inline void Dial::copy (const Dial* that)
{
	scale_ = that->scale_;
	Scrollable::operator= (*that);
	Draggable::operator= (*that);
	Clickable::operator= (*that);
	RadialMeter::copy (that);
}

inline void Dial::update ()
{
	scale_ = BUtilities::RectArea<> (getXOffset(), getYOffset(), getEffectiveWidth(), getEffectiveHeight());
	Widget::update();
}

inline void Dial::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (scale_.getWidth() > 0) 
	{
		const double xc = scale_.getX() + 0.5 * scale_.getWidth();
		const double yc = scale_.getY() + 0.5 * scale_.getHeight();
		const double dist = sqrt ((pev->getPosition().x - xc) * (pev->getPosition().x - xc) + (pev->getPosition().y - yc) * (pev->getPosition().y - yc));
		if (dist > 0.1 * scale_.getWidth())
		{
			double ang = 
			(
				pev->getPosition().y >= yc ? 
				acos ((pev->getPosition().x - xc) / dist) :
				2.0 * M_PI - acos ((pev->getPosition().x - xc) / dist)
			);
			if (ang < BWIDGETS_DEFAULT_DRAWARC_START) ang += 2.0 * M_PI;
			if (ang <= BWIDGETS_DEFAULT_DRAWARC_END)
			{
				const double rval = (ang - BWIDGETS_DEFAULT_DRAWARC_START) / BWIDGETS_DEFAULT_DRAWARC_SIZE;
				setValue (getValueFromRatio (rval, transfer_, reTransfer_));
			}
		}
	}
	Clickable::onButtonPressed (event);
}

inline void Dial::onPointerDragged (BEvents::Event* event)
{
	if (isClickable()) onButtonPressed (event);
	else
	{
		BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
		if (!pev) return;
		if (scale_.getWidth() > 0) 
		{
			if (getStep() != 0.0) setValue (getValue() - pev->getDelta().y * getStep ());
			else setValue (getValueFromRatio	(getRatioFromValue (getValue(), transfer_) - pev->getDelta().y / (0.5 * scale_.getWidth() * BWIDGETS_DEFAULT_DRAWARC_SIZE), 
												 transfer_, 
												 reTransfer_));
		}
	}
	Draggable::onPointerDragged (event);
}

inline void Dial::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (scale_.getWidth() > 0) 
	{
		if (getStep() != 0.0) setValue (getValue() - wev->getDelta().y * getStep ());

		else setValue (getValueFromRatio	(getRatioFromValue (getValue(), transfer_) - wev->getDelta().y / (0.5 * scale_.getWidth() * BWIDGETS_DEFAULT_DRAWARC_SIZE), 
											 transfer_, 
											 reTransfer_));
		
	}
	Scrollable::onWheelScrolled (event);
}

inline void Dial::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Dial::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea<> (x0, y0, width, height));
}

inline void Dial::draw (const BUtilities::RectArea<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1))
	{
		cairo_t* cr = cairo_create (surface_);

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const double rval = getRatioFromValue (getValue(), transfer_);
			const double rad = 0.5 * (scale_.getWidth() < scale_.getHeight() ? scale_.getWidth() : scale_.getHeight());
			const BStyles::Color fgColor = getFgColors()[getStatus()];
			const BStyles::Color bgColor = getBgColors()[getStatus()];
			drawArc (cr, scale_.getX() + 0.5 * scale_.getWidth(), scale_.getY() + 0.5 * scale_.getHeight(), rad - 1.0, 0.0, rval, fgColor, bgColor);
			drawKnob(cr, scale_.getX() + 0.5 * scale_.getWidth() + 0.5, scale_.getY() + 0.5 * scale_.getHeight() + 0.5, 0.6 * rad - 1.0, 1.0, bgColor, bgColor);
			
			// Draw spot
			cairo_set_source_rgba(cr, CAIRO_RGBA(fgColor));
			cairo_set_line_width(cr, 0.0);
			cairo_arc
			(
				cr, 
				scale_.getX() + 0.5 * scale_.getWidth() + 0.4 * rad * cos (BWIDGETS_DEFAULT_DRAWARC_START + rval * BWIDGETS_DEFAULT_DRAWARC_SIZE), 
				scale_.getY() + 0.5 * scale_.getHeight() + 0.4 * rad * sin (BWIDGETS_DEFAULT_DRAWARC_START + rval * BWIDGETS_DEFAULT_DRAWARC_SIZE), 
				0.075 * rad, 
				0.0,
				2.0 * M_PI
			);
			cairo_fill (cr);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_DIAL_HPP_ */
