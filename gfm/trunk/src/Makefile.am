## Process this file with automake to produce Makefile.in

AM_CFLAGS = -Wall -W

# programs and files to compile and install
bin_PROGRAMS = gfm

# build instructions
gfm_CPPFLAGS = @TIFILES_CFLAGS@ @TICONV_CFLAGS@ \
	@GLIB_CFLAGS@ @GTK_CFLAGS@ @GLADE_CFLAGS@ \
	-DSHARE_DIR=\"$(pkgdatadir)\"
#	-I$(top_srcdir)/intl \
#	-DLOCALEDIR=\"$(datadir)/locale\" \
#	-DSYSCONFDIR=\"$(sysconfdir)\" \
#	-DGTK_DISABLE_DEPRECATED

gfm_LDFLAGS = -export-dynamic

gfm_LDADD = \
	@TIFILES_LIBS@ @TICONV_LIBS@ \
	@GLIB_LIBS@ @GTK_LIBS@ @GLADE_LIBS@

# automake wants all .c files listed explicitly. This sucks. qmake does the
# right thing with just "*.c".
gfm_SOURCES = \
	*.h \
	cmdline.c	\
	file.c		\
	ftree_sort.c	\
	main.c		\
	support.c	\
	configfile.c	\
	folder_tree.c  	\
	gui.c         	\
	paths.c         \
	tilibs.c	\
	dialog.c   	\
	ftree_menu.c   	\
	labels.c      	\
	splashscreen.c

