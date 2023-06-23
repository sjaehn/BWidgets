# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [1.5.0] - 2023-06-23
* Implement emit key events to widgets which grabbed selected keys
* Add substeps to `BWidgets::ValidatableRange`
* Implement substep scrolling and dragging if shift key pressed in (image-) 
  dial, scale, and scrollbar widgets
* Fix documentation


## [1.4.0] - 2023-06-20
* Merge 1.3.0 - 1.3.2, in brief:
  * Move event queue from `BWidgets::Windows` to `BWidgets::EventQueueable`,
    inherit in `BWidgets::Windows`
  * Make `BWidgets::Messagable` and `BWidgets::Closeable` header only
  * Add `BEvents::Event::EventType::all`
  * Enable uint16_t for `BDevices::Keys::KeyType`
  * Add `BDevices::Keys::KeyType::enter`
  * Add class `BWidgets::Activatable` for user driven widget status change
  * Add class `BWidgets::Enterable` for entering a widget
  * Add class `BWidgets::Navigatable` to navigate between child widgets
  * Add hot keys and methods to `BWidgets::Enterable`
  * Add enter by hot key method in `BWidgets::Navigatable`
  * Implement `BWidgets::Activatable`, `BWidgets::Enterable`, and / or
    `BWidgets::Navigatable` in `BWidgets::FileChooser`, 
    `BWidgets::SampleChooser`, `BWidgets::EditLabel`, `BWidgets::SpinBox`, 
    `BWidgets::ListBox`, `BWidgets::ComboBox`, `BWidgets::Box` and
    `BWidgets::Button`
  * Fix prevent twice addition of events to the event loop
  * Fix issue #6 by always updating child widgets in `BWidgets::Box`
  * Update documentation


## [1.3.2] - 2023-06-18
* Enable uint16_t for `BDevices::Keys::KeyType`
* Add `BDevices::Keys::KeyType::enter`
* Add hot keys and methods to `BWidgets::Enterable`
* Add enter by hot key method in `BWidgets::Navigatable`
* Implement enter by hot key in widgets
* Fix issue #6 by always updating child widgets in `BWidgets::Box`


## [1.3.1] - 2023-06-17
* Add `Navigatable::enterNavigated()`, `Navigatable::resetNavigation()`,
  `Navigatable::isNavigated()`
* Remove unused `Navigatable::autoDeactivation_`
* Change implementation of `BWidgets::Enterable`, now at `BWidgets::Widget`
  level.
* Furter extend implementation of `BWidgets::Enterable` in 
  `BWidgets::FileChooser`, `BWidgets::SampleChooser`, `BWidgets::EditLabel`,
  `BWidgets::SpinBox`, `BWidgets::ListBox`, `BWidgets::ComboBox`


## [1.3.0] - 2023-06-10
* Add class `BWidgets::Activatable` and implement in `BWidgets::Widget`
* Add class `BWidgets::Navigatable` and implement in `BWidgets::Box`
* Add class `BWidgets::Enterable` and implement in `BWidgets::Box` and
  `BWidgets::Button`
* Add `BEvents::Event::EventType::all`
* Move event queue from `BWidgets::Windows` to `BWidgets::EventQueueable`,
  inherit in `BWidgets::Windows`
* Make `BWidgets::Messagable` and `BWidgets::Closeable` header only
* Fix prevent twice addition of events to the event loop
* Update documentation


## [1.2.2] - 2023-06-02
* Fix incorrectly displayed meter values due to floating point operations
* Animate meters in draws and valuepositions demo


## [1.2.0] - 2023-06-02
* Merge 1.1.0 - 1.1.3, in brief:
    * Add default and parametrized constructors to `BWidgets::Support`
    * Add class `BWidgets::ValueVisualizable`
    * Add parametrized overrides of `getExtends()`, `getWidth()`, and `getHeight()` in `BWidgets::Label` to get Widget extends for a not yet applied text string
    * Implement `BWidgets::ValueVisualizable::ValuePosition` in ValueDials, ValueMeters, and ValueSliders (Note: Minor changes in widget element positioning (esp. in `BWidgets::ValueHSlider`) to become more consistent)
    * Add definitions `BWIDGETS_DEFAULT_XXX_XSPACING` and `BWIDGETS_DEFAULT_XXX_YSPACING` for spacing between label and dial/meter/slider.
    * Add drawing sets color parameters
    * Add drawing sets bar size paramters
    * Add drawing sets Lolly and Flow
    * Add functional focus text
    * Add `Widget::setFocusText()` and `Widget::getFocusText()`
    * Fix `drawPad()` call in `Pad<T>::draw()`
    * Fix implementation of `BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE` (now only applies on Sliders; now matches with `BWIDGETS_DEFAULT_SLIDER_KNOB_REL_SIZE`)
    * Fix warnings unused variables fgColor and bgColor
    * Add value position demo
    * Update documentation
    

## [1.1.3] - 2023-06-02
* Added default and parametrized constructors to `BWidgets::Support`
* Fix center `BWidgets::RadialMeter`
* Add class `BWidgets::ValueVisualizable`
* Add parametrized overrides of `getExtends()`, `getWidth()`, and `getHeight()` 
in `BWidgets::Label` to get Widget extends for a not yet applied text string
* Implement `BWidgets::ValueVisualizable::ValuePosition` in ValueDials,
ValueMeters, and ValueSliders (Note: Minor changes in widget element 
positioning (esp. in `BWidgets::ValueHSlider`) to become more consistent)
* Add definitions `BWIDGETS_DEFAULT_XXX_XSPACING` and 
`BWIDGETS_DEFAULT_XXX_YSPACING` for spacing between label and 
dial/meter/slider.
* Add value position demo


## [1.1.2] - 2023-05-27
* Added `Widget::setFocusText()` and `Widget::getFocusText()`
* Implemented functional focus Label text


## [1.1.1] - 2023-05-24

* Fixed implementation of `BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE` (now only
applies on Sliders; now matches with `BWIDGETS_DEFAULT_SLIDER_KNOB_REL_SIZE`)
* Fixed warnings unused variables fgColor and bgColor


## [1.1.0] - 2023-05-24

* Added drawing sets color parameters
* Added drawing sets bar size paramters
* Added drawing set Lolly
* Added drawing set Flow
* Added documentation for drawing set parameters in BWidgets/README.md
* Fixed `drawPad()` call in `Pad<T>::draw()`


## [1.0.0] - 2023-05-22

First release.

### Features provided

* Widgets
    * Basic container widgets (`Widget`, `Window`, `Frame`, ...)
    * Text widgets (`Label`, `Text`, ...)
    * Button and switch widgets
    * Choice box widgets (`SpinBox`, `ListBox`, `ComboBox`, ...)
    * Meter widgets
    * Sliders and dial widgets
    * Pad widgets
    * Pattern widget
    * Piano roll widget
    * Image-based widgets
    * Dialog widgets (`Box`, `TextBox`, `MessageBox`, ...)
    * File selection dialog widgets (`FileChooser`, `SampleChooser`)
* Styles
    * Types (`Color`, `ColorMap`, `Line`, `Border`, ...)
    * Forward and update styles to child widgets with matching URID (see 
      below)
    * Use themes
*Devices
    * Keyboard support
    * Mouse support
    * Take control (grab) or release control (free) over devices
    * Implement to support dragging, clicking, enter text
* Events
    * Base events (expose, close, ...)
    * Mouse / Pointer events (press, release, click, drag, move, scroll, focus)
    * Keyboard events
    * Value change events
    * Custom message events
    * Handle events in main Window
    * Enable events in widgets using interface classes (Supports)
* Widget functionality
    * Container functionality by supporting `Linkable`
    * Visualization by supporting `Visualizable`
    * Event handling in the main Window
    * Control of event handling by supporting `EventMergeable` and 
    `EventPassable`
    * User interaction by supporting `Clickable`, `Draggable`, `PointerFocusable`,
    `Toggleable`, `Scrollable` and `KeyPressable`
    * Generic control over widget values using `Valueable`
    * Additional messages by supporting `Messageable` 
    * Widget visibility control by supporting `Closeable`
    * Enable re-definition of widget default sizes at compile time
    (`BWIDGETS_DEFAULT_XXX_WIDTH` and `BWIDGETS_DEFAULT_XXX_HEIGHT`)
    * Define substitutable widget elemet drawing sets at compile time
     (draws)
    * Optimize widget size using `resize()`
    * Show default hover text (widget title, if set) by supporting
    `PointerFocusable`
    * Layers visualization and event handling
    * Scale (zoom) main Window and linked child widgets
    * Reversed Valueable widgets by `setStep()` with negative values
    * Transfer functions to transfer values from an external context to an 
    internal context. 
* URID
    * Static URID management: Link URIs to their respective ID
    * Assign URIDs to styles, widgets, ...
* Dictionary
    * Static management of terms and translations
    * Default dictionary for common UI dialogs
    * Dictionary replacable at compile time
    * Add terms and translations at runtime
    * Optional fallback to installed third party dictionaries (e. g., GTK)
* Shortcut macros (`BURID`, `BDICT`, ...)
* Doxygen documentation