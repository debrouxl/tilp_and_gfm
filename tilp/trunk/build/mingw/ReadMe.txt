Procedure to set up the environment:

- get MinGW & MSys from <http://www.mingw.org/> and install it
- get pkg-config from <http://www.gimp.org/~tml/gimp/win32/downloads.html>
- pkg-config depends on: glib, glib-dev, libiconv, libgettext. Get them at same location.
- get pango, atk, glib, gtk+ as devel & runtime packages from <http://www.gimp.org>.
- go into the lib/pkgconfig folder and replace /target by /usr in *.pc files (same for libglade, too)

- get the libxml2 from <http://gnuwin32.Sf.net>
	think to add .pc and override .la files
- get the libglade devel from <http://gladewin32.sourceforge.net/> 
	or 
  get the libglade source and build it.	You may need to copy iconv.h into 
	include/libxml2 and to copy xml2.dll into lib/.libs

- simply select folders and copy them into MSys.

Before running ./configure --disable-nls, set the PKG_CONFIG_PATH with:
export PKG_CONFIG_PATH="c:/msys/1.0/lib/pkgconfig".

----
zlib from gnuwin32 (used by libxml2 ?)

pkg-config _must_ be installed in MinGW/bin, not MSys !