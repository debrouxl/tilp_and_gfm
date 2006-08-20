LINK_ICONS = \
	App_Var.ico \
	Complex_List.ico \
	Complex_Matrix.ico \
	Complex_Vector.ico \
	Diff_Equ.ico \
	Function.ico \
	Parametric.ico \
	Polar.ico \
	Y_Var.ico

iconsdir = $(pkgdatadir)/icons
icons_DATA = $(LINK_ICONS) *.ico

EXTRA_DIST = *.ico

dist-hook:
	@list='$(LINK_ICONS)'; for icon in $$list; do \
	  rm -rf $(distdir)/$$icon; \
	done

App_Var.ico: Application.ico
	ln -sf Application.ico App_Var.ico
Complex_List.ico: List.ico
	ln -sf List.ico Complex_List.ico
Complex_Matrix.ico: Matrix.ico
	ln -sf Matrix.ico Complex_Matrix.ico
Complex_Vector.ico: Vector.ico
	ln -sf Vector.ico Complex_Vector.ico
Diff_Equ.ico: Equation.ico
	ln -sf Equation.ico Diff_Equ.ico
Function.ico: Equation.ico
	ln -sf Equation.ico Function.ico
Parametric.ico: Equation.ico
	ln -sf Equation.ico Parametric.ico
Polar.ico: Equation.ico
	ln -sf Equation.ico Polar.ico
Y_Var.ico: Equation.ico
	ln -sf Equation.ico Y_Var.ico

FN = `echo $$I | sed 's/\.ico$//'`

convert:
	@echo Converting icons to pixmaps
	@for I in *.ico ; do \
		echo $$I into $(FN).xpm; \
		winicontoppm $$I | ppmtoxpm  -name $(FN) > $(FN).xpm; \
	done
	@echo Done
