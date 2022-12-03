/* Window.cpp
 * Copyright (C) 2018, 2019 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <cairo/cairo.h>
#ifdef PKG_HAVE_FONTCONFIG
#include <fontconfig/fontconfig.h>
#endif /*PKG_HAVE_FONTCONFIG*/

#include "Window.hpp"
#include "pugl/pugl/cairo.h"
#include "../BEvents/ExposeEvent.hpp"
#include "../BEvents/PointerEvent.hpp"
#include "../BEvents/ValueChangedEvent.hpp"
#include "../BEvents/WheelEvent.hpp"
#include "../BEvents/KeyEvent.hpp"
#include "../BEvents/PointerFocusEvent.hpp"
#include "Supports/Closeable.hpp"
#include "Supports/Clickable.hpp"
#include "Supports/Draggable.hpp"
#include "Supports/PointerFocusable.hpp"
#include "Supports/KeyPressable.hpp"
#include "Supports/Messagable.hpp"
#include "Supports/Pointable.hpp"
#include "Supports/Scrollable.hpp"
#include "Supports/Valueable.hpp"


namespace BWidgets
{

Window::Window () : Window (BWIDGETS_DEFAULT_WINDOW_WIDTH, BWIDGETS_DEFAULT_WINDOW_HEIGHT, 0) {}

Window::Window (const uint32_t urid, const std::string& title) :
	Window (BWIDGETS_DEFAULT_WINDOW_WIDTH, BWIDGETS_DEFAULT_WINDOW_HEIGHT, 0, urid, title) {}

Window::Window (const double width, const double height, PuglNativeView nativeWindow, 
		uint32_t urid, std::string title, bool resizable,
		PuglWorldType worldType, int worldFlag) :
		Widget (0.0, 0.0, width, height, urid, title),
		zoom_ (1.0),
		keyGrabStack_ (), 
		buttonGrabStack_ (),
		world_ (NULL), 
		worldType_ (worldType),
		view_ (NULL), 
		nativeWindow_ (nativeWindow),
		quit_ (false), 
		focused_ (false), 
		pointer_ (),
		eventQueue_ ()
{
	main_ = this;
	layer_ = BWIDGETS_DEFAULT_WINDOW_LAYER;

	world_ = puglNewWorld (worldType, worldFlag);
	puglSetClassName (world_, "BWidgets");

	view_ = puglNewView (world_);
	if (nativeWindow_ != 0) puglSetParentWindow(view_, nativeWindow_);
	puglSetWindowTitle(view_, title.c_str());
	puglSetDefaultSize (view_, getWidth (), getHeight ());
	puglSetViewHint(view_, PUGL_RESIZABLE, resizable ? PUGL_TRUE : PUGL_FALSE);
	puglSetViewHint(view_, PUGL_IGNORE_KEY_REPEAT, PUGL_TRUE);
	puglSetWorldHandle(world_, this);
	puglSetHandle (view_, this);
	puglSetBackend(view_, puglCairoBackend());
	puglSetEventFunc (view_, Window::translatePuglEvent);
	puglRealize (view_);
	puglShow (view_);

	emitExposeEvent();
}

Window::~Window ()
{
	hide();
	while (!children_.empty ())
	{
		Widget* w = dynamic_cast<Widget*>(children_.front ());
		if (w) release (w);
	}
	purgeEventQueue ();
	keyGrabStack_.clear ();
	buttonGrabStack_.clear ();
	puglFreeView (view_);
	puglFreeWorld (world_);
	main_ = nullptr;	// Important switch for the super destructor. It took
						// days of debugging ...

	// Cleanup debug information for memory checkers
	// Remove if cairo may still be live at this timepoint of call.
	// (e.g. within plugins !!!)
	if (worldType_ == PUGL_PROGRAM) 
	{
		cairo_debug_reset_static_data();
#ifdef PKG_HAVE_FONTCONFIG
		FcFini();
#endif /*PKG_HAVE_FONTCONFIG*/
	}
}

void Window::setZoom (const double zoom)
{
	if (zoom != zoom_)
	{
		zoom_ = zoom;
		update();
	}
}

double Window::getZoom () const
{
	return zoom_;
}

PuglView* Window::getPuglView () {return view_;}

cairo_t* Window::getPuglContext ()
{
	if (view_) return (cairo_t*) puglGetContext (view_);
	else return NULL;
}

void Window::run ()
{
	while (!quit_) handleEvents();
}

void Window::onConfigureRequest (BEvents::Event* event)
{

	Widget::onConfigureRequest (event);
	BEvents::ExposeEvent* ev = dynamic_cast<BEvents::ExposeEvent*>(event);
	if (ev && (getExtends () != ev->getArea().getExtends () / getZoom())) Widget::resize (ev->getArea().getExtends () / getZoom());
}

void Window::onCloseRequest (BEvents::Event* event)
{
	BEvents::WidgetEvent* ev = dynamic_cast<BEvents::WidgetEvent*>(event);
	if (ev && (ev->getRequestWidget () == this)) quit_ = true;
	else Closeable::onCloseRequest (event);
}

void Window::onExposeRequest (BEvents::Event* event)
{
	BEvents::ExposeEvent* ev = dynamic_cast<BEvents::ExposeEvent*>(event);
	if (ev) puglPostRedisplayRect (view_,	{ev->getArea().getX() * getZoom(), 
											 ev->getArea().getY() * getZoom(), 
											 ev->getArea().getWidth() * getZoom(), 
											 ev->getArea().getHeight() * getZoom()});
}

void Window::addEventToQueue (BEvents::Event* event)
{
	// Try to merge with precursor event
	if
	(
		(event) &&
		(event->getWidget()) &&
		(!eventQueue_.empty ()) &&
		(eventQueue_.back())
	)
	{
		BEvents::Event::EventType eventType = event->getEventType();

		if
		(
			(event->getWidget()->isEventMergeable(eventType)) &&
			(
				(eventType & BEvents::Event::CONFIGURE_REQUEST_EVENT) ||
				(eventType & BEvents::Event::EXPOSE_REQUEST_EVENT) ||
				(eventType & BEvents::Event::POINTER_MOTION_EVENT) ||
				(eventType & BEvents::Event::POINTER_DRAG_EVENT) ||
				(eventType & BEvents::Event::WHEEL_SCROLL_EVENT) ||
				(eventType & BEvents::Event::VALUE_CHANGED_EVENT)
			)
		)
		{
			// Check for mergeable precursor events
			for (std::list<BEvents::Event*>::reverse_iterator rit = eventQueue_.rbegin(); rit != eventQueue_.rend(); ++rit)
			{
				BEvents::Event* precursor = *rit;

				if ((precursor->getEventType() & eventType) && (event->getWidget () == precursor->getWidget ()))
				{
					// CONFIGURE_EVENT
					if (eventType & BEvents::Event::CONFIGURE_REQUEST_EVENT)
					{
						BEvents::ExposeEvent* firstEvent = (BEvents::ExposeEvent*) precursor;
						BEvents::ExposeEvent* nextEvent = (BEvents::ExposeEvent*) event;

						BUtilities::Area<> area = nextEvent->getArea ();
						firstEvent->setArea (area);

						delete event;
						return;
					}

					// EXPOSE_EVENT
					if (eventType & BEvents::Event::EXPOSE_REQUEST_EVENT)
					{
						BEvents::ExposeEvent* firstEvent = (BEvents::ExposeEvent*) precursor;
						BEvents::ExposeEvent* nextEvent = (BEvents::ExposeEvent*) event;

						BUtilities::Area<> area = firstEvent->getArea ();
						area.extend (nextEvent->getArea ());
						firstEvent->setArea (area);

						delete event;
						return;
					}


					// POINTER_MOTION_EVENT
					else if (eventType & BEvents::Event::POINTER_MOTION_EVENT)
					{
						BEvents::PointerEvent* firstEvent = (BEvents::PointerEvent*) precursor;
						BEvents::PointerEvent* nextEvent = (BEvents::PointerEvent*) event;

						firstEvent->setPosition (nextEvent->getPosition ());
						firstEvent->setDelta (firstEvent->getDelta () + nextEvent->getDelta ());

						delete event;
						return;
					}

					// POINTER_DRAG_EVENT
					else if (eventType & BEvents::Event::POINTER_DRAG_EVENT)
					{
						BEvents::PointerEvent* firstEvent = (BEvents::PointerEvent*) precursor;
						BEvents::PointerEvent* nextEvent = (BEvents::PointerEvent*) event;

						if
						(
							(nextEvent->getButton() == firstEvent->getButton()) &&
							(nextEvent->getOrigin() == firstEvent->getOrigin())
						)
						{
							firstEvent->setPosition (nextEvent->getPosition ());
							firstEvent->setDelta (firstEvent->getDelta () + nextEvent->getDelta ());

							delete event;
							return;
						}
					}


					// WHEEL_SCROLL_EVENT
					else if (eventType & BEvents::Event::WHEEL_SCROLL_EVENT)
					{
						BEvents::WheelEvent* firstEvent = (BEvents::WheelEvent*) precursor;
						BEvents::WheelEvent* nextEvent = (BEvents::WheelEvent*) event;

						if (nextEvent->getPosition() == firstEvent->getPosition())
						{
							firstEvent->setDelta (firstEvent->getDelta () + nextEvent->getDelta ());

							delete event;
							return;
						}
					}

					// VALUE_CHANGED_EVENT
					else if (eventType & BEvents::Event::VALUE_CHANGED_EVENT)
					{
						if (dynamic_cast<BEvents::ValueChangedEvent*>(precursor))
						{
							dynamic_cast<BEvents::ValueChangedEvent*>(precursor)->setValue (event);
							delete event;
						}
						
						return;
					}
				}
			}
		}
	}

	eventQueue_.push_back (event);
}

BDevices::DeviceGrabStack<uint32_t>* Window::getKeyGrabStack () {return &keyGrabStack_;}

BDevices::DeviceGrabStack<BDevices::MouseDevice>* Window::getButtonGrabStack () {return &buttonGrabStack_;}

void Window::handleEvents ()
{
	puglUpdate (world_, 0);
	translateTimeEvent ();

	while (!eventQueue_.empty ())
	{
		BEvents::Event* event = eventQueue_.front ();
		eventQueue_.pop_front ();

		if (event)
		{
			Widget* widget = event->getWidget ();
			if (widget)
			{
				BEvents::Event::EventType eventType = event->getEventType ();

				switch (eventType)
				{
				case BEvents::Event::CONFIGURE_REQUEST_EVENT:
					widget->onConfigureRequest (event);
					break;

				// Expose events: Forward to pugl!
				case BEvents::Event::EXPOSE_REQUEST_EVENT:
					widget->onExposeRequest (event);
					break;

				case BEvents::Event::CLOSE_REQUEST_EVENT:
					if (widget->is<Closeable>()) dynamic_cast<Closeable*> (widget)->onCloseRequest (event);
					break;

				case BEvents::Event::KEY_PRESS_EVENT:
					buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
					if (widget->is<KeyPressable>()) dynamic_cast<KeyPressable*> (widget)->onKeyPressed (event);
					break;

				case BEvents::Event::KEY_RELEASE_EVENT:
					buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
					if (widget->is<KeyPressable>()) dynamic_cast<KeyPressable*> (widget)->onKeyReleased (event);
					break;

				case BEvents::Event::BUTTON_PRESS_EVENT:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus();
						buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
						buttonGrabStack_.add
						(
							BDevices::DeviceGrab<BDevices::MouseDevice>
							(
								widget,
								BDevices::MouseDevice(be->getButton (), be->getPosition())
							)
						);
						if (widget->is<Clickable>()) dynamic_cast<Clickable*> (widget)->onButtonPressed (be);
					}
					break;

				case BEvents::Event::BUTTON_RELEASE_EVENT:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus ();
						buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
						buttonGrabStack_.remove
						(
							BDevices::DeviceGrab<BDevices::MouseDevice>
							(
								widget,
								BDevices::MouseDevice(be->getButton (), be->getPosition())
							)
						);
						if (widget->is<Clickable>()) dynamic_cast<Clickable*> (widget)->onButtonReleased (be);
					}
					break;

				case BEvents::Event::BUTTON_CLICK_EVENT:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus ();
						buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
						buttonGrabStack_.remove
						(
							BDevices::DeviceGrab<BDevices::MouseDevice>
							(
								widget,
								BDevices::MouseDevice(be->getButton (), be->getPosition())
							)
						);
						if (widget->is<Clickable>()) dynamic_cast<Clickable*> (widget)->onButtonClicked (be);
					}
					break;

				case BEvents::Event::POINTER_MOTION_EVENT:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus ();
						buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
						BUtilities::Point<> p = widget->getAbsolutePosition() + be->getPosition();
						Widget* w = getWidgetAt 
						(
							p, 
							[] (const Widget* f) 
							{
								return dynamic_cast<const PointerFocusable*>(f) && dynamic_cast<const PointerFocusable*>(f)->isFocusable();
							}
						);
						if (w)
						{
							buttonGrabStack_.add
							(
								BDevices::DeviceGrab<BDevices::MouseDevice>
								(
									w,
									BDevices::MouseDevice(BDevices::MouseDevice::NO_BUTTON, p - w->getAbsolutePosition())
								)
							);
						}
						if (widget->is<Pointable>()) dynamic_cast<Pointable*> (widget)->onPointerMotion (be);
					}
					break;

				case BEvents::Event::POINTER_DRAG_EVENT:
					unfocus ();
					buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
					if (widget->is<Draggable>()) dynamic_cast<Draggable*> (widget)->onPointerDragged(event);
					break;

				case BEvents::Event::WHEEL_SCROLL_EVENT:
					unfocus ();
					buttonGrabStack_.remove (BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON));
					if (widget->is<Scrollable>()) dynamic_cast<Scrollable*> (widget)->onWheelScrolled(event);
					break;

				case BEvents::Event::VALUE_CHANGED_EVENT:
					if (widget->is<Valueable>()) dynamic_cast<Valueable*>(widget)->onValueChanged(event);
					break;

				case BEvents::Event::POINTER_FOCUS_IN_EVENT:
					if (widget->is<PointerFocusable>()) dynamic_cast<PointerFocusable*> (widget)->onFocusIn(event);
					break;

				case BEvents::Event::POINTER_FOCUS_OUT_EVENT:
					if (widget->is<PointerFocusable>()) dynamic_cast<PointerFocusable*> (widget)->onFocusOut(event);
					break;

				case BEvents::Event::MESSAGE_EVENT:
					if (widget->is<Messagable>()) dynamic_cast<Messagable*> (widget)->onMessage (event);
					break;

				default:
					break;
				}

			}
			delete event;
		}
	}
}

PuglStatus Window::translatePuglEvent (PuglView* view, const PuglEvent* puglEvent)
{
	Window* w = (Window*) puglGetHandle (view);
	if (!w) return PUGL_BAD_PARAMETER;

	switch (puglEvent->type) {

	case PUGL_KEY_PRESS:
		{
			if ((puglEvent->key.key >= PUGL_KEY_F1) && (puglEvent->key.key <= PUGL_KEY_PAUSE))
			{
				uint32_t key = puglEvent->key.key;
				BDevices::DeviceGrab<uint32_t>* grab = w->getKeyGrabStack()->getGrab(key);
				Widget* widget = (grab ? grab->getWidget() : nullptr);
				if (widget && widget->is<KeyPressable>())
				{
					w->addEventToQueue(new BEvents::KeyEvent (widget, BEvents::Event::KEY_PRESS_EVENT, puglEvent->key.x, puglEvent->key.y, key));
				}
			}
		}
		break;

	case PUGL_KEY_RELEASE:
		{
			if ((puglEvent->key.key >= PUGL_KEY_F1) && (puglEvent->key.key <= PUGL_KEY_PAUSE))
			{
				uint32_t key = puglEvent->key.key;
				BDevices::DeviceGrab<uint32_t>* grab = w->getKeyGrabStack()->getGrab(key);
				Widget* widget = (grab ? grab->getWidget() : nullptr);
				if (widget && widget->is<KeyPressable>())
				{
					w->addEventToQueue(new BEvents::KeyEvent (widget, BEvents::Event::KEY_RELEASE_EVENT, puglEvent->key.x, puglEvent->key.y, key));
				}
			}
		}
		break;

		case PUGL_TEXT:
			{
				uint32_t key = puglEvent->text.character;
				BDevices::DeviceGrab<uint32_t>* grab = w->getKeyGrabStack()->getGrab(key);
				Widget* widget = (grab ? grab->getWidget() : nullptr);
				if (widget && widget->is<KeyPressable>())
				{
					w->addEventToQueue(new BEvents::KeyEvent (widget, BEvents::Event::KEY_PRESS_EVENT, puglEvent->text.x, puglEvent->text.y, key));
				}
			}
			break;

		case PUGL_BUTTON_PRESS:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->button.x, puglEvent->button.y) / w->getZoom();
			Widget* widget = w->getWidgetAt	(position, 
											 [] (Widget* w) {return w->is<Clickable>() || w->is<Draggable>();},
											 [] (Widget* w) {return w->isEventPassable(BEvents::Event::BUTTON_PRESS_EVENT);});
			if (widget && (widget != w))
			{
				w->addEventToQueue
				(
					new BEvents::PointerEvent
					(
						widget,
						BEvents::Event::BUTTON_PRESS_EVENT,
						position - widget->getAbsolutePosition (),
						position - widget->getAbsolutePosition (),
						BUtilities::Point<> (),
						(BDevices::MouseDevice::ButtonCode) puglEvent->button.button
					)
				);
			}
			w->pointer_ = position;
		}
		break;

	case PUGL_BUTTON_RELEASE:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->button.x, puglEvent->button.y) / w->getZoom();
			BDevices::MouseDevice::ButtonCode button = (BDevices::MouseDevice::ButtonCode) puglEvent->button.button;
			BDevices::MouseDevice mouse = BDevices::MouseDevice (button);
			BDevices::DeviceGrab<BDevices::MouseDevice>* grab = w->getButtonGrabStack()->getGrab(mouse);
			if (grab)
			{
				Widget* widget = grab->getWidget();
				if (widget)
				{
					std::set<BDevices::MouseDevice> buttonDevices = grab->getDevices();
					std::set<BDevices::MouseDevice>::iterator it = buttonDevices.find(mouse);
					BUtilities::Point<> origin = (it != buttonDevices.end() ? it->position : BUtilities::Point<> ());

					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::BUTTON_RELEASE_EVENT,
							position - widget->getAbsolutePosition (),
							origin,
							BUtilities::Point<> (),
							button
						)
					);


					// Also emit BUTTON_CLICK_EVENT ?
					Widget* widget2 = w->getWidgetAt	(position, 
														 [] (Widget* w) {return w->is<Clickable>() || w->is<Draggable>();},
														 [] (Widget* w) {return w->isEventPassable (BEvents::Event::BUTTON_CLICK_EVENT);});
					if (widget == widget2)
					{
						w->addEventToQueue
						(
							new BEvents::PointerEvent
							(
								widget,
								BEvents::Event::BUTTON_CLICK_EVENT,
								position - widget->getAbsolutePosition (),
								origin,
								BUtilities::Point<> (),
								button
							)
						);
					}
				}
			}
			w->pointer_ = position;
		}
		break;

	case PUGL_MOTION:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->motion.x, puglEvent->motion.y) / w->getZoom();
			BDevices::MouseDevice::ButtonCode button = BDevices::MouseDevice::NO_BUTTON;

			// Scan for pressed buttons associated with a widget
			for (int i = BDevices::MouseDevice::NO_BUTTON + 1; i < BDevices::MouseDevice::NR_OF_BUTTONS; ++i)
			{
				BDevices::MouseDevice::ButtonCode b = BDevices::MouseDevice::ButtonCode (i);
				BDevices::MouseDevice mouse = BDevices::MouseDevice (b);
				BDevices::DeviceGrab<BDevices::MouseDevice>* grab = w->getButtonGrabStack()->getGrab(mouse);

				if (grab)
				{
					button = b;
					Widget* widget = grab->getWidget();

					if (widget && widget->is<Draggable>())
					{
						std::set<BDevices::MouseDevice> buttonDevices = grab->getDevices();
						std::set<BDevices::MouseDevice>::iterator it = buttonDevices.find(mouse);
						BUtilities::Point<> origin = (it != buttonDevices.end() ? it->position : BUtilities::Point<> ());

						// new
						w->addEventToQueue
						(
							new BEvents::PointerEvent
							(
								widget,
								BEvents::Event::POINTER_DRAG_EVENT,
								position - widget->getAbsolutePosition (),
								origin,
								position - w->pointer_,
								button
							)
						);
					}
				}
			}
			// No button associated with a widget? Only POINTER_MOTION_EVENT or FOCUS_EVENT
			if (button == BDevices::MouseDevice::NO_BUTTON)
			{
				// POINTER_MOTION_EVENT
				Widget* widget = w->getWidgetAt	(position, 
												 [] (Widget* widget) {return widget->is<Pointable>();},
												 [] (Widget* widget) {return widget->isEventPassable (BEvents::Event::POINTER_MOTION_EVENT);});
				if (widget && (widget != w))
				{
					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::POINTER_MOTION_EVENT,
							position - widget->getAbsolutePosition (),
							BUtilities::Point<> (),
							position - w->pointer_,
							button));
				}

				// FOCUS_EVENT
				widget = w->getWidgetAt	(position, 
												 [] (Widget* widget) {return widget->is<PointerFocusable>();},
												 [] (Widget* widget) {return widget->isEventPassable (BEvents::Event::POINTER_FOCUS_IN_EVENT);});
				if (widget && (widget != w))
				{
					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::POINTER_MOTION_EVENT,
							position - widget->getAbsolutePosition (),
							BUtilities::Point<> (),
							position - w->pointer_,
							button));
				}


			}
			w->pointer_ = position;
		}
		break;

	case PUGL_SCROLL:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->scroll.x, puglEvent->scroll.y) / w->getZoom();
			BUtilities::Point<> scroll = BUtilities::Point<> (puglEvent->scroll.dx, puglEvent->scroll.dy) / w->getZoom();
			Widget* widget = w->getWidgetAt	(position, 
											 [] (Widget* widget) {return widget->is<Scrollable>();},
											 [] (Widget* widget) {return widget->isEventPassable (BEvents::Event::WHEEL_SCROLL_EVENT);});
			if (widget && (widget != w))
			{
				w->addEventToQueue
				(
					new BEvents::WheelEvent
					(
						widget,
						BEvents::Event::WHEEL_SCROLL_EVENT,
						position - widget->getAbsolutePosition (),
						scroll
					)
				);
			}
			w->pointer_ = position;
		}
		break;

	case PUGL_CONFIGURE:
		if (w->is<Visualizable>())
		{
			w->addEventToQueue
			(
				new BEvents::ExposeEvent
				(
					w, w,
					BEvents::Event::CONFIGURE_REQUEST_EVENT,
					puglEvent->configure.x,
					puglEvent->configure.y,
					puglEvent->configure.width,
					puglEvent->configure.height
				)
			);
		}
		break;

	// Expose events handled HERE
	case PUGL_EXPOSE:
		{
			// Calculate the non-zoomed area from the event data
			BUtilities::Area<> area = BUtilities::Area<>	(puglEvent->expose.x / w->getZoom(), 
															 puglEvent->expose.y / w->getZoom(), 
															 puglEvent->expose.width / w->getZoom(), 
															 puglEvent->expose.height / w->getZoom());

			// Get access to the host provided surface
			cairo_t* crw = w->getPuglContext ();
			if (crw && (cairo_status (crw) == CAIRO_STATUS_SUCCESS))
			{
				// Create a temporary window surface
				cairo_surface_t* windowSurface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w->getWidth() , w->getHeight());
				if (windowSurface && (cairo_surface_status (windowSurface) == CAIRO_STATUS_SUCCESS))
				{
					//Get access to the temporary window surface
					cairo_t* cr = cairo_create(windowSurface);
					if (cr && (cairo_status (cr) == CAIRO_STATUS_SUCCESS))
					{
						// Get a map of layered surfaces for the selected area
						std::map<int,cairo_surface_t*> storageSurfaces;
						w->display (storageSurfaces, BUtilities::Point<> (w->getWidth(), w->getHeight()), area);

						// Write all layered surfaces to the temporary window surface from back to front
						for (std::map<int,cairo_surface_t*>::reverse_iterator rit = storageSurfaces.rbegin(); rit != storageSurfaces.rend(); ++rit)
						{
							cairo_surface_t* s = rit->second;
							if (s && (cairo_surface_status (s) == CAIRO_STATUS_SUCCESS))
							{
								cairo_save (cr);
								cairo_set_source_surface (cr, s, 0.0, 0.0);
								cairo_paint (cr);
								cairo_restore (cr);
								cairo_surface_destroy(s);
							}
						}

						cairo_destroy (cr);	
					}

					// Write temporary window surface to the host provided surface
					cairo_save (crw);
					cairo_scale (crw, w->getZoom(), w->getZoom());
					cairo_set_source_surface (crw, windowSurface, 0.0, 0.0);
					cairo_paint (crw);
					cairo_restore (crw);
					cairo_surface_destroy (windowSurface);
				}
			}
		}
		break;

	case PUGL_CLOSE:
		if (w->is<Closeable>()) w->addEventToQueue (new BEvents::WidgetEvent (w, w, BEvents::Event::CLOSE_REQUEST_EVENT));
		break;

	default:
		break;
	}

	return PUGL_SUCCESS;
}

void Window::translateTimeEvent ()
{
	BDevices::MouseDevice mouse = BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON);
	BDevices::DeviceGrab<BDevices::MouseDevice>* grab = buttonGrabStack_.getGrab(mouse);
	if (grab)
	{		
		Widget* widget = grab->getWidget();
		if (widget)
		{
			PointerFocusable* focus = dynamic_cast<PointerFocusable*> (widget);
			if (focus)
			{
				std::set<BDevices::MouseDevice> buttonDevices = grab->getDevices();
				std::set<BDevices::MouseDevice>::iterator it = buttonDevices.find(mouse);
				BUtilities::Point<> position = (it != buttonDevices.end() ? it->position : BUtilities::Point<> ());
				std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now();
				std::chrono::steady_clock::time_point pointerTime = (it != buttonDevices.end() ? it->getTime() : nowTime);
				std::chrono::milliseconds diffMs = std::chrono::duration_cast<std::chrono::milliseconds> (nowTime - pointerTime);

				if ((!focused_) && focus->isFocusActive (diffMs))
				{
					addEventToQueue (new BEvents::PointerFocusEvent (widget, BEvents::Event::POINTER_FOCUS_IN_EVENT, position));
					focused_ = true;
				}

				else if (focused_ && (!focus->isFocusActive (diffMs)))
				{
					addEventToQueue (new BEvents::PointerFocusEvent (widget, BEvents::Event::POINTER_FOCUS_OUT_EVENT, position));
					focused_ = false;
				}
			}
			else focused_ = false;
		}
		else focused_ = false;
	}
	else focused_ = false;
}

void Window::unfocus ()
{
	if (focused_)
	{
		BDevices::MouseDevice mouse = BDevices::MouseDevice (BDevices::MouseDevice::NO_BUTTON);
		BDevices::DeviceGrab<BDevices::MouseDevice>* grab = buttonGrabStack_.getGrab (mouse);
		if (grab)
		{
			Widget* widget = grab->getWidget();
			if (widget)
			{
				PointerFocusable* focus = dynamic_cast<PointerFocusable*> (widget);
				if (focus)
				{
					std::set<BDevices::MouseDevice> buttonDevices = grab->getDevices();
					std::set<BDevices::MouseDevice>::iterator it = buttonDevices.find(mouse);
					BUtilities::Point<> position = (it != buttonDevices.end() ? it->position : BUtilities::Point<> ());
					addEventToQueue (new BEvents::PointerFocusEvent (widget, BEvents::Event::POINTER_FOCUS_OUT_EVENT, position));
				}
			}
		}
		focused_ = false;
	}
}

void Window::purgeEventQueue (Widget* widget)
{
	for (std::list<BEvents::Event*>::iterator it = eventQueue_.begin (); it != eventQueue_.end (); /* empty */)
	{
		BEvents::Event* event = *it;
		if
		(
			(event) &&
			(
				// Nullptr = joker
				(widget == nullptr) ||
				// Hit
				(widget == event->getWidget ()) ||
				(
					// Hit in request widgets
					(
						(event->getEventType () & BEvents::Event::CONFIGURE_REQUEST_EVENT) ||
						(event->getEventType () & BEvents::Event::EXPOSE_REQUEST_EVENT) ||
						(event->getEventType () & BEvents::Event::CLOSE_REQUEST_EVENT)
					) &&
					(widget == ((BEvents::WidgetEvent*)event)->getRequestWidget ())
				)
			)
		)
		{
			it = eventQueue_.erase (it);
			delete event;
		}
		else ++it;
	}
}

bool Window::isQuit() const
{
	return quit_;
}

}
