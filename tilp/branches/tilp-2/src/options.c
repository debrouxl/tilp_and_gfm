/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU options Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU options Public License for more details.
 *
 *  You should have received a copy of the GNU options Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "support.h"
#include "options.h"
#include "tilp_core.h"

static TilpOptions tmp_options;

gint display_options_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	xml = glade_xml_new(tilp_paths_build_glade("options-2.glade"), "options_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "options_dbox");
	memcpy(&tmp_options, &options, sizeof(options));

	data = glade_xml_get_widget(xml, "radiobutton21");
	if (!options.local_path)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton22");
	if (options.local_path)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	data = glade_xml_get_widget(xml, "radiobutton31");

	data = glade_xml_get_widget(xml, "radiobutton81");
	if (!options.recv_as_group)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton82");
	if (options.recv_as_group)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton51");
	if (options.show_all)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	
	data = glade_xml_get_widget(xml, "radiobutton52");
	if (!options.show_all)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	
	data = glade_xml_get_widget(xml, "checkbutton2");
	if (options.overwrite == CONFIRM_YES)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), FALSE);
	
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
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
options_radiobutton51_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.show_all = 1;
} 

GLADE_CB void
options_radiobutton52_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.show_all = 0;
} 

GLADE_CB void
options_checkbutton2_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	if (togglebutton->active == TRUE)
		tmp_options.overwrite = CONFIRM_YES;
	else
		tmp_options.overwrite = CONFIRM_NO;
}

GLADE_CB void
options_radiobutton21_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.local_path = PATH_FULL;
} 

GLADE_CB void
options_radiobutton22_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.local_path = PATH_LOCAL;
} 

GLADE_CB void
options_radiobutton81_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.recv_as_group = 0;
} 

GLADE_CB void
options_radiobutton82_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.recv_as_group = 1;
}
