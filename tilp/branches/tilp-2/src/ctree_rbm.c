/* Hey EMACS -*- linux-c -*- */
/* $Id: ctree_rbm.c 1218 2005-06-22 09:27:55Z roms $ */

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

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "support.h"
#include "gstruct.h"
#include "device.h"
#include "toolbar.h"
#include "tilp_core.h"

/* Create/update menu */

GtkWidget *create_ctree_rbm(void)
{
	GladeXML *xml;
	GtkWidget *menu;
	gpointer data;

	xml = glade_xml_new(tilp_paths_build_glade("ctree_rbm-2.glade"), "ctree_rbm", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	data = glade_xml_get_widget(xml, "full_path1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), !options.local_path);

	data = glade_xml_get_widget(xml, "local_view1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), options.full_gui);

	menu = glade_xml_get_widget(xml, "ctree_rbm");
	return menu;
}

/* Callbacks */

GLADE_CB void
rbm_full_path1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	options.local_path = !GTK_CHECK_MENU_ITEM(menuitem)->active;
}

GLADE_CB void
rbm_change_device1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	display_device_dbox();
}

extern void show_right_view(int view);

GLADE_CB void
rbm_local_view1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	options.full_gui = GTK_CHECK_MENU_ITEM(menuitem)->active;
	show_right_view(options.full_gui);
	toolbar_refresh_buttons();
}

GLADE_CB void 
rbm_options1_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	display_options_dbox();
}