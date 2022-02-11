/* HScrollBar.hpp
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

#ifndef BWIDGETS_HSCROLLBAR_HPP_
#define BWIDGETS_HSCROLLBAR_HPP_

#include "HScale.hpp"

#ifndef BWIDGETS_DEFAULT_HSCROLLBAR_WIDTH
#define BWIDGETS_DEFAULT_HSCROLLBAR_WIDTH BWIDGETS_DEFAULT_HSCALE_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_HSCROLLBAR_HEIGHT
#define BWIDGETS_DEFAULT_HSCROLLBAR_HEIGHT BWIDGETS_DEFAULT_HSCALE_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  %Horizontal scroll bar widget.
 *
 *  %HScrollBar is a Valueable Widget derived from HScale. It displays a value
 *  as a horizontal scrollbar and supports user interaction via Draggable, and 
 *  Scrollable. Its appearance is defined by the BgColors parameter.
 *
 *  The value can be point value (vsize = 0) or a range value (start value
 *  = widget value; end value = start value + vsize).
 *
 *  @todo Inverse range, negative step.
 */
class HScrollBar :	public HScale
{
protected:
	double vsize_;

public:

	/**
	 *  @brief  Constructs a default %HScrollBar object.
	 */
	HScrollBar ();

	/**
	 *  @brief  Constructs a default %HScrollBar object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	HScrollBar (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %HScrollBar with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param vsize  Optional, range covered by the value.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HScrollBar	(const double value, const double min, const double max, double step = 0.0, double vsize = 0.0,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HScrollBar.
	 *  @param x  %HScrollBar X origin coordinate.
	 *  @param y  %HScrollBar Y origin coordinate.
	 *  @param width  %HScrollBar width.
	 *  @param height  %HScrollBar height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param vsize  Optional, range covered by the value.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %HScrollBar title (default = "").
	 */
	HScrollBar	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0, double vsize = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %HScrollBar. 
	 *  @return  Pointer to the new %HScrollBar.
	 *
	 *  Creates a clone of this %HScrollBar by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %HScrollBar. 
	 *  @param that  Other %HScrollBar.
	 *
	 *  Copies all properties from another %HScrollBar. But NOT its linkage.
	 */
	void copy (const HScrollBar* that);

	/**
	 *  @brief  Sets the size of the value range. 
	 *  @param vsize  Scrollbar value range size.
	 *
	 *  The value can be point value (vsize = 0) or a range value (start value
	 *  = widget value; end value = start value + vsize).
	 */
	virtual void setValueSize (const double& vsize);

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

protected:
	/**
     *  @brief  Unclipped draw a %HScrollBar to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %HScrollBar to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %HScrollBar to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea<>& area) override;
};

inline HScrollBar::HScrollBar () :
	HScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HSCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HSCROLLBAR_HEIGHT, 
				 0.0, 0.0, 1.0, 0.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 URID_UNKNOWN_URID, "")
{

}

inline HScrollBar::HScrollBar (const uint32_t urid, const std::string& title) : 
	HScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HSCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HSCROLLBAR_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline HScrollBar::HScrollBar (double value, const double min, const double max, double step, double vsize, uint32_t urid, std::string title) : 
	HScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HSCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HSCROLLBAR_HEIGHT, 
			 value, min, max, step, vsize,
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline HScrollBar::HScrollBar	(const double  x, const double y, const double width, const double height, 
						 double value, const double min, const double max, double step, double vsize,
						 std::function<double (const double& x)> transferFunc,
			 			 std::function<double (const double& x)> reTransferFunc,
						 uint32_t urid, std::string title) :
		HScale	(x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
		vsize_ (vsize)
{

}

inline Widget* HScrollBar::clone () const 
{
	Widget* f = new HScrollBar (urid_, title_);
	f->copy (this);
	return f;
}

inline void HScrollBar::copy (const HScrollBar* that)
{
	vsize_ = that->vsize_;
	HScale::copy (that);
}

inline void HScrollBar::setValueSize (const double& vsize)
{
	if (vsize_ != vsize)
	{
		vsize_ = vsize;
		update();
	}
}

inline void HScrollBar::onButtonPressed (BEvents::Event* event)
{
	// Bypass HScale::onButtonPressed()
	Clickable::onButtonPressed (event);
}

inline void HScrollBar::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (scale_.getWidth()) 
	{
		if (getStep() != 0.0) setValue (getValue() + pev->getDelta().x * getStep ());
		else setValue (getValueFromRatio (getRatioFromValue(getValue(), transfer_) + pev->getDelta().x / scale_.getWidth(), transfer_, reTransfer_));
	}
	Draggable::onPointerDragged (event);
}

inline void HScrollBar::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void HScrollBar::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea<> (x0, y0, width, height));
}

inline void HScrollBar::draw (const BUtilities::RectArea<>& area)
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

			const double rval1 = getRatioFromValue (getValue(), transfer_);
			const double rval2 = getRatioFromValue (getValue() + vsize_, transfer_);
			const BStyles::Color fgColor = getBgColors()[getStatus()];
			const BStyles::Color bgColor = getBgColors()[getStatus()];
			drawHBar
			(
				cr, 
				scale_.getX(), scale_.getY(), scale_.getWidth(), scale_.getHeight(), 
				rval1 * (1.0 - scale_.getHeight() / scale_.getWidth()), 
				rval2 * (1.0 - scale_.getHeight() / scale_.getWidth()) + scale_.getHeight() / scale_.getWidth(), 
				fgColor, bgColor
			);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_HSCROLLBAR_HPP_ */
