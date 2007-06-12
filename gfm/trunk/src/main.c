/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  28/05/06 20:28 - main.c

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#include <stdio.h>
#include <gtk/gtk.h>

#include "cmdline.h"
#include "gui.h"
#include "paths.h"
#include "file.h"
#include "splashscreen.h"
#include "support.h"
#include "tilibs.h"

/* Main Function */
int main(int argc, char *argv[])
{
    static gchar *icon_dir;

    /* Initialize Group File Manager */
    gfm_cmdline(&argc, &argv);
    gfm_paths_init();

    /* Load GTK */
    gtk_init(&argc, &argv); // Loadup GTK+
    add_pixmap_directory(inst_paths.pixmap_dir); // Add Pixmap directory
    icon_dir = g_strconcat(inst_paths.base_dir, "icons/", NULL);
    add_pixmap_directory(icon_dir); // Add Icon Directory
    g_free(icon_dir);

    /* Load Splash Screen */
    splash_screen_start();

    /* Checking for GUI Files */
    splash_screen_message("Checking for GUI files...");
    glade_files_check();

    /* Load tilibs2 */
    splash_screen_message("Loading tilibs2...");
    load_tilibs(); // Load tilibs

    /* Launching GUI */
    splash_screen_message("Launching GUI...");
    launch_gfmgui();
    splash_screen_delete(); // Delete Splash Screen

    /* Run into a loop! */
    gtk_main();
    
    /* Close tilibs */
    tifiles_library_exit(); // libtifiles2

    /* Done */
    return 0;
}

#if defined(__WIN32__) && defined(_WINDOWS)

#ifdef __MINGW32__
#include <windows.h>
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return main(__argc, __argv);
}
#endif
