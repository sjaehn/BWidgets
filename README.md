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