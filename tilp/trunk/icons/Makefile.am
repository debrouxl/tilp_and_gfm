iconsdir = $(pkgdatadir)/icons
dist_icons_DATA = *.ico

convert:
	@echo Converting icons to pixmaps
	@for I in *.ico; do winicontoppm -writeand $$I $$I; \
	ppmtoxpm -alphamask $${I}_and.pbm $${I}_xor.ppm > \
	`echo $$I | sed -e 's/\.ico$$/.xpm/g'`; rm -f \
	$${I}_???.p?m; \
	done
	@echo Done

dos2unix:
	dos2unix
	lowercase
	uppercase
