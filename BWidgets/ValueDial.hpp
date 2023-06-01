/* ValueDial.hpp
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

#ifndef BWIDGETS_VALUEDIAL_HPP_
#define BWIDGETS_VALUEDIAL_HPP_

#include "Dial.hpp"
#include "EditLabel.hpp"
#include "Supports/ValueVisualizable.hpp"
#include <exception>
#include <functional>

#ifndef BWIDGETS_DEFAULT_VALUEDIAL_WIDTH
#define BWIDGETS_DEFAULT_VALUEDIAL_WIDTH 40.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEDIAL_HEIGHT
#define BWIDGETS_DEFAULT_VALUEDIAL_HEIGHT 50.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEDIAL_XSPACING
#define BWIDGETS_DEFAULT_VALUEDIAL_XSPACING 2.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEDIAL_YSPACING
#define BWIDGETS_DEFAULT_VALUEDIAL_YSPACING 2.0
#endif

#ifndef BWIDGETS_DEFAULT_VALUEDIAL_VALUE_POSITION
#define BWIDGETS_DEFAULT_VALUEDIAL_VALUE_POSITION ValuePosition::bottom
#endif

#ifndef BDOUBLE_TO_STRING
#define BDOUBLE_TO_STRING BWidgets::ValueDial::valueToString
#endif

#ifndef BSTRING_TO_DOUBLE
#define BSTRING_TO_DOUBLE BWidgets::ValueDial::stringToValue
#endif

namespace BWidgets
{

/**
 *  @brief  %ValueDial widget.
 *
 *  %ValueDial is a Dial Widget with an additional editable label for
 *  displaying its value.
 */
class ValueDial :	public Dial,
					public ValueVisualizable
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
	 *  @brief  Constructs a default %ValueDial object.
	 */
	ValueDial ();

	/**
	 *  @brief  Constructs a default %ValueDial object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ValueDial (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ValueDial with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	ValueDial	(const double value, const double min, const double max, double step = 0.0, 
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ValueDial.
	 *  @param x  %ValueDial X origin coordinate.
	 *  @param y  %ValueDial Y origin coordinate.
	 *  @param width  %ValueDial width.
	 *  @param height  %ValueDial height.
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
	 *  @param title  Optional, %ValueDial title (default = "").
	 *
	 *  The optional parameters @a displayFunc and @a reDisplayFunc can be used
	 *  as powerful tools to visualize the value in any way (including units,
	 *  prefixes, postfixes, text substitution, ...) and to parse it. By 
	 *  default, %ValueDial displays the value via @c valueToString() and
	 *  thus shows a decimal floating point representation with up to 3 digits
	 *  after the point.
	 */
	ValueDial	(const double x, const double y, const double width, const double height, 
				 const double value, const double min, const double max, double step = 0.0,
				 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
				 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
				 std::function<std::string (const double& x)> displayFunc = valueToString,
				 std::function<double (const std::string& s)> reDisplayFunc = stringToValue,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ValueDial. 
	 *  @return  Pointer to the new %ValueDial.
	 *
	 *  Creates a clone of this %ValueDial by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ValueDial. 
	 *  @param that  Other %ValueDial.
	 *
	 *  Copies all properties from another %ValueDial. But NOT its linkage.
	 */
	void copy (const ValueDial* that);

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

inline ValueDial::ValueDial () :
	ValueDial	(
				 0.0, 0.0, BWIDGETS_DEFAULT_VALUEDIAL_WIDTH, BWIDGETS_DEFAULT_VALUEDIAL_HEIGHT, 
				 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, 
				 ValueTransferable<double>::noTransfer, 
				 valueToString,
				 stringToValue,
				 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline ValueDial::ValueDial (const uint32_t urid, const std::string& title) : 
	ValueDial	(0.0, 0.0, BWIDGETS_DEFAULT_VALUEDIAL_WIDTH, BWIDGETS_DEFAULT_VALUEDIAL_HEIGHT, 
				 0.0, 0.0, 1.0, 0.0,  
				 ValueTransferable<double>::noTransfer, 
				 ValueTransferable<double>::noTransfer,
				 valueToString,
				 stringToValue, 
				 urid, title) 
{

}

inline ValueDial::ValueDial (const double value, const double min, const double max, double step, uint32_t urid, std::string title) : 
	ValueDial	(0.0, 0.0, BWIDGETS_DEFAULT_VALUEDIAL_WIDTH, BWIDGETS_DEFAULT_VALUEDIAL_HEIGHT, 
				 value, min, max, step, 
				 ValueTransferable<double>::noTransfer, 
				 ValueTransferable<double>::noTransfer,
				 valueToString,
				 stringToValue, 
				 urid, title) 
{

}

inline ValueDial::ValueDial	(const double  x, const double y, const double width, const double height, 
							 const double value, const double min, const double max, double step, 
							 std::function<double (const double& x)> transferFunc,
				 			 std::function<double (const double& x)> reTransferFunc,
							 std::function<std::string (const double& x)> displayFunc,
							 std::function<double (const std::string& s)> reDisplayFunc,
							 uint32_t urid, std::string title) :
	Dial (x, y, width, height, value, min, max, step, transferFunc, reTransferFunc, urid, title),
	ValueVisualizable(true, BWIDGETS_DEFAULT_VALUEDIAL_VALUE_POSITION),
	display_ (displayFunc),
	reDisplay_ (reDisplayFunc),
	label (BUtilities::Urid::urid (BUtilities::Urid::uri (urid) + "/label"), "")
{
	add (&label);
	label.setCallbackFunction (BEvents::Event::EventType::valueChangedEvent, labelChangedCallback);
	label.setEventPassable(BEvents::Event::EventType::wheelScrollEvent);
	label.setEventPassable(BEvents::Event::EventType::pointerDragEvent);
	label.setEventPassable(BEvents::Event::EventType::pointerFocusEvents);
}

inline Widget* ValueDial::clone () const 
{
	Widget* f = new ValueDial (urid_, title_);
	f->copy (this);
	return f;
}

inline void ValueDial::copy (const ValueDial* that)
{
	display_ = that->display_;
	reDisplay_ = that->reDisplay_;
	label.copy (&that->label);
	ValueVisualizable::operator= (*that);
	Dial::copy (that);
}

inline void ValueDial::update ()
{
	if (!isValueVisualizable()) 
	{
		scale_ = BUtilities::Area<> (getXOffset(), getYOffset(), getEffectiveWidth(), getEffectiveHeight());
		label.hide();
	}

	else
	{
		// Update value label text
		const bool lv = label.isValueable();
		label.setValueable (false);
		label.setText (display_ (getValue()));
		label.setValueable (lv);
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
		const double xspacing = ((pos == ValuePosition::left) || (pos == ValuePosition::right)) * BWIDGETS_DEFAULT_VALUEDIAL_XSPACING;
		const double yspacing = ((pos == ValuePosition::top) || (pos == ValuePosition::bottom)) * BWIDGETS_DEFAULT_VALUEDIAL_YSPACING;
		
		// Calculate the dial radius from the widget extends diminished by the extends allocaded for the value
		const double rad = 0.5 * std::max (0.0, std::min (getEffectiveWidth() - labelWidth - xspacing, getEffectiveHeight() - labelHeight - yspacing));

		// Calculate the scale position.
		// Centered. And moved by the value text extends, if needed.  
		const double sw = 2.0 * rad;
		const double sh = sw;
		const double sx = getXOffset() + 0.5 * (getEffectiveWidth() - labelWidth - xspacing) - rad + (pos == ValuePosition::left) * (labelWidth + xspacing);
		const double sy = getYOffset() + 0.5 * (getEffectiveHeight() - labelHeight - yspacing) - rad  + (pos == ValuePosition::top) * (labelHeight + yspacing);
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

	Widget::update(); // Skip Dial and RadialMeter
}

inline void ValueDial::labelChangedCallback (BEvents::Event* event)
{
	BEvents::ValueChangeTypedEvent<std::string>* vew = dynamic_cast<BEvents::ValueChangeTypedEvent<std::string>*>(event);
	if (!vew) return;
	EditLabel* widget = dynamic_cast<EditLabel*>(vew->getWidget());
	if (!widget) return;
	ValueDial* parent = dynamic_cast<ValueDial*>(widget->getParentWidget());
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

inline std::string ValueDial::valueToString (const double& x)
{
	const int dPre = ((x == 0) || (fabs (x) <= 1.0) ? 1 : log10 (fabs (x)) + 1);
	const int dPost = std::max (4 - dPre, 0);
	char buf[256];
	std::sprintf (buf, ("%1." + std::to_string (dPost) + "f").c_str(), x);
	return std::string (buf);
}

inline double ValueDial::stringToValue (const std::string& s)
{
	return std::stod (s);
}

}

#endif /* BWIDGETS_VALUEDIAL_HPP_ */
