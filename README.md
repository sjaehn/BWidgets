# B.Widgets
Widget toolkit based on Cairo and PUGL.

This is a simple widget toolkit for the B.Music projects.

**This toolkit is still in development**

Dependencies
------------
* Cairo
* X11 (for Linux systems, for MacOS X and Windows see description)

Install the developers versions of these packages first. BWidgets may also be adapted to MacOS X and Windows. For these systems, take hands on and adapt the final parameter in line 2 of the makefile.

Installation
------------
Clone this repository. To build the demo simply call

```
make
```
from the root directory of the clone.

Run the demo
------------
Simply call

```
./demo
```

Usage
-----
BWidgets is a toolkit intended to use directly in B.Music projects. If you want to use it, simply copy the BWidgets folder (includig its subfolders) into your project folder. Remove the widgets you don't need, but take care for dependencies.

Class hierarchy
---------------
```
namespace BColors
 ├── Color
 ╰── ColorSet

namespace BStyles
 ├── Line
 ├── Border
 ├── Fill
 ├── Font
 ├── Style
 ├── StyleSet
 ╰── Theme

namespace BEvents
 ╰── Event
      ├── ExposeEvent
      ├── KeyEvent
      ├── PointerEvent
      ├── WheelEvent
      ├── FocusEvent
      ╰── ValueChangedEvent

namespace BItems
 ╰── Item

namespace BWidgets
 ╰── Widget
      ├── Window
      ├── FocusWidget
      ├── DrawingSurface
      ├── ImageIcon
      ├── Label
      ├── Text
      ├── Knob
      ├── ValueWidget
      │    ├── Button
      │    │    ├── UpButton
      │    │    ├── DownButton
      │    │    ├── TextButton
      │    │    ╰── ToggleButton
      │    │         ╰── TextToggleButton
      │    ├── MessageBox
      │    ├── ItemBox
      │    │    ╰── PopupListBox
      │    ├── ChoiceBox
      │    │    ╰── ListBox
      │    ╰── RangeWidget
      │         ├── Dial
      │         │    ╰── DisplayDial
      │         ├── HScale
      │         │    ╰── HSlider
      │         │         ├── HSwitch
      │         │         ╰── DisplayHSlider
      │         ╰── VScale
      │              ╰── VSlider
      │                   ├── VSwitch
      │                   ╰── DisplayVSlider
      ╰── PianoWidget
           ╰── HPianoRoll

```

Widgets
-------

All widget classes of BWidgets are derived from **BWidgets::Widget**. This widget class contain all important basic widget informations, such as position in the widget tree (children, parent, main), position on screen (relative to its parent widget), size, border, background, visibility and their ability to emit events (clickability, draggability, scrollability, focusability). Thus, all derived widget inherit and may extend these properties.

The most important class of BWidgets is **BWidgets::Window**. An object of this class is not only the main window to add all other widget to. Is also hosts the event handler and represents the connection to the system. Therefore, only one BWidgets::Window is allowed.

The **BWidgets::FocusWidget** class is the only derived class that is handled in both BWidgets::Widget and BWidgets::Window. It is a container class for widgets that pop up (or off) upon a FocusEvent. The widget itself hosts parameters for FocusEvent handling, such as the time for focus in and out.

**BWidgets::ValueWidget**s extends BWidgets::Widgets by a value and their ability to emit ValueChangedEvents.

In **BWidgets::RangeWidget**s, the value is additionally kept within a defines range.
