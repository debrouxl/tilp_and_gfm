# Microsoft Developer Studio Generated NMAKE File, Based on tilp_gtk_win32.dsp
!IF "$(CFG)" == ""
CFG=tilp_gtk_win32 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tilp_gtk_win32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tilp_gtk_win32 - Win32 Release" && "$(CFG)" != "tilp_gtk_win32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tilp_gtk_win32.mak" CFG="tilp_gtk_win32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tilp_gtk_win32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tilp_gtk_win32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "tilp_gtk_win32 - Win32 Release"

OUTDIR=.
INTDIR=C:\msvc\Output\tilp_gtk
# Begin Custom Macros
OutDir=.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tilp.exe"

!ELSE 

ALL : "tifiles - Win32 Release" "ticalcs - Win32 Release" "ticables - Win32 Release" "$(OUTDIR)\tilp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 ReleaseCLEAN" "ticalcs - Win32 ReleaseCLEAN" "tifiles - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\about_cb.obj"
	-@erase "$(INTDIR)\about_dbox.obj"
	-@erase "$(INTDIR)\advanced_cb.obj"
	-@erase "$(INTDIR)\advanced_dbox.obj"
	-@erase "$(INTDIR)\calc_cb.obj"
	-@erase "$(INTDIR)\calc_dbox.obj"
	-@erase "$(INTDIR)\cb_calc.obj"
	-@erase "$(INTDIR)\cb_misc.obj"
	-@erase "$(INTDIR)\cb_screen.obj"
	-@erase "$(INTDIR)\cl_indep.obj"
	-@erase "$(INTDIR)\cl_refresh.obj"
	-@erase "$(INTDIR)\clist.obj"
	-@erase "$(INTDIR)\clist_cb.obj"
	-@erase "$(INTDIR)\clist_rbm.obj"
	-@erase "$(INTDIR)\cmdinterface.obj"
	-@erase "$(INTDIR)\ctree.obj"
	-@erase "$(INTDIR)\entry_cb.obj"
	-@erase "$(INTDIR)\entry_dbox.obj"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\extprgms_cb.obj"
	-@erase "$(INTDIR)\extprgms_dbox.obj"
	-@erase "$(INTDIR)\files.obj"
	-@erase "$(INTDIR)\font_cb.obj"
	-@erase "$(INTDIR)\font_dbox.obj"
	-@erase "$(INTDIR)\fsel_cb.obj"
	-@erase "$(INTDIR)\fsel_dbox.obj"
	-@erase "$(INTDIR)\general_cb.obj"
	-@erase "$(INTDIR)\general_dbox.obj"
	-@erase "$(INTDIR)\gfm_cb.obj"
	-@erase "$(INTDIR)\gfm_dbox.obj"
	-@erase "$(INTDIR)\ginfo.obj"
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\gselect.obj"
	-@erase "$(INTDIR)\gui_indep.obj"
	-@erase "$(INTDIR)\gxpm.obj"
	-@erase "$(INTDIR)\help_cb.obj"
	-@erase "$(INTDIR)\help_dbox.obj"
	-@erase "$(INTDIR)\idle_cb.obj"
	-@erase "$(INTDIR)\img_cnv.obj"
	-@erase "$(INTDIR)\img_jpg.obj"
	-@erase "$(INTDIR)\img_pcx.obj"
	-@erase "$(INTDIR)\img_xpm.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\lang_cb.obj"
	-@erase "$(INTDIR)\lang_dbox.obj"
	-@erase "$(INTDIR)\link_cb.obj"
	-@erase "$(INTDIR)\link_dbox.obj"
	-@erase "$(INTDIR)\linkspeed_cb.obj"
	-@erase "$(INTDIR)\linkspeed_dbox.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\manpage_cb.obj"
	-@erase "$(INTDIR)\manpage_dbox.obj"
	-@erase "$(INTDIR)\msg_cb.obj"
	-@erase "$(INTDIR)\msg_dbox.obj"
	-@erase "$(INTDIR)\pbar_cb.obj"
	-@erase "$(INTDIR)\pbar_dbox.obj"
	-@erase "$(INTDIR)\plugins_cb.obj"
	-@erase "$(INTDIR)\plugins_dbox.obj"
	-@erase "$(INTDIR)\probeio_cb.obj"
	-@erase "$(INTDIR)\probeio_dbox.obj"
	-@erase "$(INTDIR)\pwd.obj"
	-@erase "$(INTDIR)\rcfile.obj"
	-@erase "$(INTDIR)\refresh.obj"
	-@erase "$(INTDIR)\scopt_cb.obj"
	-@erase "$(INTDIR)\scopt_dbox.obj"
	-@erase "$(INTDIR)\screendump_cb.obj"
	-@erase "$(INTDIR)\screendump_dbox.obj"
	-@erase "$(INTDIR)\shell_cb.obj"
	-@erase "$(INTDIR)\shell_dbox.obj"
	-@erase "$(INTDIR)\startup_cb.obj"
	-@erase "$(INTDIR)\startup_dbox.obj"
	-@erase "$(INTDIR)\sub_main.obj"
	-@erase "$(INTDIR)\support.obj"
	-@erase "$(INTDIR)\term_cb.obj"
	-@erase "$(INTDIR)\term_dbox.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\thanks_cb.obj"
	-@erase "$(INTDIR)\thanks_dbox.obj"
	-@erase "$(INTDIR)\tifileinfo_cb.obj"
	-@erase "$(INTDIR)\tifileinfo_dbox.obj"
	-@erase "$(INTDIR)\tilp.res"
	-@erase "$(INTDIR)\tilp_cb.obj"
	-@erase "$(INTDIR)\tilp_dbox.obj"
	-@erase "$(INTDIR)\toolbar.obj"
	-@erase "$(INTDIR)\unistd.obj"
	-@erase "$(INTDIR)\user_cb.obj"
	-@erase "$(INTDIR)\user_dbox.obj"
	-@erase "$(INTDIR)\vars.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wizard_cb.obj"
	-@erase "$(INTDIR)\wizard_dbox.obj"
	-@erase "$(OUTDIR)\tilp.exe"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /w /W0 /GX /O2 /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "NDEBUG" /D "_WINDOWS" /D "__WIN32__" /D "_MBCS" /D "WIN32" /D "HAVE_LIBINTL_H" /D "ENABLE_NLS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\Tilp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tilp_gtk_win32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gnu-intl.lib gmodule-1.3.lib glib-1.3.lib gdk-1.3.lib gtk-1.3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\tilp.pdb" /machine:I386 /out:"$(OUTDIR)\tilp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cb_calc.obj" \
	"$(INTDIR)\cb_misc.obj" \
	"$(INTDIR)\cb_screen.obj" \
	"$(INTDIR)\cl_indep.obj" \
	"$(INTDIR)\cl_refresh.obj" \
	"$(INTDIR)\cmdinterface.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\files.obj" \
	"$(INTDIR)\gui_indep.obj" \
	"$(INTDIR)\img_cnv.obj" \
	"$(INTDIR)\img_jpg.obj" \
	"$(INTDIR)\img_pcx.obj" \
	"$(INTDIR)\img_xpm.obj" \
	"$(INTDIR)\info.obj" \
	"$(INTDIR)\rcfile.obj" \
	"$(INTDIR)\sub_main.obj" \
	"$(INTDIR)\vars.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\pwd.obj" \
	"$(INTDIR)\unistd.obj" \
	"$(INTDIR)\about_cb.obj" \
	"$(INTDIR)\about_dbox.obj" \
	"$(INTDIR)\advanced_cb.obj" \
	"$(INTDIR)\advanced_dbox.obj" \
	"$(INTDIR)\calc_cb.obj" \
	"$(INTDIR)\calc_dbox.obj" \
	"$(INTDIR)\clist.obj" \
	"$(INTDIR)\clist_cb.obj" \
	"$(INTDIR)\clist_rbm.obj" \
	"$(INTDIR)\ctree.obj" \
	"$(INTDIR)\entry_cb.obj" \
	"$(INTDIR)\entry_dbox.obj" \
	"$(INTDIR)\extprgms_cb.obj" \
	"$(INTDIR)\extprgms_dbox.obj" \
	"$(INTDIR)\font_cb.obj" \
	"$(INTDIR)\font_dbox.obj" \
	"$(INTDIR)\fsel_cb.obj" \
	"$(INTDIR)\fsel_dbox.obj" \
	"$(INTDIR)\general_cb.obj" \
	"$(INTDIR)\general_dbox.obj" \
	"$(INTDIR)\gfm_cb.obj" \
	"$(INTDIR)\gfm_dbox.obj" \
	"$(INTDIR)\ginfo.obj" \
	"$(INTDIR)\gselect.obj" \
	"$(INTDIR)\gxpm.obj" \
	"$(INTDIR)\help_cb.obj" \
	"$(INTDIR)\help_dbox.obj" \
	"$(INTDIR)\idle_cb.obj" \
	"$(INTDIR)\lang_cb.obj" \
	"$(INTDIR)\lang_dbox.obj" \
	"$(INTDIR)\link_cb.obj" \
	"$(INTDIR)\link_dbox.obj" \
	"$(INTDIR)\linkspeed_cb.obj" \
	"$(INTDIR)\linkspeed_dbox.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\manpage_cb.obj" \
	"$(INTDIR)\manpage_dbox.obj" \
	"$(INTDIR)\msg_cb.obj" \
	"$(INTDIR)\msg_dbox.obj" \
	"$(INTDIR)\pbar_cb.obj" \
	"$(INTDIR)\pbar_dbox.obj" \
	"$(INTDIR)\plugins_cb.obj" \
	"$(INTDIR)\plugins_dbox.obj" \
	"$(INTDIR)\probeio_cb.obj" \
	"$(INTDIR)\probeio_dbox.obj" \
	"$(INTDIR)\refresh.obj" \
	"$(INTDIR)\scopt_cb.obj" \
	"$(INTDIR)\scopt_dbox.obj" \
	"$(INTDIR)\screendump_cb.obj" \
	"$(INTDIR)\screendump_dbox.obj" \
	"$(INTDIR)\shell_cb.obj" \
	"$(INTDIR)\shell_dbox.obj" \
	"$(INTDIR)\startup_cb.obj" \
	"$(INTDIR)\startup_dbox.obj" \
	"$(INTDIR)\support.obj" \
	"$(INTDIR)\term_cb.obj" \
	"$(INTDIR)\term_dbox.obj" \
	"$(INTDIR)\test.obj" \
	"$(INTDIR)\thanks_cb.obj" \
	"$(INTDIR)\thanks_dbox.obj" \
	"$(INTDIR)\tifileinfo_cb.obj" \
	"$(INTDIR)\tifileinfo_dbox.obj" \
	"$(INTDIR)\tilp_cb.obj" \
	"$(INTDIR)\tilp_dbox.obj" \
	"$(INTDIR)\toolbar.obj" \
	"$(INTDIR)\user_cb.obj" \
	"$(INTDIR)\user_dbox.obj" \
	"$(INTDIR)\wizard_cb.obj" \
	"$(INTDIR)\wizard_dbox.obj" \
	"$(INTDIR)\tilp.res" \
	"..\..\..\libs\cables\win32\msvc\ticables.lib" \
	"..\..\..\libs\calcs\win32\msvc\ticalcs.lib" \
	"..\..\..\libs\files\win32\msvc\tifiles.lib"

"$(OUTDIR)\tilp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tilp_gtk_win32 - Win32 Debug"

OUTDIR=C:\msvc\tilp
INTDIR=C:\msvc\Output\tilp_gtk
# Begin Custom Macros
OutDir=C:\msvc\tilp\ 
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tilp.exe"

!ELSE 

ALL : "tifiles - Win32 Debug" "ticalcs - Win32 Debug" "ticables - Win32 Debug" "$(OUTDIR)\tilp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 DebugCLEAN" "ticalcs - Win32 DebugCLEAN" "tifiles - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\about_cb.obj"
	-@erase "$(INTDIR)\about_dbox.obj"
	-@erase "$(INTDIR)\advanced_cb.obj"
	-@erase "$(INTDIR)\advanced_dbox.obj"
	-@erase "$(INTDIR)\calc_cb.obj"
	-@erase "$(INTDIR)\calc_dbox.obj"
	-@erase "$(INTDIR)\cb_calc.obj"
	-@erase "$(INTDIR)\cb_misc.obj"
	-@erase "$(INTDIR)\cb_screen.obj"
	-@erase "$(INTDIR)\cl_indep.obj"
	-@erase "$(INTDIR)\cl_refresh.obj"
	-@erase "$(INTDIR)\clist.obj"
	-@erase "$(INTDIR)\clist_cb.obj"
	-@erase "$(INTDIR)\clist_rbm.obj"
	-@erase "$(INTDIR)\cmdinterface.obj"
	-@erase "$(INTDIR)\ctree.obj"
	-@erase "$(INTDIR)\entry_cb.obj"
	-@erase "$(INTDIR)\entry_dbox.obj"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\extprgms_cb.obj"
	-@erase "$(INTDIR)\extprgms_dbox.obj"
	-@erase "$(INTDIR)\files.obj"
	-@erase "$(INTDIR)\font_cb.obj"
	-@erase "$(INTDIR)\font_dbox.obj"
	-@erase "$(INTDIR)\fsel_cb.obj"
	-@erase "$(INTDIR)\fsel_dbox.obj"
	-@erase "$(INTDIR)\general_cb.obj"
	-@erase "$(INTDIR)\general_dbox.obj"
	-@erase "$(INTDIR)\gfm_cb.obj"
	-@erase "$(INTDIR)\gfm_dbox.obj"
	-@erase "$(INTDIR)\ginfo.obj"
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\gselect.obj"
	-@erase "$(INTDIR)\gui_indep.obj"
	-@erase "$(INTDIR)\gxpm.obj"
	-@erase "$(INTDIR)\help_cb.obj"
	-@erase "$(INTDIR)\help_dbox.obj"
	-@erase "$(INTDIR)\idle_cb.obj"
	-@erase "$(INTDIR)\img_cnv.obj"
	-@erase "$(INTDIR)\img_jpg.obj"
	-@erase "$(INTDIR)\img_pcx.obj"
	-@erase "$(INTDIR)\img_xpm.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\lang_cb.obj"
	-@erase "$(INTDIR)\lang_dbox.obj"
	-@erase "$(INTDIR)\link_cb.obj"
	-@erase "$(INTDIR)\link_dbox.obj"
	-@erase "$(INTDIR)\linkspeed_cb.obj"
	-@erase "$(INTDIR)\linkspeed_dbox.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\manpage_cb.obj"
	-@erase "$(INTDIR)\manpage_dbox.obj"
	-@erase "$(INTDIR)\msg_cb.obj"
	-@erase "$(INTDIR)\msg_dbox.obj"
	-@erase "$(INTDIR)\pbar_cb.obj"
	-@erase "$(INTDIR)\pbar_dbox.obj"
	-@erase "$(INTDIR)\plugins_cb.obj"
	-@erase "$(INTDIR)\plugins_dbox.obj"
	-@erase "$(INTDIR)\probeio_cb.obj"
	-@erase "$(INTDIR)\probeio_dbox.obj"
	-@erase "$(INTDIR)\pwd.obj"
	-@erase "$(INTDIR)\rcfile.obj"
	-@erase "$(INTDIR)\refresh.obj"
	-@erase "$(INTDIR)\scopt_cb.obj"
	-@erase "$(INTDIR)\scopt_dbox.obj"
	-@erase "$(INTDIR)\screendump_cb.obj"
	-@erase "$(INTDIR)\screendump_dbox.obj"
	-@erase "$(INTDIR)\shell_cb.obj"
	-@erase "$(INTDIR)\shell_dbox.obj"
	-@erase "$(INTDIR)\startup_cb.obj"
	-@erase "$(INTDIR)\startup_dbox.obj"
	-@erase "$(INTDIR)\sub_main.obj"
	-@erase "$(INTDIR)\support.obj"
	-@erase "$(INTDIR)\term_cb.obj"
	-@erase "$(INTDIR)\term_dbox.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\thanks_cb.obj"
	-@erase "$(INTDIR)\thanks_dbox.obj"
	-@erase "$(INTDIR)\tifileinfo_cb.obj"
	-@erase "$(INTDIR)\tifileinfo_dbox.obj"
	-@erase "$(INTDIR)\tilp.res"
	-@erase "$(INTDIR)\tilp_cb.obj"
	-@erase "$(INTDIR)\tilp_dbox.obj"
	-@erase "$(INTDIR)\toolbar.obj"
	-@erase "$(INTDIR)\unistd.obj"
	-@erase "$(INTDIR)\user_cb.obj"
	-@erase "$(INTDIR)\user_dbox.obj"
	-@erase "$(INTDIR)\vars.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wizard_cb.obj"
	-@erase "$(INTDIR)\wizard_dbox.obj"
	-@erase "$(OUTDIR)\tilp.exe"
	-@erase "$(OUTDIR)\tilp.ilk"
	-@erase "$(OUTDIR)\tilp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /w /W0 /Gm /GX /ZI /Od /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "GTK" /D "_DEBUG" /D "_WINDOWS" /D "__WIN32__" /D "_MBCS" /D "WIN32" /D "HAVE_LIBINTL_H" /D "ENABLE_NLS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\Tilp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tilp_gtk_win32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gnu-intl.lib glib-1.3.lib gdk-1.3.lib gtk-1.3.lib gmodule-1.3.lib gthread-1.3.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\TiLP.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TiLP.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cb_calc.obj" \
	"$(INTDIR)\cb_misc.obj" \
	"$(INTDIR)\cb_screen.obj" \
	"$(INTDIR)\cl_indep.obj" \
	"$(INTDIR)\cl_refresh.obj" \
	"$(INTDIR)\cmdinterface.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\files.obj" \
	"$(INTDIR)\gui_indep.obj" \
	"$(INTDIR)\img_cnv.obj" \
	"$(INTDIR)\img_jpg.obj" \
	"$(INTDIR)\img_pcx.obj" \
	"$(INTDIR)\img_xpm.obj" \
	"$(INTDIR)\info.obj" \
	"$(INTDIR)\rcfile.obj" \
	"$(INTDIR)\sub_main.obj" \
	"$(INTDIR)\vars.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\pwd.obj" \
	"$(INTDIR)\unistd.obj" \
	"$(INTDIR)\about_cb.obj" \
	"$(INTDIR)\about_dbox.obj" \
	"$(INTDIR)\advanced_cb.obj" \
	"$(INTDIR)\advanced_dbox.obj" \
	"$(INTDIR)\calc_cb.obj" \
	"$(INTDIR)\calc_dbox.obj" \
	"$(INTDIR)\clist.obj" \
	"$(INTDIR)\clist_cb.obj" \
	"$(INTDIR)\clist_rbm.obj" \
	"$(INTDIR)\ctree.obj" \
	"$(INTDIR)\entry_cb.obj" \
	"$(INTDIR)\entry_dbox.obj" \
	"$(INTDIR)\extprgms_cb.obj" \
	"$(INTDIR)\extprgms_dbox.obj" \
	"$(INTDIR)\font_cb.obj" \
	"$(INTDIR)\font_dbox.obj" \
	"$(INTDIR)\fsel_cb.obj" \
	"$(INTDIR)\fsel_dbox.obj" \
	"$(INTDIR)\general_cb.obj" \
	"$(INTDIR)\general_dbox.obj" \
	"$(INTDIR)\gfm_cb.obj" \
	"$(INTDIR)\gfm_dbox.obj" \
	"$(INTDIR)\ginfo.obj" \
	"$(INTDIR)\gselect.obj" \
	"$(INTDIR)\gxpm.obj" \
	"$(INTDIR)\help_cb.obj" \
	"$(INTDIR)\help_dbox.obj" \
	"$(INTDIR)\idle_cb.obj" \
	"$(INTDIR)\lang_cb.obj" \
	"$(INTDIR)\lang_dbox.obj" \
	"$(INTDIR)\link_cb.obj" \
	"$(INTDIR)\link_dbox.obj" \
	"$(INTDIR)\linkspeed_cb.obj" \
	"$(INTDIR)\linkspeed_dbox.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\manpage_cb.obj" \
	"$(INTDIR)\manpage_dbox.obj" \
	"$(INTDIR)\msg_cb.obj" \
	"$(INTDIR)\msg_dbox.obj" \
	"$(INTDIR)\pbar_cb.obj" \
	"$(INTDIR)\pbar_dbox.obj" \
	"$(INTDIR)\plugins_cb.obj" \
	"$(INTDIR)\plugins_dbox.obj" \
	"$(INTDIR)\probeio_cb.obj" \
	"$(INTDIR)\probeio_dbox.obj" \
	"$(INTDIR)\refresh.obj" \
	"$(INTDIR)\scopt_cb.obj" \
	"$(INTDIR)\scopt_dbox.obj" \
	"$(INTDIR)\screendump_cb.obj" \
	"$(INTDIR)\screendump_dbox.obj" \
	"$(INTDIR)\shell_cb.obj" \
	"$(INTDIR)\shell_dbox.obj" \
	"$(INTDIR)\startup_cb.obj" \
	"$(INTDIR)\startup_dbox.obj" \
	"$(INTDIR)\support.obj" \
	"$(INTDIR)\term_cb.obj" \
	"$(INTDIR)\term_dbox.obj" \
	"$(INTDIR)\test.obj" \
	"$(INTDIR)\thanks_cb.obj" \
	"$(INTDIR)\thanks_dbox.obj" \
	"$(INTDIR)\tifileinfo_cb.obj" \
	"$(INTDIR)\tifileinfo_dbox.obj" \
	"$(INTDIR)\tilp_cb.obj" \
	"$(INTDIR)\tilp_dbox.obj" \
	"$(INTDIR)\toolbar.obj" \
	"$(INTDIR)\user_cb.obj" \
	"$(INTDIR)\user_dbox.obj" \
	"$(INTDIR)\wizard_cb.obj" \
	"$(INTDIR)\wizard_dbox.obj" \
	"$(INTDIR)\tilp.res" \
	"$(OUTDIR)\ticables.lib" \
	"$(OUTDIR)\ticalcs.lib" \
	"$(OUTDIR)\tifiles.lib"

"$(OUTDIR)\tilp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("tilp_gtk_win32.dep")
!INCLUDE "tilp_gtk_win32.dep"
!ELSE 
!MESSAGE Warning: cannot find "tilp_gtk_win32.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tilp_gtk_win32 - Win32 Release" || "$(CFG)" == "tilp_gtk_win32 - Win32 Debug"
SOURCE=..\src\cb_calc.c

"$(INTDIR)\cb_calc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\cb_misc.c

"$(INTDIR)\cb_misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\cb_screen.c

"$(INTDIR)\cb_screen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\cl_indep.c

"$(INTDIR)\cl_indep.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\cl_refresh.c

"$(INTDIR)\cl_refresh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\cmdinterface.c

"$(INTDIR)\cmdinterface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\error.c

"$(INTDIR)\error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\files.c

"$(INTDIR)\files.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\gui_indep.c

"$(INTDIR)\gui_indep.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img_cnv.c

"$(INTDIR)\img_cnv.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img_jpg.c

"$(INTDIR)\img_jpg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img_pcx.c

"$(INTDIR)\img_pcx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img_xpm.c

"$(INTDIR)\img_xpm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\info.c

"$(INTDIR)\info.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\rcfile.c

"$(INTDIR)\rcfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sub_main.c

"$(INTDIR)\sub_main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\vars.c

"$(INTDIR)\vars.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\win32\grp.c

"$(INTDIR)\grp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\win32\pwd.c

"$(INTDIR)\pwd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\win32\unistd.c

"$(INTDIR)\unistd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\about_cb.c

"$(INTDIR)\about_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\about_dbox.c

"$(INTDIR)\about_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\advanced_cb.c

"$(INTDIR)\advanced_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\advanced_dbox.c

"$(INTDIR)\advanced_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\calc_cb.c

"$(INTDIR)\calc_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\calc_dbox.c

"$(INTDIR)\calc_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\clist.c

"$(INTDIR)\clist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\clist_cb.c

"$(INTDIR)\clist_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\clist_rbm.c

"$(INTDIR)\clist_rbm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\ctree.c

"$(INTDIR)\ctree.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\entry_cb.c

"$(INTDIR)\entry_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\entry_dbox.c

"$(INTDIR)\entry_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\extprgms_cb.c

"$(INTDIR)\extprgms_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\extprgms_dbox.c

"$(INTDIR)\extprgms_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\font_cb.c

"$(INTDIR)\font_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\font_dbox.c

"$(INTDIR)\font_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\fsel_cb.c

"$(INTDIR)\fsel_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\fsel_dbox.c

"$(INTDIR)\fsel_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\general_cb.c

"$(INTDIR)\general_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\general_dbox.c

"$(INTDIR)\general_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\gfm_cb.c

"$(INTDIR)\gfm_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\gfm_dbox.c

"$(INTDIR)\gfm_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\ginfo.c

"$(INTDIR)\ginfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\gselect.c

"$(INTDIR)\gselect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\gxpm.c

"$(INTDIR)\gxpm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\help_cb.c

"$(INTDIR)\help_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\help_dbox.c

"$(INTDIR)\help_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\idle_cb.c

"$(INTDIR)\idle_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\info.c

"$(INTDIR)\info.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\lang_cb.c

"$(INTDIR)\lang_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\lang_dbox.c

"$(INTDIR)\lang_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\link_cb.c

"$(INTDIR)\link_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\link_dbox.c

"$(INTDIR)\link_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\linkspeed_cb.c

"$(INTDIR)\linkspeed_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\linkspeed_dbox.c

"$(INTDIR)\linkspeed_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\main.c

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\manpage_cb.c

"$(INTDIR)\manpage_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\manpage_dbox.c

"$(INTDIR)\manpage_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\msg_cb.c

"$(INTDIR)\msg_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\msg_dbox.c

"$(INTDIR)\msg_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\pbar_cb.c

"$(INTDIR)\pbar_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\pbar_dbox.c

"$(INTDIR)\pbar_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\plugins_cb.c

"$(INTDIR)\plugins_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\plugins_dbox.c

"$(INTDIR)\plugins_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\probeio_cb.c

"$(INTDIR)\probeio_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\probeio_dbox.c

"$(INTDIR)\probeio_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\refresh.c

"$(INTDIR)\refresh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\scopt_cb.c

"$(INTDIR)\scopt_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\scopt_dbox.c

"$(INTDIR)\scopt_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\screendump_cb.c

"$(INTDIR)\screendump_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\screendump_dbox.c

"$(INTDIR)\screendump_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\shell_cb.c

"$(INTDIR)\shell_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\shell_dbox.c

"$(INTDIR)\shell_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\startup_cb.c

"$(INTDIR)\startup_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\startup_dbox.c

"$(INTDIR)\startup_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\support.c

"$(INTDIR)\support.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\term_cb.c

"$(INTDIR)\term_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\term_dbox.c

"$(INTDIR)\term_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\test.c

"$(INTDIR)\test.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\thanks_cb.c

"$(INTDIR)\thanks_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\thanks_dbox.c

"$(INTDIR)\thanks_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\tifileinfo_cb.c

"$(INTDIR)\tifileinfo_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\tifileinfo_dbox.c

"$(INTDIR)\tifileinfo_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\tilp_cb.c

"$(INTDIR)\tilp_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\tilp_dbox.c

"$(INTDIR)\tilp_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\toolbar.c

"$(INTDIR)\toolbar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\user_cb.c

"$(INTDIR)\user_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\user_dbox.c

"$(INTDIR)\user_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\wizard_cb.c

"$(INTDIR)\wizard_cb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\gtk\wizard_dbox.c

"$(INTDIR)\wizard_dbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "tilp_gtk_win32 - Win32 Release"

"ticables - Win32 Release" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticables - Win32 ReleaseCLEAN" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ELSEIF  "$(CFG)" == "tilp_gtk_win32 - Win32 Debug"

"ticables - Win32 Debug" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticables - Win32 DebugCLEAN" : 
   cd "\devel\tilp_project\libs\cables\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ENDIF 

!IF  "$(CFG)" == "tilp_gtk_win32 - Win32 Release"

"ticalcs - Win32 Release" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticalcs - Win32 ReleaseCLEAN" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ELSEIF  "$(CFG)" == "tilp_gtk_win32 - Win32 Debug"

"ticalcs - Win32 Debug" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" 
   cd "..\..\..\..\tilp\win32\msvc"

"ticalcs - Win32 DebugCLEAN" : 
   cd "\devel\tilp_project\libs\calcs\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ENDIF 

!IF  "$(CFG)" == "tilp_gtk_win32 - Win32 Release"

"tifiles - Win32 Release" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" 
   cd "..\..\..\..\tilp\win32\msvc"

"tifiles - Win32 ReleaseCLEAN" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ELSEIF  "$(CFG)" == "tilp_gtk_win32 - Win32 Debug"

"tifiles - Win32 Debug" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" 
   cd "..\..\..\..\tilp\win32\msvc"

"tifiles - Win32 DebugCLEAN" : 
   cd "\devel\tilp_project\libs\files\win32\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\..\tilp\win32\msvc"

!ENDIF 

SOURCE=.\Tilp.rc

"$(INTDIR)\tilp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

