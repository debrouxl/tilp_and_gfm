#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "gtk_font_cb.h"
#include "gtk_font_dbox.h"
#include "support.h"

#include "includes.h"

void
on_font_dbox_show                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  //fprintf(stdout, "show: <%s>\n", options.right_font_name);
  gtk_font_selection_dialog_set_font_name(GTK_FONT_SELECTION_DIALOG(user_data),
					  options.right_font_name);
}


void
on_font_ok_button1_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  strcpy(options.right_font_name, gtk_font_selection_dialog_get_font_name(GTK_FONT_SELECTION_DIALOG(user_data)));
  //fprintf(stdout, "ok: <%s>\n", options.right_font_name);

  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_font_cancel_button1_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_font_apply_button1_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  //gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* */
