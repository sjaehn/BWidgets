/* HScale.hpp
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

#ifndef BWIDGETS_HSCALE_HPP_
#define BWIDGETS_HSCALE_HPP_

#include "HMeter.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Scrollable.hpp"
#include "Supports/KeyPressable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "../BEvents/KeyEvent.hpp"
#include BWIDGETS_DEFAULT_DRAWHBAR_PATH

#ifndef BWIDGETS_DEFAULT_HSCALE_WIDTH
#define BWIDGETS_DEFAULT_HSCALE_WIDTH 80.0
#endif

#ifndef BWIDGETS_DEFAULT_HSCALE_HEIGHT
#define BWIDGETS_DEFAULT_HSCALE_HEIGHT 10.0
#endif

namespace BWidgets
{

/**
 *  @brief  %HScale widget.
 *
 *  %HScale is a Valueable Widget derived from HMeter. It displays a value as 
 *  a horizontal scale and supports user interaction via Clickable, Draggable,
 *  Scrollable, and KeyPressable. Its appearance is defined by the BgColors 
 *  parameter (static elements) and by the FgColors parameter (value).
 */
class HScale :	public HMeter, 
				public Clickable, 
				public Draggable, 
				public Scrollable,
				public KeyPressable
{

protected:

	bool fineTuned_;

public:

	/**
	 *  @brief  Constructs a default %HScale object.
	 */
	HScale ();

	/**
	 *  @brief  Constructs a default %HScale object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	HScale (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %HScale with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HScale	(const double value, const double min, const double max, double step = 0.0, 
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HScale.
	 *  @param x  %HScale X origin coordinate.
	 *  @param y  %HScale Y origin coordinate.
	 *  @param width  %HScale width.
	 *  @param height  %HScale height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %HScale title (default = "").
	 */
	HScale	(const double x, const double y, const double width, const double height, 
			 const double value, const double min, const double max, double step = 0.0,
			 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
			 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
			 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %HScale. 
	 *  @return  Pointer to the new %HScale.
	 *
	 *  Creates a clone of this %HScale by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %HScale. 
	 *  @param that  Other %HScale.
	 *
	 *  Copies all properties from another %HScale. But NOT its linkage.
	 */
	void copy (const HScale* that);

	/**
     *  @brief  Sets the range step size.
     *  @param step  Step size.
	 *
	 *  Also sets the number of sub steps to BWIDGETS_DEFAULT_NR_SUBSTEPS if 
	 *  step size is 0.0.
     */
    virtual void setStep (const double& step) override;

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

	/**
     *  @brief  Method when a KeyEvent with the type keyPressEvent is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler if a
     *  key is pressed. By default, it calls its static callback function.
     */
    virtual void onKeyPressed (BEvents::Event* event) override;

    /**
     *  @brief  Method when a KeyEvent with the type keyReleaseEvent is 
     *  received.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler if a
     *  key is released. By default, it calls its static callback function.
     */
    virtual void onKeyReleased (BEvents::Event* event) override;

protected:
	/**
     *  @brief  Unclipped draw a %HScale to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %HScale to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %HScale to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;
};

inline HScale::HScale () :
	HScale	(0.0, 0.0, BWIDGETS_DEFAULT_HSCALE_WIDTH, BWIDGETS_DEFAULT_HSCALE_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline HScale::HScale (const uint32_t urid, const std::string& title) : 
	HScale	(0.0, 0.0, BWIDGETS_DEFAULT_HSCALE_WIDTH, BWIDGETS_DEFAULT_HSCALE_HEIGHT, 
			 0.0, 0.0, 1.0, 0.0,
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline HScale::HScale (const double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	HScale	(0.0, 0.0, BWIDGETS_DEFAULT_HSCALE_WIDTH, BWIDGETS_DEFAULT_HSCALE_HEIGHT, 
			 value, min, max, step, 
			 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
			 urid, title) 
{

}

inline HScale::HScale	(const double  x, const double y, const double width, const double height, 
						 const double value, const double min, const double max, double step, 
						 std::function<double (const double& x)> transferFunc,
			 			 std::function<double (const double& x)> reTransferFunc,
						 uint32_t urid, std::string title) :
		HMeter	(x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
		Clickable(),
		Draggable(),
		Scrollable(),
		KeyPressable(), 
		fineTuned_(false)
{
	setKeyPressable(true);
	grabDevice(BDevices::Keys(BDevices::Keys::KeyType::shiftL));
	grabDevice(BDevices::Keys(BDevices::Keys::KeyType::shiftR));
	if (step == 0.0) setNrSubs(BWIDGETS_DEFAULT_NR_SUBSTEPS);
}

inline Widget* HScale::clone () const 
{
	Widget* f = new HScale (urid_, title_);
	f->copy (this);
	return f;
}

inline void HScale::copy (const HScale* that)
{
	fineTuned_ = that->fineTuned_;
	KeyPressable::operator=(*that);
	Scrollable::operator= (*that);
	Draggable::operator= (*that);
	Clickable::operator= (*that);
	HMeter::copy (that);
}

inline void HScale::setStep (const double &step)
{
	ValidatableRange<double>::setStep(step);
	if (step == 0.0) setNrSubs(BWIDGETS_DEFAULT_NR_SUBSTEPS);
}

inline void HScale::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	if (scale_.getWidth()) 
	{
		if (step_ >= 0) setValue (getValueFromRatio ((pev->getPosition().x - scale_.getX()) / scale_.getWidth()));
		else setValue (getValueFromRatio ((scale_.getWidth() - (pev->getPosition().x - scale_.getX())) / scale_.getWidth()));
	}
	Clickable::onButtonPressed (event);
}

inline void HScale::onPointerDragged (BEvents::Event* event)
{
	if (isClickable()) onButtonPressed (event);
	else
	{
		BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
		if (!pev) return;
		if (scale_.getWidth()) 
		{
			if (getStep() != 0.0) setValue (getValue() - pev->getDelta().y * (fineTuned_ ?	getSubStep() : getStep()));
			else 
			{
				const double step = (fineTuned_ ?	1.0 / ((static_cast<double>(getNrSubs() + 1.0)) * scale_.getWidth()) :
													1.0 / scale_.getWidth());
				setValue (getValueFromRatio	(getRatioFromValue (getValue()) - pev->getDelta().y * step));
			}
		}
	}
	Draggable::onPointerDragged (event);
}

inline void HScale::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (scale_.getWidth()) 
	{
		if (getStep() != 0.0) setValue (getValue() - wev->getDelta().y * (fineTuned_ ?	getSubStep() : getStep()));
		else 
		{
			const double step = (fineTuned_ ?	1.0 / ((static_cast<double>(getNrSubs() + 1.0)) * scale_.getWidth()) :
												1.0 / scale_.getWidth());
			setValue (getValueFromRatio	(getRatioFromValue (getValue()) - wev->getDelta().y * step));
		}
	}
	Scrollable::onWheelScrolled (event);
}

inline void HScale::onKeyPressed (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() == this) fineTuned_ = true;
	
	KeyPressable::onKeyPressed(event);
}

inline void HScale::onKeyReleased (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() == this) fineTuned_ = false;

	KeyPressable::onKeyReleased(event);
}

inline void HScale::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

inline void HScale::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

inline void HScale::draw (const BUtilities::Area<>& area)
{
	if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

	// Draw super class widget elements first
	Widget::draw (area);

	// Draw only if minimum requirements satisfied
	if ((getHeight () >= 1) && (getWidth () >= 1))
	{
		cairo_t* cr = cairo_create (cairoSurface());

		if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
		{
			// Limit cairo-drawing area
			cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
			cairo_clip (cr);

			const double rval = getRatioFromValue (getValue());

			if (step_ >= 0.0) 
			{
				drawHBar(cr, 
						 scale_.getX(), scale_.getY(), 
						 scale_.getWidth(), scale_.getHeight(), 
						 0.0, rval, BWIDGETS_DEFAULT_SLIDER_BAR_FGCOLOR, BWIDGETS_DEFAULT_SLIDER_BAR_BGCOLOR);
			}
			else 
			{
				drawHBar(cr, scale_.getX(), scale_.getY(), 
						 scale_.getWidth(), scale_.getHeight(),
						 1.0 - rval, 1.0, BWIDGETS_DEFAULT_SLIDER_BAR_FGCOLOR, BWIDGETS_DEFAULT_SLIDER_BAR_BGCOLOR);
			}
		}

		cairo_destroy (cr);
	}
}

}

#endif /* BWIDGETS_HSCALE_HPP_ */
