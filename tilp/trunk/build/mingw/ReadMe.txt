Procedure to set up the environment:

- get MinGW & MSys from <http://www.mingw.org/> and install it
- get pkg-config from <http://www.gimp.org/~tml/gimp/win32/downloads.html>
- pkg-config depends on: glib, glib-dev, libiconv, libgettext. Get them at same location.
- get pango, atk, glib, gtk+ as devel & runtime packages from <http://www.gimp.org>.
- go into the lib/pkgconfig folder and replace /target by /usr in *.pc files

- get the libxml2 from <http://gnuwin32.Sf.net> and add the libxml-2.0.pc provided
- get the libglade from <http://gladewin32.sourceforge.net/modules.php?name=Downloads&d_op=viewdownload&cid=3>
- go into and build it/install it.

- simply select folders and copy them into MSys.

Before running ./configure --disable-nls, set the PKG_CONFIG_PATH with:
export PKG_CONFIG_PATH="c:/msys/1.0/lib/pkgconfig".


Enjoy (especially Kevin who likes MiNGW ;-) !