#include <gtk/gtk.h>

gchar *dlgbox_entry(const char *title, 
		    const char *message, 
		    const char *content);

void
on_entry_dbox_show1                    (GtkWidget       *widget,
                                        gpointer         user_data);

void
entry_ok_button_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_entry_dbox_show2                    (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_entry_dbox_show3                    (GtkWidget       *widget,
                                        gpointer         user_data);

void
entry_cancel_button_clicked            (GtkButton       *button,
                                        gpointer         user_data);
