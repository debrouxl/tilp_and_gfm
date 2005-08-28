## Process this file with automake to produce Makefile.in

# subdirectories to scan
SUBDIRS = build glade help icons intl pixmaps src #po

if USE_GROFF
SUBDIRS += man
endif

dist_pkgdata_DATA = COPYING RELEASE

EXTRA_DIST = README.* TODO po/TRANSLATORS

#bundle:
#	tar cvf tarball.tar /usr/share/tilp /usr/bin/tilp /usr/lib/libticables* /usr/lib/libticalcs* /usr/lib/libtifiles*
#	gzip tarball.tar
