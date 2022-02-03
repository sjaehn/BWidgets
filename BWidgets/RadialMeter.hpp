/* RadialMeter.hpp
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

#ifndef BWIDGETS_RADIALMETER_HPP_
#define BWIDGETS_RADIALMETER_HPP_

#include "Widget.hpp"
#include "Supports/Validatable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include <cairo/cairo.h>
#include <cmath>

#ifndef BWIDGETS_DEFAULT_RADIALMETER_WIDTH
#define BWIDGETS_DEFAULT_RADIALMETER_WIDTH 40.0
#endif

#ifndef BWIDGETS_DEFAULT_RADIALMETER_HEIGHT
#define BWIDGETS_DEFAULT_RADIALMETER_HEIGHT 40.0
#endif

#ifndef STYLEPROPERTY_HICOLORS_URI
#define STYLEPROPERTY_HICOLORS_URI STYLEPROPERTY_URI "#HiColors"
#endif

namespace BWidgets
{

/**
 *  @brief  %RadialMeter widget.
 *
 *  %RadialMeter is a Valueable Widget and displays a value as a radial
 *  meter without user interaction. The value is kept within a defined range
 *  and displayed in blocks defined by the parameter @a step . Its appearance
 *  is defined by the parameters BgColors (static elements), FgColors (value,
 *  low range), and HiColors (value, high range).
 *
 *  Advanced settings allow a %RadialMeter to display a value in a non-linear
 *  manner (e.g. for levels and frequencies) using transfer functions and / or
 *  to use non-line color gradients for display using gradient functions. 
 *
 *  @todo Inverse range, negative step.
 */
class RadialMeter :	public Widget, 
				public ValueableTyped<double>, 
				public ValidatableRange<double>, 
				public ValueTransferable<double>
{
protected:
	BUtilities::RectArea scale_;
	std::function<double (const double& x)> gradient_ = noTransfer;

public:

	/**
	 * @brief  Constructs a default %RadialMeter object.
	 * 
	 */
	RadialMeter ();

	/**
	 *  @brief  Creates a %RadialMeter with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	RadialMeter	(const double value, const double min, const double max, double step = 0.0, 
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %RadialMeter.
	 *  @param x  %RadialMeter X origin coordinate.
	 *  @param y  %RadialMeter Y origin coordinate.
	 *  @param width  %RadialMeter width.
	 *  @param height  %RadialMeter height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %RadialMeter title (default = "").
	 */
	RadialMeter	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %RadialMeter. 
	 *  @return  Pointer to the new %RadialMeter.
	 *
	 *  Creates a clone of this %RadialMeter by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %RadialMeter. 
	 *  @param that  Other %RadialMeter.
	 *
	 *  Copies all properties from another %RadialMeter. But NOT its linkage.
	 */
	void copy (const RadialMeter* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
     *  @brief  Gets the high range value colors Property from the base level.
     *  @return  High range value ColorMap.
     *
     *  Gets the base level high range value colors Property using the default 
     *  high range value colors URID. Returns FgColors if the default high 
	 *  range value  colors URID is not set.
     */
    BStyles::ColorMap getHiColors() const;

    /**
     *  @brief  Sets the high range value colors Property from the base level.
     *  @param colors  High range value ColorMap.
     *
     *  Sets the base level high range value colors Property using the default 
     *  high range value colors URID.
     */
    void setHiColors (const BStyles::ColorMap& colors);

	/**
	 *  @brief  Set the color gradient function.
	 *  @param gradientFunc  Color gradient function.
	 *
	 *  The color gradient function is responsible for the (optional) color 
	 *  transition from FgColors to HiColors (if defined). By default, the
	 *  gradient is a linear function ([] (const double& x) {return x;}).
	 */
	void setGradientFunction (std::function<double (const double& x)> gradientFunc)
	{
		gradient_ = gradientFunc;
	}

protected:
	/**
     *  @brief  Unclipped draw a %RadialMeter to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %RadialMeter to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %RadialMeter to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea& area) override;
};

inline RadialMeter::RadialMeter () :
	RadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_RADIALMETER_WIDTH, BWIDGETS_DEFAULT_RADIALMETER_HEIGHT, 
				 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 URID_UNKNOWN_URID, "")
{

}

inline RadialMeter::RadialMeter (double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	RadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_RADIALMETER_WIDTH, BWIDGETS_DEFAULT_RADIALMETER_HEIGHT, 
				 value, min, max, step, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 urid, title) 
{

}

inline RadialMeter::RadialMeter	(const double  x, const double y, const double width, const double height, 
								 double value, const double min, const double max, double step, 
								 std::function<double (const double& x)> transferFunc,
			 					 std::function<double (const double& x)> reTransferFunc,
								 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<double> (value),
	ValidatableRange<double> (min, max, step),
	ValueTransferable<double> (transferFunc, reTransferFunc),
	scale_ (0, 0, width, height)
{

}

inline Widget* RadialMeter::clone () const 
{
	Widget* f = new RadialMeter ();
	f->copy (this);
	return f;
}

inline void RadialMeter::copy (const RadialMeter* that)
{
	scale_ = that->scale_;
	gradient_ = that->gradient_;
	ValueTransferable<double>::operator= (*that);
	ValidatableRange<double>::operator= (*that);
	ValueableTyped<double>::operator= (*that);
	Widget::copy (that);
}

inline void RadialMeter::update ()
{
	scale_ = BUtilities::RectArea (getXOffset(), getYOffset(), getEffectiveWidth(), getEffectiveHeight());
	Widget::update();
}

inline BStyles::ColorMap RadialMeter::getHiColors() const
{
    BStyles::Style::const_iterator it = style_.find (BUtilities::Urid::urid (STYLEPROPERTY_HICOLORS_URI));
    if ((it == style_.end()) || style_.isStyle (it)) return getFgColors();
    else return it->second.get<BStyles::ColorMap>();
}

inline void RadialMeter::setHiColors (const BStyles::ColorMap& colors)
{
    style_[BUtilities::Urid::urid (STYLEPROPERTY_HICOLORS_URI)] = BUtilities::makeAny<BStyles::ColorMap> (colors);
}

inline void RadialMeter::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void RadialMeter::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea (x0, y0, width, height));
}

inline void RadialMeter::draw (const BUtilities::RectArea& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1) && (getMin() < getMax()))
	{
		cairo_t* cr = cairo_create (surface_);

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const double xc = 0.5 * scale_.getWidth();
			const double yc = 0.5 * scale_.getHeight();
			const double rad = 0.5 * (scale_.getWidth() < scale_.getHeight() ? scale_.getWidth() : scale_.getHeight());
			const double rval = getRatioFromValue (getValue(), transfer_);
			const double drv = (getStep() > 1.0 / (1.5 * M_PI * rad) ? getStep() / (getMax() - getMin()) : 1.0 / (1.5 * M_PI * rad));
			const double da = (1.5 * M_PI) * drv;
			const double sa = 1.0 / rad;
			const BStyles::Color fgHi = getFgColors()[getStatus()].illuminate (BStyles::Color::illuminated);
			const BStyles::Color fgLo = getFgColors()[getStatus()];
			const BStyles::Color hiHi = getHiColors()[getStatus()].illuminate (BStyles::Color::illuminated);
			const BStyles::Color hiLo = getHiColors()[getStatus()];
			const BStyles::Color bgLo = getBgColors()[getStatus()].illuminate (BStyles::Color::shadowed);
			const BStyles::Color bgHi = getBgColors()[getStatus()];
			const BStyles::Color bgDk = getBgColors()[getStatus()].illuminate (-0.75);

			// Background fill
    		cairo_set_line_width (cr, 0.0);
			cairo_set_source_rgba (cr, CAIRO_RGBA(bgDk));
			cairo_arc (cr, xc, yc, 0.96 * rad, 0.75 * M_PI, 2.25 * M_PI);
    		cairo_arc_negative (cr, xc, yc, 0.5 * rad, 2.25 * M_PI, 0.75 * M_PI);
			cairo_fill (cr);

			// Border
			cairo_pattern_t* pat = cairo_pattern_create_linear (xc - rad, yc - rad, xc + rad, yc + rad);
			if (pat && (cairo_pattern_status (pat) == CAIRO_STATUS_SUCCESS))
			{
				cairo_pattern_add_color_stop_rgba (pat, 0, CAIRO_RGBA(bgLo));
				cairo_pattern_add_color_stop_rgba (pat, 1, CAIRO_RGBA(bgHi));
				cairo_arc (cr, xc, yc, 0.96 * rad, 0.75 * M_PI, 2.25 * M_PI);
    			cairo_arc_negative (cr, xc, yc, 0.5 * rad, 2.25 * M_PI, 0.75 * M_PI);
				cairo_set_source (cr, pat);
				cairo_set_line_width (cr, 1.0);
				cairo_stroke (cr);
				cairo_pattern_destroy (pat);
			}

			// Fill
			cairo_set_line_width (cr, 0.0);
			cairo_pattern_t* fgPat = cairo_pattern_create_linear (xc - rad, yc - rad, xc + rad, yc + rad);
			cairo_pattern_t* bgPat = cairo_pattern_create_linear (xc - rad, yc - rad, xc + rad, yc + rad);
			if (fgPat && bgPat && (cairo_pattern_status (fgPat) == CAIRO_STATUS_SUCCESS) && (cairo_pattern_status (bgPat) == CAIRO_STATUS_SUCCESS))
			{
				cairo_pattern_add_color_stop_rgba (fgPat, 0, CAIRO_RGBA(fgLo));
				cairo_pattern_add_color_stop_rgba (fgPat, 0.25, CAIRO_RGBA(fgHi));
				cairo_pattern_add_color_stop_rgba (fgPat, 1, CAIRO_RGBA(fgLo));
				cairo_pattern_add_color_stop_rgba (bgPat, 0, CAIRO_RGBA(bgLo));
				cairo_pattern_add_color_stop_rgba (bgPat, 0.25, CAIRO_RGBA(bgHi));
				cairo_pattern_add_color_stop_rgba (bgPat, 1, CAIRO_RGBA(bgLo));

				for (double v = 0; v < 1.0; v += drv)
				{
					if (v <= rval) 
					{
						if ((fgHi != hiHi) || (fgLo != hiLo))
						{
							fgPat = cairo_pattern_create_linear (xc - rad, yc - rad, xc + rad, yc + rad);
							BStyles::Color cLo; 
							cLo.setHSV
							(
								fgLo.hue() * (1.0 - gradient_ (v)) + hiLo.hue() * gradient_ (v),
								fgLo.saturation() * (1.0 - gradient_ (v)) + hiLo.saturation() * gradient_ (v),
								fgLo.value() * (1.0 - gradient_ (v)) + hiLo.value() * gradient_ (v),
								fgLo.alpha * (1.0 - gradient_ (v)) + hiLo.alpha * gradient_ (v)
							);
							BStyles::Color cHi;
							cHi.setHSV
							(
								fgHi.hue() * (1.0 - gradient_ (v)) + hiHi.hue() * gradient_ (v),
								fgHi.saturation() * (1.0 - gradient_ (v)) + hiHi.saturation() * gradient_ (v),
								fgHi.value() * (1.0 - gradient_ (v)) + hiHi.value() * gradient_ (v),
								fgHi.alpha * (1.0 - gradient_ (v)) + hiHi.alpha * gradient_ (v)
							);

							cairo_pattern_add_color_stop_rgba (fgPat, 0, CAIRO_RGBA(cLo));
							cairo_pattern_add_color_stop_rgba (fgPat, 0.25, CAIRO_RGBA(cHi));
							cairo_pattern_add_color_stop_rgba (fgPat, 1, CAIRO_RGBA(cLo));
						}
						cairo_set_source (cr, fgPat);
					}

					else cairo_set_source (cr, bgPat);

					const double a = 0.75 * M_PI + v * (1.5 * M_PI);

					if (da < 3.0 * sa) 
					{
						cairo_arc (cr, xc, yc, 0.91 * rad, a, a + da);
    					cairo_arc_negative (cr, xc, yc, 0.55 * rad, a + da, a);
					}
					else 
					{
						cairo_arc (cr, xc, yc, 0.91 * rad, a + sa, a + da - sa);
    					cairo_arc_negative (cr, xc, yc, 0.55 * rad, a + da - sa, a + sa);
					}
					cairo_fill (cr);
				}

				cairo_pattern_destroy (bgPat);
				cairo_pattern_destroy (fgPat);
			}
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_RADIALMETER_HPP_ */
