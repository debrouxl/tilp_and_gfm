## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/intl
AM_CFLAGS = -Wall

# programs and files to compile and install 
bin_PROGRAMS = tilp
pkginclude_HEADERS = tilp_plugin.h

# build instructions
tilp_CPPFLAGS = @TICABLES_CFLAGS@ @TIFILES_CFLAGS@ @TICALCS_CFLAGS@ \
	@GLIB_CFLAGS@ @GTK_CFLAGS@ @GLADE_CFLAGS@ \
	-DSHARE_DIR=\"$(pkgdatadir)\" \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-DPLUGIN_DIR=\"$(pkglibdir)\" \
	-DSYSCONFDIR=\"$(sysconfdir)\" \
	-DGTK_DISABLE_DEPRECATED
tilp_LDADD = @TICABLES_LIBS@ @TIFILES_LIBS@ @TICALCS_LIBS@ \
	@GLIB_LIBS@ @GTK_LIBS@ @GLADE_LIBS@ \
	@LTLIBINTL@
tilp_SOURCES = *.h \
	tilp_calcs.c tilp_error.c tilp_files.c tilp_indep.c tilp_main.c \
	tilp_misc.c tilp_prompt.c tilp_rcfile.c tilp_refresh.c tilp_screen.c \
	tilp_slct.c tilp_vars.c tilp_paths.c \
	tilp_plugin.c tilp_printl.c main.c \
	\
	support.c toolbar.c gtk_refresh.c \
	\
	tilp.c dboxes.c pbars.c clist.c ctree.c labels.c popup.c \
	general.c extprgms.c comm.c clock.c filesel.c logfile.c manpage.c \
	about.c release.c scroptions.c screenshot.c splash.c wizard.c \
	shell.c action.c dnd.c

dos2unix:
	dos2unix
	lowercase
	uppercase
