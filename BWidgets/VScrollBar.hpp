/* VScrollBar.hpp
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

#ifndef BWIDGETS_VSCROLLBAR_HPP_
#define BWIDGETS_VSCROLLBAR_HPP_

#include "VScale.hpp"

#ifndef BWIDGETS_DEFAULT_VSCROLLBAR_WIDTH
#define BWIDGETS_DEFAULT_VSCROLLBAR_WIDTH BWIDGETS_DEFAULT_VSCALE_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_VSCROLLBAR_HEIGHT
#define BWIDGETS_DEFAULT_VSCROLLBAR_HEIGHT BWIDGETS_DEFAULT_VSCALE_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  %Vertical scroll bar widget.
 *
 *  %VScrollBar is a Valueable Widget derived from VScale. It displays a value
 *  as a vertical scrollbar and supports user interaction via Draggable, and 
 *  Scrollable. Its appearance is defined by the BgColors parameter.
 *
 *  The value can be point value (vsize = 0) or a range value (start value
 *  = widget value; end value = start value + vsize).
 */
class VScrollBar :	public VScale
{
protected:
	double vsize_;

public:

	/**
	 * @brief  Constructs a default %VScrollBar object.
	 * 
	 */
	VScrollBar ();

	/**
	 *  @brief  Constructs a default %VScrollBar object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	VScrollBar (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %VScrollBar with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param vsize  Optional, range covered by the value.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	VScrollBar	(const double value, const double min, const double max, double step = 0.0, double vsize = 0.0,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %VScrollBar.
	 *  @param x  %VScrollBar X origin coordinate.
	 *  @param y  %VScrollBar Y origin coordinate.
	 *  @param width  %VScrollBar width.
	 *  @param height  %VScrollBar height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param vsize  Optional, range covered by the value.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %VScrollBar title (default = "").
	 */
	VScrollBar	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0, double vsize = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %VScrollBar. 
	 *  @return  Pointer to the new %VScrollBar.
	 *
	 *  Creates a clone of this %VScrollBar by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %VScrollBar. 
	 *  @param that  Other %VScrollBar.
	 *
	 *  Copies all properties from another %VScrollBar. But NOT its linkage.
	 */
	void copy (const VScrollBar* that);

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
     *  @brief  Unclipped draw a %VScrollBar to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %VScrollBar to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %VScrollBar to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline VScrollBar::VScrollBar () :
	VScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_VSCROLLBAR_WIDTH, BWIDGETS_DEFAULT_VSCROLLBAR_HEIGHT, 
				 0.0, 0.0, 1.0, 0.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline VScrollBar::VScrollBar (const uint32_t urid, const std::string& title) : 
	VScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_VSCROLLBAR_WIDTH, BWIDGETS_DEFAULT_VSCROLLBAR_HEIGHT, 
				 0.0, 0.0, 1.0, 0.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 urid, title) 
{

}

inline VScrollBar::VScrollBar (const double value, const double min, const double max, double step, double vsize, uint32_t urid, std::string title) : 
	VScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_VSCROLLBAR_WIDTH, BWIDGETS_DEFAULT_VSCROLLBAR_HEIGHT, 
				 value, min, max, step, vsize,
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 urid, title) 
{

}

inline VScrollBar::VScrollBar	(const double  x, const double y, const double width, const double height, 
								 const double value, const double min, const double max, double step, double vsize,
								 std::function<double (const double& x)> transferFunc,
					 			 std::function<double (const double& x)> reTransferFunc,
								 uint32_t urid, std::string title) :
	VScale	(x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
	vsize_ (vsize)
{

}

inline Widget* VScrollBar::clone () const 
{
	Widget* f = new VScrollBar (urid_, title_);
	f->copy (this);
	return f;
}

inline void VScrollBar::copy (const VScrollBar* that)
{
	vsize_ = that->vsize_;
	VScale::copy (that);
}

inline void VScrollBar::setValueSize (const double& vsize)
{
	if (vsize_ != vsize)
	{
		vsize_ = vsize;
		update();
	}
}

inline void VScrollBar::onButtonPressed (BEvents::Event* event)
{
	// Bypass VScale::onButtonPressed()
	Clickable::onButtonPressed (event);
}

inline void VScrollBar::onPointerDragged (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (scale_.getHeight()) 
	{
		if (getStep() != 0.0) setValue (getValue() + pev->getDelta().y * getStep ());
		else setValue (getValueFromRatio (getRatioFromValue(getValue()) + pev->getDelta().y / scale_.getHeight()));
	}
	Draggable::onPointerDragged (event);
}

inline void VScrollBar::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void VScrollBar::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void VScrollBar::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1))
	{
		cairo_t* cr = cairo_create (cairoSurface());

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const double rval1 = (step_ >= 0.0 ? getRatioFromValue (getValue()) : 1.0 - getRatioFromValue (getValue() + vsize_));
			const double rval2 = (step_ >= 0.0 ? getRatioFromValue (getValue() + vsize_) : 1.0 - getRatioFromValue (getValue()));
			const BStyles::Color fgColor = getFgColors()[getStatus()];
			const BStyles::Color bgColor = getBgColors()[getStatus()];
			drawVBar
			(
				cr, 
				scale_.getX(), scale_.getY(), scale_.getWidth(), scale_.getHeight(), 
				rval1 * (1.0 - scale_.getWidth() / scale_.getHeight()), 
				rval2 * (1.0 - scale_.getWidth() / scale_.getHeight()) + scale_.getWidth() / scale_.getHeight(), 
				BWIDGETS_DEFAULT_SCROLLBAR_BAR_FGCOLOR, BWIDGETS_DEFAULT_SCROLLBAR_BAR_BGCOLOR
			);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_VSCROLLBAR_HPP_ */
