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

#include "release.h"
#include "tilp_core.h"

#if GTK_CHECK_VERSION(3,0,0)
#define gtk_widget_modify_font(widget,font_desc) gtk_widget_override_font(widget,font_desc)
#endif

gint display_release_dbox()
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *dbox;
	GtkTextBuffer *txtbuf;
	GtkWidget *text;
	FILE *fd;
	gchar *filename;
	gchar buffer[32768];
	gint len = 0;
	struct stat stbuf;
	gint result;
	PangoFontDescription *font_desc;

#ifdef _MSC_VER /* MSVC builds. MinGW builds use Linux file structures. */
	filename = g_strconcat(inst_paths.base_dir, "Release.txt", NULL);
#else				/*  */
	filename = g_strconcat(inst_paths.base_dir, "RELEASE", NULL);
#endif				/*  */

	if (access(filename, F_OK) == 0) 
	{
		if (stat(filename, &stbuf) != -1) 
		{
			len = stbuf.st_size;
			len -= 2;
		}
		if ((fd = fopen(filename, "r")) != NULL) 
		{
			memset(buffer, 0, sizeof(buffer));
			len = fread(buffer, 1, len, fd);
			fclose(fd);
		}
	}

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("release.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	dbox = GTK_WIDGET (gtk_builder_get_object (builder, "release_dbox"));
	text = GTK_WIDGET (gtk_builder_get_object (builder, "textview1"));

	// Change font
	font_desc = pango_font_description_from_string ("Courier");
	gtk_widget_modify_font (text, font_desc);
	pango_font_description_free (font_desc);

	// Set text
	txtbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	gtk_text_buffer_set_text(txtbuf, buffer, len);
	
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		break;
	default:
		break;
	}
	gtk_widget_destroy(dbox);

	return 0;
}
