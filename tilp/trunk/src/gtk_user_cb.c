#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_user_cb.h"
#include "gtk_user_dbox.h"
#include "support.h"

static const gchar *title;
static gchar *message;
static const gchar *button1;
static const gchar *button2;
static const gchar *button3;
static gint ret_val = 0;

/* Dialog box, type 1 */
gint user1_box(const char *titl, char *messag, const char *b1)
{
  GtkWidget *dialog;

  ret_val = 0;
  title = titl;
  message = messag;
  button1 = b1;

  gtk_widget_show_all(dialog = create_user1_dbox());

  while(!ret_val)
    {
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }
  gtk_widget_destroy(dialog);
  
  return ret_val;  
}

/* This a general function used to display a message with 2 buttons */
gint user2_box(const char *titl, char *messag, const char *b1, const char *b2)
{
  GtkWidget *dialog;

  ret_val = 0;
  title = titl;
  message = messag;
  button1 = b1;
  button2 = b2;

  dialog = create_user2_dbox();
  gtk_widget_show_all(dialog);

  while(!ret_val)
    {
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }
  gtk_widget_destroy(dialog);
  
  return ret_val;  
}

/* This a general function used to display a message with 3 buttons */
gint user3_box(const char *titl, char *messag, 
	       const char *b1, const char *b2, const char *b3)
{
  GtkWidget *dialog;

  ret_val = 0;
  title = titl;
  message = messag;
  button1 = b1;
  button2 = b2;
  button3 = b3;

  gtk_widget_show_all(dialog = create_user3_dbox());

  while(!ret_val)
    {
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }
  gtk_widget_destroy(dialog);
  
  return ret_val;  
}

/* Change the title of the box */
void
on_user1_dbox_show1                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_window_set_title (GTK_WINDOW (user_data), title);
}

/* Change the content of the box */
void
on_user1_dbox_show2                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_label_set_text(GTK_LABEL(user_data), message);
}

/* Change the button label of the box */
void
on_user1_dbox_show3                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_label_set_text(GTK_LABEL(user_data), button1);
}

void
on_user1_dbox_show4                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
   gtk_label_set_text(GTK_LABEL(user_data), button2);
}

void
on_user1_dbox_show5                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
   gtk_label_set_text(GTK_LABEL(user_data), button3);
}

/* First button clicked */
void
user1_ok_button_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  ret_val = 1;
  //gtk_widget_destroy(GTK_WIDGET(user_data));
}



void
user2_ok_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  ret_val = 2;
  //gtk_widget_destroy(GTK_WIDGET(user_data));
}

void
user3_ok_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  ret_val = 3;
  //gtk_widget_destroy(GTK_WIDGET(user_data));
}
