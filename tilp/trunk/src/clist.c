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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>

#ifdef __WIN32__
# include "win32/dirent.h"
#endif				/*  */

#include "tilp_core.h"

#include "gstruct.h"
#include "support.h"
#include "labels.h"
#include "popup.h"

static GtkListStore *list;

enum { COLUMN_NAME, COLUMN_TYPE, COLUMN_SIZE, COLUMN_DATE, COLUMN_DATA,
	COLUMN_ICON, COLUMN_NUMBER
};

#define CLIST_NCOLS COLUMN_DATA


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
	TilpFileInfo *fi;
	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_get(model, &iter, COLUMN_DATA, &fi, -1);
	if (S_ISDIR(fi->attrib))
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
	tilp_clist_selection_destroy();

	// clear ctree selection(one selection active at a time)
	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(ctree_wnd));
	gtk_tree_selection_unselect_all(sel);

	// create a new selection
	list = gtk_tree_selection_get_selected_rows(selection, &model);
	while (list != NULL) {
		GtkTreePath *path = list->data;
		TilpFileInfo *fi;
		gchar *full_path;

		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &fi, -1);

		clist_win.selection =
		    g_list_append(clist_win.selection, fi);
		full_path =
		    g_strconcat(clist_win.current_dir, DIR_SEPARATOR,
				fi->name, NULL);
		clist_win.file_selection =
		    g_list_append(clist_win.file_selection, full_path);
		list = g_list_next(list);
	}
}

void clist_init(void)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;

	gint i;
	list =
	    gtk_list_store_new(COLUMN_NUMBER, G_TYPE_STRING,
			       G_TYPE_STRING, G_TYPE_STRING,
			       G_TYPE_STRING, G_TYPE_POINTER,
			       GDK_TYPE_PIXBUF);
	model = GTK_TREE_MODEL(list);

	gtk_tree_view_set_model(view, model);
	gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_headers_clickable(view, TRUE);
	gtk_tree_view_set_rules_hint(view, FALSE);

	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, "",
						    renderer, "pixbuf",
						    COLUMN_ICON, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Name"),
						    renderer, "text",
						    COLUMN_NAME, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Type"),
						    renderer, "text",
						    COLUMN_TYPE, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Size"),
						    renderer, "text",
						    COLUMN_SIZE, NULL);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(view, -1, _("Date"),
						    renderer, "text",
						    COLUMN_DATE, NULL);

	for (i = 0; i < CLIST_NCOLS; i++) {
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
}

/* Attempt to determine if string is Unicode (heuristic way) */
static int detect_for_utf8(const char *s)
{
	int i;

	for(i=0; i<strlen(s); i++)
	{
		if(((uint8_t)s[i] >= 0xC0) && ((uint8_t)s[i] <= 0xCF)) 
			break;
	}

	return (i < strlen(s));
}


/**************/
/* Management */
/**************/
void clist_refresh(void)
{
	GtkTreeIter iter;
	GdkPixbuf *pix1, *pix2, *pix;
	GList *dirlist;
	gsize br, bw;
	gchar *utf8;
	int i;

	// reparse folders
	tilp_clist_selection_destroy();
	tilp_dirlist_local();
	gtk_list_store_clear(list);

	// sort files
	switch (options.clist_sort) {
	case SORT_BY_NAME:
		tilp_sort_files_by_name();
		break;
	case SORT_BY_TYPE:
		//tilp_sort_files_by_type();
	case SORT_BY_DATE:
		tilp_sort_files_by_date();
		break;
	case SORT_BY_SIZE:
		tilp_sort_files_by_size();
		break;
	}

	pix1 = create_pixbuf("up.ico");
	//pix1 = create_pixbuf("clist_dotdot.xpm");
	pix2 = create_pixbuf("clist_dir.xpm");
	for (dirlist = clist_win.dirlist; dirlist != NULL;
	     dirlist = dirlist->next) {
		TilpFileInfo *fi = (TilpFileInfo *) dirlist->data;
		if ((options.file_disp == SHOW_ALL)
		    || S_ISDIR(fi->attrib)
		    || (tifiles_is_a_ti_file(fi->name)
			&& (tifiles_which_calc_type(fi->name) ==
			    options.lp.calc_type))) {
		} else
			continue;
		if (S_ISDIR(fi->attrib)) {
			if (!strcmp(fi->name, "..")) {
				pix = pix1;
			} else {
				pix = pix2;
			}
		} else {
			char icon_name[256];
			strcpy(icon_name, tifiles_file_icon(fi->name));
			if (!strcmp(icon_name, ""))
				strcpy(icon_name, "TIicon1");
			strcat(icon_name, ".ico");
			tilp_file_underscorize(icon_name);
			pix = create_pixbuf(icon_name);
		}

		// Attempt to separate locale & UTF8 filenames in a heuristic fashion
		if(tifiles_is_a_ti_file(fi->name) && detect_for_utf8(fi->name))
			utf8 = fi->name;
		else
			utf8 = g_filename_to_utf8(fi->name, -1, &br, &bw, NULL);
#if 0
		DISPLAY("<%s> ", fi->name);
		for (i = 0; i < 8; i++)
		DISPLAY("%02X ", fi->name[i] & 0xff);
		DISPLAY("<%s> ", utf8);
		for (i = 0; i < 8; i++)
		DISPLAY("%02X ", utf8[i] & 0xff);
		DISPLAY("\n");
#endif		
		gtk_list_store_append(list, &iter);
		gtk_list_store_set(list, &iter, COLUMN_NAME,
				   utf8,
				   COLUMN_TYPE, tilp_file_get_type(fi),
				   COLUMN_SIZE, tilp_file_get_size(fi),
				   COLUMN_DATE, tilp_file_get_date(fi),
				   COLUMN_DATA, (gpointer) fi, COLUMN_ICON,
				   pix, -1);
		//g_object_unref(pix);
	}
}


/*******************/
/* CList callbacks */
/*******************/


GLADE_CB gboolean
on_treeview2_button_press_event(GtkWidget * widget,
				GdkEventButton * event, gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkTreeModel *model = GTK_TREE_MODEL(list);
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GdkEventButton *bevent;
	gint tx = (gint) event->x;
	gint ty = (gint) event->y;
	gint cx, cy;
	TilpFileInfo *fi;

	gtk_tree_view_get_path_at_pos(view, tx, ty, &path, &column, &cx,
				      &cy);

	switch (event->type) {
	case GDK_BUTTON_PRESS:	// third button clicked
		if (event->button == 3) {
			bevent = (GdkEventButton *) (event);
			gtk_menu_popup(GTK_MENU(create_clist_rbm()),
				       NULL, NULL, NULL, NULL,
				       bevent->button, bevent->time);
			return TRUE;
		}
		break;
	case GDK_2BUTTON_PRESS:	// double click
		if (path == NULL)
			return FALSE;
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, COLUMN_DATA, &fi, -1);
		if (S_ISDIR(fi->attrib)) {

			// go into folder
			tilp_chdir(fi->name);
			g_free(clist_win.current_dir);
			clist_win.current_dir = g_get_current_dir();
			clist_refresh();
			labels_refresh();
		} else {
			// open file with plugin
/*		
		bevent = (GdkEventButton *) (event);		
		gtk_menu_popup(GTK_MENU(create_clist_rbm()),
		NULL, NULL, NULL, NULL,
		bevent->button, bevent->time);
		return TRUE;
*/
		}
		break;
	default:
		break;
	}

	return FALSE;		// pass event on
}


#include <gdk/gdkkeysyms.h>


/* Key pressed */
GLADE_CB gboolean
on_treeview2_key_press_event(GtkWidget * widget, GdkEventKey * event,
			     gpointer user_data)
{
	if (event->keyval == GDK_Delete) {
		on_delete_file1_activate(NULL, NULL);
		return TRUE;
	}
	if ((event->state == GDK_CONTROL_MASK) &&
	    ((event->keyval == GDK_X) || (event->keyval == GDK_x))) {
		on_cut1_activate(NULL, NULL);
		return TRUE;
	}
	if ((event->state == GDK_CONTROL_MASK) &&
	    ((event->keyval == GDK_c) || (event->keyval == GDK_C))) {
		on_copy1_activate(NULL, NULL);
		return TRUE;
	}
	if ((event->state == GDK_CONTROL_MASK) &&
	    ((event->keyval == GDK_V) || (event->keyval == GDK_v))) {
		on_paste1_activate(NULL, NULL);
		return TRUE;
	}
	return FALSE;
}
