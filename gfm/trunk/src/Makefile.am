## Process this file with automake to produce Makefile.in

AM_CFLAGS = -Wall -W

# programs and files to compile and install
bin_PROGRAMS = gfm

# build instructions
gfm_CPPFLAGS = @TIFILES_CFLAGS@ @TICONV_CFLAGS@ @TICALCS_CFLAGS@ \
	@GLIB_CFLAGS@ @GTK_CFLAGS@ @GLADE_CFLAGS@ \
	-DSHARE_DIR=\"$(pkgdatadir)\" \
	-I$(top_srcdir)/intl \
	-DLOCALEDIR=\"$(datadir)/locale\"

gfm_LDFLAGS = -export-dynamic

gfm_LDADD = \
	@TIFILES_LIBS@ @TICONV_LIBS@ @TICALCS_LIBS@ \
	@GLIB_LIBS@ @GTK_LIBS@ @GLADE_LIBS@

# automake wants all .c files listed explicitly. This sucks. qmake does the
# right thing with just "*.c".
gfm_SOURCES = \
	*.h \
	cmdline.c \
	ctree.c \
	dialog.c \
	file.c \
	filesel.c \
	gui.c \
	labels.c \
	main.c \
	paths.c \
	rwgroup.c \
	splashscreen.c \
	support.c \
	tilibs.c \
	ungroup.c

if OS_WIN32
  gfm_DEPENDENCIES = ../build/mingw/gfm-rc.o
  gfm_LDFLAGS += -Wl,../build/mingw/gfm-rc.o
endif