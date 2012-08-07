/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  28/05/06 20:38 - paths.c

  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

/*
	Manage paths to be multi-platform.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <glib.h>

#ifdef __WIN32__
#include <windows.h>
#endif

#include "paths.h"

// Let's setup some of the paths that are defined
GFMInstPaths inst_paths =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

/* GFM Installation Paths Initialization */
int paths_init(void)
{
	// Set Base Path
#ifndef __WIN32__
	inst_paths.base_dir = g_strconcat(SHARE_DIR, G_DIR_SEPARATOR_S, NULL);
#else
	HMODULE hModule;
	DWORD dWord;
	char *sBuffer;
	gchar *basename, *dirname;

	// Find the Path to the gfm.exe File!
	hModule = GetModuleHandle("gfm.exe");
	sBuffer = (char *)malloc(4096 * sizeof(char));
	dWord = GetModuleFileName(hModule, sBuffer, 4096);
	dirname = g_path_get_dirname(sBuffer);
	basename = g_path_get_basename(dirname);

  /*******************************************/
  // Will replace /target/bin with /target/share/gfm in MinGW/MSYS
  #define MINGW_REL "share\\gfm"
  if ((strlen(basename) == 3) && !g_strcasecmp(basename, "bin"))
  {
	  gchar *token;
	  dirname = g_realloc(dirname, strlen(dirname) + strlen(MINGW_REL) + 1);
	  token = dirname + strlen(dirname) - 3;
	  strcpy(token, MINGW_REL);
  }
  /********************************************/

	// Set the Base Directory
	inst_paths.base_dir = g_strconcat(dirname, "\\", NULL);
	
	// Free some stuff
	free(sBuffer);
	g_free(dirname);
	g_free(basename);
#endif
	
	// Set the rest of the paths
	inst_paths.help_dir = g_strconcat(inst_paths.base_dir, "help", G_DIR_SEPARATOR_S, NULL);
	inst_paths.pixmap_dir = g_strconcat(inst_paths.base_dir, "pixmaps", G_DIR_SEPARATOR_S, NULL);
	inst_paths.glade_dir = g_strconcat(inst_paths.base_dir, "glade", G_DIR_SEPARATOR_S, NULL);
	inst_paths.tmp_dir = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, NULL);
	inst_paths.home_dir = g_strconcat(g_get_user_data_dir(), G_DIR_SEPARATOR_S, NULL);

#ifdef ENABLE_NLS
#ifndef __WIN32__
	inst_paths.locale_dir = g_strconcat(LOCALEDIR, "/", NULL);
#else
	inst_paths.locale_dir = g_strconcat(inst_paths.base_dir, "locale\\",
					    NULL);
#endif
#endif

  // Return
  return 0;
}

/* Will return full path from executable to glade file given */
const char *paths_build_glade(const char *name)
{
      static gchar *gladepath = NULL;
      g_free(gladepath);

	  // Set new gladepath and return
      gladepath = g_strconcat(inst_paths.glade_dir, name, NULL);
      return gladepath;
}
