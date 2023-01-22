#ifndef __ACTION_H__
#define __ACTION_H__

#include "tilp_defs.h"
#include <gtk/gtk.h>

gint display_action_dbox(gchar * dst_folder);

TILP_EXPORT void action_overwrite_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void action_rename_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void action_skip_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void action_select_all_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void action_deselect_all_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT gboolean action_treeview1_button_press_event(GtkWidget* widget, GdkEventButton* event, gpointer user_data);

#endif
