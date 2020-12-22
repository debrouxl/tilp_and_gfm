/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "support.h"
#include "gstruct.h"
#include "labels.h"
#include "screenshot.h"
#include "tilp.h"
#include "ctree.h"
#include "ctree_rbm.h"
#include "clock.h"
#include "toolbar.h"
#include "tilp_core.h"

#if !GTK_CHECK_VERSION(2,24,0)
#define GDK_KEY_D GDK_D
#define GDK_KEY_d GDK_d
#define GDK_KEY_O GDK_O
#define GDK_KEY_o GDK_o
#define GDK_KEY_Delete GDK_Delete
#define GDK_KEY_Insert GDK_Insert
#endif

#if GTK_CHECK_VERSION(3,10,0)
#define GTK_STOCK_DIRECTORY "folder"
#endif

static GtkTreeStore *tree;

#define FONT_NAME ""	//"courier"	// use my or TI font ?

// MUST be the same in dnd.c
enum
{
	COLUMN_NAME, COLUMN_ATTR, COLUMN_TYPE, COLUMN_SIZE,
	COLUMN_DATA, COLUMN_FONT, COLUMN_ICON
};

#define CTREE_NVCOLS	(4)		// 4 visible columns
#define CTREE_NCOLS		(7)		// 7 real columns

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

	if (ve->type == tifiles_folder_type(options.calc_model))
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

		if (ve->type != tifiles_flash_type(options.calc_model))
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
}

static void column_clicked(GtkTreeViewColumn* column, gpointer user_data)
{
	int col = column2index(user_data, column);
	GtkSortType sort1 = gtk_tree_view_column_get_sort_order(column);
	GtkSortType sort2 = (options.remote_sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);

	if(sort1 == sort2)
	{
		options.remote_sort_order = !options.remote_sort_order;
		ctree_refresh();
	}
	
	switch(col)
	{
	case COLUMN_NAME:
		options.remote_sort = SORT_BY_NAME;
		ctree_refresh();
		break;
	case COLUMN_TYPE:
		options.remote_sort = SORT_BY_TYPE;
		ctree_refresh();
		break;
	case COLUMN_SIZE:
		options.remote_sort = SORT_BY_SIZE;
		ctree_refresh();
		break;
	case COLUMN_ATTR:
		options.remote_sort = SORT_BY_INFO;
		ctree_refresh();
		break;
	default: break;
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

		gtk_tree_view_column_set_clickable(col, TRUE);
		g_signal_connect(G_OBJECT(col), "clicked", G_CALLBACK(column_clicked), view);
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
	GtkTreeIter clc_node;
	GtkTreeIter *top_node = NULL;
	GtkTreeIter lcd_node, rom_node, idl_node, clk_node;
	gchar* str;

	// clear tree
	gtk_tree_store_clear(tree);

	// top node
	str = g_strdup_printf(_("%s -> %s:#%i"), tifiles_model_to_string(options.calc_model),
		ticables_model_to_string(options.cable_model), options.cable_port);

	top_node = &clc_node;
	gtk_tree_store_append(tree, top_node, NULL);
	gtk_tree_store_set(tree, &clc_node,
		COLUMN_NAME, str,
		COLUMN_DATA, (gpointer) NULL, -1);
	g_free(str);

	// lcd, rom, vars & apps nodes
	gtk_tree_store_append(tree, &lcd_node, top_node);
	gtk_tree_store_set(tree, &lcd_node, COLUMN_NAME, NODE1,
			   COLUMN_DATA, (gpointer) NULL, -1);

	gtk_tree_store_append(tree, &rom_node, top_node);
	gtk_tree_store_set(tree, &rom_node, COLUMN_NAME, NODE2,
			   COLUMN_DATA, (gpointer) NULL, -1);

	gtk_tree_store_append(tree, &vars_node, top_node);
	gtk_tree_store_set(tree, &vars_node, COLUMN_NAME, NODE3,
			   COLUMN_DATA, (gpointer) NULL, -1);

	if (tifiles_is_flash(options.calc_model))
	{
		gtk_tree_store_append(tree, &apps_node, top_node);
		gtk_tree_store_set(tree, &apps_node, COLUMN_NAME, NODE4,
				   COLUMN_DATA, (gpointer) NULL, -1);

		gtk_tree_store_append(tree, &idl_node, top_node);
		gtk_tree_store_set(tree, &idl_node, COLUMN_NAME, NODE5,
				   COLUMN_DATA, (gpointer) NULL, -1);

		gtk_tree_store_append(tree, &clk_node, top_node);
		gtk_tree_store_set(tree, &clk_node, COLUMN_NAME, NODE6,
				   COLUMN_DATA, (gpointer) NULL, -1);
	}

	gtk_tree_view_expand_all(GTK_TREE_VIEW(ctree_wnd));
}

/* Management */

void ctree_refresh(void)
{
	GtkTreeView *view = GTK_TREE_VIEW(ctree_wnd);
	GtkTreeViewColumn *col;
	GdkPixbuf *pix1, *pix2, *pix3, *pix4, *pix5, *pix6;
	GdkPixbuf *pix9 = NULL;
	GdkPixbuf *pix_file = NULL;
	GtkTreeIter parent_node;
	GtkTreeIter child_node;
	GtkIconTheme *theme;
	GNode *vars, *apps;
	int i, j;

	const uint8_t folder_type_for_model = tifiles_folder_type(options.calc_model);

	if (remote.var_tree == NULL)
		return;

	if(working_mode & MODE_CMD)
		return;

	// sort variables
	for(i = 0; i < CTREE_NVCOLS; i++)
	{
		col = gtk_tree_view_get_column(view, i);
		gtk_tree_view_column_set_sort_indicator(col, FALSE);
	}

	switch (options.remote_sort)
	{
	case SORT_BY_NAME:
		tilp_vars_sort_by_name();
		col = gtk_tree_view_get_column(view, COLUMN_NAME);
		gtk_tree_view_column_set_sort_indicator(col, TRUE);
		gtk_tree_view_column_set_sort_order(col, options.remote_sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);
		break;
	case SORT_BY_INFO:
		tilp_vars_sort_by_info();
		col = gtk_tree_view_get_column(view, COLUMN_ATTR);
		gtk_tree_view_column_set_sort_indicator(col, TRUE);
		gtk_tree_view_column_set_sort_order(col, options.remote_sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);
		break;
	case SORT_BY_TYPE:
		tilp_vars_sort_by_type();
		col = gtk_tree_view_get_column(view, COLUMN_TYPE);
		gtk_tree_view_column_set_sort_indicator(col, TRUE);
		gtk_tree_view_column_set_sort_order(col, options.remote_sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);
		break;
	case SORT_BY_SIZE:
		tilp_vars_sort_by_size();
		col = gtk_tree_view_get_column(view, COLUMN_SIZE);
		gtk_tree_view_column_set_sort_indicator(col, TRUE);
		gtk_tree_view_column_set_sort_order(col, options.remote_sort_order ? GTK_SORT_ASCENDING : GTK_SORT_DESCENDING);
		break;
	}

	// place base nodes
	ctree_set_basetree();
	memcpy(&parent_node, &vars_node, sizeof(GtkTreeIter));

	// load pixmaps
	theme = gtk_icon_theme_get_default();
	pix1 = gtk_icon_theme_load_icon(theme, GTK_STOCK_DIRECTORY, 16, 0, NULL);
	pix_file = create_pixbuf("TIicon1.ico");
	pix2 = create_pixbuf("TIicon2.ico");
	pix3 = gtk_icon_theme_load_icon(theme, "folder-open", 16, 0, NULL);
	if (pix3 == NULL)
	{
		pix3 = create_pixbuf("ctree_open_dir.png");
	}
	pix4 = gtk_icon_theme_load_icon(theme, "emblem-readonly", 16, 0, NULL);
	if (pix4 == NULL)
	{
		pix4 = create_pixbuf("attr_locked.png");
	}
	pix5 = gtk_icon_theme_load_icon(theme, "emblem-system", 16, 0, NULL);
	if (pix5 == NULL)
	{
		pix5 = create_pixbuf("attr_archived.png");
	}
	pix6 = create_pixbuf("TIicon4.ico");

	// variables tree
	vars = remote.var_tree;
	for (i = 0; i < (int)g_node_n_children(vars); i++)
	{
		GNode *parent = g_node_nth_child(vars, i);
		VarEntry *fe = (VarEntry *) (parent->data);

		if ((fe != NULL) && (ticalcs_calc_features(calc_handle) & FTS_FOLDER))
		{
			char *utf8 = ticonv_varname_to_utf8(options.calc_model, fe->name, -1);

			gtk_tree_store_append(tree, &parent_node, &vars_node);
			if (fe->type == folder_type_for_model)
			{
				gtk_tree_store_set(tree, &parent_node,
						   COLUMN_NAME, utf8,
						   COLUMN_DATA, (gpointer) fe,
						   COLUMN_ICON, pix1, -1);
			}
			else
			{
				gchar **row_text = g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
				row_text[2] = g_strdup_printf("%s", tifiles_vartype2string(options.calc_model, fe->type));
				tilp_var_get_size(fe, &row_text[3]);
				gtk_tree_store_set(tree, &parent_node,
						   COLUMN_NAME, utf8,
						   COLUMN_TYPE, row_text[2],
						   COLUMN_SIZE, row_text[3],
						   COLUMN_DATA, (gpointer) fe,
						   COLUMN_ICON, pix_file, -1);
				g_strfreev(row_text);
			}
			ticonv_utf8_free(utf8);
		}

		for (j = 0; j < (int)g_node_n_children(parent); j++)
		{
			GNode *node = g_node_nth_child(parent, j);
			gchar **row_text = g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
			VarEntry *ve = (VarEntry *) (node->data);
			char icon_name[256];
			char * utf8 = ticonv_varname_to_utf8(options.calc_model, ve->name, ve->type);

			row_text[0] = g_strdup(utf8); ticonv_utf8_free(utf8);
			row_text[2] = g_strdup_printf("%s", tifiles_vartype2string(options.calc_model, ve->type));
			tilp_var_get_size(ve, &row_text[3]);

			strcpy(icon_name, tifiles_vartype2icon(options.calc_model, ve->type));
			strcat(icon_name, ".ico");
			tilp_file_underscorize(icon_name);
			pix9 = create_pixbuf(icon_name);

			// ticonv wrapper
			tilp_vars_translate(row_text[0]);

			gtk_tree_store_append(tree, &child_node, &parent_node);
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
	apps = remote.app_tree;
	for (i = 0; i < (int)g_node_n_children(apps); i++)
	{
		GNode *parent = g_node_nth_child(apps, i);

		for (j = 0; j < (int)g_node_n_children(parent); j++)
		{
			GNode *node = g_node_nth_child(parent, j);
			gchar **row_text = g_malloc0((CTREE_NCOLS + 1) * sizeof(gchar *));
			VarEntry *ve = (VarEntry *) (node->data);
			char icon_name[256];
			char * utf8 = ticonv_varname_to_utf8(options.calc_model, ve->name, ve->type);

			row_text[0] = g_strdup(utf8); ticonv_utf8_free(utf8);
			row_text[2] = g_strdup_printf("%s", tifiles_vartype2string(options.calc_model, ve->type));
			row_text[3] = g_strdup_printf("%u", (int) (ve->size));

			strcpy(icon_name, tifiles_vartype2icon(options.calc_model, ve->type));
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
	gtk_tree_view_expand_all(GTK_TREE_VIEW(ctree_wnd));

	g_object_unref(pix_file);
	g_object_unref(pix1);
	g_object_unref(pix2);
	g_object_unref(pix3);
	g_object_unref(pix4);
	g_object_unref(pix5);
	g_object_unref(pix6);

	tilp_remote_selection_destroy();
}

/* Callbacks */

gchar *name_to_drag = NULL;
GtkTreePath *path_to_drag = NULL;

TILP_EXPORT gboolean on_treeview1_button_press_event(GtkWidget * widget, GdkEventButton * event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(ctree_wnd);
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

	if(event->type == GDK_BUTTON_PRESS)
	{
		if(event->button == 1)
		{
			/*
			printf("clicked !\n");
			ctree_select_vars(!0);
			printf("selected ?!\n");
*/
		}
		else if (event->button == 3)
		{
			GdkEventButton *bevent = (GdkEventButton *) (event);

			gtk_menu_popup(GTK_MENU(create_ctree_rbm()),
				       NULL, NULL, NULL, NULL,
				       bevent->button, bevent->time);

			return TRUE;
		}
	}

	if (event->type == GDK_2BUTTON_PRESS)
	{
		gchar *name;

		gtk_tree_model_get(model, &parent, COLUMN_NAME, &name, -1);
		if (!strcmp(name, NODE1))
			display_screenshot_dbox();

		else if (!strcmp(name, NODE2))
			on_rom_dump1_activate(NULL, NULL);

		else if (!strcmp(name, NODE3))
			on_tilp_button3_clicked(NULL, NULL);

		else if(!strcmp(name, NODE5))
			tilp_calc_idlist(0);

		else if(!strcmp(name, NODE6))
			display_clock_dbox();

		else if(!strncmp(name, tifiles_model_to_string(options.calc_model), 4))
		{
			CalcInfos infos;
			tilp_calc_get_infos(&infos);
		}

		return TRUE;
	}

	if (ve == NULL)
		return FALSE;

	if (ve->type != tifiles_folder_type(options.calc_model))
		return FALSE;

	name_to_drag = NODEx;

	return FALSE;		// pass the event on
}

#include <gdk/gdkkeysyms.h>


/* Key pressed */
TILP_EXPORT gboolean on_treeview1_key_press_event(GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	if ((event->state == GDK_CONTROL_MASK) &&
	    ((event->keyval == GDK_KEY_D) || (event->keyval == GDK_KEY_d)))
	{
		rbm_change_device1_activate(NULL, NULL);
		return TRUE;
	}
	if ((event->state == GDK_CONTROL_MASK) &&
	    ((event->keyval == GDK_KEY_O) || (event->keyval == GDK_KEY_o)))
	{
		rbm_options1_activate(NULL, NULL);
		return TRUE;
	}
	if (event->keyval == GDK_KEY_Delete)
	{
		rbm_delete_var1_activate(NULL, NULL);
		return TRUE;
	}
	if (event->keyval == GDK_KEY_Insert)
	{
		rbm_create_folder1_activate(NULL, NULL);
		return TRUE;
	}
	
	return FALSE;
}

void ctree_select_vars(gint action)
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
		{
			gtk_tree_selection_select_range(sel, start_path, end_path);
		}

		gtk_tree_path_free(start_path);
		gtk_tree_path_free(end_path);
	}
}
