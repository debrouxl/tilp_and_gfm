Compiling LPG Software with MinGW
Version 1.99 20070416
Copyright (C) 2005-2007 Kevin Kofler
Copyright (C) 2001-2006 Romain Lievin
Copyright (C) 2006 Tyler Cassidy

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

This is how to compile LPG software with MinGW. This bugger can be tricky so watch out. :)

These compiling instructions will work for:
- libticables2, libticonv, libtifiles2, libticables2
- TiLP 2
- TiEmu 3
- GFM

Follow the instructions very closely or you will soon see that monkeys will start biting. ;-)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

---------------------------------------
| Retrieving sources                  |
---------------------------------------

There are two ways to retrieve source code:
- downloads tarballs from <http://sourceforge.net/project/showfiles.php?group_id=23169>
- uses SubVersion (svn for short)

1) from tarballs: create a folder and extract all of your tarballs

2) from subversion: you will have to install svn-tools (linux) or a client (TortoiseSVN/Win32).
Take a look at <http://tortoisesvn.tigris.org> and <http://svnbook.red-bean.com>.
 
There is no specific tree for download sources but you can use this convenient one:

	c:\sources\ or /home/devel/
	|
	+- ticables2
	+- ticalcs2
	+- ticonv
	+- tiemu3
	+- tifile2
	+- ticables2
	+- tilp2

Next, check-out the following URLs for each target folder: 
- svn co http://svn.tilp.info/repos/tilp/tilp/trunk tilp2
- svn co http://svn.tilp.info/repos/tilp/libticables/trunk ticables2 
- svn co http://svn.tilp.info/repos/tilp/libticalcs/trunk ticalcs2 
- svn co http://svn.tilp.info/repos/tilp/libtifiles/trunk tifiles2 
- svn co http://svn.tilp.info/repos/tilp/libticonv/trunk ticonv  
- svn co http://svn.tilp.info/repos/tilp/tiemu/trunk tiemu3

---------------------------------------
| Compiling on Windows                |
---------------------------------------

1. Download the following stuff, but do not install it yet!
   - MinGW and MSYS from http://www.mingw.org/
   - Bison Binaries, Dependancies and Developer Files from http://gnuwin32.sf.net/packages/bison.htm
   - Flex Binaries, Dependancies and Developer Files from http://gnuwin32.sf.net/packages/flex.htm

2. Extract the MinGW stuff into C:\mingw and install MSYS into C:\msys, not C:\msys\1.0

3. Extract all the Bison and Flex archives into the C:\mingw directory

4. Create a C:\msys\target folder. This is where the compiled stuff will be placed.
	 This is alse the location where you will install GladeWin32 (see below).

5. Download and Install the GladeWin32 Development Packages from
   http://prdownloads.sf.net/gladewin32/gtk-win32-devel-2.6.10-rc1.exe and make sure you check the
   "Install MSYS environment variables" checkbox when the installer asks you, if you don't, the
   monkeys WILL bite :)
   
   WARNING: DON'T build against GTK+ 2.8 for Windows! GTK+ 2.8 uses Cairo, which doesn't work at all
            on Windows 95/98/Me. Nobody seems interested in fixing that. We've learned this the hard
            way. You have been warned.
            
   You have to change the target folder of the installer into C:\msys\target otherwise you will have to 
   replace any 'prefix=/target' entry in any of INST_PATH\lib\pkgconfig\*.pc by 'prefix=INST_PATH'.

6. Edit the C:\msys\etc\profile file and add the following on a new line at the bottom:
   export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/target/lib/pkgconfig

7. Restart MSYS if you have done step 5 while MSYS was running.

8. Now let's compile. Open up MSYS if you haven't already. Make sure all of your source is extracted
   and ready to compile. With your basic Linux skills, go into the following directory and type the
   following:

   - Go into the libticables2 directory
   - Run:
     ./configure --prefix=/target --disable-nls
     make
     make install

9. Repeat Step 7 for the additional libti* libraries in the FOLLOWING order: libticonv, libtifiles2,
   libticalcs2.

10. Ok. Now all you have to do is repeat step 7 for TiLP, TiEmu, or GFM, or all of them if you so
   wish!

11. Your files are now all located in /target (C:\msys\target). If it does not work, an instruction
    may have been missed or performed wrong, or the source code is broken (which would be a bug,
    please report it).

Have fun :)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

---------------------------------------------------
| Building an Installer on Windows for TiEmu3+GDB |
---------------------------------------------------

Once you have successfully built TiEmu 3, here's how to build an installer on Windows:

1. Fetch the latest NSIS installer from http://nsis.sf.net and install it.

2. Fetch UPX from http://upx.sf.net and unzip it.

3. Adjust the paths in build\nsis\tiemu.nsi (in the TiEmu 3 source directory) for your installation.

4. Right-click on build\nsis\tiemu.nsi and select "Build".

NOTE: TiLP and GFM don't have NSIS installer scripts yet.

------------------------------------------------------------
| Building an Installer on Windows for TiLP2 or TiEmu3-GDB |
------------------------------------------------------------

Once you have successfully built TiLP2/TiEmu3, here's how to build an installer on Windows:

1. Fetch the latest InnoSetup installer v5 from http://www.jrsoftware.org/isinfo.php and install it.

2. Fetch the GNU wget for Win32 from http://xoomer.alice.it/hherold/wget-1.10.2b.zip and unzip it into build/InnoSetup/wget.

3. Press Ctrl+F9 ("Build>Compile").

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

---------------------------------------
| Cross Compiling on Linux (Fedora)   |
---------------------------------------

1. Download and Install the following RPMs from http://mirzam.it.vu.nl/mingw/ :
   - mingw-binutils
   - mingw-w32api
   - mingw-runtime

2. Download and Install the MinGW GCC RPM from http://bitwalk.hp.infoseek.co.jp/download.html
   (Make sure you get a package which includes g++. It is needed to build oleaut.cpp.)

3. Install WINE from Fedora Extras. (Can be retrieved with yum: "yum install wine".)

4. Install the last GTK+ 2.6 development package (version 2.6.10-rc1) from http://gladewin32.sf.net
   in WINE.
   WARNING: DON'T build against GTK+ 2.8 for Windows! GTK+ 2.8 uses Cairo, which doesn't work at all
            on Windows 95/98/Me. Nobody seems interested in fixing that. We've learned this the hard
            way. You have been warned.

5. Run the following command:
   ln -s ~/.wine/c/GTK /target
   (This makes pkg-config happy, you can replace .../c/... with whatever directory/drive you wish to
   use.)

6. In order to avoid a needless dependency on mingwm10.dll, edit the following file:
   /usr/local/i386-mingw32/lib/libstdc++.la
   and remove "-lmingwthrd".

7. Edit cross-mingw32-gtkaio.sh to your system's needs.

8. Use the following commands to build TiEmu (TiLP and GFM can be built the same way, if this is
   broken, please report it as a bug):
   source cross-mingw32-gtkaio.sh #(needs to be done for EACH build!)
   export CFLAGS="-Os -s -fno-exceptions"
   export CXXFLAGS="-Os -s -fno-exceptions"
   cd libticables-mingw-build
   ./configure --prefix=~/.wine/c/tiemu --disable-nls --host=i386-mingw32 --build=i686-redhat-linux-gnu
   make
   make install
   cd ../libticonv-mingw-build
   ./configure --prefix=~/.wine/c/tiemu --disable-nls --host=i386-mingw32 --build=i686-redhat-linux-gnu
   make
   make install
   cd ../libtifiles-mingw-build
   ./configure --prefix=~/.wine/c/tiemu --disable-nls --host=i386-mingw32 --build=i686-redhat-linux-gnu
   make
   make install
   cd ../libticalcs-mingw-build
   ./configure --prefix=~/.wine/c/tiemu --disable-nls --host=i386-mingw32 --build=i686-redhat-linux-gnu
   make
   make install
   cd ../tiemu-mingw-build
   ./configure --prefix=~/.wine/c/tiemu --disable-nls --host=i386-mingw32 --build=i686-redhat-linux-gnu
   make
   make install
   i386-mingw32-strip ~/.wine/c/tiemu/bin/*
   NOTE: You'll have to substitute an absolute path for ~ to make configure happy.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

---------------------------------------
| Running your software on WINE       |
---------------------------------------

If you have built your program against GTK+ 2.6 as per the instructions above, it will run in WINE.

1. Open WINE regedit and add ";c:\GTK\bin" to HKEY_CURRENT_USER\Environment\PATH.

2. Copy all the .ttf files from /usr/share/fonts/bitstream-vera/ to ~/.wine/c/windows/Fonts so GTK+
   in WINE has fonts to work with.

3. Add "bitstream vera sans" to the aliases for "sans" and likewise for "serif", "monospace" and
   "courier" in ~/.wine/c/GTK/etc/pango/pango.aliases.

4. Run:
   wine 'c:\tiemu\bin\tiemu.exe'

WARNING: DON'T use GTK+ 2.8 if you want to be able to test with WINE!

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

---------------------------------------
| Cross-Building a Windows Installer  |
---------------------------------------

Once you have successfully cross-built TiEmu 3, here's how to build a Windows installer on Fedora:

1. Fetch the latest NSIS source tarball from http://nsis.sf.net

2. Install the SCons development version (a noarch RPM) from http://www.scons.org

3. Build NSIS:
   scons PREFIX=/usr/local SKIPSTUBS=all SKIPPLUGINS=all SKIPUTILS=all SKIPMISC=all VERSION=2.xx
   scons PREFIX=/usr/local SKIPSTUBS=all SKIPPLUGINS=all SKIPUTILS=all SKIPMISC=all VERSION=2.xx install
   where 2.xx is the NSIS version (otherwise the binary will claim to be a CVS version).

4. Fetch the corresponding NSIS ZIP file from http://nsis.sf.net

5. Extract some of the contents of the ZIP file into /usr/local:
   Docs, Examples -> /usr/local/share/doc/nsis
   Bin, Contrib, Include, Menu, Plugins, Stubs -> /usr/local/share/nsis

6. Install UPX from Fedora Extras. (Can be retrieved with yum: "yum install upx".)

7. Use the following commands to build the TiEmu setup wizard:
   cd build/nsis
   makensis tiemu-cross.nsi

NOTE: TiLP and GFM don't have NSIS installer scripts yet.
