/* ImageDial.hpp
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

#ifndef BWIDGETS_IMAGEDIAL_HPP_
#define BWIDGETS_IMAGEDIAL_HPP_

#include "ImageRadialMeter.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/Scrollable.hpp"
#include "Supports/KeyPressable.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "../BEvents/KeyEvent.hpp"

#ifndef BWIDGETS_DEFAULT_IMAGEDIAL_WIDTH
#define BWIDGETS_DEFAULT_IMAGEDIAL_WIDTH BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH
#endif

#ifndef BWIDGETS_DEFAULT_IMAGEDIAL_HEIGHT
#define BWIDGETS_DEFAULT_IMAGEDIAL_HEIGHT BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT
#endif

namespace BWidgets
{

/**
 *  @brief  %ImageDial widget.
 *
 *  %ImageDial is a Valueable widget derived from ImageRadialMeter. It displays 
 *  a value in a radial representation in the same way as ImageRadialMeter and 
 *  additionally supports user interaction via Clickable, Draggable,
 *  Scrollable, and KeyPressable.
 */
class ImageDial :	public ImageRadialMeter, 
					public Clickable, 
					public Draggable, 
					public Scrollable,
					public KeyPressable
{

protected:

	bool fineTuned_;

public:

	/**
	 * @brief  Constructs an empty %ImageDial object.
	 * 
	 */
	ImageDial ();

	/**
	 *  @brief  Constructs an empty %ImageDial object.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	ImageDial (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a %ImageDial with default size.
	 *  @param staticImage  Filename of the static passive content image.
	 *  @param staticAnchor  Anchor point of the static active content which 
	 *  also represents the center of rotation
	 *  @param staticMinAngle  Angle for the min value.
	 *  @param staticMaxAngle  Angle for the max value.
	 *  @param activeImage  Optional, filename of the static active content 
	 *  image.
	 *  @param activeAnchor  Optional, anchor point of the static active
	 *  content which fits to center of rotation.
	 *  @param dynamicImage  Optional, filename of the dynamic content image.
	 *  @param dynamicAnchor  Optional, anchor point of the dynamic content
	 *  which fits to center of rotation.
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 *
	 *  Note: It's mandatory to provide an image for the static passive content
	 *  @a staticImage (background, labels, ...) and its anchor points for the
	 *  min value and the max value. The image area of @a staticImage MUST
	 *  cover ALL possible positions of the static active content 
	 *  @a activeImage and the dynamic content @a dynamicImage.
	 */
	ImageDial	(const std::string staticImage, const BUtilities::Point<> staticAnchor, const double staticMinAngle, const double staticMaxAngle,
				 std::string activeImage = "", BUtilities::Point<> activeAnchor = {0,0},
				 std::string dynamicImage = "", BUtilities::Point<> dynamicAnchor = {0,0},
				 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a %ImageDial.
	 *  @param x  %ImageDial X origin coordinate.
	 *  @param y  %ImageDial Y origin coordinate.
	 *  @param width  %ImageDial width.
	 *  @param height  %ImageDial height.
	 *  @param staticImage  Filename of the static passive content image.
	 *  @param staticAnchor  Anchor point of the static active content which 
	 *  also represents the center of rotation
	 *  @param staticMinAngle  Angle for the min value.
	 *  @param staticMaxAngle  Angle for the max value.
	 *  @param activeImage  Optional, filename of the static active content 
	 *  image.
	 *  @param activeAnchor  Optional, anchor point of the static active
	 *  content which fits to center of rotation.
	 *  @param dynamicImage  Optional, filename of the dynamic content image.
	 *  @param dynamicAnchor  Optional, anchor point of the dynamic content
	 *  which fits to center of rotation.
	 *  @param value  Optional, initial value.
	 *  @param min  Optional, lower value limit.
	 *  @param max  Optional, upper value limit.
	 *  @param step  Optional, value increment steps.
	 *  @param transferFunc  Optinonal, function to transfer a value from an
	 *  external context to the internal context.
	 *  @param reTransferFunc  Optinonal, function to transfer a value from the
	 *  internal context to an external context.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %ImageDial title (default = "").
	 *
	 *  Note: It's mandatory to provide an image for the static passive content
	 *  @a staticImage (background, labels, ...) and its anchor points for the
	 *  min value and the max value. The image area of @a staticImage MUST
	 *  cover ALL possible positions of the static active content 
	 *  @a activeImage and the dynamic content @a dynamicImage.
	 */
	ImageDial	(const double x, const double y, const double width, const double height, 
				 const std::string staticImage, const BUtilities::Point<> staticAnchor, const double staticMinAngle, const double staticMaxAngle,
				 std::string activeImage = "", BUtilities::Point<> activeAnchor = {0,0},
				 std::string dynamicImage = "", BUtilities::Point<> dynamicAnchor = {0,0},
				 double value = 0.0, double min = 0.0, double max = 1.0, double step = 0.0, 
				 std::function<double (const double& x)> transferFunc = ValueTransferable<double>::noTransfer,
				 std::function<double (const double& x)> reTransferFunc = ValueTransferable<double>::noTransfer,
				 uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	/**
	 *  @brief  Creates a clone of the %ImageDial. 
	 *  @return  Pointer to the new %ImageDial.
	 *
	 *  Creates a clone of this %ImageDial by copying all properties. But NOT its
	 *  linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const override; 

	/**
	 *  @brief  Copies from another %ImageDial. 
	 *  @param that  Other %ImageDial.
	 *
	 *  Copies all properties from another %ImageDial. But NOT its linkage.
	 */
	void copy (const ImageDial* that);

	/**
     *  @brief  Sets the range step size.
     *  @param step  Step size.
	 *
	 *  Also sets the number of sub steps to BWIDGETS_DEFAULT_NR_SUBSTEPS if 
	 *  step size is 0.0.
     */
    virtual void setStep (const double& step) override;

	/**
     *  @brief  Enters this %ImageDial.
     *
     *  Activates this %ImageDial, takes over keyboard control, and calls to leave 
	 *  all other widgets linked to the main Window to become the only entered 
	 *  Widget.
     */
    virtual void enter () override;

	/**
     *  @brief  Leaves this %ImageDial
     *
     *  De-activates this %ImageDial and release keyboard conrol.
     */
    virtual void leave () override;

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

};

inline ImageDial::ImageDial () :
	ImageDial	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH, BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT,
				 "", BUtilities::Point<>(0,0), 0.0, 2.0 * M_PI,
				 "", BUtilities::Point<> (0,0),
				 "", BUtilities::Point<> (0,0),
				 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 BUTILITIES_URID_UNKNOWN_URID, "")
{

}

inline ImageDial::ImageDial (const uint32_t urid, const std::string& title) : 
	ImageDial	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH, BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT,
				 "", BUtilities::Point<>(0,0), 0.0, 2.0 * M_PI,
				 "", BUtilities::Point<> (0,0),
				 "", BUtilities::Point<> (0,0),
				 0.0, 0.0, 1.0, 0.0, 
				 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
				 urid, title)
{

}

inline ImageDial::ImageDial (const std::string staticImage, const BUtilities::Point<> staticAnchor, 
							 const double staticMinAngle, const double staticMaxAngle,
							 std::string activeImage, BUtilities::Point<> activeAnchor,
							 std::string dynamicImage, BUtilities::Point<> dynamicAnchor,
							 double value, const double min, const double max, double step, 
							 uint32_t urid, std::string title) : 
	ImageDial	(0.0, 0.0, BWIDGETS_DEFAULT_IMAGERADIALMETER_WIDTH, BWIDGETS_DEFAULT_IMAGERADIALMETER_HEIGHT,
						 staticImage, staticAnchor, staticMinAngle, staticMaxAngle, 
						 activeImage, activeAnchor, dynamicImage, dynamicAnchor,
						 value, min, max, step, 
						 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
						 urid, title) 
{

}

inline ImageDial::ImageDial	(const double  x, const double y, const double width, const double height, 
							 const std::string staticImage, const BUtilities::Point<> staticAnchor, 
							 const double staticMinAngle, const double staticMaxAngle,
							 std::string activeImage, BUtilities::Point<> activeAnchor,
							 std::string dynamicImage, BUtilities::Point<> dynamicAnchor,
							 double value, const double min, const double max, double step,
							 std::function<double (const double& x)> transferFunc,
				 			 std::function<double (const double& x)> reTransferFunc, 
							 uint32_t urid, std::string title) :
		ImageRadialMeter	(x, y, width, height,
					 staticImage, staticAnchor, staticMinAngle, staticMaxAngle, activeImage, activeAnchor, dynamicImage, dynamicAnchor,
					 value, min, max, step, 
					 ValueTransferable<double>::noTransfer, ValueTransferable<double>::noTransfer, 
					 urid, title),
		Clickable(),
		Draggable(),
		Scrollable(),
		KeyPressable(), 
		fineTuned_(false)
{
	setActivatable(true);
	setEnterable(true);
	setKeyPressable(true);
	grabDevice(BDevices::Keys(BDevices::Keys::KeyType::shiftL));
	grabDevice(BDevices::Keys(BDevices::Keys::KeyType::shiftR));
	if (step == 0.0) setNrSubs(BWIDGETS_DEFAULT_NR_SUBSTEPS);
}

inline Widget* ImageDial::clone () const 
{
	Widget* f = new ImageDial (urid_, title_);
	f->copy (this);
	return f;
}

inline void ImageDial::copy (const ImageDial* that)
{
	fineTuned_ = that->fineTuned_;
	KeyPressable::operator=(*that);
	Scrollable::operator= (*that);
	Draggable::operator= (*that);
	Clickable::operator= (*that);
	ImageRadialMeter::copy (that);
}

inline void ImageDial::setStep (const double &step)
{
	ValidatableRange<double>::setStep(step);
	if (step == 0.0) setNrSubs(BWIDGETS_DEFAULT_NR_SUBSTEPS);
}

inline void ImageDial::enter () 
{
	if (isEnterable() && (!isEntered()))
	{
		grabDevice (BDevices::Keys());
		Widget::enter();
	}
}

inline void ImageDial::leave () 
{
	if (isEnterable() && isEntered())
	{
		if (isDeviceGrabbed(BDevices::Keys())) freeDevice(BDevices::Keys ());
		Widget::leave();
	}
}

inline void ImageDial::onButtonPressed (BEvents::Event* event)
{
	BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
	if (!pev) return;

	enter();
	if (staticMinAngle_ != staticMaxAngle_)
	{
		const double x0 = getXOffset();
		const double y0 = getYOffset();
		const double w = getEffectiveWidth();
		const double h = getEffectiveHeight();
		const double ws = cairo_image_surface_get_width (staticImageSurface_);
		const double hs = cairo_image_surface_get_height (staticImageSurface_);

		if ((ws >= 1.0) && (hs >= 1.0) && (w >= 1) && (h >= 1))
		{
			const double szs = ((w / ws < h / hs) ? (w / ws) : (h / hs));
			const double xc = x0 + 0.5 * w - 0.5 * ws * szs + staticAnchor_.x * szs;
			const double yc = y0 + 0.5 * h - 0.5 * hs * szs + staticAnchor_.y * szs;
			const double r = sqrt (pow (pev->getPosition().x - xc, 2.0) + pow (pev->getPosition().y - yc, 2.0));
			if (r >= 1.0)
			{
				double a = (pev->getPosition().y  < yc ? 2.0 * M_PI - acos ((pev->getPosition().x - xc) / r) : acos ((pev->getPosition().x - xc) / r));
				if (a < staticMinAngle_) a += 2.0 * M_PI;
				if (a > staticMaxAngle_) a -= 2.0 * M_PI;
				if ((a >= staticMinAngle_) && (a <= staticMaxAngle_)) 
				{
					if (step_ < 0.0) a = staticMaxAngle_ - (a - staticMinAngle_);
					setValue (getValueFromRatio	((a - staticMinAngle_) / (staticMaxAngle_ - staticMinAngle_)));
				}
			}
		}
	}
	Clickable::onButtonPressed (event);
}

inline void ImageDial::onPointerDragged (BEvents::Event* event)
{
	if (isClickable()) onButtonPressed (event);
	else
	{
		BEvents::PointerEvent* pev = dynamic_cast<BEvents::PointerEvent*> (event);
		if (!pev) return;

		enter();
		const double w = getEffectiveWidth();
		const double h = getEffectiveHeight();
		const double r = 0.5 * std::min (w, h);

		if ((staticMinAngle_ != staticMaxAngle_) && (r >= 1.0))
		{
			if (getStep() != 0.0) setValue (getValue() - pev->getDelta().y * (fineTuned_ ?	getSubStep() : getStep()));
			else 
			{
				const double step = (fineTuned_ ?	1.0 /	((static_cast<double>(getNrSubs() + 1.0)) * 
															 ((staticMaxAngle_ - staticMinAngle_) * r)) :
													1.0 /	((staticMaxAngle_ - staticMinAngle_) * r));
				setValue (getValueFromRatio (getRatioFromValue(getValue()) - pev->getDelta().y * step));
			}
		}
	}
	Draggable::onPointerDragged (event);
}

inline void ImageDial::onWheelScrolled (BEvents::Event* event)
{
	BEvents::WheelEvent* wev = dynamic_cast<BEvents::WheelEvent*> (event);
	if (!wev) return;

	const double w = getEffectiveWidth();
	const double h = getEffectiveHeight();
	const double r = 0.5 * std::min (w, h);

	if ((staticMinAngle_ != staticMaxAngle_) && (r >= 1.0))
	{
		if (getStep() != 0.0) setValue (getValue() - wev->getDelta().y * (fineTuned_ ?	getSubStep() : getStep()));
		else 
		{
			const double step = (fineTuned_ ?	1.0 /	((static_cast<double>(getNrSubs() + 1.0)) * 
															((staticMaxAngle_ - staticMinAngle_) * r)) :
												1.0 /	((staticMaxAngle_ - staticMinAngle_) * r));
			setValue (getValueFromRatio (getRatioFromValue(getValue()) - wev->getDelta().y * step));
		}
	}

	Scrollable::onWheelScrolled (event);
}

inline void ImageDial::onKeyPressed (BEvents::Event* event)
{
	BEvents::KeyEvent* kev = dynamic_cast<BEvents::KeyEvent*>(event);
	if (!kev) return;
	if (kev->getWidget() != this) return; 
	
	BDevices::Keys::KeyType key = static_cast<BDevices::Keys::KeyType>(kev->getKey ());
	switch (key)
	{
		case BDevices::Keys::KeyType::shiftL:
		case BDevices::Keys::KeyType::shiftR:	fineTuned_ = true;
												break;

		case BDevices::Keys::KeyType::down:
		case BDevices::Keys::KeyType::left:		{
													BEvents::WheelEvent wev = BEvents::WheelEvent(this, BEvents::Event::EventType::wheelScrollEvent, 0.5 * getWidth(), 0.5 * getHeight(), 0, 1);
													onWheelScrolled(&wev);
												}
												break;

		case BDevices::Keys::KeyType::up:
		case BDevices::Keys::KeyType::right:	{
													BEvents::WheelEvent wev = BEvents::WheelEvent(this, BEvents::Event::EventType::wheelScrollEvent, 0.5 * getWidth(), 0.5 * getHeight(), 0, -1);
													onWheelScrolled(&wev);
												}
												break;

		case BDevices::Keys::KeyType::escape:	leave();
												break;

		default:								break;
	}

	KeyPressable::onKeyPressed(event);
}

inline void ImageDial::onKeyReleased (BEvents::Event* event)
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

}

#endif /* BWIDGETS_IMAGEDIAL_HPP_ */
