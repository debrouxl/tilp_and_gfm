/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

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
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "support.h"
#include "scroptions.h"
#include "tilp_core.h"

gint tmp_image_format;
gint tmp_screen_mode;
gint tmp_grayscales;

gint display_scroptions_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	xml = glade_xml_new(tilp_paths_build_glade("screenopts-2.glade"), "screenopts_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "screenopts_dbox");

	data = glade_xml_get_widget(xml, "radiobutton10");
	tmp_image_format = options.screen_format;
	if (options.screen_format == PNG)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton11");
	tmp_image_format = options.screen_format;
	if (options.screen_format == XPM)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton12");
	tmp_image_format = options.screen_format;
	if (options.screen_format == JPG)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),  TRUE);

	data = glade_xml_get_widget(xml, "radiobutton13");
	tmp_image_format = options.screen_format;
	if (options.screen_format == BMP)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);
	data = glade_xml_get_widget(xml, "radiobutton23");
	tmp_image_format = options.screen_format;
	if (options.screen_format == PDF)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton24");
	tmp_image_format = options.screen_format;
	if (options.screen_format == EPS)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton21");
	tmp_screen_mode = options.screen_clipping;
	if (options.screen_clipping == SCREEN_FULL)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "radiobutton22");
	tmp_screen_mode = options.screen_clipping;
	if (options.screen_clipping == SCREEN_CLIPPED)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = glade_xml_get_widget(xml, "checkbutton1");
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

GLADE_CB void
on_radiobutton10_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = PNG;
}

GLADE_CB void
on_radiobutton11_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = XPM;
}

GLADE_CB void
on_radiobutton12_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = JPG;
}
GLADE_CB void
on_radiobutton13_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = BMP;
}
GLADE_CB void
on_radiobutton23_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = PDF;
}
GLADE_CB void
on_radiobutton24_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_image_format = EPS;
}

GLADE_CB void
on_radiobutton21_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_screen_mode = SCREEN_FULL;
}

GLADE_CB void
on_radiobutton22_toggled(GtkToggleButton * togglebutton,
			 gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton))
		tmp_screen_mode = SCREEN_CLIPPED;
}

GLADE_CB void
on_scopt_checkbutton1_toggled(GtkToggleButton * togglebutton,
			      gpointer user_data)
{
	if (togglebutton->active == TRUE)
		tmp_grayscales = !0;
	else
		tmp_grayscales = 0;
}
