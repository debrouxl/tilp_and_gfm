iconsdir = $(pkgdatadir)/icons
dist_icons_DATA = *.ico

convert:
	@echo Converting icons to pixmaps
	@for I in *.ico ; do \
		echo $$I into $(FN).xpm; \
		winicontoppm $$I | ppmtoxpm  -name $(FN) > $(FN).xpm; \
	done
	@echo Done

dos2unix:
	dos2unix
	lowercase
	uppercase
