/* Hey EMACS -*- linux-c -*- */
/* $Id: ctree_rbm.c 1218 2005-06-22 09:27:55Z roms $ */

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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#include "support.h"
#include "gstruct.h"
#include "device.h"
#include "toolbar.h"
#include "options.h"
#include "tilp_core.h"
#include "labels.h"
#include "ctree.h"

/* Callbacks */

GLADE_CB void
rbm_change_device1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	display_device_dbox();
}

extern void show_right_view(int view);

GLADE_CB void
rbm_local_view1_activate             (GtkCheckMenuItem    *action,
                                        gpointer         user_data)
{
	if(options.full_gui)
		gtk_window_get_size(GTK_WINDOW(main_wnd), &options.wnd_x_size1, &options.wnd_y_size1);
	else
		gtk_window_get_size(GTK_WINDOW(main_wnd), &options.wnd_x_size2, &options.wnd_y_size2);

	options.full_gui = gtk_check_menu_item_get_active(action);
	show_right_view(options.full_gui);
	toolbar_refresh_buttons();

	if(options.full_gui)
		gtk_window_resize(GTK_WINDOW(main_wnd), options.wnd_x_size1, options.wnd_y_size1);
	else
		gtk_window_resize(GTK_WINDOW(main_wnd), options.wnd_x_size2, options.wnd_y_size2);
}

GLADE_CB void 
rbm_options1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	display_options_dbox();
}

GLADE_CB void 
rbm_delete_var1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	tilp_calc_del_var();
	remote.memory.ram_used = ticalcs_dirlist_ram_used(remote.var_tree);

	labels_refresh();
	ctree_refresh();
}

GLADE_CB void 
rbm_create_folder1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	tilp_calc_new_fld();
}

GLADE_CB void
rbm_recv_as_group1_activate             (GtkCheckMenuItem *action,
                                        gpointer         user_data)
{
	options.recv_as_group = gtk_check_menu_item_get_active(action);
}

GLADE_CB void
rbm_backup_as_tigroup1_activate        (GtkCheckMenuItem  *action,
                                        gpointer         user_data)
{
	options.backup_as_tigroup = gtk_check_menu_item_get_active(action);
}

/* Create/update menu */

GtkWidget *create_ctree_rbm(void)
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *menu;
	gpointer data;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("ctree_rbm.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}

	gtk_builder_connect_signals(builder, NULL);

	data = gtk_builder_get_object (builder, "local_view1");
	g_signal_handlers_block_by_func(data, rbm_local_view1_activate, NULL);
	gtk_check_menu_item_set_active(data, options.full_gui);
	g_signal_handlers_unblock_by_func(data, rbm_local_view1_activate, NULL);

	data = gtk_builder_get_object (builder, "recv_as_group1");
	gtk_check_menu_item_set_active(data, options.recv_as_group);
	if(options.calc_model == CALC_NSPIRE)
		gtk_widget_set_sensitive(data, FALSE);

	data = gtk_builder_get_object (builder, "backup_as_tigroup1");
	gtk_check_menu_item_set_active(data, options.backup_as_tigroup);
	if(options.calc_model == CALC_NSPIRE)
		gtk_widget_set_sensitive(data, FALSE);

	data = gtk_builder_get_object (builder, "delete_var1");
	gtk_widget_set_sensitive(data, (ticalcs_calc_features(calc_handle) & OPS_DELVAR));

	data = gtk_builder_get_object (builder, "create_folder1");
	gtk_widget_set_sensitive(data, (ticalcs_calc_features(calc_handle) & OPS_NEWFLD));

	menu = GTK_WIDGET (gtk_builder_get_object (builder, "ctree_rbm"));
	return menu;
}
