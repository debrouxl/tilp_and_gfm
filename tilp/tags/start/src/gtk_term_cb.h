#include <gtk/gtk.h>


void
on_term_dbox_show                      (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_term_quit1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_term_remote_control1_activate       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_term_terminal1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_term_leave1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_term_help3_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_term_manpage1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_term_about1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_text1_key_press_event               (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_term_dbox_show_text                 (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_term_dbox_show_dbox                 (GtkWidget       *widget,
                                        gpointer         user_data);
