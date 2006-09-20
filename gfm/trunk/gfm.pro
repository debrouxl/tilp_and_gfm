TEMPLATE	= app
LANGUAGE	= C

CONFIG	-= qt debug_and_release debug_and_release_target
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

pkgdata.path = $$PREFIX/share/gfm
pkgdata.files = man/Manpage.txt

glade.path = $${pkgdata.path}/glade
glade.files = glade/*.glade glade/*.gladep

icons.path = $${pkgdata.path}/icons
icons.files = icons/*.ico icons/ListOfTypes.txt

pixmaps.path = $${pkgdata.path}/pixmaps
pixmaps.files = pixmaps/*.xpm

man.path = $$PREFIX/share/man/man1
man.files = man/gfm.1

INSTALLS += pkgdata target glade icons pixmaps man

CFLAGS = $$(CFLAGS)
isEmpty(CFLAGS) {
  debug {
    CFLAGS = -Os -g
  } else {
    CFLAGS = -Os -s -fomit-frame-pointer
  }
}
QMAKE_CFLAGS_DEBUG = $$CFLAGS $$PKGCONFIG_CFLAGS -DSHARE_DIR='"'"$$PREFIX/share/gfm"'"'
QMAKE_CFLAGS_RELEASE = $$CFLAGS $$PKGCONFIG_CFLAGS -DSHARE_DIR='"'"$$PREFIX/share/gfm"'"'

QMAKE_LFLAGS_RELEASE = -s

DISTFILES += $${pkgdata.files} $${glade.files} $${icons.files} $${pixmaps.files} $${man.files} build/mingw/* build/devcpp/* glade/*.str man/cleaner.c INFO README acinclude.m4 configure.ac aclocal.m4 Makefile.am Makefile.in config.h.in configure AUTHORS COPYING ChangeLog INSTALL NEWS compile config.guess config.sub depcomp install-sh ltmain.sh missing build/Makefile.am build/Makefile.in glade/Makefile.am glade/Makefile.in help/Makefile.am help/Makefile.in icons/Makefile.am icons/Makefile.in man/Makefile.am man/Makefile.in pixmaps/Makefile.am pixmaps/Makefile.in src/Makefile.am src/Makefile.in

distbz2.target = dist-bzip2
distbz2.commands = zcat gfm.tar.gz | bzip2 --best -c > gfm.tar.bz2
distbz2.depends = dist
QMAKE_EXTRA_UNIX_TARGETS += distbz2
