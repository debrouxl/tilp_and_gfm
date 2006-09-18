iconsdir = $(pkgdatadir)/icons
icons_DATA = *.ico

EXTRA_DIST = *.ico

FN = `echo $$I | sed 's/\.ico$//'`

convert:
	@echo Converting icons to pixmaps
	@for I in *.ico ; do \
		echo $$I into $(FN).xpm; \
		winicontoppm $$I | ppmtoxpm  -name $(FN) > $(FN).xpm; \
	done
	@echo Done
