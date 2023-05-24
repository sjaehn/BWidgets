#ifndef BWIDGETS_DEFAULT_DRAWARC_PATH
#define BWIDGETS_DEFAULT_DRAWARC_PATH "Draws/Lolly/drawArc.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWKNOB_PATH
#define BWIDGETS_DEFAULT_DRAWKNOB_PATH "Draws/Lolly/drawKnob.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWARCHANDLE_PATH
#define BWIDGETS_DEFAULT_DRAWARCHANDLE_PATH "Draws/Lolly/drawArcHandle.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWHBAR_PATH
#define BWIDGETS_DEFAULT_DRAWHBAR_PATH "Draws/Lolly/drawHBar.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWVBAR_PATH
#define BWIDGETS_DEFAULT_DRAWVBAR_PATH "Draws/Lolly/drawVBar.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWHMETER_PATH
#define BWIDGETS_DEFAULT_DRAWHMETER_PATH "Draws/Lolly/drawHMeter.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWVMETER_PATH
#define BWIDGETS_DEFAULT_DRAWVMETER_PATH "Draws/Lolly/drawVMeter.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWRMETER_PATH
#define BWIDGETS_DEFAULT_DRAWRMETER_PATH "Draws/Lolly/drawRMeter.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWBUTTON_PATH
#define BWIDGETS_DEFAULT_DRAWBUTTON_PATH "Draws/Lolly/drawButton.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWPAD_PATH
#define BWIDGETS_DEFAULT_DRAWPAD_PATH "Draws/Lolly/drawPad.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_ARC_FGCOLOR
#define BWIDGETS_DEFAULT_DIAL_ARC_FGCOLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_ARC_BGCOLOR
#define BWIDGETS_DEFAULT_DIAL_ARC_BGCOLOR getBgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_KNOB_REL_SIZE 
#define BWIDGETS_DEFAULT_DIAL_KNOB_REL_SIZE 0.0
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_KNOB_COLOR
#define BWIDGETS_DEFAULT_DIAL_KNOB_COLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE 
#define BWIDGETS_DEFAULT_SLIDER_BAR_REL_SIZE 0.25
#endif

#ifndef BWIDGETS_DEFAULT_SLIDER_BAR_FGCOLOR
#define BWIDGETS_DEFAULT_SLIDER_BAR_FGCOLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SLIDER_BAR_BGCOLOR
#define BWIDGETS_DEFAULT_SLIDER_BAR_BGCOLOR getBgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SLIDER_KNOB_REL_SIZE 
#define BWIDGETS_DEFAULT_SLIDER_KNOB_REL_SIZE 1.0
#endif

#ifndef BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR
#define BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SWITCH_BAR_REL_SIZE 
#define BWIDGETS_DEFAULT_SWITCH_BAR_REL_SIZE 0.5
#endif

#ifndef BWIDGETS_DEFAULT_SWITCH_BAR_FGCOLOR
#define BWIDGETS_DEFAULT_SWITCH_BAR_FGCOLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SWITCH_BAR_BGCOLOR
#define BWIDGETS_DEFAULT_SWITCH_BAR_BGCOLOR getBgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SWITCH_KNOB_REL_SIZE 
#define BWIDGETS_DEFAULT_SWITCH_KNOB_REL_SIZE 1.0
#endif

#ifndef BWIDGETS_DEFAULT_SWITCH_KNOB_COLOR
#define BWIDGETS_DEFAULT_SWITCH_KNOB_COLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SCROLLBAR_BAR_REL_SIZE 
#define BWIDGETS_DEFAULT_SCROLLBAR_BAR_REL_SIZE 1.0
#endif

#ifndef BWIDGETS_DEFAULT_SCROLLBAR_BAR_FGCOLOR
#define BWIDGETS_DEFAULT_SCROLLBAR_BAR_FGCOLOR getBgColors()[getStatus()].illuminate(BStyles::Color::illuminated)
#endif

#ifndef BWIDGETS_DEFAULT_SCROLLBAR_BAR_BGCOLOR
#define BWIDGETS_DEFAULT_SCROLLBAR_BAR_BGCOLOR getBgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SCROLLBAR_KNOB_REL_SIZE 
#define BWIDGETS_DEFAULT_SCROLLBAR_KNOB_REL_SIZE 0.25
#endif

#ifndef BWIDGETS_DEFAULT_SCROLLBAR_KNOB_COLOR
#define BWIDGETS_DEFAULT_SCROLLBAR_KNOB_COLOR getBgColors()[getStatus()].illuminate(0.5 * BStyles::Color::illuminated)
#endif