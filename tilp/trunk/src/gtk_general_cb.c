#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_general_cb.h"
#include "gtk_general_dbox.h"
#include "support.h"

#include "includes.h"

static struct goptions tmp_options;

void
on_general_dbox_show                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  memcpy(&tmp_options, &options, sizeof(options));
}


void
on_general_dbox_show2                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(user_data), options.xsize);
}


void
on_general_dbox_show3                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(user_data), options.ysize);
}


void
on_general_dbox_show4                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.transfer_mode == SILENT_MODE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show5                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.transfer_mode == MANUAL_MODE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show6                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.path_mode == FULL_PATH)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show7                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.path_mode == LOCAL_PATH)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show8                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.ctree_sort == SORT_BY_NAME)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show9                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.ctree_sort == SORT_BY_TYPE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show10                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.ctree_sort == SORT_BY_INFO)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show11                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.ctree_sort == SORT_BY_SIZE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show12                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.ctree_sort_order == SORT_UP)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show13                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.ctree_sort_order == SORT_DOWN)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show14                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.show == SHOW)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show15                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.show == HIDE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show16                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.file_mode == EXTENDED_FORMAT)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(user_data), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(user_data), FALSE);
}


void
on_general_dbox_show17                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.confirm == CONFIRM_YES)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(user_data), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(user_data), FALSE);
}


void
on_general_dbox_show18                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort == SORT_BY_NAME)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show19                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort == SORT_BY_SIZE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show20                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort == SORT_BY_GROUP)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show21                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort == SORT_BY_DATE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show22                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort == SORT_BY_ATTRB)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show23                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort == SORT_BY_USER)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show24                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort_order == SORT_UP)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_dbox_show25                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(options.clist_sort_order == SORT_DOWN)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_general_spinbutton1_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_options.xsize = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


void
on_spinbutton2_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_options.ysize = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


void
on_radiobutton11_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.transfer_mode = SILENT_MODE;
}


void
on_radiobutton12_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.transfer_mode = MANUAL_MODE;
}


void
on_general_radiobutton21_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.path_mode = FULL_PATH;
}


void
on_general_radiobutton22_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.path_mode = LOCAL_PATH;
}


void
on_radiobutton31_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.ctree_sort = SORT_BY_NAME;
}


void
on_radiobutton32_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.ctree_sort = SORT_BY_TYPE;
}


void
on_radiobutton33_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.ctree_sort = SORT_BY_INFO;
}


void
on_radiobutton34_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.ctree_sort = SORT_BY_SIZE;
}


void
on_radiobutton41_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.ctree_sort_order = SORT_UP;
}


void
on_radiobutton42_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.ctree_sort_order = SORT_DOWN;
}


void
on_radiobutton51_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.show = SHOW;
}


void
on_radiobutton52_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.show = HIDE;
}


void
on_general_checkbutton1_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(togglebutton->active == TRUE)
    tmp_options.file_mode = EXTENDED_FORMAT;
  else
    tmp_options.file_mode = NORMAL_FORMAT;
}


void
on_general_checkbutton2_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(togglebutton->active == TRUE)
    tmp_options.confirm = CONFIRM_YES;
  else
    tmp_options.confirm = CONFIRM_NO;
}


void
on_radiobutton61_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort = SORT_BY_NAME;
}


void
on_radiobutton62_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort = SORT_BY_SIZE;
}


void
on_radiobutton63_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort = SORT_BY_GROUP;
}


void
on_radiobutton66_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort = SORT_BY_DATE;
}


void
on_radiobutton65_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort = SORT_BY_ATTRB;
}


void
on_radiobutton64_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort = SORT_BY_USER;
}


void
on_radiobutton71_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort_order = SORT_UP;
}


void
on_radiobutton72_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  tmp_options.clist_sort_order = SORT_DOWN;
}


void
on_general_ok_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
  memcpy(&options, &tmp_options, sizeof(tmp_options));
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_general_cancel_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_general_dbox_show26                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  switch(tmp_options.file_checking)
    {
    case FILE_CHECKING_OFF:
      gtk_entry_set_text (GTK_ENTRY (user_data), _("none"));
      break;
    case FILE_CHECKING_MID:
      gtk_entry_set_text (GTK_ENTRY (user_data), _("middle"));
      break;
    case FILE_CHECKING_ON:
      gtk_entry_set_text (GTK_ENTRY (user_data), _("restrictive"));
      break;
    default:
      gtk_entry_set_text (GTK_ENTRY (user_data), _("restrictive"));
      break;
    }
}


void
on_general_combo_entry1_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *ed;

  ed = gtk_editable_get_chars(editable, 0, -1);
  //printf("<%s>\n", ed = gtk_editable_get_chars(editable, 0, -1));
  
  if(!strcmp(ed, _("none")))
    tmp_options.file_checking = FILE_CHECKING_OFF;
  else if(!strcmp(ed, _("middle")))
    tmp_options.file_checking  = FILE_CHECKING_MID;
  else if(!strcmp(ed, _("restrictive")))
    tmp_options.file_checking = FILE_CHECKING_ON;
  else
    tmp_options.file_checking = FILE_CHECKING_ON;
}

