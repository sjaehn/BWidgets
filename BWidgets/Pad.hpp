/* Pad.hpp
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

#ifndef BWIDGETS_PAD_HPP_
#define BWIDGETS_PAD_HPP_

#include "Widget.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Scrollable.hpp"
#include "Supports/ValueableTyped.hpp"
#include "Supports/ValidatableRange.hpp"
#include "Supports/ValueTransferable.hpp"
#include "Supports/KeyPressable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "../BEvents/PointerEvent.hpp"
#include "../BEvents/KeyEvent.hpp"
#include BWIDGETS_DEFAULT_DRAWPAD_PATH

#ifndef BWIDGETS_DEFAULT_PAD_WIDTH
#define BWIDGETS_DEFAULT_PAD_WIDTH 20
#endif

#ifndef BWIDGETS_DEFAULT_PAD_HEIGHT
#define BWIDGETS_DEFAULT_PAD_HEIGHT 20
#endif

namespace BWidgets
{
/**
 *  @brief  Widget imitating an LED pad.
 *  @tparam T  Value type.
 *
 *  %Pad is a Valueable widget imitating an LED pad. Its value is represented
 *  by its color from dark to bright. It supports user interaction via
 *  Clickable (switch on / off), Scrollable (increase / decrease value), and
 *  KeyPressable (to be implemented). 
 *  The visualble content of the %Pad is represented by FgColors.
 *
 *  The value type @a T can be used to specialize %Pad (e. g., by writing
 *  specialized @c draw() methods). @a T MUST support the standard comparison
 *  operators and MUST also support the standard arithmetic operators. It
 *  also MUST be compatible with ValueableTyped, ValidatableRange, and
 *  ValueTransferable.
 */
template <class T = double>
class Pad : public Widget, 
			public ValueableTyped<T>, 
			public ValidatableRange<T>, 
			public ValueTransferable<T>, 
			public Clickable, 
			public Scrollable,
			public KeyPressable
{

protected:
	T storedValue_;
	bool fineTuned_;

public:

	/**
	 *  @brief  Constructs a new %Pad object with default parameters.
	 */
	Pad ();

	/**
	 *  @brief  Constructs a new %Pad object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Pad (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %Pad with default size.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pad	(const T value, const T min, const T max, T step = 0.0, 
		 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %Pad.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param value  Initial value.
	 *  @param min  Lower value limit.
	 *  @param max  Upper value limit.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Pad	(const double x, const double y, const double width, const double height, 
		 const T value, const T min, const T max, T step = 0.0,
		 std::function<T (const T& x)> transferFunc = ValueTransferable<T>::noTransfer,
		 std::function<T (const T& x)> reTransferFunc = ValueTransferable<T>::noTransfer,
		 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

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
     *  @brief  Sets the range step size.
     *  @param step  Step size.
	 *
	 *  Also sets the number of sub steps to BWIDGETS_DEFAULT_NR_SUBSTEPS if 
	 *  step size is 0.0.
     */
    virtual void setStep (const double& step) override;

	/**
     *  @brief  Enters this %Pad.
     *
     *  Activates this %Pad, takes over keyboard control, and calls to leave 
	 *  all other widgets linked to the main Window to become the only entered 
	 *  Widget.
     */
    virtual void enter () override;

	/**
     *  @brief  Leaves this %Pad
     *
     *  De-activates this %Pad and release keyboard conrol.
     */
    virtual void leave () override;

	/**
     *  @brief  Method called when pointer button pressed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  pointer button pressed. By default, it calls its static callback 
     *  function.
     */
    virtual void onButtonPressed (BEvents::Event* event) override;

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

	/**
     *  @brief  Optimizes the widget extends.
     *
	 *  Resizes the widget to include all direct children into the widget
	 *  area. Resizes the widget to its standard size if this widget doesn't 
	 *  have any children.
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
    virtual void draw (const BUtilities::Area<>& area) override;
};

template <class T>
inline Pad<T>::Pad () : 
	Pad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT,
		 T(), T(), T() + 1.0, T(), 
		 ValueTransferable<T>::noTransfer, ValueTransferable<T>::noTransfer,  
		 BUTILITIES_URID_UNKNOWN_URID, "") 
{

}

template <class T>
inline Pad<T>::Pad	(const uint32_t urid, const std::string& title) :
	Pad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT, 
		 T(), T(), T() + 1.0, T(),
		 ValueTransferable<T>::noTransfer, ValueTransferable<T>::noTransfer, 
		 urid, title) 
{

}

template <class T>
inline Pad<T>::Pad	(const T value, const T min, const T max, T step, uint32_t urid, std::string title) :
	Pad	(0.0, 0.0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT, 
		 min, max, step, urid, 
		 ValueTransferable<T>::noTransfer, ValueTransferable<T>::noTransfer, 
		 urid, title) 
{

}

template <class T>
inline Pad<T>::Pad	(const double x, const double y, const double width, const double height, 
				 	 const T value, const T min, const T max, T step, 
					 std::function<T (const T& x)> transferFunc,
				 	 std::function<T (const T& x)> reTransferFunc,
					 uint32_t urid, std::string title) :
	Widget (x, y, width, height, urid, title),
	ValueableTyped<T> (value),
	ValidatableRange<T> (min, max, step),
	ValueTransferable<T> (transferFunc, reTransferFunc),
	Clickable(),
	Scrollable(),
	KeyPressable(),
	storedValue_ (value == min ? max : min),
	fineTuned_(false)
{
	setActivatable(true);
	setEnterable(true);
	setKeyPressable(true);
	grabDevice(BDevices::Keys(BDevices::Keys::KeyType::shiftL));
	grabDevice(BDevices::Keys(BDevices::Keys::KeyType::shiftR));
	if (step == 0.0) ValidatableRange<T>::setNrSubs(BWIDGETS_DEFAULT_NR_SUBSTEPS);
	setFocusText([](const Widget* w) {return	w->getTitle() + 
												": " + 
												(dynamic_cast<const Pad<T>*> (w) ? 
												 std::to_string (dynamic_cast<const Pad<T>*> (w)->getValue()) : 
												 "");});
}

template <class T>
inline Widget* Pad<T>::clone () const 
{
	Widget* f = new Pad (urid_, title_);
	f->copy (this);
	return f;
}

template <class T>
inline void Pad<T>::copy (const Pad* that)
{
	fineTuned_ = that->fineTuned_;
	storedValue_ = that->storedValue_;
	Scrollable::operator= (*that);
	Clickable::operator= (*that);
	ValueTransferable<T>::operator= (*that);
	ValidatableRange<T>::operator= (*that);
	ValueableTyped<T>::operator= (*that);
	KeyPressable::operator=(*that);
	Widget::copy (that);
}

template <class T>
inline void Pad<T>::setStep (const double &step)
{
	ValidatableRange<T>::setStep(step);
	if (step == 0.0) ValidatableRange<T>::setNrSubs(BWIDGETS_DEFAULT_NR_SUBSTEPS);
}

template <class T>
inline void Pad<T>::enter () 
{
	if (isEnterable() && (!isEntered()))
	{
		grabDevice (BDevices::Keys());
		Widget::enter();
	}
}

template <class T>
inline void Pad<T>::leave () 
{
	if (isEnterable() && isEntered())
	{
		if (isDeviceGrabbed(BDevices::Keys())) freeDevice(BDevices::Keys ());
		Widget::leave();
	}
}

template <class T>
inline void Pad<T>::resize ()
{
	BUtilities::Area<> a = (children_.empty()? BUtilities::Area<>(0, 0, BWIDGETS_DEFAULT_PAD_WIDTH, BWIDGETS_DEFAULT_PAD_HEIGHT) : BUtilities::Area<>());
	for (Linkable* c : children_)
	{
		Widget* w = dynamic_cast<Widget*>(c);
		if (w) a.extend (BUtilities::Area<>(w->getPosition(), w->getPosition() + w->getExtends()));
	}

	resize (a.getExtends());
}

template <class T>
inline void Pad<T>::resize (const double width, const double height) 
{
	resize (BUtilities::Point<> (width, height));
}

template <class T>
inline void Pad<T>::resize (const BUtilities::Point<> extends) 
{
	Widget::resize (extends);
}

template <class T>
inline void Pad<T>::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;
	
	enter();
	if (this->getValue() == this->getMin()) this->setValue (storedValue_);
	else
	{
			storedValue_ = this->getValue();
			this->setValue (this->getMin());
	};
	Clickable::onButtonPressed (event);
}

template <class T>
inline void Pad<T>::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;
	if (getHeight()) 
	{
		if (this->getStep() != T()) this->setValue (this->getValue() - wev->getDelta().y * (fineTuned_ ? this->getSubStep() : this->getStep()));
		else 
		{
			const double step = (fineTuned_ ?	1.0 / ((static_cast<double>(this->getNrSubs() + 1.0)) * this->getHeight()) :
												1.0 / this->getHeight());
			this->setValue (this->getValueFromRatio	(this->getRatioFromValue (this->getValue()) - wev->getDelta().y * step));
		}
	}
	Scrollable::onWheelScrolled (event);
}

template <class T>
inline void Pad<T>::onKeyPressed (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() != this) return; 
	
	BDevices::Keys::KeyType key = static_cast<BDevices::Keys::KeyType>(kev->getKey ());
	switch (kev->getKey ())
	{
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::shiftL):
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::shiftR):	
			fineTuned_ = true;
			break;

		case '-':
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::down):
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::left):		
			{
				BEvents::WheelEvent wev = BEvents::WheelEvent(this, BEvents::Event::EventType::wheelScrollEvent, 0.5 * getWidth(), 0.5 * getHeight(), 0, 1);
				onWheelScrolled(&wev);
			}
			break;

		case '+':
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::up):
		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::right):	
			{
				BEvents::WheelEvent wev = BEvents::WheelEvent(this, BEvents::Event::EventType::wheelScrollEvent, 0.5 * getWidth(), 0.5 * getHeight(), 0, -1);
				onWheelScrolled(&wev);
			}
			break;

		case BDevices::Keys::keyCode(BDevices::Keys::KeyType::escape):	
			leave();
			break;

		default:								
			break;
	}

	KeyPressable::onKeyPressed(event);
}

template <class T>
inline void Pad<T>::onKeyReleased (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() != this) return;

	BDevices::Keys::KeyType key = static_cast<BDevices::Keys::KeyType>(kev->getKey ());
	switch (key)
	{
		case BDevices::Keys::KeyType::shiftL:
		case BDevices::Keys::KeyType::shiftR:	fineTuned_ = false;
												break;

		default:								break;
	}

	KeyPressable::onKeyReleased(event);
}

template <class T>
inline void Pad<T>::draw ()
{
	draw (0, 0, getWidth(), getHeight());
}

template <class T>
inline void Pad<T>::draw (const double x0, const double y0, const double width, const double height)
{
	draw (BUtilities::Area<> (x0, y0, width, height));
}

template <class T>
inline void Pad<T>::draw (const BUtilities::Area<>& area)
	{
		if ((!cairoSurface()) || (cairo_surface_status (cairoSurface()) != CAIRO_STATUS_SUCCESS)) return;

		const double x0 = getXOffset ();
		const double y0 = getYOffset ();
		const double w = getEffectiveWidth ();
		const double h = getEffectiveHeight ();

		if ((h >= 1) && (w >= 1))
		{
			// Draw super class widget elements first
			Widget::draw (area);

			cairo_t* cr = cairo_create (cairoSurface());
			if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
			{
				// Limit cairo-drawing area
				cairo_rectangle (cr, area.getX (), area.getY (), area.getWidth (), area.getHeight ());
				cairo_clip (cr);

				const double rval = this->getRatioFromValue (this->getValue());
				const BStyles::Color butColor = getFgColors()[getStatus()].illuminate (-0.95 + 0.95 * rval);
				drawPad (cr, x0, y0, w, h, butColor);
				cairo_destroy (cr);
			}
		}
	}

}

#endif /* BWIDGETS_PAD_HPP_ */
