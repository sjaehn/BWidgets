SHELL = /bin/sh

PKG_CONFIG ?= pkg-config
PKG_LIBS += sndfile x11 cairo
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

BUNDLE = widgetgallery helloworld buttontest symbols pattern styles themes draws values

CXX_INCL = $(shell cat cppfiles.txt) 
C_INCL = $(shell cat cfiles_x11.txt)

all: $(BUNDLE)

$(BUNDLE):
	mkdir -p $@.tmp
	cd $@.tmp ; $(CC) $(CPPFLAGS) $(CFLAGS) $(PKGCFLAGS) $(addprefix ../, $(C_INCL)) -c
	cd $@.tmp ; $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PKGCFLAGS) $(addprefix ../, examples/$@.cpp $(CXX_INCL)) -c
	$(CXX) $(CPPFLAGS) -iquote $(CXXFLAGS) $(LDFLAGS) -Wl,--start-group $(PKGLFLAGS) $@.tmp/*.o -Wl,--end-group -o $@
	rm -rf $@.tmp
