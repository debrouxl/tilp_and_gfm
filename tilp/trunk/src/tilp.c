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

#include "tilp_core.h"
#include "gstruct.h"
#include "dboxes.h"
#include "toolbar.h"
#include "labels.h"
#include "clist.h"
#include "ctree.h"
#include "general.h"
#include "extprgms.h"
#include "comm.h"
#include "clock.h"
#include "filesel.h"
#include "manpage.h"
#include "about.h"
#include "screenshot.h"
#include "action.h"


/******************/
/* Initialization */
/******************/


static GtkWidget *statbar = NULL;
void dnd_init(void);

static void ready_callback(int status)
{
	gint id;
	gchar *str;

	if(status == READY_NOK)
		str = g_strdup(_("Status: not connected."));
	else
		str = g_strdup_printf("Status: connected (%s).",
					 tifiles_calctype_to_string(options.lp.
						  calc_type));

	id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statbar), str);
	gtk_statusbar_push(GTK_STATUSBAR(statbar), id, str);
	g_free(str);
}

/*
	char s[256] = "é";
	char *utf;
	int8_t utf8[16];
	gsize bw;
	uint16_t c;

	c = 'é';
	printf("$%02X\n", c & 0xff);
	c = 0x3A0;
	utf8[0] = (0xC0 | ((uint16_t)c >> 6)) & 0xff;
	utf8[1] = (0x80 | ((uint16_t)c & 0x3f)) & 0xff;
	utf8[2] = 0;
	ready_callback(utf8);
*/

GtkWidget *display_tilp_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *sb;
	GtkWidget *paned;

	xml = glade_xml_new
	    (tilp_paths_build_glade("tilp-2.glade"), "tilp_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);
	dbox = glade_xml_get_widget(xml, "tilp_dbox");
	ctree_wnd = glade_xml_get_widget(xml, "treeview1");
	clist_wnd = glade_xml_get_widget(xml, "treeview2");
	clabel_win.label21 = glade_xml_get_widget(xml, "label21");
	clabel_win.label22 = glade_xml_get_widget(xml, "label22");
	toolbar_win.toolbar = glade_xml_get_widget(xml, "toolbar2");

	//toolbar_set_images();
	toolbar_win.button10 = glade_xml_get_widget(xml, "button4");
	toolbar_win.button11 = glade_xml_get_widget(xml, "button6");
	toolbar_win.button12 = glade_xml_get_widget(xml, "button7");
	toolbar_win.button13 = glade_xml_get_widget(xml, "button8");
	toolbar_win.button14 = glade_xml_get_widget(xml, "button9");
	toolbar_win.button20 = glade_xml_get_widget(xml, "button10");
	toolbar_win.button21 = glade_xml_get_widget(xml, "button11");
	toolbar_win.button22 = glade_xml_get_widget(xml, "button12");
	statbar = sb = glade_xml_get_widget(xml, "statusbar1");
	ready_callback(READY_NOK);
	paned = glade_xml_get_widget(xml, "hpaned1");
	gtk_paned_set_position(GTK_PANED(paned), options.xsize);
	clist_init();
	ctree_init();
	dnd_init();
	tilp_calc_register(ready_callback);

	return dbox;
}

GLADE_CB void on_hpaned1_size_request(GtkPaned * paned, gpointer user_data)
{
	options.xsize = gtk_paned_get_position(paned);
}


/******************/
/* Menu callbacks */
/******************/


GLADE_CB void on_tilp_dbox_destroy(GtkObject * object, gpointer user_data)
{
	tilp_error(link_cable.exit());
	gtk_main_quit();
}

GLADE_CB void on_open1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
}

GLADE_CB void on_save_config1_activate(GtkMenuItem * menuitem,
				       gpointer user_data)
{
	tilp_config_save();
}

GLADE_CB void on_reload_config1_activate(GtkMenuItem * menuitem,
					 gpointer user_data)
{
	tilp_config_load();
}

GLADE_CB void on_default_config1_activate(GtkMenuItem * menuitem,
					  gpointer user_data)
{
	tilp_config_default();
}

GLADE_CB void on_quit1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	gtk_widget_destroy(GTK_WIDGET(main_wnd));
}

GLADE_CB void on_general1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	display_general_dbox();
}

GLADE_CB void on_external_programs1_activate(GtkMenuItem * menuitem,
					     gpointer user_data)
{
	display_extprgms_dbox();
}

GLADE_CB void on_communication1_activate(GtkMenuItem * menuitem,
					 gpointer user_data)
{
	display_comm_dbox();
}

GLADE_CB void on_clock1_activate(GtkMenuItem * menuitem,
				 gpointer user_data)
{
	display_clock_dbox();
}

GLADE_CB void on_get_idlist1_activate(GtkMenuItem * menuitem,
				      gpointer user_data)
{
	tilp_calc_idlist();
}

GLADE_CB void on_remote1_activate(GtkMenuItem * menuitem,
				  gpointer user_data)
{
	msg_box("Information",
		"This function is no longer available...\nPlease use TiEmu (http://lpg.ticalc.org/prj_tiemu) as a better replacement.");
}

GLADE_CB void on_rom_dump1_activate(GtkMenuItem * menuitem,
				    gpointer user_data)
{
	if (tilp_calc_rom_dump())
		return;
	display_fileselection_7();
	clist_refresh();
	labels_refresh();
}


#ifdef __WIN32__
#define strcasecmp _stricmp
#endif				/* __WIN32__ */

GLADE_CB void on_upgrade_os1_activate(GtkMenuItem * menuitem,
				      gpointer user_data)
{
	GList *selection;
	if (!tilp_clist_selection_ready())
		return;
	selection = clist_win.selection;
	while (selection != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) selection->data;
		if (!strcasecmp
		    (tifiles_get_extension(f->name),
		     tifiles_flash_os_file_ext())) {

			//gif->destroy_pbar();
			tilp_calc_send_flash_os(f->name);
			return;
		} else {

			//gif->destroy_pbar();
			gif->msg_box(_("Error"), _
				     ("It's not a FLASH upgrade or this FLASH file is not intended for this calculator type."));
			return;
		}
	}
}


GLADE_CB void on_manual1_activate(GtkMenuItem * menuitem,
				  gpointer user_data)
{
	gboolean result;
	gchar **argv = g_malloc0(3 * sizeof(gchar *));

	argv[0] = g_strdup(options.web_location);
	argv[1] = g_strconcat(options.web_options, inst_paths.help_dir,
			      "User_Manual.html", NULL);

	result = g_spawn_async(inst_paths.help_dir, argv, NULL, 0, NULL, NULL,
			       NULL, NULL);
	g_strfreev(argv);
	if (result == FALSE) {
	  msg_box("Error",
		  "Spawn error: do you have Mozilla/IE installed ? If you are using another web browser, please set-up it in 'Setup->External Programs'.");
	} else {
	  GtkDialog *dialog;
	  GTimer *timer;
	  const gchar *message =
	    "A web browser has been laucnhed: this may take a while before it appears. If it is already launched, the page will be opened in the existing frame.";
	  dialog =
	    gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
				   GTK_MESSAGE_INFO,
				   GTK_BUTTONS_CLOSE, message);
	  g_signal_connect_swapped(GTK_OBJECT(dialog), "response",
				   G_CALLBACK(gtk_widget_destroy),
					 GTK_OBJECT(dialog));
	  gtk_widget_show_all(GTK_WIDGET(dialog));
	  while (gtk_events_pending())
	    gtk_main_iteration();
	  timer = g_timer_new();
	  while (g_timer_elapsed(timer, NULL) < 3.0);
	  g_timer_destroy(timer);
	  gtk_widget_destroy(GTK_WIDGET(dialog));
	}
}


GLADE_CB void on_manpage1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	display_manpage_dbox();
}

static void go_to_bookmark(const char *link)
{
	gboolean result;
	gchar *argv[3] = {
		0
	};
	argv[0] = g_strdup(options.web_location);
	argv[1] = g_strdup(link);
	argv[2] = NULL;
	result =
	    g_spawn_async(NULL, argv, NULL, 0, NULL, NULL, NULL, NULL);
	g_free(argv[0]);
	g_free(argv[1]);
	if (result == FALSE) {
		msg_box("Error",
			"Spawn error: do you have Mozilla/IE installed ? If you are using another web browser, please set-up it in 'Setup->External Programs'.");
	} else {
		GtkDialog *dialog;
		GTimer *timer;
		const gchar *message =
		    "A web browser has been laucnhed: this may take a while before it appears. If it is already launched, the page will be opened in the existing frame.";
		dialog =
		    gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
					   GTK_MESSAGE_INFO,
					   GTK_BUTTONS_CLOSE, message);
		g_signal_connect_swapped(GTK_OBJECT(dialog), "response",
					 G_CALLBACK(gtk_widget_destroy),
					 GTK_OBJECT(dialog));
		gtk_widget_show_all(GTK_WIDGET(dialog));
		while (gtk_events_pending())
			gtk_main_iteration();
		timer = g_timer_new();
		while (g_timer_elapsed(timer, NULL) < 3.0);
		g_timer_destroy(timer);
		gtk_widget_destroy(GTK_WIDGET(dialog));
	}
}


GLADE_CB void on_ti_s_web_site1_activate(GtkMenuItem * menuitem,
					 gpointer user_data)
{
	go_to_bookmark("http://education.ti.com");
}

GLADE_CB void on_calculator_software1_activate(GtkMenuItem *
					       menuitem,
					       gpointer user_data)
{
	go_to_bookmark("http://epsstore.ti.com");
}

GLADE_CB void on_ticalcorg1_activate(GtkMenuItem * menuitem,
				     gpointer user_data)
{
	go_to_bookmark("http://www.ticalc.org");
}

GLADE_CB void on_tinewsnet1_activate(GtkMenuItem * menuitem,
				     gpointer user_data)
{
	go_to_bookmark("http://www.tinews.net");
}

GLADE_CB void on_ti_frorg1_activate(GtkMenuItem * menuitem,
				    gpointer user_data)
{
	go_to_bookmark("http://www.ti-fr.org");
} GLADE_CB void on_the_lpg1_activate(GtkMenuItem * menuitem,
				     gpointer user_data)
{
	go_to_bookmark("http://lpg.ticalc.org");
} GLADE_CB void on_tilp_s_web_site1_activate(GtkMenuItem * menuitem,
					     gpointer user_data)
{
	go_to_bookmark("http://tilp.info");
} GLADE_CB void on_about1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	display_about_dbox();
}

/*****************************/
/* Toolbar buttons callbacks */
/*****************************/
GLADE_CB void on_tilp_button4_clicked(GtkButton * button,
				      gpointer user_data)
{
	tilp_calc_isready();
}

GLADE_CB void on_tilp_button5_clicked(GtkButton * button,
				      gpointer user_data)
{
	display_screenshot_dbox();
}

GLADE_CB void on_tilp_button6_clicked(GtkButton * button,
				      gpointer user_data)
{
	if (tilp_calc_dirlist() != 0)
		return;
	ctree_refresh();
	labels_refresh();
}


GLADE_CB void on_tilp_button7_clicked(GtkButton * button,
				      gpointer user_data)
{
	if (tilp_calc_recv_backup() != 0)
		return;
	display_fileselection_3();
}


GLADE_CB void on_tilp_button8_clicked(GtkButton * button,
				      gpointer user_data)
{
	display_fileselection_2();
}

// Note: user_data is a string:
// - such as "FLASH" for sending var into FLASH (ti83+/89/92+/v200)
// - such as "" for sending var in the default folder
// - such as "foo" for sending var in the 'foo' folder
// - unused for sending FLASH files
void on_tilp_button9b_clicked(GtkButton * button, gpointer user_data)
{
	int to_flash = 0;
	gchar *dst_folder;
	TilpFileInfo *f;

	printf("<%p>\n", user_data);
	dst_folder = g_strdup((gchar *) user_data);
	if (dst_folder != NULL)
		to_flash = !strcmp(dst_folder, "FLASH");
	if (clist_win.selection == NULL)
		return;
	f = (TilpFileInfo *) clist_win.selection->data;
	if (tifiles_is_a_flash_file(f->name)) {
		if (tilp_calc_send_flash_app(f->name) != 0)
			return;
	} else {
		if (options.confirm == CONFIRM_YES) {

			// note: dst_folder must be a copy b/c the user_data
			// pointer is no longer valid after dirlist_remote
			if (ti_calc.is_silent) {
				if (tilp_dirlist_remote())
					return;
			}
			if (display_action_dbox(dst_folder) == BUTTON2) {
				g_free(dst_folder);
				return;
			}
			g_free(dst_folder);
		}
		// needed: avoid box locking/flickering !
		while (gtk_events_pending())
			gtk_main_iteration();
		if (tilp_calc_send_var(to_flash) != 0)
			return;
	}
}


// used for receiving vars
GLADE_CB void on_tilp_button9_clicked(GtkButton * button,
				      gpointer user_data)
{
	int ret;
	if ((ctree_win.selection != NULL)
	    || (ctree_win.selection2 != NULL)) {
		if (ctree_win.selection != NULL) {
			ret = tilp_calc_recv_var();
			if (ret < 0)
				return;

			else if (ret > 0)
				display_fileselection_4();
		}
		if (ctree_win.selection2 != NULL) {
			ret = tilp_calc_recv_app();
			if (ret != 0)
				return;
		}
	} else if ((options.lp.calc_type == CALC_TI82) |
		   (options.lp.calc_type == CALC_TI85)) {
		ret = tilp_calc_recv_var();
		if (ret < 0)
			return;
		if (ret > 0)
			display_fileselection_4();

		else {
			clist_refresh();
			labels_refresh();
		}
	}
}


// make new dir
GLADE_CB void on_tilp_button10_clicked(GtkButton * button,
				       gpointer user_data)
{
	gchar *utf8 = NULL;
	gsize br, bw;
	gchar *dirname;

	utf8 = gif->msg_entry(_("Make a new directory"), _("Name: "),
				 _("new_directory"));
	if (utf8 == NULL)
		return;

	dirname = g_filename_from_utf8(utf8, -1, &br, &bw, NULL);

	tilp_file_mkdir(dirname);
	g_free(dirname);

	clist_refresh();
	labels_refresh();
}


// trash
GLADE_CB void on_tilp_button11_clicked(GtkButton * button,
				       gpointer user_data)
{
	tilp_delete_selected_files();
	clist_refresh();
	labels_refresh();
}

// refresh
GLADE_CB void on_tilp_button12_clicked(GtkButton * button,
				       gpointer user_data)
{
	if (!clist_win.copy_cut)
		tilp_clist_file_selection_destroy();
	clist_refresh();
	labels_refresh();
}


/*****************************/
/* Drag & Drop support (DnD) */
/*****************************/


enum { TARGET_STRING, TARGET_ROOTWIN, TARGET_LEFT, TARGET_RIGHT,
};

/*static GtkTargetEntry target_table[] = {
  { "STRING",     0, TARGET_STRING },
  { "text/plain", 0, TARGET_STRING },
  { "application/x-rootwin-drop", 0, TARGET_ROOTWIN },
  };*/

static GtkTargetEntry target_table_1[] = {
	{"clist", 0, TARGET_STRING},
	{"application/x-rootwin-drop", 0, TARGET_ROOTWIN}
};

static GtkTargetEntry target_table_2[] = {
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
	gtk_selection_data_set(data, data->target, 8, name, strlen(name));
}

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
	TiVarEntry *ve;
	gchar *name;
	if ((data->length >= 0) && (data->format == 8)) {
		gtk_tree_view_get_dest_row_at_pos(view, x, y, &path, &pos);
		if (path == NULL) {
			gtk_drag_finish(drag_context, FALSE, FALSE, time);
			return;
		}
		gtk_tree_model_get_iter(model, &iter, path);
		gtk_tree_model_get(model, &iter, CTREE_DATA, &ve, -1);
		gtk_tree_model_get(model, &iter, CTREE_NAME, &name, -1);
		if (ve && (ve->type == tifiles_folder_type())) {
			on_tilp_button9b_clicked(NULL, ve->name);
			gtk_drag_finish(drag_context, TRUE, FALSE, time);
			return;
		}
		on_tilp_button9b_clicked(NULL, "");
		gtk_drag_finish(drag_context, TRUE, FALSE, time);
		return;
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
	printf("<<%s>>\n", name_to_drag);
	if (!strcmp(name_to_drag, NODEx) && ti_calc.has_folder)
		select_vars_under_folder(!0);

	else if (!strcmp(name_to_drag, NODE3) && !ti_calc.has_folder)
		select_vars_under_folder(!0);
}

GLADE_CB void
on_treeview1_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint time, gpointer user_data)
{
	if (info == TARGET_ROOTWIN) {
		//g_print("I was dropped on the rootwin\n");
	} else
		gtk_selection_data_set(data, data->target, 8,
				       name_to_drag, strlen(name_to_drag));
}

GLADE_CB void
on_treeview2_drag_data_received(GtkWidget * widget,
				GdkDragContext * drag_context,
				gint x,
				gint y,
				GtkSelectionData * data,
				guint info, guint time, gpointer user_data)
{
	if ((data->length >= 0) && (data->format == 8)) {
		gchar *name = (gchar *) data->data;

		//g_print("Received \"%s\" as selection information.\n", name);
		if (!strcmp(name, NODE1)) {

			// screenshot
			display_screenshot_dbox();
			on_scdbox_button1_clicked(NULL, NULL);
			if (info_update.cancel == 0) {
				on_sc_save1_activate(NULL, NULL);
				on_sc_quit1_activate(NULL, NULL);
			}
		} else if (!strcmp(name, NODE2)) {

			// ROM dumping
			on_rom_dump1_activate(NULL, NULL);
		} else if (!strcmp(name, NODE3)) {

			// all variables to get
//if(ti_calc.has_folder)
			on_tilp_button9_clicked(NULL, NULL);
			select_vars_under_folder(0);	//deselect
		} else if (!strcmp(name, NODE4)) {

			// nothing to do
		} else if (!strcmp(name, NODEx)) {

			// folder to get
			on_tilp_button9_clicked(NULL, NULL);
			select_vars_under_folder(0);	//deselect
		} else {

			// single/group to get
			on_tilp_button9_clicked(NULL, NULL);
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
	GtkTreeIter parent, iter;
	view = GTK_TREE_VIEW(ctree_wnd);
	model = gtk_tree_view_get_model(view);

	// select var beneath a folder
	gtk_tree_model_get_iter(model, &parent, path);
	if (gtk_tree_model_iter_has_child(model, &parent)) {
		GtkTreeSelection *sel;
		GtkTreePath *start_path, *end_path;
		gint n;
		gboolean valid;
		sel =
		    gtk_tree_view_get_selection(GTK_TREE_VIEW(ctree_wnd));
		n = gtk_tree_model_iter_n_children(model, &parent);
		valid =
		    gtk_tree_model_iter_children(model, &iter, &parent);
		start_path = gtk_tree_model_get_path(model, &iter);
		valid =
		    gtk_tree_model_iter_nth_child(model, &iter, &parent,
						  n - 1);
		end_path = gtk_tree_model_get_path(model, &iter);
		if (!action)
			gtk_tree_selection_unselect_range(sel, start_path,
							  end_path);

		else
			gtk_tree_selection_select_range(sel, start_path,
							end_path);
		gtk_tree_path_free(start_path);
		gtk_tree_path_free(end_path);
	}
}
