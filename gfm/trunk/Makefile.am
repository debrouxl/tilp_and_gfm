## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS=-I m4

# subdirectories to scan
SUBDIRS = build builder desktop glade help icons pixmaps po src

if USE_GROFF
  SUBDIRS += man
endif

DISTCLEANFILES = ... intltool-extract intltool-merge intltool-update po/.intltool-merge-cache

INTLTOOL_FILES = intltool-extract.in intltool-merge.in intltool-update.in
