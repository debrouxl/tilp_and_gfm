#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_plugins_cb.h"
#include "gtk_plugins_dbox.h"
#include "support.h"

#include "includes.h"

static gint temp;

void
on_plugins_dbox_show                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.plugins_loading == PLUGINS_AUTO)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_plugins_ok_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
  options.plugins_loading = temp;
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_plugins_cancel_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(temp == PLUGINS_AUTO)
    temp = PLUGINS_MANUAL;
  else
    temp = PLUGINS_AUTO; 
}

/* */

void display_entry(gpointer data, gpointer user_data)
{
#ifdef HAVE_TIFFEP
  RegistryEntry *entry = (RegistryEntry *)data;
  GtkCList *clist = GTK_CLIST(user_data);
  gchar *text[1];

  text[0] = g_strconcat("Name: ", entry->name->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strconcat("Description: ", entry->description->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strconcat("Path: ", entry->path->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strconcat("Type: ", entry->type->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strconcat("Calc: ", entry->calc->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strconcat("Var: ", entry->var->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strconcat("Status: ", entry->status->str, NULL);
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
  text[0] = g_strdup("---");
  gtk_clist_append(GTK_CLIST(clist), text);
  g_free(text[0]);
#endif
}

void
on_registry_dbox_show                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gint err;
  gchar *text[1] = { "Registry unavailable." };
  GtkWidget *clist = GTK_WIDGET(user_data);

  err = registry_get_pointer(&plugin_registry);
  if(plugin_registry == NULL)
    {
      gtk_clist_append(GTK_CLIST(clist), text);
      return;
    }
  g_list_foreach(registry, display_entry, clist);
#endif
}


void
on_registry_button1_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_registry_button2_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_registry_clist1_click_column        (GtkCList        *clist,
                                        gint             column,
                                        gpointer         user_data)
{
  
}

/* */
