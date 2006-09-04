/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  08/06/06 19:10 - folder_tree.c
  
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
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "tilibs.h"
#ifdef __WIN32__
#include <dirent.h>
#endif

#include "dialog.h"
#include "file.h"
#include "folder_tree.h"
#include "ftree_menu.h"
#include "gui.h"
#include "gfm.h"
#include "labels.h"
#include "support.h"

// Keep this numbered, because ordering may be messed up when running with
// column2index and the switch that uses these as the cases
enum { COLUMN_ICON=0, COLUMN_NAME=1, COLUMN_TYPE=2, COLUMN_SIZE=3,
       COLUMN_DATE=4, COLUMN_DATA=5 };

#define FLIST_NCOLS (6) // 6 columns
#define FLIST_NVCOLS (5) // 5 viewable columns

static GtkListStore *list;

// Post information about Folder Tree
FolderTreeData ftree_info;

/* Column Find Selected Routine */
static gint column2index(GtkWidget* list, GtkTreeViewColumn* column)
{
	gint i;

    // Scan
	for (i=0; i<FLIST_NVCOLS; i++) 
	{
		GtkTreeViewColumn *col;
        
        // Load Column
		col = gtk_tree_view_get_column(GTK_TREE_VIEW(list), i);
		if (col == column)
			return i; // Have a match
	}
    
    // Return
	return -1;
}

/* Column Clicked Function */
static void folder_tree_column_clicked(GtkTreeViewColumn* column, gpointer user_data)
{
    int col = (int)column2index(user_data, column);
	GtkSortType sort1 = gtk_tree_view_column_get_sort_order(column);
	GtkSortType sort2 = ftree_info.sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING;
    int col_set;
    
    // Do we have a match?
    if (sort1 == sort2)
    {
        // Lets Flip
        if (ftree_info.sort_order)
					ftree_info.sort_order = FTREE_SORT_ASC; // A-Z
        else
					ftree_info.sort_order = FTREE_SORT_DESC; // Z-A
    }
    
    // Lets set the Column to Sort by.
    switch(col)
    {
        case COLUMN_NAME: // Sort by Name
        case COLUMN_ICON: // Sort by Name (Icon->name)
             col_set = FTREE_SORT_NAME;
        break;
        case COLUMN_TYPE: // Sort by Type
             col_set = FTREE_SORT_TYPE;
        break;
        case COLUMN_SIZE: // Sort by Size
             col_set = FTREE_SORT_SIZE;
        break;
        case COLUMN_DATE: // Sort by Date
             col_set = FTREE_SORT_DATE;
        break;
        default:
             col_set = FTREE_SORT_NAME;
        break; // Default to Name
    }
    
    // If switching Columns, always A-Z
    if (col_set != ftree_info.column)
        ftree_info.sort_order = FTREE_SORT_ASC; // A-Z
    
    // Set the Column to Sort by
    ftree_info.column = col_set;
    
    // Refresh the List
    folder_tree_refresh();
}

/* Selection Test Function */
static gboolean select_func(GtkTreeSelection* selection, GtkTreeModel* model,
			                GtkTreePath* path, gboolean path_currently_selected,
			                gpointer data)
{
	GtkTreeIter iter;
	FileEntry *fe;

	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, COLUMN_DATA, &fe, -1);
    
    if (S_ISDIR(fe->attrib))
		return FALSE;
    
	return TRUE;
}

static void ftree_file_selection_add(const char *filename)
{
  GList *ptr;
  
	for(ptr = ftree_info.selected_files; ptr; ptr = ptr->next)
    if (!strcmp((char *)ptr->data, filename))
      return;

  ftree_info.selected_files = g_list_append(ftree_info.selected_files, (gpointer) filename);
}

/* Selection Selected */
static void folder_tree_selection_changed(GtkTreeSelection *selection, gpointer user_data)
{
  GList *list;
	GtkTreeIter iter;
	GtkTreeModel *model;

	// destroy the selection first
	if (ftree_info.selection != NULL) 
	{
		g_list_free(ftree_info.selection);
		ftree_info.selection = NULL;
	}
	if (ftree_info.selected_files != NULL && ftree_info.working_act == 0)
	{
		g_list_free(ftree_info.selected_files);
		ftree_info.selected_files = NULL;
	}
	
	// create a new selection
	for(list = gtk_tree_selection_get_selected_rows(selection, &model);
      list; list = g_list_next(list))
	{
		GtkTreePath *path = list->data;
		FileEntry *fe;
		gchar *full_path;
        
    // Get the FileEntry
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &fe, -1);
 
		// Lets Add the Path to the file in the selected_files list
		full_path = g_strconcat(settings.cur_dir, G_DIR_SEPARATOR_S, fe->name, NULL);
		if (ftree_info.working_act == 0)
		  ftree_file_selection_add(full_path);

	  // Add to List
		ftree_info.selection = g_list_append(ftree_info.selection, fe);
	}

    // Free some stuff
	g_list_foreach(list, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(list);
}

/* Folder Tree Init */
int folder_tree_init(void)
{
    GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.comp_tree);
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;
	gint i;
	
	// Setup the List
	list = gtk_list_store_new(FLIST_NCOLS, GDK_TYPE_PIXBUF,
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
    
    // Date
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, "Date",
						    renderer, "text",
						    COLUMN_DATE, NULL);
    
    // Let Columns be clicked/resized
    for(i=0; i<FLIST_NVCOLS; i++)
    {
        GtkTreeViewColumn *col;
        
        // Get Column
        col = gtk_tree_view_get_column(view, i);
        
        // Set stuff up
        gtk_tree_view_column_set_resizable(col, TRUE);
        gtk_tree_view_column_set_clickable(col, TRUE);
        
        // Attach Signal
        g_signal_connect(G_OBJECT(col), "clicked", G_CALLBACK(folder_tree_column_clicked), view);
    }
    
    // Selection Setup
    selection = gtk_tree_view_get_selection(view);
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
    gtk_tree_selection_set_select_function(selection, select_func, NULL, NULL);
    g_signal_connect(G_OBJECT(selection), "changed", G_CALLBACK(folder_tree_selection_changed), NULL);
    
    // Return
    return 0;
}

/* Refresh the Folder Tree */
int folder_tree_refresh(void)
{
  GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.comp_tree);
	GtkTreeSelection *selection;
	GtkTreeViewColumn *col;
	GtkTreeIter iter;
	GdkPixbuf *pix1, *pix2, *pix;
	GList *dirlist;
	gsize br, bw;
	gchar *utf8;
	int i, col_ind = -1;
	
	// Clear the Selection
	if (ftree_info.selection != NULL) 
	{
		g_list_free(ftree_info.selection);
		ftree_info.selection = NULL;
	}
	
	// Get the Directory List
	file_get_dirlist();

	// Clear the List
	selection = gtk_tree_view_get_selection(view);
	g_signal_handlers_block_by_func(G_OBJECT(selection), folder_tree_selection_changed, NULL);
	gtk_list_store_clear(list);
	g_signal_handlers_unblock_by_func(G_OBJECT(selection), folder_tree_selection_changed, NULL);

	// Clear the Sorter Buttons on the Columns
	for (i=0; i<FLIST_NVCOLS; i++)
	{
    col = gtk_tree_view_get_column(view, i);
    gtk_tree_view_column_set_sort_indicator(col, FALSE);
  }
    
  // Sort the Files
  switch(ftree_info.column)
  {
    case FTREE_SORT_NAME: // Sort by Name
      col_ind = COLUMN_NAME; // Column to Edit
    break;
    case FTREE_SORT_TYPE: // Sort by Type
      col_ind = COLUMN_TYPE; // Column to Edit
    break;
    case FTREE_SORT_SIZE: // Sort by Size
      col_ind = COLUMN_SIZE; // Column to Edit
    break;
    case FTREE_SORT_DATE: // Sort by Date
      col_ind = COLUMN_DATE; // Column to Edit
    break;
    default: // Nothing
    break;
  }
  col = gtk_tree_view_get_column(view, col_ind); // Got Column
  gtk_tree_view_column_set_sort_indicator(col, TRUE);
  gtk_tree_view_column_set_sort_order(col, ftree_info.sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);
  ftree_sort_list(ftree_info.column); // Sort the List

  // Setup the Two Default Icons
  pix1 = create_pixbuf("up.ico");
	pix2 = create_pixbuf("clist_dir.xpm");
	
	// Add the Items to the Tree
	for (dirlist=ftree_info.dir_list; dirlist!=NULL; dirlist=dirlist->next)
	{
    FileEntry *fe = (FileEntry *)dirlist->data;
		gboolean b;
		
		// Pass a test	
		CalcModel s = tifiles_file_get_model(fe->name);
		
		b = settings.show_all || S_ISDIR(fe->attrib) ||
			tifiles_file_is_tib(fe->name) ||
			tifiles_file_is_tigroup(fe->name) ||
            tifiles_calc_are_compat(s, s);
		if(!b)
			continue;
		
    // File, or something else
		if (S_ISDIR(fe->attrib))
		  pix = strcmp(fe->name, "..") ? pix2 : pix1;
    else
    {
      char icon_name[256];
            
      // Copy to icon_name
      strcpy(icon_name, tifiles_file_get_icon(fe->path));
            
      // Empty value?
      if (!strcmp(icon_name, ""))
        strcpy(icon_name, "TIicon1");
            
      // Add file extension
      strcat(icon_name, ".ico");
            
      // Make sure filename is valid.
      strcpy(icon_name, file_fix_letters(icon_name));
            
      // Create the Icon
      pix = create_pixbuf(icon_name);
    }
        
    // Add item to list now
    utf8 = g_filename_to_utf8(fe->name, -1, &br, &bw, NULL);
		gtk_list_store_append(list, &iter);
		gtk_list_store_set(list, &iter, 
				   COLUMN_NAME, utf8,
				   COLUMN_TYPE, file_get_type(fe),
				   COLUMN_SIZE, file_get_size(fe),
				   COLUMN_DATE, file_get_date(fe),
				   COLUMN_DATA, (gpointer)fe, 
                   COLUMN_ICON, pix, 
                   -1);
		g_free(utf8);
  }
  
	// Unreference Icons
	g_object_unref(pix1);
	g_object_unref(pix2);
	
	// Set Folder Tree Current Directory Label
	ftree_label_refresh();
	
	// Return
	return 0;
}

/* Folder Tree Click Event */
GLADE_CB gboolean on_folder_tree_button_press_event(GtkWidget *widget,
                                                    GdkEventButton *event, 
                                                    gpointer user_data)
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
                gtk_menu_popup(GTK_MENU(create_folder_menu()),
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
                // Is the path null?
                if (path == NULL)
                    return FALSE;
                
                // Get the File Entry
                gtk_tree_model_get_iter(model, &iter, path);
		        gtk_tree_model_get(model, &iter, COLUMN_DATA, &fe, -1);
		        
		        /* What are we doing now? */
		        // Changing Directory
		        if (S_ISDIR(fe->attrib))
		        {
                    // Change Directory
                    gfm_change_cwd(fe->name);
                    
                    // Update Variable
                    g_free(settings.cur_dir);
                    settings.cur_dir = g_get_current_dir();

                    // Refresh List
                    folder_tree_refresh();
                }
                
                // Opening File
                else if (tifiles_file_is_group(fe->path))
                {
                    msgbox_error("Group File!\nCode In: Line ~475 folder_tree.c");
                }
            }
        break;
        // Nothing
        default:
        break;
    }

	// Done
    return FALSE;
}

/* Folder Tree Key Press Event */
GLADE_CB gboolean on_folder_tree_key_press_event(GtkWidget *widget,
                                                 GdkEventKey *event,
                                                 gpointer user_data)
{
    // code
    
    // Return is bad
    return FALSE;
}
