#! /bin/sh

# Maintainer script for automating the compilation and installation of tilp & gfm
# from a checkout of the complete tilp repository over at svn.tilp.info.
#
# Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015 Lionel Debroux

# The prefix where the binaries will be installed, e.g. $HOME, /usr, /usr/local.
PREFIX="$HOME"

# Common flags and definitions.
CCFLAGS="-Os -g3 -Wall -W -Wno-unused-parameter -Werror=shadow -Werror=write-strings -Werror=redundant-decls -Werror=format -Werror=format-nonliteral -Werror=format-security -Werror=declaration-after-statement -Werror=implicit-function-declaration -Werror=date-time -Werror=missing-prototypes -Werror=return-type -Werror=pointer-arith -fstack-protector-all -Wstack-protector --param=ssp-buffer-size=1 -fsanitize=undefined,bounds"
CCPPFLAGS="-D_FORTIFY_SOURCE=2"

# Configure and build the given module
handle_one_module() {
  module_name="$1"
  shift # Kick the first argument, so as to be able to pass the rest to configure.

  cd "$module_name/trunk"
  echo "Configuring $module_name"
  rm -f config.cache
  ./configure CPPFLAGS="$CCPPFLAGS" CFLAGS="$CCFLAGS $CFLAGS" CXXFLAGS="$CCFLAGS $CFLAGS" --prefix="$PREFIX" $@ || return 1
  echo "Building $module_name"
  make clean || return 1
  make -j4 || return 1
  echo "Installing $module_name"
  make check || return 1
  make install || return 1
  cd -
}

if [ "x$NOAUTORECONF" = "x" -a "x$NO_AUTORECONF" = "x" ]; then
echo "=== AUTORECONF ==="
./run_autoreconf.sh || exit 1
fi

echo "=== UPDATEPOT ==="
./run_updatepot.sh || exit 1


echo "=== tfdocgen ==="
handle_one_module tfdocgen || exit 1


echo "=== libticonv ==="
handle_one_module tilibs/libticonv --enable-iconv || exit 1
# Useful configure options include --disable-nls.
echo "=== libtifiles ==="
handle_one_module tilibs/libtifiles || exit 1
# Useful configure options include --disable-nls, --enable-logging.
echo "=== libticables ==="
handle_one_module tilibs/libticables --enable-logging --enable-libusb10 || exit 1
# Useful configure options include --disable-nls.
echo "=== libticalcs ==="
handle_one_module tilibs/libticalcs --disable-builtin-rom-dumpers || exit 1


echo "=== gfm ==="
handle_one_module tilp_and_gfm/gfm || exit 1
echo "=== tilp ==="
handle_one_module tilp_and_gfm/tilp || exit 1
