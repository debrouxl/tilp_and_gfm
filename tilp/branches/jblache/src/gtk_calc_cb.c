#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_calc_cb.h"
#include "gtk_calc_dbox.h"
#include "support.h"

#include "includes.h"

static gint calc_type;
static gint ad;

void
on_calctype_dbox_show1                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI92P)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show2                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI92)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show3                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI89)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show4                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI86)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show5                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI85)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show6                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI83P)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show7                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI83)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show8                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI82)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_calctype_dbox_show9                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  calc_type = options.lp.calc_type; 
  if(calc_type == CALC_TI73)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI92P;
}


void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI89;
}


void
on_radiobutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI83P;
}


void
on_radiobutton9_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI73;
}


void
on_radiobutton8_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI82;
}


void
on_radiobutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI85;
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI92;
}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI86;
}


void
on_radiobutton7_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  calc_type = CALC_TI83;
}


void
on_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
  options.lp.calc_type = calc_type;
  options.auto_detect = ad;
  ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);
  gtk_widget_destroy(GTK_WIDGET(user_data));
  refresh_sensitive_toolbar_buttons();
}


void
on_cancel_button_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_calctype_dbox_show10                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  ad = options.auto_detect;
  if(ad == TRUE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), FALSE);
}


void
calctype_on_checkbutton1_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(togglebutton->active == TRUE)
    ad = TRUE;
  else
    ad = FALSE;
}

/* */
