Procedure to set up the environment:

- get MinGW & MSys from <http://www.mingw.org/> and install it
- get pkg-config from <http://www.gimp.org/~tml/gimp/win32/downloads.html>
	pkg-config _must_ be installed in MinGW/bin, not MSys !
- pkg-config depends on: glib, glib-dev, libiconv, libgettext. Get them at same location.
- get pango, atk, glib, gtk+ as devel & runtime packages from <http://www.gimp.org>.
- go into the lib/pkgconfig folder and replace /target by /usr in *.pc files (same for libglade, too)

- get the zlib from <http://gnuwin32.Sf.net>
- get the libxml2 binary from <http://gnuwin32.Sf.net>
	think to add libxml2.pc and remove libxml2.la.
- get the libglade-2.0.1 devel from <http://gladewin32.sourceforge.net/> 
	or 

  get the libxml2-2.5.10 source from <http://xmlsoft.org/sources/old/>
	and build it.
  get the libglade source and build it.	You may need to copy 
	iconv.h into include/libxml2.

- simply select folders and copy them into MSys.

Before running ./configure --disable-nls, set the PKG_CONFIG_PATH with:
export PKG_CONFIG_PATH="c:/msys/1.0/lib/pkgconfig".

----