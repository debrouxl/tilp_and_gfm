/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *  Copyright (C) 2007  Kevin Kofler
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "support.h"
#include "options.h"
#include "tilp_core.h"
#include "clist.h"

static TilpOptions tmp_options;

gint display_options_dbox()
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("options.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	dbox = GTK_WIDGET (gtk_builder_get_object (builder, "options_dbox"));
	gtk_dialog_set_alternative_button_order(GTK_DIALOG(dbox), GTK_RESPONSE_OK,
	                                        GTK_RESPONSE_CANCEL,-1);
	memcpy(&tmp_options, &options, sizeof(options));

	if(options.calc_model == CALC_NSPIRE)
	{
		data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton31"));
		gtk_widget_set_sensitive(data, FALSE);
		data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton32"));
		gtk_widget_set_sensitive(data, FALSE);
	}
	else
	{
	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton31"));
	if (!options.backup_as_tigroup)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton32"));
	if (options.backup_as_tigroup)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	}

	if(options.calc_model == CALC_NSPIRE)
	{
		data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton81"));
		gtk_widget_set_sensitive(data, FALSE);
		data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton82"));
		gtk_widget_set_sensitive(data, FALSE);
	}
	else
	{
		data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton81"));
		if (!options.recv_as_group)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

		data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton82"));
		if (options.recv_as_group)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	}

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton51"));
	if (options.show_all)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	
	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton52"));
	if (!options.show_all)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	
	data = GTK_WIDGET (gtk_builder_get_object (builder, "checkbutton2"));
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

TILP_EXPORT void
options_radiobutton51_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.show_all = 1;
} 

TILP_EXPORT void
options_radiobutton52_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.show_all = 0;
} 

TILP_EXPORT void
options_checkbutton2_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	if (togglebutton->active == TRUE)
		tmp_options.overwrite = CONFIRM_YES;
	else
		tmp_options.overwrite = CONFIRM_NO;
}

TILP_EXPORT void
options_radiobutton81_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.recv_as_group = 0;
} 

TILP_EXPORT void
options_radiobutton82_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.recv_as_group = 1;
}

TILP_EXPORT void
options_radiobutton31_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.backup_as_tigroup = 0;
} 

TILP_EXPORT void
options_radiobutton32_toggled(GtkToggleButton * togglebutton, gpointer user_data)
{
	tmp_options.backup_as_tigroup = 1;
}
