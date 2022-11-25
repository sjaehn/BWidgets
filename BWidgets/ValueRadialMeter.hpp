/* ValueRadialMeter.hpp
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

#ifndef BWIDGETS_VALUERADIALMETER_HPP_
#define BWIDGETS_VALUERADIALMETER_HPP_

#include "RadialMeter.hpp"
#include "Label.hpp"
#include <cmath>
#include <exception>
#include <functional>

#ifndef BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH
#define BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH 40.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT
#define BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT 50.0
#endif

#ifndef BDOUBLE_TO_STRING
#define BDOUBLE_TO_STRING(x) BWidgets::ValueRadialMeter::valueToString(x)
#endif

#ifndef BSTRING_TO_DOUBLE
#define BSTRING_TO_DOUBLE(x) BWidgets::ValueRadialMeter::stringToValue(x)
#endif

namespace BWidgets
{

/**
 *  @brief  %ValueRadialMeter widget.
 *
 *  %ValueRadialMeter is a RadialMeter Widget with an additional label for
 *  displaying its value. 
 */
class ValueRadialMeter : public RadialMeter
{

public:

	static std::string valueToString (const double& x);
	
	static double stringToValue (const std::string& s);

protected:
	std::function<std::string (const double& x)> display_ = valueToString;
	std::function<double (const std::string& s)> reDisplay_ = stringToValue;

public:

	Label label;

	/**
	 *  @brief  Constructs a default %ValueRadialMeter object.
	 */
	ValueRadialMeter ();

	/**
	 *  @brief  Constructs a default %ValueRadialMeter object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ValueRadialMeter (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ValueRadialMeter with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ValueRadialMeter	(const double value, const double min, const double max, double step = 0.0, 
					 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ValueRadialMeter.
	 *  @param x  %ValueRadialMeter X origin coordinate.
	 *  @param y  %ValueRadialMeter Y origin coordinate.
	 *  @param width  %ValueRadialMeter width.
	 *  @param height  %ValueRadialMeter height.
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
	 *  @param title  Optional, %ValueRadialMeter title (default = "").
	 *
	 *  The optional parameters @a displayFunc and @a reDisplayFunc can be used
	 *  as powerful tools to visualize the value in any way (including units,
	 *  prefixes, postfixes, text substitution, ...) and to parse it. By 
	 *  default, %ValueRadialMeter displays the value via @c valueToString() and
	 *  thus shows a decimal floating point representation with up to 3 digits
	 *  after the point.
	 */
	ValueRadialMeter	(const double x, const double y, const double width, const double height, 
					 const double value, const double min, const double max, double step = 0.0,
					 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
					 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
					 std::function<std::string (const double& x)> displayFunc = valueToString,
					 std::function<double (const std::string& s)> reDisplayFunc = stringToValue,
					 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ValueRadialMeter. 
	 *  @return  Pointer to the new %ValueRadialMeter.
	 *
	 *  Creates a clone of this %ValueRadialMeter by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ValueRadialMeter. 
	 *  @param that  Other %ValueRadialMeter.
	 *
	 *  Copies all properties from another %ValueRadialMeter. But NOT its linkage.
	 */
	void copy (const ValueRadialMeter* that);
	
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

inline ValueRadialMeter::ValueRadialMeter () :
	ValueRadialMeter	(
					 0.0, 0.0, BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH, BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT, 
					 0.0, 0.0, 1.0, 0.0, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer, 
					 valueToString,
					 stringToValue,
					 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline ValueRadialMeter::ValueRadialMeter (const uint32_t urid, const std::string& title) : 
	ValueRadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH, BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT, 
					 0.0, 0.0, 1.0, 0.0, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer,
					 valueToString,
					 stringToValue, 
				 	 urid, title) 
{

}

inline ValueRadialMeter::ValueRadialMeter (double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	ValueRadialMeter	(0.0, 0.0, BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH, BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT, 
					 value, min, max, step, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer,
					 valueToString,
					 stringToValue, 
				 	 urid, title) 
{

}

inline ValueRadialMeter::ValueRadialMeter	(const double  x, const double y, const double width, const double height, 
									 double value, const double min, const double max, double step, 
									 std::function<double (const double& x)> transferFunc,
						 			 std::function<double (const double& x)> reTransferFunc,
									 std::function<std::string (const double& x)> displayFunc,
									 std::function<double (const std::string& s)> reDisplayFunc,
									 uint32_t urid, std::string title) :
	RadialMeter (x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
	display_ (displayFunc),
	reDisplay_ (reDisplayFunc),
	label (BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), "")
{
	add (&label);
}

inline Widget* ValueRadialMeter::clone () const 
{
	Widget* f = new ValueRadialMeter (urid_, title_);
	f->copy (this);
	return f;
}

inline void ValueRadialMeter::copy (const ValueRadialMeter* that)
{
	display_ = that->display_;
	reDisplay_ = that->reDisplay_;
	label.copy (&that->label);
	RadialMeter::copy (that);
}

inline void ValueRadialMeter::resize ()
{
	if (children_.size() == 1) resize (BUtilities::Point<> (BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH, BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT));

	else
	{
		label.resize();
		label.moveTo (getXOffset(), getYOffset());
		RadialMeter::resize();
	}
}

inline void ValueRadialMeter::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void ValueRadialMeter::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void ValueRadialMeter::update ()
{
	Label* f = dynamic_cast<Label*>(focus_);
	if (f)
	{
		f->setText(getTitle() + ": " + std::to_string (this->getValue()));
		f->resize();
	}

	const double rad = 0.5 *
	(
		getEffectiveWidth() * BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT <  getEffectiveHeight() * BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH ?
		getEffectiveWidth() :
		getEffectiveHeight() * BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH / BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT
	);

	scale_ = BUtilities::Area<> 
	(
		getXOffset() + 0.5 * getEffectiveWidth() - rad , 
		getYOffset() + 0.5 * getEffectiveHeight() - rad * BWIDGETS_DEFAULT_VALUERADIALMETER_HEIGHT / BWIDGETS_DEFAULT_VALUERADIALMETER_WIDTH, 
		2.0 * rad, 
		2.0 * rad
	);

	label.setText (display_ (getValue()));
	label.resize();
	label.moveTo (label.center(), scale_.getPosition().y + scale_.getHeight());

	Widget::update();
}

inline std::string ValueRadialMeter::valueToString (const double& x)
{
	const int dPre = ((x == 0) || (fabs (x) <= 1.0) ? 1 : log10 (fabs (x)));
	const int dPost = std::max (4 - dPre, 0);
	char buf[256];
	std::sprintf (buf, ("%1." + std::to_string (dPost) + "f").c_str(), x);
	return std::string (buf);
}

inline double ValueRadialMeter::stringToValue (const std::string& s)
{
	return std::stod (s);
}

}

#endif /* BWIDGETS_VALUERADIALMETER_HPP_ */
