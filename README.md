# B.Widgets

Current version: 0.13.0 (alpha)

Rewrite of the widget toolkit of the B.Music project.

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
`helloworld`, `buttontest`, `symbols`, `pattern`, `styles`, `draws`, and/or 
`values`. 
This will only build the respective example.

Then call the respective example, e. g.:
```
./widgetgallery
```

## Documentation


## TODO

### Until 1.0

- [x] Widgets
  - [x] Basic container widgets (Widget, Window, Frame, ...)
  - [x] Text widgets (Label, Text, ...)
  - [x] Button and switch widgets
  - [x] Choice box widgets (SpinBox, ListBox, ComboBox, ...)
  - [x] Meter widgets
  - [x] Sliders and dial widgets
  - [x] Pad widgets
  - [x] Pattern widget
  - [x] Piano roll widget
  - [x] Image-based widgets
  - [x] Dialog widgets (Box, TextBox, MessageBox, ...)
  - [x] File selection dialog widgets (FileChooser, SampleChooser)
- [x] URID
  - [x] URID management
  - [x] Assign URIDs to styles, widgets, ...
- [x] Dictionary
  - [x] Add translations for words and phrases used by the widgets
  - [x] Fallback to installed third party dictionaries (e. g., GTK)
- [x] Styles
  - [x] Types (Color, ColorMap, Line, Border, ...)
  - [x] Set widget styles
  - [x] Forward and update styles to child widgets with matching URID
  - [x] Use themes
- [x] Events
  - [x] Base events (expose, close, ...)
  - [x] Mouse / Pointer events (press, release, click, drag, move, scroll, focus)
  - [x] Keyboard events
  - [x] Value change events
  - [x] Custom message events
  - [x] Handle events in main Window
  - [x] Enable events in widgets using interface classes (Supports)
- [x] Widget functionality
  - [x] Container functionality by supporting `Linkable`
  - [x] Visualization by supporting `Visualizable`
  - [x] Event handling in the main Window
  - [x] Control of event handling by supporting `EventMergeable` and 
        `EventPassable`
  - [x] User interaction by supporting `Clickable`, `Draggable`, `PointerFocusable`,
        `Toggleable`, `Scrollable` and `KeyPressable`
  - [x] Generic control over widget values using `Valueable`
  - [x] Additional messages by supporting `Messageable` 
  - [x] Widget visibility control by supporting `Closeable`
  - [x] Enable re-definition of widget default sizes
        (`BWIDGETS_DEFAULT_XXX_WIDTH` and `BWIDGETS_DEFAULT_XXX_HEIGHT`)
  - [x] Define substitutable widget elemet draw functions (see Draws)
  - [x] Optimize widget size using `resize()`
  - [x] Show default hover text (widget title, if set) by supporting
        `PointerFocusable`
  - [x] Layers
  - [x] Scale (zoom) main Window and linked child widgets
  - [x] Reversed Valueable widgets by `setStep()` with negative values
  - [x] Enable / fix transfer functions
- [x] Define shortcut macros
- [ ] Header files only (where possible)
- [ ] Documentation


### Until 1.2

- [x] Class Shape
- [ ] Shape widget
- [ ] Update pugl


### Until 1.4

- [ ] Layout widgets
- [ ] Conditional widgets


### Until 1.6+

- [ ] Load images from SVG
- [ ] Time events
- [ ] Enable scale (zoom) for all widgets
- [ ] Vector-based zoom
- [ ] Use NanoVG
- [ ] Simplify mp3 support
- [ ] Link URID to third party
- [ ] Journal
- [ ] Import styles from TTL
- [ ] Import styles from JSON(-LD)
- [ ] Import dictionary from TTL
- [ ] Import dictionary from JSON(-LD)