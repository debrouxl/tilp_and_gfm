/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
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
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "tilp_version.h"
typedef struct {
	GtkWidget *window;
	GtkWidget *label;
} TilpSplashScreen;
static TilpSplashScreen splashscreen;
GtkWidget *splash_screen_start(void)
{
	GtkWidget *image, *vbox;
	GdkColor color;
	GdkPixbuf *pixbuf;
	splashscreen.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(splashscreen.window),
			     TILP_VERSION);
	gtk_window_set_position(GTK_WINDOW(splashscreen.window),
				GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_decorated(GTK_WINDOW(splashscreen.window), FALSE);
	gtk_window_set_role(GTK_WINDOW(splashscreen.window), "splash");
	gtk_window_set_resizable(GTK_WINDOW(splashscreen.window), FALSE);
	gtk_window_set_default_size(GTK_WINDOW(splashscreen.window), 150, 150);
	color.red = 65535;
	color.blue = 65535;
	color.green = 65535;
	gtk_widget_modify_bg(splashscreen.window, GTK_STATE_NORMAL,
			     &color);
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(splashscreen.window), vbox);
	gtk_widget_show(vbox);
	splashscreen.label = gtk_label_new("starting TiLP...");
	gtk_box_pack_end(GTK_BOX(vbox), splashscreen.label, FALSE, FALSE,
			 0);
	gtk_widget_show(splashscreen.label);
	pixbuf = create_pixbuf("logo.xpm");
	image = gtk_image_new_from_pixbuf(pixbuf);
	gtk_box_pack_end(GTK_BOX(vbox), image, FALSE, FALSE, 0);
	g_object_unref(pixbuf);
	gtk_widget_show(image);
	gtk_widget_show(splashscreen.window);
	while (gtk_events_pending()) {
		gtk_main_iteration();
	}
	return splashscreen.window;
}
void splash_screen_stop(void)
{
	gtk_widget_destroy(splashscreen.window);
} void splash_screen_set_label(gchar * label)
{
	gtk_label_set_text(GTK_LABEL(splashscreen.label), label);
	while (gtk_events_pending()) {
		gtk_main_iteration();
	}
}
