# Microsoft Developer Studio Generated NMAKE File, Based on tilp_win32.dsp
!IF "$(CFG)" == ""
CFG=tilp_win32 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tilp_win32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tilp_win32 - Win32 Release" && "$(CFG)" != "tilp_win32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tilp_win32.mak" CFG="tilp_win32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tilp_win32 - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "tilp_win32 - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.\Release
INTDIR=.\Release

ALL : 


CLEAN :
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!IF  "$(CFG)" == "tilp_win32 - Win32 Release"

MTL=midl.exe
MTL_PROJ=

!ELSEIF  "$(CFG)" == "tilp_win32 - Win32 Debug"

MTL=midl.exe
MTL_PROJ=

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("tilp_win32.dep")
!INCLUDE "tilp_win32.dep"
!ELSE 
!MESSAGE Warning: cannot find "tilp_win32.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tilp_win32 - Win32 Release" || "$(CFG)" == "tilp_win32 - Win32 Debug"

!ENDIF 

