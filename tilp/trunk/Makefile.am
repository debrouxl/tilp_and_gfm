## Process this file with automake to produce Makefile.in

# subdirectories to scan
SUBDIRS = \
	build desktop glade help icons intl man misc \
	pixmaps po src registry #plugins

EXTRA_DIST = README.* RELEASE TODO po/TRANSLATORS

bundle:
	tar cvf tarball.tar /usr/share/tilp /usr/bin/tilp /usr/lib/libticables* /usr/lib/libticalcs* /usr/lib/libtifiles*
	gzip tarball.tar
