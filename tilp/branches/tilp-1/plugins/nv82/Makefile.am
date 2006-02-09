## Process this file with automake to produce Makefile.in

libexecdir = $(tilpplugindir)
libdir = $(tilp_plugin_dir)

plugin_name		= nv82

lib_LTLIBRARIES         = libnv82.la

libnv82includedir       = $(includedir)/tilp
libnv82_la_LDFLAGS      = -export-dynamic
nv82_public_h_sources   = *.h
nv82_c_sources          = main.c interface.c callbacks.c support.c
libnv82include_HEADERS  = $(nv82_public_h_sources)
libnv82_la_SOURCES      = $(nv82_c_sources)

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


