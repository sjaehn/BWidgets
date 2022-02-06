/* Knob.hpp
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

#ifndef BWIDGETS_KNOB_HPP_
#define BWIDGETS_KNOB_HPP_

#include "Button.hpp"
#include "Draws/drawKnob.hpp"

#ifndef BWIDGETS_DEFAULT_KNOB_WIDTH
#define BWIDGETS_DEFAULT_KNOB_WIDTH 20.0
#endif

#ifndef BWIDGETS_DEFAULT_KNOB_HEIGHT
#define BWIDGETS_DEFAULT_KNOB_HEIGHT BWIDGETS_DEFAULT_KNOB_WIDTH
#endif

namespace BWidgets
{

/**
 *  @brief  %Knob Button widget.
 *
 *  %Knob is a Button Widget. It is a pseudo 3D visualization of a knob which
 *  can change its status (bool value) upon user interaction via  Clickable. 
 *  Its appearance is defined by the BgColors parameter (static elements, 
 *  false) and by the FgColors parameter (active elements, true).
 */
class Knob : public Button
{
protected:
	double depth_;

public:

	/**
	 *  @brief  Constructs a default %Knob object.
	 * 
	 */
	Knob ();

	/**
	 *  @brief  Constructs a default %Knob object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Knob (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %Knob with default size.
	 *  @param depth  Pseudo 3D %Knob depth.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Knob	(const double depth, bool toggleable = false, bool clicked = false, uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Knob.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param depth  Pseudo 3D %Knob depth.
	 *  @param toggleable  Support of button toggling.
	 *  @param clicked  Default click status.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Knob	(const double x, const double y, const double width, const double height, 
			 const double depth = 1.0, bool toggleable = false, bool clicked = false,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Knob. 
	 *  @return  Pointer to the new %Knob.
	 *
	 *  Creates a clone of this %Knob by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Knob. 
	 *  @param that  Other %Knob.
	 *
	 *  Copies all properties from another %Knob. But NOT its linkage.
	 */
	void copy (const Knob* that);

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;

	/**
	 *  @brief  Sets the pseudo 3D depth of the knob.
	 *  @param depth  Pseudo 3D depth.
	 */
	void setDepth (const double depth);

	/**
	 *  @brief  Gets the pseudo 3D depth of the knob.
	 *  @return  Pseudo 3D depth.
	 */
	double getDepth () const;

protected:
	/**
     *  @brief  Unclipped draw a %Knob to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %Knob to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %Knob to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea& area) override;
};

inline Knob::Knob () :
	Knob (0.0, 0.0, BWIDGETS_DEFAULT_KNOB_WIDTH, BWIDGETS_DEFAULT_KNOB_HEIGHT, 1.0, false, false, URID_UNKNOWN_URID, "")
{

}

inline Knob::Knob (const uint32_t urid, const std::string& title) : 
	Knob (0.0, 0.0, BWIDGETS_DEFAULT_KNOB_WIDTH, BWIDGETS_DEFAULT_KNOB_HEIGHT, 1.0, false, false, urid, title) 
{

}

inline Knob::Knob (const double depth, bool toggleable, bool clicked, uint32_t urid, std::string title) : 
	Knob (0.0, 0.0, BWIDGETS_DEFAULT_KNOB_WIDTH, BWIDGETS_DEFAULT_KNOB_HEIGHT, depth, toggleable, clicked, urid, title) 
{

}

inline Knob::Knob (const double  x, const double y, const double width, const double height, double depth, bool toggleable, bool clicked, uint32_t urid, std::string title) :
		Button (x, y, width, height, toggleable, clicked, urid, title),
		depth_ (depth)
{
	setBackground (BStyles::noFill);
	setBorder (BStyles::noBorder);
}

inline Widget* Knob::clone () const 
{
	Widget* f = new Knob ();
	f->copy (this);
	return f;
}

inline void Knob::copy (const Knob* that)
{
	depth_ = that->depth_;
    Widget::copy (that);
}

inline void Knob::update()
{
	Widget::update();
}

inline void Knob::setDepth (const double depth)
{
	if (depth != depth_)
	{
		depth_ = depth;
		update ();
	}
}

inline double Knob::getDepth () const 
{
	return depth_;
}

inline void Knob::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Knob::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea (x0, y0, width, height));
}

inline void Knob::draw (const BUtilities::RectArea& area)
{
	if ((!surface_) || (cairo_surface_status (surface_) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	const double x0 = getXOffset();
	const double y0 = getYOffset();
	const double heff = getEffectiveHeight ();
	const double weff = getEffectiveWidth ();

	// Draw knob
	// only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1))
	{
		cairo_t* cr = cairo_create (surface_);

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			// Calculate aspect ratios first
			const double radius = (heff < weff ? 0.5 * heff : 0.5 * weff) - depth_;
			const double xc = x0 + 0.5 * weff + depth_;
			const double yc = y0 + 0.5 * heff + depth_;

			const BStyles::Color color = (getValue() ? getFgColors() : getBgColors()) [getStatus()];
			const double depth = (getValue() ? 0.5 * depth_ : depth_);
			drawKnob(cr, xc, yc, radius, depth, color, getBgColors()[getStatus()]);
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_KNOB_HPP_ */
