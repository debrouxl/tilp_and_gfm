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
#endif				/*  */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "tilp_version.h"
#include "tilp_core.h"
#include "gtk_update.h"
#include "splash.h"

#if GTK_CHECK_VERSION(3,2,0)
#define gtk_vbox_new(a,spacing) gtk_box_new(GTK_ORIENTATION_VERTICAL,spacing)
#endif

typedef struct 
{
	GtkWidget *window;
	GtkWidget *label;
} TilpSplashScreen;

static TilpSplashScreen ss;

GtkWidget *splash_screen_start(void)
{
	GtkWidget *image, *vbox;
#if GTK_CHECK_VERSION(3,0,0)
	GdkRGBA color;
#else
	GdkColor color;
#endif
	GdkPixbuf *pixbuf;

	ss.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ss.window), TILP_VERSION);
	gtk_window_set_position(GTK_WINDOW(ss.window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_decorated(GTK_WINDOW(ss.window), FALSE);
	gtk_window_set_role(GTK_WINDOW(ss.window), "splash");
	gtk_window_set_resizable(GTK_WINDOW(ss.window), FALSE);
	gtk_window_set_default_size(GTK_WINDOW(ss.window), 150, 150);
#if GTK_CHECK_VERSION(3,0,0)
	color.red = 1.0;
	color.blue = 1.0;
	color.green = 1.0;
	color.alpha = 1.0;
	gtk_widget_override_background_color(ss.window, GTK_STATE_NORMAL, &color);
#else
	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	gtk_widget_modify_bg(ss.window, GTK_STATE_NORMAL, &color);
#endif
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(ss.window), vbox);
	gtk_widget_show(vbox);
	ss.label = gtk_label_new("starting TiLP...");
	gtk_box_pack_end(GTK_BOX(vbox), ss.label, FALSE, FALSE, 0);
	gtk_widget_show(ss.label);
	pixbuf = create_pixbuf("logo.png");
	image = gtk_image_new_from_pixbuf(pixbuf);
	gtk_box_pack_end(GTK_BOX(vbox), image, FALSE, FALSE, 0);
	g_object_unref(pixbuf);
	gtk_widget_show(image);
	gtk_widget_show(ss.window);

	return ss.window;
}

void splash_screen_stop(void)
{
	gtk_widget_destroy(ss.window);
} 

void splash_screen_set_label(gchar * label)
{
	gtk_label_set_text(GTK_LABEL(ss.label), label);
	GTK_REFRESH();
}
