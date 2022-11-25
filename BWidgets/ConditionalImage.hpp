/* ConditionalImage.hpp
 * Copyright (C) 2019 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_IMAGECONDITIONAL_HPP_
#define BWIDGETS_IMAGECONDITIONAL_HPP_

#include "Widget.hpp"
#include "Label.hpp"
#include <algorithm>
#include <cairo/cairo.h>
#include "Supports/Validatable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Scrollable.hpp"
#include "../BEvents/WheelEvent.hpp"

#ifndef BWIDGETS_DEFAULT_IMAGECONDITIONAL_WIDTH
#define BWIDGETS_DEFAULT_IMAGECONDITIONAL_WIDTH 60
#endif

#ifndef BWIDGETS_DEFAULT_IMAGECONDITIONAL_HEIGHT
#define BWIDGETS_DEFAULT_IMAGECONDITIONAL_HEIGHT 60
#endif

namespace BWidgets 
{
/**
 *  @brief  Widget displaying an image depending on a condition.
 *
 *  %ConditionalImage is a Valueable widget which may take up multiple images
 *  each linked to a specific value. The widget shows the image(s) depending
 *  on its value. By default, the widget shows the image whos value is the
 *  closest to the widget value.
 *
 *  %ConditionalImage supports user interaction via Clickable, Draggable, and 
 *  Scrollable.
 */
class ConditionalImage :	public Widget, 
							public ValueableTyped<double>, 
							public ValidatableRange<double>, 
							public ValueTransferable<double>,
							public Clickable, 
							public Draggable, 
							public Scrollable
{
protected:
	std::map<double, cairo_surface_t*> imageSurfaces_;
	std::function<bool (ConditionalImage* widget, const double& x)> showFunc_;

public:
	/**
	 *  @brief  Construct an empty default %ConditionalImage.
	 */
	ConditionalImage ();

	/**
	 *  @brief  Construct an empty default %ConditionalImage.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ConditionalImage (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a multi Status %ConditionalImage with defined 
	 *  coordinates and size from an image file.
	 *  @param filenames  Initializer list of pairs of values and filenames. 
	 *  Supported file types are: PNG.
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ConditionalImage	(const std::initializer_list<std::pair<double, std::string>>& filenames,
						 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
						 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a multi Status %ConditionalImage with defined 
	 *  coordinates and size from an image file.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param filenames  Initializer list of pairs of values and filenames. 
	 *  Supported file types are: PNG.
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param showFunc  Optinonal, function to test if an image represented
	 *  by its value will be shown or not.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ConditionalImage	(const double x, const double y, const double width, const double height, 
						 const std::initializer_list<std::pair<double, std::string>>& filenames,
						 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
						 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
						 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
						 std::function<bool (ConditionalImage* widget, const double& x)> showFunc = isClosestToValue,
						 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	virtual ~ConditionalImage();

	/**
	 *  @brief  Creates a clone of the %ConditionalImage. 
	 *  @return  Pointer to the new %ConditionalImage.
	 *
	 *  Creates a clone of this %ConditionalImage by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ConditionalImage. 
	 *  @param that  Other %ConditionalImage.
	 *
	 *  Copies all properties from another %ConditionalImage. But NOT its linkage.
	 */
	void copy (const ConditionalImage* that);

	/**
	 *  @brief  Clears all visual content. 
	 */
	virtual void clear ();

	/**
	 *  @brief  Clears the visual content for a value.
	 *  @param value  Value (exact match). 
	 */
	virtual void clear (const double value);

	/**
     *  @brief  Optimizes the object extends.
     *
     *  Resizes the widget to fit all images which are currently visualized.
	 *  Resizes to first image if no image is currently visualized.
	 *  Resizes to (0, 0) if no image is stored.
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

	/**
	 *  @brief  Loads an image from a Cairo surface or an image file.
	 *  @param value  Value for the image to be loaded.
	 *  @param surface  Cairo surface with the image.
	 */
	virtual void loadImage (const double value, cairo_surface_t* surface);

	/**
	 *  @brief  Loads an image from a Cairo surface or an image file.
	 *  @param value  Value for the image to be loaded.
	 *  @param filename  Image file name.
	 */
	virtual void loadImage (const double value, const std::string& filename);

	/**
	 *  @brief  Access to the Cairo image surface.
	 *  @param value  Value (exact match).
	 *  @return  Pointer to the Cairo surface or nullptr if no surface for
	 *  the passed value is stored.
	 */
	cairo_surface_t* getImageSurface (const double value);

	static bool isClosestToValue (ConditionalImage* widget, const double& value);

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
     *  @brief  Unclipped draw an %ConditionalImage to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw an %ConditionalImage to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw an %ConditionalImage to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline ConditionalImage::ConditionalImage () : 
	ConditionalImage	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGECONDITIONAL_WIDTH, BWIDGETS_DEFAULT_IMAGECONDITIONAL_HEIGHT,
						 {},
						 0.0, 0.0, 1.0, 0.0,
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer,
						 isClosestToValue,
						 BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

inline ConditionalImage::ConditionalImage (const uint32_t urid, const std::string& title) :
	ConditionalImage	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGECONDITIONAL_WIDTH, BWIDGETS_DEFAULT_IMAGECONDITIONAL_HEIGHT,
						 {},
						 0.0, 0.0, 1.0, 0.0,
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
						 isClosestToValue,
						 urid, title)
	
{

}

inline ConditionalImage::ConditionalImage	(const std::initializer_list<std::pair<double, std::string>>& filenames,
											 double value, double min, double max, double step, 
											 uint32_t urid, std::string title) :
	ConditionalImage	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGECONDITIONAL_WIDTH, BWIDGETS_DEFAULT_IMAGECONDITIONAL_HEIGHT, 
						 filenames, 
						 value, min, max, step,
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
						 isClosestToValue,
						 urid, title)
{

}



inline ConditionalImage::ConditionalImage	(const double x, const double y, const double width, const double height, 
											 const std::initializer_list<std::pair<double, std::string>>& filenames,
											 double value, double min, double max, double step,
											 std::function<double (const double& x)> transferFunc,
											 std::function<double (const double& x)> reTransferFunc,
											 std::function<bool (ConditionalImage* widget,const double& x)> showFunc,
											 uint32_t urid, std::string title) :
	Widget	(x, y, width, height, urid, title),
	ValueableTyped<double> (value),
	ValidatableRange<double> (min, max, step),
	ValueTransferable<double> (transferFunc, reTransferFunc),
	Clickable(),
	Draggable(),
	Scrollable(),
	imageSurfaces_(),
	showFunc_ (showFunc)
{
	for (std::initializer_list<std::pair<double, std::string>>::const_reference f : filenames) 
	{
		imageSurfaces_[f.first] = cairo_image_surface_create_from_png (f.second.c_str());
	}
}

inline ConditionalImage::~ConditionalImage ()
{
	while (!imageSurfaces_.empty())
	{
		std::map<double, cairo_surface_t*>::iterator it = imageSurfaces_.begin();
		if (it->second && (cairo_surface_status(it->second) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (it->second);
		imageSurfaces_.erase (it);
	}
}

inline Widget* ConditionalImage::clone () const 
{
	Widget* f = new ConditionalImage (urid_, title_);
	f->copy (this);
	return f;
}

inline void ConditionalImage::copy (const ConditionalImage* that)
{
	clear();
	for (std::map<double, cairo_surface_t*>::const_reference t : that->imageSurfaces_) loadImage (t.first, t.second);
	showFunc_ = that->showFunc_;
	Scrollable::operator= (*that);
	Draggable::operator= (*that);
	Clickable::operator= (*that);
	ValueTransferable<double>::operator= (*that);
	ValidatableRange<double>::operator= (*that);
	ValueableTyped<double>::operator= (*that);
	Widget::copy (that);
}

inline void ConditionalImage::clear()
{
	while (!imageSurfaces_.empty())
	{
		std::map<double, cairo_surface_t*>::iterator it = imageSurfaces_.begin();
		if (it->second && (cairo_surface_status(it->second) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (it->second);
		imageSurfaces_.erase (it);
	}

	update();
}

inline void ConditionalImage::clear (const double value)
{
	std::map<double, cairo_surface_t*>::iterator it = imageSurfaces_.find (value);
	if (it != imageSurfaces_.end())
	{
		if (it->second && (cairo_surface_status(it->second) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (it->second);
		imageSurfaces_.erase (it);
		update();
	}
}

inline void ConditionalImage::resize ()
{
	// Resize to the surface covered by the visible images
	BUtilities::Area<> a = BUtilities::Area<>();
	for (std::map<double, cairo_surface_t*>::const_reference i : imageSurfaces_)
	{
		if	(showFunc_ (this,i.first) && i.second && (cairo_surface_status (i.second) == CAIRO_STATUS_SUCCESS))
		{
			a += BUtilities::Area<> (0, 0, cairo_image_surface_get_width (i.second), cairo_image_surface_get_height (i.second));
		}
	}

	// Otherwise resize to the first image
	if	((a == BUtilities::Area<>()) && 
		 (!imageSurfaces_.empty()) && 
		 (imageSurfaces_.begin()->second) &&
		 (cairo_surface_status (imageSurfaces_.begin()->second) == CAIRO_STATUS_SUCCESS))
	{
		a = BUtilities::Area<> (0, 0, cairo_image_surface_get_width (imageSurfaces_.begin()->second), cairo_image_surface_get_height (imageSurfaces_.begin()->second));
	}

	// Or use embedded widgets size, if bigger
	for (Linkable* l : children_)
	{
		Widget* w = dynamic_cast<Widget*>(l);
		if (w)  a += w->getArea();
	}

	resize (a.getExtends());
}

inline void ConditionalImage::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void ConditionalImage::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void ConditionalImage::loadImage (const double value, cairo_surface_t* surface)
{
	clear (value);
	imageSurfaces_[value] = cairoplus_image_surface_clone_from_image_surface (surface);
	update ();
}

inline void ConditionalImage::loadImage (const double value, const std::string& filename)
{
	clear (value);
	imageSurfaces_[value] = cairo_image_surface_create_from_png (filename.c_str());
	update ();
}

inline cairo_surface_t* ConditionalImage::getImageSurface (const double value)
{
	if (imageSurfaces_.find(value) == imageSurfaces_.end()) return nullptr;
	return imageSurfaces_[value];
}

inline bool ConditionalImage::isClosestToValue (ConditionalImage* widget, const double& value)
{
	if (!widget) return false;

	// No images: invalid / false
	if (widget->imageSurfaces_.empty()) return false;

	// No image for this value: false
	map<double, cairo_surface_t*>::const_iterator it = widget->imageSurfaces_.find (value);
	if (it == widget->imageSurfaces_.end()) return false;

	// Only one image: always the closest
	if (std::next (widget->imageSurfaces_.begin()) == widget->imageSurfaces_.end()) return true;

	const double x = widget->getRatioFromValue (widget->getValue());
	const double rval = widget->getRatioFromValue (value);

	if (x < rval)
	{
		if (it == widget->imageSurfaces_.begin()) return true;

		const double prval = widget->getRatioFromValue (std::prev (it)->first);
		if (x < prval) return false;

		return (x - prval >= rval - x);
	}

	else 
	{
		if (std::next (it) == widget->imageSurfaces_.end()) return true;

		const double nrval = widget->getRatioFromValue (std::next (it)->first);
		if (x > nrval) return false;

		return (nrval - x > x - rval);

	}
}

inline void ConditionalImage::update ()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + std::to_string (this->getValue()));
		f->resize();
	}

	Widget::update();
}

inline void ConditionalImage::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;

	
	Clickable::onButtonPressed (event);
}

inline void ConditionalImage::onPointerDragged (BEvents::Event* event)
{
	//if (isClickable()) onButtonPressed (event);
	//else
	{
		BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
		if (!pev) return;

		const double h = getEffectiveHeight();
		if (h >= 1.0)
		{
			if (getStep() != 0.0) setValue (getValue() - pev->getDelta().y * getStep ());
			else setValue (getValueFromRatio (getRatioFromValue(getValue()) - pev->getDelta().y / (h)));
		}
	}
	Draggable::onPointerDragged (event);
}

inline void ConditionalImage::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;

	const double h = getEffectiveHeight();
	if (h >= 1.0)
	{
		if (getStep() != 0.0) setValue (getValue() - wev->getDelta().y * getStep ());
		else setValue (getValueFromRatio (getRatioFromValue(getValue()) - wev->getDelta().y / (h)));
	}

	Scrollable::onWheelScrolled (event);
}

inline void ConditionalImage::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void ConditionalImage::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void ConditionalImage::draw (const BUtilities::Area<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	if ((getWidth () >= 1) && (getHeight () >= 1))
	{
		// Draw super class widget elements first
		Widget::draw (area);

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

			for (std::map<double, cairo_surface_t*>::const_reference i : imageSurfaces_)
			{
				if	(showFunc_ (this,i.first) &&
					 i.second && 
					 (cairo_surface_status (i.second) == CAIRO_STATUS_SUCCESS))
				{
					const double ws = cairo_image_surface_get_width (i.second);
					const double hs = cairo_image_surface_get_height (i.second);
					if ((ws >= 1.0) && (hs >= 1.0))
					{
						const double szs = ((w / ws < h / hs) ? (w / ws) : (h / hs));
						const double x0s = x0 + 0.5 * w - 0.5 * ws * szs;
						const double y0s = y0 + 0.5 * h - 0.5 * hs * szs;

						cairo_save (cr);
						cairo_translate(cr, x0s, y0s);
						cairo_scale (cr, szs, szs);
						cairo_set_source_surface(cr, i.second, 0, 0);
						cairo_paint (cr);
						cairo_restore (cr);
					}
				}
			}

		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_IMAGECONDITIONAL_HPP_ */
