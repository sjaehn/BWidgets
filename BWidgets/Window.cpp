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

#include "Supports/Linkable.hpp"
#include "Widget.hpp"
#include <cairo/cairo.h>
#include <list>
#ifdef PKG_HAVE_FONTCONFIG
#include <fontconfig/fontconfig.h>
#endif /*PKG_HAVE_FONTCONFIG*/

#include "Window.hpp"
#include "pugl/pugl/cairo.h"
#include "../BDevices/MouseButton.hpp"
#include "../BDevices/Keys.hpp"
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

void Window::freeDevice ()
{
	Widget::freeDevice();
	forEachChild
	(
		[](Linkable* obj) 
		{
			Widget* w = dynamic_cast<Widget*>(obj);
			if (w) w->freeDevice();
			return true;
		}
	);
}

void Window::freeDevice (const BDevices::Device &device)
{
	Widget::freeDevice (device);
	forEachChild
	(
		[&device](Linkable* obj) 
		{
			Widget* w = dynamic_cast<Widget*>(obj);
			if (w) w->freeDevice (device);
			return true;
		}
	);
}

std::list<Widget*> Window::listDeviceGrabbed (const BDevices::Device& device) const
{
	std::list<Widget*> widgets;
	forEachChild
	(
		[&device, &widgets] (Linkable* obj)
		{
			Widget* w = dynamic_cast<Widget*>(obj);
			if (w)
			{
				if (w->isDeviceGrabbed(device)) widgets.push_back(w);
			}
			return true;
		}
	);

	return widgets;
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
				(static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::configureRequestEvent)) ||
				(static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::exposeRequestEvent)) ||
				(static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::pointerMotionEvent)) ||
				(static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::pointerDragEvent)) ||
				(static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::wheelScrollEvent)) ||
				(static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::valueChangedEvent))
			)
		)
		{
			// Check for mergeable precursor events
			for (std::list<BEvents::Event*>::reverse_iterator rit = eventQueue_.rbegin(); rit != eventQueue_.rend(); ++rit)
			{
				BEvents::Event* precursor = *rit;

				if ((static_cast<uint32_t>(precursor->getEventType()) & static_cast<uint32_t>(eventType)) && (event->getWidget () == precursor->getWidget ()))
				{
					// CONFIGURE_EVENT
					if (static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::configureRequestEvent))
					{
						BEvents::ExposeEvent* firstEvent = (BEvents::ExposeEvent*) precursor;
						BEvents::ExposeEvent* nextEvent = (BEvents::ExposeEvent*) event;

						BUtilities::Area<> area = nextEvent->getArea ();
						firstEvent->setArea (area);

						delete event;
						return;
					}

					// EXPOSE_EVENT
					if (static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::exposeRequestEvent))
					{
						BEvents::ExposeEvent* firstEvent = (BEvents::ExposeEvent*) precursor;
						BEvents::ExposeEvent* nextEvent = (BEvents::ExposeEvent*) event;

						BUtilities::Area<> area = firstEvent->getArea ();
						area.extend (nextEvent->getArea ());
						firstEvent->setArea (area);

						delete event;
						return;
					}


					// pointerMotionEvent
					else if (static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::pointerMotionEvent))
					{
						BEvents::PointerEvent* firstEvent = (BEvents::PointerEvent*) precursor;
						BEvents::PointerEvent* nextEvent = (BEvents::PointerEvent*) event;

						firstEvent->setPosition (nextEvent->getPosition ());
						firstEvent->setDelta (firstEvent->getDelta () + nextEvent->getDelta ());

						delete event;
						return;
					}

					// pointerDragEvent
					else if (static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::pointerDragEvent))
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


					// wheelScrollEvent
					else if (static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::wheelScrollEvent))
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

					// ValueChangedEvent
					else if (static_cast<uint32_t>(eventType) & static_cast<uint32_t>(BEvents::Event::EventType::valueChangedEvent))
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
				case BEvents::Event::EventType::configureRequestEvent:
					widget->onConfigureRequest (event);
					break;

				// Expose events: Forward to pugl!
				case BEvents::Event::EventType::exposeRequestEvent:
					widget->onExposeRequest (event);
					break;

				case BEvents::Event::EventType::closeRequestEvent:
					if (widget->is<Closeable>()) dynamic_cast<Closeable*> (widget)->onCloseRequest (event);
					break;

				case BEvents::Event::EventType::keyPressEvent:
					unfocus();
					freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
					if (widget->is<KeyPressable>()) dynamic_cast<KeyPressable*> (widget)->onKeyPressed (event);
					break;

				case BEvents::Event::EventType::keyReleaseEvent:
					unfocus();
					freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
					if (widget->is<KeyPressable>()) dynamic_cast<KeyPressable*> (widget)->onKeyReleased (event);
					break;

				case BEvents::Event::EventType::buttonPressEvent:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus();
						freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
						widget->grabDevice(BDevices::MouseButton (be->getButton(), be->getPosition()));
						if (widget->is<Clickable>()) dynamic_cast<Clickable*> (widget)->onButtonPressed (be);
					}
					break;

				case BEvents::Event::EventType::buttonReleaseEvent:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus ();
						freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
						widget->freeDevice (BDevices::MouseButton (be->getButton ()));
						if (widget->is<Clickable>()) dynamic_cast<Clickable*> (widget)->onButtonReleased (be);
					}
					break;

				case BEvents::Event::EventType::buttonClickEvent:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus ();
						freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
						widget->freeDevice (BDevices::MouseButton (be->getButton ()));
						if (widget->is<Clickable>()) dynamic_cast<Clickable*> (widget)->onButtonClicked (be);
					}
					break;

				case BEvents::Event::EventType::pointerMotionEvent:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						unfocus ();
						freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
						BUtilities::Point<> p = widget->getAbsolutePosition() + be->getPosition();
						Widget* w = getWidgetAt 
						(
							p, 
							[] (const Widget* f) {return dynamic_cast<const PointerFocusable*>(f) && dynamic_cast<const PointerFocusable*>(f)->isFocusable();},
							[] (const Widget* f) {return f->isEventPassable(BEvents::Event::EventType::pointerFocusInEvent);}
						);
						if (w) w->grabDevice(BDevices::MouseButton (BDevices::MouseButton::ButtonType::none, p - w->getAbsolutePosition()));
						if (widget->is<Pointable>()) dynamic_cast<Pointable*> (widget)->onPointerMotion (be);
					}
					break;

				case BEvents::Event::EventType::pointerDragEvent:
					unfocus ();
					freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
					if (widget->is<Draggable>()) dynamic_cast<Draggable*> (widget)->onPointerDragged(event);
					break;

				case BEvents::Event::EventType::wheelScrollEvent:
					unfocus ();
					freeDevice (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
					if (widget->is<Scrollable>()) dynamic_cast<Scrollable*> (widget)->onWheelScrolled(event);
					break;

				case BEvents::Event::EventType::valueChangedEvent:
					if (widget->is<Valueable>()) dynamic_cast<Valueable*>(widget)->onValueChanged(event);
					break;

				case BEvents::Event::EventType::pointerFocusInEvent:
					if (widget->is<PointerFocusable>()) dynamic_cast<PointerFocusable*> (widget)->onFocusIn(event);
					break;

				case BEvents::Event::EventType::pointerFocusOutEvent:
					if (widget->is<PointerFocusable>()) dynamic_cast<PointerFocusable*> (widget)->onFocusOut(event);
					break;

				case BEvents::Event::EventType::messageEvent:
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
				std::list<Widget*> gwidgets = w->listDeviceGrabbed(BDevices::Keys());
				for (Widget* gw : gwidgets)
				{
					if (gw && gw->is<KeyPressable>())
					{
						w->addEventToQueue(new BEvents::KeyEvent (gw, BEvents::Event::EventType::keyPressEvent, puglEvent->key.x, puglEvent->key.y, key));
					}
				}
			}
		}
		break;

	case PUGL_KEY_RELEASE:
		{
			if ((puglEvent->key.key >= PUGL_KEY_F1) && (puglEvent->key.key <= PUGL_KEY_PAUSE))
			{
				uint32_t key = puglEvent->key.key;
				std::list<Widget*> gwidgets = w->listDeviceGrabbed(BDevices::Keys());
				for (Widget* gw : gwidgets)
				{
					if (gw && gw->is<KeyPressable>())
					{
						w->addEventToQueue(new BEvents::KeyEvent (gw, BEvents::Event::EventType::keyReleaseEvent, puglEvent->key.x, puglEvent->key.y, key));
					}
				}
			}
		}
		break;

		case PUGL_TEXT:
			{
				uint32_t key = puglEvent->text.character;
				std::list<Widget*> gwidgets = w->listDeviceGrabbed(BDevices::Keys());
				for (Widget* gw : gwidgets)
				{
					if (gw && gw->is<KeyPressable>())
					{
						w->addEventToQueue(new BEvents::KeyEvent (gw, BEvents::Event::EventType::keyPressEvent, puglEvent->key.x, puglEvent->key.y, key));
					}
				}
			}
			break;

		case PUGL_BUTTON_PRESS:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->button.x, puglEvent->button.y) / w->getZoom();
			Widget* widget = w->getWidgetAt	(position, 
											 [] (Widget* w) {return w->is<Clickable>() || w->is<Draggable>();},
											 [] (Widget* w) {return w->isEventPassable(BEvents::Event::EventType::buttonPressEvent);});
			if (widget && (widget != w))
			{
				w->addEventToQueue
				(
					new BEvents::PointerEvent
					(
						widget,
						BEvents::Event::EventType::buttonPressEvent,
						position - widget->getAbsolutePosition (),
						position - widget->getAbsolutePosition (),
						BUtilities::Point<> (),
						static_cast<BDevices::MouseButton::ButtonType>(puglEvent->button.button)
					)
				);
			}
			w->pointer_ = position;
		}
		break;

	case PUGL_BUTTON_RELEASE:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->button.x, puglEvent->button.y) / w->getZoom();
			BDevices::MouseButton::ButtonType button = static_cast<BDevices::MouseButton::ButtonType>(puglEvent->button.button);
			std::list<Widget*> gwidgets = w->listDeviceGrabbed (BDevices::MouseButton (button));

			for (Widget* widget : gwidgets)
			{
				BDevices::Device* dev = widget->getDevice(BDevices::MouseButton (button));
				BDevices::MouseButton* mdev = (dev ? dynamic_cast<BDevices::MouseButton*>(dev) : nullptr);
				BUtilities::Point<> origin = (mdev ? mdev->getPosition() : BUtilities::Point<> ());

				w->addEventToQueue
				(
					new BEvents::PointerEvent
					(
						widget,
						BEvents::Event::EventType::buttonReleaseEvent,
						position - widget->getAbsolutePosition (),
						origin,
						BUtilities::Point<> (),
						button
					)
				);

				// Also emit buttonClickEvent ?
				Widget* widget2 = w->getWidgetAt	(position, 
														[] (Widget* w) {return w->is<Clickable>() || w->is<Draggable>();},
														[] (Widget* w) {return w->isEventPassable (BEvents::Event::EventType::buttonClickEvent);});
				if (widget == widget2)
				{
					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::EventType::buttonClickEvent,
							position - widget->getAbsolutePosition (),
							origin,
							BUtilities::Point<> (),
							button
						)
					);
				}
			}
			w->pointer_ = position;
		}
		break;

	case PUGL_MOTION:
		{
			BUtilities::Point<> position = BUtilities::Point<> (puglEvent->motion.x, puglEvent->motion.y) / w->getZoom();
			BDevices::MouseButton::ButtonType button = BDevices::MouseButton::ButtonType::none;

			// Scan for pressed buttons associated with a widget => Drag event
			for (int i = static_cast<int>(BDevices::MouseButton::ButtonType::left); 
				 i <= static_cast<int>(BDevices::MouseButton::ButtonType::right); 
				 ++i)
			{
				BDevices::MouseButton::ButtonType b = static_cast<BDevices::MouseButton::ButtonType>(i);
				std::list<Widget*> gwidgets = w->listDeviceGrabbed (BDevices::MouseButton (b));
				if (!gwidgets.empty()) button = b;
				for (Widget* widget : gwidgets)
				{
					BDevices::Device* dev = widget->getDevice(BDevices::MouseButton (b));
					BDevices::MouseButton* mdev = (dev ? dynamic_cast<BDevices::MouseButton*>(dev) : nullptr);
					BUtilities::Point<> origin = (mdev ? mdev->getPosition() : BUtilities::Point<> ());

					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::EventType::pointerDragEvent,
							position - widget->getAbsolutePosition (),
							origin,
							position - w->pointer_,
							button
						)
					);
				}
			}

			// No button associated with a widget? Only pointerMotionEvent or FOCUS_EVENT
			if (button == BDevices::MouseButton::ButtonType::none)
			{
				// pointerMotionEvent
				Widget* widget = w->getWidgetAt	(position, 
												 [] (Widget* widget) {return widget->is<Pointable>();},
												 [] (Widget* widget) {return widget->isEventPassable (BEvents::Event::EventType::pointerMotionEvent);});
				if (widget && (widget != w))
				{
					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::EventType::pointerMotionEvent,
							position - widget->getAbsolutePosition (),
							BUtilities::Point<> (),
							position - w->pointer_,
							button));
				}

				// FOCUS_EVENT
				widget = w->getWidgetAt	(position, 
												 [] (Widget* widget) {return widget->is<PointerFocusable>();},
												 [] (Widget* widget) {return widget->isEventPassable (BEvents::Event::EventType::pointerFocusInEvent);});
				if (widget && (widget != w))
				{
					w->addEventToQueue
					(
						new BEvents::PointerEvent
						(
							widget,
							BEvents::Event::EventType::pointerMotionEvent,
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
											 [] (Widget* widget) {return widget->isEventPassable (BEvents::Event::EventType::wheelScrollEvent);});
			if (widget && (widget != w))
			{
				w->addEventToQueue
				(
					new BEvents::WheelEvent
					(
						widget,
						BEvents::Event::EventType::wheelScrollEvent,
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
					BEvents::Event::EventType::configureRequestEvent,
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
		if (w->is<Closeable>()) w->addEventToQueue (new BEvents::WidgetEvent (w, w, BEvents::Event::EventType::closeRequestEvent));
		break;

	default:
		break;
	}

	return PUGL_SUCCESS;
}

void Window::translateTimeEvent ()
{
	std::list<Widget*> gwidgets = listDeviceGrabbed (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
	if (gwidgets.empty()) focused_ = false;
	else
	{
		for (Widget* widget : gwidgets)
		{
			PointerFocusable* focus = dynamic_cast<PointerFocusable*> (widget);
			if (focus)
			{
				BDevices::Device* dev = widget->getDevice(BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
				BDevices::MouseButton* mdev = (dev ? dynamic_cast<BDevices::MouseButton*> (dev) : nullptr);
				BUtilities::Point<> position = (mdev ? mdev->getPosition() : BUtilities::Point<>());
				std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now();
				std::chrono::steady_clock::time_point pointerTime = (mdev ? mdev->getActionTime() : nowTime);
				std::chrono::milliseconds diffMs = std::chrono::duration_cast<std::chrono::milliseconds> (nowTime - pointerTime);

				if ((!focused_) && focus->isFocusActive (diffMs))
				{
					addEventToQueue (new BEvents::PointerFocusEvent (widget, BEvents::Event::EventType::pointerFocusInEvent, position));
					focused_ = true;
				}

				else if (focused_ && (!focus->isFocusActive (diffMs)))
				{
					addEventToQueue (new BEvents::PointerFocusEvent (widget, BEvents::Event::EventType::pointerFocusOutEvent, position));
					focused_ = false;
				}
			}
			else focused_ = false;
		}
	}
}

void Window::unfocus ()
{
	if (focused_)
	{
		std::list<Widget*> gwidgets = listDeviceGrabbed (BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
		for (Widget* widget : gwidgets)
		{
			BDevices::Device* dev = widget->getDevice(BDevices::MouseButton (BDevices::MouseButton::ButtonType::none));
			BDevices::MouseButton* mdev = (dev ? dynamic_cast<BDevices::MouseButton*> (dev) : nullptr);
			if (mdev)
			{
				PointerFocusable* focus = dynamic_cast<PointerFocusable*> (widget);
				if (focus)
				{
					BUtilities::Point<> position = (mdev ? mdev->getPosition() : BUtilities::Point<> ());
					addEventToQueue (new BEvents::PointerFocusEvent (widget, BEvents::Event::EventType::pointerFocusOutEvent, position));
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
						(static_cast<uint32_t>(event->getEventType ()) & static_cast<uint32_t>(BEvents::Event::EventType::configureRequestEvent)) ||
						(static_cast<uint32_t>(event->getEventType ()) & static_cast<uint32_t>(BEvents::Event::EventType::exposeRequestEvent)) ||
						(static_cast<uint32_t>(event->getEventType ()) & static_cast<uint32_t>(BEvents::Event::EventType::closeRequestEvent))
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
