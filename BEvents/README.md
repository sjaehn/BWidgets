# BEvents

Events are emitted by a widget (or by the system via the main window) to the 
main window event queue. The main window is the place for event handling in
its `handleEvents()` method.

```
Event
 ├── WidgetEvent
 |    ╰── ExposeEvent
 ├── KeyEvent
 ├── PointerEvent
 ├── WheelEvent
 ├── PointerFocusEvent
 ├── ValueChangedEvent
 |    ╰── ValueChangeTypedEvent<T>
 ╰── MessageEvent
 ```


## Event

Main class of events. Stores the event type and a pointer to the widget that
caused the event. All other event classes are derived from this class.


## WidgetEvent

Widget action request event. Widget events are emitted by an (event) widget if
the widget is requested by an other (request) widget. This event class is
typically used if opening or closing of a window or an request widget is 
requested.


## ExposeEvent

Event to request (re-)visualization of a widget. ExposeEvent is emitted by a
parent event widget (or window) if the visual content of a child (request)
widget is requested to be updated. An ExposeEvent additionally contains the 
coordinates (x, y, width and height) of the output region (relative to the
widgets origin) to be updated.


## KeyEvent

KeyEvents are emitted by the system if a key is pressed or released.


## PointerEvent

Pointer movement and button events. A PointerEvent is emitted by the system 
(via pugl and the main window) if a button is pressed or released and/or the 
pointer is moved over a widget. The PointerEvent contains data about the 
position (relative to the respective widget and the button pressed (or not). 
PointerEvents will be handled by the respective widget and can be redirected 
to external callback functions.


## WheelEvent

Mouse wheel scrolling event. Wheel events are emitted by the system (via pugl 
and the main window) if a (mouse) wheel is turned.

The WheelEvent contains data about the relative change of the wheel and about 
the pointer position (relative to the respective widget. WheelEvents will be 
handled by the respective widget and can be redirected to external callback 
functions.


## PointerFocusEvent

FocusEvents are emitted by widgets if the pointer rests for a predefined time
over the widget.


## ValueChangedEvent

Event to communicate a changed value of Widgets supporting Valueable. A
ValueChangedEvent is emitted by widgets if their respective `setValue()`
method is called. 

ValueChangedEvents can be handled internally (e.g., by composite widgets) and
can also be redirected to external callback functions.

ValueChangedEvent shoud be specialized by ValueChangeTypedEvent\<T\>.


## ValueChangeTypedEvent\<T\>

Specialization of ValueChangedEvent. ValueChangeTypedEvent\<T\> additionally
contains a copy of the value from the time of emission of the event.


## MessageEvent

Ubiquitous event type. Can be used to send messages of any type.