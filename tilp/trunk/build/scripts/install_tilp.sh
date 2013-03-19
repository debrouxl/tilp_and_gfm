#! /bin/bash

# This script, aimed at users, automates the compilation and installation of tilp & gfm
# from the SVN repository.
# It's mirrored at http://lpg.ticalc.org/prj_tilp/download/install_tilp.sh
#
# **********
# IMPORTANT:
# **********
#     * please read below for prerequisites (build dependencies) or peculiarities (e.g. 64-bit Fedora).
#     * you should remove equivalent packages, if any, before running this script.
#
# Copyright (C) Lionel Debroux 2009, 2010, 2011

# libti* and tilp are compiled with a proposed set of configuration options,
# but you may wish to use others. The complete list is available through
# `./configure --help` run in $SRCDIR/tilp/libticonv, $SRCDIR/tilp/libtifiles,
# $SRCDIR/tilp/libticables, $SRCDIR/tilp/libticalcs, $SRCDIR/tilp/gfm and $SRCDIR/tilp/tilp.



# **********************************************************************
# MANDATORY dependencies for compiling and running libti*, gfm and tilp:
# **********************************************************************
# (Debian and Fedora package names are given as examples, install respectively with `apt-get install ...` and `yum install ...`)
# * Subversion (subversion, subversion)
# * Suitable C compiler + C++ compiler:
#      * GCC + G++: (gcc + g++, gcc + gcc-c++)
#      * Clang (clang, clang), preferably version 3.0 and later.
# * GNU make (make, make). BSD make might work.
#   (on Debian, you can install "build-essential" to get gcc, g++ and make)
# * pkg-config (pkg-config, pkgconfig)
# * GNU autoconf (autoconf, autoconf)
# * GNU automake (automake, automake)
# * GNU libtool (libtool, libtool)
# * glib 2.x development files (libglib2.0-dev, glib2-devel)
# * zlib development files (zlib1g-dev, zlib-devel)
# * libusb development files (libusb-dev + libusb-1.0-0-dev, libusb-devel + libusb1-devel)
#   (libusb 0.1.x preferred, but libticables now has a libusb 1.0 backend activated with "--enable-libusb10", see below)
# * GTK+ 2.x development files (libgtk2.0-dev, gtk2-devel)
# * Glade development files (libglade2-dev, libglade2-devel)
# * SDL 1.2 development files (libsdl1.2-dev, SDL-devel)
# * GNU gettext (gettext, gettext)
# * GNU bison (bison, bison)
# * GNU flex (flex, flex)
# * GNU groff (groff, groff)
# * GNU texinfo (texinfo, texinfo)
# * XDG utils (xdg-utils, xdg-utils)
# * libarchive (libarchive-dev)
# * intltool (intltool)
#
# Optional dependencies:
# * KDE 3.x development files (kdelibs4-dev, kdelibs3-devel), if you want to compile tilp with support for the KDE file dialog.
#   (this implies a slew of development files, among which the Qt development files, and is therefore disabled by default)


# ******************************************************************************
# Default prefix where the binaries will be installed, e.g.
# $HOME, /usr, /usr/local, /opt/tilp.
# Note that you can set the value of PREFIX interactively through e.g.:
# $ PREFIX="$HOME" <path>/install_tilp.sh
# ******************************************************************************

# IMPORTANT NOTES:
# ----------------
# * for compilation to succeed, you may have to execute
# $ export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:[{$PREFIX}]/lib/pkgconfig
# (where [{$PREFIX}] is the contents of the PREFIX line below, without the quotes).
# The main cause for having to execute this line is installing to e.g. PREFIX=$HOME or /usr/local,
# but it may be necessary when installing to PREFIX=/usr, if your distro doesn't store
# libraries into the standard /usr/lib path.
#
# * after successful installation, you may have to add $PREFIX/bin to $PATH,
# and $PREFIX/lib to $LD_LIBRARY_PATH, for the SVN versions of libti*, tilp & gfm
# to get picked up.
if [ "x$PREFIX" = "x" ]; then
    PREFIX="/usr"
fi
echo Will use "PREFIX=$PREFIX"

# ******************************************************************************
# Default place where the sources will be stored, if it's not de
# Note that you can set the value of SRCDIR thusly:
# $ SRCDIR="/opt/src" <path>/install_tilp.sh
# ******************************************************************************
if [ "x$SRCDIR" = "x" ]; then
    SRCDIR="$HOME/lpg"
fi
echo Will use "SRCDIR=$SRCDIR"


# ******************************************************************************
# Default values for the C and C++ compilers, if these variables are not set
# in the environment or the command-line (before the invocation of install_tilp.sh).
# ******************************************************************************
if [ "x$CC" = "x" ]; then
    #CC=clang
    CC=gcc
fi
if [ "x$CXX" = "x" ]; then
    #CXX=clang++
    CXX=g++
fi


# Subroutine: checkout/update, `configure`, `make` and `make install` the given module
handle_one_module() {
  module_name="$1"
  shift # Kick the first argument, so as to be able to pass the rest to configure.

  if [ -d "$module_name" -a -d "$module_name/.svn" ]; then
    echo "Updating $module_name"
    cd "$module_name"
    svn up || return 1
    cd ..
  else
    echo "Checking out $module_name"
    svn co "http://svn.tilp.info/repos/tilp/$module_name/trunk" "$module_name" || return 1
  fi

  cd "$module_name"
  echo "Configuring $module_name"
  # Add --libdir=/usr/lib64 on e.g. 64-bit Fedora 14, which insists on searching for 64-bit libs in /usr/lib64.
  # Or modify PKG_CONFIG_PATH as described above.
  ./configure "--prefix=$PREFIX" CC=$CC CXX=$CXX $@ || return 1
  echo "Building $module_name"
  make || return 1
  echo "Installing $module_name"
  make install || return 1
  cd ..
}

# Subroutine: perform quick rough sanity check on compilers and PREFIX.
rough_sanity_checks() {
  echo "Performing a quick rough sanity check on compilers"
  # Test CC, which also checks whether the user can write to SRCDIR
  cat << EOF > "$SRCDIR/tilp/hello.c"
#include <stdio.h>

int main(int argc, char * argv[]) {
    printf("Hello World !\n");
    return 0;
}
EOF

  "$CC" "$SRCDIR/tilp/hello.c" -o "$SRCDIR/tilp/hello" || exit 1
  echo "CC=$CC exists"
  # Test CXX, which also checks whether the user can write to SRCDIR
  cat << EOF > "$SRCDIR/tilp/hello.cc"
#include <cstdio>

int main(int argc, char * argv[]) {
    printf("Hello World !\n");
    return 0;
}

EOF

  "$CXX" "$SRCDIR/tilp/hello.cc" -o "$SRCDIR/tilp/hello" || exit 1
  echo "CXX=$CXX exists"

  echo "Checking whether $PREFIX can be written to"
  TEMPFILE=`mktemp $PREFIX/XXXXXXXXXXX`
  if [ "$?" -ne 0 ]; then
    echo -e "\033[1mNo, cannot write to $PREFIX. Perhaps you need to run the script as root ?\nAborting.\033[m"
    exit 1
  fi
  cat << EOF > "$TEMPFILE"
This is a test file
EOF
  if [ "$?" -ne 0 ]; then
    echo -e "\033[1mNo, cannot write to $PREFIX. Perhaps you need to run the script as root ?\nAborting.\033[m"
    exit 1
  fi
  rm "$TEMPFILE"
}

# The main part of the script starts here.
echo -e "\033[4mBefore proceeding further, make sure that you're ready to go (look inside the install script):\033[m"
echo -e "1) configured \033[1mPREFIX\033[m and \033[1mSRCDIR\033[m the way you wish"
echo -e "   (as well as \033[1mCC\033[m and \033[1mCXX\033[m if you're into using non-GCC compilers);"
echo -e "2a) if you're using \033[1m64-bit Fedora\033[m (or any distro which installs libraries to non-standard paths), added --libdir=/usr/lib64 to the marked line, or..."
echo -e "2b) configured \033[1mPKG_CONFIG_PATH\033[m if necessary"
echo -e "3) installed the build dependencies listed in the script. Unless you're on Debian and derivatives, use libusb 1.0."
echo -e "        For instance, on Debian and derivatives, you would run:"
echo -e "        (sudo) apt-get install subversion autoconf automake libtool libglib2.0-dev zlib1g-dev libusb-dev libgtk2.0-dev libglade2-dev libsdl1.2-dev gettext bison flex groff texinfo xdg-utils libarchive-dev intltool"
echo -e "\033[4mOtherwise, the build will fail!\033[m."
echo -e "\033[1mENTER to proceed, CTRL + C to abort\033[m."
read

echo "Creating output folder if necessary"
mkdir -p "$SRCDIR/tilp" || exit 1

rough_sanity_checks

cd "$SRCDIR/tilp"
echo "=== libticonv ==="
handle_one_module libticonv || exit 1
# Useful configure options include --disable-nls.
echo "=== libtifiles ==="
handle_one_module libtifiles || exit 1
# Useful configure options include --disable-nls, --enable-logging, --enable-libusb10
echo "=== libticables ==="
handle_one_module libticables --enable-logging || exit 1
# Useful configure options include --disable-nls.
echo "=== libticalcs ==="
handle_one_module libticalcs || exit 1

# Use --with-kde if you want to use the native KDE file dialogs (it defaults to disabled because it requires a slew of development package dependencies).
echo "=== gfm ==="
handle_one_module gfm || exit 1
echo "=== tilp ==="
handle_one_module tilp || exit 1

echo "=================================================="
echo "=== libti* + gfm + tilp installed successfully ==="
echo "=================================================="
echo ""
echo ""
echo ""
echo "=================================================="
echo "IMPORTANT NOTES                    IMPORTANT NOTES"
echo "=================================================="
echo "If you want to use TILP as a non-root user, follow the instructions in $SRCDIR/tilp/libticables/CONFIG"
