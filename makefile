SHELL = /bin/sh

PKG_CONFIG ?= pkg-config
CXX ?= g++
CPPFLAGS += -DPIC
CXXFLAGS += -std=c++11 -g -fPIC -DPUGL_HAVE_CAIRO `$(PKG_CONFIG) --cflags --libs x11 cairo`
LDFLAGS +=

SRC = BWidgets-demo.cpp
INCL = BWidgets/HPianoRoll.cpp \
BWidgets/PianoWidget.cpp \
BWidgets/ImageIcon.cpp \
BWidgets/Icon.cpp \
BWidgets/PopupListBox.cpp \
BWidgets/ListBox.cpp \
BWidgets/ChoiceBox.cpp \
BWidgets/MessageBox.cpp \
BWidgets/ItemBox.cpp \
BWidgets/DrawingSurface.cpp \
BWidgets/VSwitch.cpp \
BWidgets/HSwitch.cpp \
BWidgets/DownButton.cpp \
BWidgets/UpButton.cpp \
BWidgets/TextToggleButton.cpp \
BWidgets/TextButton.cpp \
BWidgets/ToggleButton.cpp \
BWidgets/Button.cpp \
BWidgets/DialValue.cpp \
BWidgets/VSliderValue.cpp \
BWidgets/HSliderValue.cpp \
BWidgets/Dial.cpp \
BWidgets/VSlider.cpp \
BWidgets/VScale.cpp \
BWidgets/HSlider.cpp \
BWidgets/HScale.cpp \
BWidgets/RangeWidget.cpp \
BWidgets/ValueWidget.cpp \
BWidgets/Text.cpp \
BWidgets/Knob.cpp \
BWidgets/Label.cpp \
BWidgets/StateDisplay.cpp \
BWidgets/Display.cpp \
BWidgets/FocusWidget.cpp \
BWidgets/Window.cpp \
BWidgets/Widget.cpp \
BWidgets/BStyles.cpp \
BWidgets/BColors.cpp \
BWidgets/BEvents.cpp \
BWidgets/BItems.cpp \
BWidgets/BValues.cpp \
BWidgets/cairoplus.c \
BWidgets/pugl/pugl_x11_cairo.c \
BWidgets/pugl/pugl_x11.c

all:
	$(CXX) -iquote ./ -o demo $(SRC) $(INCL) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)
