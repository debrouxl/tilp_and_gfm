/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  16/07/06 17:15 - menu.c

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
#include <direct.h> // _chdrive()
#endif

#include <memory.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "dialog.h"
#include "file.h"
#include "folder_tree.h"
#include "ftree_menu.h"
#include "gfm.h"
#include "gui.h"
#include "paths.h"
#include "support.h"

static gboolean confirm_bypass;

/* Change Drive Feature (Windows) */
#ifdef __WIN32__
static int windows_drive_change(char drive_letter)
{
	gchar *s;

  // Change drive and copy it.
  snprintf(settings.cur_dir, 8, "%c:\\", (char)drive_letter);
  s = g_strdup(settings.cur_dir);

  // Change Drive
	if (gfm_change_cwd(s) == -1)
	    msgbox_error("Could not change drive!");

  // Free String
	g_free(s);

  // Done
	return 0;
}

/* Change Drive Activator */
static void gfm_change_drive_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	windows_drive_change((char)GPOINTER_TO_INT(user_data));

	// Refresh Folder Tree
	folder_tree_refresh();
}

static void set_drives(GtkWidget* widget, gpointer user_data)
{
	GtkWidget *menu = GTK_WIDGET(user_data);
	GtkWidget *change_drive;
	GtkWidget *change_drive_menu;
	GtkWidget *c_drive;
	int drive, curdrive;
	gchar buffer[8];
	gint available_drives[27];	// A..Z -> 26 letters

	change_drive = gtk_menu_item_new_with_label("Change drive");
	g_object_set_data_full(G_OBJECT(menu), "change_drive",
			       gtk_widget_ref(change_drive),
			       (GDestroyNotify)gtk_widget_unref);
	gtk_widget_show(change_drive);

	gtk_container_add(GTK_CONTAINER(menu), change_drive);
	change_drive_menu = gtk_menu_new();
	g_object_set_data_full(G_OBJECT(menu), "change_drive_menu",
			       gtk_widget_ref(change_drive_menu),
			       (GDestroyNotify)gtk_widget_unref);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(change_drive), change_drive_menu);

	curdrive = _getdrive();
	for (drive = 1; drive <= 26; drive++)
		available_drives[drive] = 0;

	for (drive = 3; drive <= 26; drive++)
	{
		if (!_chdrive(drive))
		{
			g_snprintf(buffer, 8, "%c:", drive + 'A' - 1);
			available_drives[drive] = drive + 'A' - 1;

			c_drive = gtk_menu_item_new_with_label(buffer);
			g_object_set_data_full(G_OBJECT(menu), "c_drive",
					       gtk_widget_ref(c_drive),
					       (GDestroyNotify)gtk_widget_unref);
			gtk_widget_show(c_drive);

			gtk_container_add(GTK_CONTAINER(change_drive_menu),
					  c_drive);
			g_signal_connect((gpointer)c_drive, "activate",
					   G_CALLBACK(gfm_change_drive_activate),
					   GINT_TO_POINTER(available_drives[drive]));
		}
	}
	_chdrive(curdrive);
}
#endif

/* Load Menu Function */
GtkWidget *create_folder_menu(void)
{
	GladeXML *xml;
	GtkWidget *menu;
	gpointer data;
	
	xml = glade_xml_new(gfm_paths_build_glade("gfm.glade"), "folder_menu", NULL);

	// Glade File Error
  if (!xml)
	g_error("GUI loading failed !\n");

	// Connect Signals
	glade_xml_signal_autoconnect(xml);
  
	// Activate the Items
	data = glade_xml_get_widget(xml, "show_all_files1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), settings.show_all);
	
	confirm_bypass = TRUE;
	data = glade_xml_get_widget(xml, "confirm_delete1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), settings.confirm);
	confirm_bypass = FALSE;

  // Load the Menu Now
	menu = glade_xml_get_widget(xml, "folder_menu");

  // Drive Letters if we are a Windows User
  #ifdef __WIN32__
  set_drives(menu, menu);
  #endif

  // Return the Menu
	return menu;
}

/* Callback Functions */
/* Show All Files Checkbox */
GLADE_CB void on_show_all_files1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	  // Update the Setting
	  settings.show_all = GTK_CHECK_MENU_ITEM(menuitem)->active;
	  
		// Refresh the Folder Tree
	  folder_tree_refresh();
}

/* Confirm Delete Checkbox */
GLADE_CB void on_confirm_delete1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	  // Run the Warning
	  if (confirm_bypass == FALSE && GTK_CHECK_MENU_ITEM(menuitem)->active == FALSE)
			if (msgbox_two(MSGBOX_CONTINUE, "Disabling this feature will not warn you when you are about to delete files!") == MSGBOX_NO)
				return;
	
	  // Update the Setting
	  settings.confirm = GTK_CHECK_MENU_ITEM(menuitem)->active;
}

/* Cut File */
GLADE_CB void on_cut2_activate(GtkMenuItem *menuitem, gpointer user_data)
{

	// Cut
	if (ftree_info.selected_files == NULL)
			return;

		ftree_info.working_act = WORKING_ACT_CUT; // Cutting Files
}

/* Copy File */
GLADE_CB void on_copy2_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	  // Copy
		if (ftree_info.selected_files == NULL)
			return;

		ftree_info.working_act = WORKING_ACT_COPY; // Copying Files
}

/* Paste File */
GLADE_CB void on_paste1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
		GList *work_list;
		int process;
		gchar *src, *dst;

		// Is there anything to do?
		if (ftree_info.selected_files == NULL)
			return; // No
 
		// Lets now go through the list
		for(work_list=ftree_info.selected_files; work_list!=NULL; work_list=work_list->next)
		{
			// Lets setup src and dst
			src = (gchar *)work_list->data;
			dst = g_strconcat(settings.cur_dir, G_DIR_SEPARATOR_S, g_basename(src), NULL);
			
			// Now lets process our action.
			// Moving Files
			if (ftree_info.working_act == WORKING_ACT_CUT)
			  process = gfm_move_file(src, dst);
					
			// Copying Files
			else
				process = gfm_copy_file(src, dst);
			
			// Free Strings
			g_free(src); // Source String
			g_free(dst); // Destination File
			
			// Check for Errors
			if (process < 0 && msgbox_two(MSGBOX_CONTINUE, "A File Transfer Error Occured! Continue?") != MSGBOX_YES)
			{
				// Have a nice Quit Message
				if (ftree_info.working_act == WORKING_ACT_CUT)
					dst = "File Move Cancelled!";
				else
					dst = "File Copy Cancelled!";
				msgbox_one(MSGBOX_INFO, dst);
				
				// Clear Working Action
				ftree_info.working_act = NULL;
				
				// Return
				return;
			}
		}
		
		// Clear Working Action
		ftree_info.working_act = NULL;
		
		// Lets refresh the Folder Tree!
		folder_tree_refresh();
}

/* Rename File */
GLADE_CB void on_rename2_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	gchar *new_path;

	// Check to see if there are more than one selection
	if (ftree_info.selected_files->next != NULL)
	{
		msgbox_one(MSGBOX_INFO, "You can only rename one file at a time.");
		return;
	}
	
	// Get the path to the new file
	new_path = gfm_repath_file(ftree_info.selected_files->data);
	
	// Is the value null?
	if (new_path == NULL)
	{
		msgbox_two(MSGBOX_INFO, "File not renamed.");
		return;
	}
	
	// Rename file.
	gfm_rename_file(ftree_info.selected_files->data, new_path);
	
	// Refresh Folder Tree
	folder_tree_refresh();
}

/* Delete File */
GLADE_CB void on_delete2_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GList *del_queue;
	
	// Shall we confirm?
	if (settings.confirm && msgbox_two(MSGBOX_YESNO, "Once you delete files they will be gone forever! Continue?") == MSGBOX_NO)
		return;
	
	// Delete Files
	for(del_queue=ftree_info.selected_files; del_queue!=NULL; del_queue=del_queue->next)
		gfm_delete_file(del_queue->data);
	
	// Refresh Folder Tree
	folder_tree_refresh();
}

/* Make Directory */
GLADE_CB void on_new_folder1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	gchar *input_value;
	gchar *dirname;
	gsize bw, br;
	
	// Get Directory name
	input_value = msgbox_input("Make Directory", NULL, "Please enter in the name for the directory you wish to create.");
	
	if (input_value == NULL)
	{
		msgbox_error("Directory creation canceled!");
		return;
	}
	
	// Convert from UTF-8 to GLib file name encoding
	dirname = g_filename_from_utf8(input_value, -1, &br, &bw, NULL);
	
	if (dirname == NULL)
	{
		msgbox_error("An error has occured creating the Directory!");
		return;
	}
	
	// Create the Folder
	gfm_mkdir(dirname);
	g_free(dirname); // Free dirname
	
	// Refresh the Folder Tree
	folder_tree_refresh();
}

/* Select All Files */
GLADE_CB void on_select_all1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.comp_tree);
	GtkTreeSelection *sel;
	
	// Select all!
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_select_all(sel);
}

/* Unselect All Files */
GLADE_CB void on_unselect_all1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.comp_tree);
	GtkTreeSelection *sel;
	
	// Unselect All!
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_unselect_all(sel);
}

/* Goto Parent Directory */
GLADE_CB void on_go_to_parent_directory1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	// Go up one directory!
	gfm_change_cwd("..");
	
	// Update the Current Directory in GFM
	g_free(settings.cur_dir);
	settings.cur_dir = g_get_current_dir();
	
	// Refresh the Folder Tree.
	folder_tree_refresh();
}

/* Refresh Folder Tree */
GLADE_CB void on_refresh4_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	// So Simple :D
	folder_tree_refresh();
}

/* Next */