/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
	Platform independant paths
*/

#ifndef __TILP_PATHS__
#define __TILP_PATHS__

#include <stdio.h>

/* Temporary filenames (used by cb_calc.c) */
#define TMPFILE_BACKUP   "tilp.backup"
#define TMPFILE_ROMDUMP  "tilp.romdump"
#define TMPFILE_GROUP    "tilp.group"
#define TMPFILE_FLASHAPP "tilp.flashapp"
#define TMPFILE_TIGROUP	 "tilp.tigroup"

typedef struct 
{
    gchar *base_dir;		// base directory
    gchar *locale_dir;		// locale
    gchar *manpage_dir;		// manpages
    gchar *help_dir;		// help files
    gchar *pixmap_dir;		// pixmaps
    gchar *icon_dir;		// icons
    gchar *glade_dir;		// directory of files for Glade
    gchar *builder_dir;		// $HOME
    gchar *home_dir;		// $HOME
} TilpInstPaths;

extern TilpInstPaths	inst_paths;

int tilp_paths_init(void);
const char *tilp_paths_build_glade(const char *name);
const char *tilp_paths_build_builder(const char *name);

#endif
