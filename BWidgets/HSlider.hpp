/* HSlider.hpp
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

#ifndef BWIDGETS_HSLIDER_HPP_
#define BWIDGETS_HSLIDER_HPP_

#include "HScale.hpp"
#include "Draws/drawKnob.hpp"

#ifndef BWIDGETS_DEFAULT_HSLIDER_WIDTH
#define BWIDGETS_DEFAULT_HSLIDER_WIDTH 80.0
#endif

#ifndef BWIDGETS_DEFAULT_HSLIDER_HEIGHT
#define BWIDGETS_DEFAULT_HSLIDER_HEIGHT 20.0
#endif

namespace BWidgets
{

/**
 *  @brief  %HSlider widget.
 *
 *  %HSlider is a HScale Widget. It displays a value as a horizontal
 *  slider and supports user interaction via Clickable, Draggable, and
 *  Scrollable. Its appearance is defined by the BgColors parameter (static
 *  elements, knob) and by the FgColors parameter (value). 
 *
 *  @todo Inverse range, negative step.
 */
class HSlider :	public HScale
{
public:

	/**
	 *  @brief  Constructs a default %HSlider object.
	 */
	HSlider ();

	/**
	 *  @brief  Constructs a default %HSlider object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	HSlider (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %HSlider with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HSlider	(const double value, const double min, const double max, double step = 0.0, 
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HSlider.
	 *  @param x  %HSlider X origin coordinate.
	 *  @param y  %HSlider Y origin coordinate.
	 *  @param width  %HSlider width.
	 *  @param height  %HSlider height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %HSlider title (default = "").
	 */
	HSlider	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %HSlider. 
	 *  @return  Pointer to the new %HSlider.
	 *
	 *  Creates a clone of this %HSlider by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %HSlider. 
	 *  @param that  Other %HSlider.
	 *
	 *  Copies all properties from another %HSlider. But NOT its linkage.
	 */
	void copy (const HSlider* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

protected:
	/**
     *  @brief  Unclipped draw a %HSlider to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %HSlider to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %HSlider to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline HSlider::HSlider () :
	HSlider	(0.0, 0.0, BWIDGETS_DEFAULT_HSLIDER_WIDTH, BWIDGETS_DEFAULT_HSLIDER_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 URID_UNKNOWN_URID, "")
{

}

inline HSlider::HSlider (const uint32_t urid, const std::string& title) : 
	HSlider	(0.0, 0.0, BWIDGETS_DEFAULT_HSLIDER_WIDTH, BWIDGETS_DEFAULT_HSLIDER_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{
	
}

inline HSlider::HSlider (double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	HSlider	(0.0, 0.0, BWIDGETS_DEFAULT_HSLIDER_WIDTH, BWIDGETS_DEFAULT_HSLIDER_HEIGHT, 
			 value, min, max, step, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline HSlider::HSlider	(const double  x, const double y, const double width, const double height, 
						 double value, const double min, const double max, double step, 
						 std::function<double (const double& x)> transferFunc,
			 			 std::function<double (const double& x)> reTransferFunc,
						 uint32_t urid, std::string title) :
		HScale (x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title)
{
	scale_ = BUtilities::Area<> (0.5 * height, 0.25 * height, width - height, 0.5 * height);
}

inline Widget* HSlider::clone () const 
{
	Widget* f = new HSlider (urid_, title_);
	f->copy (this);
	return f;
}

inline void HSlider::copy (const HSlider* that)
{
	HScale::copy (that);
}

inline void HSlider::update ()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + std::to_string (this->getValue()));
		f->resize();
	}

	scale_ = BUtilities::Area<> 
	(
		getXOffset() + 0.5 * getEffectiveHeight(), 
		getYOffset() + 0.25 * getEffectiveHeight(), 
		getEffectiveWidth() - getEffectiveHeight(), 
		0.5 * getEffectiveHeight()
	);
	Widget::update();
}

inline void HSlider::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void HSlider::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void HSlider::draw (const BUtilities::Area<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	HScale::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1))
	{
		cairo_t* cr = cairo_create (surface_);
		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const BStyles::Color bgColor = getBgColors()[getStatus()];
			const double rval = getRatioFromValue (getValue(), transfer_);
			drawKnob (cr, scale_.getX() + rval * scale_.getWidth(), scale_.getY() + 0.5 * scale_.getHeight() + 0.5, scale_.getHeight() - 1.0, 1.0, bgColor, bgColor);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_HSLIDER_HPP_ */
