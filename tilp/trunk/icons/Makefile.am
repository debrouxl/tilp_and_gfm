SHELL=/bin/sh
INSTALL=@INSTALL@

ICONS = *.ico
EXTRA_DIST = $(ICONS)

FN = `echo  $$I | mawk '{ gsub(/\.ico/, "", $$0); print ($$0)}'`

install: $(ICONS) links
	@echo Installing icons...
	@$(INSTALL) -m755 -d $(DESTDIR)$(tilp_icon_dir)
	@for I in *.ico ; do \
		$(INSTALL) -m644 $$I $(DESTDIR)$(tilp_icon_dir)/; \
        done
	@echo Done

uninstall:
	@echo Removing icons...
	$(RM) $(DESTDIR)$(tilp_icon_dir)/*.ico

convert:
	@echo Converting icons to pixmaps
	@for I in *.ico ; do \
		echo $$I into $(FN).xpm; \
		winicontoppm $$I | ppmtoxpm  -name $(FN) > $(FN).xpm; \
	done
	@echo Done

links:
	@echo Linking some icons...
	ln -sf Application.ico App_Var.ico
	ln -sf List.ico Complex_List.ico
	ln -sf Matrix.ico Complex_Matrix.ico
	ln -sf Vector.ico Complex_Vector.ico
	ln -sf Equation.ico Diff_Equ.ico
	ln -sf Equation.ico Function.ico
	ln -sf Equation.ico Parametric.ico
	ln -sf Equation.ico Polar.ico
	ln -sf Equation.ico Y_Var.ico
	@echo Done

dos2unix:
	dos2unix
	lowercase
	uppercase