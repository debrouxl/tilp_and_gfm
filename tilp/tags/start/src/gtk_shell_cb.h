#include <gtk/gtk.h>


int execute_command(gchar *cmd_line);

void
on_shell_dbox_show                     (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_shell_dbox_show2                    (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_shell_entry1_activate               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_shell_entry1_activate               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_shell_dbox_destroy                  (GtkObject       *object,
                                        gpointer         user_data);
