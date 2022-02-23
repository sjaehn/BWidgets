# B.Widgets
Rewrite of the widget toolkit of the B.Music project. Work in progress. And 
still some space to fill (as you can see).

For a detailed description of the classes and methods of B.Widgets see
[BWidgets](BWidgets/README.md) and the other namespaces below the widget gallery.

![widgetgallery](suppl/widgetgallery.png)

The toolkit uses tools from six namespaces (further info there):
* `BDevices`
* [`BEvents`](BEvents/README.md)
* [`BMusic`](BMusic/README.md)
* [`BStyles`](BStyles/README.md)
* [`BUtilities`](BUtilities/README.md)
* [`BWidgets`](BWidgets/README.md)


## Dependencies

* Cairo
* X11 (for Linux systems, for MacOS X and Windows see description)

Install the developers versions of these packages first. BWidgets may also be 
adapted to MacOS X and Windows. For these systems, take hands on and adapt 
the parameter in the makefile.


## Installation

Clone or copy this repository as a subfolder into your project. Then you can
include the widgets (or events) you need into your project, e. g.:
```
#include "path_to_BWidgets/BWidgets/Label.hpp"
#include "path_to_BWidgets/BEvents/PointerEvent.hpp"
```

To build the example binaries, simply call

```
make
```
from the root directory of the clone to build all examples, or

```
make [examples]
```

with optional parameter `[examples]` which can be `widgetgallery`, 
`helloworld`, `buttontest`, `symbols`, and/or `pattern`. This will only build
the respective example.

Then call the respective example, e. g.:
```
./widgetgallery
```


## TODO

### Until 1.0

- [ ] Widgets
  - [x] Basic container widgets (Widget, Window, Frame, ...)
  - [x] Text widgets (Label, Text, ...)
  - [x] Button and switch widgets
  - [x] Choice box widgets (SpinBox, ListBox, ComboBox, ...)
  - [x] Meter widgets
  - [x] Sliders and dial widgets
  - [x] Pad widgets
  - [x] Pattern widget
  - [ ] Shape widget
  - [x] Piano roll widget
  - [x] Image-based widgets
  - [x] Dialog widgets (Box, TextBox, MessageBox, ...)
  - [x] File selection dialog widgets (FileChooser, SampleChooser)
- [ ] URID
- [ ] Dictionary
  - [x] Add translations for words and phrases used by the widgets
  - [ ] Fallback to installed third party dictionaries (e. g., GTK)
- [ ] Styles
  - [x] Types (Color, ColorMap, Line, Border, ...)
  - [x] Set widget styles
  - [ ] Forward and update styles to child widgets with matching URID
- [x] Events
  - [x] Base events (expose, close, ...)
  - [x] Mouse / Pointer events (press, release, click, drag, move, scroll, focus)
  - [x] Keyboard events
  - [x] Value change events
  - [x] Custom message events
  - [x] Handle events in main Window
  - [x] Enable events in widgets using interface classes (Supports)
- [ ] Widget functionality
  - [x] Container functionality by supporting `Linkable`
  - [x] Visualization by supporting `Visualizable`
  - [x] Event handling in the main Window
  - [x] Control of event handling by supporting `EventMergeable` and 
        `EventPassable`
  - [x] User interaction by supporting `Clickable`, `Draggable`, `Focusable`,
        `Toggleable`, `Scrollable` and `KeyPressable`
  - [x] Generic control over widget values using `Valueable`
  - [x] Additional messages by supporting `Messageable` 
  - [x] Widget visibility control by supporting `Closeable`
  - [x] Enable re-definition of widget default sizes
        (`BWIDGETS_DEFAULT_XXX_WIDTH` and `BWIDGETS_DEFAULT_XXX_HEIGHT`)
  - [x] Define substitutable widget elemet draw functions (see Draws)
  - [x] Optimize widget size using `resize()`
  - [x] Show default hover text (widget title, if set) by supporting
        `Focusable`
  - [x] Layers
  - [ ] Scale (zoom) main Window and linked child widgets
- [ ] Header files only (if possible)
- [ ] Documentation


### Until 1.2

- [ ] Layout widgets.
- [ ] Load images from SVG.


### Until 1.4+

- [ ] Time events
- [ ] Enable scale (zoom) for all widgets
- [ ] Use NanoVG.