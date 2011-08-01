#! /bin/sh

# Maintainer script for automating the cross-compilation and installation of tilp & gfm
# from a checkout of the complete tilp repository over at svn.tilp.info.
#
# Copyright (C) 2010, 2011 Lionel Debroux, Benjamin Moody


# REMINDERS: don't forget to:
# 1) create AND chmod +x a "i586-mingw32msvc-pkg-config" script in the path:
# #!/bin/sh
# export PKG_CONFIG_LIBDIR=/usr/i586-mingw32msvc/lib
# exec pkg-config $@
# (this is for my Debian Lenny, at least)
#
# 2) create a /target folder pointing to the GTK Wine install path, e.g.
#    $HOME/.wine/drive_c/GTK
#
# 3) if necessary (dependency error about pixman-1), remove "pixman-1 >= 0.10.0"
#    from the "Requires.private:" line in <GTK_INSTALL_DIR>/lib/pkgconfig/cairo.pc.

# The prefix where the binaries will be installed, e.g. $HOME, /usr, /usr/local.
PREFIX="$HOME/lpg/packages"

# Common flags and definitions.
CCFLAGS="-Os -g3 -Wall -W -Wno-unused-parameter -Wshadow -Wwrite-strings -Wredundant-decls -Wdeclaration-after-statement"
CCPPFLAGS="-D_FORTIFY_SOURCE=2 -I$HOME/lpg/deps/gtk-win32/include"
CLDFLAGS="-L$HOME/lpg/deps/gtk-win32/lib"
LIBUSB_DIR="$HOME/lpg/deps/libusb-win32"
CHOST="i586-mingw32msvc"

export PKG_CONFIG_PATH=$HOME/lpg/packages/lib/pkgconfig:$HOME/lpg/deps/gtk-win32/lib/pkgconfig:$PKG_CONFIG_PATH
export PKG_CONFIG_LIBDIR=$HOME/lpg/pkgconfig

# Configure and build the given module
handle_one_module() {
  module_name="$1"
  shift # Kick the first argument, so as to be able to pass the rest to configure.

  cd "$module_name/trunk"
  echo "Configuring $module_name"
  rm -f config.cache
  ./configure --host="$CHOST" CPPFLAGS="$CCPPFLAGS" CFLAGS="$CCFLAGS" CXXFLAGS="$CCFLAGS" LDFLAGS="$CLDFLAGS" LIBUSB_CFLAGS="-I$LIBUSB_DIR/include" LIBUSB_LIBS="-L$LIBUSB_DIR/lib/gcc -lusb" --prefix="$PREFIX" $@ || return 1
  echo "Building $module_name"
  make clean || return 1
  make || return 1
  echo "Installing $module_name"
  make install || return 1
  cd ../..
}


echo "=== AUTORECONF ==="
sh run_autoreconf.sh

echo "=== UPDATEPOT ==="
sh run_updatepot.sh


sed "s/+ _nl_msg.*$//" -i libtifiles/trunk/configure
sed "s/+ _nl_msg.*$//" -i libticables/trunk/configure
sed "s/+ _nl_msg.*$//" -i libticalcs/trunk/configure
sed "s/+ _nl_msg.*$//" -i gfm/trunk/configure
sed "s/+ _nl_msg.*$//" -i tilp/trunk/configure


echo "=== tfdocgen ==="
handle_one_module tfdocgen || exit 1


echo "=== libticonv ==="
handle_one_module libticonv || exit 1

echo "=== libtifiles ==="
handle_one_module libtifiles || exit 1

echo "=== libticables ==="
handle_one_module libticables --enable-logging || exit 1

echo "=== libticalcs ==="
handle_one_module libticalcs || exit 1


echo "=== gfm ==="
handle_one_module gfm || exit 1
echo "=== tilp ==="
handle_one_module tilp || exit 1
