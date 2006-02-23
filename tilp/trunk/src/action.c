/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

#include "action.h"
#include "support.h"
#include "tilp_core.h"

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
		fe->selected[n] = 0;
	else
		fe->selected[n] = !0;

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
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	GtkTreeIter iter;
	GList *sel;
	int i, button = 0;
	gint result;
	gboolean empty = TRUE;

	// update folder listing (if supported)
	if (!(ticalcs_calc_features(calc_handle) & FTS_SILENT) )
		return BUTTON1;
	else
		if (tilp_dirlist_remote())
			return BUTTON1;

	// box creation
	xml = glade_xml_new(tilp_paths_build_glade("action-2.glade"), "action_dbox", PACKAGE);
	if (!xml)
		g_error(_("action.c: GUI loading failed !\n"));
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "action_dbox");
	clist = data = glade_xml_get_widget(xml, "treeview1");

	// clist creation
	create_clist(data);

	// fill model
	for (sel = local.selection; sel != NULL; sel = sel->next) 
	{
		FileEntry *f = (FileEntry *)sel->data;
		FileContent *c = (FileContent *)f->content;

		if(f->content == NULL)	// file can't be loaded
			continue;

		if(tifiles_file_is_backup(f->name) && !tifiles_file_is_group(f->name)) 
		{
			gif->msg_box(_("Error"),
				     _("You can not send backups in this way. Use the 'Restore' button instead."));

			button = BUTTON2; // skip box as cancel
			goto out_clean;
		}

		// parse each VarEntry in FileEntry
		for (i = 0; i < c->num_entries; i++) 
		{
			VarEntry *v = c->entries[i];
			VarEntry *w;
			gchar **row_text = g_malloc0(5 * sizeof(gchar *));
			char *trans;
			char full_name[19];

			// modify attr or folder if target is specified
			if(strcmp(target, ""))
			{
				if(!strcmp(target, "FLASH"))
				{
					v->attr = ATTRB_ARCHIVED;
				}
				else
				{
					strcpy(v->folder, target);
				}
			}

			// search for matching var
			trans = ticonv_varname_to_utf8(c->model, (const char *)v->name, (unsigned int)v->type);
			tifiles_build_fullname(c->model, full_name, v->folder, v->name);

			w = ticalcs_dirlist_var_exist(remote.var_tree, full_name);
			if (w == NULL)
				continue;

			if(w->attr == ATTRB_LOCKED || w->attr == ATTRB_ARCHIVED)
				v->action = ACT_SKIP;
			else
				v->action = ACT_OVER;

			// file contains an already existing var: add it to the window
			row_text[0] = g_strdup(trans); g_free(trans);
			row_text[1] = g_strdup(tifiles_attribute_to_string(v->attr));
			row_text[2] = g_strdup(f->name);
			row_text[3] = g_strdup(action2string(v->action));

			gtk_list_store_append(list, &iter);
			gtk_list_store_set(list, &iter,
					   COLUMN_VAR,  full_name,
					   COLUMN_ATTR, row_text[1],
					   COLUMN_FILE, row_text[2],
					   COLUMN_ACTION, row_text[3],
					   COLUMN_DATA_F, (gpointer)f, 
					   COLUMN_DATA_V, (gpointer)v, 
					   COLUMN_DATA_N, i,
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

GLADE_CB void action_overwrite_clicked(GtkButton * button, gpointer user_data)
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
		
		if (!f->selected[n])
			continue;

		if (v->attr != ATTRB_NONE)
			continue;

		v->action = ACT_OVER;
		gtk_list_store_set(list, &iter, COLUMN_ACTION, _("overwrite"), -1);
	}
}

GLADE_CB void action_rename_clicked(GtkButton * button, gpointer user_data)
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
		char full_name[19];

		gtk_tree_model_get(model, &iter, 
				COLUMN_DATA_F, &f, COLUMN_DATA_V, &v, COLUMN_DATA_N, &n,
				-1);

		if (!f->selected[n])
			continue;

		// get new name
		c = f->content;
		new_name = gif->msg_entry(_("Rename the file"), _("New name: "), tifiles_get_varname(v->name));
		if (new_name == NULL)
			continue;

		// check that new varname does not exist
		tifiles_build_fullname(c->model, full_name, v->folder, new_name);
		g_free(new_name);
		w = ticalcs_dirlist_var_exist(remote.var_tree, full_name);

		// update action
		v->attr = (w != NULL) ? w->attr : ATTRB_NONE;
		v->action = (v->attr != ATTRB_NONE) ? ACT_SKIP : ACT_RENAME;

		// update var entry
		strcpy(v->folder, tifiles_get_fldname(full_name));
		strcpy(v->name,   tifiles_get_varname(full_name));
		trans = ticonv_varname_to_utf8(c->model, (const char *)v->name, (unsigned int)v->type);

		// update entry
		row_text[0] = g_strdup(trans); g_free(trans);
		row_text[1] = g_strdup(tifiles_attribute_to_string(v->attr));
		row_text[3] = g_strdup(action2string(v->action));
		gtk_list_store_set(list, &iter, 
					COLUMN_VAR, row_text[0],
				   COLUMN_ATTR, row_text[1], 
				   COLUMN_ACTION, row_text[3], -1);
		g_strfreev(row_text);   //bug
	}
}

GLADE_CB void action_skip_clicked(GtkButton * button, gpointer user_data)
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
		
		if (!f->selected[n])
			continue;

		v->action = ACT_SKIP;
		gtk_list_store_set(list, &iter, COLUMN_ACTION, "skip", -1);
	}
}

GLADE_CB void action_select_all_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist);
	GtkTreeSelection *sel;
	
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_select_all(sel);
} 

GLADE_CB void action_deselect_all_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist);
	GtkTreeSelection *sel;
	
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_unselect_all(sel);
}

GLADE_CB gboolean
action_treeview1_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	gint tx = (gint) event->x;
	gint ty = (gint) event->y;
	gint cx, cy;

	if(event->type == GDK_2BUTTON_PRESS)
	{
		VarEntry *ve;

		gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx, &cy);

		if (path == NULL)
			return FALSE;

		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA_V, &ve, -1);

		if(ve->attr == ATTRB_NONE)
			ve->attr = ATTRB_LOCKED;
		else if(ve->attr == ATTRB_LOCKED)
			ve->attr = ATTRB_ARCHIVED;
		else if(ve->attr == ATTRB_ARCHIVED)
			ve->attr = ATTRB_NONE;

		gtk_list_store_set(list, &iter, COLUMN_ATTR, tifiles_attribute_to_string(ve->attr), -1);
	}

	return FALSE;
}
