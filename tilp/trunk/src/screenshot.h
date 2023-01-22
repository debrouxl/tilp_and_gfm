#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__

#include "tilp_defs.h"
#include <gtk/gtk.h>

gint display_screenshot_dbox(void);

TILP_EXPORT void on_sc_load1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void on_sc_save1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void on_sc_quit1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void on_sc_options1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void on_scdbox_button1_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void on_scdbox_button2_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void on_scdbox_button3_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void on_scdbox_button4_clicked(GtkButton * button, gpointer user_data);
TILP_EXPORT void on_scdbox_button5_clicked(GtkButton * button, gpointer user_data);

#endif
