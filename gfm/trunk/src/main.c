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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#if WITH_KDE
#include "kde.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <locale.h>

#include "cmdline.h"
#include "gui.h"
#include "paths.h"
#include "file.h"
#include "splashscreen.h"
#include "support.h"
#include "tilibs.h"

int main(int argc, char *argv[])
{
    static gchar *icon_dir;

    /* Initialize GFM */
    paths_init();

    /* Init i18n support */
#ifdef ENABLE_NLS
    g_message("setlocale: %s\n", setlocale(LC_ALL, ""));
    g_message("bindtextdomain: %s\n", 
	    bindtextdomain(PACKAGE, inst_paths.locale_dir));
    bind_textdomain_codeset(PACKAGE, "UTF-8");
    g_message("textdomain: %s\n", textdomain(PACKAGE));
#endif

    /* Scan command line */
    cmdline_scan(&argc, &argv);

    /* Load GTK */
    gtk_init(&argc, &argv); // Loadup GTK+
    add_pixmap_directory(inst_paths.pixmap_dir); // Add Pixmap directory
    icon_dir = g_strconcat(inst_paths.base_dir, "icons/", NULL);
    add_pixmap_directory(icon_dir); // Add Icon Directory
    g_free(icon_dir);

    /* Load Splash Screen */
    splash_screen_start();

#if WITH_KDE
    splash_screen_message(_("Initializing KDE..."));
    sp_kde_init(argc, argv, "gfm", _("GFM"), VERSION, _("Group File Manager"), "Copyright (c) 2006-2007 Tyler Cassidy, Romain Lievin", "http://lpg.ticalc.org/prj_gfm/", "tilp-users@lists.sf.net");
    atexit(sp_kde_finish);
    // Not needed unless we want to add a DCOP interface.
    // g_timeout_add(26, sp_kde_process_qt_events, NULL);
#endif

    /* Checking for GUI Files */
    splash_screen_message(_("Checking for GUI files..."));
    glade_files_check();

    /* Load tilibs2 */
    splash_screen_message(_("Loading tilibs..."));
    load_tilibs(); // Load tilibs

    /* Launching GUI */
    splash_screen_message(_("Launching GUI..."));
    launch_gfmgui();
    splash_screen_delete(); // Delete Splash Screen

    /* Run into a loop! */
    gtk_main();
    
    /* Close tilibs */
    ticalcs_library_exit();
    tifiles_library_exit();

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
