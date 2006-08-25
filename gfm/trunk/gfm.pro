TEMPLATE	= app
LANGUAGE	= C

CONFIG	+= warn_on debug

LIBS	+= -Wl,--export-dynamic

HEADERS	+= src/*.h

SOURCES	+= src/*.c

# If this is not used, a build from /usr/.... will generate
# Makefiles with relative paths for install.  This totally
# fucks up using INSTALL_ROOT for a staged install.
# See http://bugs.debian.org/180240
# (Thanks to Debian for the fix for this qmake stupidity.)
QMAKE_PROJECT_DEPTH=1

unix:OBJECTS_DIR = .obj

GLIB2_MINVERSION = 2.6.0
HAVE_GLIB2 = $$system(pkg-config --atleast-version=$$GLIB2_MINVERSION glib-2.0 && echo yes || echo no)
!equals(HAVE_GLIB2,yes):error(glib2 $$GLIB2_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags glib-2.0)
LIBS += $$system(pkg-config --libs glib-2.0)

GTK2_MINVERSION = 2.6.0
HAVE_GTK2 = $$system(pkg-config --atleast-version=$$GTK2_MINVERSION gtk+-2.0 && echo yes || echo no)
!equals(HAVE_GTK2,yes):error(gtk2 $$GTK2_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags gtk+-2.0)
LIBS += $$system(pkg-config --libs gtk+-2.0)

LIBGLADE2_MINVERSION = 2.5.0
HAVE_LIBGLADE2 = $$system(pkg-config --atleast-version=$$LIBGLADE2_MINVERSION libglade-2.0 && echo yes || echo no)
!equals(HAVE_LIBGLADE2,yes):error(glib2 $$LIBGLADE2_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags libglade-2.0)
LIBS += $$system(pkg-config --libs libglade-2.0)

TICONV_MINVERSION = 0.0.5
HAVE_TICONV = $$system(pkg-config --atleast-version=$$TICONV_MINVERSION ticonv && echo yes || echo no)
!equals(HAVE_TICONV,yes):error(libticonv $$TICONV_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags ticonv)
LIBS += $$system(pkg-config --libs ticonv)

TIFILES_MINVERSION = 0.2.2
HAVE_TIFILES = $$system(pkg-config --atleast-version=$$TIFILES_MINVERSION tifiles2 && echo yes || echo no)
!equals(HAVE_TIFILES,yes):error(libtifiles2 $$TIFILES_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags tifiles2)
LIBS += $$system(pkg-config --libs tifiles2)

PREFIX = $$(PREFIX)
isEmpty(PREFIX) {
  PREFIX = /usr/local
}

target.path = $$PREFIX/bin

glade.path = $$PREFIX/share/gfm/glade
glade.files = glade/*

icons.path = $$PREFIX/share/gfm/icons
icons.files = icons/*

pixmaps.path = $$PREFIX/share/gfm/pixmaps
pixmaps.files = pixmaps/*

INSTALLS += target glade icons pixmaps

CFLAGS = $$(CFLAGS)
isEmpty(CFLAGS) {
  debug {
    CFLAGS = -Os -g
  } else {
    CFLAGS = -Os -s -fomit-frame-pointer
  }
}
unix:CFLAGS += -D__LINUX__
win32:CFLAGS += -D__WIN32__
QMAKE_CFLAGS_DEBUG = $$CFLAGS $$PKGCONFIG_CFLAGS -DSHARE_DIR='"'"$$PREFIX/share/gfm"'"'
QMAKE_CFLAGS_RELEASE = $$CFLAGS $$PKGCONFIG_CFLAGS -DSHARE_DIR='"'"$$PREFIX/share/gfm"'"'

QMAKE_LFLAGS_RELEASE = -s

DISTFILES += $${glade.files} $${icons.files} $${pixmaps.files} build/ktigcc/* INFO

distbz2.target = dist-bzip2
distbz2.commands = zcat gfm.tar.gz | bzip2 --best -c > gfm.tar.bz2
distbz2.depends = dist
QMAKE_EXTRA_UNIX_TARGETS += distbz2
