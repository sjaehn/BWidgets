# Supports

Supports are fully or partially defined interface classes to add additional
features to objects (incl. Widgets).

```
Support
 ├── Pointable          < Callback
 ├── PointerFocusable   < Callback
 ├── Clickable          < Callback
 ├── Toggleable
 ├── Draggable          < Callback
 ├── Scrollable         < Callback
 ├── KeyPressable       < Callback
 ├── Activatable
 ├── Navigatable
 ├── Valueable          < Callback
 |    ╰── ValueableTyped<T>
 ├── ValueTransferable<T>
 ├── Validatable<T>
 |    ├── ValidatablePass<T>
 |    ╰── ValidatableRange<T>
 ├── Messagable         < Callback
 ├── Visualizable       < Callback
 ├── ValueVisualizable
 ├── Closable           < Callback
 ╰── Linkable
 
()
 ├── EventMergeable
 ╰── EventPassable
```

Supports can be switched on or off by calling its respective virtual setXXX 
method (e. g., `setDraggable()` for the class Draggable). The status can be
requsted using the respective non-virtual isXXX method (e. g., 
`isDraggable()`). Inheriting classes may contain additional member parameters
with virtual setter and non-virtual getter methods. 

## Support

Base class of all supports (except EventMergeable) containing a simple switch 
for the respective support functionality.


## Callback

The Callback class provides callback functionality for Events. Callback is 
supported by all Widgets via Visualizable.


## Pointable

Supports pointer tracking by pointer motion events.


## PointerFocusable

PointerFocusable supports FocusEvents of the type PointerFocusInEvent or 
PointerFocusOutEvent. FocusEvents are typically emitted if the (mouse) 
pointer rests over a widget.


## Clickable

Pointer button click (incl. press and release) support.


## Toggleable

Support of button toggling.


## Draggable

Pointer drag support. Dragging may be interpreted diffenrently depending on the
context. Widgets of the class Frame use Draggable to enable drag and drop
support.


## Scrollable

(Mouse) wheel scroll support.


## KeyPressable

Supports keyboard key press and release events.


## Activatable

Support of Widget activation by an user interaction.


## Navigatable

Support of navigation between Activatable child Widgets by an user interaction.


## Valueable

Base class for Support of objects with a value and ValueChangedEvents. Needs to
be specialized.


## ValueableTyped\<T\>
Support of objects with a value and ValueChangedEvents.


## ValueTransferable\<T\>
Support of value transfer functions in combination with Valueable. Transfer 
functions are intented to be used to transfer values from an external context 
(e. g., frequencies with a logarithmic distribution) to an internal context 
(e. g., a slider with linear distribution).


## Validatable\<T\>

Base class. Supports value validation in combination with Valueable.


## ValidatablePass\<T\>

Supports validity of the value in any case.


## ValidatableRange\<T\>

Validates the value to be within a range.


## Messagable

Custom message event support.


## Visualizable

Visualizable makes objects visible. Visualizable supports:
1. Drawing each Visualizable object to its own (Cairo) RGBA surface.
2. Expose the visual content of connected Visualizable objects by the main
   Window.

Principle: Each widget is drawn to its own (Cairo) RGBA surface. If the visual
content of a widget is changed, the widget should emit an ExposeEvent of the
type ExposeRequestEvent by calling @c postRedisplay() to inform the main
window event handler about the changed content. Then the main window event
handler will request a host system expose event.

If the main window (then) receives a host system expose event, the main window
updates the visual content covered by this event.


## ValueVisualizable

Support of value visualization (incl. the value visualization position) in 
composite Valueable widgets.


## Closable

Widget and Window close request support.


## Linkable

Support for embedding widgets into other widgets by linking to parent and child
objects.


## EventMergeable

Event merging support.


## EventPassable

By default, host events (e. g., PointerEvent, WheelEvent, PointerFocusEvent) 
are associated with the most frontward visible widget for the respective
position. The event is then emitted by this widget if this widget supports
the respective event. Otherwise it blocks this event.

EventPassable supports passing events to subjacent widgets even if (or
if not) the widget doesn't support the respective event type.