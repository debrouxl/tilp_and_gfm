# Microsoft Developer Studio Generated NMAKE File, Based on tilp_mfc.dsp
!IF "$(CFG)" == ""
CFG=tilp_mfc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tilp_mfc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tilp_mfc - Win32 Release" && "$(CFG)" != "tilp_mfc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tilp_mfc.mak" CFG="tilp_mfc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tilp_mfc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tilp_mfc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tilp_mfc - Win32 Release"

OUTDIR=.
INTDIR=C:\msvc\Output\tilp_mfc

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\..\..\Program Files\TiLP\tilp.exe" "..\..\..\..\..\..\msvc\Output\tilp_mfc\tilp_mfc.pch"

!ELSE 

ALL : "tifiles - Win32 Release" "ticalcs - Win32 Release" "ticables - Win32 Release" "..\..\..\..\..\..\Program Files\TiLP\tilp.exe" "..\..\..\..\..\..\msvc\Output\tilp_mfc\tilp_mfc.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 ReleaseCLEAN" "ticalcs - Win32 ReleaseCLEAN" "tifiles - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\bmp.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\cnv.obj"
	-@erase "$(INTDIR)\CommPg1.obj"
	-@erase "$(INTDIR)\CommPg2.obj"
	-@erase "$(INTDIR)\CommPg3.obj"
	-@erase "$(INTDIR)\CommSht.obj"
	-@erase "$(INTDIR)\CustomStatusBar.obj"
	-@erase "$(INTDIR)\DlgClock.obj"
	-@erase "$(INTDIR)\EntryDlg.obj"
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\HelpAbout.obj"
	-@erase "$(INTDIR)\HelpManpage.obj"
	-@erase "$(INTDIR)\ico.obj"
	-@erase "$(INTDIR)\jpg.obj"
	-@erase "$(INTDIR)\LeftDoc.obj"
	-@erase "$(INTDIR)\LeftView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\mfc_indep.obj"
	-@erase "$(INTDIR)\mfc_refresh.obj"
	-@erase "$(INTDIR)\MiscPg1.obj"
	-@erase "$(INTDIR)\MiscPg2.obj"
	-@erase "$(INTDIR)\MiscSht.obj"
	-@erase "$(INTDIR)\PbarDlg.obj"
	-@erase "$(INTDIR)\pcx.obj"
	-@erase "$(INTDIR)\PrgmsPg1.obj"
	-@erase "$(INTDIR)\PrgmsPg2.obj"
	-@erase "$(INTDIR)\PrgmsSht.obj"
	-@erase "$(INTDIR)\pwd.obj"
	-@erase "$(INTDIR)\RightView.obj"
	-@erase "$(INTDIR)\ScreenDlg.obj"
	-@erase "$(INTDIR)\ScreenPg1.obj"
	-@erase "$(INTDIR)\ScreenPg2.obj"
	-@erase "$(INTDIR)\ScreenSht.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TiLP.obj"
	-@erase "$(INTDIR)\TiLP.res"
	-@erase "$(INTDIR)\tilp_calcs.obj"
	-@erase "$(INTDIR)\tilp_error.obj"
	-@erase "$(INTDIR)\tilp_files.obj"
	-@erase "$(INTDIR)\tilp_indep.obj"
	-@erase "$(INTDIR)\tilp_main.obj"
	-@erase "$(INTDIR)\tilp_mfc.pch"
	-@erase "$(INTDIR)\tilp_misc.obj"
	-@erase "$(INTDIR)\tilp_paths.obj"
	-@erase "$(INTDIR)\tilp_prompt.obj"
	-@erase "$(INTDIR)\tilp_rcfile.obj"
	-@erase "$(INTDIR)\tilp_refresh.obj"
	-@erase "$(INTDIR)\tilp_screen.obj"
	-@erase "$(INTDIR)\tilp_slct.obj"
	-@erase "$(INTDIR)\tilp_vars.obj"
	-@erase "$(INTDIR)\unistd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VisualKB.obj"
	-@erase "$(INTDIR)\xpm.obj"
	-@erase "..\..\..\..\..\..\Program Files\TiLP\tilp.exe"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MT /w /W0 /GX /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "NDEBUG" /D "__WIN32__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\TiLP.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tilp_mfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=glib-1.3.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\tilp.pdb" /machine:I386 /out:"C:\Program Files\TiLP\tilp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CommPg1.obj" \
	"$(INTDIR)\CommPg2.obj" \
	"$(INTDIR)\CommPg3.obj" \
	"$(INTDIR)\CommSht.obj" \
	"$(INTDIR)\PrgmsPg1.obj" \
	"$(INTDIR)\PrgmsPg2.obj" \
	"$(INTDIR)\PrgmsSht.obj" \
	"$(INTDIR)\HelpAbout.obj" \
	"$(INTDIR)\HelpManpage.obj" \
	"$(INTDIR)\DlgClock.obj" \
	"$(INTDIR)\EntryDlg.obj" \
	"$(INTDIR)\PbarDlg.obj" \
	"$(INTDIR)\ScreenDlg.obj" \
	"$(INTDIR)\ScreenPg1.obj" \
	"$(INTDIR)\ScreenPg2.obj" \
	"$(INTDIR)\ScreenSht.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\LeftDoc.obj" \
	"$(INTDIR)\LeftView.obj" \
	"$(INTDIR)\RightView.obj" \
	"$(INTDIR)\MiscPg1.obj" \
	"$(INTDIR)\MiscPg2.obj" \
	"$(INTDIR)\MiscSht.obj" \
	"$(INTDIR)\mfc_indep.obj" \
	"$(INTDIR)\mfc_refresh.obj" \
	"$(INTDIR)\CustomStatusBar.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TiLP.obj" \
	"$(INTDIR)\VisualKB.obj" \
	"$(INTDIR)\tilp_calcs.obj" \
	"$(INTDIR)\tilp_error.obj" \
	"$(INTDIR)\tilp_files.obj" \
	"$(INTDIR)\tilp_indep.obj" \
	"$(INTDIR)\tilp_main.obj" \
	"$(INTDIR)\tilp_misc.obj" \
	"$(INTDIR)\tilp_paths.obj" \
	"$(INTDIR)\tilp_prompt.obj" \
	"$(INTDIR)\tilp_rcfile.obj" \
	"$(INTDIR)\tilp_refresh.obj" \
	"$(INTDIR)\tilp_screen.obj" \
	"$(INTDIR)\tilp_slct.obj" \
	"$(INTDIR)\tilp_vars.obj" \
	"$(INTDIR)\bmp.obj" \
	"$(INTDIR)\cnv.obj" \
	"$(INTDIR)\ico.obj" \
	"$(INTDIR)\jpg.obj" \
	"$(INTDIR)\pcx.obj" \
	"$(INTDIR)\xpm.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\pwd.obj" \
	"$(INTDIR)\unistd.obj" \
	"$(INTDIR)\TiLP.res" \
	"..\..\win32_libs\glib\glib-src-20001226\src\glib\glib_dynamic\glib-1.3.lib" \
	"..\..\..\..\ticables\build\msvc\ticables.lib" \
	"..\..\..\..\ticalcs\build\msvc\ticalcs.lib" \
	"..\..\..\..\tifiles\build\msvc\tifiles.lib"

"..\..\..\..\..\..\Program Files\TiLP\tilp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tilp_mfc - Win32 Debug"

OUTDIR=C:\msvc\tilp
INTDIR=C:\msvc\Output\tilp_mfc
# Begin Custom Macros
OutDir=C:\msvc\tilp\ 
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TiLP.exe" "..\..\..\..\..\..\msvc\Output\tilp_mfc\tilp_mfc.pch"

!ELSE 

ALL : "tifiles - Win32 Debug" "ticalcs - Win32 Debug" "ticables - Win32 Debug" "$(OUTDIR)\TiLP.exe" "..\..\..\..\..\..\msvc\Output\tilp_mfc\tilp_mfc.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 DebugCLEAN" "ticalcs - Win32 DebugCLEAN" "tifiles - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\bmp.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\cnv.obj"
	-@erase "$(INTDIR)\CommPg1.obj"
	-@erase "$(INTDIR)\CommPg2.obj"
	-@erase "$(INTDIR)\CommPg3.obj"
	-@erase "$(INTDIR)\CommSht.obj"
	-@erase "$(INTDIR)\CustomStatusBar.obj"
	-@erase "$(INTDIR)\DlgClock.obj"
	-@erase "$(INTDIR)\EntryDlg.obj"
	-@erase "$(INTDIR)\grp.obj"
	-@erase "$(INTDIR)\HelpAbout.obj"
	-@erase "$(INTDIR)\HelpManpage.obj"
	-@erase "$(INTDIR)\ico.obj"
	-@erase "$(INTDIR)\jpg.obj"
	-@erase "$(INTDIR)\LeftDoc.obj"
	-@erase "$(INTDIR)\LeftView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\mfc_indep.obj"
	-@erase "$(INTDIR)\mfc_refresh.obj"
	-@erase "$(INTDIR)\MiscPg1.obj"
	-@erase "$(INTDIR)\MiscPg2.obj"
	-@erase "$(INTDIR)\MiscSht.obj"
	-@erase "$(INTDIR)\PbarDlg.obj"
	-@erase "$(INTDIR)\pcx.obj"
	-@erase "$(INTDIR)\PrgmsPg1.obj"
	-@erase "$(INTDIR)\PrgmsPg2.obj"
	-@erase "$(INTDIR)\PrgmsSht.obj"
	-@erase "$(INTDIR)\pwd.obj"
	-@erase "$(INTDIR)\RightView.obj"
	-@erase "$(INTDIR)\ScreenDlg.obj"
	-@erase "$(INTDIR)\ScreenPg1.obj"
	-@erase "$(INTDIR)\ScreenPg2.obj"
	-@erase "$(INTDIR)\ScreenSht.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TiLP.obj"
	-@erase "$(INTDIR)\TiLP.res"
	-@erase "$(INTDIR)\tilp_calcs.obj"
	-@erase "$(INTDIR)\tilp_error.obj"
	-@erase "$(INTDIR)\tilp_files.obj"
	-@erase "$(INTDIR)\tilp_indep.obj"
	-@erase "$(INTDIR)\tilp_main.obj"
	-@erase "$(INTDIR)\tilp_mfc.pch"
	-@erase "$(INTDIR)\tilp_misc.obj"
	-@erase "$(INTDIR)\tilp_paths.obj"
	-@erase "$(INTDIR)\tilp_prompt.obj"
	-@erase "$(INTDIR)\tilp_rcfile.obj"
	-@erase "$(INTDIR)\tilp_refresh.obj"
	-@erase "$(INTDIR)\tilp_screen.obj"
	-@erase "$(INTDIR)\tilp_slct.obj"
	-@erase "$(INTDIR)\tilp_vars.obj"
	-@erase "$(INTDIR)\unistd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VisualKB.obj"
	-@erase "$(INTDIR)\xpm.obj"
	-@erase "$(OUTDIR)\TiLP.exe"
	-@erase "$(OUTDIR)\TiLP.ilk"
	-@erase "$(OUTDIR)\TiLP.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MTd /w /W0 /Gm /GX /ZI /Od /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "_DEBUG" /D "__WIN32__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\TiLP.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tilp_mfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\tilp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\tilp.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CommPg1.obj" \
	"$(INTDIR)\CommPg2.obj" \
	"$(INTDIR)\CommPg3.obj" \
	"$(INTDIR)\CommSht.obj" \
	"$(INTDIR)\PrgmsPg1.obj" \
	"$(INTDIR)\PrgmsPg2.obj" \
	"$(INTDIR)\PrgmsSht.obj" \
	"$(INTDIR)\HelpAbout.obj" \
	"$(INTDIR)\HelpManpage.obj" \
	"$(INTDIR)\DlgClock.obj" \
	"$(INTDIR)\EntryDlg.obj" \
	"$(INTDIR)\PbarDlg.obj" \
	"$(INTDIR)\ScreenDlg.obj" \
	"$(INTDIR)\ScreenPg1.obj" \
	"$(INTDIR)\ScreenPg2.obj" \
	"$(INTDIR)\ScreenSht.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\LeftDoc.obj" \
	"$(INTDIR)\LeftView.obj" \
	"$(INTDIR)\RightView.obj" \
	"$(INTDIR)\MiscPg1.obj" \
	"$(INTDIR)\MiscPg2.obj" \
	"$(INTDIR)\MiscSht.obj" \
	"$(INTDIR)\mfc_indep.obj" \
	"$(INTDIR)\mfc_refresh.obj" \
	"$(INTDIR)\CustomStatusBar.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TiLP.obj" \
	"$(INTDIR)\VisualKB.obj" \
	"$(INTDIR)\tilp_calcs.obj" \
	"$(INTDIR)\tilp_error.obj" \
	"$(INTDIR)\tilp_files.obj" \
	"$(INTDIR)\tilp_indep.obj" \
	"$(INTDIR)\tilp_main.obj" \
	"$(INTDIR)\tilp_misc.obj" \
	"$(INTDIR)\tilp_paths.obj" \
	"$(INTDIR)\tilp_prompt.obj" \
	"$(INTDIR)\tilp_rcfile.obj" \
	"$(INTDIR)\tilp_refresh.obj" \
	"$(INTDIR)\tilp_screen.obj" \
	"$(INTDIR)\tilp_slct.obj" \
	"$(INTDIR)\tilp_vars.obj" \
	"$(INTDIR)\bmp.obj" \
	"$(INTDIR)\cnv.obj" \
	"$(INTDIR)\ico.obj" \
	"$(INTDIR)\jpg.obj" \
	"$(INTDIR)\pcx.obj" \
	"$(INTDIR)\xpm.obj" \
	"$(INTDIR)\grp.obj" \
	"$(INTDIR)\pwd.obj" \
	"$(INTDIR)\unistd.obj" \
	"$(INTDIR)\TiLP.res" \
	"..\..\win32_libs\glib\glib-src-20001226\src\glib\glib_dynamic\glib-1.3.lib" \
	"$(OUTDIR)\ticables.lib" \
	"$(OUTDIR)\ticalcs.lib" \
	"$(OUTDIR)\tifiles.lib"

"$(OUTDIR)\TiLP.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("tilp_mfc.dep")
!INCLUDE "tilp_mfc.dep"
!ELSE 
!MESSAGE Warning: cannot find "tilp_mfc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tilp_mfc - Win32 Release" || "$(CFG)" == "tilp_mfc - Win32 Debug"
SOURCE=.\CommPg1.cpp

"$(INTDIR)\CommPg1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CommPg2.cpp

"$(INTDIR)\CommPg2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CommPg3.cpp

"$(INTDIR)\CommPg3.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CommSht.cpp

"$(INTDIR)\CommSht.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PrgmsPg1.cpp

"$(INTDIR)\PrgmsPg1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PrgmsPg2.cpp

"$(INTDIR)\PrgmsPg2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PrgmsSht.cpp

"$(INTDIR)\PrgmsSht.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HelpAbout.cpp

"$(INTDIR)\HelpAbout.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HelpManpage.cpp

"$(INTDIR)\HelpManpage.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DlgClock.cpp

"$(INTDIR)\DlgClock.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\EntryDlg.cpp

"$(INTDIR)\EntryDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PbarDlg.cpp

"$(INTDIR)\PbarDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ScreenDlg.cpp

"$(INTDIR)\ScreenDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ScreenPg1.cpp

"$(INTDIR)\ScreenPg1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ScreenPg2.cpp

"$(INTDIR)\ScreenPg2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ScreenSht.cpp

"$(INTDIR)\ScreenSht.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LeftDoc.cpp

"$(INTDIR)\LeftDoc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LeftView.cpp

"$(INTDIR)\LeftView.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RightView.cpp

"$(INTDIR)\RightView.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MiscPg1.cpp

"$(INTDIR)\MiscPg1.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MiscPg2.cpp

"$(INTDIR)\MiscPg2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MiscSht.cpp

"$(INTDIR)\MiscSht.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mfc_indep.cpp

"$(INTDIR)\mfc_indep.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mfc_refresh.cpp

"$(INTDIR)\mfc_refresh.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CustomStatusBar.cpp

"$(INTDIR)\CustomStatusBar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "tilp_mfc - Win32 Release"

CPP_SWITCHES=/nologo /MT /w /W0 /GX /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "NDEBUG" /D "__WIN32__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\tilp_mfc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\tilp_mfc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tilp_mfc - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /w /W0 /Gm /GX /ZI /Od /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "_DEBUG" /D "__WIN32__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\tilp_mfc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\tilp_mfc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TiLP.cpp

"$(INTDIR)\TiLP.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TiLP.rc

"$(INTDIR)\TiLP.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VisualKB.cpp

"$(INTDIR)\VisualKB.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\src\tilp_calcs.c

"$(INTDIR)\tilp_calcs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_error.c

"$(INTDIR)\tilp_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_files.c

"$(INTDIR)\tilp_files.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_indep.c

"$(INTDIR)\tilp_indep.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_main.c

"$(INTDIR)\tilp_main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_misc.c

"$(INTDIR)\tilp_misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_paths.c

"$(INTDIR)\tilp_paths.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_prompt.c

"$(INTDIR)\tilp_prompt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_rcfile.c

"$(INTDIR)\tilp_rcfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_refresh.c

"$(INTDIR)\tilp_refresh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_screen.c

"$(INTDIR)\tilp_screen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_slct.c

"$(INTDIR)\tilp_slct.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\tilp_vars.c

"$(INTDIR)\tilp_vars.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img\bmp.c

"$(INTDIR)\bmp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img\cnv.c

"$(INTDIR)\cnv.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img\ico.c

"$(INTDIR)\ico.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img\jpg.c

"$(INTDIR)\jpg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img\pcx.c

"$(INTDIR)\pcx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\img\xpm.c

"$(INTDIR)\xpm.obj" : $(SOURCE) "$(INTDIR)"
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


!IF  "$(CFG)" == "tilp_mfc - Win32 Release"

"ticables - Win32 Release" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" 
   cd "..\..\..\tilp\build\msvc\mfc"

"ticables - Win32 ReleaseCLEAN" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc\mfc"

!ELSEIF  "$(CFG)" == "tilp_mfc - Win32 Debug"

"ticables - Win32 Debug" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" 
   cd "..\..\..\tilp\build\msvc\mfc"

"ticables - Win32 DebugCLEAN" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc\mfc"

!ENDIF 

!IF  "$(CFG)" == "tilp_mfc - Win32 Release"

"ticalcs - Win32 Release" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" 
   cd "..\..\..\tilp\build\msvc\mfc"

"ticalcs - Win32 ReleaseCLEAN" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc\mfc"

!ELSEIF  "$(CFG)" == "tilp_mfc - Win32 Debug"

"ticalcs - Win32 Debug" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" 
   cd "..\..\..\tilp\build\msvc\mfc"

"ticalcs - Win32 DebugCLEAN" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc\mfc"

!ENDIF 

!IF  "$(CFG)" == "tilp_mfc - Win32 Release"

"tifiles - Win32 Release" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" 
   cd "..\..\..\tilp\build\msvc\mfc"

"tifiles - Win32 ReleaseCLEAN" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc\mfc"

!ELSEIF  "$(CFG)" == "tilp_mfc - Win32 Debug"

"tifiles - Win32 Debug" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" 
   cd "..\..\..\tilp\build\msvc\mfc"

"tifiles - Win32 DebugCLEAN" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc\mfc"

!ENDIF 


!ENDIF 

