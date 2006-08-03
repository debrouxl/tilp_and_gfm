/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  28/05/06 20:54 - splashscreen.c

  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "splashscreen.h"
#include "support.h"
#include "version.h"

/* Structure for inner communication */
typedef struct {
        GtkWidget *splash, *text;
        short enabled;
} GFMSplashScreen;
static GFMSplashScreen splashscreen = { 0 };

/* Splash Screen Initialization Function */
void splash_screen_start(void)
{
    GtkWidget *image, *vbox, *ver_lbl;
    GdkColor color;
    GdkPixbuf *pixbuf;
    char *version_string;

    // Is Splash Screen started?
    if (splashscreen.enabled == 1)
        return;

    // Make the Splash Screen
     splashscreen.splash = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(splashscreen.splash), "GFM Loading...");
     gtk_window_set_position(GTK_WINDOW(splashscreen.splash), GTK_WIN_POS_CENTER_ALWAYS);
     gtk_window_set_decorated(GTK_WINDOW(splashscreen.splash), FALSE);
     gtk_window_set_role(GTK_WINDOW(splashscreen.splash), "splash");
     gtk_window_set_resizable(GTK_WINDOW(splashscreen.splash), FALSE);
     gtk_window_set_default_size(GTK_WINDOW(splashscreen.splash), 150, 110); // 150x110 pixels

     // Set the Colors
     color.red = 65535;
     color.green = 65535;
     color.blue = 65535;
     gtk_widget_modify_bg(splashscreen.splash, GTK_STATE_NORMAL, &color);

     // Create a VBOX
     vbox = gtk_vbox_new(FALSE, 0);
     gtk_container_add(GTK_CONTAINER(splashscreen.splash), vbox);
     gtk_widget_show(vbox);

     // Set the Text Label
     splashscreen.text = gtk_label_new("Starting Group File Manager...");
     gtk_box_pack_end(GTK_BOX(vbox), splashscreen.text, FALSE, FALSE, 0);
     gtk_widget_show(splashscreen.text);

     // Set the Version
     version_string = g_strconcat("Version ", GFM_VERSION, NULL);
     ver_lbl = gtk_label_new(version_string);
     gtk_box_pack_end(GTK_BOX(vbox), ver_lbl, FALSE, FALSE, 0);
     gtk_widget_show(ver_lbl);
     g_free(version_string);

     // Setup the Splash Logo
     pixbuf = create_pixbuf("logo.xpm");
     image = gtk_image_new_from_pixbuf(pixbuf);
     gtk_box_pack_end(GTK_BOX(vbox), image, FALSE, FALSE, 0);
     g_object_unref(pixbuf);

     // Lets show the Splash Screen now
     gtk_widget_show(image);
     gtk_widget_show(splashscreen.splash);

     // Lets Make sure this works
     GTK_REFRESH(); // Defintion in support.h

     // Ok, done
     splashscreen.enabled = 1;
     return;
}

/* Delete Splash Screen */
void splash_screen_delete(void)
{
    // Enabled?
    if (!splashscreen.enabled)
        return;

    // Delete
    gtk_widget_destroy(splashscreen.splash);
    splashscreen.enabled = 0;

    return;
}

/* Set new Splash Screen Text */
int splash_screen_message(char *message)
{
    // Enabled?
    if (!splashscreen.enabled)
        return -1;

    // Update Label
    gtk_label_set_text(GTK_LABEL(splashscreen.text), (gchar *)message);

    // Refresh GTK+
    GTK_REFRESH();

    return 0;
}
