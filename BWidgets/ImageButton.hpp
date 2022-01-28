/* ImageButton.hpp
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

#ifndef BWIDGETS_IMAGEBUTTON_HPP_
#define BWIDGETS_IMAGEBUTTON_HPP_

#include "Button.hpp"
#include "Image.hpp"

namespace BWidgets
{
/**
 *  @brief Composite Button Widget containing an Image.
 *
 *  %ImageButton is a Button containing an Image. A %ImageButton changes its 
 *  Image status (and thus its visual content) in addition to the change of 
 *  its Border Color upon changing the condition.
 */
class ImageButton : public Button
{
public:

	Image image;

	/**
	 * @brief  Constructs a new %ImageButton object with default parameters.
	 */
	ImageButton ();

	/**
	 *  @brief  Creates a %ImageButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surface  Pointer to a Cairo surface.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ImageButton	(const double x, const double y, const double width, const double height, 
					 cairo_surface_t* surface, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param filename  Filename, supported file types are: PNG.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ImageButton	(const double x, const double y, const double width, const double height, 
					 const std::string& filename, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surfaces  Vector of pointers to Cairo surfaces.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ImageButton	(const double x, const double y, const double width, const double height, 
					 const std::vector<cairo_surface_t*>& surfaces, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surfaces  Map of pointer to Cairo surfaces for each Status.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ImageButton	(const double x, const double y, const double width, const double height, 
					 const std::map<BStyles::Status, cairo_surface_t*>& surfaces, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param filenames  Vector of filenames. Supported file types are: PNG.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ImageButton	(const double x, const double y, const double width, const double height, 
					 const std::vector<std::string>& filenames, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageButton.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param surface  Pointer to a Cairo surface.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ImageButton	(const double x, const double y, const double width, const double height, 
					 const std::map<BStyles::Status, std::string>& filenames, bool toggleable = false, bool clicked = false,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ImageButton. 
	 *  @return  Pointer to the new %ImageButton.
	 *
	 *  Creates a clone of this %ImageButton by copying all properties. But NOT
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ImageButton. 
	 *  @param that  Other %ImageButton.
	 *
	 *  Copies all properties from another %ImageButton. But NOT its linkage.
	 */
	void copy (const ImageButton* that);

	/**
     *  @brief  Optimizes the object surface extends.
     *
     *  Creates a new RGBA surface with the new optimized extends, copies the
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the object surface extends.
	 *  @param width  New object width.
	 *  @param height  New object height.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the object surface extends.
	 *  @param extends  New object extends.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const BUtilities::Point extends) override;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;
};

inline ImageButton::ImageButton () : 
	ImageButton (0.0, 0.0, BWIDGETS_DEFAULT_BUTTON_WIDTH, BWIDGETS_DEFAULT_BUTTON_HEIGHT, 
	std::map<BStyles::Status, cairo_surface_t*>(), false, false, URID_UNKNOWN_URID, "") 
{

}

inline ImageButton::ImageButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 cairo_surface_t* surface, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	image (0, 0, width, height, surface, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/image"))
{
	
	add (&image);
	image.moveTo (image.center(), image.middle());
}

inline ImageButton::ImageButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 const std::string& filename, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	image (0, 0, width, height, filename, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/image"))
{
	
	add (&image);
	image.moveTo (image.center(), image.middle());
}

inline ImageButton::ImageButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 const std::vector<cairo_surface_t*>& surfaces, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	image (0, 0, width, height, surfaces, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/image"))
{
	
	add (&image);
	image.moveTo (image.center(), image.middle());
}

inline ImageButton::ImageButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 const std::map<BStyles::Status, cairo_surface_t*>& surfaces, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	image (0, 0, width, height, surfaces, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/image"))
{
	
	add (&image);
	image.moveTo (image.center(), image.middle());
}

inline ImageButton::ImageButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 const std::vector<std::string>& filenames, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	image (0, 0, width, height, filenames, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/image"))
{
	
	add (&image);
	image.moveTo (image.center(), image.middle());
}

inline ImageButton::ImageButton	(const double x, const double y, const double width, const double height, 
			 	 		 	 const std::map<BStyles::Status, std::string>& filenames, bool toggleable, bool clicked, uint32_t urid, std::string title) :
	Button (x, y, width, height, toggleable, clicked, urid, title),
	image (0, 0, width, height, filenames, BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/image"))
{
	
	add (&image);
	image.moveTo (image.center(), image.middle());
}

inline Widget* ImageButton::clone () const 
{
	Widget* f = new ImageButton ();
	f->copy (this);
	return f;
}

inline void ImageButton::copy (const ImageButton* that)
{
	image.copy (&that->image);
    Button::copy (that);
}

inline void ImageButton::resize ()
{
	image.resize ();
	image.moveTo (0, 0);
	Button::resize ();
}

inline void ImageButton::resize (const double width, const double height) 
{
	ImageButton::resize (BUtilities::Point (width, height));
}

inline void ImageButton::resize (const BUtilities::Point extends)
{
	Button::resize (BUtilities::Point (extends.x, extends.y));
	image.resize (BUtilities::Point (getEffectiveWidth(), getEffectiveHeight()));
	image.moveTo (image.center(), image.middle());
}

inline void ImageButton::update ()
{
	image.setStatus (getValue() ? BStyles::Status::STATUS_ACTIVE : BStyles::Status::STATUS_NORMAL);
	image.resize (getEffectiveWidth(), getEffectiveHeight());
	image.moveTo (image.center(), image.middle());
	Button::update ();

}

}

#endif /* BWIDGETS_IMAGEBUTTON_HPP_ */