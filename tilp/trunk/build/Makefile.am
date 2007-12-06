SUBDIRS = mingw
EXTRA_DIST = fedora InnoSetup mingw msvc osx

dist-hook:
	if test ! -d .svn; then \
	rm -f *.odt
	fi
	rm -rf $(distdir)/*.odt
