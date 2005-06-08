# Microsoft Developer Studio Project File - Name="tilp_mfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tilp_mfc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tilp_mfc.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tilp_mfc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "C:\msvc\Output\tilp_mfc"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "NDEBUG" /D "__WIN32__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 glib-1.3.lib /nologo /subsystem:windows /machine:I386 /out:"C:\Program Files\TiLP\tilp.exe"

!ELSEIF  "$(CFG)" == "tilp_mfc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\msvc\tilp\"
# PROP Intermediate_Dir "C:\msvc\Output\tilp_mfc"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /I "../../libs/files/src/" /I "../src" /I "../../libs/cables/src/" /I "../../libs/calcs/src/" /I "../dep/win32/" /I "../../../" /D "_DEBUG" /D "__WIN32__" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"C:\msvc\tilp\tilp.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "tilp_mfc - Win32 Release"
# Name "tilp_mfc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Comm Box"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CommPg1.cpp
# End Source File
# Begin Source File

SOURCE=.\CommPg2.cpp
# End Source File
# Begin Source File

SOURCE=.\CommPg3.cpp
# End Source File
# Begin Source File

SOURCE=.\CommSht.cpp
# End Source File
# End Group
# Begin Group "Prgms Box"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PrgmsPg1.cpp
# End Source File
# Begin Source File

SOURCE=.\PrgmsPg2.cpp
# End Source File
# Begin Source File

SOURCE=.\PrgmsSht.cpp
# End Source File
# End Group
# Begin Group "Help Box"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HelpAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpManpage.cpp
# End Source File
# End Group
# Begin Group "Misc Box"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgClock.cpp
# End Source File
# Begin Source File

SOURCE=.\EntryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PbarDlg.cpp
# End Source File
# End Group
# Begin Group "Screen Box"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ScreenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenPg1.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenPg2.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSht.cpp
# End Source File
# End Group
# Begin Group "Frames"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# End Group
# Begin Group "Views"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LeftDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\RightView.cpp
# End Source File
# End Group
# Begin Group "Main Box"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MiscPg1.cpp
# End Source File
# Begin Source File

SOURCE=.\MiscPg2.cpp
# End Source File
# Begin Source File

SOURCE=.\MiscSht.cpp
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mfc_indep.cpp
# End Source File
# Begin Source File

SOURCE=.\mfc_refresh.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CustomStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TiLP.cpp
# End Source File
# Begin Source File

SOURCE=.\TiLP.rc
# End Source File
# Begin Source File

SOURCE=.\VisualKB.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CommPg1.h
# End Source File
# Begin Source File

SOURCE=.\CommPg2.h
# End Source File
# Begin Source File

SOURCE=.\CommPg3.h
# End Source File
# Begin Source File

SOURCE=.\CommSht.h
# End Source File
# Begin Source File

SOURCE=.\DlgClock.h
# End Source File
# Begin Source File

SOURCE=.\EntryDlg.h
# End Source File
# Begin Source File

SOURCE=.\HelpAbout.h
# End Source File
# Begin Source File

SOURCE=.\HelpManpage.h
# End Source File
# Begin Source File

SOURCE=.\LeftDoc.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\ListDoc.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\mfc_indep.h
# End Source File
# Begin Source File

SOURCE=.\mfc_refresh.h
# End Source File
# Begin Source File

SOURCE=.\MfcRefresh.h
# End Source File
# Begin Source File

SOURCE=.\MiscPg1.h
# End Source File
# Begin Source File

SOURCE=.\MiscPg2.h
# End Source File
# Begin Source File

SOURCE=.\MiscSht.h
# End Source File
# Begin Source File

SOURCE=.\PbarDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrgmsPg1.h
# End Source File
# Begin Source File

SOURCE=.\PrgmsPg11.h
# End Source File
# Begin Source File

SOURCE=.\PrgmsPg2.h
# End Source File
# Begin Source File

SOURCE=.\PrgmsSht.h
# End Source File
# Begin Source File

SOURCE=.\ProbeIO.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RightView.h
# End Source File
# Begin Source File

SOURCE=.\ScreenDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScreenPg1.h
# End Source File
# Begin Source File

SOURCE=.\ScreenPg2.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSht.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TiLP.h
# End Source File
# Begin Source File

SOURCE=.\VisualKB.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Application.ico
# End Source File
# Begin Source File

SOURCE=.\res\Asm_Program.ico
# End Source File
# Begin Source File

SOURCE=.\res\Backup.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Certificate.ico
# End Source File
# Begin Source File

SOURCE=.\res\clist_di.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clist_do.bmp
# End Source File
# Begin Source File

SOURCE=.\res\clist_up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Complex.ico
# End Source File
# Begin Source File

SOURCE=.\res\Constant.ico
# End Source File
# Begin Source File

SOURCE=.\res\ctree_ar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctree_dc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctree_di.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctree_do.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctree_ke.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctree_lo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ctree_sc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Data.ico
# End Source File
# Begin Source File

SOURCE=.\res\dir.bmp
# End Source File
# Begin Source File

SOURCE=.\res\doc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dotdot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Drives.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Equation.ico
# End Source File
# Begin Source File

SOURCE=.\res\Expression.ico
# End Source File
# Begin Source File

SOURCE=.\res\Figure.ico
# End Source File
# Begin Source File

SOURCE=.\res\foldeR.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Function.ico
# End Source File
# Begin Source File

SOURCE=.\res\GDB.ico
# End Source File
# Begin Source File

SOURCE=.\res\Group.ico
# End Source File
# Begin Source File

SOURCE=.\res\Large.bmp
# End Source File
# Begin Source File

SOURCE=.\res\List.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Macro.ico
# End Source File
# Begin Source File

SOURCE=.\res\Matrix.ico
# End Source File
# Begin Source File

SOURCE=.\res\operatio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OS_upgrade.ico
# End Source File
# Begin Source File

SOURCE=.\res\Picture.ico
# End Source File
# Begin Source File

SOURCE=.\res\screensh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TiLP.ico
# End Source File
# Begin Source File

SOURCE=.\res\TiLPDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolb2r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolb2s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.bmp
# End Source File
# End Group
# Begin Group "TiLP Core"

# PROP Default_Filter ""
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\tilp_calcs.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_error.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_files.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_indep.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_main.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_misc.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_paths.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_prompt.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_rcfile.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_refresh.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_screen.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_slct.c
# End Source File
# Begin Source File

SOURCE=..\src\tilp_vars.c
# End Source File
# End Group
# Begin Group "img"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\img\bmp.c
# End Source File
# Begin Source File

SOURCE=..\src\img\cnv.c
# End Source File
# Begin Source File

SOURCE=..\src\img\ico.c
# End Source File
# Begin Source File

SOURCE=..\src\img\jpg.c
# End Source File
# Begin Source File

SOURCE=..\src\img\pcx.c
# End Source File
# Begin Source File

SOURCE=..\src\img\xpm.c
# End Source File
# End Group
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\win32\grp.c
# End Source File
# Begin Source File

SOURCE=..\src\win32\pwd.c
# End Source File
# Begin Source File

SOURCE=..\src\win32\unistd.c
# End Source File
# End Group
# Begin Group "headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\tilp_cb.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_dbox.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_defs.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_indep.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_paths.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_prompt.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_struct.h
# End Source File
# Begin Source File

SOURCE=..\src\tilp_version.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\ChangeLog
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\src\tilp_core.h
# End Source File
# Begin Source File

SOURCE="..\..\win32_libs\glib\glib-src-20001226\src\glib\glib_dynamic\glib-1.3.lib"
# End Source File
# End Target
# End Project
