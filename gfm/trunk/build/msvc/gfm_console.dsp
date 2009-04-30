# Microsoft Developer Studio Project File - Name="gfm_console" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gfm_console - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gfm_console.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gfm_console.mak" CFG="gfm_console - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gfm_console - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gfm_console - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gfm_console - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "C:\lpg\msvc\Output\gfm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G3 /MD /w /W0 /GX /O2 /I "../../../ticonv/src" /I "../../../ticables2/src" /I "../../../tifiles2/src" /I "../../../ticalcs2/src" /I "../../src/win32" /I "C:\LPG\GTK\INCLUDE\GTK-2.0" /I "C:\LPG\GTK\LIB\GTK-2.0\INCLUDE" /I "C:\LPG\GTK\INCLUDE\GLIB-2.0" /I "C:\LPG\GTK\LIB\GLIB-2.0\INCLUDE" /I "C:\LPG\GTK\INCLUDE\PANGO-1.0" /I "C:\LPG\GTK\INCLUDE\ATK-1.0" /I "C:\LPG\GTK\include" /I "C:\LPG\GTK\include\libglade-2.0" /I "C:\LPG\GTK\include\cairo" /I "." /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "__WIN32__" /D "_MBCS" /D "ENABLE_NLS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib   /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib   /nologo /subsystem:console /machine:I386 /out:"gfm.exe"

!ELSEIF  "$(CFG)" == "gfm_console - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\lpg\msvc\gfm\"
# PROP Intermediate_Dir "C:\lpg\msvc\Output\gfm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "../../../ticonv/src" /I "../../../ticables2/src" /I "../../../tifiles2/src" /I "../../../ticalcs2/src" /I "../../src/win32" /I "C:\LPG\GTK\INCLUDE\GTK-2.0" /I "C:\LPG\GTK\LIB\GTK-2.0\INCLUDE" /I "C:\LPG\GTK\INCLUDE\GLIB-2.0" /I "C:\LPG\GTK\LIB\GLIB-2.0\INCLUDE" /I "C:\LPG\GTK\INCLUDE\PANGO-1.0" /I "C:\LPG\GTK\INCLUDE\ATK-1.0" /I "C:\LPG\GTK\include" /I "C:\LPG\GTK\include\libglade-2.0" /I "C:\LPG\GTK\include\cairo" /I "." /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "__WIN32__" /D "_MBCS" /D "ENABLE_NLS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib   /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib   /nologo /subsystem:console /debug /machine:I386 /out:"c:\lpg\msvc\gfm.exe" /pdbtype:sept /libpath:"C:\LPG\GTK\Lib"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "gfm_console - Win32 Release"
# Name "gfm_console - Win32 Debug"
# Begin Group "External Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE="C:\LPG\GTK\lib\glib-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\gdk-win32-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\gtk-win32-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\gobject-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\gdk_pixbuf-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\gthread-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\gmodule-2.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\pango-1.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\atk-1.0.lib"
# End Source File
# Begin Source File

SOURCE="C:\LPG\GTK\lib\glade-2.0.lib"
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\cmdline.c
# End Source File
# Begin Source File

SOURCE=..\..\src\ctree.c
# End Source File
# Begin Source File

SOURCE=..\..\src\dialog.c
# End Source File
# Begin Source File

SOURCE=..\..\src\file.c
# End Source File
# Begin Source File

SOURCE=..\..\src\filesel.c
# End Source File
# Begin Source File

SOURCE=..\..\src\gui.c
# End Source File
# Begin Source File

SOURCE=..\..\src\labels.c
# End Source File
# Begin Source File

SOURCE=..\..\src\main.c
# End Source File
# Begin Source File

SOURCE=..\..\src\paths.c
# End Source File
# Begin Source File

SOURCE=..\..\src\rwgroup.c
# End Source File
# Begin Source File

SOURCE=..\..\src\splashscreen.c
# End Source File
# Begin Source File

SOURCE=..\..\src\support.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tilibs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\ungroup.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\cmdline.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ctree.h
# End Source File
# Begin Source File

SOURCE=..\..\src\dialog.h
# End Source File
# Begin Source File

SOURCE=..\..\src\file.h
# End Source File
# Begin Source File

SOURCE=..\..\src\filesel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\gui.h
# End Source File
# Begin Source File

SOURCE=..\..\src\labels.h
# End Source File
# Begin Source File

SOURCE=..\..\src\paths.h
# End Source File
# Begin Source File

SOURCE=..\..\src\rwgroup.h
# End Source File
# Begin Source File

SOURCE=..\..\src\splashscreen.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tilibs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\ungroup.h
# End Source File
# Begin Source File

SOURCE=..\..\src\version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\mingw\gfm.ico
# End Source File
# Begin Source File

SOURCE=..\mingw\gfm.rc
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\ChangeLog
# End Source File
# Begin Source File

SOURCE=C:\LPG\GTK\lib\intl.lib
# End Source File
# End Target
# End Project
