/* Hey EMACS -*- linux-c -*- */
/* $Id: ctree.c 3250 2007-04-03 15:50:21Z roms $ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2007  Romain Lievin
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "support.h"
#include "ctree.h"
#include "tilibs.h"
#include "groups.h"
#include "file.h"

static GtkTreeStore *tree;

#define FONT_NAME "courier"

/* Initialization */

static gint column2index(GtkWidget* list, GtkTreeViewColumn* column)
{
	gint i;

	for (i = 0; i < CTREE_NVCOLS; i++) 
	{
		GtkTreeViewColumn *col;

		col = gtk_tree_view_get_column(GTK_TREE_VIEW(list), i);
		if (col == column)
			return i;
	}

	return -1;
}

static gboolean select_func(GtkTreeSelection * selection,
			    GtkTreeModel * model,
			    GtkTreePath * path,
			    gboolean path_currently_selected,
			    gpointer data)
{
	GtkTreeIter iter;
	VarEntry *ve;

	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, COLUMN_DATA, &ve, -1);

	if (ve == NULL)
		return FALSE;

	if (ve->type == tifiles_folder_type(GFile.model))
		return FALSE;

	return TRUE;
}

static void tree_selection_changed(GtkTreeSelection * selection,
				   gpointer user_data)
{
#if 0
	GList *list;
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreeSelection *sel;

	// destroy selection
	tilp_remote_selection_destroy();

	// clear clist selection(one selection active at a time)
	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(clist_wnd));
	gtk_tree_selection_unselect_all(sel);

	// create a new selection
	for (list = gtk_tree_selection_get_selected_rows(selection, &model);
	     list != NULL; list = list->next) 
	{
		GtkTreePath *path = list->data;
		VarEntry *ve;
		
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &ve, -1);

		if (ve->type != tifiles_flash_type(GFile.model)) 
		{
			remote.selection1 = g_list_append(remote.selection1, ve);
		} 
		else 
		{
			remote.selection2 = g_list_append(remote.selection2, ve);
		}
	}

	g_list_foreach(list, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(list);
#endif
}

void ctree_init(void)
{
	GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.tree);
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;
	GtkTreeViewColumn *column;
	gint i;

	tree = gtk_tree_store_new(CTREE_NCOLS, G_TYPE_STRING,
				  GDK_TYPE_PIXBUF, G_TYPE_STRING,
				  G_TYPE_STRING, G_TYPE_POINTER,
				  G_TYPE_STRING, GDK_TYPE_PIXBUF);
	model = GTK_TREE_MODEL(tree);

	gtk_tree_view_set_model(view, model);
	gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_headers_clickable(view, TRUE);
	gtk_tree_view_set_rules_hint(view, FALSE);

	column = gtk_tree_view_column_new();
	gtk_tree_view_append_column(view, column);
	gtk_tree_view_column_set_title(column, _("Name"));

	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer, "pixbuf",
					    COLUMN_ICON, NULL);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer, "text", COLUMN_NAME,
						"font", COLUMN_FONT,
					    NULL);

	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Attr"),
						    renderer, "pixbuf",
						    COLUMN_ATTR, NULL);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Type"),
						    renderer, "text",
						    COLUMN_TYPE, NULL);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Size"),
						    renderer, "text",
						    COLUMN_SIZE, NULL);

	for (i = 0; i < CTREE_NVCOLS; i++) 
	{
		GtkTreeViewColumn *col;
		col = gtk_tree_view_get_column(view, i);
		gtk_tree_view_column_set_resizable(col, TRUE);
	}

	selection = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(selection, select_func, NULL, NULL);
	g_signal_connect(G_OBJECT(selection), "changed", G_CALLBACK(tree_selection_changed), NULL);

	ctree_set_basetree();
}

static GtkTreeIter vars_node;
static GtkTreeIter apps_node;

void ctree_set_basetree(void)
{
	GtkTreeIter *top_node = NULL;

	// clear tree
	gtk_tree_store_clear(tree);

	gtk_tree_store_append(tree, &vars_node, top_node);
	gtk_tree_store_set(tree, &vars_node, COLUMN_NAME, NODE3,
			   COLUMN_DATA, (gpointer) NULL, -1);

	if (tifiles_is_flash(GFile.model)) 
	{
		gtk_tree_store_append(tree, &apps_node, top_node);
		gtk_tree_store_set(tree, &apps_node, COLUMN_NAME, NODE4,
				   COLUMN_DATA, (gpointer) NULL, -1);
	}

	gtk_tree_view_expand_all(GTK_TREE_VIEW(gfm_widget.tree));
}

/* Management */

void ctree_refresh(void)
{
	GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.tree);
	GdkPixbuf *pix1, *pix2, *pix3, *pix4, *pix5, *pix6;
	GdkPixbuf *pix9 = NULL;
	GtkTreeIter pareng_node;
	GtkTreeIter child_node;
	GNode *vars, *apps;
	int i, j;

	if (GFile.trees.vars == NULL)
		return;

	// place base nodes
	ctree_set_basetree();
	memcpy(&pareng_node, &vars_node, sizeof(GtkTreeIter));

	// load pixmaps
	pix1 = create_pixbuf("ctree_close_dir.xpm");
	pix2 = create_pixbuf("TIicon2.ico");
	pix3 = create_pixbuf("ctree_open_dir.xpm");
	pix4 = create_pixbuf("attr_locked.xpm");
	pix5 = create_pixbuf("attr_archived.xpm");
	pix6 = create_pixbuf("TIicon4.ico");

	// variables tree
	vars = GFile.trees.vars;
	for (i = 0; i < (int)g_node_n_children(vars); i++) 
	{
		GNode *parent = g_node_nth_child(vars, i);
		VarEntry *fe = (VarEntry *) (parent->data);

		if ((fe != NULL) || tifiles_calc_is_ti9x(GFile.model))
		{
			char *utf8 = ticonv_varname_to_utf8(GFile.model, fe->name);

			gtk_tree_store_append(tree, &pareng_node, &vars_node);
			gtk_tree_store_set(tree, &pareng_node, 
					   COLUMN_NAME, utf8, 
					   COLUMN_DATA, (gpointer) fe,
					   COLUMN_ICON, pix1, -1);
			g_free(utf8);
		}

		for (j = 0; j < (int)g_node_n_children(parent); j++) 
		{
			GNode *node = g_node_nth_child(parent, j);
			gchar **row_text = g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
			VarEntry *ve = (VarEntry *) (node->data);
			char icon_name[256];

			row_text[0] = ticonv_varname_to_utf8(GFile.model, ve->name);
			row_text[2] = g_strdup_printf("%s", tifiles_vartype2string(GFile.model, ve->type));
			tilp_var_get_size(ve, &row_text[3]);

			strcpy(icon_name, tifiles_vartype2icon(GFile.model, ve->type));
			strcat(icon_name, ".ico");
			tilp_file_underscorize(icon_name);
			pix9 = create_pixbuf(icon_name);

			// ticonv wrapper
			tilp_vars_translate(row_text[0]);

			gtk_tree_store_append(tree, &child_node, &pareng_node);
			gtk_tree_store_set(tree, &child_node, COLUMN_NAME,
					   row_text[0],
					   COLUMN_TYPE,
					   row_text[2], COLUMN_SIZE,
					   row_text[3], COLUMN_DATA,
					   (gpointer) ve, COLUMN_ICON, pix9,
					   COLUMN_FONT, FONT_NAME,
					   -1);

			switch (ve->attr) 
			{
			case ATTRB_LOCKED:
				gtk_tree_store_set(tree, &child_node, COLUMN_ATTR, pix4, -1);
				break;
			case ATTRB_ARCHIVED:
				gtk_tree_store_set(tree, &child_node, COLUMN_ATTR, pix5, -1);
				break;
			default:
				break;
			}
			g_object_unref(pix9);
			g_strfreev(row_text);
		}
	}

	// Appplications tree
	apps = GFile.trees.apps;
	for (i = 0; i < (int)g_node_n_children(apps) && tifiles_is_flash(GFile.model); i++) 
	{
		GNode *parent = g_node_nth_child(apps, i);

		for (j = 0; j < (int)g_node_n_children(parent); j++) 
		{
			GNode *node = g_node_nth_child(parent, j);
			gchar **row_text = g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
			VarEntry *ve = (VarEntry *) (node->data);
			char icon_name[256];

			row_text[0] = ticonv_varname_to_utf8(GFile.model, ve->name);
			row_text[2] = g_strdup_printf("%s", tifiles_vartype2string(GFile.model, ve->type));
			row_text[3] = g_strdup_printf("%u", (int) (ve->size));

			strcpy(icon_name, tifiles_vartype2icon(GFile.model, ve->type));
			strcat(icon_name, ".ico");
			tilp_file_underscorize(icon_name);
			pix9 = create_pixbuf(icon_name);

			gtk_tree_store_append(tree, &child_node, &apps_node);
			gtk_tree_store_set(tree, &child_node, 
					COLUMN_NAME, row_text[0], 
					COLUMN_TYPE, row_text[2],
					COLUMN_SIZE, row_text[3], 
					COLUMN_DATA, (gpointer) ve, 
					COLUMN_ICON, pix9,
					COLUMN_FONT, FONT_NAME,
					   -1);
			g_object_unref(pix9);
			g_strfreev(row_text);
		}
	}
	gtk_tree_view_expand_all(GTK_TREE_VIEW(gfm_widget.tree));

	g_object_unref(pix1);
	g_object_unref(pix2);
	g_object_unref(pix3);
	g_object_unref(pix4);
	g_object_unref(pix5);
	g_object_unref(pix6);

	//tilp_remote_selection_destroy();
}

/* Callbacks */

gchar *name_to_drag = NULL;
GtkTreePath *path_to_drag = NULL;

GLADE_CB gboolean
on_treeview1_button_press_event(GtkWidget * widget,
				GdkEventButton * event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(gfm_widget.tree);
	GtkTreeModel *model = GTK_TREE_MODEL(tree);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter parent;
	VarEntry *ve;
	gint tx = (gint) event->x;
	gint ty = (gint) event->y;
	gint cx, cy;
	gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx, &cy);

	if (path == NULL)
		return FALSE;

	gtk_tree_model_get_iter(model, &parent, path);
	gtk_tree_model_get(model, &parent, COLUMN_DATA, &ve, -1);

	path_to_drag = path;
	gtk_tree_model_get(model, &parent, COLUMN_NAME, &name_to_drag, -1);

	if (ve == NULL)
		return FALSE;

	if (ve->type != tifiles_folder_type(GFile.model))
		return FALSE;

	name_to_drag = NODEx;

	return FALSE;		// pass the event on
}

#include <gdk/gdkkeysyms.h>


/* Key pressed */
GLADE_CB gboolean
on_treeview1_key_press_event(GtkWidget* widget, GdkEventKey* event,
								gpointer user_data)
{	
	return FALSE;
}

void ctree_select_vars(gint action)
{
	GtkTreeView *view;
	GtkTreeModel *model;
	GtkTreePath *path = path_to_drag;
	GtkTreeIter parent, start_iter, end_iter, iter;
	view = GTK_TREE_VIEW(gfm_widget.tree);
	model = gtk_tree_view_get_model(view);

	// select var beneath a folder
	gtk_tree_model_get_iter(model, &parent, path);

	if (gtk_tree_model_iter_has_child(model, &parent)) 
	{
		GtkTreeSelection *sel;
		GtkTreePath *start_path, *end_path;
		gint n;
		gboolean valid;

		sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(gfm_widget.tree));
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
		{
			gtk_tree_selection_select_range(sel, start_path, end_path);
			printf("!!!\n");
		}

		gtk_tree_path_free(start_path);
		gtk_tree_path_free(end_path);
	}
}

