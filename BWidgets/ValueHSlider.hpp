/* ValueHSlider.hpp
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

#ifndef BWIDGETS_VALUEHSLIDER_HPP_
#define BWIDGETS_VALUEHSLIDER_HPP_

#include "HSlider.hpp"
#include "EditLabel.hpp"
#include <exception>
#include <functional>

#ifndef BWIDGETS_DEFAULT_VALUEHSLIDER_WIDTH
#define BWIDGETS_DEFAULT_VALUEHSLIDER_WIDTH 80.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEHSLIDER_HEIGHT
#define BWIDGETS_DEFAULT_VALUEHSLIDER_HEIGHT 40.0
#endif

#ifndef BDOUBLE_TO_STRING
#define BDOUBLE_TO_STRING BWidgets::ValueHSlider::valueToString
#endif

#ifndef BSTRING_TO_DOUBLE
#define BSTRING_TO_DOUBLE BWidgets::ValueHSlider::stringToValue
#endif

namespace BWidgets
{

/**
 *  @brief  %ValueHSlider widget.
 *
 *  %ValueHSlider is a HSlider Widget with an additional editable label for
 *  displaying its value. 
 */
class ValueHSlider : public HSlider
{

public:

	static std::string valueToString (const double& x);
	
	static double stringToValue (const std::string& s);

protected:
	std::function<std::string (const double& x)> display_ = valueToString;
	std::function<double (const std::string& s)> reDisplay_ = stringToValue;

public:

	EditLabel label;

	/**
	 *  @brief  Constructs a default %ValueHSlider object.
	 */
	ValueHSlider ();

	/**
	 *  @brief  Constructs a default %ValueHSlider object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ValueHSlider (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ValueHSlider with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ValueHSlider	(const double value, const double min, const double max, double step = 0.0, 
					 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ValueHSlider.
	 *  @param x  %ValueHSlider X origin coordinate.
	 *  @param y  %ValueHSlider Y origin coordinate.
	 *  @param width  %ValueHSlider width.
	 *  @param height  %ValueHSlider height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param displayFunc  Optional, function to convert the value to a string
	 *  which will be displayed as a label.
	 *  @param reDisplayFunc  Optional, function to convert the string from
	 *  the (edited) label to the value.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %ValueHSlider title (default = "").
	 *
	 *  The optional parameters @a displayFunc and @a reDisplayFunc can be used
	 *  as powerful tools to visualize the value in any way (including units,
	 *  prefixes, postfixes, text substitution, ...) and to parse it. By 
	 *  default, %ValueHSlider displays the value via @c valueToString() and
	 *  thus shows a decimal floating point representation with up to 3 digits
	 *  after the point.
	 */
	ValueHSlider	(const double x, const double y, const double width, const double height, 
					 const double value, const double min, const double max, double step = 0.0,
					 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
					 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
					 std::function<std::string (const double& x)> displayFunc = valueToString,
					 std::function<double (const std::string& s)> reDisplayFunc = stringToValue,
					 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ValueHSlider. 
	 *  @return  Pointer to the new %ValueHSlider.
	 *
	 *  Creates a clone of this %ValueHSlider by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ValueHSlider. 
	 *  @param that  Other %ValueHSlider.
	 *
	 *  Copies all properties from another %ValueHSlider. But NOT its linkage.
	 */
	void copy (const ValueHSlider* that);
	
	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area. Resizes the widget to its standard size if this widget doesn't 
	 *  have any children (except its label).
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
	 *  @brief  Callback function to be called by the label upon change of
	 *  the label content. 
	 *  @param event  Event of the type ValueChangedEvent
	 */
	static void labelChangedCallback (BEvents::Event* event);
};

inline ValueHSlider::ValueHSlider () :
	ValueHSlider	(
					 0.0, 0.0, BWIDGETS_DEFAULT_VALUEHSLIDER_WIDTH, BWIDGETS_DEFAULT_VALUEHSLIDER_HEIGHT, 
					 0.0, 0.0, 1.0, 0.0, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer, 
					 valueToString,
					 stringToValue,
					 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline ValueHSlider::ValueHSlider (const uint32_t urid, const std::string& title) : 
	ValueHSlider	(0.0, 0.0, BWIDGETS_DEFAULT_VALUEHSLIDER_WIDTH, BWIDGETS_DEFAULT_VALUEHSLIDER_HEIGHT, 
					 0.0, 0.0, 1.0, 0.0, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer,
					 valueToString,
					 stringToValue, 
				 	 urid, title) 
{

}

inline ValueHSlider::ValueHSlider (const double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	ValueHSlider	(0.0, 0.0, BWIDGETS_DEFAULT_VALUEHSLIDER_WIDTH, BWIDGETS_DEFAULT_VALUEHSLIDER_HEIGHT, 
					 value, min, max, step, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer,
					 valueToString,
					 stringToValue, 
				 	 urid, title) 
{

}

inline ValueHSlider::ValueHSlider	(const double  x, const double y, const double width, const double height, 
								 const double value, const double min, const double max, double step, 
								 std::function<double (const double& x)> transferFunc,
					 			 std::function<double (const double& x)> reTransferFunc,
								 std::function<std::string (const double& x)> displayFunc,
								 std::function<double (const std::string& s)> reDisplayFunc,
								 uint32_t urid, std::string title) :
	HSlider (x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
	display_ (displayFunc),
	reDisplay_ (reDisplayFunc),
	label (BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), "")
{
	add (&label);
	label.setCallbackFunction (BEvents::Event::EventType::ValueChangedEvent, labelChangedCallback);
	label.setEventPassable(BEvents::Event::EventType::WheelScrollEvent);
	label.setEventPassable(BEvents::Event::EventType::PointerDragEvent);
	label.setEventPassable(BEvents::Event::EventType::PointerFocusEvents);
}

inline Widget* ValueHSlider::clone () const 
{
	Widget* f = new ValueHSlider (urid_, title_);
	f->copy (this);
	return f;
}

inline void ValueHSlider::copy (const ValueHSlider* that)
{
	display_ = that->display_;
	reDisplay_ = that->reDisplay_;
	label.copy (&that->label);
	HSlider::copy (that);
}

inline void ValueHSlider::resize ()
{
	if (children_.size() <= 1) resize (BUtilities::Point<> (BWIDGETS_DEFAULT_VALUEHSLIDER_WIDTH, BWIDGETS_DEFAULT_VALUEHSLIDER_HEIGHT));

	else
	{
		label.resize();
		label.moveTo (getXOffset(), getYOffset());
		HSlider::resize();
	}
}

inline void ValueHSlider::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void ValueHSlider::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void ValueHSlider::update ()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + std::to_string (this->getValue()));
		f->resize();
	}

	scale_ = BUtilities::Area<> 
	(
		getXOffset() + 0.25 * getEffectiveHeight(), 
		getYOffset() + 0.625 * getEffectiveHeight(), 
		getEffectiveWidth() - 0.5 * getEffectiveHeight(), 
		0.25 * getEffectiveHeight()
	);

	const bool lv = label.isValueable();
	label.setValueable (false);
	label.setText (display_ (getValue()));
	label.setValueable (lv);
	label.resize();
	const double rval = getRatioFromValue(getValue());
	const double xc = scale_.getX() + rval * scale_.getWidth();
	const double x0 = xc - 0.5 * label.getWidth();
	label.moveTo (std::min (std::max (x0, label.left()), label.right()), getYOffset());

	Widget::update();
}

inline void ValueHSlider::labelChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<std::string>* vew = dynamic_cast<BEvents::ValueChangeTypedEvent<std::string>*>(event);
	if (!vew) return;
	EditLabel* widget = dynamic_cast<EditLabel*>(vew->getWidget());
	if (!widget) return;
	ValueHSlider* parent = dynamic_cast<ValueHSlider*>(widget->getParentWidget());
	if (!parent) return;

	double nval = parent->getValue();
	try {nval = parent->reDisplay_ (widget->getText());} 
	catch (std::exception& exc) 
	{
		widget->setText (parent->display_ (parent->getValue()));
		return;
	}

	parent->setValue (nval);
	parent->update ();
}

inline std::string ValueHSlider::valueToString (const double& x)
{
	const int dPre = ((x == 0) || (fabs (x) <= 1.0) ? 1 : log10 (fabs (x)) + 1);
	const int dPost = std::max (4 - dPre, 0);
	char buf[256];
	std::sprintf (buf, ("%1." + std::to_string (dPost) + "f").c_str(), x);
	return std::string (buf);
}

inline double ValueHSlider::stringToValue (const std::string& s)
{
	return std::stod (s);
}

}

#endif /* BWIDGETS_VALUEHSLIDER_HPP_ */
