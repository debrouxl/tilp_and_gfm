# Microsoft Developer Studio Project File - Name="tilp_gtk_win32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tilp_gtk_win32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tilp_gtk_win32.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tilp_gtk_win32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "C:\msvc\Output\tilp_gtk"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /w /W0 /GX /O2 /I "../../../ticables/src" /I "../../../tifiles/src" /I "../../../ticalcs/src" /I "../../src/win32" /I "C:\GTK2DEV\INCLUDE\GTK-2.0" /I "C:\GTK2DEV\LIB\GTK-2.0\INCLUDE" /I "C:\GTK2DEV\INCLUDE\GLIB-2.0" /I "C:\GTK2DEV\LIB\GLIB-2.0\INCLUDE" /I "C:\GTK2DEV\INCLUDE\PANGO-1.0" /I "C:\GTK2DEV\INCLUDE\ATK-1.0" /I "c:\gtk2dev\include" /I "C:\Gtk2Dev\include\libglade-2.0" /D "NDEBUG" /D "_WINDOWS" /D "__WIN32__" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"TiLP.exe"

!ELSEIF  "$(CFG)" == "tilp_gtk_win32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\msvc\tilp\"
# PROP Intermediate_Dir "C:\msvc\Output\tilp_gtk"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /w /W0 /Gm /GX /ZI /Od /I "../../../ticables/src" /I "../../../tifiles/src" /I "../../../ticalcs/src" /I "../../src/win32" /I "C:\GTK2DEV\INCLUDE\GTK-2.0" /I "C:\GTK2DEV\LIB\GTK-2.0\INCLUDE" /I "C:\GTK2DEV\INCLUDE\GLIB-2.0" /I "C:\GTK2DEV\LIB\GLIB-2.0\INCLUDE" /I "C:\GTK2DEV\INCLUDE\PANGO-1.0" /I "C:\GTK2DEV\INCLUDE\ATK-1.0" /I "c:\gtk2dev\include" /I "C:\Gtk2Dev\include\libglade-2.0" /D "_DEBUG" /D "_WINDOWS" /D "__WIN32__" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"C:\msvc\tilp\TiLP.exe" /pdbtype:sept /libpath:"C:\Gtk2Dev\Lib"

!ENDIF 

# Begin Target

# Name "tilp_gtk_win32 - Win32 Release"
# Name "tilp_gtk_win32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\about.c
# End Source File
# Begin Source File

SOURCE=..\..\src\action.c
# End Source File
# Begin Source File

SOURCE=..\..\src\clist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\clock.c
# End Source File
# Begin Source File

SOURCE=..\..\src\comm.c
# End Source File
# Begin Source File

SOURCE=..\..\src\ctree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\dboxes.c
# End Source File
# Begin Source File

SOURCE=..\..\src\dnd.c
# End Source File
# Begin Source File

SOURCE=..\..\src\extprgms.c
# End Source File
# Begin Source File

SOURCE=..\..\src\filesel.c
# End Source File
# Begin Source File

SOURCE=..\..\src\general.c
# End Source File
# Begin Source File

SOURCE=..\..\src\gtk_refresh.c
# End Source File
# Begin Source File

SOURCE=..\..\src\labels.c
# End Source File
# Begin Source File

SOURCE=..\..\src\logfile.c
# End Source File
# Begin Source File

SOURCE=..\..\src\main.c
# End Source File
# Begin Source File

SOURCE=..\..\src\manpage.c
# End Source File
# Begin Source File

SOURCE=..\..\src\pbars.c
# End Source File
# Begin Source File

SOURCE=..\..\src\popup.c
# End Source File
# Begin Source File

SOURCE=..\..\src\release.c
# End Source File
# Begin Source File

SOURCE=..\..\src\screenshot.c
# End Source File
# Begin Source File

SOURCE=..\..\src\scroptions.c
# End Source File
# Begin Source File

SOURCE=..\..\src\shell.c
# End Source File
# Begin Source File

SOURCE=..\..\src\splash.c
# End Source File
# Begin Source File

SOURCE=..\..\src\support.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\toolbar.c
# End Source File
# Begin Source File

SOURCE=..\..\src\wizard.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\about.h
# End Source File
# Begin Source File

SOURCE=..\..\src\action.h
# End Source File
# Begin Source File

SOURCE=..\..\src\clist.h
# End Source File
# Begin Source File

SOURCE=..\..\src\clock.h
# End Source File
# Begin Source File

SOURCE=..\..\src\comm.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ctree.h
# End Source File
# Begin Source File

SOURCE=..\..\src\dboxes.h
# End Source File
# Begin Source File

SOURCE=..\..\src\dnd.h
# End Source File
# Begin Source File

SOURCE=..\..\src\extprgms.h
# End Source File
# Begin Source File

SOURCE=..\..\src\filesel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\general.h
# End Source File
# Begin Source File

SOURCE=..\..\src\gstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\src\gtk_refresh.h
# End Source File
# Begin Source File

SOURCE=..\..\src\intl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\labels.h
# End Source File
# Begin Source File

SOURCE=..\..\src\logfile.h
# End Source File
# Begin Source File

SOURCE=..\..\src\manpage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\pbars.h
# End Source File
# Begin Source File

SOURCE=..\..\src\pbars_db.h
# End Source File
# Begin Source File

SOURCE=..\..\src\popup.h
# End Source File
# Begin Source File

SOURCE=..\..\src\release.h
# End Source File
# Begin Source File

SOURCE=..\..\src\screenshot.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scroptions.h
# End Source File
# Begin Source File

SOURCE=..\..\src\shell.h
# End Source File
# Begin Source File

SOURCE=..\..\src\splash.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilibs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_core.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_indep.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_paths.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_plugin.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_prompt.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_struct.h
# End Source File
# Begin Source File

SOURCE=..\..\src\toolbar.h
# End Source File
# Begin Source File

SOURCE=..\..\src\wizard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tilp.ico
# End Source File
# Begin Source File

SOURCE=.\Tilp.rc
# End Source File
# Begin Source File

SOURCE=.\tilp2.ico
# End Source File
# End Group
# Begin Group "TiLP core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\tilp_calcs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_error.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_files.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_indep.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_main.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_misc.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_paths.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_plugin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_printl.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_prompt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_rcfile.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_refresh.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_screen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_slct.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_vars.c
# End Source File
# End Group
# Begin Group "External Libraries"

# PROP Default_Filter "*.lib"
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\glib-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\gdk-win32-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\gtk-win32-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\gobject-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\gdk_pixbuf-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\gthread-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\gmodule-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\pango-1.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\libglade-2.0.lib"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Gtk2Dev\lib\atk-1.0.lib"
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\ChangeLog
# End Source File
# Begin Source File

SOURCE=..\..\src\tilp_version.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\Gtk2Dev\lib\intl.lib
# End Source File
# End Target
# End Project
