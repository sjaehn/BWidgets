/* VSlider.hpp
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

#ifndef BWIDGETS_VSLIDER_HPP_
#define BWIDGETS_VSLIDER_HPP_

#ifndef BWIDGETS_DEFAULT_DRAWKNOB_PATH
#define BWIDGETS_DEFAULT_DRAWKNOB_PATH "Draws/Ergo/drawKnob.hpp"
#endif

#include "VScale.hpp"
#include BWIDGETS_DEFAULT_DRAWKNOB_PATH

#ifndef BWIDGETS_DEFAULT_VSLIDER_WIDTH
#define BWIDGETS_DEFAULT_VSLIDER_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_VSLIDER_HEIGHT
#define BWIDGETS_DEFAULT_VSLIDER_HEIGHT 80.0
#endif

namespace BWidgets
{

/**
 *  @brief  %VSlider widget.
 *
 *  %VSlider is a VScale Widget. It displays a value as a horizontal
 *  slider and supports user interaction via Clickable, Draggable, and
 *  Scrollable. Its appearance is defined by the BgColors parameter (static
 *  elements, knob) and by the FgColors parameter (value). 
 */
class VSlider :	public VScale
{
public:

	/**
	 * @brief  Constructs a default %VSlider object.
	 * 
	 */
	VSlider ();

	/**
	 *  @brief  Constructs a default %VSlider object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	VSlider (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %VSlider with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	VSlider	(const double value, const double min, const double max, double step = 0.0, 
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %VSlider.
	 *  @param x  %VSlider X origin coordinate.
	 *  @param y  %VSlider Y origin coordinate.
	 *  @param width  %VSlider width.
	 *  @param height  %VSlider height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %VSlider title (default = "").
	 */
	VSlider	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %VSlider. 
	 *  @return  Pointer to the new %VSlider.
	 *
	 *  Creates a clone of this %VSlider by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %VSlider. 
	 *  @param that  Other %VSlider.
	 *
	 *  Copies all properties from another %VSlider. But NOT its linkage.
	 */
	void copy (const VSlider* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:
	/**
     *  @brief  Unclipped draw a %VSlider to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %VSlider to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %VSlider to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline VSlider::VSlider () :
	VSlider	(0.0, 0.0, BWIDGETS_DEFAULT_VSLIDER_WIDTH, BWIDGETS_DEFAULT_VSLIDER_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline VSlider::VSlider (const uint32_t urid, const std::string& title) : 
	VSlider	(0.0, 0.0, BWIDGETS_DEFAULT_VSLIDER_WIDTH, BWIDGETS_DEFAULT_VSLIDER_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline VSlider::VSlider (const double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	VSlider	(0.0, 0.0, BWIDGETS_DEFAULT_VSLIDER_WIDTH, BWIDGETS_DEFAULT_VSLIDER_HEIGHT, 
			 value, min, max, step, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline VSlider::VSlider	(const double  x, const double y, const double width, const double height, 
						 const double value, const double min, const double max, double step, 
						 std::function<double (const double& x)> transferFunc,
			 			 std::function<double (const double& x)> reTransferFunc,
						 uint32_t urid, std::string title) :
		VScale (x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title)
{
	scale_ = BUtilities::Area<> (0.25 * width, 0.5 * width, 0.5 * width, height - width);
}

inline Widget* VSlider::clone () const 
{
	Widget* f = new VSlider (urid_, title_);
	f->copy (this);
	return f;
}

inline void VSlider::copy (const VSlider* that)
{
	VScale::copy (that);
}

inline void VSlider::update ()
{
	scale_ = BUtilities::Area<> 
	(
		getXOffset() + (0.5 - 0.5 * BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE) * getEffectiveWidth(), 
		getYOffset() + 0.5 * getEffectiveWidth(), 
		BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE * getEffectiveWidth(),
		getEffectiveHeight() - getEffectiveWidth()
	);
	Widget::update();
}

inline void VSlider::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void VSlider::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void VSlider::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	VScale::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1))
	{
		cairo_t* cr = cairo_create (cairoSurface());
		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const double rval = getRatioFromValue (getValue());

			if (step_ >= 0.0) drawKnob	(cr, 
										 scale_.getX() + 0.5 * scale_.getWidth(), 
										 scale_.getY() + (1.0 - rval) * scale_.getHeight(), 
										 0.5 * (BWIDGETS_DEFAULT_SLIDER_KNOB_REL_SIZE /BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE) * (scale_.getWidth() - 1.0), 
										 1.0, 
										 BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR, BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR);

			else drawKnob				(cr, 
										 scale_.getX() + 0.5 * scale_.getWidth(), 
										 scale_.getY() + rval * scale_.getHeight(), 
										 0.5 * (BWIDGETS_DEFAULT_SLIDER_KNOB_REL_SIZE / BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE) * (scale_.getWidth() - 1.0), 
										 1.0, 
										 BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR, BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR);

		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_VSLIDER_HPP_ */
