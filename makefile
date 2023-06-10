SHELL = /bin/sh

# destination
BUILDDIR ?= build
INCLUDEDIR ?= include

# resources
PUGL_C_FILES = pugl/src/common.c pugl/src/internal.c
CORE_CPP_FILES = BUtilities/Urid.cpp BUtilities/Dictionary.cpp BWidgets/Window.cpp BWidgets/Widget.cpp

# pgk-config
PKG_CONFIG ?= pkg-config
PKG_LIBS += sndfile x11 cairo
ifneq ($(shell $(PKG_CONFIG) --exists fontconfig || echo no), no)
	override PKG_LIBS += fontconfig
	override CPPFLAGS += -DPKG_HAVE_FONTCONFIG
endif
PKGCFLAGS = `$(PKG_CONFIG) --cflags $(PKG_LIBS)`
PKGLIBS = `$(PKG_CONFIG) --libs --static $(PKG_LIBS)`

# archive
AR ?= ar
ARFLAGS = rcs

# compiler
CC ?= gcc
CXX ?= g++
override CPPFLAGS += -DPIC -I$(CURDIR)/$(INCLUDEDIR) $(PKGCFLAGS)
override CXXFLAGS += -std=c++17 -fPIC
override CFLAGS += -fPIC
override LDFLAGS += -L$(CURDIR)/$(BUILDDIR)

# os
ifeq ($(OS), Windows_NT)
	override PUGL_C_FILES += pugl/src/win.c pugl/src/win_cairo.c pugl/src/win_stub.c
else
	UNAME = $(shell uname)
	ifeq ($(UNAME), Darwin)
		override PUGL_C_FILES += pugl/src/mac.m pugl/src/mac_cairo.m pugl/src/mac_stub.m
	else
		override PUGL_C_FILES += pugl/src/x11.c pugl/src/x11_cairo.c pugl/src/x11_stub.c
	endif
endif

BUNDLE = widgetgallery helloworld buttontest symbols pattern styles themes draws values valuepositions

all: cairoplus pugl bwidgets $(BUNDLE)

$(BUILDDIR)/libcairoplus.a: BUtilities/cairoplus.h BUtilities/cairoplus.c
	mkdir -p $(INCLUDEDIR)
	cd $(INCLUDEDIR); mkdir -p BUtilities
	cp BUtilities/cairoplus.h $(INCLUDEDIR)/BUtilities
	mkdir -p $(@D)
	mkdir -p $@.tmp
	cd $@.tmp ; $(CC) $(CPPFLAGS) $(CFLAGS) $(addprefix $(CURDIR)/, BUtilities/cairoplus.c) -c
	$(AR) $(ARFLAGS) $@ $@.tmp/*.o
	rm -rf $@.tmp

$(BUILDDIR)/libpugl.a: $(shell find pugl/)
	mkdir -p $(INCLUDEDIR)
	cp -r pugl/include/pugl $(INCLUDEDIR)
	mkdir -p $(@D)
	mkdir -p $@.tmp
	cd $@.tmp ; $(CC) $(CPPFLAGS) $(CFLAGS) $(addprefix $(CURDIR)/, $(PUGL_C_FILES)) -c
	$(AR) $(ARFLAGS) $@ $@.tmp/*.o
	rm -rf $@.tmp

$(BUILDDIR)/libbwidgetscore.a: $(BUILDDIR)/libcairoplus.a $(BUILDDIR)/libpugl.a $(shell find BDevices/) $(shell find BEvents/) $(shell find BMusic/) $(shell find BStyles/) $(shell find BUtilities/) $(shell find BWidgets/)
	mkdir -p $(INCLUDEDIR)
	find BDevices/ -iname '*.hpp' | cpio -pdm include/
	find BEvents/ -iname '*.hpp' | cpio -pdm include/
	find BMusic/ -iname '*.h' | cpio -pdm include/
	find BStyles/ -iname '*.hpp' | cpio -pdm include/
	find BUtilities/ -iname '*.hpp' | cpio -pdm include/
	find BWidgets/ -iname '*.hpp' | cpio -pdm include/
	mkdir -p $(@D)
	mkdir -p $@.tmp
	cd $@.tmp ; $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(addprefix $(CURDIR)/, $(CORE_CPP_FILES)) -c
	$(AR) $(ARFLAGS) $@ $@.tmp/*.o
	rm -rf $@.tmp

$(addprefix $(BUILDDIR)/, $(BUNDLE)): $(BUILDDIR)/libbwidgetscore.a
	mkdir -p $(@D)
	cd $(@D); $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PKGCFLAGS) -I$(CURDIR)/include $(CURDIR)/examples/$(@F).cpp -c -o $(@F).o
	cd $(@D); $(CXX) $(LDFLAGS) $(@F).o -lbwidgetscore -lpugl -lcairoplus $(PKGLIBS) -o $(@F)

$(BUNDLE):
	$(MAKE) $(BUILDDIR)/$@

cairoplus: $(BUILDDIR)/libcairoplus.a
	
pugl: $(BUILDDIR)/libpugl.a

bwidgets: $(BUILDDIR)/libbwidgetscore.a

clean:
	rm -rf $(BUILDDIR)
	rm -rf $(INCLUDEDIR)

.PHONY: cairoplus pugl bwidgets all clean

