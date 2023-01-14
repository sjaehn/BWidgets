# B.Widgets

Rewrite of the widget toolkit of the B.Music project.

B.Widgets is the Graphical User Interface (GUI) toolkit for the B.Music 
project. This toolkit includes widgets, styles, event handling, device support,
and internationalization. B.Widgets also takes care about the special needs for
user interaction elements in music production.

**Current version:** 0.23.0 (alpha)

**Pre-release notice:** The B.Widgets toolkit is currently being developed 
and still not officially released (alpha). Thus, there's no stable API yet.
This means the API still may change until the final release. This may cause
breaks. Keeping this in your mind, you may use this pre-release at your own 
risk. 

For a detailed description of the classes and methods of B.Widgets see
[BWidgets](BWidgets/README.md) and the other namespaces below the widget gallery.

![widgetgallery](suppl/widgetgallery.png)

The toolkit uses tools from six namespaces (further info there):
* [`BDevices`](BDevices/README.md)
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

Clone or copy this repository.

```
git clone https://github.com/sjaehn/BWidgets
```

will create a folder called `BWidgets` which contains all the files including
the examples.

To build all the example binaries, simply call

```
cd BWidgets
make
```

If you only want to install selected examples, call instead

```
cd BWidgets
make [examples]
```

with optional parameter `[examples]` which can be `widgetgallery`, 
`helloworld`, `buttontest`, `symbols`, `pattern`, `styles`, `themes`, `draws`, 
and/or `values`. 

Then execute the respective example, e. g.:
```
./widgetgallery
```

Note: If you want to use BWidgets within your project, copy or clone it as a
subdirectory into your project.

## Documentation

### Getting started ("Hello world!")

Once B.Widgets is installed, you can create a helloworld.cpp file and start 
coding. You have to
* include the widgets (or events, or ...) you need into your project,
* create a main window,
* create widgets (like a label),
* add the widgets to the main window,
* and call the main loop:

```
#include "path_to_BWidgets/BWidgets/Window.hpp"
#include "path_to_BWidgets/BWidgets/Label.hpp"

using namespace BWidgets;

int main ()
{
    Window w;
    Label l ("Hello World!");
    w.add (&l);
    w.run();
}
```

This is all of the magic.

To build this example, you have compile and link the .c and .cpp of B.Widgets 
and its Pugl graphics library. For the GNU C++ compiler for X11-based systems
you may call:
```
mkdir tmp
cd tmp
gcc -DPIC -DPUGL_HAVE_CAIRO -std=c99 -fPIC `pkg-config --cflags x11 cairo` \
../BWidgets/BUtilities/cairoplus.c \
../BWidgets/BWidgets/pugl/implementation.c \ 
../BWidgets/BWidgets/pugl/x11_stub.c \
../BWidgets/BWidgets/pugl/x11_cairo.c \
../BWidgets/BWidgets/pugl/x11.c -c
g++ -DPIC -DPUGL_HAVE_CAIRO -std=c++11 -fPIC `pkg-config --cflags x11 cairo` \
../helloworld.cpp \
../BWidgets/BUtilities/Urid.cpp \
../BWidgets/BUtilities/Dictionary.cpp \
../BWidgets/BWidgets/Supports/Closeable.cpp \
../BWidgets/BWidgets/Supports/Messagable.cpp \
../BWidgets/BWidgets/Window.cpp \
../BWidgets/BWidgets/Widget.cpp -c
cd ..
g++ -DPIC -DPUGL_HAVE_CAIRO -iquote -std=c++11 -fPIC -Wl,--start-group \ 
`pkg-config --libs x11 cairo` tmp/*.o -Wl,--end-group -o helloworld
rm -rf tmp
```

To see the result, call
```
./helloworld
```

Further reading: [BWidgets/README.md](BWidgets/README.md)


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
- [x] Devices
  - [x] Keyboard support
  - [x] Mouse support
  - [x] Take control (grab) or release control (free) over devices
  - [x] Implement to support dragging, clicking, enter text
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
  - [x] Layers visualization and event handling
  - [x] Scale (zoom) main Window and linked child widgets
  - [x] Reversed Valueable widgets by `setStep()` with negative values
  - [x] Enable / fix transfer functions
- [x] Define shortcut macros
- [x] Make at least the setters virtual (where possible)
- [x] Header files only (where possible)
- [x] Remove redundant methods, members and parameters before release of version 1.0
- [x] Documentation


### Until 1.2

- [x] Class Shape
- [ ] Shape widget
- [ ] Range widgets
- [ ] Functional focus label text
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
- [ ] Support fine adjustment for dials and sliders
- [ ] Support keyboard shortcuts in menus