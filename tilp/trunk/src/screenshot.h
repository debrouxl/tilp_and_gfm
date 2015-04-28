#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__

#include <gtk/gtk.h>

gint display_screenshot_dbox(void);

void on_sc_load1_activate(GtkMenuItem * menuitem, gpointer user_data);
void on_sc_save1_activate(GtkMenuItem * menuitem, gpointer user_data);
void on_sc_quit1_activate(GtkMenuItem * menuitem, gpointer user_data);
void on_sc_options1_activate(GtkMenuItem * menuitem, gpointer user_data);
void on_scdbox_button1_clicked(GtkButton * button, gpointer user_data);
void on_scdbox_button2_clicked(GtkButton * button, gpointer user_data);
void on_scdbox_button3_clicked(GtkButton * button, gpointer user_data);
void on_scdbox_button4_clicked(GtkButton * button, gpointer user_data);
void on_scdbox_button5_clicked(GtkButton * button, gpointer user_data);

#endif
