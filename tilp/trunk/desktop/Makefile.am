desktopdir = $(datadir)/applications
pixmapsdir = $(pkgdatadir)/pixmaps
desktop_in_files = tilp.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

EXTRA_DIST = $(desktop_in_files) README.txt

CLEANFILES = $(desktop_in_files:.desktop.in=.desktop)

tilp.desktop:
	cat $(srcdir)/$@.in | sed -e "s=\@bindir\@=${bindir}=" | sed -e "s=\@pixmapsdir\@=${pixmapsdir}=" > $@
