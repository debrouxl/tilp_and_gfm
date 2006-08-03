/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  01/07/06 18:49 - config.c

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

#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "config.h"
#include "dialog.h"
#include "file.h"
#include "folder_tree.h"
#include "gfm.h"
#include "paths.h"

#define FTREE_SETTINGS "FTREE_SETTINGS"
#define SETTINGS "SETTINGS"

/* Setup Configuration Presets */
int config_presets(void)
{
    /* Set the defaults incase of no Config File */
    ftree_info.column = FTREE_SORT_NAME; // Sort by Name
    ftree_info.sort_order = 0; // Ascending Order
    settings.confirm = TRUE; // Confirm Deletions
    settings.show_all = FALSE; // Show only TI Files
    settings.cur_dir = inst_paths.home_dir; // Default to Home Dir
    settings.cur_file = "NULL"; // No File to Load

    // Return
    return 0;
}

/* Load Configuration File */
int config_load(void)
{
    char *save_file;
    GKeyFile *keyfile;
    gboolean ret_val;
    GError *error = NULL;

    // Get the Save File
    #ifdef __WIN32__
    save_file = g_strconcat(inst_paths.home_dir, "gfm.ini", NULL);
    #else
    save_file = g_strconcat(inst_paths.home_dir, ".gfmrc", NULL);
    #endif

    // Does the file exist?
    if (!file_exists(save_file))
    {
        g_free(save_file);
        return -1;
    }

    // Create Key File
    keyfile = g_key_file_new();

    // Try and load the Data
    ret_val = g_key_file_load_from_file(keyfile, save_file, G_KEY_FILE_NONE, &error);

    // Could not Configuration
    if (!ret_val)
    {
        g_free(save_file); // Free Save File Path
        g_key_file_free(keyfile); // Free Key File
        return -1;
    }

    // Load the Settings now
    // Folder Tree Settings
    ftree_info.sort_order = g_key_file_get_integer(keyfile, FTREE_SETTINGS, "sort_order", &error);
    ftree_info.column = g_key_file_get_integer(keyfile, FTREE_SETTINGS, "sort_column", &error);

    // Settings
    settings.confirm = g_key_file_get_boolean(keyfile, SETTINGS, "confirm", &error);
    settings.show_all = g_key_file_get_boolean(keyfile, SETTINGS, "show_all", &error);
    settings.cur_dir = g_key_file_get_string(keyfile, SETTINGS, "cur_dir", &error);
    settings.cur_file = g_key_file_get_string(keyfile, SETTINGS, "cur_file", &error);

    // Free some stuff
    g_free(save_file);
    g_key_file_free(keyfile);

    // Return
    return 0;
}

/* Save Configuration File */
int config_save(void)
{
    GKeyFile *keyfile;
    gchar *key_data;
    gchar *save_file;
    GError *error = NULL;
    FILE *f_handle;

    // Create the Key File
    keyfile = g_key_file_new();

    // Set GFM Info
    g_key_file_set_comment(keyfile, NULL, NULL,
		"# Config file for GFM\n" \
		"# Copyright (C) 2006 The TiLP Team <tilp-devel@lists.sf.net>\n" \
		"# Warning: any comments that you add to this file WILL be overwritten\n\n", &error);

    // Set Sort Order and Column
    g_key_file_set_integer(keyfile, FTREE_SETTINGS, "sort_order", ftree_info.sort_order); // Sort Order
    g_key_file_set_comment(keyfile, FTREE_SETTINGS, "sort_order", " Which way to sort files: 0 asc, 1 desc", &error);

    g_key_file_set_integer(keyfile, FTREE_SETTINGS, "sort_column", ftree_info.column); // Column
    g_key_file_set_comment(keyfile, FTREE_SETTINGS, "sort_column", "\n Which Column to sort by: 100 Name, 101 Type, 102 Size, 103 Date", &error);

    // Set Confirm, Show All
    g_key_file_set_boolean(keyfile, SETTINGS, "confirm", settings.confirm); // Confirm
    g_key_file_set_comment(keyfile, SETTINGS, "confirm", " Confirm Deletions?", &error);

    g_key_file_set_boolean(keyfile, SETTINGS, "show_all", settings.show_all); // Show All
    g_key_file_set_comment(keyfile, SETTINGS, "show_all", "\n Show all files?", &error);

    // Set Current Directory/File
    g_key_file_set_string(keyfile, SETTINGS, "cur_dir", settings.cur_dir); // Directory
    g_key_file_set_comment(keyfile, SETTINGS, "cur_dir", "\n Current Working Directory", &error);

    g_key_file_set_string(keyfile, SETTINGS, "cur_file", settings.cur_file); // File
    g_key_file_set_comment(keyfile, SETTINGS, "cur_file", "\n Last Group File Open", &error);

    // Convert to String
    key_data = g_key_file_to_data(keyfile, NULL, &error);

    // Get the Save File Path
    #ifdef __WIN32__
    save_file = g_strconcat(inst_paths.home_dir, "gfm.ini", NULL);
    #else
    save_file = g_strconcat(inst_paths.home_dir, ".gfmrc", NULL);
    #endif

    // Save to File
    f_handle = fopen(save_file, "wt");
    if (f_handle == NULL)
    {
        msgbox_error("Could not save Configuration File!");
        return -1;
    }

    // Save Contents
    fwrite(key_data, strlen(key_data), 1, f_handle);
    fclose(f_handle); // Close handle now

    // Free some stuff
    g_free(key_data); // Key Data Freed
    g_free(save_file); // Save File Path Freed
    g_key_file_free(keyfile); // Key File Freed

    return 0;
}
