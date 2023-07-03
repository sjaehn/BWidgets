/* ImageVMeter.hpp
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

#ifndef BWIDGETS_IMAGEVMETER_HPP_
#define BWIDGETS_IMAGEVMETER_HPP_

#include "Widget.hpp"
#include "Label.hpp"
#include "Supports/Validatable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include <cairo/cairo.h>
#include <utility>

#ifndef BWIDGETS_DEFAULT_IMAGEVMETER_WIDTH
#define BWIDGETS_DEFAULT_IMAGEVMETER_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_IMAGEVMETER_HEIGHT
#define BWIDGETS_DEFAULT_IMAGEVMETER_HEIGHT 80.0
#endif

namespace BWidgets
{

/**
 *  @brief  %ImageVMeter widget.
 *
 *  %ImageVMeter is a Valueable Widget and displays a value as a vertical
 *  meter based on images. The visual output is constructed using three
 *  freely selectable images along the provided anchor points:
 *  * static: All static elements in a passive state (background, labels, 
 *    scales, ...).
 *  * active: All static elements in an active state (LEDs, ...).
 *  * dynamic: The dymacic element (sliding contoller, ...).
 *
 *  %ImageVMeter itself doesn't possess any user interaction. The value is 
 *  kept within a defined range and is displayed by the value-dependently
 *  cropped active image and by the position of the dynamic image.
 *
 *  Advanced settings allow an %ImageVMeter to display a value in a non-linear
 *  manner (e.g. for levels and frequencies) using transfer functions and / or
 *  to use non-line color gradients for display using gradient functions. 
 */
class ImageVMeter :	public Widget, 
				public ValueableTyped<double>, 
				public ValidatableRange<double>, 
				public ValueTransferable<double>
{
protected:
	std::pair<BUtilities::Point<>, BUtilities::Point<>> staticAnchors_;
	BUtilities::Point<> activeAnchor_;
	BUtilities::Point<> dynamicAnchor_;
	cairo_surface_t* staticImageSurface_;
	cairo_surface_t* activeImageSurface_;
	cairo_surface_t* dynamicImageSurface_;

public:

	/**
	 * @brief  Constructs an empty %ImageVMeter object.
	 * 
	 */
	ImageVMeter ();

	/**
	 *  @brief  Constructs an empty %ImageVMeter object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ImageVMeter (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ImageVMeter with default size.
	 *  @param staticImage  Filename of the static passive content image.
	 *  @param staticAnchors  Anchor points of the static passive content 
	 *  (std::pair of position for the min value and position of the max 
	 *  value).
	 *  @param activeImage  Optional, filename of the static active content 
	 *  image.
	 *  @param activeAnchor  Optional, anchor point of the static active
	 *  content which fits to the min value.
	 *  @param dynamicImage  Optional, filename of the dynamic content image.
	 *  @param dynamicAnchor  Optional, anchor point of the dynamic content
	 *  (position anchored along the min value to max value line).
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Note: It's mandatory to provide an image for the static passive content
	 *  @a staticImage (background, labels, ...) and its anchor points for the
	 *  min value and the max value. The image area of @a staticImage MUST
	 *  cover ALL possible positions of the static active content 
	 *  @a activeImage and the dynamic content @a dynamicImage.
	 */
	ImageVMeter	(const std::string staticImage, const std::pair<BUtilities::Point<>, BUtilities::Point<>> staticAnchors,
				 std::string activeImage = "", BUtilities::Point<> activeAnchor = {0,0},
				 std::string dynamicImage = "", BUtilities::Point<> dynamicAnchor = {0,0},
				 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageVMeter.
	 *  @param x  %ImageVMeter X origin coordinate.
	 *  @param y  %ImageVMeter Y origin coordinate.
	 *  @param width  %ImageVMeter width.
	 *  @param height  %ImageVMeter height.
	 *  @param staticImage  Filename of the static passive content image.
	 *  @param staticAnchors  Anchor points of the static passive content 
	 *  (std::pair of position for the min value and position of the max 
	 *  value).
	 *  @param activeImage  Optional, filename of the static active content 
	 *  image.
	 *  @param activeAnchor  Optional, anchor point of the static active
	 *  content which fits to the min value.
	 *  @param dynamicImage  Optional, filename of the dynamic content image.
	 *  @param dynamicAnchor  Optional, anchor point of the dynamic content
	 *  (position anchored along the min value to max value line).
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %ImageVMeter title (default = "").
	 *
	 *  Note: It's mandatory to provide an image for the static passive content
	 *  @a staticImage (background, labels, ...) and its anchor points for the
	 *  min value and the max value. The image area of @a staticImage MUST
	 *  cover ALL possible positions of the static active content 
	 *  @a activeImage and the dynamic content @a dynamicImage.
	 */
	ImageVMeter	(const double x, const double y, const double width, const double height, 
				 const std::string staticImage, const std::pair<BUtilities::Point<>, BUtilities::Point<>> staticAnchors,
				 std::string activeImage = "", BUtilities::Point<> activeAnchor = {0,0},
				 std::string dynamicImage = "", BUtilities::Point<> dynamicAnchor = {0,0},
				 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
				 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
				 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	virtual ~ImageVMeter();

	/**
	 *  @brief  Creates a clone of the %ImageVMeter. 
	 *  @return  Pointer to the new %ImageVMeter.
	 *
	 *  Creates a clone of this %ImageVMeter by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ImageVMeter. 
	 *  @param that  Other %ImageVMeter.
	 *
	 *  Copies all properties from another %ImageVMeter. But NOT its linkage.
	 */
	void copy (const ImageVMeter* that);
	
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
     *  @brief  Unclipped draw a %ImageVMeter to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %ImageVMeter to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %ImageVMeter to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline ImageVMeter::ImageVMeter () :
	ImageVMeter	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGEVMETER_WIDTH, BWIDGETS_DEFAULT_IMAGEVMETER_HEIGHT,
				 "", std::pair<BUtilities::Point<>, BUtilities::Point<>> ({0,0}, {0,0}),
				 "", BUtilities::Point<> (0,0),
				 "", BUtilities::Point<> (0,0),
				 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline ImageVMeter::ImageVMeter (const uint32_t urid, const std::string& title) : 
	ImageVMeter	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGEVMETER_WIDTH, BWIDGETS_DEFAULT_IMAGEVMETER_HEIGHT,
				 "", std::pair<BUtilities::Point<>, BUtilities::Point<>> ({0,0}, {0,0}),
				 "", BUtilities::Point<> (0,0),
				 "", BUtilities::Point<> (0,0),
				 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 urid, title)
{

}

inline ImageVMeter::ImageVMeter (const std::string staticImage, const std::pair<BUtilities::Point<>, BUtilities::Point<>> staticAnchors,
								 std::string activeImage, BUtilities::Point<> activeAnchor,
								 std::string dynamicImage, BUtilities::Point<> dynamicAnchor,
								 double value, const double min, const double max, double step, 
								 uint32_t urid, std::string title) : 
	ImageVMeter	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGEVMETER_WIDTH, BWIDGETS_DEFAULT_IMAGEVMETER_HEIGHT,
				 staticImage, staticAnchors, activeImage, activeAnchor, dynamicImage, dynamicAnchor,
				 value, min, max, step, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 urid, title) 
{

}

inline ImageVMeter::ImageVMeter	(const double  x, const double y, const double width, const double height, 
								 const std::string staticImage, const std::pair<BUtilities::Point<>, BUtilities::Point<>> staticAnchors,
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
	staticAnchors_(staticAnchors),
	activeAnchor_(activeAnchor),
	dynamicAnchor_(dynamicAnchor),
	staticImageSurface_(staticImage != "" ? cairo_image_surface_create_from_png (staticImage.c_str()) : nullptr),
	activeImageSurface_(staticImage != "" ? cairo_image_surface_create_from_png (activeImage.c_str()) : nullptr),
	dynamicImageSurface_(staticImage != "" ? cairo_image_surface_create_from_png (dynamicImage.c_str()) : nullptr)
{
	setFocusText([](const Widget* w) {return	w->getTitle() + 
												": " + 
												(dynamic_cast<const ImageVMeter*>(w) ? 
												 std::to_string (dynamic_cast<const ImageVMeter*>(w)->getValue()) : 
												 "");});
}

inline ImageVMeter::~ImageVMeter()
{
	if (staticImageSurface_ && (cairo_surface_status(staticImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (staticImageSurface_);
	if (activeImageSurface_ && (cairo_surface_status(activeImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (activeImageSurface_);
	if (dynamicImageSurface_ && (cairo_surface_status(dynamicImageSurface_) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (dynamicImageSurface_);
}

inline Widget* ImageVMeter::clone () const 
{
	Widget* f = new ImageVMeter (urid_, title_);
	f->copy (this);
	return f;
}

inline void ImageVMeter::copy (const ImageVMeter* that)
{
	staticAnchors_ = that->staticAnchors_;
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

inline void ImageVMeter::resize ()
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

inline void ImageVMeter::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void ImageVMeter::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void ImageVMeter::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void ImageVMeter::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void ImageVMeter::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1) && (getMin() < getMax()))
	{
		cairo_t* cr = cairo_create (cairoSurface());

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			cairo_scale (cr, surface_.scale, surface_.scale);
			
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const double x0 = getXOffset();
			const double y0 = getYOffset();
			const double w = getEffectiveWidth();
			const double h = getEffectiveHeight();
			const double rval = getRatioFromValue (getValue());
			const double ws = cairo_image_surface_get_width (staticImageSurface_);
			const double hs = cairo_image_surface_get_height (staticImageSurface_);

			if (staticImageSurface_ && (cairo_surface_status (staticImageSurface_) == CAIRO_STATUS_SUCCESS) && (ws >= 1.0) && (hs >= 1.0))
			{
				const double szs = ((w / ws < h / hs) ? (w / ws) : (h / hs));
				const double x0s = x0 + 0.5 * w - 0.5 * ws * szs;
				const double y0s = y0 + 0.5 * h - 0.5 * hs * szs;
				const BUtilities::Point<> anchorv = BUtilities::Point<>	
				(
					staticAnchors_.first != staticAnchors_.second ?
					staticAnchors_.first + (step_ >= 0 ? rval : 1.0 - rval) * (staticAnchors_.second - staticAnchors_.first) :
					staticAnchors_.first
				);

				cairo_save (cr);
				cairo_translate(cr, x0s, y0s);
				cairo_scale (cr, szs, szs);
				cairo_set_source_surface(cr, staticImageSurface_, 0, 0);
				cairo_paint (cr);
				cairo_restore (cr);

				if (activeImageSurface_ && (cairo_surface_status (activeImageSurface_) == CAIRO_STATUS_SUCCESS))
				{
					const double x0a = x0s + (staticAnchors_.first.x - activeAnchor_.x) * szs;
					const double y0a = y0s + (staticAnchors_.first.y - activeAnchor_.y) * szs;
					const double y0a0 = y0s + (step_ >= 0 ? staticAnchors_.first.y : anchorv.y) * szs;
					const double y0av = y0s + (step_ >= 0 ? anchorv.y : staticAnchors_.second.y) * szs;
					cairo_save (cr);
					cairo_rectangle (cr, x0, y0a0, w, y0av - y0a0);
					cairo_translate(cr, x0a, y0a);
					cairo_scale (cr, szs, szs);
					cairo_set_source_surface(cr, activeImageSurface_, 0, 0);
					cairo_set_line_width (cr, 0.0);
					cairo_fill (cr);
					cairo_restore (cr);
				}

				if (dynamicImageSurface_ && (cairo_surface_status (dynamicImageSurface_) == CAIRO_STATUS_SUCCESS))
				{
					const double x0d = x0s + (anchorv.x - dynamicAnchor_.x) * szs;
					const double y0d = y0s + (anchorv.y - dynamicAnchor_.y) * szs;
					cairo_save (cr);
					cairo_translate(cr, x0d, y0d);
					cairo_scale (cr, szs, szs);
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

#endif /* BWIDGETS_IMAGEVMETER_HPP_ */
