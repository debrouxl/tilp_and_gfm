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

#include "tilp_core.h"
#include "screenshot.h"
#include "support.h"
#include "dboxes.h"
#include "scroptions.h"
#include "gtk_refresh.h"

GtkWidget *scrn_win;
static GtkWidget *scrn_img;
extern TilpScreen ti_screen;
static const gchar *create_fsel(void);

gint display_screenshot_dbox()
{
	GladeXML *xml;
	GdkPixbuf *pixbuf;

	xml = glade_xml_new
	    (tilp_paths_build_glade("screenshot-2.glade"),
	     "screenshot_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");

	glade_xml_signal_autoconnect(xml);
	scrn_win = glade_xml_get_widget(xml, "screenshot_dbox");
	scrn_img = glade_xml_get_widget(xml, "pixmap7");
	pixbuf = create_pixbuf("screendump.xpm");
	gtk_image_set_from_pixbuf(GTK_IMAGE(scrn_img), pixbuf);
	g_object_unref(pixbuf);

	gtk_widget_show_all(scrn_win);

	return 0;
}

GLADE_CB void on_sc_load1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	const gchar *filename;
	GdkPixbuf *pixbuf;
	GError *error = NULL;

	filename = create_fsel();
	if (!filename)
		return;

	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (!pixbuf) 
	{
		printl(2, "Failed to load pixbuf file: %s: %s\n",
			filename, error->message);
		g_error_free(error);
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(scrn_img), pixbuf);
	g_object_unref(pixbuf);
}

static gboolean screen_success = FALSE;

GLADE_CB void on_sc_save1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	GdkPixbuf *pixbuf;
	gboolean result = FALSE;
	GError *error = NULL;
	gchar *type;
	const gchar *filename = NULL;

	if(screen_success == FALSE)
		return;

	switch (options.screen_format) {
	case XPM:
	case PCX:
	case BMP:
		msg_box("Information",
			"Sorry, these formats are not supported any longer.");
		return;
		break;
	case JPG:
		type = "jpeg";
		filename = create_fsel();
		if (!filename)
			return;
		pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));
		result =
		    gdk_pixbuf_save(pixbuf, filename, type, &error,
				    "quality", "100", NULL);
		break;
	case PNG:
		type = "png";
		filename = create_fsel();
		if (!filename)
			return;
		pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));
		result =
		    gdk_pixbuf_save(pixbuf, filename, type, &error, NULL);
		break;
	default:
		type = "";
		break;
	}
	
	if (result == FALSE) {
		printl(2, "Failed to save pixbuf file: %s: %s\n",
			filename, error->message);
		g_error_free(error);
	}
	filename = NULL;
}

GLADE_CB void on_sc_quit1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	gtk_widget_destroy(scrn_win);
}

GLADE_CB void on_sc_options1_activate(GtkMenuItem * menuitem,
				      gpointer user_data)
{
	display_scroptions_dbox();
}

static void destroy_pixbuf(guchar * pixels, gpointer data)
{
	g_free(pixels);
}

GLADE_CB void on_scdbox_button1_clicked(GtkButton * button,
					gpointer user_data)
{
	GdkPixbuf *pixbuf;
	guchar *bytemap;
	gint w, h;

	if (tilp_screen_capture()) {
		screen_success = FALSE;	
		return;
	} else
		screen_success = TRUE;
	
	w = ti_screen.width;
	h = ti_screen.height;

	if (options.screen_blurry)
		bytemap = tilp_screen_blurry();
	else
		bytemap = tilp_screen_convert();

	pixbuf =
	    gdk_pixbuf_new_from_data(bytemap, GDK_COLORSPACE_RGB, FALSE,
				     8, w, h, 3 * w, destroy_pixbuf, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(scrn_img), pixbuf);
	g_object_unref(pixbuf);
	//g_free(bytemap);
}

GLADE_CB void on_scdbox_button2_clicked(GtkButton * button,
					gpointer user_data)
{
	on_sc_save1_activate(NULL, NULL);
}

GLADE_CB void on_scdbox_button3_clicked(GtkButton * button,
					gpointer user_data)
{
	gtk_widget_destroy(scrn_win);
}

extern void on_manual1_activate(GtkMenuItem * menuitem,
				gpointer user_data);

GLADE_CB void on_scdbox_button4_clicked(GtkButton * button,
					gpointer user_data)
{
	on_manual1_activate(NULL, NULL);
} 

static gchar *filename = NULL;

static void store_filename(GtkFileSelection * file_selector,
			   gpointer user_data)
{
	filename = (gchar *)
	    gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
} 

static void cancel_filename(GtkButton * button, gpointer user_data)
{
	filename = "";
} 

static const gchar *create_fsel(void)
{
	GtkWidget *fs;
	gchar *ext;

	switch (options.screen_format) {
	case JPG:
		ext = "*.jpg";
		break;
	case PNG:
		ext = "*.png";
		break;
	default:
		ext = "";
		break;
	}

	fs = gtk_file_selection_new("Select a File.");
	gtk_file_selection_complete(GTK_FILE_SELECTION(fs), ext);
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(store_filename), fs);
	g_signal_connect(GTK_OBJECT
			 (GTK_FILE_SELECTION(fs)->cancel_button),
			 "clicked", G_CALLBACK(cancel_filename), fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->ok_button),
				 "clicked",
				 G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);

	filename = NULL;
	gtk_widget_show(fs);
	while (filename == NULL)
		GTK_REFRESH();

	if (!strcmp(filename, ""))
		return NULL;
	else
		return filename;
}





