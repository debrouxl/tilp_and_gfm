## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS=-I m4

# subdirectories to scan
SUBDIRS = build builder desktop help icons pixmaps po src wicons

if USE_GROFF
  SUBDIRS += man
endif

dist_doc_DATA = COPYING RELEASE

DISTCLEANFILES = ... intltool-extract intltool-merge intltool-update po/.intltool-merge-cache

EXTRA_DIST = README.* TODO po/copy.bat install.bat

#bundle:
#	tar cvf tarball.tar /usr/share/tilp /usr/bin/tilp /usr/lib/libticables* /usr/lib/libticalcs* /usr/lib/libtifiles*
#	gzip tarball.tar

INTLTOOL_FILES = intltool-extract.in intltool-merge.in intltool-update.in
