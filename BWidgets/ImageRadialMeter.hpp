/* ImageRadialMeter.hpp
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

#ifndef BWIDGETS_IMAGERADIALMETER_HPP_
#define BWIDGETS_IMAGERADIALMETER_HPP_

#include "Widget.hpp"
#include "Supports/Validatable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include <cairo/cairo.h>
#include <cmath>
#include <utility>

#ifndef BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH
#define BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH 60.0
#endif

#ifndef BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT
#define BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT 60.0
#endif

namespace BWidgets
{

/**
 *  @brief  %ImageRadialMeter widget.
 *
 *  %ImageRadialMeter is a Valueable Widget and displays a value as a radial
 *  meter based on images. The visual output is constructed using three
 *  freely selectable images by rotation around the provided anchor points:
 *  * static: All static elements in a passive state (background, labels, 
 *    scales, ...).
 *  * active: All static elements in an active state (LEDs, ...).
 *  * dynamic: The dymacic element (sliding contoller, ...).
 *
 *  %ImageRadialMeter itself doesn't possess any user interaction. The value is 
 *  kept within a defined range and is displayed by the value-dependently
 *  cropped active image (pie sliced) and by the position of the dynamic image
 *  (rotated around the anchor).
 *
 *  Advanced settings allow an %ImageRadialMeter to display a value in a non-linear
 *  manner (e.g. for levels and frequencies) using transfer functions and / or
 *  to use non-line color gradients for display using gradient functions. 
 *
 *  @todo Inverse range, negative step.
 */
class ImageRadialMeter :	public Widget, 
							public ValueableTyped<double>, 
							public ValidatableRange<double>, 
							public ValueTransferable<double>
{
protected:
	BUtilities::Point<> staticAnchor_;
	double staticMinAngle_;
	double staticMaxAngle_;
	BUtilities::Point<> activeAnchor_;
	BUtilities::Point<> dynamicAnchor_;
	cairo_surface_t* staticImageSurface_;
	cairo_surface_t* activeImageSurface_;
	cairo_surface_t* dynamicImageSurface_;

public:

	/**
	 * @brief  Constructs an empty %ImageRadialMeter object.
	 * 
	 */
	ImageRadialMeter ();

	/**
	 *  @brief  Constructs an empty %ImageRadialMeter object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ImageRadialMeter (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ImageRadialMeter with default size.
	 *  @param staticImage  Filename of the static passive content image.
	 *  @param staticAnchor  Anchor point of the static active content which 
	 *  also represents the center of rotation
	 *  @param staticMinAngle  Angle for the min value.
	 *  @param staticMaxAngle  Angle for the max value.
	 *  @param activeImage  Optional, filename of the static active content 
	 *  image.
	 *  @param activeAnchor  Optional, anchor point of the static active
	 *  content which fits to center of rotation.
	 *  @param dynamicImage  Optional, filename of the dynamic content image.
	 *  @param dynamicAnchor  Optional, anchor point of the dynamic content
	 *  which fits to center of rotation.
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Note: It's mandatory to provide an image for the static passive content
	 *  @a staticImage (background, labels, ...) and its anchor points for the
	 *  min value and the max value. The image area of @a staticImage MUST
	 *  cover ALL possible positions of the static active content 
	 *  @a activeImage and the dynamic content @a dynamicImage.
	 */
	ImageRadialMeter	(const std::string staticImage, const BUtilities::Point<> staticAnchor, const double staticMinAngle, const double staticMaxAngle,
						 std::string activeImage = "", BUtilities::Point<> activeAnchor = {0,0},
						 std::string dynamicImage = "", BUtilities::Point<> dynamicAnchor = {0,0},
						 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
						 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageRadialMeter.
	 *  @param x  %ImageRadialMeter X origin coordinate.
	 *  @param y  %ImageRadialMeter Y origin coordinate.
	 *  @param width  %ImageRadialMeter width.
	 *  @param height  %ImageRadialMeter height.
	 *  @param staticImage  Filename of the static passive content image.
	 *  @param staticAnchor  Anchor point of the static active content which 
	 *  also represents the center of rotation
	 *  @param staticMinAngle  Angle for the min value.
	 *  @param staticMaxAngle  Angle for the max value.
	 *  @param activeImage  Optional, filename of the static active content 
	 *  image.
	 *  @param activeAnchor  Optional, anchor point of the static active
	 *  content which fits to center of rotation.
	 *  @param dynamicImage  Optional, filename of the dynamic content image.
	 *  @param dynamicAnchor  Optional, anchor point of the dynamic content
	 *  which fits to center of rotation.
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %ImageRadialMeter title (default = "").
	 *
	 *  Note: It's mandatory to provide an image for the static passive content
	 *  @a staticImage (background, labels, ...) and its anchor points for the
	 *  min value and the max value. The image area of @a staticImage MUST
	 *  cover ALL possible positions of the static active content 
	 *  @a activeImage and the dynamic content @a dynamicImage.
	 */
	ImageRadialMeter	(const double x, const double y, const double width, const double height, 
						 const std::string staticImage, const BUtilities::Point<> staticAnchor, const double staticMinAngle, const double staticMaxAngle,
						 std::string activeImage = "", BUtilities::Point<> activeAnchor = {0,0},
						 std::string dynamicImage = "", BUtilities::Point<> dynamicAnchor = {0,0},
						 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
						 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
						 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
						 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	virtual ~ImageRadialMeter();

	/**
	 *  @brief  Creates a clone of the %ImageRadialMeter. 
	 *  @return  Pointer to the new %ImageRadialMeter.
	 *
	 *  Creates a clone of this %ImageRadialMeter by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ImageRadialMeter. 
	 *  @param that  Other %ImageRadialMeter.
	 *
	 *  Copies all properties from another %ImageRadialMeter. But NOT its linkage.
	 */
	void copy (const ImageRadialMeter* that);
	
	/**
     *  @brief  Optimizes the object extends.
     *
     *  Resizes the widget to fit the static passive image. Resizes to (0, 0)
	 *  if no image is stored.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the object extends.
	 *  @param width  New object width.
	 *  @param height  New object height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the object extends.
	 *  @param extends  New object extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

protected:
	/**
     *  @brief  Unclipped draw a %ImageRadialMeter to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %ImageRadialMeter to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %ImageRadialMeter to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline ImageRadialMeter::ImageRadialMeter () :
	ImageRadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH, BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT,
						 "", BUtilities::Point<>(0,0), 0.0, 2.0 * M_PI,
						 "", BUtilities::Point<> (0,0),
						 "", BUtilities::Point<> (0,0),
						 0.0, 0.0, 1.0, 0.0, 
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
						 URID_UNKNOWN_URID, "")
{

}

inline ImageRadialMeter::ImageRadialMeter (const uint32_t urid, const std::string& title) : 
	ImageRadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH, BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT,
						 "", BUtilities::Point<>(0,0), 0.0, 2.0 * M_PI,
						 "", BUtilities::Point<> (0,0),
						 "", BUtilities::Point<> (0,0),
						 0.0, 0.0, 1.0, 0.0, 
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
						 urid, title)
{

}

inline ImageRadialMeter::ImageRadialMeter (const std::string staticImage, const BUtilities::Point<> staticAnchor, 
								 const double staticMinAngle, const double staticMaxAngle,
								 std::string activeImage, BUtilities::Point<> activeAnchor,
								 std::string dynamicImage, BUtilities::Point<> dynamicAnchor,
								 double value, const double min, const double max, double step, 
								 uint32_t urid, std::string title) : 
	ImageRadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH, BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT,
						 staticImage, staticAnchor, staticMinAngle, staticMaxAngle, 
						 activeImage, activeAnchor, dynamicImage, dynamicAnchor,
						 value, min, max, step, 
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
						 urid, title) 
{

}

inline ImageRadialMeter::ImageRadialMeter	(const double  x, const double y, const double width, const double height, 
											 const std::string staticImage, const BUtilities::Point<> staticAnchor, 
											 const double staticMinAngle, const double staticMaxAngle,
											 std::string activeImage, BUtilities::Point<> activeAnchor,
											 std::string dynamicImage, BUtilities::Point<> dynamicAnchor,
											 double value, const double min, const double max, double step,
											 std::function<double (const double& x)> transferFunc,
								 			 std::function<double (const double& x)> reTransferFunc, 
											 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<double> (value),
	ValidatableRange<double> (min, max, step),
	ValueTransferable<double> (transferFunc, reTransferFunc),
	staticAnchor_(staticAnchor),
	staticMinAngle_(staticMinAngle),
	staticMaxAngle_(staticMaxAngle),
	activeAnchor_(activeAnchor),
	dynamicAnchor_(dynamicAnchor),
	staticImageSurface_(staticImage != "" ? cairo_image_surface_create_from_png (staticImage.c_str()) : nullptr),
	activeImageSurface_(staticImage != "" ? cairo_image_surface_create_from_png (activeImage.c_str()) : nullptr),
	dynamicImageSurface_(staticImage != "" ? cairo_image_surface_create_from_png (dynamicImage.c_str()) : nullptr)
{

}

inline ImageRadialMeter::~ImageRadialMeter()
{
	if (staticImageSurface_ && (cairo_surface_status(staticImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (staticImageSurface_);
	if (activeImageSurface_ && (cairo_surface_status(activeImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (activeImageSurface_);
	if (dynamicImageSurface_ && (cairo_surface_status(dynamicImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (dynamicImageSurface_);
}

inline Widget* ImageRadialMeter::clone () const 
{
	Widget* f = new ImageRadialMeter (urid_, title_);
	f->copy (this);
	return f;
}

inline void ImageRadialMeter::copy (const ImageRadialMeter* that)
{
	staticAnchor_ = that->staticAnchor_;
	staticMinAngle_ = that->staticMinAngle_;
	staticMaxAngle_ = that->staticMaxAngle_;
	activeAnchor_ = that->activeAnchor_;
	dynamicAnchor_ = that->dynamicAnchor_;
	if (staticImageSurface_ && (cairo_surface_status(staticImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (staticImageSurface_);
	staticImageSurface_ = cairoplus_image_surface_clone_from_image_surface (that->staticImageSurface_);
	if (activeImageSurface_ && (cairo_surface_status(activeImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (activeImageSurface_);
	activeImageSurface_ = cairoplus_image_surface_clone_from_image_surface (that->activeImageSurface_);
	if (dynamicImageSurface_ && (cairo_surface_status(dynamicImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (dynamicImageSurface_);
	dynamicImageSurface_ = cairoplus_image_surface_clone_from_image_surface (that->dynamicImageSurface_);
	ValueTransferable<double>::operator= (*that);
	ValidatableRange<double>::operator= (*that);
	ValueableTyped<double>::operator= (*that);
	Widget::copy (that);
}

inline void ImageRadialMeter::resize ()
{
	BUtilities::Area<> a =	(staticImageSurface_ && (cairo_surface_status(staticImageSurface_) == CAIRO_STATUS_SUCCESS) ?
			  				 BUtilities::Area<>	(0.0, 0.0,
								   				 cairo_image_surface_get_width (staticImageSurface_) + 2.0 * getXOffset(), 
												 cairo_image_surface_get_height (staticImageSurface_) + 2.0 * getYOffset()) :
			  				 BUtilities::Area<>	());
							   
	for (Linkable* l : children_)
	{
		Widget* w = dynamic_cast<Widget*>(l);
		if (w)  a += w->getArea();
	}

	resize (a.getExtends());
}

inline void ImageRadialMeter::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void ImageRadialMeter::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void ImageRadialMeter::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void ImageRadialMeter::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void ImageRadialMeter::draw (const BUtilities::Area<>& area)
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

			const double x0 = getXOffset();
			const double y0 = getYOffset();
			const double w = getEffectiveWidth();
			const double h = getEffectiveHeight();
			const double rval = getRatioFromValue (getValue(), transfer_);
			const double ws = cairo_image_surface_get_width (staticImageSurface_);
			const double hs = cairo_image_surface_get_height (staticImageSurface_);

			if (staticImageSurface_ && (cairo_surface_status (staticImageSurface_) == CAIRO_STATUS_SUCCESS) && (ws >= 1.0) && (hs >= 1.0))
			{
				const double szs = ((w / ws < h / hs) ? (w / ws) : (h / hs));
				const double x0s = x0 + 0.5 * w - 0.5 * ws * szs;
				const double y0s = y0 + 0.5 * h - 0.5 * hs * szs;
				cairo_save (cr);
				cairo_translate(cr, x0s, y0s);
				cairo_scale (cr, szs, szs);
				cairo_set_source_surface(cr, staticImageSurface_, 0, 0);
				cairo_paint (cr);
				cairo_restore (cr);

				if (activeImageSurface_ && (cairo_surface_status (activeImageSurface_) == CAIRO_STATUS_SUCCESS))
				{
					const double x0a = x0s + (staticAnchor_.x - activeAnchor_.x) * szs;
					const double y0a = y0s + (staticAnchor_.y - activeAnchor_.y) * szs;
					const double xca = x0a + activeAnchor_.x * szs;
					const double yca = y0a + activeAnchor_.y * szs;
					const double rad =
					(
						xca > x0a + 0.5 * ws * szs ?
						(
							yca > y0a + 0.5 * hs * szs ?
							sqrt (pow (xca - x0a, 2.0) + pow (yca - y0a, 2.0)) :
							sqrt (pow (xca - x0a, 2.0) + pow (yca - (y0a + hs * szs), 2.0))
						) :
						(
							yca > y0a + 0.5 * hs * szs ?
							sqrt (pow (xca - (x0a + ws * szs), 2.0) + pow (yca - y0a, 2.0)) :
							sqrt (pow (xca -  (x0a + ws * szs), 2.0) + pow (yca - (y0a + hs * szs), 2.0))
						)
					);
					cairo_save (cr);
					cairo_move_to (cr, xca, yca);
					cairo_arc (cr, xca, yca, rad, staticMinAngle_, staticMinAngle_ + (staticMaxAngle_ - staticMinAngle_) * rval);
					cairo_close_path (cr);
					cairo_translate(cr, x0a, y0a);
					cairo_scale (cr, szs, szs);
					cairo_set_source_surface(cr, activeImageSurface_, 0, 0);
					cairo_set_line_width (cr, 0.0);
					cairo_fill (cr);
					cairo_restore (cr);
				}

				if (dynamicImageSurface_ && (cairo_surface_status (dynamicImageSurface_) == CAIRO_STATUS_SUCCESS))
				{
					const double ad = (staticMaxAngle_ - staticMinAngle_) * rval;
					cairo_save (cr);

					cairo_translate (cr, x0s + staticAnchor_.x * szs, y0s + staticAnchor_.y * szs);
					cairo_scale (cr, szs, szs);
					cairo_rotate (cr, ad);
					cairo_translate (cr, -dynamicAnchor_.x, -dynamicAnchor_.y);
					cairo_set_source_surface(cr, dynamicImageSurface_, 0, 0);
					cairo_paint (cr);
					cairo_restore (cr);
				}
			}
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_IMAGERADIALMETER_HPP_ */
