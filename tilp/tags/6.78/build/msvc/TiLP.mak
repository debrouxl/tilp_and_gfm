# Microsoft Developer Studio Generated NMAKE File, Based on TiLP.dsp
!IF "$(CFG)" == ""
CFG=TiLP - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TiLP - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TiLP - Win32 Release" && "$(CFG)" != "TiLP - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TiLP.mak" CFG="TiLP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TiLP - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "TiLP - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.
INTDIR=C:\msvc\Output\TiLP

!IF "$(RECURSE)" == "0" 

ALL : 

!ELSE 

ALL : "tifiles - Win32 Release" "ticalcs - Win32 Release" "ticables - Win32 Release" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ticables - Win32 ReleaseCLEAN" "ticalcs - Win32 ReleaseCLEAN" "tifiles - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase 

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe

!IF  "$(CFG)" == "TiLP - Win32 Release"

!ELSEIF  "$(CFG)" == "TiLP - Win32 Debug"

!ENDIF 

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TiLP.dep")
!INCLUDE "TiLP.dep"
!ELSE 
!MESSAGE Warning: cannot find "TiLP.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TiLP - Win32 Release" || "$(CFG)" == "TiLP - Win32 Debug"

!IF  "$(CFG)" == "TiLP - Win32 Release"

"ticables - Win32 Release" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" 
   cd "..\..\..\tilp\build\msvc"

"ticables - Win32 ReleaseCLEAN" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc"

!ELSEIF  "$(CFG)" == "TiLP - Win32 Debug"

"ticables - Win32 Debug" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" 
   cd "..\..\..\tilp\build\msvc"

"ticables - Win32 DebugCLEAN" : 
   cd "\home\devel\ticables\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticables.mak CFG="ticables - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc"

!ENDIF 

!IF  "$(CFG)" == "TiLP - Win32 Release"

"ticalcs - Win32 Release" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" 
   cd "..\..\..\tilp\build\msvc"

"ticalcs - Win32 ReleaseCLEAN" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc"

!ELSEIF  "$(CFG)" == "TiLP - Win32 Debug"

"ticalcs - Win32 Debug" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" 
   cd "..\..\..\tilp\build\msvc"

"ticalcs - Win32 DebugCLEAN" : 
   cd "\home\devel\ticalcs\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\ticalcs.mak CFG="ticalcs - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc"

!ENDIF 

!IF  "$(CFG)" == "TiLP - Win32 Release"

"tifiles - Win32 Release" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" 
   cd "..\..\..\tilp\build\msvc"

"tifiles - Win32 ReleaseCLEAN" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc"

!ELSEIF  "$(CFG)" == "TiLP - Win32 Debug"

"tifiles - Win32 Debug" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" 
   cd "..\..\..\tilp\build\msvc"

"tifiles - Win32 DebugCLEAN" : 
   cd "\home\devel\tifiles\build\msvc"
   $(MAKE) /$(MAKEFLAGS) /F .\tifiles.mak CFG="tifiles - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\tilp\build\msvc"

!ENDIF 


!ENDIF 

