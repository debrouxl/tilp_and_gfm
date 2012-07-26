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
	Initialization of portable paths
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef __WIN32__
#include <windows.h>
#endif

#include <glib.h>
#include <glib/gstdio.h>

#include "tilp_core.h"

TilpInstPaths inst_paths = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

/*
  Called by TiLP at startup for initializing platform dependant paths.
*/
#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
static void init_linux_paths(void)
{
	inst_paths.base_dir =
	    g_strconcat(SHARE_DIR, G_DIR_SEPARATOR_S, NULL);
	inst_paths.pixmap_dir =
	    g_strconcat(inst_paths.base_dir, "pixmaps/", NULL);
	inst_paths.icon_dir =
	    g_strconcat(inst_paths.base_dir, "icons/", NULL);
	inst_paths.help_dir =
	    g_strconcat(inst_paths.base_dir, "help/", NULL);
	inst_paths.manpage_dir = 
            g_strconcat(inst_paths.base_dir, "", NULL);
	inst_paths.glade_dir =
	    g_strconcat(inst_paths.base_dir, "glade/", NULL);
	inst_paths.builder_dir =
	    g_strconcat(inst_paths.base_dir, "builder/", NULL);
	inst_paths.home_dir =
		g_strdup(g_get_home_dir());

#ifdef ENABLE_NLS
	inst_paths.locale_dir = g_strconcat(LOCALEDIR, "/", NULL);
#endif				/*  */
}
#endif				/*  */

#ifdef __WIN32__
static void init_win32_paths(void)
{
	char *home_dir = NULL;
	HMODULE hModule;
	DWORD dWord;
	char *dirname;
	char *sBuffer;

	// Init the path for the Windows version by getting the 
	// executable location.
	hModule = GetModuleHandle("tilp.exe");
	sBuffer = (char *) malloc(4096 * sizeof(char));
	dWord = GetModuleFileName(hModule, sBuffer, 4096);
    dirname = g_dirname(sBuffer);
	
    // MinGW Option, allows Windows Users to run on a Linux File Hierarhcy
	#ifdef __MINGW32__
	  #define MINGW_REL "share\\tilp2"
	  
	  char *basename;
	  basename = g_path_get_basename(dirname);
	  
      // Will replace /target/bin with /target/share/tilp2 in MinGW/MSYS
      if ((strlen(basename) == 3) && !g_strcasecmp(basename, "bin"))
      {
          gchar *token;
          dirname = g_realloc(dirname, strlen(dirname) + strlen(MINGW_REL) + 1);
          token = dirname + strlen(dirname) - 3;
          strcpy(token, MINGW_REL);
      }
    #endif
    
    inst_paths.base_dir = g_strconcat(dirname, "\\", NULL);
	g_free(dirname);
	free(sBuffer);

	inst_paths.pixmap_dir =
	    g_strconcat(inst_paths.base_dir, "pixmaps\\", NULL);
	inst_paths.icon_dir =
	    g_strconcat(inst_paths.base_dir, "icons\\", NULL);
	inst_paths.help_dir =
	    g_strconcat(inst_paths.base_dir, "help\\", NULL);
	inst_paths.manpage_dir =
	    g_strconcat(inst_paths.base_dir, "", NULL);
	inst_paths.glade_dir =
	    g_strconcat(inst_paths.base_dir, "glade\\", NULL);
	inst_paths.builder_dir =
	    g_strconcat(inst_paths.base_dir, "builder\\", NULL);
	#ifdef __MINGW32__
	inst_paths.home_dir = g_get_current_dir();
	#else
	if((g_win32_get_windows_version() & 255) > 5)
	{
		// Windows Vista
		inst_paths.home_dir = 
			g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, "Documents", G_DIR_SEPARATOR_S, _("My TI Files"), NULL);
		g_mkdir(inst_paths.home_dir, 0);
	}
	else
	{
		// Windows XP
		inst_paths.home_dir = g_strconcat(inst_paths.base_dir, "My TI files\\", NULL);
		g_mkdir(inst_paths.home_dir, 0);
	}
	#endif

#ifdef ENABLE_NLS
	inst_paths.locale_dir =
	    g_strconcat(inst_paths.base_dir, "locale\\", NULL);
#endif				/*  */
}
#endif				/*  */

int tilp_paths_init(void)
{

#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
	init_linux_paths();

#elif defined(__WIN32__)
	init_win32_paths();

#endif				/*  */
	return 0;
}

const char *tilp_paths_build_glade(const char *name)
{
	static char *path = NULL;

	g_free(path);
	path = g_strconcat(inst_paths.glade_dir, name, NULL);

	return path;
}

const char *tilp_paths_build_builder(const char *name)
{
	static char *path = NULL;

	g_free(path);
	path = g_strconcat(inst_paths.builder_dir, name, NULL);

	return path;
}
