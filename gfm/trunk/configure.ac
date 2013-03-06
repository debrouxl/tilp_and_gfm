dnl Process this file with autoconf to produce a configure script.

# Init.
AC_PREREQ(2.57)
AC_INIT(GFM, 1.07, [tilp-users@lists.sourceforge.net])

AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])

AC_PREFIX_DEFAULT(/usr/local)

# Files to configure.
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  build/Makefile
  build/mingw/Makefile
  desktop/Makefile
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
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_CHECK_PROG(GROFF, groff, yes, no)
AM_CONDITIONAL(USE_GROFF, test "$GROFF" != "no")
AC_CHECK_TOOL(RC, windres, windres)

# Checks for libraries.
AM_GNU_GETTEXT(external)
AM_GNU_GETTEXT_VERSION([0.17])

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

# KDE dialogs support
AC_ARG_WITH(kde, AC_HELP_STRING([--with-kde], [Compile with KDE support]), [kde=$withval], [kde=no])
if test "x$kde" = "xdefault"; then
  case $host_os in
    *mingw*)
      kde=no
      ;;
    *)
      kde=yes
      ;;
  esac
fi
if test "x$kde" = "xyes"; then
        AC_PROG_CXX
        AC_PATH_KDE
        AC_DEFINE(WITH_KDE, 1, [Use KDE support])
fi
AM_CONDITIONAL(USE_KDE, test "x$kde" = "xyes")
AC_SUBST(kde)

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

# Find a C compiler for the build system (needed for compiling cleaner)
AC_ARG_VAR([CC_FOR_BUILD], [C compiler for programs to be run on the build system])
AC_ARG_VAR([CFLAGS_FOR_BUILD], [C compiler flags for CC_FOR_BUILD])
AC_MSG_CHECKING([for the host compiler])
if test "x$build" == "x$host" ; then
  # Not cross-compiling.
  CC_FOR_BUILD=$CC
  CFLAGS_FOR_BUILD=$CFLAGS
  AC_MSG_RESULT([${CC_FOR_BUILD}])
else
  # Try to find the host CC among several choices
  AC_CHECK_PROGS(CC_FOR_BUILD, [gcc cc clang c89 c99], [false])
  if test "x$CC_FOR_BUILD" = "xfalse" ; then
    AC_MSG_FAILURE([not found.])
  else
    AC_MSG_RESULT([${CC_FOR_BUILD}])
  fi
fi

case "$host" in
  *-*-linux*) EXFL="-Wl,--export-dynamic" ;;
  *-*-mingw*) EXFL="-lcomdlg32" ;;
  *)          EXFL="" ;;
esac
LDFLAGS="$LDFLAGS $EXFL"

# On Darwin, libglade chokes on stripped executables.
case "$host" in
  *-apple-darwin*)
    case "$CFLAGS $CXXFLAGS $LDFLAGS" in
      *" -s "*|"-s "*|*" -s"|"-s")
         echo "warning: cannot strip libglade executables on this host"
         CFLAGS=`echo "$CFLAGS"|sed 's/\( -s\)* / /g;s/^-s //g;s/ -s$//g;s/^-s$//g'`
         CXXFLAGS=`echo "$CXXFLAGS"|sed 's/\( -s\)* / /g;s/^-s //g;s/ -s$//g;s/^-s$//g'`
         LDFLAGS=`echo "$LDFLAGS"|sed 's/\( -s\)* / /g;s/^-s //g;s/ -s$//g;s/^-s$//g'`
         ;;
    esac
    ;;
esac

# some extra flags
CXXFLAGS="$CFLAGS -fno-rtti -fno-exceptions"

AC_SUBST(CFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(CXXFLAGS)

# Output.
AC_OUTPUT

echo "Now, you can type 'make' and 'make install'."
