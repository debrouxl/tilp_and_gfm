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
#include <string.h>

#include "general.h"
#include "tilp_core.h"
#include "clist.h"
static TilpOptions tmp_options;
gint display_general_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;
	xml = glade_xml_new
	    (tilp_paths_build_glade("general-2.glade"), "general_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);
	dbox = glade_xml_get_widget(xml, "general_dbox");
	memcpy(&tmp_options, &options, sizeof(options));
	data = glade_xml_get_widget(xml, "radiobutton21");
	if (options.path_mode == FULL_PATH)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton22");
	if (options.path_mode == LOCAL_PATH)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton31");
	if (options.ctree_sort == SORT_BY_NAME)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton32");
	if (options.ctree_sort == SORT_BY_TYPE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton33");
	if (options.ctree_sort == SORT_BY_INFO)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton34");
	if (options.ctree_sort == SORT_BY_SIZE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton41");
	if (options.ctree_sort_order == SORT_UP)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton42");
	if (options.ctree_sort_order == SORT_DOWN)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton81");
	if (options.single_or_group == RECV_AS_SINGLE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton82");
	if (options.single_or_group == RECV_AS_GROUP)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton51");
	if (options.file_disp == SHOW_ALL)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton52");
	if (options.file_disp == SHOW_TIF)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "checkbutton2");
	if (options.confirm == CONFIRM_YES)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);

	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     FALSE);
	data = glade_xml_get_widget(xml, "radiobutton61");
	if (options.clist_sort == SORT_BY_NAME)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton62");
	if (options.clist_sort == SORT_BY_TYPE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton63");
	if (options.clist_sort == SORT_BY_DATE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton64");
	if (options.clist_sort == SORT_BY_SIZE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton71");
	if (options.clist_sort_order == SORT_UP)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton72");
	if (options.clist_sort_order == SORT_DOWN)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	while (gtk_events_pending())
		gtk_main_iteration();
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) {
	case GTK_RESPONSE_OK:
		memcpy(&options, &tmp_options, sizeof(tmp_options));
		clist_refresh();
		break;
	case GTK_RESPONSE_HELP:
		break;
	default:
		break;
	}
	gtk_widget_destroy(dbox);
	return 0;
}
GLADE_CB void
on_radiobutton61_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.clist_sort = SORT_BY_NAME;
} GLADE_CB void
on_radiobutton63_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.clist_sort = SORT_BY_DATE;
} GLADE_CB void
on_radiobutton64_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.clist_sort = SORT_BY_SIZE;
} GLADE_CB void
on_radiobutton62_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.clist_sort = SORT_BY_TYPE;
} GLADE_CB void
on_radiobutton51_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.file_disp = SHOW_ALL;
} GLADE_CB void
on_radiobutton52_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.file_disp = SHOW_TIF;
} GLADE_CB void
on_radiobutton71_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.clist_sort_order = SORT_UP;
} GLADE_CB void
on_radiobutton72_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.clist_sort_order = SORT_DOWN;
} GLADE_CB void
on_general_checkbutton2_toggled(GtkToggleButton * togglebutton,
				gpointer user_data)
{
	if (togglebutton->active == TRUE)
		tmp_options.confirm = CONFIRM_YES;

	else
		tmp_options.confirm = CONFIRM_NO;
}
GLADE_CB void
on_radiobutton31_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.ctree_sort = SORT_BY_NAME;
} GLADE_CB void
on_radiobutton32_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.ctree_sort = SORT_BY_TYPE;
} GLADE_CB void
on_radiobutton33_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.ctree_sort = SORT_BY_INFO;
} GLADE_CB void
on_radiobutton34_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.ctree_sort = SORT_BY_SIZE;
} GLADE_CB void
on_radiobutton41_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.ctree_sort_order = SORT_UP;
} GLADE_CB void
on_radiobutton42_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.ctree_sort_order = SORT_DOWN;
} GLADE_CB void
on_general_radiobutton21_toggled(GtkToggleButton * togglebutton,
				 gpointer user_data)
{
	tmp_options.path_mode = FULL_PATH;
} GLADE_CB void
on_general_radiobutton22_toggled(GtkToggleButton * togglebutton,
				 gpointer user_data)
{
	tmp_options.path_mode = LOCAL_PATH;
} GLADE_CB void
on_radiobutton81_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.single_or_group = RECV_AS_SINGLE;
} GLADE_CB void
on_radiobutton82_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	tmp_options.single_or_group = RECV_AS_GROUP;
}
