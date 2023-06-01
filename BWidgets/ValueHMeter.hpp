/* ValueHMeter.hpp
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

#ifndef BWIDGETS_VALUEHMETER_HPP_
#define BWIDGETS_VALUEHMETER_HPP_

#include "HMeter.hpp"
#include "Label.hpp"
#include "Supports/ValueVisualizable.hpp"
#include <cmath>
#include <exception>
#include <functional>

#ifndef BWIDGETS_DEFAULT_VALUEHMETER_WIDTH
#define BWIDGETS_DEFAULT_VALUEHMETER_WIDTH 120.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEHMETER_HEIGHT
#define BWIDGETS_DEFAULT_VALUEHMETER_HEIGHT 20.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEHMETER_XSPACING
#define BWIDGETS_DEFAULT_VALUEHMETER_XSPACING 2.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEHMETER_YSPACING
#define BWIDGETS_DEFAULT_VALUEHMETER_YSPACING 8.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEHMETER_VALUE_POSITION
#define BWIDGETS_DEFAULT_VALUEHMETER_VALUE_POSITION ValuePosition::top
#endif

#ifndef BDOUBLE_TO_STRING
#define BDOUBLE_TO_STRING BWidgets::ValueHMeter::valueToString
#endif

#ifndef BSTRING_TO_DOUBLE
#define BSTRING_TO_DOUBLE BWidgets::ValueHMeter::stringToValue
#endif

namespace BWidgets
{

/**
 *  @brief  %ValueHMeter widget.
 *
 *  %ValueHMeter is a HMeter Widget with an additional label for
 *  displaying its value.
 */
class ValueHMeter : public HMeter,
					public ValueVisualizable
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
	 *  @brief  Constructs a default %ValueHMeter object.
	 */
	ValueHMeter ();

	/**
	 *  @brief  Constructs a default %ValueHMeter object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ValueHMeter (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ValueHMeter with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ValueHMeter	(const double value, const double min, const double max, double step = 0.0, 
					 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ValueHMeter.
	 *  @param x  %ValueHMeter X origin coordinate.
	 *  @param y  %ValueHMeter Y origin coordinate.
	 *  @param width  %ValueHMeter width.
	 *  @param height  %ValueHMeter height.
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
	 *  @param title  Optional, %ValueHMeter title (default = "").
	 *
	 *  The optional parameters @a displayFunc and @a reDisplayFunc can be used
	 *  as powerful tools to visualize the value in any way (including units,
	 *  prefixes, postfixes, text substitution, ...) and to parse it. By 
	 *  default, %ValueHMeter displays the value via @c valueToString() and
	 *  thus shows a decimal floating point representation with up to 3 digits
	 *  after the point.
	 */
	ValueHMeter	(const double x, const double y, const double width, const double height, 
					 const double value, const double min, const double max, double step = 0.0,
					 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
					 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
					 std::function<std::string (const double& x)> displayFunc = valueToString,
					 std::function<double (const std::string& s)> reDisplayFunc = stringToValue,
					 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ValueHMeter. 
	 *  @return  Pointer to the new %ValueHMeter.
	 *
	 *  Creates a clone of this %ValueHMeter by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ValueHMeter. 
	 *  @param that  Other %ValueHMeter.
	 *
	 *  Copies all properties from another %ValueHMeter. But NOT its linkage.
	 */
	void copy (const ValueHMeter* that);
	
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

inline ValueHMeter::ValueHMeter () :
	ValueHMeter	(
					 0.0, 0.0, BWIDGETS_DEFAULT_VALUEHMETER_WIDTH, BWIDGETS_DEFAULT_VALUEHMETER_HEIGHT, 
					 0.0, 0.0, 1.0, 0.0, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer, 
					 valueToString,
					 stringToValue,
					 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline ValueHMeter::ValueHMeter (const uint32_t urid, const std::string& title) : 
	ValueHMeter	(0.0, 0.0, BWIDGETS_DEFAULT_VALUEHMETER_WIDTH, BWIDGETS_DEFAULT_VALUEHMETER_HEIGHT, 
					 0.0, 0.0, 1.0, 0.0, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer,
					 valueToString,
					 stringToValue, 
				 	 urid, title) 
{

}

inline ValueHMeter::ValueHMeter (const double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	ValueHMeter	(0.0, 0.0, BWIDGETS_DEFAULT_VALUEHMETER_WIDTH, BWIDGETS_DEFAULT_VALUEHMETER_HEIGHT, 
					 value, min, max, step, 
					 ValueTransferable<double>::noTransfer, 
					 ValueTransferable<double>::noTransfer,
					 valueToString,
					 stringToValue, 
				 	 urid, title) 
{

}

inline ValueHMeter::ValueHMeter	(const double  x, const double y, const double width, const double height, 
									 const double value, const double min, const double max, double step, 
									 std::function<double (const double& x)> transferFunc,
						 			 std::function<double (const double& x)> reTransferFunc,
									 std::function<std::string (const double& x)> displayFunc,
									 std::function<double (const std::string& s)> reDisplayFunc,
									 uint32_t urid, std::string title) :
	HMeter (x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
	ValueVisualizable(true, BWIDGETS_DEFAULT_VALUEHMETER_VALUE_POSITION),
	display_ (displayFunc),
	reDisplay_ (reDisplayFunc),
	label (BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), "")
{
	add (&label);
}

inline Widget* ValueHMeter::clone () const 
{
	Widget* f = new ValueHMeter (urid_, title_);
	f->copy (this);
	return f;
}

inline void ValueHMeter::copy (const ValueHMeter* that)
{
	display_ = that->display_;
	reDisplay_ = that->reDisplay_;
	label.copy (&that->label);
	ValueVisualizable::operator= (*that);
	HMeter::copy (that);
}

inline void ValueHMeter::resize ()
{
	if (children_.size() == 1) resize (BUtilities::Point<> (BWIDGETS_DEFAULT_VALUEHMETER_WIDTH, BWIDGETS_DEFAULT_VALUEHMETER_HEIGHT));

	else
	{
		label.resize();
		label.moveTo (getXOffset(), getYOffset());
		HMeter::resize();
	}
}

inline void ValueHMeter::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

inline void ValueHMeter::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

inline void ValueHMeter::update ()
{
	if (!isValueVisualizable()) 
	{
		scale_ = BUtilities::Area<> (getXOffset(), getYOffset(), getEffectiveWidth(), getEffectiveHeight());
		label.hide();
	}

	else
	{
		// Update value label text
		label.setText (display_ (getValue()));
		label.resize();

		// Get the text extends for min and max value
		std::string minText = display_(getMin());
		const BUtilities::Point<> labelMinTextExtends = label.getExtends (minText);
		std::string maxText = display_(getMax());
		const BUtilities::Point<> labelMaxTextExtends = label.getExtends (maxText);

		// Calculate the width / height to be allocated for the value
		// depending on the ValuePosition and the max text extends
		const ValuePosition pos = getValuePosition();
		const double labelMaxWidth = std::max ({labelMinTextExtends.x, labelMaxTextExtends.x, label.getWidth()});
		const double labelMaxHeight = std::max ({labelMinTextExtends.y, labelMaxTextExtends.y, label.getHeight()});
		const double labelHeight = ((pos == ValuePosition::top) || (pos == ValuePosition::bottom)) * labelMaxHeight;
		const double labelWidth = ((pos == ValuePosition::left) || (pos == ValuePosition::right)) * labelMaxWidth;
		const double xspacing = ((pos == ValuePosition::left) || (pos == ValuePosition::right)) * BWIDGETS_DEFAULT_VALUEHMETER_XSPACING;
		const double yspacing = ((pos == ValuePosition::top) || (pos == ValuePosition::bottom)) * BWIDGETS_DEFAULT_VALUEHMETER_YSPACING;
		
		// Calculate the scale position.
		// Centered. And moved by the value text extends, if needed.  
		const double sw = getEffectiveWidth() - labelWidth - xspacing;
		const double sh = getEffectiveHeight() - labelHeight - yspacing;
		const double sx = getXOffset() + (pos == ValuePosition::left) * (labelWidth + xspacing);
		const double sy = getYOffset() + (pos == ValuePosition::top) * (labelHeight + yspacing);
		scale_ = BUtilities::Area<> (sx, sy, sw, sh);

		// Set value position
		label.moveTo	((pos == ValuePosition::left) * getXOffset() +
						 ((pos == ValuePosition::top) || (pos == ValuePosition::center) || (pos == ValuePosition::bottom)) * label.center() +
						 (pos == ValuePosition::right) * (sx + sw + xspacing),

						 (pos == ValuePosition::top) * getYOffset() +
						 ((pos == ValuePosition::left) || (pos == ValuePosition::center) || (pos == ValuePosition::right)) * label.middle() +
						 (pos == ValuePosition::bottom) * (sy + sh + yspacing));
		label.show();
	}

	Widget::update();
}

inline std::string ValueHMeter::valueToString (const double& x)
{
	const int dPre = ((x == 0) || (fabs (x) <= 1.0) ? 1 : log10 (fabs (x)) + 1);
	const int dPost = std::max (4 - dPre, 0);
	char buf[256];
	std::sprintf (buf, ("%1." + std::to_string (dPost) + "f").c_str(), x);
	return std::string (buf);
}

inline double ValueHMeter::stringToValue (const std::string& s)
{
	return std::stod (s);
}

}

#endif /* BWIDGETS_VALUEHMETER_HPP_ */
