@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TILP.HPJ. >"hlp\TiLP.hm"
echo. >>"hlp\TiLP.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\TiLP.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\TiLP.hm"
echo. >>"hlp\TiLP.hm"
echo // Prompts (IDP_*) >>"hlp\TiLP.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\TiLP.hm"
echo. >>"hlp\TiLP.hm"
echo // Resources (IDR_*) >>"hlp\TiLP.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\TiLP.hm"
echo. >>"hlp\TiLP.hm"
echo // Dialogs (IDD_*) >>"hlp\TiLP.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\TiLP.hm"
echo. >>"hlp\TiLP.hm"
echo // Frame Controls (IDW_*) >>"hlp\TiLP.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\TiLP.hm"
REM -- Make help for Project TILP


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\TiLP.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\TiLP.hlp" goto :Error
if not exist "hlp\TiLP.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\TiLP.hlp" Debug
if exist Debug\nul copy "hlp\TiLP.cnt" Debug
if exist Release\nul copy "hlp\TiLP.hlp" Release
if exist Release\nul copy "hlp\TiLP.cnt" Release
echo.
goto :done

:Error
echo hlp\TiLP.hpj(1) : error: Problem encountered creating help file

:done
echo.
