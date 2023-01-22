#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "tilp_defs.h"
#include <gtk/gtk.h>

gint display_device_dbox(void);

gboolean comm_treeview1_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
TILP_EXPORT void on_device_combobox1_changed(GtkComboBox *combobox, gpointer user_data);
TILP_EXPORT void on_device_combobox2_changed(GtkComboBox *combobox, gpointer user_data);
TILP_EXPORT void on_device_combobox3_changed(GtkComboBox *combobox, gpointer user_data);
TILP_EXPORT void comm_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
TILP_EXPORT void comm_spinbutton_delay_changed(GtkEditable *editable, gpointer user_data);
TILP_EXPORT void comm_spinbutton_timeout_changed(GtkEditable *editable, gpointer user_data);
TILP_EXPORT void comm_button_search_clicked(GtkButton *button, gpointer user_data);

#endif
