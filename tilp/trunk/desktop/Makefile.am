desktopdir = $(datadir)/applications
mimedir = $(datadir)/mime/packages
pixmapsdir = $(pkgdatadir)/pixmaps
appdatadir = $(datadir)/appdata
desktop_in_files = tilp.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
mime_files = tilp.xml
mime_DATA = tilp.xml
appdata_files = tilp.appdata.xml
appdata_DATA = tilp.appdata.xml

EXTRA_DIST = $(desktop_in_files) $(mime_files) $(appdata_files) README.txt

CLEANFILES = $(desktop_in_files:.desktop.in=.desktop)

tilp.desktop:
	cat $(srcdir)/$@.in | sed -e "s=\@bindir\@=${bindir}=" | sed -e "s=\@pixmapsdir\@=${pixmapsdir}=" > $@
