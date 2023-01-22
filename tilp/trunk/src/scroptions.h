#ifndef __SCROPTIONS_H__
#define __SCROPTIONS_H__

#include "tilp_defs.h"
#include <gtk/gtk.h>

gint display_scroptions_dbox(void);

TILP_EXPORT void on_radiobutton10_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton11_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton12_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton13_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton14_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton15_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton21_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_radiobutton22_toggled(GtkToggleButton * togglebutton, gpointer user_data);
TILP_EXPORT void on_scopt_checkbutton1_toggled(GtkToggleButton * togglebutton, gpointer user_data);

#endif
