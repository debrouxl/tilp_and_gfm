/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
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

/* Todo List: - Leave, its easy to access in Dev-C++
   Computer (Folder) Tree:
   -dragging (folder_drag.c/h)
     -Group File into the Group Tree and opens Group File
     -TI File onto TI File in FOlder Tree to merge into Group File
   -Enter Key on selection in folder tree to open file in Group Tree.
   -Complete the Right Click Menu Items (I will get these)
   -Current Folder Label, folders can get long, and they move the slider, so lets cut them with "..." in the middle ;)
   -All GUI Callback functions for tree in gui.c

   Group File Tree:
   -Init (program in group_tree.c, gtree_sort.c, [group_tree.h]) and call in gui.c where folder
    tree is called (~line 72)
   -Dragging (group_drag.c/h)
     -File onto Folder Tree to extract
     -File onto TI File in Folder Tree to merge/create Group File
     -File from Folder Tree into Group Tree to add to Group File
   -Sorting (code in gtree_sort.c) and implement
   -Right Click to open that menu and get items coded (in menu.c,menu.h [maybe have two files for different tree menus]      would be fine I think)
   -Update Labels under Group Tree (Groupfile Size, Num of files in group)
    (pointers to labels in gfm_widget in gui.h struct)
   -Double Click (Rename Group File)

   Other:
   -Buttons at top of Program (New, MkDir, Refresh, Delete || Add, Rename, Delete, Refresh, Help)
    all need coded (nothing done for) callback functions in gui.c
   -input dialog in dialogs.glade needs to be implemented into dialog.c/h
   -progress bars need to be done in pbar.c/.h
   -man page dialog needs to be implemented
   -html launcher needs to be done
   -Changelog/Release Dialog (like on on first time TiLP is booted)
   -Options Dialog (options.c/h) (I have the config file handled in config.c/h)

   Notes:
   -file filtering in folder tree?? check the compat part...
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#include <stdio.h>
#include <gtk/gtk.h>

#include "config.h"
#include "cmdline.h"
#include "file.h"
#include "folder_tree.h"
#include "gfm.h"
#include "paths.h"
#include "splashscreen.h"
#include "tilibs.h"

/* Settings Structure */
SettingsStruct settings;

/* Main Function */
int main(int argc, char *argv[])
{
    static gchar *icon_dir;

    /* Initialize Group File Manager */
    gfm_cmdline(); // Clear warnings on Command line
    gfm_paths_init(); // Setup paths for executable

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
    tifiles_library_init(); // Load tifiles2

    /* Load Settings */
    splash_screen_message("Loading Settings...");
    config_presets(); // Load the Defaults before the User Preferences
    config_load(); // Load User Preferences now
    gfm_change_cwd(settings.cur_dir); // Set the CWD at boot!
    // Or it will start off at where the binary is...

    /* Launching GUI */
    splash_screen_message("Launching GUI...");
    launch_gfmgui();
    splash_screen_delete(); // Delete Splash Screen

    /* Run into a loop! */
    gtk_main();

    /* Save Settings */
    config_save();

    /* Close tilibs2 */
    tifiles_library_exit(); // tifiles2

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
