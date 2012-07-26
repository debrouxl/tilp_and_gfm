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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
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
	TARGET_STRING, TARGET_ROOTWIN, TARGET_TEXT_URI_LIST,
	TARGET_LEFT, TARGET_RIGHT,
};

/*static GtkTargetEntry target_table[] = {
  { "STRING",     0, TARGET_STRING },
  { "text/plain", 0, TARGET_STRING },
  { "application/x-rootwin-drop", 0, TARGET_ROOTWIN },
  };*/

static GtkTargetEntry target_table_1[] = 
{
	{(char *)"clist", 0, TARGET_STRING},
	{(char *)"text/uri-list", 0, TARGET_TEXT_URI_LIST, },
	{(char *)"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};

static GtkTargetEntry target_table_2[] = 
{
	{(char *)"ctree", 0, TARGET_STRING},
	{(char *)"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};

static guint n_targets = 1;

void dnd_init(void)
{
	// from list to tree
	gtk_drag_source_set(clist_wnd, GDK_BUTTON1_MASK,
			    target_table_1, n_targets,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE);
	gtk_drag_dest_set(ctree_wnd, GTK_DEST_DEFAULT_ALL,
			  target_table_1, n_targets+1,
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

// pass data
TILP_EXPORT void
on_treeview2_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint _time, gpointer user_data)
{
	gchar *name = (char *)"foo_bar";
	gtk_selection_data_set(data, data->target, 8, 
			       (guchar *)name, strlen(name));
}

extern int on_tilp_send(const gchar*);

// retrieve data
TILP_EXPORT void
on_treeview1_drag_data_received(GtkWidget * widget,
				GdkDragContext * drag_context,
				gint x,
				gint y,
				GtkSelectionData * data,
				guint info, guint _time, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreeModel *model = gtk_tree_view_get_model(view);
	GtkTreePath *path;
	GtkTreeViewDropPosition pos;
	GtkTreeIter iter;
	VarEntry *ve;
	gchar *name;
	gchar *target = NULL;
	gboolean success = FALSE;

	if ((data->length >= 0) && (data->format == 8))
	{
		if (drag_context->action == GDK_ACTION_ASK)
		{
			drag_context->action = GDK_ACTION_COPY;
		}

		if (info == TARGET_TEXT_URI_LIST)
		{
			int i;
			gchar **list;
			//list = g_uri_list_extract_uris((gchar *)gtk_selection_data_get_data(data));
			list = gtk_selection_data_get_uris(data);
			tilp_local_selection_destroy();
			for (i = 0;list[i] != NULL; i++)
			{
				name = g_filename_from_uri(list[i], NULL, NULL);
				tilp_local_selection_add(name);
			}
			g_strfreev(list);
		}

		gtk_tree_view_get_dest_row_at_pos(view, x, y, &path, &pos);
		if (path == NULL)
			goto end;
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ve, -1);
		gtk_tree_model_get(model, &iter, COLUMN_NAME, &name, -1);

		//g_print("Received \"%s\" as selection information.\n", name);

		if(strchr(name, '#'))			// Calc
		{
		}
		else if(!strcmp(name, NODE4))	// Applications
		{
			// send to flash
			target=(char *)"<FLASH>";
		}
		else if (ve && tifiles_has_folder(options.calc_model))
		{
			// send to folder
			if(!strcmp(ve->folder, ""))
				target = ve->name;
			else
				target = ve->folder;
		}
		else if(!strcmp(name, NODE2))	// Operating System
		{
			target=(char *)"";
		}
		else
		{
			if(options.calc_model == CALC_NSPIRE)
			{
				gif->msg_box1(_("Error"), "You have to drag&drop to a target folder!");
				return;
			}
			else
			{
				// send standard
				target=(char *)"";
			}
		}

		if (target!=NULL)
			on_tilp_send(target);

		tilp_local_selection_destroy();
		success = TRUE;
	}
end:
	gtk_drag_finish(drag_context, success, FALSE, _time);
	return;
}


/* CTree -> CList */

extern gchar *name_to_drag;
extern GtkTreePath *path_to_drag;

TILP_EXPORT void
on_treeview1_drag_begin(GtkWidget * widget,
			GdkDragContext * drag_context, gpointer user_data)
{
	// Folder
	if (!strcmp(name_to_drag, NODEx) && (ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		ctree_select_vars(!0);

	// Variables
	else if (!strcmp(name_to_drag, NODE3) && !(ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		ctree_select_vars(!0);

	// Variables
	else if (!strcmp(name_to_drag, NODE3) && (ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		ctree_select_vars(!0);

	// Applications
	else if (!strcmp(name_to_drag, NODE4) && (ticalcs_calc_features(calc_handle) & FTS_FLASH))
		ctree_select_vars(!0);
}

TILP_EXPORT void
on_treeview1_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint _time, gpointer user_data)
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

TILP_EXPORT void
on_treeview2_drag_data_received(GtkWidget * widget,
				GdkDragContext * drag_context,
				gint x,
				gint y,
				GtkSelectionData * data,
				guint info, guint _time, gpointer user_data)
{
	if ((data->length >= 0) && (data->format == 8)) 
	{
		gchar *name = (gchar *) data->data;

		//g_print("Received \"%s\" as selection information.\n", name);

		if(strchr(name, '#'))			// Calc
		{
			//on_tilp_button7_clicked(NULL, NULL);
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
			ctree_select_vars(0);
		}
		else if (!strcmp(name, NODE4))	// Apps & Archives
		{
			// all apps to get
			on_tilp_button5_clicked(NULL, NULL);
			ctree_select_vars(0);
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
			ctree_select_vars(0);
		} 
		else 
		{
			// single/group/app to get
			on_tilp_button5_clicked(NULL, NULL);
		}

		gtk_drag_finish(drag_context, TRUE, FALSE, _time);
		return;
	}

	gtk_drag_finish(drag_context, FALSE, FALSE, _time);
	return;
}

