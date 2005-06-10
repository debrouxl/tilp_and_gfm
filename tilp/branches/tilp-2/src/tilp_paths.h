/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

#include <stdio.h>

/* in tilp_printl.c */
const gchar * tilp_get_logfile (void);
FILE * tilp_open_log (const char *mode);

/* Paths */
#if defined(__LINUX__) || defined(__BSD__)
# define INI_FILE  "/.tilp"
# define REG_FILE "tilp.registry"
# define LOG_FILE tilp_get_logfile()
#elif defined(__WIN32__)
# define INI_FILE  "tilp.ini"
# define REG_FILE "tilp.registry"
# define LOG_FILE tilp_get_logfile()
#endif

/* Temporary filenames (used by cb_calc.c) */
#define TMPFILE_BACKUP   "tilp.backup"
#define TMPFILE_ROMDUMP  "tilp.romdump"
#define TMPFILE_GROUP    "tilp.group"
#define TMPFILE_FLASHAPP "tilp.flashapp"

#endif
