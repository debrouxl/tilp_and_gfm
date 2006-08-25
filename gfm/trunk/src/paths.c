/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
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
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <glib.h>

#ifdef __WIN32__
#include <windows.h>
#endif

#include "paths.h"

// Lets setup some of the paths that are definate
GFMInstPaths inst_paths =
{
    "",
    "\\help",
    "\\pixmaps",
    "\\glade",
    NULL,
    NULL
};

/* GFM Installation Paths Initialization */
int gfm_paths_init(void)
{
    // Linux/BSD
    #if defined(__LINUX__) || defined(__BSD__)
       inst_paths.base_dir = g_strconcat(SHARE_DIR, G_DIR_SEPARATOR_S, NULL); // Base Directory
       inst_paths.help_dir = g_strconcat(inst_paths.base_dir, "help/", NULL); // Help Directory
       inst_paths.pixmap_dir = g_strconcat(inst_paths.base_dir, "pixmaps/", NULL); // Pixmaps Directory
       inst_paths.glade_dir = g_strconcat(inst_paths.base_dir, "glade/", NULL); // Glade Directory
       inst_paths.tmp_dir = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, NULL); // Temporary Directory
       inst_paths.home_dir = g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, NULL); // Home Directory
    #endif // End of Linux/BSD

    // Windows!
    #ifdef __WIN32__
       HMODULE hModule;
       DWORD dWord;
       char *sBuffer;
       gchar *dirname, *basename;

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
       free(sBuffer);
       g_free(dirname);
       g_free(basename);

       // Set the Rest
       inst_paths.help_dir = g_strconcat(inst_paths.base_dir, "help\\", NULL); // Help Directory
       inst_paths.pixmap_dir = g_strconcat(inst_paths.base_dir, "pixmaps\\", NULL); // Pixmaps Directory
       inst_paths.glade_dir = g_strconcat(inst_paths.base_dir, "glade\\", NULL); // Glade Directory
       inst_paths.tmp_dir = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, NULL); // Temporary Directory
       inst_paths.home_dir = g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, NULL); // Home Directory
    #endif // End of Windows

    // Return
    return 0;
}

/* Will return full path from executable to glade file given */
const char *gfm_paths_build_glade(const char *name)
{
      static gchar *gladepath = NULL;
      g_free(gladepath);

      gladepath = g_strconcat(inst_paths.glade_dir, name, NULL);
      return gladepath;
}
