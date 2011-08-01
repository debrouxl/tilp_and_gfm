#! /bin/sh

# Maintainer script for automating the compilation and installation of tilp & gfm
# from a checkout of the complete tilp repository over at svn.tilp.info.
#
# Copyright (C) 2010, 2011 Lionel Debroux

# The prefix where the binaries will be installed, e.g. $HOME, /usr, /usr/local.
PREFIX="$HOME"

# Common flags and definitions.
CCFLAGS="-Os -g3 -Wall -W -Wno-unused-parameter -Wshadow -Wwrite-strings -Wredundant-decls -Wdeclaration-after-statement -fstack-protector-all -Wstack-protector --param=ssp-buffer-size=1"
CCPPFLAGS="-D_FORTIFY_SOURCE=2"

# Configure and build the given module
handle_one_module() {
  module_name="$1"
  shift # Kick the first argument, so as to be able to pass the rest to configure.

  cd "$module_name/trunk"
  echo "Configuring $module_name"
  rm -f config.cache
  ./configure CPPFLAGS="$CCPPFLAGS" CFLAGS="$CCFLAGS" CXXFLAGS="$CCFLAGS" --prefix="$PREFIX" $@ || return 1
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


echo "=== tfdocgen ==="
handle_one_module tfdocgen || exit 1


echo "=== libticonv ==="
handle_one_module libticonv || exit 1
# Useful configure options include --disable-nls.
echo "=== libtifiles ==="
handle_one_module libtifiles || exit 1
# Useful configure options include --disable-nls, --enable-logging.
echo "=== libticables ==="
handle_one_module libticables --enable-logging || exit 1
# Useful configure options include --disable-nls.
echo "=== libticalcs ==="
handle_one_module libticalcs || exit 1


echo "=== gfm ==="
handle_one_module gfm || exit 1
echo "=== tilp ==="
handle_one_module tilp || exit 1
