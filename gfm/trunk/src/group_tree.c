/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  04/10/06 19:56 - gtree.c

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "dialog.h"
#include "group_tree.h"
#include "gtree_menu.h"
#include "gfm.h"
#include "gui.h"
#include "labels.h"
#include "support.h"
#include "tilibs.h"

// Keep this numbered, because ordering may be messed up when running with
// column2index and the switch that uses these as the cases
enum { COLUMN_ICON=0, COLUMN_NAME=1, COLUMN_TYPE=2, COLUMN_SIZE=3,
       COLUMN_DATA=4 };

#define GLIST_NCOLS (5) // 5 columns
#define GLIST_NVCOLS (4) // 4 viewable columns

static GtkListStore *list;

// Post information about Group Tree
GroupTreeData gtree_info;

/* Column Clicked Function */
static void group_tree_column_clicked(GtkTreeViewColumn *column, gpointer user_data)
{

  // code

}

/* Selection Selected */
static void group_tree_selection_changed(GtkTreeSelection *selection, gpointer user_data)
{

  // code

}

/* Selection Test Function */
static gboolean select_func(GtkTreeSelection *selection, GtkTreeModel *model,
			    GtkTreePath *path, gboolean path_currently_selected,
			    gpointer data)
{
  GtkTreeIter iter;
  FileEntry *fe;

  gtk_tree_model_get_iter(model, &iter, path);
  gtk_tree_model_get(model, &iter, COLUMN_DATA, &fe, -1);
  
  // Return  
  return TRUE;
}

/* Group Tree Init */
int group_tree_init(void)
{
  GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.group_tree);
  GtkTreeModel *model = GTK_TREE_MODEL(list);
  GtkCellRenderer *renderer;
  GtkTreeSelection *selection;
  gint i;
	
  // Setup the List
  list = gtk_list_store_new(GLIST_NCOLS, GDK_TYPE_PIXBUF,
	                    G_TYPE_STRING, G_TYPE_STRING,
	                    G_TYPE_STRING, G_TYPE_STRING,
	                    G_TYPE_POINTER);
  model = GTK_TREE_MODEL(list); // Update the Model
    
  // Set the Model into the Treeview
  gtk_tree_view_set_model(view, model);
  gtk_tree_view_set_headers_visible(view, TRUE);
  gtk_tree_view_set_headers_clickable(view, TRUE);
  gtk_tree_view_set_rules_hint(view, FALSE);
    
  // Set names for the Columns
  // Icon
  renderer = gtk_cell_renderer_pixbuf_new();
  gtk_tree_view_insert_column_with_attributes(view, -1, "",
				              renderer, "pixbuf",
				              COLUMN_ICON, NULL);
    
  // Name
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(view, -1, "Name",
					      renderer, "text",
					      COLUMN_NAME, NULL);
    
  // Type
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(view, -1, "Type",
				              renderer, "text",
					      COLUMN_TYPE, NULL);
    
  // Size
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(view, -1, "Size",
				              renderer, "text",
					      COLUMN_SIZE, NULL);
    
  // Let Columns be clicked/resized
  for(i=0; i<GLIST_NVCOLS; i++)
  {
    GtkTreeViewColumn *col;
        
    // Get Column
    col = gtk_tree_view_get_column(view, i);
        
    // Set stuff up
    gtk_tree_view_column_set_resizable(col, TRUE);
    gtk_tree_view_column_set_clickable(col, TRUE);
        
    // Attach Signal
    g_signal_connect(G_OBJECT(col), "clicked", G_CALLBACK(group_tree_column_clicked), view);
  }
    
  // Selection Setup
  selection = gtk_tree_view_get_selection(view);
  gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
  gtk_tree_selection_set_select_function(selection, select_func, NULL, NULL);
  g_signal_connect(G_OBJECT(selection), "changed", G_CALLBACK(group_tree_selection_changed), NULL);
    
  // Return
  return 0;
}

/* Clear Group Tree */
int group_tree_clear(void)
{
  GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.group_tree);
  GtkTreeSelection *selection;  

  // Clear the List
  selection = gtk_tree_view_get_selection(view);
  g_signal_handlers_block_by_func(G_OBJECT(selection), group_tree_selection_changed, NULL);
  gtk_list_store_clear(list);
  g_signal_handlers_unblock_by_func(G_OBJECT(selection), group_tree_selection_changed, NULL);

  // Return
  return 0;
}

/* Group Tree Clicked Button Event */
GLADE_CB gboolean on_group_tree_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
  GtkTreeView *view = GTK_TREE_VIEW(widget);
  GtkTreeModel *model = GTK_TREE_MODEL(list);
  GtkTreePath *path;
  GtkTreeViewColumn *column;
  GdkEventButton *bevent;
  gint tx = (gint) event->x;
  gint ty = (gint) event->y;
  gint cx, cy;
  FileEntry *fe;
  GtkTreeIter iter;

  // Get Path
  gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx, &cy);

  switch (event->type) 
  {
    // Single Click
    case GDK_BUTTON_PRESS:
      // Right Click - popup Right Click Menu
      if (event->button == 3)
      {
        bevent = (GdkEventButton *)(event);
                
        // Popup Menu
        gtk_menu_popup(GTK_MENU(create_group_menu()),
                       NULL, NULL, NULL, NULL,
                       bevent->button, bevent->time);
                               
        // Return
        return TRUE;
      }
    break;
    // Double Click
    case GDK_2BUTTON_PRESS:
      // Left Click
      if (event->button == 1)
      {
        // code
      }
    break;
    // Nothing
    default:
    break;
  }

  // Return
  return FALSE;
}
