## Process this file with automake to produce Makefile.in

# subdirectories to scan
SUBDIRS = \
	build desktop glade help icons intl man misc \
	pixmaps po src plugins registry

EXTRA_DIST = \
	ABOUT-NLS AUTHORS ChangeLog COPYING INSTALL* NEWS 	\
	README README* TODO RELEASE ./po/TRANSLATORS

INCLUDES = -I$(top_srcdir) -I$(includedir) 		\
	-I../intl -I$(top_srcdir)/intl 			\
	-DPREFIX=\"${prefix}\" -I. -I../ -I../../

bundle:
	tar cvf tarball.tar /usr/share/tilp /usr/bin/tilp /usr/lib/libticables* /usr/li\b/libticalcs* /usr/lib/libtifiles*
	gzip tarball.tar



