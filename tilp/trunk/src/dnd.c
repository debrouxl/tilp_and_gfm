/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "gstruct.h"
#include "ctree.h"
#include "tilp.h"
#include "screenshot.h"
#include "tilp_core.h"
#include "gtk_update.h"

// MUST be the same in ctree.c
enum 
{ 
	COLUMN_NAME, COLUMN_ATTR, COLUMN_TYPE, COLUMN_SIZE, 
	COLUMN_DATA, COLUMN_FONT, COLUMN_ICON
};

/* Drag & Drop support (DnD) */

enum 
{ 
	TARGET_STRING, TARGET_ROOTWIN, TARGET_LEFT, TARGET_RIGHT,
};

/*static GtkTargetEntry target_table[] = {
  { "STRING",     0, TARGET_STRING },
  { "text/plain", 0, TARGET_STRING },
  { "application/x-rootwin-drop", 0, TARGET_ROOTWIN },
  };*/

static GtkTargetEntry target_table_1[] = 
{
	{"clist", 0, TARGET_STRING},
	{"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};

static GtkTargetEntry target_table_2[] = 
{
	{"ctree", 0, TARGET_STRING},
	{"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};

static guint n_targets = 1;

void dnd_init(void)
{
	// from list to tree
	gtk_drag_source_set(clist_wnd, GDK_BUTTON1_MASK,
			    target_table_1, n_targets,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE);
	gtk_drag_dest_set(ctree_wnd, GTK_DEST_DEFAULT_ALL,
			  target_table_1, n_targets,
			  GDK_ACTION_COPY | GDK_ACTION_MOVE);

	// from tree to list
	gtk_drag_source_set(ctree_wnd, GDK_BUTTON1_MASK,
			    target_table_2, n_targets,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE);
	gtk_drag_dest_set(clist_wnd, GTK_DEST_DEFAULT_ALL,
			  target_table_2, n_targets,
			  GDK_ACTION_COPY | GDK_ACTION_MOVE);
}

/* CList -> CTree */

GLADE_CB void
on_treeview2_drag_begin(GtkWidget * widget,
			GdkDragContext * drag_context, gpointer user_data)
{
}

// pass data
GLADE_CB void
on_treeview2_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint time, gpointer user_data)
{
	gchar *name = "foo_bar";
	gtk_selection_data_set(data, data->target, 8, 
			       (guchar *)name, strlen(name));
}

extern int on_tilp_send(gchar*);

// retrieve data
GLADE_CB void
on_treeview1_drag_data_received(GtkWidget * widget,
				GdkDragContext * drag_context,
				gint x,
				gint y,
				GtkSelectionData * data,
				guint info, guint time, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreeModel *model = gtk_tree_view_get_model(view);
	GtkTreePath *path;
	GtkTreeViewDropPosition pos;
	GtkTreeIter iter;
	VarEntry *ve;
	gchar *name;

	if ((data->length >= 0) && (data->format == 8)) 
	{
		gtk_tree_view_get_dest_row_at_pos(view, x, y, &path, &pos);
		if (path == NULL) 
		{
			gtk_drag_finish(drag_context, FALSE, FALSE, time);
			return;
		}
		gtk_tree_model_get_iter(model, &iter, path);

		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ve, -1);
		gtk_tree_model_get(model, &iter, COLUMN_NAME, &name, -1);

		g_print("Received \"%s\" as selection information.\n", name);

		if(!strcmp(name, NODE4))	// Apps/Archive
		{
			// send to flash
			on_tilp_send("FLASH");
			gtk_drag_finish(drag_context, TRUE, FALSE, time);
			return;
		}

		else if (ve && tifiles_has_folder(options.calc_model))
		{
			// send to folder
			char *target;

			if(!strcmp(ve->folder, ""))
				target = ve->name;
			else
				target = ve->folder;
			on_tilp_send(target);
			gtk_drag_finish(drag_context, TRUE, FALSE, time);
			return;
		}

		else
		{
			// send standard
			on_tilp_send("");
			gtk_drag_finish(drag_context, TRUE, FALSE, time);
			return;
		}
	}

	gtk_drag_finish(drag_context, FALSE, FALSE, time);
	return;
}


/* CTree -> CList */

extern gchar *name_to_drag;
extern GtkTreePath *path_to_drag;
static void select_vars_under_folder(gint action);

GLADE_CB void
on_treeview1_drag_begin(GtkWidget * widget,
			GdkDragContext * drag_context, gpointer user_data)
{
	// Folder
	if (!strcmp(name_to_drag, NODEx) && (ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		select_vars_under_folder(!0);

	// Variables
	else if (!strcmp(name_to_drag, NODE3) && !(ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		select_vars_under_folder(!0);

	// Variables
	else if (!strcmp(name_to_drag, NODE3) && (ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		select_vars_under_folder(!0);

	// Applications
	else if (!strcmp(name_to_drag, NODE4) && (ticalcs_calc_features(calc_handle) & FTS_FLASH))
		select_vars_under_folder(!0);
}

GLADE_CB void
on_treeview1_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint time, gpointer user_data)
{
	if (info == TARGET_ROOTWIN) 
	{
		tilp_info("I was dropped on the rootwin\n");
	} 
	else
	{
		gtk_selection_data_set(data, data->target, 8, 
				       (guchar *)name_to_drag, 
				       strlen(name_to_drag));
	}
}

GLADE_CB void
on_treeview2_drag_data_received(GtkWidget * widget,
				GdkDragContext * drag_context,
				gint x,
				gint y,
				GtkSelectionData * data,
				guint info, guint time, gpointer user_data)
{
	if ((data->length >= 0) && (data->format == 8)) 
	{
		gchar *name = (gchar *) data->data;

		g_print("Received \"%s\" as selection information.\n", name);


		if(strchr(name, '#'))			// Calc
		{
			on_tilp_button7_clicked(NULL, NULL);

		}
		else if (!strcmp(name, NODE1))	// Screen
		{
			display_screenshot_dbox();
			on_scdbox_button1_clicked(NULL, NULL);

			if (gtk_update.cancel == 0) 
			{
				on_sc_save1_activate(NULL, NULL);
				on_sc_quit1_activate(NULL, NULL);
			}
		} 
		else if (!strcmp(name, NODE2))	// OS
		{
			on_rom_dump1_activate(NULL, NULL);
		} 
		else if (!strcmp(name, NODE3))	// Variables
		{
			// all variables to get
			on_tilp_button5_clicked(NULL, NULL);
			select_vars_under_folder(0);
		}
		else if (!strcmp(name, NODE4))	// Apps & Archives
		{
			// all apps to get
			on_tilp_button5_clicked(NULL, NULL);
			select_vars_under_folder(0);
		}
		else if (!strcmp(name, NODE5))	// IDlist
		{
			// put IDLIST in a text file
			tilp_calc_idlist(1);
		}
		else if (!strcmp(name, NODE6))	// Clock
		{
		}
		else if (!strcmp(name, NODEx))	// Folder
		{
			// folder to get
			on_tilp_button5_clicked(NULL, NULL);
			select_vars_under_folder(0);
		} 
		else 
		{
			// single/group/app to get
			on_tilp_button5_clicked(NULL, NULL);
		}

		gtk_drag_finish(drag_context, TRUE, FALSE, time);
		return;
	}

	gtk_drag_finish(drag_context, FALSE, FALSE, time);
	return;
}

static void select_vars_under_folder(gint action)
{
	GtkTreeView *view;
	GtkTreeModel *model;
	GtkTreePath *path = path_to_drag;
	GtkTreeIter parent, start_iter, end_iter, iter;
	view = GTK_TREE_VIEW(ctree_wnd);
	model = gtk_tree_view_get_model(view);

	// select var beneath a folder
	gtk_tree_model_get_iter(model, &parent, path);

	if (gtk_tree_model_iter_has_child(model, &parent)) 
	{
		GtkTreeSelection *sel;
		GtkTreePath *start_path, *end_path;
		gint n;
		gboolean valid;

		sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(ctree_wnd));
		n = gtk_tree_model_iter_n_children(model, &parent);

		valid = gtk_tree_model_iter_children(model, &start_iter, &parent);
		start_path = gtk_tree_model_get_path(model, &start_iter);

		valid = gtk_tree_model_iter_nth_child(model, &end_iter, &parent, n - 1);
		if(gtk_tree_model_iter_has_child(model, &end_iter))
		{
			n = gtk_tree_model_iter_n_children(model, &end_iter);
			valid = gtk_tree_model_iter_nth_child(model, &iter, &end_iter, n - 1);
			memcpy(&end_iter, &iter, sizeof(GtkTreeIter));
		}
		end_path = gtk_tree_model_get_path(model, &end_iter);

		if (!action)
			gtk_tree_selection_unselect_range(sel, start_path, end_path);
		else
			gtk_tree_selection_select_range(sel, start_path, end_path);

		gtk_tree_path_free(start_path);
		gtk_tree_path_free(end_path);
	}
}
