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

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "tilp_core.h"

#include "gstruct.h"
#include "ctree.h"
#include "clist.h"
#include "labels.h"
#include "dboxes.h"
#include "tilp.h"
#include "shell.h"


/***********************/
/* Popup menu creation */
/***********************/


static void on_clist_rbm_show(GtkWidget * widget, gpointer user_data);
GtkWidget *create_clist_rbm(void)
{
	GladeXML *xml;
	GtkWidget *menu;
	xml = glade_xml_new
	    (tilp_paths_build_glade("clist_rbm-2.glade"), "clist_rbm",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);
	menu = glade_xml_get_widget(xml, "clist_rbm");
	on_clist_rbm_show(menu, menu);
	return menu;
}


/************************/
/* Popup menu callbacks */
/************************/


GLADE_CB void on_cut1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	clist_win.copy_cut = CUT_FILE;
} 

GLADE_CB void on_copy1_activate(GtkMenuItem * menuitem,
				  gpointer user_data)
{
	clist_win.copy_cut = COPY_FILE;
} 

GLADE_CB void on_paste1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	GList *ptr;
	gchar *src;
	gchar *dst;

	/* If no selection, quits */
	if (clist_win.file_selection == NULL)
		return;

	/* Move every file */
	ptr = clist_win.file_selection;
	while (ptr != NULL) {
		src = (gchar *) (ptr->data);
		dst =
		    g_strconcat(clist_win.current_dir, DIR_SEPARATOR,
				g_basename(src), NULL);
		if (clist_win.copy_cut == COPY_FILE) {
			tilp_file_copy(src, dst);
			g_free(dst);
		} else {
			tilp_file_move_with_check(src, dst);
			g_free(dst);
		}
		ptr = ptr->next;
	}

	/* No action */
	clist_win.copy_cut = 0;

	/* Destroy the file selection and refresh */
	tilp_clist_file_selection_destroy();
	clist_refresh();
	labels_refresh();
}

GLADE_CB void
on_move_to_parent_dir1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	tilp_chdir("..");
	g_free(clist_win.current_dir);
	clist_win.current_dir = g_get_current_dir();
	clist_refresh();
	labels_refresh();
} 

GLADE_CB void on_select_all1_activate(GtkMenuItem * menuitem,
					gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeSelection *sel;
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_select_all(sel);
} 

GLADE_CB void on_unselect_all1_activate(GtkMenuItem * menuitem,
					  gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeSelection *sel;
	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_unselect_all(sel);
}

#ifdef __WIN32__
#define popen _popen
#define pclose _pclose
#endif				/*  */
GLADE_CB void on_unzip1_activate(GtkMenuItem * menuitem,
				 gpointer user_data)
{
	gchar *cmdline;
	gchar *s;
	gchar buffer[MAXCHARS];
	FILE *p;
	GList *ptr;
	int ret;

#ifdef __WIN32__
	gint n;

#endif				/*  */

//
	if (clist_win.selection == NULL) {
		msg_box(_("Information"), _
			("A file must have been selected in the right window."));
		return;
	}
	// Detect whether the program is available else error !
	p = popen(options.unzip_location, "r");
	if (p == NULL) {
		msg_box(_("Error"), _
			("It seems that the 'unzip' program is unavailable.\nWindows users: you must have the 'WinZip Command Line Support Add-On' (233 Kb) for this. If not, \nyou can download it at www.winzip.com."));
		return;
	}
	pclose(p);

	//
	ptr = clist_win.selection;
	while (ptr != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) ptr->data;

		// unzip the file archive
		cmdline = (gchar *)
		    g_malloc((strlen(options.unzip_location) +
			      strlen(options.unzip_options) + 1 +
			      MAXCHARS) * sizeof(gchar));
		strcpy(cmdline, options.unzip_location);
		strcat(cmdline, " ");
		if (!strcmp(options.unzip_options, ""))
#if defined(__LINUX__) || defined(__BSD__)
		{		// default options
			strcat(cmdline, "-o ");	// overwrite
			strcat(cmdline, "-d ");	// unzip in a sub directory
			sprintf(buffer, "%s", f->name);
			s = (gchar *) strrchr(buffer, '.');
			if (s != NULL)
				buffer[strlen(buffer) - strlen(s)] = '\0';
			strcat(cmdline, buffer);
		}
#elif defined(__WIN32__)
		{		// default options
			strcat(cmdline, "-o ");	// overwrite
			strcat(cmdline, "-d ");	// unzip in a sub directory

			// sprintf(buffer, "%s", f->name);
			// printf("-> <%s>\n", buffer);
			// s = strrchr(buffer, '.');
			// if(s != NULL)
			// buffer[strlen(buffer) - strlen(s)] = '\0';
			strcat(cmdline, buffer);
		}
#endif				/*  */
		else {		// user options
			strcat(cmdline, options.unzip_options);
		}
		strcat(cmdline, " ");
		sprintf(buffer, "%s", f->name);
		strcat(cmdline, buffer);

		// execute
		fprintf(stdout, "Unzip cmdline: <%s>\n", cmdline);
		ret = execute_command(cmdline);
		ptr = ptr->next;
	}
	clist_refresh();
}

GLADE_CB void on_untar1_activate(GtkMenuItem * menuitem,
				 gpointer user_data)
{
	gchar *cmdline;
	FILE *p;
	GList *ptr;
	int ret;

#ifdef __WIN32__
	gint n;
	gchar buffer[MAXCHARS];

#endif				/*  */

//
	if (!tilp_clist_selection_ready()) {
		msg_box(_("Information"), _
			("A file must have been selected in the right window."));
		return;
	}
	// Check for program existence
	p = popen(options.tar_location, "r");
	if (p == NULL) {
		msg_box(_("Error"), _
			("It seems that the 'unzip' program is unavailable.\nWindows users: you must have the 'WinZip Command Line Support Add-On' (233 Kb) for this. Else, \nyou can download it at www.wintar.com."));
		return;
	}
	pclose(p);

//
	ptr = clist_win.selection;
	while (ptr != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) ptr->data;

		// untar the file archive
		cmdline = (gchar *)
		    g_malloc((strlen(options.tar_location) +
			      strlen(options.tar_options) + 1 +
			      MAXCHARS) * sizeof(gchar));
		strcpy(cmdline, options.tar_location);
		strcat(cmdline, " ");
		if (!strcmp(options.tar_options, ""))
#if defined(__LINUX__) || defined(__BSD__)
		{		// default options
			strcat(cmdline, "x");	// extract
			strcat(cmdline, "v");	// verbose
			strcat(cmdline, "z");	// gzipped
			strcat(cmdline, "f");	// force = overwrite
			strcat(cmdline, " ");
			strcat(cmdline, f->name);
		}
#elif defined(__WIN32__)
		{		// default options
			strcat(cmdline, "-o ");	// overwrite
			strcat(cmdline, "-d ");	// untar in a sub directory
			strcat(cmdline, buffer);
		}
#endif				/*  */
		else {		// user's options
			strcat(cmdline, options.tar_options);
			strcat(cmdline, " ");
			strcat(cmdline, f->name);
		}

// execute
		fprintf(stdout, "Untar cmdline: <%s>\n", cmdline);
		ret = execute_command(cmdline);
		ptr = ptr->next;
	}
	clist_refresh();
}

GLADE_CB void on_ungroup1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	tilp_tifiles_ungroup();
	clist_refresh();
	labels_refresh();
} 

GLADE_CB void on_group1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	tilp_tifiles_group();
	clist_refresh();
	labels_refresh();
} 

GLADE_CB void on_open2_activate(GtkMenuItem * menuitem,
				  gpointer user_data)
{

/*
	GList *sel;

	if ((sel = clist_win.selection) == NULL)
		return;

	while (sel != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) sel->data;
		display_gfm_dbox(f->name);
		sel = g_list_next(sel);
	}
*/
} 

void on_view1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	msg_box(_("Information"),
		_("Plugin mechanism: system not defined yet !"));
} 

GLADE_CB void on_rename1_activate(GtkMenuItem * menuitem,
				    gpointer user_data)
{
	tilp_rename_selected_files();

	/* I've been able to trace a SIGSEGV till the first g_malloc()
	 * of the function below. It seems that a part of the software
	 * corrupts the heap, given that after the call to malloc(), the
	 * code (which is normally protected) is written. */
	clist_refresh();
	labels_refresh();
} 

GLADE_CB void on_update_window1_activate(GtkMenuItem * menuitem,
					   gpointer user_data)
{
	on_tilp_button12_clicked(NULL, NULL);
} 

GLADE_CB void
on_make_a_new_dir1_activate(GtkMenuItem * menuitem, gpointer user_data)
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

GLADE_CB void on_delete_file1_activate(GtkMenuItem * menuitem,
				       gpointer user_data)
{
	on_tilp_button11_clicked(NULL, NULL);
} 

GLADE_CB void on_shell1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	display_shell_dbox();
} 

GLADE_CB void
on_sign_ti83_flash_apps1_activate(GtkMenuItem * menuitem,
				  gpointer user_data)
{
	gchar *cmdline;
	gchar *s;
	gchar buffer[MAXCHARS];
	FILE *p;
	GList *ptr;
	int ret;
	if (!tilp_clist_selection_ready())
		return;

	// detect whether the program is available
	p = popen(options.appsign_location, "r");
	if (p == NULL) {
		msg_box(_("Error"), _
			("It seems that the 'appsign' program is not available.\nYou can download it on http://education.ti.com."));
		return;
	}
	pclose(p);

//
	ptr = clist_win.selection;
	while (ptr != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) ptr->data;

		// build cmdline
		cmdline = (gchar *)
		    g_malloc((strlen(options.appsign_location) +
			      strlen(options.appsign_options) + 1 +
			      MAXCHARS) * sizeof(gchar));
		strcpy(cmdline, options.appsign_location);
		strcat(cmdline, " ");
		strcat(cmdline, options.appsign_options);
		strcat(cmdline, " ");
		sprintf(buffer, "%s", f->name);
		s = (gchar *) strrchr(buffer, '.');
		if (s != NULL)
			*s = '\0';
		strcat(cmdline, buffer);

		// execute
		ret = execute_command(cmdline);
		ptr = ptr->next;
	}
	clist_refresh();
}

GLADE_CB void
on_convert_ams_upgrade1_activate(GtkMenuItem * menuitem,
				 gpointer user_data)
{
	GList *ptr;
	if (!tilp_clist_selection_ready())
		return;
	ptr = clist_win.selection;
	while (ptr != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) ptr->data;
		if (tilp_calc_ams2rom(f->name) != 0)
			return;
		ptr = ptr->next;
	}
	clist_refresh();
}

GLADE_CB void
on_set_as_working_dir1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	g_free(options.working_dir);
	options.working_dir = g_get_current_dir();
	tilp_config_save();
} 

GLADE_CB void
on_send_vars_to_flash1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	if (tifiles_is_flash(options.lp.calc_type))
		on_tilp_button9b_clicked(NULL, "FLASH");

	else {
		msg_box("Information",
			"Only available with TI83+ calculators...");
		return;
	}
}


/*****************/
/* Dynamic menus */
/*****************/

#ifdef __WIN32__
static void rbm_change_drive_activate(GtkMenuItem * menuitem,
				      gpointer user_data)
{
	tilp_drive_change((char) GPOINTER_TO_INT(user_data));
	clist_refresh();
	labels_refresh();
}
#endif				/*  */

static void rbm_plugin_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *child = GTK_BIN(menuitem)->child;
	gchar *plugin_name;

	gtk_label_get(GTK_LABEL(child), &plugin_name);
	tilp_plugins_open(plugin_name);
	tilp_plugins_run();
	tilp_plugins_read((gchar *) user_data);
} 

static void on_clist_rbm_show1(GtkWidget * widget, gpointer user_data)
{
	GtkWidget *menu = GTK_WIDGET(user_data);
	GtkWidget *menu_item;
	GtkWidget *plugin_menu;
	GtkWidget *plugin_item;

	menu_item = gtk_menu_item_new_with_label(_("Open with"));
	gtk_widget_ref(menu_item);
	gtk_object_set_data_full(GTK_OBJECT(menu), "menu_item", menu_item,
				 (GtkDestroyNotify) gtk_widget_unref);
	gtk_widget_show(menu_item);
	gtk_container_add(GTK_CONTAINER(menu), menu_item);
	plugin_menu = gtk_menu_new();
	gtk_widget_ref(plugin_menu);
	gtk_object_set_data_full(GTK_OBJECT(menu), "plugin_menu",
				 plugin_menu,
				 (GtkDestroyNotify) gtk_widget_unref);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), plugin_menu);
	if (clist_win.selection == NULL) {
		plugin_item =
		    gtk_menu_item_new_with_label("No file selected !");
		gtk_widget_show(plugin_item);
		gtk_container_add(GTK_CONTAINER(plugin_menu), plugin_item);
	} else {
		TilpFileInfo *f =
		    (TilpFileInfo *) clist_win.selection->data;
		gchar *plugin_name = NULL;
		gint i = 0;
		tilp_plugins_search_start();
		for (i = 0;; i++) {
			plugin_name = tilp_plugins_search_query
			    (tifiles_get_extension(f->name));
			if (plugin_name == NULL)
				break;
			plugin_item =
			    gtk_menu_item_new_with_label(plugin_name);

			/*gtk_widget_ref (plugin_item);
			   gtk_object_set_data_full (GTK_OBJECT (menu), plugin_name, 
			   plugin_item,
			   (GtkDestroyNotify) gtk_widget_unref); */
			gtk_widget_show(plugin_item);
			gtk_container_add(GTK_CONTAINER(plugin_menu),
					  plugin_item);
			gtk_signal_connect(GTK_OBJECT(plugin_item),
					   "activate",
					   GTK_SIGNAL_FUNC
					   (rbm_plugin_activate), f->name);
		}
		if (i == 0) {
			plugin_item =
			    gtk_menu_item_new_with_label("No plug-in !");
			gtk_widget_show(plugin_item);
			gtk_container_add(GTK_CONTAINER(plugin_menu),
					  plugin_item);
		}
	}
}


#ifdef __WIN32__
static void on_clist_rbm_show2(GtkWidget * widget, gpointer user_data)
{
	GtkWidget *menu = GTK_WIDGET(user_data);
	GtkWidget *change_drive;
	GtkWidget *change_drive_menu;
	GtkWidget *c_drive;
	int ch, drive, curdrive;
	gchar buffer[8];
	gint available_drives[27];	// A..Z -> 26 letters
	change_drive = gtk_menu_item_new_with_label(_("Change drive"));
	gtk_widget_ref(change_drive);
	gtk_object_set_data_full(GTK_OBJECT(menu), "change_drive",
				 change_drive,
				 (GtkDestroyNotify) gtk_widget_unref);
	gtk_widget_show(change_drive);
	gtk_container_add(GTK_CONTAINER(menu), change_drive);
	change_drive_menu = gtk_menu_new();
	gtk_widget_ref(change_drive_menu);
	gtk_object_set_data_full(GTK_OBJECT(menu), "change_drive_menu",
				 change_drive_menu,
				 (GtkDestroyNotify) gtk_widget_unref);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(change_drive),
				  change_drive_menu);
	curdrive = _getdrive();
	for (drive = 1; drive <= 26; drive++)
		available_drives[drive] = 0;
	for (drive = 3; drive <= 26; drive++) {
		if (!_chdrive(drive)) {
			g_snprintf(buffer, 8, "%c:", drive + 'A' - 1);
			available_drives[drive] = drive + 'A' - 1;
			c_drive = gtk_menu_item_new_with_label(buffer);
			gtk_widget_ref(c_drive);
			gtk_object_set_data_full(GTK_OBJECT(menu),
						 "c_drive", c_drive,
						 (GtkDestroyNotify)
						 gtk_widget_unref);
			gtk_widget_show(c_drive);
			gtk_container_add(GTK_CONTAINER(change_drive_menu),
					  c_drive);
			gtk_signal_connect(GTK_OBJECT(c_drive), "activate",
					   GTK_SIGNAL_FUNC
					   (rbm_change_drive_activate),
					   GINT_TO_POINTER(available_drives
							   [drive]));
		}
	}
	_chdrive(curdrive);
}
#endif				/* __WIN32__ */

void on_clist_rbm_show(GtkWidget * widget, gpointer user_data)
{
	on_clist_rbm_show1(widget, user_data);
#ifdef __WIN32__
	on_clist_rbm_show2(widget, user_data);
#endif				/* __WIN32__ */
}
