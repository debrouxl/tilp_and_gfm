## Process this file with automake to produce Makefile.in

DEFS = @DEFS@ -DPLUGIN_DIR=\"$(pkglibdir)\"
AM_CPPFLAGS = -I$(top_srcdir)/intl

# program to compile and install
noinst_PROGRAMS = tilpreg
tilpreg_SOURCES = main.c main.h

registrydir = $(pkgdatadir)/tilp
dist_registry_DATA = tilp.registry

install:
	@$(INSTALL) -d $(tilp_plugin_dir)
