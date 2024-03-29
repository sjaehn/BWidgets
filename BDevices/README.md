# BDevices

Devices store information about its type (e. g., mouse), a parameter type
(e. g., left button), and the time point when it has been created or changed.
The type and the parameter type are immutable, the time point of action can
be accessed with `setActionTime()` and `getActionTime()`

Device classes derived from the main class may also store additional data
like position.

```
Device
 ├── Keys
 ╰── MouseButton
 ```

Widgets can take control over a device by grabbing it (`Widget::grabDevice()`)
and can release control again (`Widget::freeDevice()`).


## Device

Main class of devices. Devices are comparable by (only) its type and its
parameter type. This means, if two device objects have got the same type and
the same parameter type, but may differ in other data stored in the object
(like the activation time point), then both objects are interpreted as the
same.

All other event classes are derived from this class.


## Keys

A Keys device object is responsible the keyboard interaction. A Keys device
object can be responsible for selected keys or all keys (`KeyType::any`).

A Keys object of the `KeyType::any` is grabbed by the widget `EditLabel` and
may be gabbed by `BWidgets::Navigatable` widgets upon clicking on it to make 
all keyboard entries to be passed to the respective widget.


## MouseButton

A MouseButton device object is responsible the mouse interaction. They 
additionally store information where a mouse button action (press / release)
has taken place (`setPosition()`, `getPosition()`). 

Mouse objects with the parameter types ButtonType::left, ButtonType::middle, 
and ButtonType::right are responsible for the respective mouse buttons.
They are automatically grabbed by the respective widgets upon pressing the 
button until the button is released. These objects are used to store the
button information for dragging and clicking (= press + release). 

In addition, there are Mouse objects with the parameter type ButtonType::none.
These objects are automatically grabbed by the respective widget upon
moving or resting a mouse pointer over it. These mouse objects enable pointer
focusing and hover widgets.