SUBDIRS = mingw
EXTRA_DIST = InnoSetup mingw msvc osx scripts

dist-hook:
	if test ! -d .svn; then \
	rm -f *.odt; \
	fi
	rm -rf $(distdir)/*.odt
