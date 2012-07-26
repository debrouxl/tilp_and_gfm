#include <gtk/gtk.h>

gint display_screenshot_dbox();

void on_scdbox_button1_clicked(GtkButton * button,
					gpointer user_data);

void on_sc_save1_activate(GtkMenuItem * menuitem,
				   gpointer user_data);

void on_sc_quit1_activate(GtkMenuItem * menuitem,
				   gpointer user_data);
