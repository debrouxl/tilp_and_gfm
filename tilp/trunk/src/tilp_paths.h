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

/*
	Platform independant paths
*/

#ifndef __TILP_PATHS__
#define __TILP_PATHS__

#include <stdio.h>

/* Paths */
#if defined(__LINUX__) || defined(__BSD__)
# define INI_FILE  "/.tilp"
#elif defined(__WIN32__)
# define INI_FILE  "tilp.ini"
#endif

/* Temporary filenames (used by cb_calc.c) */
#define TMPFILE_BACKUP   "tilp.backup"
#define TMPFILE_ROMDUMP  "tilp.romdump"
#define TMPFILE_GROUP    "tilp.group"
#define TMPFILE_FLASHAPP "tilp.flashapp"

#ifndef __MACOSX__
typedef struct 
{
    gchar *base_dir;		// base directory
    gchar *locale_dir;		// locale
    gchar *manpage_dir;		// manpages
    gchar *help_dir;		// help files
    gchar *pixmap_dir;		// pixmaps
    gchar *icon_dir;		// icons
    gchar *glade_dir;		// directory of files for Glade
    gchar *home_dir;		// $HOME
} TilpInstPaths;
#endif

#ifndef __MACOSX__
extern TilpInstPaths	inst_paths;
#endif /* !__MACOSX__ */

int tilp_paths_init(void);
const char *tilp_paths_build_glade(const char *name);

#endif
