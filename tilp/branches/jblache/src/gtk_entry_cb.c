#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "gtk_entry_cb.h"
#include "gtk_entry_dbox.h"
#include "support.h"

#include "includes.h"

static const gchar* s_title = NULL;
static const gchar* s_message = NULL;
static const gchar* s_content = NULL;
static gint ret_val = 0;
static GtkWidget *entry = NULL;

/* Create the dialog box entry and wait */
gchar *dlgbox_entry(const char *title, 
		    const char *message, 
		    const char *content)
{
  gchar *ret = NULL;
  gchar *s = NULL;
  GtkWidget *dialog = NULL;

  ret_val = 0;
  s_title = title;
  s_message = message;
  s_content = content;

  dialog = create_entry_dbox();
  gtk_widget_show_all(dialog);

  while(!ret_val)
    {
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }

  switch(ret_val)
    {
    case 1:
      s = gtk_editable_get_chars(GTK_EDITABLE(entry), 0, -1);
      ret=(gchar *)g_malloc((strlen(s)+1)*sizeof(gchar));
      strcpy(ret, s);
      break;
    case 2:
      ret=NULL;
      break;
    default:
      ret=NULL;
      break;
    }
  g_free(s);
  gtk_widget_destroy(dialog);
  
  return ret;  
}

void
on_entry_dbox_show1                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_window_set_title(GTK_WINDOW(user_data), s_title);
}


void
entry_ok_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  ret_val = 1;
}


void
entry_cancel_button_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
  ret_val = 2;
}

void
on_entry_dbox_show2                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_frame_set_label(GTK_FRAME(user_data), s_message);
}


void
on_entry_dbox_show3                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
  entry = GTK_WIDGET(user_data);
  gtk_entry_set_text(GTK_ENTRY(user_data), s_content);
}

/* */
