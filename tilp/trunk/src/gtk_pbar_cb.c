#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_pbar_cb.h"
#include "gtk_pbar_dbox.h"
#include "support.h"

#include "includes.h"

/* 
   For Win32 platforms, it is better to use discrete pbar 
   because they are faster 
*/
#ifdef __WIN32__
//#define PROGRESS_TYPE GTK_PROGRESS_DISCRETE
#define PROGRESS_TYPE GTK_PROGRESS_CONTINUOUS
#else
#define PROGRESS_TYPE GTK_PROGRESS_CONTINUOUS
#endif

/*******************/
/* Local variables */
/*******************/

static GtkWidget *pbar_window;
static const gchar *i_title;
static gchar *i_text;

/**************************/
/* General pbar functions */
/**************************/

/* Create a window with one progress bar */
void create_pbar_type1(const gchar *title)
{
  i_title = title;
  is_active = LOCK;
  info_update.prev_percentage = 0.0;
  info_update.percentage = 0.0;
  info_update.cancel = 0;

  pbar_window = create_pbar1_dbox();
  gtk_widget_show_all(pbar_window);
}

/* Create a window with one label */
void create_pbar_type2(const gchar *title, gchar *text)
{
  i_title = title;
  i_text = text;
  is_active = LOCK;
  info_update.prev_percentage = 0.0;
  info_update.percentage = 0.0;
  info_update.cancel = 0;

  pbar_window = create_pbar2_dbox();
  gtk_widget_show_all(pbar_window);
}

/* Create a window with two progress bars */
void create_pbar_type3(const gchar *title)
{
  i_title = title;
  is_active = LOCK;
  info_update.prev_main_percentage = 0.0;
  info_update.main_percentage = 0.0;
  info_update.prev_percentage = 0.0;
  info_update.percentage = 0.0;
  info_update.cancel = 0;

  pbar_window = create_pbar3_dbox();
  gtk_widget_show_all(pbar_window);
}

/* Create a window with a one progress bar and one label */
void create_pbar_type4(const gchar *title, gchar *text)
{
  i_title = title;
  i_text = text;
  is_active = LOCK;
  info_update.percentage=0.0;
  info_update.cancel=0;

  pbar_window = create_pbar4_dbox();
  gtk_widget_show_all(pbar_window);
}

/* Create a window with two progress bars and one label */
void create_pbar_type5(const gchar *title, gchar *text)
{
  i_title = title;
  i_text = text;
  is_active = LOCK;
  info_update.prev_main_percentage = 0.0;
  info_update.main_percentage = 0.0;
  info_update.prev_percentage = 0.0;
  info_update.percentage = 0.0;
  info_update.cancel = 0;

  pbar_window = create_pbar5_dbox();
  gtk_widget_show_all(pbar_window);
}

/* 
   Destroy a pbar window
*/
void destroy_pbar(void)
{
  p_win.pbar=NULL;
  p_win.pbar2=NULL;
  p_win.label=NULL;

  i_title = NULL;
  i_text = NULL;

  gtk_widget_destroy(pbar_window);
  is_active = UNLOCK;
}

/*************/
/* Callbacks */
/*************/


void
pbar1_ok_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  info_update.cancel = 1;

  return;
}


void
on_pbar1_dbox_show1                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_window_set_title(GTK_WINDOW(user_data), i_title);
}


void
on_pbar_dbox_show_pbar1                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  p_win.pbar = GTK_WIDGET(user_data);
  gtk_progress_bar_set_bar_style (GTK_PROGRESS_BAR (p_win.pbar),
				  PROGRESS_TYPE);
}


void
on_pbar_dbox_show_pbar2                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  p_win.pbar2 = GTK_WIDGET(user_data);
  gtk_progress_bar_set_bar_style (GTK_PROGRESS_BAR (p_win.pbar2),
				  PROGRESS_TYPE);
}


void
on_pbar_dbox_show_label1               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  p_win.label = GTK_WIDGET(user_data);
  gtk_label_set(GTK_LABEL(user_data), i_text);
}


void
on_pbar_dbox_show_rate                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  p_win.label_rate = GTK_WIDGET(user_data);
  //gtk_label_set(GTK_LABEL(user_data), "Rate: 0.0 Kb/s");
}

/* */

