/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *  Copyright (C) 2007  Kevin Kofler
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

#include "action.h"
#include "support.h"
#include "tilp_core.h"
#include "ctree.h"
#include "labels.h"

static GtkWidget *clist;
static GtkListStore *list;

// be able to modify var attribute

enum 
{ 
	COLUMN_VAR, COLUMN_ATTR, COLUMN_FILE, COLUMN_ACTION,
	COLUMN_DATA_F, COLUMN_DATA_V, COLUMN_DATA_N, COLUMN_NUMBER
};

#define CLIST_NVCOLS	(4)		// 4 visible columns
#define CLIST_NCOLS		(8)		// 6 real columns

static gboolean select_function(GtkTreeSelection * selection,
				GtkTreeModel * model,
				GtkTreePath * path,
				gboolean path_currently_selected,
				gpointer data)
{
	GtkTreeIter iter;
	FileEntry *fe;
	int n;

	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, COLUMN_DATA_F, &fe, COLUMN_DATA_N, &n, -1);

	if (gtk_tree_selection_path_is_selected(selection, path))
		fe->selected = 0;
	else
		fe->selected = !0;

	return TRUE;
}

static void create_clist(GtkWidget * clist_wnd)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeSelection *sel;
	gint i;

	list = gtk_list_store_new(COLUMN_NUMBER, 
				G_TYPE_STRING, G_TYPE_STRING, 
				G_TYPE_STRING, G_TYPE_STRING, 
				G_TYPE_POINTER, G_TYPE_POINTER, G_TYPE_INT);
	model = GTK_TREE_MODEL(list);
	
	gtk_tree_view_set_model(view, model);
	gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_headers_clickable(view, TRUE);
	gtk_tree_view_set_rules_hint(view, FALSE);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    _("Varname"),
						    renderer, "text",
						    COLUMN_VAR, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    _("Attribute"),
						    renderer, "text",
						    COLUMN_ATTR, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    _("Filename"),
						    renderer, "text",
						    COLUMN_FILE, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1,
						    _("Action"),
						    renderer, "text",
						    COLUMN_ACTION, NULL);

	for (i = 0; i < CLIST_NVCOLS - 1; i++) 
	{
		GtkTreeViewColumn *col;
		col = gtk_tree_view_get_column(view, i);
		gtk_tree_view_column_set_resizable(col, TRUE);
	}

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(sel, select_function, NULL, NULL);
}

static const char* action2string(int action)
{
	switch(action)
	{
	case ACT_NONE:   return _("none"); break;
	case ACT_RENAME: return _("rename"); break;
	case ACT_OVER:   return _("overwrite"); break;
	case ACT_SKIP:   return _("skip"); break;
	}

	return "";
}

gint display_action_dbox(gchar *target)
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *dbox;
	GtkWidget *data;
	GtkTreeIter iter;
	GList *sel;
	int button = 0;
	gint result;
	gboolean empty = TRUE;

	// update folder listing (if supported)
	if (!(ticalcs_calc_features(calc_handle) & FTS_SILENT) )
		return BUTTON1;
	else
	{
		if(remote.var_tree == NULL)
		{
			if (tilp_dirlist_remote())
				return BUTTON1;

			ctree_refresh();
			labels_refresh();
		}
	}

	// box creation
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("action.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	dbox = GTK_WIDGET (gtk_builder_get_object (builder, "action_dbox"));
	gtk_dialog_set_alternative_button_order(GTK_DIALOG(dbox), GTK_RESPONSE_OK, GTK_RESPONSE_CANCEL, -1);
	clist = data = GTK_WIDGET (gtk_builder_get_object (builder, "treeview1"));

	// clist creation
	create_clist(data);

	// fill model
	for (sel = local.selection1; sel != NULL; sel = sel->next) 
	{
		FileEntry *f = (FileEntry *)sel->data;
		FileContent *c = (FileContent *)f->content1;

		if(f->content1 == NULL)	// file can't be loaded
			continue;

		// we have now 1 VarEntry per FileContent
		{
			VarEntry *v = c->entries[0];
			VarEntry *w;
			gchar **row_text = g_malloc0(5 * sizeof(gchar *));
			char *trans;
			char full_name[260];

			// modify attr or folder if target is specified
			if(strcmp(target, ""))
			{
				if(!strcmp(target, "<FLASH>"))
				{
					v->attr = ATTRB_ARCHIVED;
				}
				else
				{
					strcpy(v->folder, target);
				}
			}

			// search for matching var
			tifiles_build_fullname(options.calc_model, full_name, v->folder, v->name);
			trans = ticonv_varname_to_utf8(options.calc_model, (const char *)full_name, v->type);

			w = ticalcs_dirlist_ve_exist(remote.var_tree, v);
			if (w == NULL)
				continue;

			if(w->attr == ATTRB_LOCKED || w->attr == ATTRB_ARCHIVED)
				v->action = ACT_SKIP;
			else
				v->action = ACT_SKIP;	//don't overwrite as default behaviour

			// file contains an already existing var: add it to the window
			row_text[0] = g_strdup(trans); ticonv_utf8_free(trans);
			row_text[1] = g_strdup(tifiles_attribute_to_string(v->attr));
			row_text[2] = g_strdup(f->name);
			row_text[3] = g_strdup(action2string(v->action));
			tilp_vars_translate(row_text[0]);

			gtk_list_store_append(list, &iter);
			gtk_list_store_set(list, &iter,
					   COLUMN_VAR,  row_text[0],
					   COLUMN_ATTR, row_text[1],
					   COLUMN_FILE, row_text[2],
					   COLUMN_ACTION, row_text[3],
					   COLUMN_DATA_F, (gpointer)f,
					   COLUMN_DATA_V, (gpointer)v,
					   -1);
			g_strfreev(row_text);

			empty = FALSE;
		}
	}

	if (empty == TRUE) 
	{
		button = BUTTON1; // skip box as ok
		goto out_clean;
	}

	// select all vars
	{
		GtkTreeView *view = GTK_TREE_VIEW(clist);
		GtkTreeSelection *sel2;

		sel2 = gtk_tree_view_get_selection(view);
		gtk_tree_selection_select_all(sel2);
	}

	// box running
	gtk_dialog_set_default_response(GTK_DIALOG(dbox), GTK_RESPONSE_CANCEL);
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		button = BUTTON1;
		break;
	case GTK_RESPONSE_CANCEL:
		button = BUTTON2;
	default:
		button = BUTTON2;
		break;
	}

out_clean:
	gtk_widget_destroy(dbox);

	return button;
}

void action_overwrite_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;

	for (valid = gtk_tree_model_get_iter_first(model, &iter); valid;
	     valid = gtk_tree_model_iter_next(model, &iter)) 
	{
		FileEntry *f;
		VarEntry *v;
		int n;

		gtk_tree_model_get(model, &iter, 
			COLUMN_DATA_F, &f, COLUMN_DATA_V, &v, COLUMN_DATA_N, &n,
			-1);

		if (!f->selected)
			continue;

		if (v->attr != ATTRB_NONE)
			continue;

		v->action = ACT_OVER;
		gtk_list_store_set(list, &iter, COLUMN_ACTION, _("overwrite"), -1);
	}
}

void action_rename_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;

	for (valid = gtk_tree_model_get_iter_first(model, &iter); valid;
	     valid = gtk_tree_model_iter_next(model, &iter)) 
	{
		FileEntry *f;
		FileContent *c;
		VarEntry *v;
		VarEntry *w;
		int n;
	
		gchar *new_name = NULL;
		gchar **row_text = g_malloc0(5 * sizeof(gchar *));
		char *trans;
		char full_name[260];

		gtk_tree_model_get(model, &iter, 
				COLUMN_DATA_F, &f, COLUMN_DATA_V, &v, COLUMN_DATA_N, &n,
				-1);

		if (!f->selected)
			continue;

		// get new name
		c = f->content1;
		new_name = gif->msg_entry(_("Rename the file"), _("New name: "), tifiles_get_varname(v->name));
		if (new_name == NULL)
			continue;

		// check that new varname does not exist
		tifiles_build_fullname(options.calc_model, full_name, v->folder, new_name);
		g_free(new_name);
		w = ticalcs_dirlist_ve_exist(remote.var_tree, v);

		// update action
		v->attr = (w != NULL) ? w->attr : ATTRB_NONE;
		v->action = (v->attr != ATTRB_NONE) ? ACT_SKIP : ACT_RENAME;

		// update var entry
		strncpy(v->folder, tifiles_get_fldname(full_name), 8); v->folder[8] = 0;
		strncpy(v->name,   tifiles_get_varname(full_name), 8); v->name[8] = 0;
		trans = ticonv_varname_to_utf8(options.calc_model, (const char *)v->name, v->type);

		// update entry
		row_text[0] = g_strdup(trans); ticonv_utf8_free(trans);
		row_text[1] = g_strdup(tifiles_attribute_to_string(v->attr));
		row_text[3] = g_strdup(action2string(v->action));
		gtk_list_store_set(list, &iter, 
					COLUMN_VAR, row_text[0],
				   COLUMN_ATTR, row_text[1], 
				   COLUMN_ACTION, row_text[3], -1);
		g_strfreev(row_text);   //bug
	}
}

void action_skip_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;

	for (valid = gtk_tree_model_get_iter_first(model, &iter); valid;
	     valid = gtk_tree_model_iter_next(model, &iter)) 
	{
		FileEntry *f;
		VarEntry *v;
		int n;

		gtk_tree_model_get(model, &iter, 
			COLUMN_DATA_F, &f, COLUMN_DATA_V, &v, COLUMN_DATA_N, &n,
			-1);
		
		if (!f->selected)
			continue;

		v->action = ACT_SKIP;
		gtk_list_store_set(list, &iter, COLUMN_ACTION, "skip", -1);
	}
}

void action_select_all_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist);
	GtkTreeSelection *sel;

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_select_all(sel);
} 

void action_deselect_all_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist);
	GtkTreeSelection *sel;

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_unselect_all(sel);
}

gboolean action_treeview1_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	gint tx = (gint) event->x;
	gint ty = (gint) event->y;
	gint cx, cy;

	if (event->type == GDK_2BUTTON_PRESS)
	{
		VarEntry *ve;

		gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx, &cy);

		if (path == NULL)
			return FALSE;

		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA_V, &ve, -1);

		if (ve->attr == ATTRB_NONE)
			ve->attr = ATTRB_LOCKED;
		else if (ve->attr == ATTRB_LOCKED)
			ve->attr = ATTRB_ARCHIVED;
		else if (ve->attr == ATTRB_ARCHIVED)
			ve->attr = ATTRB_NONE;

		gtk_list_store_set(list, &iter, COLUMN_ATTR, tifiles_attribute_to_string(ve->attr), -1);
	}

	return FALSE;
}
