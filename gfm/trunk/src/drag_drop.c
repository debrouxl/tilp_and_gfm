/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  27/09/06 19:45 - drag_drop.c

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

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "dialog.h"
#include "drag_drop.h"
#include "folder_tree.h"
#include "gfm.h"
#include "group_file.h"
#include "gui.h"
#include "support.h"
#include "tilibs.h"

// DND Structure Info
DNDStruct DNDInfo;

/* Enumerations for Target Entries */
enum { TARGET_STRING, TARGET_ROOTWIN, TARGET_LEFT, TARGET_RIGHT };

/* Target Entries */
static GtkTargetEntry TargetEntry1[] = 
{
  {"folder_tree", 0, TARGET_STRING},
  {"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};
static GtkTargetEntry TargetEntry2[] =
{
  {"group_tree", 0, TARGET_STRING},
  {"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};

/* Initialize Drag & Drop */
int drag_drop_init(void)
{
  // Setup Drag and Drop from Folder Tree to Group Tree/Folder Tree
  gtk_drag_source_set(gfm_widget.comp_tree, GDK_BUTTON1_MASK, TargetEntry1, 1, GDK_ACTION_COPY);
  gtk_drag_dest_set(gfm_widget.group_tree, GTK_DEST_DEFAULT_ALL, TargetEntry1, 1, GDK_ACTION_COPY);
  
  // Group Tree => Folder Tree
  gtk_drag_source_set(gfm_widget.group_tree, GDK_BUTTON1_MASK, TargetEntry2, 1, GDK_ACTION_COPY | GDK_ACTION_MOVE);
  gtk_drag_dest_set(gfm_widget.comp_tree, GTK_DEST_DEFAULT_ALL, TargetEntry2, 1, GDK_ACTION_COPY | GDK_ACTION_MOVE);
}

/* Drag Data Begin on Folder Tree - When Send begins. */
GLADE_CB void on_folder_tree_drag_begin(GtkWidget *widget, GdkDragContext *drag_context, gpointer user_data)
{
  // nothing I am aware of.
}

/* Drag Data Get on Folder Tree - When Sent over to Group Tree */
GLADE_CB void on_folder_tree_drag_data_get(GtkWidget *widget, GdkDragContext *drag_context, GtkSelectionData *data,
			                   guint info, guint time, gpointer user_data)
{
  // Activate the Receiver Handler (on_group_tree_drag_data_received)
  gchar *name = "foo_bar";
  gtk_selection_data_set(data, data->target, 8, name, strlen(name)); 
}

/* Drag Data Received on Group Tree */
GLADE_CB void on_group_tree_drag_data_received(GtkWidget *widget, GdkDragContext *drag_context,
                                               gint x, gint y, GtkSelectionData *data,
                                               guint info, guint time, gpointer user_data)
{
  GList *select_list;
  GList *add_list;
  
  // Test to see if anything is selected.
  if (ftree_info.selected_files == NULL)
    return; // Nothing
  
  // Search through file(s) and pick out TI Files.
  add_list = NULL;
  for(select_list=ftree_info.selected_files; select_list!=NULL; select_list=select_list->next)
  {
    if (tifiles_file_is_ti(select_list->data))
      add_list = g_list_insert(add_list, select_list->data, -1);
  }
  
  // Do we have any files to add now?
  if (add_list == NULL)
  {
    msgbox_error("The file(s) you tried adding to the Group File are not TI Compatible!");
    return;
  }
  
  // Do we have group file open?
  if (settings.cur_file == NULL)
  {
    // Open TI Group File
    if (add_list->next == NULL && tifiles_file_is_tigroup(add_list->data))
    {
      tigfile_open(add_list->data);
      return; // Added to Tree, settings.cur_file dealt with.
    }
    
    // Open Group File
    else if (add_list->next == NULL && tifiles_file_is_group(add_list->data))
    {
      // gfile_open(add_list->data);
      // return;
    }
    
    // Create Group File
    else
    {
      if (tigfile_create(TRUE))
        return; // Error, returning
      else
        if (tigfile_open(DNDInfo.file_path))
          return; // Error
    }
  }
  
  // Add to (TI)/group file routines & refresh
  // open routines set settings.cur_file && settings.cur_filetype
  
  ////// If TI Group File(s), Split Files out into /tmp and add individually.
 
  
  printf("G-Received\n");
  //- Parse for Multiple Files
  //-If one file && not tifile- error
  //- check to see if TI File.
  // Then add to Group Tree Queue in group_tree.h structure (still have to make)
  // Than add to group file (code in group_file.c)
}

/* Drag Data Begin on Group Tree */
GLADE_CB void on_group_tree_drag_begin(GtkWidget *widget, GdkDragContext *drag_context, gpointer user_data)
{
  // code - nothing I think
}

/* Drag Data Get on Group Tree - when sent to Folder Tree */
GLADE_CB void on_group_tree_drag_data_get(GtkWidget *widget, GdkDragContext *drag_context, GtkSelectionData *data,
                                          guint info, guint time, gpointer user_data)
{
  // Activate the Receiver Handler (on_folder_tree_drag_data_received)
  gchar *name = "foo_bar";
  gtk_selection_data_set(data, data->target, 8, name, strlen(name)); 
}

/* Drag Data Received on Folder Tree */
GLADE_CB void on_folder_tree_drag_data_received(GtkWidget *widget, GdkDragContext *drag_context,
                                                gint x, gint y, GtkSelectionData *data,
                                                guint info, guint time, gpointer user_data)
{
  printf("Received\n");
  // Find appropiate extension
  // If file exists, ask to overwrite or rename or cancel
}

