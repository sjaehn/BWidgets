# BWidgets
Widget toolkit of the B.Music project.

The B.Widgets toolkit is a widget toolkit intended for small (single window)
standalone applications and for plugins. It comes along with a series of
built-in widgets, including labels, buttons, dials, sliders, menues and so on.

B.Widgets allows recursive embedding of widgets including changing the order
of embedding. 

B.Widgets supports events from the keyboard, the mouse, the host windowing 
system and also internal events like value change and messaging events. 

Widgets can be decorated using styles.

## Quickstart

You can also find this source code at "../examples/buttontest.cpp".

1. Include the header files of the widgets you need.
   ```
   #include "path/to/BWidgets/Window.hpp"
   #include "path/to/BWidgets/TextButton.hpp"
   ```
   Optional, simplify using namespace BWidgets, BStyles, and BEvents:
   ```
   using namespace BWidgets;
   using namespace BStyles;
   using namespace BEvents;
   ```

2. Create a main window object.
   ```
   Window window;  // Creates an empty window with default size
   ```

3. Create the widget objects you need.
   ```
   Label label ("Button pressed");  // Creates a label with the text
                                    // "Button pressed" and optimized size.

   TextButton button (70, 40, 60, 20, "Press"); // Creates a text Button
                                                // at position 70, 40 with
                                                // the size 60 x 20 and
                                                // the text "Press".
   ```

4. Add the widgets to the main window (or to other widgets which are (or will 
be) added to the main window).
   ```
   window.add (&label);     // Adds the label to the window.
   window.add (&button);    // Adds the button to the window.
   ```
   Note: Linking widgets to the main window make them visible by default.

5. Optional, change widget attributes and change decoration.
   ```
   label.setTxColors (ColorMap ({black})); // Black label on ...
   window.setBackground (blackFill);       // black window background
   
   label.moveTo (label.center(), label.bottom ()); // Move label to bottom
                                                   // center.
   ```

6. Optional, handle events using callbacks.

   First create a callback function. 
   ```
   void valueChangedCallback (BEvents::Event* event)
   {
      ValueChangeTypedEvent<bool>* e = dynamic_cast<ValueChangeTypedEvent<bool>*>(event);
      if (e->getValue()) e->getWidget()->getMainWindow()->setBackground (redFill);
      else e->getWidget()->getMainWindow()->setBackground (blackFill);
   }
   ```

   Then link this callback function.
   ```
   button.setCallbackFunction (Event::VALUE_CHANGED_EVENT, valueChangedCallback);
   ```

7. For standalone applications, process until the main window will be closed.
   ```
   window.run ();
   ```


## Namespaces

The toolkit uses tools from five namespaces:
* `BDevices`
* `BEvents`
* `BStyles`
* `BUtilities`
* `BWidgets`


### BDevices

Interaction with the system input devices (mouse, keyboard).


### BEvents

The [`BEvents`](../BEvents/README.md) namespace contains different classes of
events. `BEvents` are emitted by a widget (or by the system via the main
window) to the main window event queue.


### BStyles

The [`BStyles`](../BStyles/README.md) namespace contain classes to describe a
widget style.


### BUtilities

The `BUtilities` namespace contains a collection of different useful tools.


### BWidgets

Core namespace of the BWidgets toolkit. Contains all widget classes and the 
supporting interface classes.


## Widgets

All widgets are located in the BWidgets namespace. And all widgets are
derived from the `Widget` class. Including the main `Window`.

```
Widget
 ├── Window
 ├── Frame
 ├── Label
 |    ├── LabelEdit
 |    ╰── Text
 ├── Symbol
 ├── Image
 ├── Button
 |    ├── TextButton
 |    ├── SymbolButton
 |    ├── ImageButton
 |    ├── Checkbox
 |    ├── RadioButton
 |    ├── Knob
 |    ├── HSwitch
 |    ╰── VSwitch
 ├── HMeter
 |    ├── ValueHMeter
 |    ╰── HScale
 |         ╰── HSlider
 |              ╰── ValueHSlider
 ├── VMeter
 |    ├── ValueVMeter
 |    ╰── VScale
 |         ╰── VSlider
 |              ╰── ValueHSlider
 ├── RadialMeter
 |    ├── ValueRadialMeter
 |    ╰── Dial
 |         ╰── ValueDial
 ├── HPianoRoll
 .
 .
 .
```


### Main Window

The main `Window` object is the core `Widget` in BWidgets. Each project MUST
contain exactly one `Window` object (more are not allowed, less don't make
any sense).

The main `Window` object controls the visibility of all linked widgets. All
Widgets need be be linked to the main `Window` object to become visible.

A simple example of linking and visualizing a "Hello World" `Label` to a 
`Window` (see "../examples/helloworld.cpp"):
```
int main ()
{
     Window w;                // Creates an empty window with default size
     Label l ("Hello World")  // Creates a "Hello world" label
     w.add (&l);              // Links the label to the window
     w.run ();                // Keeps the window open until close
}
```

The main `Window` object also controls and routes the events emitted by the
linked widgets and by the host system in its event queue and its event
handler. 

The full event routing process is:
1.  Emission of an event either by a `Widget` either
    * by a host event and an assignment to a `Widget` by the main `Window`
      translate function, or
    * by the `Widget` directly

    to the main `Window` event queue.
2.  Analyzing, merging and routing in the main `Window` event handler and
    calling the widget `onXXX()` method.
3.  Responding in the widget `onXXX()` method and optional call of a linked
    `Callback` function.
4.  Optional, respond to the effect in a `Callback` function.


### Widget

`Widget` is the base widget class of BWidgets.

All widgets support the features:
* Linkable (may got linked to parent and child widgets)
* Visualizable (may draw to a RGBA surface and may become visible)
* EventMergeable (may let the main `Window` merge its events)

In addtion, widgets have got:
 * an *URID* to identify the widget,
 * a *position* to be placed (relative to its parent widget),
 * an infomation about its *stacking* type,
 * a *status* ,
 * a *title* , and
 * a *style* .

`Widget` objects are the most simple widgets. Their visual content is only
defined by the `Style` properties border and background. There is no further 
user interaction.

Each `Widget` must be directly or indirectly linked to the main `Window` to
become visible.


### Frame

`Frame` is a simple derivative of `Widget` without any additional content.
But it supports `Draggable`. This means, you can drag and drop `Frame`
objects.


### Label

`Label` is a simple one line text output widget. It can be decorated by setting
a font and a text color in addtion to the style properties supported by
`Widget`. 


### LabelEdit

`LabelEdit` is an editable version of `Label`. It additionally supports:
* `Clickable` and `Draggable` to set the cursor,
* `KeyPressable` to enter / change a text via the keyboard, and
* `Valueable` to store the text and inform the event handler.

`LabelEdit` can be decorated like a `Label`.


### Text

`Text` is a multi line text output widget. It can be decorated like a `Label`.


### Image

`Image` is an image displaying widget. It supports one image for each Status.


### Symbol

`Symbol` is a Widget that displays a symbol. It can be decorated by setting
a TxColor in addtion to the StyleProperty settings supported by Widget. 


### Button

`Button` draws a simple button. It supports `Clickable` and `Valueable`. The
value has two conditions: on (true) or off (false). A `Button` changes its 
border color upon changing the condition.


### TextButton

`TextButton` is a `Button` containing a label. A `TextButton` changes its 
label status (and thus its color) in addition to the change of its border
color upon changing the condition.


### SymbolButton


### ImageButton


### Knob
`Knob` is a Button Widget. It is a pseudo 3D visualization of a knob which
can change its status (bool value) upon user interaction via `Clickable`. 
Its appearance is defined by the BgColors parameter (static elements, 
false) and by the FgColors parameter (active elements, true).


### HSwitch

`HSwitch` is a Button Widget. It displays its status (represented by its 
bool value) as a horizontal switch. It supports user interaction via 
`Clickable`, `Draggable`, and `Scrollable`. Its appearance is defined by the 
BgColors parameter (static elements, false) and by the FgColors parameter
(active elements, true).


### VSwitch

`VSwitch` is a Button Widget. It displays its status (represented by its 
bool value) as a vertical switch. It supports user interaction via 
`Clickable`, `Draggable`, and `Scrollable`. Its appearance is defined by the 
BgColors parameter (static elements, false) and by the FgColors parameter
(active elements, true).


### HMeter

`HMeter` is a Valueable Widget and displays a value as a horizontal
meter without user interaction. The value is kept within a defined range
and displayed in blocks defined by the parameter @a step . Its appearance
is defined by the parameters BgColors (static elements), FgColors (value,
low range), and HiColors (value, high range).

Advanced settings allow a `HMeter` to display a value in a non-linear
manner (e.g. for levels and frequencies) using transfer functions and / or
to use non-line color gradients for display using gradient functions.


### ValueHMeter

`ValueHMeter` is a HMeter Widget with an additional label for
displaying its value.


### HScale

`HScale` is a Valueable Widget derived from `HMeter`. It displays a value as a 
horizontal scale and supports user interaction via `Clickable`, `Draggable`, 
and `Scrollable`. Its appearance is defined by the BgColors parameter (static 
elements) and by the FgColors parameter (value).


### HSlider

`HSlider` is a HScale Widget. It displays a value as a horizontal
slider and supports user interaction via `Clickable`, `Draggable`, and
`Scrollable`. Its appearance is defined by the BgColors parameter (static
elements, knob) and by the FgColors parameter (value).


### ValueHSlider
`ValueHSlider` is a HSlider Widget with an additional editable label for
displaying its value.


### VMeter

`VMeter` is a Valueable Widget and displays a value as a vertical
meter without user interaction. The value is kept within a defined range
and displayed in blocks defined by the parameter @a step . Its appearance
is defined by the parameters BgColors (static elements), FgColors (value,
low range), and HiColors (value, high range).

Advanced settings allow a `VMeter` to display a value in a non-linear
manner (e.g. for levels and frequencies) using transfer functions and / or
to use non-line color gradients for display using gradient functions.


### ValueVMeter

`ValueVMeter` is a VMeter Widget with an additional label for
displaying its value.


### VScale

`VScale` is a Valueable Widget derived from `VMeter`. It displays a value as a
vertical scale and supports user interaction via `Clickable`, `Draggable`, and 
`Scrollable`. Its appearance is defined by the BgColors parameter (static 
elements) and by the FgColors parameter (value).


### VSlider

`VSlider` is a VScale Widget. It displays a value as a vertical
slider and supports user interaction via `Clickable`, `Draggable`, and
`Scrollable`. Its appearance is defined by the BgColors parameter (static
elements, knob) and by the FgColors parameter (value).


### ValueVSlider
`ValueVSlider` is a VSlider Widget with an additional editable label for
displaying its value.


### RadialMeter

`RadialMeter` is a Valueable Widget and displays a value as a radial
meter without user interaction. The value is kept within a defined range
and displayed in blocks defined by the parameter @a step . Its appearance
is defined by the parameters BgColors (static elements), FgColors (value,
low range), and HiColors (value, high range).

Advanced settings allow a `RadialMeter` to display a value in a non-linear
manner (e.g. for levels and frequencies) using transfer functions and / or
to use non-line color gradients for display using gradient functions.


### ValueRadialMeter

`ValueRadialMeter` is a RadialMeter Widget with an additional label for
displaying its value.


### Dial

`Dial` is a Valueable Widget derived from `RadialMeter`. It displays a pseudo 
3D dial consisting of a knob and an arc scale. It supports user interaction 
via `Clickable`, `Draggable`, and `Scrollable`. Its appearance is defined by 
the BgColors parameter (static elements) and by the FgColors parameter (value).


### ValueDial
`ValueDial` is a Dial Widget with an additional editable label for
displaying its value.


### HPianoRoll


## Attributes and decorations


### URID

ID number of the widget derived from its URI (see class `BUtilities::Urid`).
The URID is set upon widget construction and can be returned using `getUrid()`.
The widget URID can be used to assign styles and to identify a widget.


### Title

The widget title is shown in the case of a `Window` object in the title bar.
It can also be used to identify a widget. The widget title is set with 
`rename()` and returned by `getTitle()`.


### Visibility

Widgets added directly or indirectly to the main window become visible by 
default. The visibility can be changed using `show()` and `hide()` and is
returned by `isVisible()`. Child widgets become invisible too if their
parent widget is hidden and gain back visibility if their parent widget is
shown again.


### Level and Stacking

Widgets are displayed in the order they are added to the main window from
back (first added) to front (last added). In the same way, child widgets are
displayed embedded into the parent widget in order they are added to it.

The order (level) can be changed using `raise()`, `raiseToFront()`, `drop()`,
and `dropToBack()`.

By default, child widgets are located within their parents and oversized child 
widgets will be clipped to fit (`STACKING_NORMAL`). `STACKING_EXCEED` breaks
this limitation. Stacking behaviour can be changed using `setStacking()` and
is returned by `getStacking()`


### Position

A widget can be placed relative to its parent widget using `moveTo()` using
X and Y coordinates and `moveRel()`. Its position relative to its parent widget
is returned by `getPosition()`. The methods `left()`, `center()`, `right()`, 
`top()`, `middle()`, and `bottom()` can be used to get widget X or Y 
coordinates for relative placement of the widget in combination with 
`moveTo()`.

Thus, to center a widget (horizontally and vertically) relative to its parent
widget simply call:

```
widget.moveTo (widget.center(), widget.middle());
```


### Size

The size of a widget can be changed using `resize()` and is returned by 
`getExtends()`, `getWidth()`, or `getHeight()`. The parameter-free `resize()`
methods tries to fit the widget size to its content. Parameter-free `resize()`
will resize the widget to (0, 0) if it has got no children and no content with
a restricted size.


### Style

Widgets can be decorates with styles using `setStyle()`. The setter methods
`setBackground()`, `setBorder()`, `setFont()`, `setFgColors()`, 
`setBgColors()`, and `setTxColors()` and their respective getter methods 
`getBackground()`, `getBorder()`, `getFont()`, `getFgColors()`, 
`getBgColors()`, and `getTxColors()` allow a shortcut access to the default
widget StyleProperties:
* *Background*, a `BStyles::Fill`, which can take up an image or a color.
* *Border*, a `BStyles::Border`, defined by its parameters margin, line (width, 
  color), padding, and corner radius.
* *Font*, a `BStyles::Font`.
* *FgColors*, a `BStyles::ColorMap` (a `std::map` consisting of a 
  `BStyles::Color` for each status) for active / foreground widget elements.
* *BgColors*, a `BStyles::ColorMap` for inactive / background widget elements.
* *TxColors*, a `BStyles::ColorMap` for text and labels.

Example: Changing the text colors of a label `l` is simply done by:

```
l.setTxColors (reds);    // Changes text colors for l to reds
```

Styles can also include other styles in a recursive way to describe 
specific widget elements or to forward them to included child widgets.


### Status

A widget can take the states `STATUS_NORMAL`, `STATUS_ACTIVE`, 
`STATUS_INACTIVE`, `STATUS_OFF`, and `STATUS_USER_DEFINED` as defined in
`BStyles::Status`. The widget status is relevant for status-dependent
decorations (like FgColors, BgColors, and TxColors) and widgets (like `Image`). 

The status is set by `setStatus()` and returned by `getStatus()`.


### Widget-specific attributes and decorations

Specifc widgets may have got specific attributes and decorations. Like values,
ranges, labels, ... . They may inherit their attributes and decorations from 
their Supports (see there).


## Events

Also see main Window.


## Supports

Part of the BWidgets namespace. [Supports](Supports/README.md) are fully or
partially defined interface classes to add additional features to objects
(incl. Widgets).


## Pugl

[Pugl](https://github.com/lv2/pugl) (PlUgin Graphics Library) is a minimal
portable API for GUIs which is suitable for use in plugins. It works on X11,
MacOS, and Windows, and optionally supports Vulkan, OpenGL, and Cairo graphics
contexts. Pugl is written by David Robillard *et al.*

BWidgets uses the Cairo graphics context support of Pugl.


## TODO

* Use NanoVG.
* Load images from SVG.