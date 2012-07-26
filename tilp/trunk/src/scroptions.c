/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *  Copyright (C) 2007  Kevin Kofler
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
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "support.h"
#include "scroptions.h"
#include "tilp_core.h"

gint tmp_image_format;
gint tmp_screen_mode;
gint tmp_grayscales;

gint display_scroptions_dbox()
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("screenopts.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}

	dbox = GTK_WIDGET (gtk_builder_get_object (builder, "screenopts_dbox"));
	gtk_dialog_set_alternative_button_order(GTK_DIALOG(dbox), GTK_RESPONSE_OK,
	                                        GTK_RESPONSE_CANCEL,-1);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton10"));
	tmp_image_format = options.screen_format;
	if (options.screen_format == PNG)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton11"));
	tmp_image_format = options.screen_format;
	if (options.screen_format == XPM)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton12"));
	tmp_image_format = options.screen_format;
	if (options.screen_format == JPG)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),  TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton13"));
	tmp_image_format = options.screen_format;
	if (options.screen_format == BMP)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton14"));
	tmp_image_format = options.screen_format;
	if (options.screen_format == PDF)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton15"));
	tmp_image_format = options.screen_format;
	if (options.screen_format == EPS)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton21"));
	tmp_screen_mode = options.screen_clipping;
	if (options.screen_clipping == SCREEN_FULL)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton22"));
	tmp_screen_mode = options.screen_clipping;
	if (options.screen_clipping == SCREEN_CLIPPED)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "checkbutton1"));
	tmp_grayscales = options.screen_blurry;
	if (tmp_grayscales != 0)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), FALSE);

	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		options.screen_format = tmp_image_format;
		options.screen_clipping = tmp_screen_mode;
		options.screen_blurry = tmp_grayscales;
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
on_radiobutton10_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = PNG;
}

TILP_EXPORT void
on_radiobutton11_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = XPM;
}

TILP_EXPORT void
on_radiobutton12_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = JPG;
}
TILP_EXPORT void
on_radiobutton13_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = BMP;
}
TILP_EXPORT void
on_radiobutton14_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = PDF;
}
TILP_EXPORT void
on_radiobutton15_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = EPS;
}

TILP_EXPORT void
on_radiobutton21_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_screen_mode = SCREEN_FULL;
}

TILP_EXPORT void
on_radiobutton22_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_screen_mode = SCREEN_CLIPPED;
}

TILP_EXPORT void
on_scopt_checkbutton1_toggled(GtkToggleButton * togglebutton,
			      gpointer user_data)
{
	if (togglebutton->active == TRUE)
		tmp_grayscales = !0;
	else
		tmp_grayscales = 0;
}
