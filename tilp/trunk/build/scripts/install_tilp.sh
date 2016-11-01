#! /bin/bash

# This script, aimed at users, automates the compilation and installation of tilp & gfm
# from the Git repositories.
# It's mirrored at http://lpg.ticalc.org/prj_tilp/download/install_tilp.sh
#
# **********
# IMPORTANT:
# **********
#     * please read below for prerequisites (build dependencies) or peculiarities (e.g. 64-bit Fedora).
#     * you should remove equivalent packages, if any, before running this script.
#
# Copyright (C) Lionel Debroux 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016
# Copyright (C) Adrien "Adriweb" Bertrand 2015
# Copyright (C) Fabian "Vogtinator" Vogt 2016

# libti* and tilp are compiled with a proposed set of configuration options,
# but you may wish to use others. The complete list is available through
# `./configure --help` run in $SRCDIR/tilp/tilibs/libticonv/trunk, $SRCDIR/tilp/tilibs/libtifiles/trunk,
# $SRCDIR/tilp/tilibs/libticables/trunk, $SRCDIR/tilp/tilibs/libticalcs/trunk,
# $SRCDIR/tilp/tilp_and_gfm/gfm/trunk and $SRCDIR/tilp/tilp_and_gfm/tilp/trunk.


# **********************************************************************
# MANDATORY dependencies for compiling and running libti*, gfm and tilp:
# **********************************************************************
# (Debian and Fedora package names are given as examples, install respectively with `apt-get install ...` and `yum install ...`)
# * Git (git, git)
# * Suitable C compiler + C++ compiler (the newer, the better):
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
# * libusb development files (libusb-1.0-0-dev, libusb1-devel)
#   (libusb 1.0 preferred, libticables' libusb 0.1 backend based on libusb-dev or libusb-devel in maintenance mode now)
# * GTK+ 2.x development files (libgtk2.0-dev, gtk2-devel)
# * Glade development files (libglade2-dev, libglade2-devel)
# * GNU gettext (gettext, gettext)
# * GNU bison (bison, bison)
# * GNU flex (flex, flex)
# * GNU groff (groff, groff)
# * GNU texinfo (texinfo, texinfo)
# * XDG utils (xdg-utils, xdg-utils)
# * libarchive (libarchive-dev)
# * intltool (intltool)


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
    # Default to replacing system packages (if any), because
    # 1) distro packages are usually outdated;
    # 2) /usr/local subdirs are less likely to be in $PATH / $LD_LIBRARY_PATH / $PKG_CONFIG_PATH
    #    than /usr subdirs => more spurious install issues which waste both user and maintainer time.
    PREFIX="/usr"
fi


# ******************************************************************************
# Default place where the sources will be stored, if it's not de
# Note that you can set the value of SRCDIR thusly:
# $ SRCDIR="/opt/src" <path>/install_tilp.sh
# ******************************************************************************
if [ "x$SRCDIR" = "x" ]; then
    SRCDIR="$HOME/lpg"
fi


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


# Subroutine: clone/update repository copies.
handle_repository_copies() {
  module_name="$1"
  if [ -d "$module_name" -a -d "$module_name/.git" ]; then
    echo "Updating $module_name"
    cd "$module_name"
    git pull || return 1
  else
    echo "Cloning $module_name"
    git clone "https://github.com/debrouxl/$module_name" "$module_name" || return 1
    cd "$module_name"
  fi
  if [ "x$USE_EXPERIMENTAL" != "x" ]; then
    echo "Checking out the 'experimental' branch"
    git checkout experimental || return 1
  fi
  cd ..
}

# Subroutine: checkout/update, `configure`, `make` and `make install` the given module
handle_one_module() {
  module_name="$1"
  shift # Kick the first argument, so as to be able to pass the rest to configure.

  cd "$module_name/trunk"
  echo "Configuring $module_name"
  # Add --libdir=/usr/lib64 on e.g. 64-bit Fedora 14, which insists on searching for 64-bit libs in /usr/lib64.
  # Or modify PKG_CONFIG_PATH as described above.
  mkdir -p m4 || return 1
  autoreconf -i -v -f || return 1
  ./configure "--prefix=$PREFIX" CC=$CC CXX=$CXX $@ || return 1
  echo "Building $module_name"
  make || return 1
  echo "Installing $module_name"
  make install || return 1
  cd -
}

# Subroutine: perform quick rough sanity check on compilers and PREFIX.
rough_sanity_checks() {
  echo "Creating output folder if necessary"
  mkdir -p "$SRCDIR/tilp" || return 1

  echo "Performing a quick rough sanity check on compilers"
  # Test CC, which also checks whether the user can write to SRCDIR
  cat << EOF > "$SRCDIR/tilp/hello.c"
#include <stdio.h>

int main(int argc, char * argv[]) {
    printf("Hello World !\n");
    return 0;
}
EOF

  "$CC" "$SRCDIR/tilp/hello.c" -o "$SRCDIR/tilp/hello" || return 1
  "$SRCDIR/tilp/hello" || return 1
  echo "CC=$CC exists and is not totally broken"
  # Test CXX, which also checks whether the user can write to SRCDIR
  cat << EOF > "$SRCDIR/tilp/hello.cc"
#include <cstdio>

int main(int argc, char * argv[]) {
    printf("Hello World !\n");
    return 0;
}
EOF

  "$CXX" "$SRCDIR/tilp/hello.cc" -o "$SRCDIR/tilp/hello" || return 1
  "$SRCDIR/tilp/hello" || return 1
  echo "CXX=$CXX exists and is not totally broken"

  echo "Checking whether $PREFIX can be written to"
  mkdir -p $PREFIX
  if [ "$?" -ne 0 ]; then
    echo -e "\033[1mNo, cannot create $PREFIX. Perhaps you need to run the script as root ?\nAborting.\033[m"
    return 1
  fi
  TEMPFILE=`mktemp $PREFIX/XXXXXXXXXXX`
  if [ "$?" -ne 0 ]; then
    echo -e "\033[1mNo, cannot write to $PREFIX. Perhaps you need to run the script as root ?\nAborting.\033[m"
    return 1
  fi
  cat << EOF > "$TEMPFILE"
This is a test file
EOF
  if [ "$?" -ne 0 ]; then
    echo -e "\033[1mNo, cannot write to $PREFIX. Perhaps you need to run the script as root ?\nAborting.\033[m"
    return 1
  fi
  rm "$TEMPFILE"
}

listdeps() {
    echo "Debian 8:"
    echo -e "    apt-get install build-essential git autoconf automake autopoint libtool libtool-bin libglib2.0-dev zlib1g-dev libusb-1.0-0-dev libgtk2.0-dev libglade2-dev gettext bison flex groff texinfo xdg-utils libarchive-dev intltool\n"
    echo "Fedora 23:"
    echo -e "    dnf install git gcc gcc-c++ make pkgconfig autoconf automake libtool glib2-devel zlib-devel libusb1-devel gtk2-devel libglade2-devel gettext bison flex groff texinfo xdg-utils libarchive-devel intltool xz\n"
    echo "CentOS 7:"
    echo -e "    yum install git gcc gcc-c++ make pkgconfig autoconf automake libtool glib2-devel zlib-devel libusb1-devel gtk2-devel libglade2-devel gettext bison flex groff texinfo xdg-utils libarchive-devel intltool xz\n"
    echo "OpenSUSE 42.1:"
    echo -e "    zypper install git gcc gcc-c++ make pkg-config autoconf automake libtool glib2-devel zlib-devel libusb-1_0-devel gtk2-devel libglade2-devel gettext-tools bison flex groff texinfo xdg-utils libarchive-devel intltool xz\n"
    echo "Alpine 3.3:"
    echo -e "    apk add git gcc g++ make pkgconfig autoconf automake libtool glib-dev zlib-dev libusb-dev gtk+-dev libglade-dev gettext-dev bison flex groff texinfo xdg-utils libarchive-dev intltool xz\n"
    echo "Arch Linux 2015.06.01 + upgrades:"
    echo -e "    pacman -S git gcc make pkgconfig autoconf automake libtool glib2 zlib libusb gtk2 libglade gettext bison flex groff texinfo xdg-utils libarchive intltool xz\n"
    echo "MacOS X:"
    echo -e "    brew install gettext libarchive autoconf automake libtool glib lzlib libusb gtk+ libglade sdl bison flex texinfo intltool"
    echo -e "    brew link --force libarchive gettext (you can use 'brew unlink' later)."
}

# The main part of the script starts here.
# Shall we list build deps ?
if [ "x$1" = "x--listdeps" ]; then
    echo "Build dependencies for libticonv, libtifiles, libticables, libticalcs, gfm and tilp:"
    listdeps
    exit 0
fi

# First of all, platform-specific adjustments.
UNAME=`uname`
# On MacOS X 10.11, locally compiled programs are _really_ supposed to be installed to /usr/local.
if [ "x$PREFIX" = "x/usr" ]; then
    if [ "x$UNAME" = "xDarwin" ]; then
        echo "Modern MacOS X versions don't like programs installing to /usr, using /usr/local instead"
        PREFIX="/usr/local"
    fi
fi
# On MacOS X 10.11, need to fiddle with PKG_CONFIG_PATH.
if [ "x$UNAME" = "xDarwin" ]; then
    echo "Modifying PKG_CONFIG_PATH on MacOS X"
    if [ "x$PKG_CONFIG_PATH" = "x" ]; then
        PKG_CONFIG_PATH="$PREFIX/lib/pkgconfig:/opt/X11/lib/pkgconfig"
    else
        PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$PREFIX/lib/pkgconfig:/opt/X11/lib/pkgconfig"
    fi
    export PKG_CONFIG_PATH
fi
LIBDIR="$PREFIX/lib"
# Some 64-bit Linux distros use /lib64 or /usr/lib64.
if [ "x$UNAME" = "xLinux" ]; then
    echo "Determining whether $PREFIX/lib64 is probably used"
    ldd /usr/bin/getent | grep "=>" | grep /lib64/ || echo "No, $PREFIX/lib64 is probably not used"
    ldd /usr/bin/getent | grep "=>" | grep /lib64/ && echo "Yes, $PREFIX/lib64 is probably used, will use it for LIBDIR" && LIBDIR="$PREFIX/lib64"
fi

# Go on.
echo Will use "PREFIX=$PREFIX"
echo Will use "SRCDIR=$SRCDIR"
if [ "x$USE_EXPERIMENTAL" != "x" ]; then
echo "***** Will checkout experimental branches *****"
fi
echo Will use "PATH=$PATH"
echo Will use "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
echo Will use "PKG_CONFIG_PATH=$PKG_CONFIG_PATH"
echo Will use "LIBDIR=$LIBDIR"
echo Will use "CC=$CC"
echo Will use "CXX=$CXX"

echo -e "\033[4mBefore proceeding further, make sure that you're ready to go (look inside the install script):\033[m"
echo -e "1) configured \033[1mPREFIX\033[m and \033[1mSRCDIR\033[m the way you wish"
echo -e "   (as well as \033[1mCC\033[m and \033[1mCXX\033[m if you're into using non-GCC compilers when the distro defaults to GCC);"
echo -e "2) configured \033[1mPKG_CONFIG_PATH\033[m if necessary"
echo -e "3) \033[1mpurged any installed distro packages\033[m for libticonv, libtifiles, libticables, libticalcs, gfm, tilp."
echo -e "4) installed the build dependencies listed in the script. For instance:"
listdeps
echo -e "\033[4mOtherwise, either the build will fail, or the system may not use the just-built version (e.g. if you didn't purge the distro packages) !\033[m"
echo -e "\033[1mENTER to proceed, CTRL + C to abort\033[m."
read

rough_sanity_checks || exit 1

cd "$SRCDIR/tilp"
echo "=== Downloading tilibs ==="
handle_repository_copies tilibs || exit 1
echo "=== Downloading tilp_and_gfm ==="
handle_repository_copies tilp_and_gfm || exit 1
echo "=== libticonv ==="
handle_one_module tilibs/libticonv "--libdir=$LIBDIR" --enable-iconv || exit 1
# Useful configure options include --disable-nls.
echo "=== libtifiles ==="
handle_one_module tilibs/libtifiles "--libdir=$LIBDIR" || exit 1
# Useful configure options include --disable-nls, --enable-logging
echo "=== libticables ==="
handle_one_module tilibs/libticables "--libdir=$LIBDIR" --enable-logging --enable-libusb10 || exit 1
# Useful configure options include --disable-nls.
echo "=== libticalcs ==="
handle_one_module tilibs/libticalcs "--libdir=$LIBDIR" || exit 1

# Use --with-kde if you want to use the native KDE file dialogs (it defaults to disabled because it requires a slew of development package dependencies).
echo "=== gfm ==="
handle_one_module tilp_and_gfm/gfm "--libdir=$LIBDIR" || exit 1
echo "=== tilp ==="
handle_one_module tilp_and_gfm/tilp "--libdir=$LIBDIR" || exit 1

echo "=================================================="
echo "=== libti* + gfm + tilp installed successfully ==="
echo "=================================================="
echo ""
echo ""
echo ""
echo "=================================================="
echo "IMPORTANT NOTES                    IMPORTANT NOTES"
echo "=================================================="
echo "If you want to use TILP as a non-root user, follow the instructions in $SRCDIR/tilp/tilibs/libticables/trunk/CONFIG"
