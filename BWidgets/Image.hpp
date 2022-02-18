/* Image.hpp
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

#ifndef BWIDGETS_IMAGE_HPP_
#define BWIDGETS_IMAGE_HPP_

#include "Widget.hpp"
#include <cairo/cairo.h>
#include <initializer_list>

#ifndef BWIDGETS_DEFAULT_IMAGE_WIDTH
#define BWIDGETS_DEFAULT_IMAGE_WIDTH BWIDGETS_DEFAULT_WIDGET_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_IMAGE_HEIGHT
#define BWIDGETS_DEFAULT_IMAGE_HEIGHT BWIDGETS_DEFAULT_WIDGET_HEIGHT
#endif

namespace BWidgets
{
/**
 *  @brief  %Image displaying Widget.
 *
 *  Supports one image for each Status. No user interaction.
 */
class Image : public Widget
{
protected:
	std::map<BStyles::Status, cairo_surface_t*> imageSurfaces_;

public:
	/**
	 *  @brief  Construct an empty default %Image.
	 */
	Image ();

	/**
	 *  @brief  Construct an empty default %Image.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Image (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates an empty %Image with defined coordinates and size.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a single status %Image with defined coordinates and
	 *  size from a Cairo surface.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surface  Pointer to a Cairo surface.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Most simple case of an %Image. The visual content provided by the
	 *  @a surface is displayed independently from the Widget Status. Until
	 *  a new visual content is added by loadImage().
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 cairo_surface_t* surface, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a single status %Image with defined coordinates and
	 *  size from an image file.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param filename  Filename, supported file types are: PNG.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Most simple case of an %Image. The visual content provided by the
	 *  @a filename is displayed independently from the Widget Status. Until
	 *  a new visual content is added by loadImage().
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 const std::string& filename, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a multi Status %Image with defined coordinates and
	 *  size from a Cairo surface.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surfaces  Initializer list of pointers to Cairo surfaces.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Creates an %Image with visual contents for each Widget Status as
	 *  defined by @a surfaces in the order STATUS_NORMAL, STATUS_ACTIVE,
     *  STATUS_INACTIVE, STATUS_OFF, STATUS_USER_DEFINED. The %Image behaves
	 *  like an empty %Image if an empty initializer list of @a surfaces is 
	 *  provided. And it behaves like a single status %Image if an initializer
	 *  list with only one element is passed. STATUS_NORMAL also acts for 
	 *  missing states.
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 const std::initializer_list<cairo_surface_t*>& surfaces, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a multi Status %Image with defined coordinates and
	 *  size from a Cairo surface.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surfaces  Map of pointer to Cairo surfaces for each Status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Creates an %Image with visual contents for each Widget Status as
	 *  defined by @a surfaces. The %Image behaves like an empty %Image if an
	 *  empty map is provided. Otherwise at least an image for STATUS_NORMAL
	 *  should be provided to behave at least like a single status %Image.
	 *  STATUS_NORMAL also acts for missing states.
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 const std::map<BStyles::Status, cairo_surface_t*>& surfaces, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a multi Status %Image with defined coordinates and
	 *  size from an image file.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param filenames  Initializer list of filenames. Supported file types
	 *  are: PNG.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Creates an %Image with visual contents for each Widget Status as
	 *  defined by @a filenames in the order STATUS_NORMAL, STATUS_ACTIVE,
     *  STATUS_INACTIVE, STATUS_OFF, STATUS_USER_DEFINED. The %Image behaves
	 *  like an empty %Image if an empty initializer list of @a filenames is 
	 *  provided. And it behaves like a single status %Image if an initializer
	 *  list with only one element is passed. STATUS_NORMAL also acts for 
	 *  missing states.
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 const std::initializer_list<std::string>& filenames, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a multi Status %Image with defined coordinates and
	 *  size from an image file.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param filenames  Map of filenames for each Status. Supported file 
	 *  types are: PNG.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Creates an %Image with visual contents for each Widget Status as
	 *  defined by @a filenames. The %Image behaves like an empty %Image if an
	 *  empty map is provided. Otherwise at least an image for STATUS_NORMAL
	 *  should be provided to behave at least like a single status %Image.
	 *  STATUS_NORMAL also acts for missing states.
	 */
	Image	(const double x, const double y, const double width, const double height, 
			 const std::map<BStyles::Status, std::string>& filenames, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	virtual ~Image();

	/**
	 *  @brief  Creates a clone of the %Image. 
	 *  @return  Pointer to the new %Image.
	 *
	 *  Creates a clone of this %Image by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Image. 
	 *  @param that  Other %Image.
	 *
	 *  Copies all properties from another %Image. But NOT its linkage.
	 */
	void copy (const Image* that);

	/**
	 *  @brief  Clears all visual content. 
	 */
	virtual void clear ();

	/**
	 *  @brief  Clears the visual content for a status.
	 *  @param status  Status. 
	 */
	virtual void clear (const BStyles::Status status);

	/**
     *  @brief  Optimizes the object extends.
     *
     *  Resizes the %Image to fit to the visual content for the present
	 *  Status. Resizes to the visual content extends of STATUS_NORMAL if no
	 *  visual content for the present status is defined. Resizes to (0, 0) if
	 *  neither the visual content for the present status nor the visual
	 *  content for STATUS_NORMAL is defined.
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
	 *  @param status  Widget status for the image to be loaded.
	 *  @param surface  Cairo surface with the image.
	 */
	virtual void loadImage (const BStyles::Status status, cairo_surface_t* surface);

	/**
	 *  @brief  Loads an image from a Cairo surface or an image file.
	 *  @param status  Widget status for the image to be loaded.
	 *  @param filename  Image file name.
	 */
	virtual void loadImage (const BStyles::Status status, const std::string& filename);

	/**
	 *  @brief  Access to the Cairo image surface.
	 *  @param status  Widget status.
	 *  @return  Pointer to the Cairo surface.
	 */
	cairo_surface_t* getImageSurface (const BStyles::Status status);

protected:
	/**
     *  @brief  Unclipped draw an %Image to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw an %Image to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw an %Image to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea<>& area) override;
};

inline Image::Image () : 
	Image (0.0, 0.0, BWIDGETS_DEFAULT_IMAGE_WIDTH, BWIDGETS_DEFAULT_IMAGE_HEIGHT) 
{

}

inline Image::Image (const uint32_t urid, const std::string& title) :
		Widget (0.0, 0.0, BWIDGETS_DEFAULT_IMAGE_WIDTH, BWIDGETS_DEFAULT_IMAGE_HEIGHT, urid, title),
		imageSurfaces_()
{

}

inline Image::Image (const double x, const double y, const double width, const double height,
		      uint32_t urid, std::string title) :
		Widget (x, y, width, height, urid, title),
		imageSurfaces_()
{

}

inline Image::Image (const double x, const double y, const double width, const double height,
		      cairo_surface_t* surface, uint32_t urid, std::string title) :
		Widget (x, y, width, height, urid, title),
		imageSurfaces_()
{
	loadImage (BStyles::Status::STATUS_NORMAL, surface);
}

inline Image::Image (const double x, const double y, const double width, const double height,
		      const std::string& filename, uint32_t urid, std::string title) :
		Image (x, y, width, height, urid, title)
{
	loadImage (BStyles::Status::STATUS_NORMAL, filename);
}

inline Image::Image (const double x, const double y, const double width, const double height,
		      const std::initializer_list<cairo_surface_t*>& surfaces, uint32_t urid, std::string title) :
		Image (x, y, width, height, urid, title)
{
	size_t i = 0;
	for (cairo_surface_t* s : surfaces)
	{
		loadImage (BStyles::Status (i), s);
		++i;
	}
}

inline Image::Image (const double x, const double y, const double width, const double height,
		      const std::map<BStyles::Status, cairo_surface_t*>& surfaces, uint32_t urid, std::string title) :
		Image (x, y, width, height, urid, title)
{
	for (std::map<BStyles::Status, cairo_surface_t*>::const_reference s : surfaces) loadImage (s.first, s.second);
}

inline Image::Image (const double x, const double y, const double width, const double height,
		      const std::initializer_list<std::string>& filenames, uint32_t urid, std::string title) :
		Image (x, y, width, height, urid, title)
{
	size_t i = 0;
	for (const std::string& f : filenames)
	{
		loadImage (BStyles::Status (i), f);
		++i;
	}
}

inline Image::Image (const double x, const double y, const double width, const double height,
		      const std::map<BStyles::Status, std::string>& filenames, uint32_t urid, std::string title) :
		Image (x, y, width, height, urid, title)
{
	for (std::map<BStyles::Status, std::string>::const_reference f : filenames) loadImage (f.first, f.second);
}

inline Image::~Image ()
{
	while (!imageSurfaces_.empty())
	{
		std::map<BStyles::Status, cairo_surface_t*>::iterator it = imageSurfaces_.begin();
		if (it->second && (cairo_surface_status(it->second) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (it->second);
		imageSurfaces_.erase (it);
	}
}

inline Widget* Image::clone () const 
{
	Widget* f = new Image (urid_, title_);
	f->copy (this);
	return f;
}

inline void Image::copy (const Image* that)
{
	clear();
	for (std::map<BStyles::Status, cairo_surface_t*>::const_reference t : that->imageSurfaces_) loadImage (t.first, t.second);
	Widget::copy (that);
}

inline void Image::clear()
{
	while (!imageSurfaces_.empty())
	{
		std::map<BStyles::Status, cairo_surface_t*>::iterator it = imageSurfaces_.begin();
		if (it->second && (cairo_surface_status(it->second) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (it->second);
		imageSurfaces_.erase (it);
	}

	update();
}

inline void Image::resize ()
{
	// Get surface extends for the present Status
	BUtilities::Point<> contExt = {0.0, 0.0};
	if (!imageSurfaces_.empty())
	{
		std::map<BStyles::Status, cairo_surface_t*>::iterator it = imageSurfaces_.find (getStatus());
		if (it == imageSurfaces_.end()) it = imageSurfaces_.find (BStyles::Status::STATUS_NORMAL);	// Fallback

		if (it != imageSurfaces_.end())
		{
			cairo_surface_t* stateSurface = it->second;

			if (stateSurface && (cairo_surface_status (stateSurface) == CAIRO_STATUS_SUCCESS))
			{
				contExt =	BUtilities::Point<> (cairo_image_surface_get_width (stateSurface), cairo_image_surface_get_height (stateSurface)) +
							BUtilities::Point<> (2.0 * getXOffset(), 2.0 * getYOffset());
			}
		}
	}

	// Or use embedded widgets size, if bigger
	for (Linkable* l : children_)
	{
		Widget* w = dynamic_cast<Widget*>(l);
		if (!w) continue;
		if (w->getPosition ().x + w->getWidth () > contExt.x) contExt.x = w->getPosition ().x + w->getWidth();
		if (w->getPosition ().y + w->getHeight () > contExt.y) contExt.y = w->getPosition ().y + w->getHeight();
	}

	resize (contExt);
}

inline void Image::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void Image::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void Image::clear (const BStyles::Status status)
{
	std::map<BStyles::Status, cairo_surface_t*>::iterator it = imageSurfaces_.find (status);
	if (it != imageSurfaces_.end())
	{
		if (it->second && (cairo_surface_status(it->second) == CAIRO_STATUS_SUCCESS)) cairo_surface_destroy (it->second);
		imageSurfaces_.erase (it);
		if (status == getStatus()) update();
	}
}

inline void Image::loadImage (const BStyles::Status status, cairo_surface_t* surface)
{
	clear (status);
	imageSurfaces_[status] = cairo_image_surface_clone_from_image_surface (surface);
	update ();
}

inline void Image::loadImage (const BStyles::Status status, const std::string& filename)
{
	clear (status);
	imageSurfaces_[status] = cairo_image_surface_create_from_png (filename.c_str());
	update ();
}

inline cairo_surface_t* Image::getImageSurface (const BStyles::Status status)
{
	return imageSurfaces_[status];
}

inline void Image::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Image::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea<> (x0, y0, width, height));
}

inline void Image::draw (const BUtilities::RectArea<>& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	if ((getWidth () >= 1) && (getHeight () >= 1))
	{
		// Draw super class widget elements first
		Widget::draw (area);

		double w = getEffectiveWidth ();
		double h = getEffectiveHeight ();

		if (!imageSurfaces_.empty())
		{
			std::map<BStyles::Status, cairo_surface_t*>::iterator it = imageSurfaces_.find (getStatus());
			if (it == imageSurfaces_.end()) it = imageSurfaces_.find (BStyles::Status::STATUS_NORMAL);	// Fallback

			if (it != imageSurfaces_.end())
			{
				cairo_surface_t* stateSurface = it->second;

				if (stateSurface && (cairo_surface_status (stateSurface) == CAIRO_STATUS_SUCCESS) && (w > 0) && (h > 0))
				{
					cairo_t* cr = cairo_create (surface_);
					if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
					{
						// Limit cairo-drawing area
						cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
						cairo_clip (cr);
						//TODO also clip to inner borders

						double oriw = cairo_image_surface_get_width (stateSurface);
						double orih = cairo_image_surface_get_height (stateSurface);
						double sz = ((w / oriw < h / orih) ? (w / oriw) : (h / orih));
						double x0 = getXOffset () + w / 2 - oriw * sz / 2;
						double y0 = getYOffset () + h / 2 - orih * sz / 2;
						cairo_translate (cr, x0, y0);
						cairo_scale (cr, sz, sz);
						cairo_set_source_surface (cr, stateSurface, 0, 0);
						cairo_paint (cr);
					}

					cairo_destroy (cr);
				}
			}
		}
	}
}

}

#endif /* BWIDGETS_IMAGE_HPP_ */
