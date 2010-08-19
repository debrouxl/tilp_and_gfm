## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS=-I m4

# subdirectories to scan
SUBDIRS = build builder glade help icons pixmaps po src wicons

if USE_GROFF
  SUBDIRS += man
endif

dist_pkgdata_DATA = COPYING RELEASE

EXTRA_DIST = README.* TODO po/copy.bat desktop install.bat

#bundle:
#	tar cvf tarball.tar /usr/share/tilp /usr/bin/tilp /usr/lib/libticables* /usr/lib/libticalcs* /usr/lib/libtifiles*
#	gzip tarball.tar
