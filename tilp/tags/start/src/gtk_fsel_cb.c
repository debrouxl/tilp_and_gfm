#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_fsel_cb.h"
#include "gtk_fsel_dbox.h"
#include "support.h"

#include "includes.h"

/* Save a screendump */
void
on_ok_fsel1                            (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];
  gint ret, skip=0;
  gchar buffer[MAXCHARS];
  gchar *dirname;

  strcpy(filename, 
	 gtk_file_selection_get_filename(GTK_FILE_SELECTION (user_data)));

  if(options.confirm == CONFIRM_YES)
    {
      if( access(filename, F_OK) == 0 )
	{
	  sprintf(buffer, _("The file %s already exists.\n\n"),
		  filename);
	  ret=user3_box(_("Warning"), buffer,
			_(" Overwrite "), _(" Rename "),
			_(" Skip "));
	  switch(ret)
	    {
	    case BUTTON2:
	      dirname=dlgbox_entry(_("Rename the file"),
					   _("New name: "), filename);
	      if(dirname == NULL) return;
	      strcpy(filename, dirname);
	      g_free(dirname);
	    case BUTTON1:
	      skip=0;
	      break;
	    case BUTTON3:
	      skip=1;
	      break;
	    default:
	      break;
	    }
	}
    }
  if(skip == 0)
    {
      if(cb_screen_save(filename) != 0)
		  return;
    }

  l_directory_list();
  refresh_clist(main_wnd);
  refresh_info(main_wnd);

  gtk_widget_destroy(user_data);
}


void
on_cancel_fsel1                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Open a backup to send */
void
on_ok_fsel2                            (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];
  
  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  gtk_widget_destroy(user_data);
  
  if(cb_send_backup(filename) != 0)
    return;
}


void
on_cancel_fsel2                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Save the received backup */
void
on_ok_fsel3                            (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar filename[MAXCHARS];
  gchar tmp_filename[MAXCHARS];
  gint ret, skip=0;
  gchar buffer[MAXCHARS];
  gchar *dirname;

  strcpy(filename, 
	 gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, "/tilp.backup");

  if(options.confirm == CONFIRM_YES)
    {
      if( access(filename, F_OK) == 0 )
	{
	  sprintf(buffer, _("The file %s already exists.\n\n"),
		  filename);
	  ret=user3_box(_("Warning"), buffer,
			_(" Overwrite "), _(" Rename "),
			_(" Skip "));
	  switch(ret)
	    {
	    case BUTTON2:
	      dirname=dlgbox_entry(_("Rename the file"),
				   _("New name: "), filename);
	      if(dirname == NULL) return;
	      strcpy(filename, dirname);
	      g_free(dirname);
	    case BUTTON1:
	      skip=0;
	      break;
	    case BUTTON3:
	      skip=1;
	      break;
	    default:
	      break;
	    }
	}
    }
  if(skip == 0)
    {
      if(move_file(tmp_filename, filename))
	{
	  msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
	}
    }
  l_directory_list();
  refresh_clist(main_wnd);
  refresh_info(main_wnd);  

  gtk_widget_destroy(user_data);
}


void
on_cancel_fsel3                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar tmp_filename[MAXCHARS];

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, "/tilp.backup");
  if(unlink(tmp_filename))
    {
      fprintf(stdout, _("Unable to remove the temporary file.\n"));
    }

  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Save received var(s) */
void
on_ok_fsel4                            (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar filename[MAXCHARS];
  gchar tmp_filename[MAXCHARS];
  gint ret, skip=0;
  gchar buffer[MAXCHARS];
  gchar *dirname;

  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  //fprintf(stderr, "%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, "/tilp.PAK");

  if(options.confirm == CONFIRM_YES)
    {
      if( access(filename, F_OK) == 0 )
	{
	  sprintf(buffer, _("The file %s already exists.\n\n"),
		  filename);
	  ret=user3_box(_("Warning"), buffer,
			_(" Overwrite "), _(" Rename "),
			_(" Skip "));

	  switch(ret)
	    {
	    case BUTTON2:
	      dirname=dlgbox_entry(_("Rename the file"),
				   _("New name: "), filename);
	      if(dirname == NULL) return;
	      strcpy(filename, dirname);
	      g_free(dirname);
	    case BUTTON1:
	      skip=0;
	      break;
	    case BUTTON3:
	      skip=1;
	      break;
	    default:
	      break;
	    }
	}
    }

  if(skip == 0)
    {
      if(move_file(tmp_filename, filename))
	{
	  fprintf(stderr, _("Unable to rename the temporary file.\n"));
	}
    }
  gtk_widget_destroy(user_data);
  l_directory_list();
  refresh_clist(main_wnd);
  refresh_info(main_wnd);
}


void
on_cancel_fsel4                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar tmp_filename[MAXCHARS];

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, "/tilp.PAK");
  if(unlink(tmp_filename))
    {
      fprintf(stderr, _("Unable to remove the temporary file.\n"));
    }

  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Open a PAK file to explode */
void
on_ok_fsel5                            (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];

  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  gtk_widget_destroy(user_data);
  //while(g_main_iteration(FALSE));
  explode_pak_file(filename);

  l_directory_list();
  refresh_clist(main_wnd);
  refresh_info(main_wnd);
}


void
on_cancel_fsel5                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_ok_fsel6                            (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];
  char buffer[MAXCHARS];
  
  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  printf("<%s>\n", filename);
  printf("Error: %i\n", ti82_gtl_to_tigl(filename, buffer));
  
  gtk_widget_destroy(user_data);
}


void
on_cancel_fsel6                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Save the received ROM dump */
void
on_ok_fsel7                            (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar filename[MAXCHARS];
  gchar tmp_filename[MAXCHARS];
  gint ret, skip=0;
  gchar buffer[MAXCHARS];
  gchar *dirname;

  strcpy(filename, 
	 gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, "/tilp.ROMdump");

  if(options.confirm == CONFIRM_YES)
    {
      if( access(filename, F_OK) == 0 )
	{
	  sprintf(buffer, _("The file %s already exists.\n\n"),
		  filename);
	  ret=user3_box(_("Warning"), buffer,
			_(" Overwrite "), _(" Rename "),
			_(" Skip "));
	  switch(ret)
	    {
	    case BUTTON2:
	      dirname=dlgbox_entry(_("Rename the file"),
				   _("New name: "), filename);
	      if(dirname == NULL) return;
	      strcpy(filename, dirname);
	      g_free(dirname);
	    case BUTTON1:
	      skip=0;
	      break;
	    case BUTTON3:
	      skip=1;
	      break;
	    default:
	      break;
	    }
	}
    }
  if(skip == 0)
    {
      if(move_file(tmp_filename, filename))
	{
	  msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
	}
    }
  l_directory_list();
  refresh_clist(main_wnd);
  refresh_info(main_wnd);  

  gtk_widget_destroy(user_data);
}


void
on_cancel_fsel7                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar tmp_filename[MAXCHARS];

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, "/tilp.ROMdump");
  if(unlink(tmp_filename))
    {
      fprintf(stdout, _("Unable to remove the temporary file.\n"));
    }

  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Open a FLASH app to send */
void
on_ok_fsel8                            (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];
  
  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  gtk_widget_destroy(user_data);
  
  if(cb_send_flash_app(filename) != 0)
    return;
}


void
on_cancel_fsel8                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Open a FLASH OS (AMS) to send */
void
on_ok_fsel9                            (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];

  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  gtk_widget_destroy(GTK_WIDGET(user_data));

  if(cb_send_flash_os(filename) != 0)
    return;
}


void
on_cancel_fsel9                        (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_fileselection_1_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  
}


void
on_fileselection_2_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  strcpy(buffer, "*.");
  strcat(buffer, ti_calc.backup_file_ext(options.lp.calc_type));
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_fileselection_3_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];
  
  strcpy(buffer, "backup.");
  strcat(buffer, ti_calc.backup_file_ext(options.lp.calc_type));
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_fileselection_4_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  strcpy(buffer, "group.");
  strcat(buffer, ti_calc.group_file_ext(options.lp.calc_type));
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_fileselection_5_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(user_data), "*.PAK");
}


void
on_fileselection_6_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), "test.PAK");
}


void
on_fileselection_7_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  strcpy(buffer, "romdump");
  strcat(buffer, ".rom");
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_fileselection_8_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  strcpy(buffer, "*.");
  strcat(buffer, ti_calc.flash_app_file_ext(options.lp.calc_type));
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_fileselection_9_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  strcpy(buffer, "*.");
  strcat(buffer, ti_calc.flash_os_file_ext(options.lp.calc_type));
  strcat(buffer, ";*.tib");
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_fileselection_10_show               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  strcpy(buffer, "*.");
  strcat(buffer, ti_calc.flash_os_file_ext(options.lp.calc_type));
  strcat(buffer, ";*.tib");
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(widget), buffer);
}


void
on_ok_fsel10                           (GtkButton       *button,
                                        gpointer         user_data)
{
  char filename[MAXCHARS];
  
  strcpy(filename, gtk_file_selection_get_filename (GTK_FILE_SELECTION (user_data)));
  gtk_widget_destroy(user_data);
  
  if(cb_ams_to_rom(filename) != 0)
    return;
}


void
on_cancel_fsel10                       (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

