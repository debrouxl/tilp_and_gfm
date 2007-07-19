dnl Process this file with autoconf to produce a configure script.

# Init.
AC_PREREQ(2.57)
AC_INIT(GFM, 1.00, [tilp-users@lists.sourceforge.net])

AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

AC_PREFIX_DEFAULT(/usr/local)

# Files to configure.
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  build/Makefile
  build/mingw/Makefile
  glade/Makefile
  help/Makefile
  icons/Makefile
  man/Makefile
  pixmaps/Makefile
  po/Makefile.in
  src/Makefile
])

# Setup libtool.
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_CHECK_PROG(GROFF, groff, yes, no)
AM_CONDITIONAL(USE_GROFF, test "$GROFF" != "no")

# Checks for libraries.
AM_GNU_GETTEXT
AM_GNU_GETTEXT_VERSION([0.16.1])

PKG_CHECK_MODULES(TICONV, ticonv >= 1.0.4)
AC_SUBST(TICONV_CFLAGS)
AC_SUBST(TICONV_LIBS)

PKG_CHECK_MODULES(TIFILES, tifiles2 >= 1.0.7)
AC_SUBST(TIFILES_CFLAGS)
AC_SUBST(TIFILES_LIBS)

PKG_CHECK_MODULES(TICALCS, ticalcs2 >= 1.0.7)
AC_SUBST(TICALCS_CFLAGS)
AC_SUBST(TICALCS_LIBS)

PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.6.0)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.6.0)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

PKG_CHECK_MODULES(GLADE, libglade-2.0 >= 2.5.0)
AC_SUBST(GLADE_CFLAGS)
AC_SUBST(GLADE_LIBS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])
AC_CHECK_HEADERS([tilp2/ticonv.h tilp2/tifiles.h tilp2/ticalcs.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STAT
AC_TYPE_UID_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_STRUCT_TM

# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_CHECK_FUNCS([getcwd memset mkdir strcasecmp strchr strdup strrchr strstr])

# Ensure MSVC-compatible struct packing convention is used when
# compiling for Win32 with gcc.
# What flag to depends on gcc version: gcc3 uses "-mms-bitfields", while
# gcc2 uses "-fnative-struct".
case $host_os in
*mingw*|*cygwin*)
  if test x$GCC = xyes; then
    msnative_struct=''
    AC_MSG_CHECKING([how to get MSVC-compatible struct packing])
    if test -z "$ac_cv_prog_CC"; then
      our_gcc="$CC"
    else
      our_gcc="$ac_cv_prog_CC"
    fi
    case `$our_gcc --version | sed -e 's,\..*,.,' -e q` in
      2.)
        if $our_gcc -v --help 2>/dev/null | grep fnative-struct >/dev/null; then
          msnative_struct='-fnative-struct'
        fi
        ;;
      *)
        if $our_gcc -v --help 2>/dev/null | grep ms-bitfields >/dev/null; then
          msnative_struct='-mms-bitfields'
        fi
        ;;
    esac
    if test x"$msnative_struct" = x ; then
      AC_MSG_RESULT([no way])
      AC_MSG_WARN([produced libraries might be incompatible with MSVC-compiled 
code])
    else
      CFLAGS="$CFLAGS $msnative_struct"
      AC_MSG_RESULT([${msnative_struct}])
    fi
  fi
  ;;
esac

AM_CONDITIONAL(OS_WIN32, test "$msnative_struct")

# Check for the new -fvisibility=hidden flag introduced in gcc 4.0
# Allow to reduce shared library size and avoid symbol clash
case $host_os in
*mingw*)
  ;;
*)
        if test x$GCC = xyes; then
           visibility_flag=''
           AC_MSG_CHECKING([whether gcc accepts -fvisibility])
           if test -z "$ac_cv_prog_CC"; then
              our_gcc="$CC"
           else
              our_gcc="$ac_cv_prog_CC"
           fi
           if $our_gcc -v --help 2>/dev/null | grep "fvisibility" >/dev/null; then
              visibility_flag='-fvisibility=hidden'
           fi
           if test x"$visibility_flag" = x ; then
              AC_MSG_RESULT([no])
           else
              CFLAGS="$CFLAGS $visibility_flag"
              AC_MSG_RESULT([${visibility_flag}])
              AC_DEFINE(HAVE_FVISIBILITY, 1, [Use -fvisibility=hidden flag])
            fi
        fi
        ;;
esac

case "$host" in
  *-*-linux*) EXFL="-Wl,--export-dynamic" ;;
  *-*-mingw*) EXFL="-lcomdlg32" ;;
  *)          EXFL="" ;;
esac
LDFLAGS="$LDFLAGS $EXFL"

AC_SUBST(CFLAGS)
AC_SUBST(LDFLAGS)

# Output.
AC_OUTPUT

echo "Now, you can type 'make' and 'make install'."
