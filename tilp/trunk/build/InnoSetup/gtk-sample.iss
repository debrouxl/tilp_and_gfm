; Sample script for using the GTK+ Runtime Environment
;
; Written by Todd Kulesza <todd@dropline.net>
;
; This script shows how to build an installer for the
; fictitous program "GTK Foo" by "Foo Software"
;

[Setup]
AppName=
AppVerName=GTK Foo 1.0.0
AppVersion=1.0.0
AppPublisher=Foo Software
AppPublisherURL=http://www.foo-software.com
AppCopyright=Copyright (C) 2003 Foo Software
AppSupportURL=http://www.foo-software.com
AppUpdatesURL=http://www.foo-software.com
DefaultDirName={pf}\GTK Foo
DefaultGroupName=GTK Foo
DisableStartupPrompt=yes
WindowShowCaption=yes
WindowVisible=no
; Make sure this file exists!
LicenseFile=license.txt
;BackColor=$FF8200
;BackColor=clPurple
;BackColor2=clBlack
Compression=bzip/9
SourceDir=.
OutputDir=.
OutputBaseFilename=GTK Foo 1.0.0
ChangesAssociations=no

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"

[Registry]
; This adds the GTK+ libraries to gtk-foo.exe's path
Root: HKLM; Subkey: "Software\Microsoft\Windows\CurrentVersion\App Paths\gtk-foo.exe"; Flags: uninsdeletekeyifempty
Root: HKLM; Subkey: "Software\Microsoft\Windows\CurrentVersion\App Paths\gtk-foo.exe"; ValueType: string; ValueData: "{app}\gtk-foo.exe"; Flags: uninsdeletevalue
Root: HKLM; Subkey: "Software\Microsoft\Windows\CurrentVersion\App Paths\gtk-foo.exe"; ValueType: string; ValueName: "Path"; ValueData: "{app};{code:GetGtkPath}\lib"; Flags: uninsdeletevalue

[Files]
Source: "gtk-foo.exe"; DestDir: "{app}"; DestName: "gtk-foo.exe"; CopyMode: normal

[Icons]
Name: "{group}\GTK Foo"; Filename: "{app}\gtk-foo.exe"; Comment: "Foo!";
Name: "{group}\GTK Foo Support Website"; Filename: "http://www.foo-software.com";
Name: "{group}\Uninstall GTK Foo"; Filename: "{uninstallexe}";
Name: "{userdesktop}\GTK Foo"; Filename: "{app}\gtk-foo.exe"; Tasks: desktopicon; Comment: "Desktop Foo!";

[Code]

var
  Exists: Boolean;
  GtkPath: String;

function GetGtkInstalled (): Boolean;
begin
  Exists := RegQueryStringValue (HKLM, 'Software\GTK\2.0', 'Path', GtkPath);
  if not Exists then begin
    Exists := RegQueryStringValue (HKCU, 'Software\GTK\2.0', 'Path', GtkPath);
  end;
   Result := Exists
end;

function GetGtkPath (S: String): String;
begin
    Result := GtkPath;
end;

function InitializeSetup(): Boolean;
begin
  Result := GetGtkInstalled ();
  if not Result then begin
    MsgBox ('Please install the GTK+ 2.0 Runtime Environment before installing GTK Foo.  You can obtain GTK+ from http://www.dropline.net/gtk.', mbError, MB_OK);
  end;
end;

