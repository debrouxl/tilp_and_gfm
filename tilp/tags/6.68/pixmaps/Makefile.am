SHELL=/bin/sh
INSTALL=@INSTALL@

PIXMAPS = *.xpm
EXTRA_DIST = $(PIXMAPS)

install: $(PIXMAPS)
	@echo Installing pixmaps...
	@$(INSTALL) -m755 -d $(DESTDIR)$(tilp_pixmap_dir)
	@for I in ./*.xpm ; do \
		$(INSTALL) -m644 $$I $(DESTDIR)$(tilp_pixmap_dir)/; \
	done
	@echo Done

uninstall:
	@echo Removing pixmaps...
	$(RM) $(DESTDIR)$(tilp_pixmap_dir)/*.xpm

dos2unix:
	dos2unix
	lowercase
	uppercase