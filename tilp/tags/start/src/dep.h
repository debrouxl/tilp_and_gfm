/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
  This file include some dependant OS headers files.
  There are few things because the GLIb is used finally.
*/

#ifndef DEP_H
#define DEP_H

#include "intl.h"		// GNU Internationalization library

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef HAVE_DIRENT_H
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <unistd.h>
#else
# if defined(__WIN32__)
#  include "win32/pwd.h"
#  include "win32/grp.h"
#  include "win32/unistd.h"
#  include "win32/dirent.h"
# endif
#endif

#if defined(HAVE_TILP_TYPEDEFS_H) && !defined(__MACOSX__)
# include <tilp/cabl_int.h>
# include <tilp/calc_int.h>
# include <tilp/defsxx.h>
#elif defined(__MACOSX__)
#include <libticables/cabl_int.h>
#include <libticalcs/calc_int.h>
#include <libticalcs/defsxx.h>
#elif defined(__WIN32__)
# include "cabl_int.h"
# include "calc_int.h"
# include "defsxx.h"
#else
# include "cabl/cabl_int.h"
# include "calc/calc_int.h"
# include "calc/defsxx.h"
#endif

#ifdef HAVE_LIBTIFFEP
# define HAVE_TIFFEP
# if defined(__LINUX__)
#  include <tiffep/tiffep.h>
# elif defined(__WIN32__)
#  include "tiffep_project/src/tiffep.h"
# endif
#endif

#ifndef __MACOSX__
#include <glib.h> // for all platforms
#else
#include <glib/glib.h>
#endif /* !__MACOSX__ */

#ifdef GTK				// Linux or Win32 with GTK
#include <gtk/gtk.h>
#endif

#if defined(__WIN32__)	// Win32 (GTK or MFC/VCL)
# include <direct.h>
# include <process.h>
# include <io.h>
#endif

#if defined(__WIN32__)
# define snprintf	_snprintf
# define popen		_popen
# define pclose	        _pclose
#endif

#endif // DEP_H

/*
 * To get prototypes for the following POSIXish functions, you have to
 * include the indicated non-POSIX headers. The functions are defined
 * in OLDNAMES.LIB (MSVC) or -lmoldname-msvc (mingw32).
 *
 * getcwd: <direct.h> (MSVC), <io.h> (mingw32)
 * getpid: <process.h>
 * access: <io.h>
 * unlink: <stdio.h> or <io.h>
 * open, read, write, lseek, close: <io.h>
 * rmdir: <direct.h>
 * pipe: <direct.h>
 */
