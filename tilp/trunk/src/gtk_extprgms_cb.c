#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_extprgms_cb.h"
#include "gtk_extprgms_dbox.h"
#include "support.h"

#include "includes.h"

static gchar *tmp_unzip_location;
static gchar *tmp_unzip_options;
static gchar *tmp_tar_location;
static gchar *tmp_tar_options;

GtkWidget *unzip_entry;
GtkWidget *tar_entry;

void
on_extprgms_dbox_show                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  //printf("coucou\n");
}

void
on_extprgms_dbox_show1                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_entry_set_text(GTK_ENTRY(user_data), options.unzip_location);
  unzip_entry = GTK_WIDGET(user_data);
}

void
on_extprgms_dbox_show2                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_entry_set_text(GTK_ENTRY(user_data), options.tar_location);
}

void
on_extprgms_dbox_show3                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_entry_set_text(GTK_ENTRY(user_data), options.unzip_options);
  tar_entry = GTK_WIDGET(user_data);
}

void
on_extprgms_dbox_show4                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_entry_set_text(GTK_ENTRY(user_data), options.tar_options);
}

void
on_entry1_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_unzip_location = gtk_editable_get_chars(GTK_EDITABLE(user_data), 0, -1);
}


void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show(create_fileselection1());
}


void
on_entry3_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_unzip_options = gtk_editable_get_chars(GTK_EDITABLE(user_data), 0, -1);
}


void
on_entry2_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_tar_location = gtk_editable_get_chars(GTK_EDITABLE(user_data), 0, -1);
}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show(create_fileselection1());
}


void
on_entry4_changed                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_tar_options = gtk_editable_get_chars(GTK_EDITABLE(user_data), 0, -1);
}


void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  options.unzip_location = tmp_unzip_location;
  options.unzip_options = tmp_unzip_options;
  options.tar_location = tmp_tar_location;
  options.tar_options = tmp_tar_options;

  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_ok_button1_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *filename;

  filename = gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
 
  gtk_entry_set_text(GTK_ENTRY(unzip_entry), filename);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

void
on_cancel_button1_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

void
on_ok_button2_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *filename;

  filename = gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
 
  gtk_entry_set_text(GTK_ENTRY(unzip_entry), filename);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

void
on_cancel_button2_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

