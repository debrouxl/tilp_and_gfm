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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <pango/pango.h>

//#include <tilp/tnode.h>//#include "tilibs.h"
#include "tilp_core.h"

#include "gstruct.h"
#include "support.h"
#include "labels.h"
#include "popup.h"
#include "screenshot.h"
#include "tilp.h"
#include "ctree.h"

static GtkTreeStore *tree;

#define FONT_NAME ""	//"courier"

/******************/
/* Initialization */
/******************/
static gboolean select_func(GtkTreeSelection * selection,
			    GtkTreeModel * model,
			    GtkTreePath * path,
			    gboolean path_currently_selected,
			    gpointer data)
{
	GtkTreeIter iter;
	TiVarEntry *ve;
	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, CTREE_DATA, &ve, -1);
	if (ve == NULL)
		return FALSE;
	if (ve->type == tifiles_folder_type())
		return FALSE;
	return TRUE;
}

static void tree_selection_changed(GtkTreeSelection * selection,
				   gpointer user_data)
{
	GList *list;
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreeSelection *sel;

	// destroy selection
	tilp_ctree_selection_destroy();

	// clear clist selection(one selection active at a time)
	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(clist_wnd));
	gtk_tree_selection_unselect_all(sel);

	// create a new selection
	for (list =
	     gtk_tree_selection_get_selected_rows(selection, &model);
	     list != NULL; list = list->next) {
		GtkTreePath *path = list->data;
		TiVarEntry *ve;
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, CTREE_DATA, &ve, -1);
		if (ve->type != tifiles_flash_type()) {
			ctree_win.selection =
			    g_list_append(ctree_win.selection, ve);
		} else {
			ctree_win.selection2 =
			    g_list_append(ctree_win.selection2, ve);
		}
	}
}

void ctree_init(void)
{
	GtkTreeView *view = GTK_TREE_VIEW(ctree_wnd);
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;
	GtkTreeViewColumn *column;
	gint i;
	
	tifiles_translate_set_encoding(ENCODING_UNICODE);

	tree = gtk_tree_store_new(CTREE_NUMBER, G_TYPE_STRING,
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
					    CTREE_ICON, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(GTK_TREE_VIEW_COLUMN(column),
					renderer, FALSE);
	gtk_tree_view_column_set_attributes(GTK_TREE_VIEW_COLUMN(column),
					    renderer, "text", CTREE_NAME,
						"font", CTREE_FONT,
					    NULL);
	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Attr"),
						    renderer, "pixbuf",
						    CTREE_ATTR, NULL);
// window appear here, why ?
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Type"),
						    renderer, "text",
						    CTREE_TYPE, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Size"),
						    renderer, "text",
						    CTREE_SIZE, NULL);
	for (i = 0; i < CTREE_NCOLS; i++) {
		GtkTreeViewColumn *col;
		col = gtk_tree_view_get_column(view, i);
		gtk_tree_view_column_set_resizable(col, TRUE);
	}
	selection = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(selection, select_func,
					       NULL, NULL);
	g_signal_connect(G_OBJECT(selection), "changed",
			 G_CALLBACK(tree_selection_changed), NULL);
	ctree_set_basetree();
}

static GtkTreeIter vars_node;
static GtkTreeIter apps_node;

void ctree_set_basetree(void)
{
	GtkTreeIter lcd_node, rom_node;

	// clear tree
	gtk_tree_store_clear(tree);

	// lcd, rom, vars & apps nodes
	gtk_tree_store_append(tree, &lcd_node, NULL);
	gtk_tree_store_set(tree, &lcd_node, CTREE_NAME, NODE1,
			   CTREE_DATA, (gpointer) NULL, -1);
	gtk_tree_store_append(tree, &rom_node, NULL);
	gtk_tree_store_set(tree, &rom_node, CTREE_NAME, NODE2,
			   CTREE_DATA, (gpointer) NULL, -1);
	gtk_tree_store_append(tree, &vars_node, NULL);
	gtk_tree_store_set(tree, &vars_node, CTREE_NAME, NODE3,
			   CTREE_DATA, (gpointer) NULL, -1);
	if (tifiles_is_flash(options.lp.calc_type)) {
		gtk_tree_store_append(tree, &apps_node, NULL);
		gtk_tree_store_set(tree, &apps_node, CTREE_NAME, NODE4,
				   CTREE_DATA, (gpointer) NULL, -1);
	}
}


/**************/
/* Management */
/**************/

void ctree_refresh(void)
{
	GdkPixbuf *pix1, *pix2, *pix3, *pix4, *pix5, *pix6;
	GdkPixbuf *pix9 = NULL;
	GtkTreeIter parent_node;
	GtkTreeIter child_node;
	TNode *vars, *apps;
	int i, j;

	// check for a valid tree
#if defined(DIRLIST_FORM1)
	if (ctree_win.dirlist == NULL)
		return;
#elif defined(DIRLIST_TRANS) || defined(DIRLIST_FORM2)
	if (ctree_win.var_tree == NULL)
		return;
#endif

	// sort variables
	switch (options.ctree_sort) {
	case SORT_BY_NAME:
		tilp_sort_vars_by_name();
		break;
	case SORT_BY_INFO:
		tilp_sort_vars_by_info();
		break;
	case SORT_BY_TYPE:
		tilp_sort_vars_by_type();
		break;
	case SORT_BY_SIZE:
		tilp_sort_vars_by_size();
		break;
	}

	// place base nodes
	ctree_set_basetree();
	memcpy(&parent_node, &vars_node, sizeof(GtkTreeIter));

	// load pixmaps
	pix1 = create_pixbuf("ctree_close_dir.xpm");
	pix2 = create_pixbuf("TIicon2.ico");
	pix3 = create_pixbuf("ctree_open_dir.xpm");
	pix4 = create_pixbuf("attr_locked.xpm");
	pix5 = create_pixbuf("attr_archived.xpm");
	pix6 = create_pixbuf("TIicon4.ico");

	// variables tree
#if defined(DIRLIST_FORM1)
	vars = t_node_nth_child(ctree_win.dirlist, 0);
#elif defined(DIRLIST_TRANS) || defined(DIRLIST_FORM2) /* DIRLIST_FORM1 */
	vars = ctree_win.var_tree;
#endif				                       /* DIRLIST_FORM2 */
	for (i = 0; i < t_node_n_children(vars); i++) {
		TNode *parent = t_node_nth_child(vars, i);
		TiVarEntry *fe = (TiVarEntry *) (parent->data);
		if ((fe != NULL) || ti_calc.has_folder) {
			gtk_tree_store_append(tree, &parent_node,
					      &vars_node);
			gtk_tree_store_set(tree, &parent_node, 
					   CTREE_NAME, fe->trans, 
					   CTREE_DATA, (gpointer) fe,
					   CTREE_ICON, pix1, -1);
		}

		for (j = 0; j < t_node_n_children(parent); j++) {
			TNode *node = t_node_nth_child(parent, j);
			gchar **row_text =
			    g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
			TiVarEntry *ve = (TiVarEntry *) (node->data);
			char icon_name[256];
			row_text[0] = g_strdup(ve->trans);
			row_text[2] =
			    g_strdup_printf("%s",
					    tifiles_vartype2string(ve->
								   type));
			tilp_var_get_size(ve, &row_text[3]);
			strcpy(icon_name, tifiles_vartype2icon(ve->type));
			strcat(icon_name, ".ico");
			tilp_file_underscorize(icon_name);
			pix9 = create_pixbuf(icon_name);

			gtk_tree_store_append(tree, &child_node,
					      &parent_node);
			gtk_tree_store_set(tree, &child_node, CTREE_NAME,
					   row_text[0],
					   CTREE_TYPE,
					   row_text[2], CTREE_SIZE,
					   row_text[3], CTREE_DATA,
					   (gpointer) ve, CTREE_ICON, pix9,
					   CTREE_FONT, FONT_NAME,
					   -1);
			switch (ve->attr) {
			case ATTRB_LOCKED:
				gtk_tree_store_set(tree, &child_node,
						   CTREE_ATTR, pix4, -1);
				break;
			case ATTRB_ARCHIVED:
				gtk_tree_store_set(tree, &child_node,
						   CTREE_ATTR, pix5, -1);
				break;
			default:
				break;
			}
			g_object_unref(pix9);
			g_strfreev(row_text);
		}
	}

	// Appplications tree
#if defined(DIRLIST_FORM1)
	apps = t_node_nth_child(ctree_win.dirlist, 1);
#elif defined(DIRLIST_TRANS) || defined(DIRLIST_FORM2) /* DIRLIST_FORM1 */
	apps = ctree_win.app_tree;
#endif				                       /* DIRLIST_FORM2 */
	for (i = 0; i < t_node_n_children(apps); i++) {
		TNode *node = t_node_nth_child(apps, i);
		gchar **row_text =
		    g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
		TiVarEntry *ve = (TiVarEntry *) (node->data);
		char icon_name[256];
		row_text[0] = g_strdup(ve->trans);
		row_text[2] =
		    g_strdup_printf("%s",
				    tifiles_vartype2string(ve->type));
		row_text[3] = g_strdup_printf("%u", (int) (ve->size));
		strcpy(icon_name, tifiles_vartype2icon(ve->type));
		strcat(icon_name, ".ico");
		tilp_file_underscorize(icon_name);
		pix9 = create_pixbuf(icon_name);
		gtk_tree_store_append(tree, &child_node, &apps_node);
		gtk_tree_store_set(tree, &child_node, CTREE_NAME,
				   row_text[0], CTREE_TYPE, row_text[2],
				   CTREE_SIZE, row_text[3], CTREE_DATA,
				   (gpointer) ve, CTREE_ICON, pix9,
				   CTREE_FONT, FONT_NAME,
				   -1);
		g_object_unref(pix9);
		g_strfreev(row_text);
	}
	gtk_tree_view_expand_all(GTK_TREE_VIEW(ctree_wnd));
	g_object_unref(pix1);
	g_object_unref(pix2);
	g_object_unref(pix3);
	g_object_unref(pix4);
	g_object_unref(pix5);
	g_object_unref(pix6);
	tilp_ctree_selection_destroy();
}

/*******************/
/* CTree callbacks */
/*******************/

gchar *name_to_drag = NULL;
GtkTreePath *path_to_drag = NULL;

GLADE_CB gboolean
on_treeview1_button_press_event(GtkWidget * widget,
				GdkEventButton * event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(ctree_wnd);
	GtkTreeModel *model = GTK_TREE_MODEL(tree);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter parent;
	TiVarEntry *ve;
	gint tx = (gint) event->x;
	gint ty = (gint) event->y;
	gint cx, cy;
	gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx,
				      &cy);

	if (path == NULL)
		return FALSE;

	gtk_tree_model_get_iter(model, &parent, path);
	gtk_tree_model_get(model, &parent, CTREE_DATA, &ve, -1);

	path_to_drag = path;
	gtk_tree_model_get(model, &parent, CTREE_NAME, &name_to_drag, -1);

	if (event->type == GDK_2BUTTON_PRESS) {
		gchar *name;

		gtk_tree_model_get(model, &parent, CTREE_NAME, &name, -1);
		if (!strcmp(name, NODE1))
			display_screenshot_dbox();

		else if (!strcmp(name, NODE2))
			on_rom_dump1_activate(NULL, NULL);

		else if (!strcmp(name, NODE3))
			on_tilp_button7_clicked(NULL, NULL);
		return TRUE;
	}

	if (ve == NULL)
		return FALSE;
	if (ve->type != tifiles_folder_type())
		return FALSE;

	name_to_drag = NODEx;

	return FALSE;		// pass the event on
}

GLADE_CB gboolean
on_treeview1_button_release_event(GtkWidget * widget,
				  GdkEventButton * event,
				  gpointer user_data)
{
	return FALSE;
}


/* */
