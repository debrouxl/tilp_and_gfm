#include <gtk/gtk.h>


void
on_plugins_dbox_show                   (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_plugins_ok_button_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_plugins_cancel_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_plugins_dbox_show                   (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_registry_dbox_show                  (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_clist1_click_column                 (GtkCList        *clist,
                                        gint             column,
                                        gpointer         user_data);

void
on_registry_button1_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_registry_button2_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_registry_clist1_click_column        (GtkCList        *clist,
                                        gint             column,
                                        gpointer         user_data);
