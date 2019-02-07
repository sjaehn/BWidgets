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
      ├── PointerEvent
      ├── WheelEvent
      ╰── ValueChangedEvent
       
namespace BItems
 ╰── Item
 
namespace BWidgets
 ╰── Widget
      ├── Window
      ├── DrawingSurface
      ├── Label
      ├── Text
      ├── Knob
      ╰── ValueWidget
           ├── Button
           │    ├── UpButton
           │    ├── DownButton
           │    ├── TextButton
           │    ╰── ToggleButton
           │         ╰── TextToggleButton
           ├── MessageBox
           ├── ItemBox
           │    ╰── PopupListBox
           ├── ChoiceBox
           │    ╰── ListBox
           ╰── RangeWidget
                ├── Dial
                │    ╰── DisplayDial
                ├── HScale
                │    ╰── HSlider
                │         ├── HSwitch
                │         ╰── DisplayHSlider
                ╰── VScale
                     ╰── VSlider
                          ├── VSwitch
                          ╰── DisplayVSlider
 
```