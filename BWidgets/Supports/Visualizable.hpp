/* Visualizable.hpp
 * Copyright (C) 2018 - 2021  Sven Jähnichen
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

#ifndef BWIDGETS_VISUALIZABLE_HPP_
#define BWIDGETS_VISUALIZABLE_HPP_

#include <cairo/cairo.h>
#include "../../BUtilities/cairoplus.h"
#include "../../BUtilities/Area.hpp"
#include "Callback.hpp"
#include "Support.hpp"

namespace BWidgets
{

/**
 *  @brief  Visualization support.
 *
 *  This support includes:
 *  (i)  Drawing each %Visualizable object to its own (Cairo) RGBA surface.
 *  (ii) Expose the visual content of connected %Visualizable objects by the 
         main Window.
 *
 *  Thus, ALL visualizable widgets MUST support %Visualizable. Each widget is
 *  drawn to its own (Cairo) RGBA surface. If the visual content of a widget is
 *  changed, the widget should emit an ExposeEvent of the type 
 *  EXPOSE_REQUEST_EVENT by calling @c postRedisplay() to inform the main 
 *  window event handler about the changed content. Then the main window event
 *  handler will request a host system expose event.
 *
 *  If the main window (then) receives a host system expose event, the
 *  main window updates the visual content covered by this event.
 */
class Visualizable : virtual public Callback, public Support
{
protected:
    bool scheduleDraw_;
    BUtilities::Point<> extends_;
    cairo_surface_t* surface_;
    int layer_;

public:

    /**
     *  @brief  Creates an empty zero-sized %Visualizable object.
     */ 
    Visualizable ();

    /**
     *  @brief  Creates an empty %Visualizable object.
     *  @param width  Drawing surface width.
     *  @param height  Drawing surface width.
     */
    Visualizable (const double width, const double height);

    /**
     *  @brief  Creates an empty %Visualizable object.
     *  @param area  Drawing surface area.
     */
    Visualizable (const BUtilities::Point<> extends);

    /**
     *  @brief  Create a copy of a %Visualizable object.
     *  @param that  Original to copy from.
     */
    Visualizable (const Visualizable& that);

    virtual ~Visualizable ();

    /**
     *  @brief  Copies a %Visualizable object.
     *  @param that  Original to copy from.
     */
    Visualizable& operator= (const Visualizable& that);

    /**
     *  @brief  Switch visualization support on/off.
     *  @param status  True if on, otherwise false.
     *
     *  Defines whether the object may draw to its RGBA surface an may emit
     *  ExposeEvents or not.
     */
    void setVisualizable (const bool status);

    /**
     *  @brief  Switch visualization support on.
     */
    virtual void show ();

    /**
     *  @brief  Switch visualization support off.
     */
    virtual void hide ();

    /**
     *  @brief  Information visualization support.
     *  @return  True if on, otherwise false.
     *
     *  If a widget is %Visualizable, it may draw to its RGBA surface and may
     *  emit ExposeEvents.
     */
    bool isVisualizable () const;

    /**
     *  @brief  Information about visibility.
     *  @return  True if on, otherwise false.
	 *
	 *  An object is visible if it is %Visualizable.
     */
    virtual bool isVisible () const;

    /**
     *  @brief  Sets the object surface width.
     *  @param width  Surface width.
     *
     *  Creates a new RGBA surface with the new width, copies the surface
     *  data from the previous surface, and calls @c update() .
     */
    virtual void setWidth (const double width);

    /**
     *  @brief  Gets the object surface width.
     *  @return  Surface width.
     */
    virtual double getWidth () const;

    /**
     *  @brief  Sets the object surface height.
     *  @param width  Surface height.
     *
     *  Creates a new RGBA surface with the new height, copies the surface
     *  data from the previous surface, and calls @c update() .
     */
    virtual void setHeight (const double height);

    /**
     *  @brief  Gets the object surface height.
     *  @return  Surface height.
     */
    virtual double getHeight () const;

    /**
     *  @brief  Optimizes the object surface extends.
     *
     *  Creates a new RGBA surface with the new optimized extends, copies the
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize ();

    /**
     *  @brief  Resizes the object surface extends.
	 *  @param width  New object width.
	 *  @param height  New object height.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const double width, const double height);

    /**
	 *  @brief  Resizes the object surface extends.
	 *  @param extends  New object extends.
     *
     *  Creates a new RGBA surface with the new extends, copies the 
     *  surface data from the previous surface, and calls @c update() .
	 */
	virtual void resize (const BUtilities::Point<> extends);

    /**
	 *  @brief  Gets the surface extends of an object.
	 *  @return  Point<> data containing width and height.
	 */
	virtual BUtilities::Point<> getExtends () const;

    /**
     *  @brief  Re-indexes the object surface.
     *  @param layer  Layer index.
     *
     *  The layer index represents the Z position of the surface. The higher
     *  the index, the more to the background. The default layer has got the
     *  index 0. Negative indexed layers will be displayed in front of the 
     *  default layer, positive indexed layers behind.
     */
    virtual void setLayer (const int layer);

    /**
     *  @brief  Gets the object surface.
     *  @param layer  Layer index.
     *
     *  The layer index represents the Z position of the surface. The higher
     *  the index, the more to the background. The default layer has got the
     *  index 0. Negative indexed layers will be displayed in front of the 
     *  default layer, positive indexed layers behind.
     */
    virtual int getLayer () const;

    /**
     *  @brief  Method to be called following an object state change.
     *
     *  Default method to be overridden. This method should be called
     *  following a %Visualizable object state change.
     */
    virtual void update ();

    /**
	 *  @brief  Emits an ExposeEvent of the type EXPOSE_REQUEST_EVENT.
	 */
	virtual void emitExposeEvent () = 0;

    /**
	 *  @brief  Emits an ExposeEvent of the type EXPOSE_REQUEST_EVENT.
     *  @param area  Area to be re-displayed.
	 */
    virtual void emitExposeEvent (const BUtilities::Area<>& area) = 0;
    
    /**
     *  @brief  Access to the Cairo surface.
     *  @return  Pointer to the Cairo surface.
     */
    cairo_surface_t* cairoSurface() const;

    /**
     *  @brief  Method called upon an configure request event.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  an ExposeEvent of the type CONFIGURE_REQUEST_EVENT emited by a widget
     *  or the host system. By default, it calls its static callback function.
     */
    virtual void onConfigureRequest (BEvents::Event* event);

    /**
     *  @brief  Method called upon an expose request event.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler upon
     *  an ExposeEvent of the type EXPOSE_REQUEST_EVENT emited by a widget. By
     *  default, it calls its static callback function.
     */
    virtual void onExposeRequest (BEvents::Event* event);

protected:

    /**
     *  @brief  Unclipped draw to the surface (if is visualizable).
     *
     *  Default empty method to be overridden.
     */
    virtual void draw ();

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     *
     *  Default empty method to be overridden.
     */
    virtual void draw (const double x0, const double y0, const double width, const double height);

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param area  Clipped area. 
     *
     *  Default empty method to be overridden.
     */
    virtual void draw (const BUtilities::Area<>& area);

};

inline Visualizable::Visualizable () : 
    Visualizable (0, 0)
{

}

inline Visualizable::Visualizable (const double width, const double height) :
    Visualizable (BUtilities::Point<> (width, height))
{

}

inline Visualizable::Visualizable (const BUtilities::Point<> extends) :
    Callback(),
    Support(),
    scheduleDraw_ (true),
    extends_ (extends),
    surface_ (cairo_image_surface_create (CAIRO_FORMAT_ARGB32, extends.x, extends.y)),
    layer_ (0)
{

}

inline Visualizable::Visualizable (const Visualizable& that) :
    Callback (that),
    Support (that),
    scheduleDraw_ (that.scheduleDraw_),
    extends_ (that.extends_),
    surface_ (cairoplus_image_surface_clone_from_image_surface (that.surface_)),
    layer_ (that.layer_)
{

}

inline Visualizable::~Visualizable ()
{
    cairo_surface_destroy (surface_);
}

inline Visualizable& Visualizable::operator= (const Visualizable& that)
{
    Callback::operator= (that);
    Support::operator= (that);
    scheduleDraw_ = that.scheduleDraw_;
    extends_ = that.extends_;
    if (surface_) cairo_surface_destroy (surface_);
    surface_ = cairoplus_image_surface_clone_from_image_surface (that.surface_);
    layer_ = that.layer_;

    update();
    return *this;
}

inline void Visualizable::setVisualizable (const bool status) 
{
    if (status) show ();
    else hide ();
}

inline void Visualizable::show ()
{
    bool wasVisible = isVisible ();
    setSupport (true);
    if (wasVisible != isVisible ()) emitExposeEvent ();
}

inline void Visualizable::hide ()
{
    setSupport (false);
}

inline bool Visualizable::isVisualizable () const 
{
    return getSupport();
}

inline bool Visualizable::isVisible () const 
{
    return isVisualizable();
}

inline void Visualizable::setWidth (const double width)
{
    resize (width, extends_.y);
}

inline double Visualizable::getWidth () const
{
    return extends_.x;
}

inline void Visualizable::setHeight (const double height)
{
    resize (extends_.x, height);
}

inline double Visualizable::getHeight () const
{
    return extends_.y;
}

inline void Visualizable::resize ()
{
    resize (0, 0);
}

inline void Visualizable::resize (const double width, const double height)
{
    resize (BUtilities::Point<> (width, height));
}

inline void Visualizable::setLayer (const int layer)
{
    if (layer != layer_)
    {
        layer_ = layer;
        update();
    }
}

inline int Visualizable::getLayer() const
{
    return layer_;
}

inline void Visualizable::resize (const BUtilities::Point<> extends)
{
    if ((extends.x != extends_.x) || (extends.y != extends_.y))
    {
        extends_ = BUtilities::Point<> (std::max (extends.x, 0.0), std::max (extends.y, 0.0));

        // Create new surface
        cairo_surface_t* new_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, extends_.x, extends_.y);

        // Copy surface
		if (new_surface && (cairo_surface_status (new_surface) == CAIRO_STATUS_SUCCESS))
		{
            cairo_t* cr = cairo_create (new_surface);
			if (cr && (cairo_status (cr) == CAIRO_STATUS_SUCCESS))
			{
				cairo_set_source_surface (cr, surface_, 0, 0);
				cairo_paint (cr);
				cairo_destroy (cr);
			}
		}

        // Delete old surface
        cairo_surface_destroy (surface_);

        // Copy new surface pointer
        surface_ = new_surface;

        update();
    }
}

inline BUtilities::Point<> Visualizable::getExtends () const 
{
    return extends_;
}

inline void Visualizable::update ()
{
    scheduleDraw_ = true;
	if (isVisible ()) emitExposeEvent ();
}

inline cairo_surface_t* Visualizable::cairoSurface() const
{
    return surface_;
}

inline void Visualizable::onConfigureRequest (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::CONFIGURE_REQUEST_EVENT) (event);
}

inline void Visualizable::onExposeRequest (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::EXPOSE_REQUEST_EVENT) (event);
}

inline void Visualizable::draw ()
{

}

inline void Visualizable::draw (const double x0, const double y0, const double width, const double height)
{

}

inline void Visualizable::draw (const BUtilities::Area<>& area)
{
    scheduleDraw_ = false;
}
}
#endif /* BWIDGETS_VISUALIZABLE_HPP_ */