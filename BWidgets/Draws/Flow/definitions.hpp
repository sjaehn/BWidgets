#ifndef BWIDGETS_DEFAULT_DRAWARC_PATH
#define BWIDGETS_DEFAULT_DRAWARC_PATH "Draws/Flow/drawArc.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWKNOB_PATH
#define BWIDGETS_DEFAULT_DRAWKNOB_PATH "Draws/Flow/drawKnob.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWARCHANDLE_PATH
#define BWIDGETS_DEFAULT_DRAWARCHANDLE_PATH "Draws/Flow/drawArcHandle.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWHBAR_PATH
#define BWIDGETS_DEFAULT_DRAWHBAR_PATH "Draws/Flow/drawHBar.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWVBAR_PATH
#define BWIDGETS_DEFAULT_DRAWVBAR_PATH "Draws/Flow/drawVBar.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWHMETER_PATH
#define BWIDGETS_DEFAULT_DRAWHMETER_PATH "Draws/Flow/drawHMeter.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWVMETER_PATH
#define BWIDGETS_DEFAULT_DRAWVMETER_PATH "Draws/Flow/drawVMeter.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWRMETER_PATH
#define BWIDGETS_DEFAULT_DRAWRMETER_PATH "Draws/Flow/drawRMeter.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWBUTTON_PATH
#define BWIDGETS_DEFAULT_DRAWBUTTON_PATH "Draws/Flow/drawButton.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DRAWPAD_PATH
#define BWIDGETS_DEFAULT_DRAWPAD_PATH "Draws/Flow/drawPad.hpp"
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_ARC_FGCOLOR
#define BWIDGETS_DEFAULT_DIAL_ARC_FGCOLOR getFgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_ARC_BGCOLOR
#define BWIDGETS_DEFAULT_DIAL_ARC_BGCOLOR getBgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_KNOB_REL_SIZE 
#define BWIDGETS_DEFAULT_DIAL_KNOB_REL_SIZE 0.8
#endif

#ifndef BWIDGETS_DEFAULT_DIAL_KNOB_COLOR
#define BWIDGETS_DEFAULT_DIAL_KNOB_COLOR getBgColors()[getStatus()]
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
#define BWIDGETS_DEFAULT_SLIDER_KNOB_COLOR getBgColors()[getStatus()]
#endif

#ifndef BWIDGETS_DEFAULT_SWITCH_BAR_REL_SIZE 
#define BWIDGETS_DEFAULT_SWITCH_BAR_REL_SIZE 0.9
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
#define BWIDGETS_DEFAULT_SWITCH_KNOB_COLOR getBgColors()[getStatus()]
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
#define BWIDGETS_DEFAULT_SCROLLBAR_KNOB_COLOR getBgColors()[getStatus()].illuminate(BStyles::Color::illuminated)
#endif