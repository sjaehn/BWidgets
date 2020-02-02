SHELL = /bin/sh

PKG_CONFIG ?= pkg-config
PKG_LIBS += x11 cairo
ifneq ($(shell $(PKG_CONFIG) --exists fontconfig || echo no), no)
  PKG_LIBS += fontconfig
  CPPFLAGS += -DPKG_HAVE_FONTCONFIG
endif

CXX ?= g++
CPPFLAGS += -DPIC -DPUGL_HAVE_CAIRO
CXXFLAGS += -std=c++11 -g -Wall -fPIC `$(PKG_CONFIG) --cflags --libs $(PKG_LIBS)`
LDFLAGS +=

SRC = BWidgets-demo.cpp
INCL = \
BUtilities/to_string.cpp \
BWidgets/FileChooser.cpp \
BWidgets/HPianoRoll.cpp \
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
BWidgets/Window.cpp \
BWidgets/Widget.cpp \
BWidgets/BStyles.cpp \
BWidgets/BColors.cpp \
BWidgets/BItems.cpp \
BWidgets/cairoplus.c \
BWidgets/pugl/pugl_x11_cairo.c \
BWidgets/pugl/pugl_x11.c

all:
	$(CXX) -iquote ./ -o demo $(SRC) $(INCL) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)
