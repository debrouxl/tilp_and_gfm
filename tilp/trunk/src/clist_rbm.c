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
#ifdef __WIN32__
#include <direct.h>     // _getdrive
#endif

#include "support.h"
#include "gstruct.h"
//#include "ctree.h"
#include "clist.h"
#include "labels.h"
#include "dboxes.h"
#include "tilp.h"
#include "tilp_core.h"
#include "fileprop.h"

/* Create/update menu */

#ifdef __WIN32__
static void rbm_change_drive_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	tilp_drive_change((char) GPOINTER_TO_INT(user_data));
	clist_refresh();
	labels_refresh();
}

static void set_drives(GtkWidget* widget, gpointer user_data)
{
	GtkWidget *menu = GTK_WIDGET(user_data);
	GtkWidget *change_drive;
	GtkWidget *change_drive_menu;
	GtkWidget *c_drive;
	int drive, curdrive;
	gchar buffer[8];
	gint available_drives[27];	// A..Z -> 26 letters

	change_drive = gtk_menu_item_new_with_label(_("Change drive"));
	g_object_set_data_full(G_OBJECT(menu), "change_drive",
			       gtk_widget_ref(change_drive),
			       (GDestroyNotify)gtk_widget_unref);
	gtk_widget_show(change_drive);

	gtk_container_add(GTK_CONTAINER(menu), change_drive);
	change_drive_menu = gtk_menu_new();
	g_object_set_data_full(G_OBJECT(menu), "change_drive_menu",
			       gtk_widget_ref(change_drive_menu),
			       (GDestroyNotify)gtk_widget_unref);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(change_drive), change_drive_menu);

	curdrive = _getdrive();
	for (drive = 1; drive <= 26; drive++)
		available_drives[drive] = 0;

	for (drive = 3; drive <= 26; drive++) 
	{
		if (!_chdrive(drive)) 
		{
			g_snprintf(buffer, 8, "%c:", drive + 'A' - 1);
			available_drives[drive] = drive + 'A' - 1;

			c_drive = gtk_menu_item_new_with_label(buffer);
			g_object_set_data_full(G_OBJECT(menu), "c_drive",
					       gtk_widget_ref(c_drive),
					       (GDestroyNotify)gtk_widget_unref);
			gtk_widget_show(c_drive);

			gtk_container_add(GTK_CONTAINER(change_drive_menu),
					  c_drive);
			g_signal_connect((gpointer)c_drive, "activate",
					   G_CALLBACK(rbm_change_drive_activate),
					   GINT_TO_POINTER(available_drives[drive]));
		}
	}
	_chdrive(curdrive);
}
#endif				/* __WIN32__ */

GtkWidget *create_clist_rbm(void)
{
	GladeXML *xml;
	GtkWidget *menu;
	gpointer data;

	xml = glade_xml_new(tilp_paths_build_glade("clist_rbm-2.glade"), "clist_rbm", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	data = glade_xml_get_widget(xml, "show_all_files1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), options.show_all);

	data = glade_xml_get_widget(xml, "confirm1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), options.overwrite);

	data = glade_xml_get_widget(xml, "recv_as_group1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), options.recv_as_group);

	menu = glade_xml_get_widget(xml, "clist_rbm");
#ifdef __WIN32__
	set_drives(menu, menu);
#endif
	return menu;
}

/* Callbacks */

GLADE_CB void rbm_cut1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	local.copy_cut = CUT_FILE;
} 

GLADE_CB void rbm_copy1_activate(GtkMenuItem* menuitem,
				  gpointer user_data)
{
	local.copy_cut = COPY_FILE;
} 

GLADE_CB void rbm_paste1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	GList *ptr;
	gchar *src;
	gchar *dst;

	/* If no selection, quits */
	if (local.file_selection == NULL)
		return;

	/* Move every file */
	ptr = local.file_selection;
	while (ptr != NULL) 
	{
		src = (gchar *) (ptr->data);
		dst = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, g_basename(src), NULL);
		if (local.copy_cut == COPY_FILE) 
		{
			tilp_file_copy(src, dst);
			g_free(dst);
		} 
		else 
		{
			tilp_file_move_with_check(src, dst);
			g_free(dst);
		}
		ptr = ptr->next;
	}

	/* No action */
	local.copy_cut = 0;

	/* Destroy the file selection and refresh */
	tilp_file_selection_destroy();
	clist_refresh();
	labels_refresh();
}

GLADE_CB void
rbm_move_to_parent_dir1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	tilp_file_chdir("..");

	g_free(local.cwdir);
	local.cwdir = g_get_current_dir();

	clist_refresh();
	labels_refresh();
} 

GLADE_CB void rbm_select_all1_activate(GtkMenuItem* menuitem,
					gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeSelection *sel;

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_select_all(sel);
} 

GLADE_CB void rbm_unselect_all1_activate(GtkMenuItem* menuitem,
					  gpointer user_data)
{
	GtkTreeView *view = GTK_TREE_VIEW(clist_wnd);
	GtkTreeSelection *sel;

	sel = gtk_tree_view_get_selection(view);
	gtk_tree_selection_unselect_all(sel);
}

#ifdef __WIN32__
static const char* get_gfm_path(void)
{
	HKEY hKey;
	static char szKeyBuf[1024];
	long lResult;
	DWORD dwType, cbData;
	gchar *str = NULL;

	// Create and open key and subkey.
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\gfm.exe", 
		0, KEY_READ, &hKey);
	if(lResult != ERROR_SUCCESS)
		return NULL;

	// Get value of key
	cbData = sizeof(szKeyBuf);
	lResult = RegQueryValueEx(hKey, NULL, 0, &dwType, szKeyBuf, &cbData);
	if(lResult != ERROR_SUCCESS)
		return NULL;
	
	// Close key
	RegCloseKey(hKey);

	return szKeyBuf;
}
#endif

GLADE_CB void rbm_opengfm_activate(GtkMenuItem* menuitem,
									gpointer user_data)
{
#ifdef __WIN32__
	const char *app_path = get_gfm_path();
#else
	const char *app_path1 = "/usr/bin/gfm";
	const char *app_path2 = "/usr/local/bin/gfm";
	const char *app_path = app_path1;
#endif
	GList *sel;

	if (local.file_selection == NULL)
		return;

#ifdef __LINUX__
	if(tilp_file_exist(app_path1))
	  app_path = app_path1;
	else if(tilp_file_exist(app_path2))
	  app_path = app_path2;
#endif
	if(!tilp_file_exist(app_path))
	{
		msg_box1(_("Error"), _("The Group File Manager seems not be installed on your system.\nDownload it from <http://lpg.ticalc.org/prj_gfm/> or take a look at the TiLP user's manual for more information."));
		return;
	}

	for(sel = local.file_selection; sel; sel = sel->next)
	{
		gchar **argv = g_malloc0(3 * sizeof(gchar *));
		gint result;
		GError *error;
		char *filename = (char *)sel->data;

		argv[0] = g_strdup(app_path);
		argv[1] = g_strdup(filename);
		argv[2] = NULL;

		result = g_spawn_async(NULL/*local.cwdir*/, argv, NULL, 0, NULL, NULL, NULL, &error);
		g_strfreev(argv);

		if(result == FALSE)
		{
			msg_box1(_("Error"), error->message);
		}
	}
} 

GLADE_CB void rbm_rename1_activate(GtkMenuItem* menuitem,
				    gpointer user_data)
{
	tilp_file_selection_rename();

	clist_refresh();
	labels_refresh();
} 

GLADE_CB void rbm_update_window1_activate(GtkMenuItem* menuitem,
					   gpointer user_data)
{
	on_tilp_button12_clicked(NULL, NULL);
} 

GLADE_CB void
rbm_make_a_new_dir1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	gchar *utf8 = NULL;
	gsize br, bw;
	gchar *dirname;

	utf8 = gif->msg_entry(_("Make a new directory"), _("Name: "),
				 _("new_directory"));
	if (utf8 == NULL)
		return;

	dirname = g_filename_from_utf8(utf8, -1, &br, &bw, NULL);
	g_free(utf8);

	tilp_file_mkdir(dirname);
	g_free(dirname);

	clist_refresh();
	labels_refresh();
}

GLADE_CB void rbm_delete_file1_activate(GtkMenuItem* menuitem,
				       gpointer user_data)
{
	on_tilp_button11_clicked(NULL, NULL);
} 

GLADE_CB void
rbm_set_as_working_dir1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	g_free(options.working_dir);
	options.working_dir = g_get_current_dir();

	tilp_config_write();
} 

GLADE_CB void
rbm_show_all_files1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	options.show_all = GTK_CHECK_MENU_ITEM(menuitem)->active;
	clist_refresh();
}


GLADE_CB void
rbm_confirm_delete_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	options.overwrite = GTK_CHECK_MENU_ITEM(menuitem)->active;
}


GLADE_CB void
rbm_recv_as_group1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	options.recv_as_group = GTK_CHECK_MENU_ITEM(menuitem)->active;
}

GLADE_CB void
rbm_properties1_activate             (GtkMenuItem     *menuitem,
                                      gpointer         user_data)
{
	GList *ptr;

	if (local.file_selection == NULL)
		return;

	for(ptr = local.file_selection; ptr; ptr = ptr->next)
	{
		gchar *fn = (gchar *)(ptr->data);

		display_properties_dbox(fn);
	}
	
}
