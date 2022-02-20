/* HRangeScrollBar.hpp
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

#ifndef BWIDGETS_HRANGESCROLLBAR_HPP_
#define BWIDGETS_HRANGESCROLLBAR_HPP_

#include "HScrollBar.hpp"
#include "Frame.hpp"
#include "Symbol.hpp"
#include "Supports/Validatable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include "Supports/Scrollable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "Draws/drawHBar.hpp"
#include "Draws/drawKnob.hpp"
#include <cairo/cairo.h>
#include <utility>

#ifndef BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH
#define BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH BWIDGETS_DEFAULT_HSCROLLBAR_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT
#define BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT BWIDGETS_DEFAULT_HSCROLLBAR_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  %Horizontal scroll bar widget with the option to resize on both
 *  ends.
 *
 *  %HRangeScrollBar is a Valueable Widget similiar to HScrollbar. It displays
 *  a value constisting of a std::pair with its min and its max value as a 
 *  horizontal scrollbar and supports user interaction via Scrollable to resize
 *  the range value. In addition, it supports dragging to move the value range
 *  or to move the ends (min, max). Its appearance is defined by the BgColors 
 *  parameter.
 *
 *  @todo Inverse range, negative step.
 */
class HRangeScrollBar :	public Widget, 
						public ValueableTyped<std::pair<double, double>>, 
						public ValidatableRange<std::pair<double, double>>, 
						public ValueTransferable<std::pair<double, double>>,
						public Scrollable
{
protected:

public:
	HScrollBar scrollbar;
	Frame button1;
	Frame button2;
	Symbol symbol1;
	Symbol symbol2;

	/**
	 *  @brief  Constructs a default %HRangeScrollBar object.
	 */
	HRangeScrollBar ();

	/**
	 *  @brief  Constructs a default %HRangeScrollBar object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	HRangeScrollBar (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %HRangeScrollBar with default size.
	 *  @param value1  Initial value (range min).
	 *  @param value2  Initial value (range max).
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param vsize  Optional, range covered by the value.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HRangeScrollBar	(const double value1, const double value2, const double min, const double max, double step = 0.0,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HRangeScrollBar with default size.
	 *  @param value  Initial value (range min, range max).
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param vsize  Optional, range covered by the value.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	HRangeScrollBar	(const value_type value, const double min, const double max, double step = 0.0,
					 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HRangeScrollBar.
	 *  @param x  %HRangeScrollBar X origin coordinate.
	 *  @param y  %HRangeScrollBar Y origin coordinate.
	 *  @param width  %HRangeScrollBar width.
	 *  @param height  %HRangeScrollBar height.
	 *  @param value1  Initial value (range min).
	 *  @param value2  Initial value (range max).
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %HRangeScrollBar title (default = "").
	 */
	HRangeScrollBar	(const double x, const double y, const double width, const double height, 
			 const double value1, const double value2, const double min, const double max, double step = 0.0,
			 std::function<value_type (const value_type& x)> transferFunc = ValueTransferable<value_type>::noTransfer,
			 std::function<value_type (const value_type& x)> reTransferFunc = ValueTransferable<value_type>::noTransfer,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %HRangeScrollBar.
	 *  @param x  %HRangeScrollBar X origin coordinate.
	 *  @param y  %HRangeScrollBar Y origin coordinate.
	 *  @param width  %HRangeScrollBar width.
	 *  @param height  %HRangeScrollBar height.
	 *  @param value  Initial value (range min, range max).
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = URID_UNKNOWN_URID).
	 *  @param title  Optional, %HRangeScrollBar title (default = "").
	 */
	HRangeScrollBar	(const double x, const double y, const double width, const double height, 
			 const value_type value, const double min, const double max, double step = 0.0,
			 std::function<value_type (const value_type& x)> transferFunc = ValueTransferable<value_type>::noTransfer,
			 std::function<value_type (const value_type& x)> reTransferFunc = ValueTransferable<value_type>::noTransfer,
			 uint32_t urid = URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %HRangeScrollBar. 
	 *  @return  Pointer to the new %HRangeScrollBar.
	 *
	 *  Creates a clone of this %HRangeScrollBar by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %HRangeScrollBar. 
	 *  @param that  Other %HRangeScrollBar.
	 *
	 *  Copies all properties from another %HRangeScrollBar. But NOT its linkage.
	 */
	void copy (const HRangeScrollBar* that);
	
	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area. Resizes the widget to its standard size if this widget doesn't 
	 *  have any children (except its scrollbar and its buttons).
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the widget extends.
	 *  @param width  New widget width.
	 *  @param height  New widget height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the widget extends.
	 *  @param extends  New widget extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

	/**
     *  @brief  Method to be called following an object state change.
     */
    virtual void update () override;
	
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

	static void buttonDraggedCallback (BEvents::Event* event);

	static void scrollbarChangedCallback (BEvents::Event* event);

};

inline HRangeScrollBar::HRangeScrollBar () :
	HRangeScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT, 
					 value_type (0.0, 0.0), 0.0, 1.0, 0.0, 
					 ValueTransferable<value_type>::noTransfer, ValueTransferable<value_type>::noTransfer, 
			 		 URID_UNKNOWN_URID, "")
{

}



inline HRangeScrollBar::HRangeScrollBar (const uint32_t urid, const std::string& title) : 
	HRangeScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT, 
					 value_type (0.0, 0.0), 0.0, 1.0, 0.0, 
					 ValueTransferable<value_type>::noTransfer, ValueTransferable<value_type>::noTransfer, 
					 urid, title) 
{

}

inline HRangeScrollBar::HRangeScrollBar (const double value1, const double value2, const double min, const double max, double step, uint32_t urid, std::string title) : 
	HRangeScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT, 
					 value_type (value1, value2), min, max, step,
					 ValueTransferable<value_type>::noTransfer, ValueTransferable<value_type>::noTransfer, 
					 urid, title) 
{

}

inline HRangeScrollBar::HRangeScrollBar (const value_type value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	HRangeScrollBar	(0.0, 0.0, BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT, 
					 value, min, max, step,
					 ValueTransferable<value_type>::noTransfer, ValueTransferable<value_type>::noTransfer, 
					 urid, title) 
{

}

inline HRangeScrollBar::HRangeScrollBar	(const double  x, const double y, const double width, const double height, 
										 const double value1, const double value2, const double min, const double max, double step,
										 std::function<value_type (const value_type& x)> transferFunc,
							 			 std::function<value_type (const value_type& x)> reTransferFunc,
										 uint32_t urid, std::string title) :
	HRangeScrollBar	(x, y, width, height, 
					 value_type (value1, value2), min, max, step,
					 ValueTransferable<value_type>::noTransfer, ValueTransferable<value_type>::noTransfer, 
					 urid, title)
{

}

inline HRangeScrollBar::HRangeScrollBar	(const double  x, const double y, const double width, const double height, 
						 const value_type value, const double min, const double max, double step, 
						 std::function<value_type (const value_type& x)> transferFunc,
			 			 std::function<value_type (const value_type& x)> reTransferFunc,
						 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title), 
	ValueableTyped<value_type> (value), 
	ValidatableRange<value_type> (value_type (min, min), value_type (max, max), value_type (step, step)), 
	ValueTransferable<value_type> (transferFunc, reTransferFunc),
	Scrollable (),
	scrollbar (urid, title),
	button1 (urid, title),
	button2 (urid, title),
	symbol1 (Symbol::MINUS_SYMBOL, urid, title),
	symbol2 (Symbol::ADD_SYMBOL, urid, title)
{
	scrollbar.setCallbackFunction(BEvents::Event::VALUE_CHANGED_EVENT, scrollbarChangedCallback);
	scrollbar.setScrollable (false);
	scrollbar.setEventPassable (BEvents::Event::WHEEL_SCROLL_EVENT);
	button1.setCallbackFunction(BEvents::Event::POINTER_DRAG_EVENT, buttonDraggedCallback);
	button1.setEventPassable (BEvents::Event::WHEEL_SCROLL_EVENT);
	button2.setCallbackFunction(BEvents::Event::POINTER_DRAG_EVENT, buttonDraggedCallback);
	button2.setEventPassable (BEvents::Event::WHEEL_SCROLL_EVENT);
	symbol1.setEventPassable (BEvents::Event::WHEEL_SCROLL_EVENT);
	symbol1.setEventPassable (BEvents::Event::BUTTON_PRESS_EVENT);
	symbol1.setEventPassable (BEvents::Event::BUTTON_RELEASE_EVENT);
	symbol1.setEventPassable (BEvents::Event::BUTTON_CLICK_EVENT);
	symbol1.setEventPassable (BEvents::Event::POINTER_DRAG_EVENT);
	symbol2.setEventPassable (BEvents::Event::WHEEL_SCROLL_EVENT);
	symbol2.setEventPassable (BEvents::Event::BUTTON_PRESS_EVENT);
	symbol2.setEventPassable (BEvents::Event::BUTTON_RELEASE_EVENT);
	symbol2.setEventPassable (BEvents::Event::BUTTON_CLICK_EVENT);
	symbol2.setEventPassable (BEvents::Event::POINTER_DRAG_EVENT);
	button1.add(&symbol1);
	button2.add(&symbol2);
	add (&scrollbar);
	add (&button1);
	add (&button2);
}

inline Widget* HRangeScrollBar::clone () const 
{
	Widget* f = new HRangeScrollBar (urid_, title_);
	f->copy (this);
	return f;
}

inline void HRangeScrollBar::copy (const HRangeScrollBar* that)
{
	scrollbar.copy (&that->scrollbar);
	button1.copy (&that->button1);
	button2.copy (&that->button2);
	symbol1.copy (&that->symbol1);
	symbol2.copy (&that->symbol2);
	Scrollable::operator= (*that);
	ValueTransferable<value_type>::operator= (*that);
	ValidatableRange<value_type>::operator= (*that);
	ValueableTyped<value_type>::operator= (*that);
	Widget::copy (that);
}

inline void HRangeScrollBar::resize ()
{
	if (children_.size() <= 3) resize (BUtilities::Point<> (BWIDGETS_DEFAULT_HRANGESCROLLBAR_WIDTH, BWIDGETS_DEFAULT_HRANGESCROLLBAR_HEIGHT));

	else
	{
		button1.resize (0,0);
		button1.moveTo (getXOffset(), getYOffset());
		button2.resize (0,0);
		button2.moveTo (getXOffset(), getYOffset());
		scrollbar.resize();
		scrollbar.moveTo (getXOffset(), getYOffset());
		Widget::resize();
	}
}

inline void HRangeScrollBar::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void HRangeScrollBar::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void HRangeScrollBar::update ()
{
	if ((getEffectiveWidth () > 0) && (getEffectiveHeight () > 0))
	{
		const double x = getXOffset ();
		const double y = getYOffset ();
		const double w = getEffectiveWidth ();
		const double h = getEffectiveHeight ();
		const value_type v = getValue();
		const value_type rv = getRatioFromValue (v, getTransferFunction());

		scrollbar.moveTo (x, y);
		scrollbar.resize (w, h);
		scrollbar.setValue (v.first);
		scrollbar.setValueSize(v.second - v.first);

		symbol1.moveTo (0.25 * h, 0.25 * h);
		symbol1.resize (0.5 * h, 0.5 * h);

		symbol2.moveTo (0.25 * h, 0.25 * h);
		symbol2.resize (0.5 * h, 0.5 * h);

		button1.moveTo (x + (w - h) * rv.first, y);
		button1.resize (h, h);

		button2.moveTo (x + (w - h) * rv.second, y);
		button2.resize (h, h);

		const BStyles::Color bgColor =getBgColors()[getStatus()];
		cairo_t* cr1 = cairo_create (button1.cairoSurface());
		drawKnob (cr1, 0.5 * h, 0.5 * h, 0.25 * h, 0.0, bgColor, bgColor);
		cairo_destroy (cr1);
		cairo_t* cr2 = cairo_create (button2.cairoSurface());
		drawKnob (cr2, 0.5 * h, 0.5 * h, 0.25 * h, 0.0, bgColor, bgColor);
		cairo_destroy (cr2);
	}

	Widget::update();
}

inline void HRangeScrollBar::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (getEffectiveWidth() >= 1) 
	{
		value_type v = getValue();
		if (getStep().first != 0.0) v.first += wev->getDelta().y * getStep ().first;
		else v.first = getValueFromRatio	(value_type	(getRatioFromValue (v, transfer_).first + wev->getDelta().y / getEffectiveWidth(), 
														 v.second), 
											 transfer_, reTransfer_).first;

		if (getStep().second != 0.0) v.second -= wev->getDelta().y * getStep ().second;
		else v.second = getValueFromRatio	(value_type	(v.first,
														 getRatioFromValue (v, transfer_).second - wev->getDelta().y / getEffectiveWidth()),
											 transfer_, reTransfer_).second;

		const value_type vr = getRatioFromValue (v, transfer_);
		if (vr.first <= vr.second) setValue (v);
	}
	Scrollable::onWheelScrolled (event);
}

inline void HRangeScrollBar::buttonDraggedCallback (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*>(event);
	if (!pev) return;

	Frame* w = dynamic_cast<Frame*>(pev->getWidget());
	if (!w) return;

	HRangeScrollBar* p = dynamic_cast<HRangeScrollBar*>(w->getParentWidget());
	if (!p) return;

	const double x0 = p->getXOffset ();
	const double width = p->getEffectiveWidth ();
	const double height = p->getEffectiveHeight ();
	const double px = std::max (std::min (w->getPosition().x, x0 + width - height), x0);

	const double rv = (px - x0) / (width - height);
	value_type v = p->getValue();
	const value_type rv0 = p->getRatioFromValue (v, p->getTransferFunction());
	if ((w ==&p->button1) && (rv <= rv0.second)) v.first = p->getValueFromRatio (value_type (rv, rv0.second)).first;
	else if ((w ==&p->button2) && (rv >= rv0.first)) v.second = p->getValueFromRatio (value_type (rv0.first, rv)).second;
	p->setValue (v);
	p->update();

}

inline void HRangeScrollBar::scrollbarChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<double>* vev = dynamic_cast<BEvents::ValueChangeTypedEvent<double>*>(event);
	if (!vev) return;

	HScrollBar* w = dynamic_cast<HScrollBar*>(vev->getWidget());
	if (!w) return;

	HRangeScrollBar* p = dynamic_cast<HRangeScrollBar*>(w->getParentWidget());
	if (!p) return;

	p->setValue (value_type (w->getValue(), p->getValue().second + w->getValue() - p->getValue().first));
	p->update();
}

}


#endif /* BWIDGETS_HRANGESCROLLBAR_HPP_ */
