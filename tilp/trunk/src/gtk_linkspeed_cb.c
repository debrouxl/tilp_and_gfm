#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_linkspeed_cb.h"
#include "gtk_linkspeed_dbox.h"
#include "support.h"

#include "includes.h"

static gint tmp_baudrate;
static gint tmp_hfc;

void
on_linkspeed_dbox_show                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  tmp_baudrate = options.lp.baud_rate;
  switch(options.lp.baud_rate)
    {
    case BR9600:
      gtk_entry_set_text (GTK_ENTRY (user_data), "9600");
      break;
    case BR19200:
      gtk_entry_set_text (GTK_ENTRY (user_data), "19200");
      break;
    case BR38400:
      gtk_entry_set_text (GTK_ENTRY (user_data), "38400");
      break;
    case BR57600:
      gtk_entry_set_text (GTK_ENTRY (user_data), "57600");
      break;
    default:
      gtk_entry_set_text (GTK_ENTRY (user_data), "9600");
      break;
    }
}


void
on_combo_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *ed = "????";

  ed = gtk_editable_get_chars(editable, 0, -1);
  //printf("<%s>\n", ed = gtk_editable_get_chars(editable, 0, -1));
  sscanf(ed, "%i", &tmp_baudrate);
}


void
on_linkspeed_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
  options.lp.baud_rate = tmp_baudrate;
  options.lp.hfc = tmp_hfc;
  ticable_set_baudrate(options.lp.baud_rate);
  ticable_set_hfc(options.lp.hfc);

  gtk_widget_destroy(GTK_WIDGET(user_data));

  if( (tilp_error(link_cable.term_port())) )
    return;
  ticable_set_cable(options.lp.link_type, &link_cable);
  ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);
  //check_access();
  if( (tilp_error(link_cable.init_port())) )
    return;
}


void
on_linkspeed_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

void
on_linkspeed_dbox_show2                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  tmp_hfc = options.lp.hfc;
  if(options.lp.hfc == HFC_ON)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), FALSE);
}

void
on_linkspeed_checkbutton1_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(togglebutton->active == TRUE)
    tmp_hfc = HFC_ON;
  else
    tmp_hfc = HFC_OFF;
}

