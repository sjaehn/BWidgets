SHELL = /bin/sh

PKG_CONFIG ?= pkg-config
PKG_LIBS += x11 cairo
ifneq ($(shell $(PKG_CONFIG) --exists fontconfig || echo no), no)
  PKG_LIBS += fontconfig
  CPPFLAGS += -DPKG_HAVE_FONTCONFIG
endif

CC ?= gcc
CXX ?= g++
CPPFLAGS += -DPIC -DPUGL_HAVE_CAIRO
CXXFLAGS += -std=c++11 -g -Wall -fPIC
CFLAGS += -std=c99 -g -Wall -fPIC
PKGCFLAGS = `$(PKG_CONFIG) --cflags $(PKG_LIBS)`
PKGLFLAGS = `$(PKG_CONFIG) --libs $(PKG_LIBS)`
LDFLAGS +=

SRC = BWidgets-demo.cpp
CXX_INCL = \
BUtilities/to_string.cpp \
BUtilities/stof.cpp \
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
BWidgets/BItems.cpp

C_INCL = \
BWidgets/cairoplus.c \
BWidgets/pugl/implementation.c \
BWidgets/pugl/x11_stub.c \
BWidgets/pugl/x11_cairo.c \
BWidgets/pugl/x11.c

all:
	mkdir -p tmp
	cd tmp ; $(CC) $(CPPFLAGS) $(CFLAGS) $(PKGCFLAGS) $(addprefix ../, $(C_INCL)) -c
	cd tmp ; $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PKGCFLAGS) $(addprefix ../, $(SRC) $(CXX_INCL)) -c
	$(CXX) $(CPPFLAGS) -iquote $(CXXFLAGS) $(LDFLAGS) -Wl,--start-group $(PKGLFLAGS) tmp/*.o -Wl,--end-group -o demo
	rm -rf tmp
