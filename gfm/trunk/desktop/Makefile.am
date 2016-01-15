desktopdir = $(datadir)/applications
pixmapsdir = $(pkgdatadir)/pixmaps
appdatadir = $(datadir)/appdata
desktop_in_files = gfm.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
appdata_files = gfm.appdata.xml
appdata_DATA = gfm.appdata.xml

EXTRA_DIST = $(desktop_in_files) $(appdata_files) README.txt

CLEANFILES = $(desktop_in_files:.desktop.in=.desktop)

gfm.desktop:
	cat $(srcdir)/$@.in | sed -e "s=\@bindir\@=${bindir}=" | sed -e "s=\@pixmapsdir\@=${pixmapsdir}=" > $@
