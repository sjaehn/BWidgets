/* Visualizable.cpp
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

#include "Visualizable.hpp"
#include "../../BUtilities/cairoplus.h"
#include "Support.hpp"

namespace BWidgets
{

Visualizable::Visualizable () : 
    Visualizable (0, 0)
{

}

Visualizable::Visualizable (const double width, const double height) :
    Visualizable (BUtilities::Point (width, height))
{

}

Visualizable::Visualizable (const BUtilities::Point extends) :
    Callback(),
    Support(),
    scheduleDraw_ (true),
    extends_ (extends),
    surface_ (cairo_image_surface_create (CAIRO_FORMAT_ARGB32, extends.x, extends.y))
{

}

Visualizable::Visualizable (const Visualizable& that) :
    Callback (that),
    Support (that),
    scheduleDraw_ (that.scheduleDraw_),
    extends_ (that.extends_),
    surface_ (cairo_image_surface_clone_from_image_surface (that.surface_))
{

}

Visualizable::~Visualizable ()
{
    cairo_surface_destroy (surface_);
}

Visualizable& Visualizable::operator= (const Visualizable& that)
{
    Callback::operator= (that);
    Support::operator= (that);
    scheduleDraw_ = that.scheduleDraw_;
    extends_ = that.extends_;
    if (surface_) cairo_surface_destroy (surface_);
    surface_ = cairo_image_surface_clone_from_image_surface (that.surface_);

    update();
    return *this;
}

void Visualizable::setVisualizable (const bool status) 
{
    if (status) show ();
    else hide ();
}

void Visualizable::show ()
{
    bool wasVisible = isVisible ();
    setSupport (true);
    if (wasVisible != isVisible ()) emitExposeEvent ();
}

void Visualizable::hide ()
{
    setSupport (false);
}

bool Visualizable::isVisualizable () const 
{
    return getSupport();
}

bool Visualizable::isVisible () const 
{
    return isVisualizable();
}

void Visualizable::setWidth (const double width)
{
    resize (width, extends_.y);
}

double Visualizable::getWidth () const
{
    return extends_.x;
}

void Visualizable::setHeight (const double height)
{
    resize (extends_.x, height);
}

double Visualizable::getHeight () const
{
    return extends_.y;
}

void Visualizable::resize ()
{
    resize (0, 0);
}

void Visualizable::resize (const double width, const double height)
{
    resize (BUtilities::Point (width, height));
}

void Visualizable::resize (const BUtilities::Point extends)
{
    if ((extends.x != extends_.x) || (extends.y != extends_.y))
    {
        extends_ = extends;

        // Create new surface
        cairo_surface_t* new_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, extends.x, extends.y);

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

BUtilities::Point Visualizable::getExtends () const 
{
    return extends_;
}

void Visualizable::update ()
{
    scheduleDraw_ = true;
	if (isVisible ()) emitExposeEvent ();
}

cairo_surface_t* Visualizable::cairoSurface() const
{
    return surface_;
}

void Visualizable::onConfigureRequest (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::CONFIGURE_REQUEST_EVENT) (event);
}

void Visualizable::onExposeRequest (BEvents::Event* event)
{
    callback (BEvents::Event::EventType::EXPOSE_REQUEST_EVENT) (event);
}

void Visualizable::draw ()
{

}

void Visualizable::draw (const double x0, const double y0, const double width, const double height)
{

}

void Visualizable::draw (const BUtilities::RectArea& area)
{
    scheduleDraw_ = false;
}

}
