## Process this file with automake to produce Makefile.in

AM_CFLAGS = -Wall

# programs and files to compile and install
bin_PROGRAMS = tilp

# build instructions
tilp_CPPFLAGS = -I$(top_srcdir)/intl \
	@TICABLES_CFLAGS@ @TIFILES_CFLAGS@ @TICALCS_CFLAGS@ @TICONV_CFLAGS@ \
	@GLIB_CFLAGS@ @GTK_CFLAGS@ \
	-DSHARE_DIR=\"$(pkgdatadir)\" \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-DSYSCONFDIR=\"$(sysconfdir)\" \
	-DGTK_DISABLE_DEPRECATED
#	@KDE_INCLUDES@ @QT_INCLUDES@
tilp_LDFLAGS = -export-dynamic
tilp_LDADD = @TICABLES_LIBS@ @TIFILES_LIBS@ @TICALCS_LIBS@ @TICONV_LIBS@ \
	@GLIB_LIBS@ @GTK_LIBS@ @LIBZ@
#	@LIB_KDECORE@ @LIB_KDEUI@ @LIB_KIO@ @LIB_QT@ @KDE_LDFLAGS@ @QT_LDFLAGS@ @X_LDFLAGS@
tilp_SOURCES = *.h \
	tilp_calcs.c tilp_cmdline.c tilp_config.c tilp_error.c \
	tilp_files.c tilp_gif.c tilp_main.c \
	tilp_misc.c tilp_paths.c tilp_screen.c tilp_slct.c \
	tilp_update.c tilp_vars.c tilp_device.c tilp.c main.c \
	\
	about.c action.c bookmark.c clist.c clist_rbm.c clock.c \
	ctree.c ctree_rbm.c dboxes.c device.c dnd.c filesel.c \
	gtk_gif.c gtk_update.c labels.c manpage.c options.c pbars.c \
	release.c screenshot.c scroptions.c splash.c support.c \
	toolbar.c fileprop.c

if OS_WIN32
  tilp_DEPENDENCIES = ../build/mingw/tilp-rc.o
  tilp_LDFLAGS += -Wl,../build/mingw/tilp-rc.o
endif

#if USE_KDE
#  tilp_SOURCES += kde.cpp
#  nodist_tilp_SOURCES = kde-private.cpp
#  CLEANFILES = kde-private.cpp
#
#  kde-private.cpp: kde-private.h
#	  @MOC@ kde-private.h -o kde-private.cpp
#else
#  EXTRA_DIST = kde.cpp
#endif

dos2unix:
	dos2unix
	lowercase
	uppercase
