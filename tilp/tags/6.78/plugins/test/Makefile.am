## Process this file with automake to produce Makefile.in

libexecdir = $(tilp_plugin_dir)
libdir = $(tilp_plugin_dir)

plugin_name		= "test"

lib_LTLIBRARIES         = libtest.la

libtestincludedir       = $(includedir)/tilp
libtest_la_LDFLAGS      = -export-dynamic
test_public_h_sources   = *.h
test_c_sources          = main.c
libtestinclude_HEADERS  = $(test_public_h_sources)
libtest_la_SOURCES      = $(test_c_sources)

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