SHELL = /bin/sh

# pgk-config
PKG_CONFIG ?= pkg-config
PKG_LIBS += sndfile x11 cairo
ifneq ($(shell $(PKG_CONFIG) --exists fontconfig || echo no), no)
	PKG_LIBS += fontconfig
	CPPFLAGS += -DPKG_HAVE_FONTCONFIG
endif

# archive
AR ?= ar
ARFLAGS = rcs

# compiler
CC ?= gcc
CXX ?= g++
CPPFLAGS += -DPIC -DPUGL_HAVE_CAIRO
CXXFLAGS += -std=c++11 -g -Wall -fPIC
CFLAGS += -Wall -fPIC -g
PKGCFLAGS = `$(PKG_CONFIG) --cflags $(PKG_LIBS)`
PKGLFLAGS = `$(PKG_CONFIG) --libs --static $(PKG_LIBS)`
LDFLAGS +=

# destination
BUILDDIR ?= build
INCLUDEDIR ?= include

# resources
PUGL_C_FILES = pugl/src/common.c pugl/src/internal.c
CORE_CPP_FILES = BUtilities/Urid.cpp BUtilities/Dictionary.cpp BWidgets/Supports/Closeable.cpp BWidgets/Supports/Messagable.cpp BWidgets/Window.cpp BWidgets/Widget.cpp

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

BUNDLE = widgetgallery helloworld buttontest symbols pattern styles themes draws values  

all: cairoplus pugl bwidgets $(BUNDLE)

$(BUILDDIR)/libcairoplus.a: BUtilities/cairoplus.h BUtilities/cairoplus.c
	mkdir -p $(INCLUDEDIR)
	cd $(INCLUDEDIR); mkdir -p BUtilities
	cp BUtilities/cairoplus.h $(INCLUDEDIR)/BUtilities
	mkdir -p $(@D)
	mkdir -p $@.tmp
	cd $@.tmp ; $(CC) $(CPPFLAGS) $(CFLAGS) $(PKGCFLAGS) -I$(CURDIR)/include $(addprefix $(CURDIR)/, BUtilities/cairoplus.c) -c
	echo $@
	$(AR) $(ARFLAGS) $@ $@.tmp/*.o
	rm -rf $@.tmp

$(BUILDDIR)/libpugl.a: $(shell find pugl/)
	mkdir -p $(INCLUDEDIR)
	cp -r pugl/include/pugl $(INCLUDEDIR)
	mkdir -p $(@D)
	mkdir -p $@.tmp
	cd $@.tmp ; $(CC) $(CPPFLAGS) $(CFLAGS) $(PKGCFLAGS) -I$(CURDIR)/include $(addprefix $(CURDIR)/, $(PUGL_C_FILES)) -c
	$(AR) $(ARFLAGS) $@ $@.tmp/*.o
	rm -rf $@.tmp

$(BUILDDIR)/libbwidgetscore: $(BUILDDIR)/libcairoplus.a $(BUILDDIR)/libpugl.a $(shell find BDevices/) $(shell find BEvents/) $(shell find BMusic/) $(shell find BStyles/) $(shell find BUtilities/) $(shell find BWidgets/)
	mkdir -p $(INCLUDEDIR)
	find BDevices/ -iname '*.hpp' | cpio -pdm include/
	find BEvents/ -iname '*.hpp' | cpio -pdm include/
	find BMusic/ -iname '*.h' | cpio -pdm include/
	find BStyles/ -iname '*.hpp' | cpio -pdm include/
	find BUtilities/ -iname '*.hpp' | cpio -pdm include/
	find BWidgets/ -iname '*.hpp' | cpio -pdm include/
	mkdir -p $(@D)
	mkdir -p $@
	cd $@ ; $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PKGCFLAGS) -I$(CURDIR)/include $(addprefix $(CURDIR)/, $(CORE_CPP_FILES)) -c
#	$(AR) $(ARFLAGS) $@ $@/*.o

cairoplus: $(BUILDDIR)/libcairoplus.a
	
pugl: $(BUILDDIR)/libpugl.a

bwidgets: $(BUILDDIR)/libbwidgetscore

$(addprefix $(BUILDDIR)/, $(BUNDLE)): $(BUILDDIR)/libbwidgetscore
	mkdir -p $(@D)
	cd $(@D); $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PKGCFLAGS) -I$(CURDIR)/include $(CURDIR)/examples/$(@F).cpp -c -o $(@F).o
	cd $(@D); $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -L$(CURDIR)/$(BUILDDIR) libbwidgetscore/*.o -lpugl -lcairoplus $(@F).o $(PKGLFLAGS) -o $(@F)
#	cd $(@D); $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -L$(CURDIR)/$(BUILDDIR) -lbwidgetscore -lpugl -lcairoplus $(@F).o $(PKGLFLAGS) -o $(@F)
#	cd $(@D); $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PKGCFLAGS) -I$(CURDIR)/include -o $(@F) $(CURDIR)/examples/$(@F).cpp $(LDFLAGS) -L$(CURDIR)/$(BUILDDIR) -Wl,--start-group $(PKGLFLAGS) -lcairoplus -lpugl -lbwidgetscore -Wl,--end-group


$(BUNDLE):
	$(MAKE) $(BUILDDIR)/$@


clean:
	rm -rf $(BUILDDIR)
	rm -rf $(INCLUDEDIR)

.PHONY: cairoplus pugl bwidgets all clean

