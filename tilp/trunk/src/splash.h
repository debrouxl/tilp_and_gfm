#ifndef __SPLASH_H__
#define __SPLASH_H__

#include <gtk/gtk.h>

void splash_screen_set_label(gchar * label);
GtkWidget *splash_screen_start(void);
void splash_screen_stop(void);

#endif
