SHELL=/bin/sh
#PREFIX=@prefix@
SHARE_DIR=$(prefix)/share/tilp
INSTALL=@INSTALL@

EXTRA_DIST = gnome/* kde/* others/*

install: $(FILES)
	@echo Installing magic local data for file\(1\) command...
	@if ! grep "\*\*TI85\*\*" /etc/magic; then	\
		cat others/magic >> /etc/magic;		\
	fi;
	@echo Done.

	@echo "---";

	@echo Installing Gnome VFS MIME magic patterns...
	@if ! grep "\*\*TI" /etc/gnome-vfs-mime-magic; then		\
		cat gnome/gnome-vfs-mime-magic >> /etc/gnome-vfs-mime-magic;	\
	fi;

	@echo Installing application registry in Gnome...
	@$(INSTALL) -d $(DESTDIR)/usr/share/application-registry
	@$(INSTALL) -m644 gnome/tilp.applications $(DESTDIR)/usr/share/application-registry

	@echo Installing file and icons handling in Gnome...
	@$(INSTALL) -d $(DESTDIR)/usr/share/mime-info
	@$(INSTALL) -m644 gnome/tilp.keys $(DESTDIR)/usr/share/mime-info
	@$(INSTALL) -m644 gnome/tilp.mime $(DESTDIR)/usr/share/mime-info

	@echo Installing TiLP menu entry in Gnome...
	@$(INSTALL) -d $(DESTDIR)/usr/share/applications
	@$(INSTALL) -m644 gnome/TiLP.desktop $(DESTDIR)/usr/share/applications
	@echo Done.

	@echo "---";

#	@echo Installing KMimeMagic local data...
#	@if ! grep "\*\*TI85" /usr/share/mimelnk/magic; then    \
#		cat kde/magic >> /usr/share/mimelnk/magic;      \
#	fi;

#	@echo Installing TiLP menu entry in KDE...
#	@$(INSTALL) -d $(DESTDIR)/usr/share/applnk/Edutainment/Mathematics
#	@$(INSTALL) -m644 kde/tilp.desktop $(DESTDIR)/usr/share/applnk/Edutainment/Mathematics/

#	@echo Installing file and icons handling in KDE...
#	@$(INSTALL) -m644 kde/x-tilp.desktop $(DESTDIR)/usr/share/mimelnk/application
#	@echo Done.

uninstall: $(FILES)
	@echo Removing desktop files...
	rm -f /usr/share/application-registry/tilp.application
	rm -f /usr/share/mime-info/tilp.*
	rm -f /usr/share/applications/TiLP.desktop
	rm -f /usr/share/applnk/Edutainment/Mathematics/tilp.desktop
	rm -f /usr/share/mimelnk/application/x-tilp.desktop
	@echo Done.


dos2unix:
	dos2unix
	lowercase
	uppercase
