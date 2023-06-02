# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


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