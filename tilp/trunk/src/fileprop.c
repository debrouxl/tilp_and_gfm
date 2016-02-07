/* Hey EMACS -*- linux-c -*- */
/* $Id: manpage.c 3064 2006-11-11 01:40:06Z kevinkofler $ */

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
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "fileprop.h"
#include "tilp_core.h"

static GtkTextBuffer *txtbuf;

static void new_log_handler(const gchar *log_domain,
                            GLogLevelFlags log_level,
                            const gchar *message,
                            gpointer user_data) 
{
	gtk_text_buffer_insert_at_cursor(txtbuf, message, strlen(message));
	gtk_text_buffer_insert_at_cursor(txtbuf, "\r\n", 2);
}

gint display_properties_dbox(const char *filename)
{
	GtkBuilder *builder;
	GObject *dbox;
	GObject *text;
	GError* error = NULL;
	gint result;
	guint hid;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("manpage.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	dbox = gtk_builder_get_object(builder, "manpage_dbox");
	text = gtk_builder_get_object(builder, "textview1");
	txtbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));

	hid = g_log_set_handler("tifiles", G_LOG_LEVEL_INFO, new_log_handler, NULL);
	tifiles_file_display(filename);
	g_log_remove_handler("tifiles", hid);

	{
		PangoFontDescription *font_desc;
		GObject *view = text;

		font_desc = pango_font_description_from_string ("Courier");
		gtk_widget_modify_font (GTK_WIDGET(view), font_desc);
		pango_font_description_free (font_desc);
	}

	gtk_window_set_title(GTK_WINDOW(dbox), g_path_get_basename(filename));
	gtk_widget_show(GTK_WIDGET(dbox));

	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		break;
	default:
		break;
	}

	gtk_widget_destroy(GTK_WIDGET(dbox));

	return 0;
}
