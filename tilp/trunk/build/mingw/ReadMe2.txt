Put msys into mingw although it's strongly discouraged but there is no files in conflict, so...

- xml2: ./configure --prefix=/usr --without-ftp --without-http
- glade: ./configure --prefix=/usr

still need PKG export ? no !

----

- get the libxml2 binary from <http://gnuwin32.Sf.net>
	think to add libxml2.pc and remove libxml2.la.
- get the libglade-2.0.1 devel from <http://gladewin32.sourceforge.net/> 
	or 

pour recompiler la libxml2, l'environnement doit etre clean: pas d'includes

from Tor (Gimp/Win32):

export CPPFLAGS="-I/target/include"
export LDFLAGS="-L/target/lib"

or add them into /etc/profile with the PKG_CONFIG_EXPORT and export PATH="$PATH:/target/bin"

./configure --prefix=/target
cross: --host=i386-pc-mingw32
