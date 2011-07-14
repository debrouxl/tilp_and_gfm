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
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "support.h"
#include "screenshot.h"
#include "dboxes.h"
#include "scroptions.h"
#include "filesel.h"
#include "tilp_core.h"

GtkWidget *scrn_win;
static GtkWidget *scrn_img;

gint display_screenshot_dbox()
{
	GladeXML *xml;
	GdkPixbuf *pixbuf;

	xml = glade_xml_new(tilp_paths_build_glade("screenshot-2.glade"), "screenshot_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	scrn_win = glade_xml_get_widget(xml, "screenshot_dbox");
	scrn_img = glade_xml_get_widget(xml, "pixmap7");

	pixbuf = create_pixbuf("screendump.png");
	gtk_image_set_from_pixbuf(GTK_IMAGE(scrn_img), pixbuf);
	g_object_unref(pixbuf);

	gtk_widget_show_all(scrn_win);

	return 0;
}

GLADE_CB void on_sc_load1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	const gchar *filename;
	GdkPixbuf *pixbuf;
	GError *error = NULL;

	filename = create_fsel(local.cwdir, NULL, "*.jpg;*.png;*.xpm;*.bmp", FALSE);
	if (!filename)
		return;

	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (!pixbuf) 
	{
		tilp_warning("Failed to load pixbuf file: %s: %s\n",
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
	const gchar *type;
	const gchar *filename = NULL;

	if(screen_success == FALSE)
		return;

	switch (options.screen_format) 
	{
	case XPM:
		type = "xpm";
		filename = create_fsel(local.cwdir, "screenshot.xpm", "*.xpm", TRUE);
		if (!filename)
			return;

		pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));
		result = gdk_pixbuf_save(pixbuf, filename, type, &error, NULL);
		break;
	case BMP:
		type = "bmp";
		filename = create_fsel(local.cwdir, "screenshot.bmp", "*.bmp", TRUE);
		if (!filename)
			return;

		pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));
		result = gdk_pixbuf_save(pixbuf, filename, type, &error, NULL);
		break;
	case JPG:
		type = "jpeg";
		filename = create_fsel(local.cwdir, "screenshot.jpg", "*.jpg", TRUE);
		if (!filename)
			return;

		pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));
		result = gdk_pixbuf_save(pixbuf, filename, type, &error, "quality", "100", NULL);
		break;
	case PNG:
		type = "png";
		filename = create_fsel(local.cwdir, "screenshot.png", "*.png", TRUE);
		if (!filename)
			return;

		pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));
		result = gdk_pixbuf_save(pixbuf, filename, type, &error, NULL);
		break;
	case PDF:
		type = "pdf";
		filename = create_fsel(local.cwdir, "screenshot.pdf", "*.pdf", TRUE);
		if (!filename)
			return;

		result = screen_write_pdf(filename, &error);
		break;
	case EPS:
		type = "eps";
		filename = create_fsel(local.cwdir, "screenshot.eps", "*.eps", TRUE);
		if (!filename)
			return;

		result = screen_write_eps(filename, &error);
		break;
	default:
		type = "";
		break;
	}
	
	if (result == FALSE) 
	{
		tilp_warning("Failed to save pixbuf file: %s: %s\n", filename, error->message);
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

extern void on_manual1_activate(GtkMenuItem * menuitem, gpointer user_data);

GLADE_CB void on_scdbox_button1_clicked(GtkButton * button,
					gpointer user_data)
{
	GdkPixbuf *pixbuf;
	guchar *bytemap;
	gint w, h;

	if (screen_capture())
	{
		screen_success = FALSE;
		return;
	} 
	else
	{
		screen_success = TRUE;
	}
	
	w = screen.width;
	h = screen.height;

	if(options.calc_model != CALC_NSPIRE)
	{
		if (options.screen_blurry)
			bytemap = screen_bw_blurry();
		else
			bytemap = screen_bw_convert();
	}
	else
	{
		// For Nspires, we have to determine the calc model...
		CalcInfos infos;
		if (ticalcs_calc_get_version(calc_handle, &infos))
		{
			screen_success = FALSE;
			return;
		}

		if (infos.bits_per_pixel == 4)
		{
			// Nspire (CAS) Clickpad or Touchpad.
			bytemap = screen_gs_convert();
		}
		else if (infos.bits_per_pixel == 16)
		{
			// Nspire (CAS) CX.
			bytemap = screen_16bitcolor_convert();
		}
		else
		{
			tilp_critical(_("Unknown calculator model with %d bpp\n"), infos.bits_per_pixel);
			screen_success = FALSE;
			return;
		}
	}

	pixbuf = gdk_pixbuf_new_from_data(bytemap, GDK_COLORSPACE_RGB, FALSE,
				     8, w, h, 3 * w, destroy_pixbuf, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(scrn_img), pixbuf);
	g_object_unref(pixbuf);
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

GLADE_CB void on_scdbox_button4_clicked(GtkButton * button, gpointer user_data)
{
	on_manual1_activate(NULL, NULL);
}

GLADE_CB void on_scdbox_button5_clicked(GtkButton * button, gpointer user_data)
{
	GdkPixbuf *pixbuf;
	GtkClipboard *clipboard;

	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(scrn_img));

	clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	gtk_clipboard_set_image(clipboard, pixbuf);
}
