#include <gtk/gtk.h>

void msg_box(const gchar *titl, gchar *messag);

void
on_msg_dbox_show                       (GtkWidget       *widget,
                                        gpointer         user_data);

void
msg_ok_button_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_msg_dbox_show1                      (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_msg_dbox_show2                      (GtkWidget       *widget,
                                        gpointer         user_data);
