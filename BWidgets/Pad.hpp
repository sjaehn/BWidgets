/* Pad.hpp
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

#ifndef BWIDGETS_PAD_HPP_
#define BWIDGETS_PAD_HPP_

#include "Widget.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Scrollable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "../BEvents/PointerEvent.hpp"
#include "Draws/drawPad.hpp"

#ifndef BWIDGETS_DEFAULT_PAD_WIDTH
#define BWIDGETS_DEFAULT_PAD_WIDTH 40
#endif

#ifndef BWIDGETS_DEFAULT_PAD_HEIGHT
#define BWIDGETS_DEFAULT_PAD_HEIGHT 20
#endif

namespace BWidgets
{
/**
 *  @brief  Widget imitating an LED pad.
 *
 *  %Pad is a Valueable widget imitating an LED pad. Its value is represented
 *  by its color from dark to bright. It supports user interaction via
 *  Clickable (switch on / off) and Scrollable (increase / decrease value). 
 *  The visualble content of the %Pad is represented by FgColors.
 */
class Pad : public Widget, 
			public ValueableTyped<double>, 
			public ValidatableRange<double>, 
			public ValueTransferable<double>, 
			public Clickable, 
			public Scrollable
{

protected:
	double storedValue_;

public:

	/**
	 * @brief  Constructs a new %Pad object with default parameters.
	 */
	Pad ();

	/**
	 *  @brief  Creates a %Pad with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pad	(const double value, const double min, const double max, double step = 0.0, 
		 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Pad.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pad	(const double x, const double y, const double width, const double height, 
		 const double value, const double min, const double max, double step = 0.0,
		 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
		 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
		 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %Pad. 
	 *  @return  Pointer to the new %Pad.
	 *
	 *  Creates a clone of this %Pad by copying all properties. But NOT
	 *  its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %Pad. 
	 *  @param that  Other %Pad.
	 *
	 *  Copies all properties from another %Pad. But NOT its linkage.
	 */
	void copy (const Pad* that);

	/**
     *  @brief  Method called when pointer button clicked (pressed and 
     *  released).
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button cklicked. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonClicked (BEvents::Event* event) override;
	
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
     *  @brief  Unclipped draw to the surface (if is visualizable).
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped Draw to the surface (if is visualizable).
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::RectArea& area) override;
};

inline Pad::Pad () : 
	Pad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
		 0.0, 0.0, 1.0, 0.0, 
		 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer,  
		 URID_UNKNOWN_URID, "") 
{

}

inline Pad::Pad	(double value, const double min, const double max, double step, uint32_t urid, std::string title) :
	Pad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT, 
		 min, max, step, urid, 
		 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
		 urid, title) 
{

}

inline Pad::Pad	(const double x, const double y, const double width, const double height, 
			 	 double value, const double min, const double max, double step, 
				 std::function<double (const double& x)> transferFunc,
			 	 std::function<double (const double& x)> reTransferFunc,
				 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<double> (value),
	ValidatableRange<double> (min, max, step),
	ValueTransferable<double> (transferFunc, reTransferFunc),
	Clickable(),
	Scrollable(),
	storedValue_ (value == min ? max : min)
{
	
}

inline Widget* Pad::clone () const 
{
	Widget* f = new Pad ();
	f->copy (this);
	return f;
}

inline void Pad::copy (const Pad* that)
{
	storedValue_ = that->storedValue_;
	Scrollable::operator= (*that);
	Clickable::operator= (*that);
	ValueTransferable<double>::operator= (*that);
	ValidatableRange<double>::operator= (*that);
	ValueableTyped<double>::operator= (*that);
	Widget::copy (that);
}

inline void Pad::onButtonClicked (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (pev->getPosition() == pev->getOrigin())
	{
		if (getValue() == getMin()) setValue (storedValue_);
		else
		{
			 storedValue_ = getValue();
			 setValue (getMin());
		};
	}
	Clickable::onButtonClicked (event);
}

inline void Pad::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (getHeight()) 
	{
		if (getStep() != 0.0) setValue (getValue() - wev->getDelta().y * getStep ());
		else setValue (getValueFromRatio (getRatioFromValue(getValue(), transfer_) - wev->getDelta().y / getHeight(), reTransfer_));
	}
	Scrollable::onWheelScrolled (event);
}

inline void Pad::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void Pad::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::RectArea (x0, y0, width, height));
}

inline void Pad::draw (const BUtilities::RectArea& area)
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

				const double x0 = getXOffset ();
				const double y0 = getYOffset ();
				const double w = getEffectiveWidth ();
				const double h = getEffectiveHeight ();
				const double rval = getRatioFromValue (getValue(), transfer_);
				const BStyles::Color butColor = getFgColors()[getStatus()].illuminate (-0.9 + 0.9 * rval);
				drawButton (cr, x0, y0, w, h, butColor);
				cairo_destroy (cr);
			}
		}
	}

}

#endif /* BWIDGETS_PAD_HPP_ */
