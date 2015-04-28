#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <gtk/gtk.h>

gint display_clock_dbox(void);

void clock_radiobutton1_toggled(GtkToggleButton * togglebutton, gpointer user_data);
void clock_radiobutton2_toggled(GtkToggleButton * togglebutton, gpointer user_data);
void clock_radiobutton3_toggled(GtkToggleButton * togglebutton, gpointer user_data);
void clock_radiobutton4_toggled(GtkToggleButton * togglebutton, gpointer user_data);
void on_clock_combobox1_changed(GtkComboBox *combobox, gpointer user_data);
void on_clock_combobox2_changed(GtkComboBox *combobox, gpointer user_data);
void clock_spinbutton3_changed(GtkEditable * editable, gpointer user_data);
void clock_spinbutton4_changed(GtkEditable * editable, gpointer user_data);
void clock_spinbutton5_changed(GtkEditable * editable, gpointer user_data);
void clock_spinbutton6_changed(GtkEditable * editable, gpointer user_data);
void clock_spinbutton1_changed(GtkEditable * editable, gpointer user_data);
void clock_sync_button_clicked(GtkButton * button, gpointer user_data);

#endif
