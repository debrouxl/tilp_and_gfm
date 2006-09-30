#
# Template
#

TEMPLATE	= app
LANGUAGE	= C

CONFIG	+= warn_on debug

HEADERS	+= src/*.h

SOURCES	+= src/*.c

QMAKE_PROJECT_DEPTH=1

unix:OBJECTS_DIR = .obj

#
# Dependancies and Version checking
#

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

TICABLES_MINVERSION = 1.0.0
HAVE_TICABLES = $$system(pkg-config --atleast-version=$$TICABLES_MINVERSION ticables2 && echo yes || echo no)
!equals(HAVE_TICABLES,yes):error(libticables $$TICABLES_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags ticables2)
LIBS += $$system(pkg-config --libs ticables2)

TICALCS_MINVERSION = 1.0.0
HAVE_TICALCS = $$system(pkg-config --atleast-version=$$TICALCS_MINVERSION ticalcs2 && echo yes || echo no)
!equals(HAVE_TICALCS,yes):error(libticalcs $$TICALCS_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags ticalcs2)
LIBS += $$system(pkg-config --libs ticalcs2)

TIFILES_MINVERSION = 1.0.0
HAVE_TIFILES = $$system(pkg-config --atleast-version=$$TIFILES_MINVERSION tifiles2 && echo yes || echo no)
!equals(HAVE_TIFILES,yes):error(libtifiles2 $$TIFILES_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags tifiles2)
LIBS += $$system(pkg-config --libs tifiles2)

TICONV_MINVERSION = 1.0.0
HAVE_TICONV = $$system(pkg-config --atleast-version=$$TICONV_MINVERSION ticonv && echo yes || echo no)
!equals(HAVE_TICONV,yes):error(libticonv $$TICONV_MINVERSION or higher required.)
PKGCONFIG_CFLAGS += $$system(pkg-config --cflags ticonv)
LIBS += $$system(pkg-config --libs ticonv)

exists( /usr/lib/libz* ) 
{
  message( "Configuring for libz..." )
  CFLAGS += -DHAVE_LIBZ
}

#
# Path settings
#

PREFIX = $$(PREFIX)
isEmpty(PREFIX) {
  PREFIX = /usr/local
}

target.path = $$PREFIX/bin

pkgdata.path = $$PREFIX/share/tilp2
pkgdata.files = man/Manpage.txt RELEASE

glade.path = $${pkgdata.path}/glade
glade.files = glade/*.glade glade/*.gladep

help.path = $${pkgdata.path}/help
help.files = help/*.html help/*.png

icons.path = $${pkgdata.path}/icons
icons.files = icons/*.ico

man.path = $$PREFIX/share/man/man1
man.files = man/tilp-2.1

pixmaps.path = $${pkgdata.path}/pixmaps
pixmaps.files = pixmaps/*.xpm

INSTALLS += pkgdata glade help icons man pixmaps

#
# Various flags
#

VERSION = 1.00
PACKAGE = TiLP2

LIBS	+= -Wl,--export-dynamic

linux-* { ARCH = -D__LINUX__ }
else *bsd-* { ARCH = -D__BSD__ }
else win32-* { ARCH = -D__WIN32__ }
CFLAGS += $$ARCH

isEmpty(CFLAGS) {
  debug {
    CFLAGS = -Os -g
  } else {
    CFLAGS = -Os -s -fomit-frame-pointer
  }
}
QMAKE_CFLAGS_DEBUG = $$CFLAGS $$PKGCONFIG_CFLAGS -DSHARE_DIR='"'"$${pkgdata.path}"'"' -DVERSION='"$$VERSION"' -DPACKAGE='"$$PACKAGE"'
QMAKE_CFLAGS_RELEASE = $$CFLAGS $$PKGCONFIG_CFLAGS -DSHARE_DIR='"'"$${pkgdata.path}"'"' -DVERSION='"$$VERSION"' -DPACKAGE='"$$PACKAGE"'

QMAKE_LFLAGS_RELEASE = -s

#
# Distribution
#

DISTFILES += $${pkgdata.files} $${glade.files} $${icons.files} $${pixmaps.files} $${man.files} build/mingw/* build/devcpp/* glade/*.str man/cleaner.c INFO README acinclude.m4 configure.ac aclocal.m4 Makefile.am Makefile.in config.h.in configure AUTHORS COPYING ChangeLog INSTALL NEWS compile config.guess config.sub depcomp install-sh ltmain.sh missing build/Makefile.am build/Makefile.in glade/Makefile.am glade/Makefile.in help/Makefile.am help/Makefile.in icons/Makefile.am icons/Makefile.in man/Makefile.am man/Makefile.in pixmaps/Makefile.am pixmaps/Makefile.in src/Makefile.am src/Makefile.in

distbz2.target = dist-bzip2
distbz2.commands = zcat gfm.tar.gz | bzip2 --best -c > gfm.tar.bz2
distbz2.depends = dist

QMAKE_EXTRA_UNIX_TARGETS += distbz2
