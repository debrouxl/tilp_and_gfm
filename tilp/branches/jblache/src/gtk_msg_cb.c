#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_msg_cb.h"
#include "gtk_msg_dbox.h"
#include "support.h"


static const gchar *title;
static gchar *message;

void msg_box(const gchar *titl, gchar *messag)
{
  title = titl;
  message = messag;

  gtk_widget_show_all(create_msg_dbox());
}


void
on_msg_dbox_show1                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_window_set_title (GTK_WINDOW (user_data), title);
}


void
on_msg_dbox_show2                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_label_set_text(GTK_LABEL(user_data), message);
}


void
msg_ok_button_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}
