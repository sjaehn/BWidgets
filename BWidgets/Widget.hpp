/* Widget.hpp
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

#ifndef BWIDGETS_WIDGET_HPP_
#define BWIDGETS_WIDGET_HPP_

#include <cstdint>
#include <functional>
#include <set>
#include <string>
#include "Draws/Ergo/definitions.hpp"
#include "../BDevices/Device.hpp"
#include "../BUtilities/Dictionary.hpp"
#include "Supports/Linkable.hpp"
#include "Supports/Visualizable.hpp"
#include "Supports/EventMergeable.hpp"
#include "Supports/EventPassable.hpp"
#include "Supports/PointerFocusable.hpp"
#include "Supports/Activatable.hpp"
#include "Supports/Enterable.hpp"
#include "../BUtilities/Any.hpp"
#include "../BStyles/Theme.hpp"
#include "../BStyles/Status.hpp"
#include "../BEvents/Event.hpp"

// Default basic widget settings
#ifndef BWIDGETS_DEFAULT_WIDGET_WIDTH
#define BWIDGETS_DEFAULT_WIDGET_WIDTH 200
#endif

#ifndef BWIDGETS_DEFAULT_WIDGET_HEIGHT
#define BWIDGETS_DEFAULT_WIDGET_HEIGHT 100
#endif

#ifndef BWIDGETS_DEFAULT_STATUS
#define BWIDGETS_DEFAULT_STATUS BStyles::Status::normal
#endif

#ifndef BWIDGETS_DEFAULT_FOCUS_LAYER
#define BWIDGETS_DEFAULT_FOCUS_LAYER -100
#endif

#ifndef BWIDGETS_DEFAULT_WINDOW_LAYER
#define BWIDGETS_DEFAULT_WINDOW_LAYER (std::numeric_limits<int>::max() - 1)
#endif

namespace BWidgets
{

// Forward declarations
class Window;

/**
 *  @brief  Root widget class of BWidgets. All other widgets (including Window)
 *  are derived from this class.
 *
 *  A %Widget (and all derived widgets) is Drawable and may have got (at 
 *  least) a border and a background. The widget is displayed embedded in its
 *  parent widget area on default StackingType::normal, see Stacking). 
 *
 *  A %Widget is Linkable and thus it can be linked to another parent widget.
 *  And it can take up other widgets as childs. The last added child is 
 *  displayed on the top.
 *
 *  The %Widget class supports Activatable and Enterable (default: false). Once 
 *  switched on, the widget can be activated or entered by the user, 
 *  respectively.
 *
 *  Widgets also support EventMergeable and EventPassable. Thus, the main 
 *  Window event handler may merge events of the same type. And may pass events
 *  to the next (subjacent) widget if not actively supported by the widget.
 *
 *  A %Widget has got:
 *  * an @a URID to identify the %Widget,
 *  * a @a position to be placed (relative to its parent %Widget),
 *  * an infomation about its @a stacking type,
 *  * a @a status,
 *  * a @a title, 
 *  * a @a style,
 *  * a @a theme,
 *  * an information about pushing styles from nested styles or themes,
 *  * and a set of @a devices it has taken control over.
 * 
 *  Note: The class %Widget is devoid of any copy constructor or assignment
 *  operator. 
 */
class Widget :	public Linkable, 
				public Visualizable, 
				public EventMergeable, 
				public EventPassable, 
				public PointerFocusable,
				public Activatable,
				public Enterable
{

protected:

	/**
	 *  @brief  %Widget stacking types.
	 *
	 *  Way of positioning / displaying the widget in relation to its parent 
	 *  widget. On default, the widget is displayed embedded into its parent 
	 *  widget (StackingType::normal). This means it is placed relative to its 
	 *  parent widget origin and any overhang is cut.
	 */
	enum class StackingType
	{
		normal,					// Embedded in parent, overhang cut
		//STACKING_FIT,
		//STACKING_RESIZE_TO_FIT,
		//STACKING_RESIZE_PARENT_TO_FIT,
		escape						// May exceed the parent widget area
	};

	const uint32_t urid_;
	BUtilities::Point<> position_;
	StackingType stacking_;
	BStyles::Status status_;
	std::string title_;
	BStyles::Style style_;
	BStyles::Theme theme_;
	Widget* focus_;
	std::function<std::string (const Widget* widget)> focusTextFunction_;
	bool pushStyle_;
	std::set<BDevices::Device*> devices_;

public:

	/**
	 *  @brief  Creates a default %Widget.

	 *  Creates a default %Widget with default dimensions 
	 *  (BWIDGETS_DEFAULT_WIDTH, BWIDGETS_DEFAULT_HEIGHT).
	 */
	Widget ();

	/**
	 *  @brief  Creates a default %Widget.
	 *  @param URID  URID.
	 *  @param title  %Widget title.
	 */
	Widget (const uint32_t urid, const std::string& title);

	/**
	 *  @brief  Creates a widget.
	 *  @param x  %Widget X origin coordinate.
	 *  @param y  %Widget Y origin coordinate.
	 *  @param width  %Widget width.
	 *  @param height  %Widget height.
	 *  @param urid  Optional, URID (default = BUTILITIES_URID_UNKNOWN_URID).
	 *  @param title  Optional, %Widget title (default = "").
	 */
	Widget (const double x, const double y, const double width, const double height, uint32_t urid = BUTILITIES_URID_UNKNOWN_URID, std::string title = "");

	Widget (const Widget& that) = delete;
	virtual ~Widget();
	Widget& operator= (const Widget& that) = delete;

	/**
	 *  @brief  Creates a clone of the %Widget. 
	 *  @return  Pointer to the new widget.
	 *
	 *  Creates a clone of this widget by copying all properties (including
	 *  URID, Style, Supports (excluding Linkable), position, extends, 
	 *  stacking, status, title, ...). But NOT its linkage.
	 *
	 *  Allocated heap memory needs to be freed using @c delete if the clone
	 *  in not needed anymore!
	 */
	virtual Widget* clone () const; 

	/**
	 *  @brief  Copies from another %Widget. 
	 *  @param that  Other %Widget.
	 *
	 *  Copies all properties from another %Widget (including Style, Supports
	 *  (excluding Linkable), position, extends, stacking, status, title, 
	 *  ...). But NOT its URID (immutable) and its linkage.
	 */
	void copy (const Widget* that);

	/**
	 *  @brief Gets the %Widget URID.
	 *  @return  URID.
	 */
	uint32_t getUrid () const;

	/**
	 *  @brief  Changes the %Widget title.
	 *  @param title  New title.
	 */
	virtual void setTitle (const std::string& title);

	/**
	 *  @brief  Gets the %Widget title.
	 *  @return  %Widget title.
	 */
	std::string getTitle () const;

	/**
	 *  @brief  Adds a child widget to the %Widget.
	 *  @param child  Child widget.
	 *  @param addfunc  Optional, function to be executed once a child object
	 *  is added.
	 *  @return  Iterator for the inserted child.
	 *
	 *  New child objects are appended to the end of list of children objects
	 *  (see @c getChildren() ).
	 *
	 *  Returns @c getChildren().end() if noting inserted (e.g, trying to add
	 *  a @c nullptr or linking is switched off).
	 */
	virtual std::list<Linkable*>::iterator 
	add	(Linkable* child, std::function<void (Linkable* obj)> addfunc = [] (Linkable* obj) {}) 
	override;

	/**
	 *  @brief  Releases (but not deletes) ALL child objects.
	 *  @param releasefunc  Optional, function to be executed once a child
	 *  object is released.
	 */
	virtual void release (std::function<void (Linkable* obj)> addfunc = [] (Linkable* obj) {}) 
	override;

	/**
	 *  @brief  Releases (but not deletes) a child widget from this %Widget.
	 *  @param child  Pointer to the child %Widget.
	 *  @param releasefunc  Optional, function to be executed once a child
	 *  object is released.
	 */
	virtual void 
	release (Linkable* child, std::function<void (Linkable* obj)> releasefunc = [] (Linkable* obj) {}) 
	override;

	/**
	 * @brief  Takes control over a device. 
	 * 
	 * @param device  Device.
	 */
	virtual void grabDevice (const BDevices::Device& device);

	/**
	 * @brief  Releases the control over all devices.
	 */
	virtual void freeDevice ();

	/**
	 * @brief  Releases the control over a device.
	 * 
	 * @param device  Device
	 */
	virtual void freeDevice (const BDevices::Device& device);

	/**
	 * @brief  Checks if a device is under the control of this widget.
	 * 
	 * @param device  Device
	 * @return  True if device is under control of this widget, otherwise 
	 * false.
	 */
	bool isDeviceGrabbed (const BDevices::Device& device) const;

	/**
	 * @brief  Get access to the Device object which is equal to @a device.
	 * 
	 * @param device  Device
	 * @return  Pointer to the device object, or nullptr if no matching device.
	 */
	BDevices::Device* getDevice (const BDevices::Device& device) const;

	/**
	 *  @brief  Drops this %Widget one step towards the background.
	 */
	virtual void drop ();

	/**
	 *  @brief  Raises this %Widget one step towards the foreground.
	 */
	virtual void raise ();

	/**
	 *  @brief  Drops this %Widget to the background.
	 */
	virtual void dropToBack ();

	/**
	 *  @brief  Raises this %Widget to the foreground.
	 */
	virtual void raiseToFront ();

	/**
	 *  @brief  Access to the main Window of this %Widget.
	 *  @return  Pointer to the main window. 
	 *
	 *  Returns @c nullptr if the widget isn't connected to a main window.
	 *  Returns a pointer to itself if the widget is the main window itself.
	 */
	Window* getMainWindow () const;

	/**
	 *  @brief  Access to the parent %Widget of this %Widget.
	 *  @return  Pointer to the parent %Widget. 
	 *
	 *  Returns @c nullptr if this %Widget doesn't have any parents or no
	 *  parents of the type %Widget.
	 */
	Widget* getParentWidget () const;

	/**
     *  @brief  Switch visibility on.
	 *
	 *  A widget becomes visible if (i) its visibility and the visibility of
	 *  all its parent widgets is switched on, and (ii) it is connected to a
	 *  main window, and (iii) it draws to its RGBA surface.
     */
    virtual void show () override;

    /**
     *  @brief  Switch visibility off.
	 *
	 *  A widget is visible if (i) its visibility and the visibility of
	 *  all its parent widgets is switched on, and (ii) it is connected to a
	 *  main window, and (iii) it draws to its RGBA surface.
     */
    virtual void hide () override;

	/**
     *  @brief  Information about visibility.
     *  @return  True if on, otherwise false.
	 *
	 *  A widget is visible if (i) its visibility and the visibility of
	 *  all its parent widgets is switched on, and (ii) it is connected to a
	 *  main window, and (iii) it draws to its RGBA surface.
     */
    bool isVisible () const override;
	
	/**
     *  @brief  Method to be called following an object state change.
     *
     *  This method should be called
     *  following a %Widgets object state change.
     */
    virtual void update () override;

    /**
	 *  @brief  Generic setter method for Supports.
	 *  @tparam T  Type of Support.
	 *  @param status  Support on (true) or off (false).
	 *
	 *  Generic alternative for the setXXXable() methods.
	 */
	template<class T>
	void set (const bool status)
	{
		if (dynamic_cast<T*>(this)) T::setSupport (status);
	}

	/**
	 *  @brief  Generic getter method for Supports.
	 *  @tparam T  Type of Support
	 *  @return  True if on, otherwise false.
	 *
	 *  Generic alternative for the isXXXable() methods.
	 */
	template<class T>
	bool is ()
	{
		return (dynamic_cast<T*>(this) && dynamic_cast<T*>(this)->getSupport());
	}

    /**
     *  @brief  Optimizes the %Widget extends.
     *
	 *  Resizes the widget to include all direct children into the %Widget
	 *  area. Resizes to (0, 0) if this %Widget doesn't have any children.
	 */
	virtual void resize () override;

    /**
     *  @brief  Resizes the %Widget extends.
	 *  @param width  New %Widget width.
	 *  @param height  New %Widget height.
	 */
	virtual void resize (const double width, const double height) override;

    /**
	 *  @brief  Resizes the %Widget extends.
	 *  @param extends  New %Widget extends.
	 */
	virtual void resize (const BUtilities::Point<> extends) override;

	/**
	 *  @brief  Moves the widget to a new position.
	 *  @param x  New x coordinate.
	 *  @param y  New y coordinate.
	 */
	virtual void moveTo (const double x, const double y);

	/**
	 *  @brief  Moves the widget to a new position.
	 *  @param position	 New position.
	 */
	virtual void moveTo (const BUtilities::Point<>& position);

	/**
	 *  @brief  Moves the widget relative to its origin.
	 *  @param dx  Change in x coordinate.
	 *  @param dy  Change in y coordinate.
	 */
	virtual void moveRel (const double dx, const double dy);

	/**
	 *  @brief  Moves the widget relative to its origin.
	 *  @param dpos	 Change in position.
	 */
	virtual void moveRel (const BUtilities::Point<>& dpos);

	/**
	 *  @brief  X position of the %Widget to be placed on the parents left
	 *  border.
	 *  @return  X position.
	 */
	virtual double left ();

	/**
	 *  @brief  Moves the %Widget horizontally to the center of its parent.
	 *
	 *  This method only changes the %Widget position data if it is connected
	 *  to a parent %Widget.
	 */
	virtual double center ();

	/**
	 *  @brief  X position of the %Widget to be placed on the parents right
	 *  border.
	 *  @return  X position.
	 */
	virtual double right ();

	/**
	 *  @brief  Y position of the %Widget to be placed on the parents top
	 *  border.
	 *  @return  Y position.
	 */
	virtual double top ();

	/**
	 *  @brief  Y position of the %Widget to be placed in the vertical middle
	 *  of the parent %Widget.
	 *  @return  Y position.
	 */
	virtual double middle ();

	/**
	 *  @brief  Y position of the %Widget to be placed on the parents top
	 *  border.
	 *  @return  Y position.
	 */
	virtual double bottom ();

	/**
	 *  @brief  Gets the %Widget position.
	 *  @return  %Widget position relative to its parent %Widget.
	 */
	BUtilities::Point<> getPosition () const;

	/**
	 *  @brief  Gets the %Widget covered area.
	 *  @return  %Widget area relative to its parent %Widget.
	 */
	BUtilities::Area<> getArea () const;

	/**
	 *  @brief  Gets the %Widget position relative to the position of its root
	 *  widget (e. g., the main Window)
	 *  @return  %Widget position relative to its root widget.
	 */
	BUtilities::Point<> getAbsolutePosition () const;

	/**
	 *  @brief  Gets the %Widget covered area relative to the position of its
	 *  root widget (e. g., the main Window).
	 *  @return  %Widget area relative to its root widet.
	 */
	BUtilities::Area<> getAbsoluteArea () const;

	/**
	 *  @brief  X offset of the %Widget content relative to the %Widget X 
	 *  position.
	 *  @return  X offset of the %Widget.
	 
	 *  The X offset is distance between the outer border and the widget 
	 *  content. It is the sum of border margin, line width, and padding if a
	 *  border is defined.
	 */
	double getXOffset () const;

	/**
	 *  @brief  Y offset of the %Widget content relative to the %Widget Y 
	 *  position.
	 *  @return  Y offset of the %Widget.
	 
	 *  The Y offset is distance between the outer border and the widget 
	 *  content. It is the sum of border margin, line width, and padding if a
	 *  border is defined.
	 */
	double getYOffset () const;

	/**
	 *  @brief  Effective width to draw a %Widget.
	 *  @return  Effective width of the widget.
	 *
	 *  The effective width is the width of the underlying RGB surface that
	 *  can effectively be used for drawing a %Widget. It is the total surface
	 *  width minus two times the sum of border margin, line width, and 
	 *  padding.
	 */
	double getEffectiveWidth () const;

	/**
	 *  @brief  Effective height to draw a %Widget.
	 *  @return  Effective height of the widget.
	 *
	 *  The effective height is the height of the underlying RGB surface that
	 *  can effectively be used for drawing a %Widget. It is the total surface
	 *  height minus two times the sum of border margin, line width, and 
	 *  padding.
	 */
	double getEffectiveHeight () const;

	/**
	 *  @brief  Effecitve area to draw a %Widget.
	 *  @return	 Effective widget area.
	 *
	 *  The effective area is the area of the underlying RGB surface that
	 *  can effectively be used for drawing a %Widget. It is the total surface
	 *  area without the borders (defined as the sum of border margin, line 
	 *  width, and padding) on each side.
	 */
	BUtilities::Area<> getEffectiveArea () const;

	/**
	 *  @brief  Sets the %Widget status.
	 *  @param status  %Widget status.
	 */
	virtual void setStatus (const BStyles::Status status);

	/**
	 *  @brief  Gets the %Widgets status.
	 *  @return  %Widget state
	 */
	BStyles::Status getStatus () const;

	/**
     *  @brief  Activates this %Widget 
     *  @param status  Optional, true for activation, false for de-activation
	 *
	 *  Sets the %Widget status to BStyles::Status::active upon activation and
	 *  BStyles::Status::normal upon de-activation if the %Widget is 
	 *  Activatable. Also de-activates all other Widgets at the same level 
	 *  (same parent) if they are Activatable too and allow auto deactivation.
     */
    virtual void activate (bool status = true) override;

	/**
     *  @brief  Enters this %Widget.
     *
     *  Activates this %Widget and calls to leave all other widgets linked to 
	 *  the main Window to become the only entered %Widget.
     */
    virtual void enter () override;

	/**
     *  @brief  Leaves this Widget
     *
     *  De-activates this %Widget.
     */
    virtual void leave () override;

	/**
	 *  @brief  Sets the type of stacking this %Widget.
	 *  @param stacking  Stacking type.
	 *
	 *  Stacking is a behaviour of a %Widget relative to its parent %Widget.
	 *  Widgets are clipped on default if they exceed the limits of their
	 *  respective parent %Widget (StackingType::normal).
	 */
	virtual void setStacking (const StackingType stacking);

	/**
	 *  @brief  Gets the type of stacking this %Widget.
	 *  @return  Stacking type. 
	 */
	StackingType getStacking () const;

	/**
	 *  @brief  Copies the style from another object.
	 *  @param style  Other style.
	 *
	 *  Composite widgets should override this method to forward the passed
	 *  @a style to embedded child widgets too.
	 */
	virtual void setStyle (const BStyles::Style& style);

	/**
	 *  @brief  Copies the theme from another object.
	 *  @param theme  Other theme.
	 */
	virtual void setTheme (const BStyles::Theme& theme);

	/**
	 *  @brief  Enables pushing styles to child widgets on @c add() or
	 *  @c setStyle() or @c setTheme(). 
	 *  @param pushStyle  True, if pushing enabled, otherwise false.
	 */
	virtual void enablePushStyle (bool pushStyle = true);

	/**
     *  @brief  Gets the border Property from the base level.
     *  @return  Border.
     *
     *  Gets the base level border Property using the default border URID.
     *  Returns noBorder if the default border URID is not set.
     */
    BStyles::Border getBorder() const;

    /**
     *  @brief  Sets the border Property at the base level.
     *  @param border  Border.
     *
     *  Sets the base level border Property using the default border URID.
     */
    virtual void setBorder(const BStyles::Border& border);

    /**
     *  @brief  Gets the background Property from the base level.
     *  @return  Background.
     *
     *  Gets the base level background Property using the default background 
     *  URID. Returns noFill if the default background URID is not set.
     */
    BStyles::Fill getBackground() const;

    /**
     *  @brief  Sets the background Property at the base level.
     *  @param fill  Background.
     *
     *  Sets the base level background Property using the default background 
     *  URID.
     */
    virtual void setBackground (const BStyles::Fill& fill);

    /**
     *  @brief  Gets the font Property from the base level.
     *  @return  Font.
     *
     *  Gets the base level font property using the default font URID.
     *  Returns sans12pt if the default font URID is not set.
     */
    BStyles::Font getFont() const;

    /**
     *  @brief  Sets the font property at the base level.
     *  @param font  Font.
     *
     *  Sets the base level font Property using the default font URID.
     */
    virtual void setFont (const BStyles::Font& font);

    /**
     *  @brief  Gets the foreground colors Property from the base level.
     *  @return  Foreground ColorMap.
     *
     *  Gets the base level foreground colors Property using the default 
     *  foreground colors URID. Returns whites if the default foreground 
     *  colors URID is not set.
     */
    BStyles::ColorMap getFgColors() const;

    /**
     *  @brief  Sets the foreground colors Property at the base level.
     *  @param colors  Foreground ColorMap.
     *
     *  Sets the base level foreground colors Property using the default 
     *  foreground colors URID.
     */
    virtual void setFgColors (const BStyles::ColorMap& colors);

    /**
     *  @brief  Gets the background colors Property from the base level.
     *  @return  Background ColorMap.
     *
     *  Gets the base level background colors Property using the default 
     *  background colors URID. Returns darks if the default background colors
     *  URID is not set.
     */
    BStyles::ColorMap getBgColors() const;

    /**
     *  @brief  Sets the background colors Property at the base level.
     *  @param colors  Background ColorMap.
     *
     *  Sets the base level background colors Property using the default 
     *  background colors URID.
     */
    virtual void setBgColors (const BStyles::ColorMap& colors);

    /**
     *  @brief  Gets the text colors Property from the base level.
     *  @return  Text ColorMap.
     *
     *  Gets the base level text colors Property using the default text colors
     *  URID. Returns whites if the default text colors URID is not set.
     */
    BStyles::ColorMap getTxColors() const;

    /**
     *  @brief  Sets the text colors Property at the base level.
     *  @param colors  Text ColorMap.
     *
     *  Sets the base level text colors Property using the default text
     *  colors URID.
     */
    virtual void setTxColors (const BStyles::ColorMap& colors);

    /**
     *  @brief  Gets the object surface.
     *  @param layer  Layer index.
     *
     *  The layer index represents the Z position of the surface. The higher
     *  the index, the more to the background. If no layer has been set
     *  (BWIDGETS_UNDEFINED_LAYER), then the index of the subjacent widjet will
	 *  be used. Lower indexed layers will be displayed in front of the 
     *  default layer, higher indexed layers behind.
     */
    virtual int getLayer () const override;

	/**
	 *  @brief  Sets the focus_ Widget text by providing a function.
	 * 
	 *  @param func  Function providing a text string.
	 *
	 *  Indirect way of setting the focus_ Label text. Sets the function to be
	 *  used to set the text content of the %Widget focus_ label. Resets the 
	 *  focusTextFunction_ to nullptr to be inactive if func is nullptr.
	 */
	virtual void setFocusText (std::function<std::string (const Widget* widget)> func);

	/**
	 *  @brief  Gets the focus text.
	 * 
	 *  @return  Focus text.
	 *
	 *  First looks for focusTextFunction_ and returns its result if 
	 *  focusTextFunction_ is NOT nullptr. Otherwise it directly takes the
	 *  focus_ Label text content if focus_ exists. Otherwise it takes "".
	 */
	std::string getFocusText () const;

	/**
	 *  @brief  Requests a redisplay of the %Widget area.
	 *
	 *  Emits an ExposeEvent of the type ExposeRequestEvent to the main
	 *  Window event queue. 
	 */
	virtual void emitExposeEvent () override;

	/**
	 *  @brief  Requests a redisplay of a part of the %Widget area.
	 *  @param area  Area to redisplay.
	 *
	 *  Emits an ExposeEvent of the type ExposeRequestEvent to the main
	 *  Window event queue. 
	 */
	virtual void emitExposeEvent (const BUtilities::Area<>& area) override;

	/**
     *  @brief  Method called when focus in time is passed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  the time for focus in is passed. By default, it calls its static 
	 *  callback function.
     */
    virtual void onFocusIn (BEvents::Event* event) override;

	/**
     *  @brief  Method called when focus out time is passed.
     *  @param event  Passed Event.
     *
     *  Overridable method called from the main window event scheduler when
     *  the time for focus out is passed. By default, it calls its static 
	 *  callback function.
     */
    virtual void onFocusOut (BEvents::Event* event) override;

protected:

	/**
	 *  @brief  Gets the area covered by this %Widget and all its children.
	 *  @param func  Optional, filter function.
	 */
	BUtilities::Area<> getFamilyArea (std::function<bool (const Widget* widget)> func = [] (const Widget* widget) {return true;}) const;

	/**
	 *  @brief  Gets the area covered by this %Widget and all its children
	 *  relative to the root widget (e. g., the main Window).
	 *  @param func  Optional, filter function.
	 */
	BUtilities::Area<> getAbsoluteFamilyArea (std::function<bool (const Widget* widget)> func = [] (const Widget* widget) {return true;}) const;

	/**
	 *  @brief  Gets the top %Widget at a given position.
	 *  @param position  Position. 
	 *  @param func  Optional, filter function.
	 *  @param passfunc  Optional, function to skip this widget and continue
	 *  with the widget below.
	 *  @return  Pointer to the %Widget.
	 *
	 *  Order of checks:
	 *  1. Checks if @a position is inside the widget area, then
	 *  2. checks the @a passfunc if this widget will be passed and the checks
	 *     are continued with the widgets below (true) or if not passed
	 *     (false), then
	 *  3. checks if the filter function @a func returns true.
	 */
	Widget* getWidgetAt	(const BUtilities::Point<>& position, 
						 std::function<bool (Widget* widget)> func = [] (Widget* widget) {return true;},
						 std::function<bool (Widget* widget)> passfunc = [] (Widget* widget) {return false;});

	/**
	 *  @brief  Draws %Widget surface and children surfaces to the provided
	 *  map of layered target surfaces.
	 *  @param surfaces  Map of target surfaces.
	 *  @param surfaceExtends  Extends of the surfaces to be created for each
	 *  layer.
	 *  @param area  Clipping area.
	 *
	 *  This method is called by the main Window system event handler upon an
	 *  ExposeEvent of the type exposeRequestEvent. Thus, this method draws
	 *  the visual content of this %Widget and all its children %Widgets stored
	 *  in their respective RGBA surfaces to the system provided RGBA surface
	 *  of the main %Window.  
	 */
	virtual void display (std::map<int, cairo_surface_t*>& surfaces, const BUtilities::Point<> surfaceExtends, const BUtilities::Area<>& area);

	/**
     *  @brief  Unclipped draw a %Widget to the surface.
     */
    virtual void draw () override;

    /**
     *  @brief  Clipped draw a %Widget to the surface.
     *  @param x0  X origin of the clipped area. 
     *  @param y0  Y origin of the clipped area. 
     *  @param width  Width of the clipped area.
     *  @param height  Height of the clipped area. 
     */
    virtual void draw (const double x0, const double y0, const double width, const double height) override;

    /**
     *  @brief  Clipped draw a %Widget to the surface.
     *  @param area  Clipped area. 
     */
    virtual void draw (const BUtilities::Area<>& area) override;

private:
	void display (std::map<int, cairo_surface_t*>& surfaces, const BUtilities::Point<> surfaceExtends, const BUtilities::Area<>& outerArea, const BUtilities::Area<>& area);

	Widget* getWidgetAt	(const BUtilities::Point<>& abspos, 
						 const BUtilities::Area<>& outerArea,
			   			 const BUtilities::Area<>& area, 
						 std::function<bool (Widget* widget)> func = [] (Widget* widget) {return true;},
						 std::function<bool (Widget* widget)> passfunc = [] (Widget* widget) {return true;});
};

}

#endif /* BWIDGETS_WIDGET_HPP_ */
