/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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
#include "tilp_core.h"

static GtkWidget *clist;
static GtkListStore *list;

enum { COLUMN_VAR, COLUMN_ATTR, COLUMN_FILE, COLUMN_ACTION,
	COLUMN_DATA, COLUMN_NUMBER
};

typedef struct {
	char varname[18];
	int varattr;
	char *filename;
	char *action;
	int selected;
} TilpAction;

static void free_actions(void)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;
	TilpAction *ta;

	valid = gtk_tree_model_get_iter_first(model, &iter);
	while (valid) {
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ta, -1);
		g_free(ta);
		valid = gtk_tree_model_iter_next(model, &iter);
	}
}

static gboolean select_function(GtkTreeSelection * selection,
				GtkTreeModel * model,
				GtkTreePath * path,
				gboolean path_currently_selected,
				gpointer data)
{
	GtkTreeIter iter;
	TilpAction *ta;

	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, COLUMN_DATA, &ta, -1);
	if (gtk_tree_selection_path_is_selected(selection, path))
		ta->selected = 0;
	else
		ta->selected = !0;

	return TRUE;
}

static void create_clist(GtkWidget * clist_wnd)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeSelection *sel;
	gint i;

	list = gtk_list_store_new(COLUMN_NUMBER, G_TYPE_STRING,
				  G_TYPE_STRING, G_TYPE_STRING,
				  G_TYPE_STRING, G_TYPE_POINTER);
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

	for (i = 0; i < COLUMN_NUMBER - 1; i++) {
	  GtkTreeViewColumn *col;
	  col = gtk_tree_view_get_column(view, i);
	  gtk_tree_view_column_set_resizable(col, TRUE);
	}
	
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(sel, GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(sel, select_function, NULL,
					       NULL);
}

gint display_action_dbox(gchar * dest)
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	GtkTreeIter iter;
	GList *sel;
	TiRegular content;
	int i, button = 0;
	gint result;

	if (!ti_calc.is_silent)
		return BUTTON1;

	// box creation
	xml = glade_xml_new
	    (tilp_paths_build_glade("action-2.glade"), "action_dbox",
	     PACKAGE);
	if (!xml)
		g_error(_("action.c: GUI loading failed !\n"));
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "action_dbox");
	clist = data = glade_xml_get_widget(xml, "treeview1");

	// clist creation
	create_clist(data);

	// fill model
	for (sel = clist_win.selection; sel != NULL; sel = sel->next) {
		TilpFileInfo *f = (TilpFileInfo *) sel->data;
		if (tifiles_is_a_flash_file(f->name))
			return BUTTON1;	// skip box
		else if (tifiles_is_a_regular_file(f->name)) {
			if (tilp_error
			    (tifiles_read_regular_file(f->name, &content)))
				return BUTTON2;	// abort operation
			f->actions =
			    ticalc_create_action_array(content.
						       num_entries);

			// parse each file for existing vars in dirlist
			for (i = 0; i < content.num_entries; i++) {
				TiVarEntry *ve_src = &(content.entries[i]);
				TiVarEntry *ve_dst = NULL;
				TilpAction *ta =
				    g_malloc0(1 * sizeof(TilpAction));
				gchar **row_text =
				    g_malloc0(5 * sizeof(gchar *));
				char trans[18];
				gchar full_name[19];

				strcpy(f->actions[i] + 1, ve_src->name);
				tifiles_build_fullname(full_name,
						       ve_src->folder,
						       ve_src->name);
				ve_dst =
				    ticalc_check_if_var_exists(ctree_win.var_tree /* ctree_win.dirlist*/,
							       full_name);
				if (ve_dst == NULL)
					continue;

				// file contain an already existing var...
				strcpy(ta->varname, full_name);
				ta->varattr = ve_dst->attr;
				ta->filename = g_strdup(f->name);
				ta->action = f->actions[i];
				ta->action[0] =
				    (ta->varattr !=
				     ATTRB_NONE) ? ACT_SKIP : ACT_OVER;
				tifiles_translate_varname(ta->varname,
							  trans,
							  ve_dst->type);

				// add it to the window
				row_text[0] = g_strdup(trans);
				row_text[1] =
				    g_strdup(tifiles_attribute_to_string
					     (ta->varattr));
				row_text[2] = g_strdup(ta->filename);
				row_text[3] =
				    g_strdup((ta->action[0] ==
					      ACT_SKIP) ? _("skip") :
					     _("overwrite"));
				gtk_list_store_append(list, &iter);
				gtk_list_store_set(list, &iter,
						   COLUMN_VAR,
						   row_text[0],
						   COLUMN_ATTR,
						   row_text[1],
						   COLUMN_FILE,
						   row_text[2],
						   COLUMN_ACTION,
						   row_text[3],
						   COLUMN_DATA,
						   (gpointer) ta, -1);
				g_strfreev(row_text);
			}
			tifiles_free_regular_content(&content);
		}
	}

	// box running
	gtk_dialog_set_default_response(GTK_DIALOG(dbox),
					GTK_RESPONSE_CANCEL);
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) {
	case GTK_RESPONSE_OK:
		button = BUTTON1;
		break;
	case GTK_RESPONSE_CANCEL:
		button = BUTTON2;
	default:
                button = BUTTON2;
		break;
	}

	// free memory...
	free_actions();
	gtk_widget_destroy(dbox);

	return button;
}

GLADE_CB void action_overwrite_clicked(GtkButton * button,
				       gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;
	TilpAction *ta;
	for (valid = gtk_tree_model_get_iter_first(model, &iter); valid;
	     valid = gtk_tree_model_iter_next(model, &iter)) {
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ta, -1);
		if (!ta->selected)
			continue;
		if (ta->varattr != ATTRB_NONE)
			continue;
		ta->action[0] = ACT_OVER;
		gtk_list_store_set(list, &iter, COLUMN_ACTION,
				   _("overwrite"), -1);
	}
}

GLADE_CB void action_rename_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;

	for (valid = gtk_tree_model_get_iter_first(model, &iter); valid;
	     valid = gtk_tree_model_iter_next(model, &iter)) {
		TilpAction *ta;
		TiVarEntry *ve_dst;
		gchar *new_name = NULL;
		gchar **row_text = g_malloc0(5 * sizeof(gchar *));
		char trans[18];
		char full_name[19];

		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ta, -1);
		if (!ta->selected)
			continue;
		ta->action[0] = ACT_OVER;

		// get new name
		new_name =
		    gif->msg_entry(_("Rename the file"), _("New name: "),
				   tifiles_get_varname(ta->varname));
		if (new_name == NULL)
			continue;
		tifiles_build_fullname(full_name,
				       tifiles_get_fldname(ta->varname),
				       new_name);

		// check that new varname does not exist
		ve_dst =
		    ticalc_check_if_var_exists(ctree_win.var_tree /*ctree_win.dirlist*/,
					       full_name);
		strcpy(ta->varname, full_name);
		g_free(new_name);

		// update action
		ta->varattr = (ve_dst != NULL) ? ve_dst->attr : ATTRB_NONE;
		ta->action[0] =
		    (ta->varattr != ATTRB_NONE) ? ACT_SKIP : ACT_OVER;
		strcpy(ta->action + 1, tifiles_get_varname(full_name));
		if (ve_dst != NULL)
			tifiles_translate_varname(ta->varname, trans,
						  ve_dst->type);
		else
			strcpy(trans, ta->varname);

		// update entry
		row_text[0] = g_strdup(trans);
		row_text[1] =
		    g_strdup(tifiles_attribute_to_string(ta->varattr));
		row_text[3] =
		    g_strdup((ta->action[0] ==
			      ACT_SKIP) ? _("skip") : _("overwrite"));
		gtk_list_store_set(list, &iter, COLUMN_VAR, row_text[0],
				   COLUMN_ATTR, row_text[1], COLUMN_ACTION,
				   row_text[3], -1);
		g_strfreev(row_text);   //bug
	}
}

GLADE_CB void action_skip_clicked(GtkButton * button, gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreeIter iter;
	gboolean valid;
	TilpAction *ta;

	for (valid = gtk_tree_model_get_iter_first(model, &iter); valid;
	     valid = gtk_tree_model_iter_next(model, &iter)) {
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ta, -1);
		if (!ta->selected)
			continue;
		ta->action[0] = ACT_SKIP;
		gtk_list_store_set(list, &iter, COLUMN_ACTION, "skip", -1);
	}
}

GLADE_CB void action_select_all_clicked(GtkButton * button,
					gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist);
	GtkTreeSelection *sel;
	
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_select_all(sel);
} 

GLADE_CB void action_deselect_all_clicked(GtkButton * button,
					  gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist);
	GtkTreeSelection *sel;
	
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_unselect_all(sel);
}
