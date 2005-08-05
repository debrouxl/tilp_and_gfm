## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/intl
AM_CFLAGS = -Wall #-Wno-pointer-sign

# programs and files to compile and install 
bin_PROGRAMS = tilp2

# build instructions
tilp2_CPPFLAGS = @TICABLES_CFLAGS@ @TIFILES_CFLAGS@ @TICALCS_CFLAGS@ \
	@GLIB_CFLAGS@ @GTK_CFLAGS@ @GLADE_CFLAGS@ \
	-DSHARE_DIR=\"$(pkgdatadir)\" \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-DSYSCONFDIR=\"$(sysconfdir)\" \
	-DGTK_DISABLE_DEPRECATED
#tilp2_LDFLAGS = -Wl,--export-dynamic
tilp2_LDADD = @TICABLES_LIBS@ @TIFILES_LIBS@ @TICALCS_LIBS@ \
	@GLIB_LIBS@ @GTK_LIBS@ @GLADE_LIBS@ \
	@LTLIBINTL@ @LIBZ@
tilp2_SOURCES = *.h \
	tilp_calcs.c tilp_cmdline.c tilp_config.c tilp_error.c \
	tilp_files.c tilp_gif.c tilp_log.c tilp_main.c \
	tilp_misc.c tilp_paths.c tilp_screen.c tilp_slct.c \
	tilp_update.c tilp_vars.c tilp.c main.c \
	\
	about.c action.c bookmark.c clist.c clist_rbm.c clock.c \
	ctree.c ctree_rbm.c dboxes.c device.c dnd.c filesel.c \
	gtk_gif.c gtk_update.c labels.c manpage.c options.c pbars.c \
	release.c screenshot.c scroptions.c splash.c support.c \
	toolbar.c

dos2unix:
	dos2unix
	lowercase
	uppercase
