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
#include "../../BUtilities/RectArea.hpp"
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
    virtual void emitExposeEvent (const BUtilities::RectArea<>& area) = 0;
    
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
    virtual void draw (const BUtilities::RectArea<>& area);

};
}
#endif /* BWIDGETS_VISUALIZABLE_HPP_ */