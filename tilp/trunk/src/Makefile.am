## Process this file with automake to produce Makefile.in

if OS_WIN32
 no_undefined = -no-undefined
endif

DEFS=@DEFS@ \
	-DSHARE_DIR=\"${prefix}/share/tilp\" 	\
	-DLOCALEDIR=\"$(locale_dir)\" 		\
	-DPLUGIN_DIR=\"${tilp_plugin_dir}\"

INCLUDES = -I$(top_srcdir) -I$(includedir) \
	-I../intl -I$(top_srcdir)/intl \
	-DPREFIX=\"${prefix}\" -I. -I../ -I../../

# program to compile and install 
bin_PROGRAMS = tilp

tilp_SOURCES = \
	tilp_calcs.c tilp_error.c tilp_files.c tilp_indep.c tilp_main.c \
	tilp_misc.c tilp_prompt.c tilp_rcfile.c tilp_refresh.c tilp_screen.c \
	tilp_slct.c tilp_vars.c tilp_paths.c \
	tilp_plugin.c main.c \
	\
	support.c toolbar.c gtk_refresh.c \
	\
	tilp.c dboxes.c pbars.c clist.c ctree.c labels.c popup.c \
	general.c extprgms.c comm.c clock.c filesel.c manpage.c \
	about.c release.c scroptions.c screenshot.c splash.c wizard.c \
	shell.c action.c

noinst_HEADERS = *.h

EXTRA_DIST = win32

# libtool stuff: set export symbols for resolving
tilp_LDFLAGS = $(LDFLAGS) $(no_undefined) #-lefence
tilp_CFLAGS = $(CLFAGS) -DGTK_DISABLE_DEPRECATED

install-data-local:
	$(INSTALL) -m755 -d $(DESTDIR)$(includedir)/tilp
	$(INSTALL) -m644 tilp_plugin.h $(DESTDIR)$(includedir)/tilp

dos2unix:
	dos2unix
	lowercase
	uppercase