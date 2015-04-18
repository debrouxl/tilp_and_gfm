iconsdir = $(pkgdatadir)/icons
icons_DATA = App_Var.ico Application.ico Asm_Program.ico Backup.ico Certificate.ico Complex.ico Complex_List.ico Complex_Matrix.ico Complex_Vector.ico Constant.ico Data.ico Diff_Equ.ico Equation.ico Expression.ico Figure.ico Function.ico GDB.ico Group.ico Group_Backup.ico Group_Var.ico List.ico Macro.ico Matrix.ico OS_upgrade.ico Parametric.ico Picture.ico Polar.ico Program.ico Range.ico Real.ico String.ico Table_Setup.ico test.ico Text.ico TiGroup.ico TIicon1.ico TIicon2.ico TIicon3.ico TIicon4.ico Unknown.ico up.ico Vector.ico Window_Setup.ico Y_Var.ico Zipped.ico Zoom.ico

EXTRA_DIST = App_Var.ico Application.ico Asm_Program.ico Backup.ico Certificate.ico Complex.ico Complex_List.ico Complex_Matrix.ico Complex_Vector.ico Constant.ico Data.ico Diff_Equ.ico Equation.ico Expression.ico Figure.ico Function.ico GDB.ico Group.ico Group_Backup.ico Group_Var.ico List.ico Macro.ico Matrix.ico OS_upgrade.ico Parametric.ico Picture.ico Polar.ico Program.ico Range.ico Real.ico String.ico Table_Setup.ico test.ico Text.ico TiGroup.ico TIicon1.ico TIicon2.ico TIicon3.ico TIicon4.ico Unknown.ico up.ico Vector.ico Window_Setup.ico Y_Var.ico Zipped.ico Zoom.ico

FN = `echo $$I | sed 's/\.ico$//'`

convert:
	@echo Converting icons to pixmaps
	@for I in App_Var.ico Application.ico Asm_Program.ico Backup.ico Certificate.ico Complex.ico Complex_List.ico Complex_Matrix.ico Complex_Vector.ico Constant.ico Data.ico Diff_Equ.ico Equation.ico Expression.ico Figure.ico Function.ico GDB.ico Group.ico Group_Backup.ico Group_Var.ico List.ico Macro.ico Matrix.ico OS_upgrade.ico Parametric.ico Picture.ico Polar.ico Program.ico Range.ico Real.ico String.ico Table_Setup.ico test.ico Text.ico TiGroup.ico TIicon1.ico TIicon2.ico TIicon3.ico TIicon4.ico Unknown.ico up.ico Vector.ico Window_Setup.ico Y_Var.ico Zipped.ico Zoom.ico ; do \
		echo $$I into $(FN).xpm; \
		winicontoppm $$I | ppmtoxpm  -name $(FN) > $(FN).xpm; \
	done
	@echo Done
