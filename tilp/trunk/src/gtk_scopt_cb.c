#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_scopt_cb.h"
#include "gtk_scopt_dbox.h"
#include "support.h"

#include "includes.h"

gint i_image_format;
gint i_screen_mode;


void
on_radiobutton18_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton))
    i_image_format = PCX;
}


void
on_radiobutton19_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton))
    i_image_format = XPM;
}


void
on_radiobutton20_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton))
    i_image_format = JPG;
}


void
on_radiobutton21_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton))
    i_screen_mode = FULL_SCREEN;
}


void
on_radiobutton22_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton))
    i_screen_mode = CLIPPED_SCREEN;
}


void
on_scopt_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
  options.screen_format = i_image_format;
  options.screen_clipping = i_screen_mode;
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_scopt_cancel_button_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_scopt_dbox_show18                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  DISPLAY("screen_format: %i\n", options.screen_format);
  i_image_format = options.screen_format;
  if(options.screen_format == PCX)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_scopt_dbox_show19                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  i_image_format = options.screen_format;
  if(options.screen_format == XPM)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_scopt_dbox_show20                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  i_image_format = options.screen_format;
  if(options.screen_format == JPG)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_scopt_dbox_show21                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  i_screen_mode = options.screen_clipping;
  if(options.screen_clipping == FULL_SCREEN)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_scopt_dbox_show22                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  i_screen_mode = options.screen_clipping;
  if(options.screen_clipping == CLIPPED_SCREEN)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}

/* */
