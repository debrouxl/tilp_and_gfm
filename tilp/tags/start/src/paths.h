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

#ifndef PATHS_H
#define PATHS_H


/* Some definitions for the Windows port */
#if defined(__UNIX__)
# define CWD_FILE "/.tilp_cwd"
# define RC_FILE  "/.tilp"
# define IO_FILE  "/etc/tilp.conf"
# define ST_FILE  "/.tilpv"
# define PLUGINS_DIR "/usr/lib/ti/plugins/"
#elif defined(__WIN32__)
# define CWD_FILE "tilp.cwd"
# define RC_FILE  "tilp.ini" // local path
# define IO_FILE  "tilp.conf"
# define ST_FILE  "tilp.version"
# define PLUGINS_DIR "\\plugins\\"
#endif

#if defined(__WIN32__)
#  define SHARE_DIR "" // local path
#endif

#endif

