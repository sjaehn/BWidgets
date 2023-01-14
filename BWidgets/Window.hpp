/* Window.hpp
 * Copyright (C) 2018, 2019 - 2023  Sven Jähnichen
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

#ifndef BWIDGETS_WINDOW_HPP_
#define BWIDGETS_WINDOW_HPP_

// Default BWidgets::Window settings (Note: use non-transparent backgrounds only)
#define BWIDGETS_DEFAULT_WINDOW_BACKGROUND BStyles::blackFill

#include <chrono>
#include "Widget.hpp"
#include "pugl/pugl/pugl.h"
#include "Supports/Closeable.hpp"

#ifndef BWIDGETS_DEFAULT_WINDOW_WIDTH
#define BWIDGETS_DEFAULT_WINDOW_WIDTH 600
#endif

#ifndef BWIDGETS_DEFAULT_WINDOW_HEIGHT
#define BWIDGETS_DEFAULT_WINDOW_HEIGHT 400
#endif

namespace BWidgets
{

/**
 *  @brief  Main %Window class of BWidgets.
 *
 *  The main %Window object controls the visibility of all linked Widgets. All
 *  Widgets need be be linked to the main %Window object to become visible.
 *
 *  The main %Window object also controls and routes the events emitted by the
 *  linked Widgets and by the host system in its event queue and its event
 *  handler. 
 *
 *  The full event routing process is:
 *  1.  Emission of an event either by a Widget either
 *      * by a host event and an assignment to a Widget by the main %Window
 *        translate function, or
 *      * by the Widget directly
 *      to the main %Window event queue.
 *  2.  Analyzing, merging and routing in the main %Window event handler and
 *      calling the Widget onXXX() method.
 *  3.  Responding in the Widget onXXX() method and optional call of a linked
 *      Callback function.
 *  4.  Optional, respond to the effect in a Callback function.
 *
 *  Note: There should only be one %Window object!
 */
class Window : public Widget, public Closeable
{
protected:
	double zoom_;
	PuglWorld* world_;
	PuglWorldType worldType_;
	PuglView* view_;
	PuglNativeView nativeWindow_;
	bool quit_;
	bool focused_;
	BUtilities::Point<> pointer_;
	std::list<BEvents::Event*> eventQueue_;

public:

	/**
	 *  @brief  Construct a %Window object with default parameters.
	 */
	Window ();

	/**
	 *  @brief  Construct a %Window object with default parameters.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Window (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Construct a %Window object.
	 *  @param width  Window width.
	 *  @param height  Window height.
	 *  @param nativeWindow  Pointer to the host provided native window or
	 *  NULL.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, Window title.
	 *  @param resizable  Optional, Window resizable or fixed size (default).
	 *  @param worldType  Optional, Program (default) or module / plugin.
	 *  @param worldFlag  Optional, PuglWorldFlags (default = 0).
	 */
	Window (const double width, const double height, PuglNativeView nativeWindow, 
		uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "BWidgets", bool resizable = false,
		PuglWorldType worldType = PUGL_PROGRAM, int worldFlag = 0);

	virtual ~Window ();

	/**
	 * @brief  Releases the control over all devices for all linked child
	 * widgets.
	 */
	virtual void freeDevice () override;

	/**
	 * @brief  Releases the control over a device for all linked child
	 * widgets.
	 * 
	 * @param device  Device
	 */
	virtual void freeDevice (const BDevices::Device& device) override;

	/**
	 * @brief  Get a list of all widgets linked to this window which grabbed
	 * a given device. 
	 * 
	 * @param device  Device
	 * @return  List of all widgets with device grabbed
	 */
	std::list<Widget*> listDeviceGrabbed (const BDevices::Device& device) const;

	/**
	 *  @brief  Sets the zoom factor visualization and user interaction.
	 *  @param zoom  Zoom factor.
	 */
	virtual void setZoom (const double zoom);

	/**
	 *  @brief  Gets the zoom factor visualization and user interaction.
	 *  @return  Zoom factor.
	 */
	double getZoom () const;

	/**
	 *  @brief  Get in contact to the host system via Pugl.
	 *  @return  Pointer to the PuglView.
	 */
	PuglView* getPuglView ();

	/**
	 *  @brief  Gets the (Cairo) context provided by the host system via Pugl.
	 *  @return  Pointer to the (Cairo) context.
	 */
	cairo_t* getPuglContext ();

	/**
	 *  @brief  Runs the %Window until it get closed.
	 *
	 *  For stand-alone applications.
	 */
	virtual void run ();

	/**
	 *  @brief  Queues an event until the next call of the @c handleEvents() 
	 *  method.
	 *  @param event  Event.
	 *
	 *  Add the @a event to the event queue. Also tries to merge the @a event
	 *  with the previous event of the queue if:
	 *  1. Both events are the same type.
	 *  2. The event type is eligible for merging.
	 *  3. Both events are emitted by the same widget.
	 *  4. The emitting widget allows event merging for the respective event
	 *     type (see @c EventMergeable::setEventMergeable() ).
	 */
	virtual void addEventToQueue (BEvents::Event* event);

	/**
	 *  @brief  Main Event handler. 
	 *
	 *  Iterates through the event queue, analyzes the events, and and routes
	 *  them to their respective @c onXXX() handling methods.
	 */
	virtual void handleEvents ();

	/**
	 *  @brief  Method called upon an expose request event. Exposes the visual 
	 *  content.
	 *  @param event  Expose request event containing the Widget that emitted
	 *  the event and the area that should be exposed.
	 *
	 *  This method calls the host system to emit a host-provided expose event
	 *  which is then interpreted in the @c translatePuglEvent() method where
	 *  it calls drawing of all linked child widget RGBA surfaces to the host
	 *  provided RGBA surface.
	 */
	virtual void onExposeRequest (BEvents::Event* event) override;

	/**
	 *  @brief  Method called upon a configure request event. Resizes the
	 *  %Window.
	 *  @param event  Configure event containing the Widget that emitted the 
	 *  event and the new area of the Widget.
	 */
	virtual void onConfigureRequest (BEvents::Event* event) override;

	/**
	 *  @brief  Method called upon a close request event. Sets the close flag
	 *  and thus ends the @c run() method.
	 *  @param event  Widget event containing the Widget that emitted the 
	 *  event.
	 */
	virtual void onCloseRequest (BEvents::Event* event) override;

	/**
	 *  @brief  Removes events from the event queue.
	 *  @param widget  Emitting widget (nullptr for all widgets).
	 */
	virtual void purgeEventQueue (Widget* widget = nullptr);

	/**
	 *  @brief  Checks if close of the main %Window is scheduled.
	 *  @return  True, if quit is scheduled, otherwise false.
	 */
	bool isQuit () const;

private:
	/**
	 *  @brief  Static event translation method to be called by Pugl.
	 *  @param view  Pointer to the PuglView.
	 *  @param event  Pointer to the PuglEvent.
	 *  @return  PuglStatus.
	 *
	 *  Event translation is performed in a multi step process and includes
	 *  analyzing the host-provided event and emission of an event of the
	 *  BEvent family:
	 *  1. Identify the host-provided event and analyze its parameters.
	 *  2. Create a new event of the BEvents family in the name of an 
	 *     associated widget (e.g., the top level clickable widget in the
	 *     case of a mouse click) or the main %Window.
	 *  3. Add this new event to the event queue.
	 */
	static PuglStatus translatePuglEvent (PuglView* view, const PuglEvent* event);

	void translateTimeEvent ();

	void unfocus();
};

}



#endif /* BWIDGETS_WINDOW_HPP_ */
