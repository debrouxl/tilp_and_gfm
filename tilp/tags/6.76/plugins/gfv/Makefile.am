## Process this file with automake to produce Makefile.in

libexecdir = $(tilpplugindir)
libdir = $(tilp_plugin_dir)

plugin_name		= gfv

lib_LTLIBRARIES         = libgfv.la

libgfvincludedir       = $(includedir)/tilp
libgfv_la_LDFLAGS      = -export-dynamic
gfv_public_h_sources   = *.h
gfv_c_sources          = main.c interface.c callbacks.c support.c
libgfvinclude_HEADERS  = $(gfv_public_h_sources)
libgfv_la_SOURCES      = $(gfv_c_sources)

INCLUDES = \
	-I$(top_srcdir)		\
	$(GTK_CFLAGS)		\
	-I$(includedir)		\
	-I$(includedir)/tilp

LDADD = \
	$(GTK_LIBS)	\
	$(INTLLIBS)

AM_CPPFLAGS = \
	-DPLUGIN=\"$(plugin_name)\" -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_DATA_DIR=\"$(tilp_pixmap_dir)\"

.PHONY: files

files:
	@files=`ls $(DISTFILES) 2> /dev/null`; for p in $$files; do \
	  echo $$p; \
	done


