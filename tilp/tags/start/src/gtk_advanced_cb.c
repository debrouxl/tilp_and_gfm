#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_advanced_cb.h"
#include "gtk_advanced_dbox.h"
#include "support.h"

#include "includes.h"

static gint tmp_timeout;
static gint tmp_delay;

void
on_timeout_dbox_show                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  tmp_timeout = options.lp.timeout;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(user_data), options.lp.timeout);
}


void
on_delay_dbox_show                     (GtkWidget       *widget,
                                        gpointer         user_data)
{
  tmp_delay = options.lp.delay;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(user_data), options.lp.delay);
}


void
on_timeout_spinbutton1_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_timeout = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (user_data));
}


void
on_delay_spinbutton2_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_delay = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (user_data));
}

void
on_timeout_ok_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
  options.lp.timeout = tmp_timeout;
  options.lp.delay = tmp_delay;

  ticable_set_delay(options.lp.delay);
  ticable_set_timeout(options.lp.timeout);

  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_timeout_cancel_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/**/
