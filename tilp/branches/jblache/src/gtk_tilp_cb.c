#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "gtk_tilp_cb.h"
#include "gtk_tilp_dbox.h"
#include "support.h"

#include "includes.h"
#include "version.h"

void
on_tilp_dbox_show                      (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_tilp_dbox_destroy                   (GtkObject       *object,
                                        gpointer         user_data)
{
  int err;

  if( (err=link_cable.term_port()) )
    {
      fprintf(stderr, "link_cable.term_port: error code %i\n", err);
      tilp_error(err);
    }
  gtk_widget_destroy(GTK_WIDGET(user_data));
  gtk_main_quit();
}


void
on_tilp_dbox_show_clist1               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clist_wnd = GTK_WIDGET(user_data);

  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 0, 16);  //
  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 1, 120); //filename
  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 2, 90);  //date
  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 3, 65);  //size
  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 4, 60);  //user
  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 5, 60);  //group
  gtk_clist_set_column_width(GTK_CLIST (clist_wnd), 6, 70);  //attributes

}


void
on_tilp_dbox_show_ctree1               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  ctree_wnd = GTK_WIDGET(user_data);

  gtk_clist_set_column_width(GTK_CLIST (ctree_wnd), 0, 135); //varname
  gtk_clist_set_column_width(GTK_CLIST (ctree_wnd), 1, 25);  //attributes
  gtk_clist_set_column_width(GTK_CLIST (ctree_wnd), 2, 50);  //type
  gtk_clist_set_column_width(GTK_CLIST (ctree_wnd), 3, 30);  //size
  //gtk_ctree_set_indent (GTK_CTREE (ctree_wnd), 17);
  gtk_clist_set_row_height(GTK_CLIST (ctree_wnd), 16);
}


void
on_tilp_dbox_show_label12              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label11 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label13              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label12 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label14              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label13 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label15              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label14 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label16              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label21 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label17              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label22 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label18              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label23 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_label19              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  clabel_win.label24 = GTK_WIDGET(user_data);
}


/* Ready button showed */
void
on_tilp_dbox_show_button4              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button1 = GTK_WIDGET(user_data);
}

/* Screen button showed */
void
on_tilp_dbox_show_button5              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button3 = GTK_WIDGET(user_data);
}

/* Dirlist button showed */
void
on_tilp_dbox_show_button6              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button4 = GTK_WIDGET(user_data);
}

/* Backup button showed */
void
on_tilp_dbox_show_button7              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button5 = GTK_WIDGET(user_data);
}

/* Restore button showed */
void
on_tilp_dbox_show_button8              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button6 = GTK_WIDGET(user_data);
}

/* Send/receive button showed */
void
on_tilp_dbox_show_button9              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button7 = GTK_WIDGET(user_data);
}

/* MkDir button showed */
void
on_tilp_dbox_show_button10             (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button8 = GTK_WIDGET(user_data);
}

/* Trash button showed */
void
on_tilp_dbox_show_button11             (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button9 = GTK_WIDGET(user_data);
}

/* Refresh button showed */
void
on_tilp_dbox_show_button12             (GtkWidget       *widget,
                                        gpointer         user_data)
{
  toolbar_win.button10 = GTK_WIDGET(user_data);
}


void
on_tilp_dbox_show_frame2               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  /*
  gtk_widget_set_usize(GTK_WIDGET(user_data), 
		       options.ysize, options.xsize);
  */
}


void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"), 
  _("This function is not yet available."));
}


void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"), 
  _("This function is not yet available."));
}


void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"), 
  _("This function is not yet available."));
}


void
on_convert_old_files1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GList *ptr;
  struct file_info *f=NULL;
  char buffer[256];

  msg_box(_("Information"), 
	  _("The 'TI file format & plugin proxy kit' is going to be developped..."));
  return;
  
  if(clist_win.selection==NULL) 
    {
      msg_box(_("Information"), 
	  _("A file must have been selected."));
      return;
    }

  ptr=clist_win.selection;
  while(ptr!=NULL)
    {
      f=(struct file_info *)ptr->data;
      printf("<%s>\n", f->filename);
      switch(options.lp.calc_type)
	{
	case CALC_TI82:
	  tilp_error(ti82_gtl_to_tigl(f->filename, buffer));
	  break;
	case CALC_TI83:
	  tilp_error(ti83_gtl_to_tigl(f->filename, buffer));
	case CALC_TI85:
	  msg_box(_("Information"), 
		  _("This function is not yet available."));
	  //error(ti85_gtl_to_tigl(f->filename, buffer));
	  break;
	case CALC_TI86:
	  msg_box(_("Information"), 
		  _("This function is not yet available."));
	  //error(ti86_gtl_to_tigl(f->filename, buffer));
	default:
		break;
	}
      
      ptr=ptr->next;
    }
  /*
    gtk_widget_show(create_fileselection_6());
  */
  
  return;
}


void
on_unzip_archive1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gchar *cmdline;
  gchar *s;
  gchar buffer[MAXCHARS];
  FILE *p;
  GList *ptr;
  struct file_info *f;
  int ret;

  if(clist_win.selection==NULL)
    {
      msg_box(_("Information"), 
	      _("A file must have been selected."));
      return;
    }
  
  /* 
     Detect whether the prog is available else error !
  */
  p = popen(options.unzip_location, "r");
  if(p == NULL)
    {
      msg_box(_("Error"), 
	      _("It seems that the 'unzip' program is unavailable.\nWindows users: you must have the 'WinZip Command Line Support Add-On' (233 Kb) for this. If not, \nyou can download it at www.winzip.com."));
      return;
    }
  pclose(p);
  
  ptr=clist_win.selection;
  while(ptr!=NULL)
    {
      f=(struct file_info *)ptr->data;
      printf("File to unzip: <%s>\n", f->filename);
      
      /* Unzip the file archive */
      cmdline = (gchar *)g_malloc((strlen(options.unzip_location) +
				   strlen(options.unzip_options) + 1 + MAXCHARS) *
				  sizeof(gchar));
      strcpy(cmdline, options.unzip_location);
      strcat(cmdline, " ");
      if(!strcmp(options.unzip_options, ""))
#if defined(__UNIX__)
	{ // default options
	  strcat(cmdline, "-o "); // overwrite
	  strcat(cmdline, "-d "); // unzip in a sub directory
	  sprintf(buffer, "%s", f->filename);
	  s = (gchar *)strrchr(buffer, '.');
	  if(s != NULL)
	    buffer[strlen(buffer) - strlen(s)] = '\0';
	  strcat(cmdline, buffer);
	}
#elif defined(__WIN32__)
      { // default options
	strcat(cmdline, "-o "); // overwrite
	strcat(cmdline, "-d "); // unzip in a sub directory
	/*
	  sprintf(buffer, "%s", f->filename);
	  printf("-> <%s>\n", buffer);
	  s = strrchr(buffer, '.');
	  if(s != NULL)
	  buffer[strlen(buffer) - strlen(s)] = '\0';
	*/
	strcat(cmdline, buffer);
      }
#endif
      else
	{ // user options
	  strcat(cmdline, options.unzip_options);
	}
      strcat(cmdline, " ");
      sprintf(buffer, "%s", f->filename);
      strcat(cmdline, buffer);
      
      fprintf(stdout, "Unzip cmdline: <%s>\n", cmdline);
#ifdef __WIN32__ // is being to change...
      p = popen(cmdline,"r");
      if(p == NULL)
	{
	  msg_box(_("Error"), 
		  _("Unable to unzip the file."));
	  return;
	}
      
      while( (n = fread(buffer, sizeof(gchar), 255, p)) > 0 )
	{  
	  buffer[n-1] ='\0';
	  printf("%s", buffer);
	}
      ret = pclose(p);
#elif defined(__LINUX__)
      ret = execute_command(cmdline);
#endif
      if(ret == -1)
	{
	  msg_box(_("Error"), 
		  _("There was some errors with unzip."));
	  return;
	}
      DISPLAY(_("\ntilp -> Unzip command finished.\n"));
      
      ptr=ptr->next;
    }
  
  //refresh_clist(main_window);

  return;
}


void
on_untar_archive1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gchar *cmdline;
  //gchar *s;
  //gchar buffer[MAXCHARS];
  //gint n;
  FILE *p;
  GList *ptr;
  struct file_info *f;
  int ret;

  if(clist_win.selection==NULL)
    {
      msg_box(_("Information"), 
	      _("A file must have been selected."));
      return;
    }
  
  /* 
     Detecter si un prg est dispo, sinon err_box
  */
  p = popen(options.tar_location, "r");
  if(p == NULL)
    {
      msg_box(_("Error"), 
	      _("It seems that the 'unzip' program is unavailable.\nWindows users: you must have the 'WinZip Command Line Support Add-On' (233 Kb) for this. Else, \nyou can download it at www.wintar.com."));
      return;
    }
  pclose(p);
  
  ptr=clist_win.selection;
  while(ptr!=NULL)
    {
      f=(struct file_info *)ptr->data;
      printf("File to untar: <%s>\n", f->filename);
      
      /* Untar the file archive */
      cmdline = (gchar *)g_malloc((strlen(options.tar_location) +
				   strlen(options.tar_options) + 
				   1 + MAXCHARS) * sizeof(gchar));
      strcpy(cmdline, options.tar_location);
      strcat(cmdline, " ");
      if(!strcmp(options.tar_options, ""))
#if defined(__UNIX__)
	{ // default options
	  strcat(cmdline, "x"); // extract
	  strcat(cmdline, "v"); // verbose
	  strcat(cmdline, "z"); // gzipped
	  strcat(cmdline, "f"); // force = overwrite
 	  strcat(cmdline, " ");
	  strcat(cmdline, f->filename);
	}
#elif defined(__WIN32__) //??
      { // default options
	strcat(cmdline, "-o "); // overwrite
	strcat(cmdline, "-d "); // untar in a sub directory
	strcat(cmdline, buffer);
      }
#endif
      else
	{ /* user's options */
	  strcat(cmdline, options.tar_options);
	  strcat(cmdline, " ");
	  strcat(cmdline, f->filename);
	}
      fprintf(stdout, "Untar cmdline: <%s>\n", cmdline);
#ifdef __WIN32__ // is being to change...
      p = popen(cmdline,"r");
      if(p == NULL)
	{
	  msg_box(_("Error"), 
		  _("Unable to untar the file."));
	  return;
	}
      
      while( (n = fread(buffer, sizeof(gchar), 255, p)) > 0 )
	{  
	  buffer[n-1] ='\0';
	  printf("%s", buffer);
	}
      ret = pclose(p);
#elif defined(__LINUX__)
      ret = execute_command(cmdline);
#endif
      if(ret == -1)
	{
	  msg_box(_("Error"), 
		  _("There was some errors with untar."));
	  return;
	}
      DISPLAY(_("\ntilp -> Untar command finished.\n"));
      
      ptr=ptr->next;
    }
  //refresh_clist(main_window);
 
  return;
}

void
on_unpack__obsolete_1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_fileselection_5());
}


void
on_save_config1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cb_save_config_file();
}


void
on_reload_config1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cb_load_config_file();
}


void
on_default_config1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cb_default_config();
}


void
on_quit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int err;

  if( (err=link_cable.term_port()) )
    {
      fprintf(stderr, "link_cable.term_port: error code %i\n", err);
      tilp_error(err);
    }
  gtk_widget_destroy(GTK_WIDGET(user_data));
  gtk_main_quit();
}


void
on_general1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show(create_general_dbox());
  //dlgbox_setup_general(main_window, user_data); // to do with Glade !
}


void
on_screen_capture1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_scopt_dbox());
}


void
on_font_type1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
   gtk_widget_show_all(create_font_dbox());
}


void
on_hardware1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show(create_linktype_dbox());
}


void
on_calculator1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show(create_calctype_dbox());
}


void
on_delay1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  //gtk_widget_show_all(create_delay_dbox());
}


void
on_timeout1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  //gtk_widget_show_all(create_timeout_dbox());
}


void
on_link_speed1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_linkspeed_dbox());
}


void
on_probe_i_o_ports1_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  //cb_probe_port();
  gtk_widget_show_all(create_probeio_dbox());
}


void
on_probe_link_cable1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gchar *os;
  PortInfo pi;

  ticable_detect_os(&os);
  ticable_detect_port(&pi);
  ticable_detect_cable(&pi);
  //cb_probe_cable();
}


void
on_probe_calc_type1_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cb_probe_calc();
}


void
on_ready____1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(cb_calc_is_ready() != 0)
    return;
}


void
on_terminal___remote1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(is_active)
    return;
  gtk_widget_show(create_term_dbox());
  //terminal_window();
}


void
on_screenshot1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(is_active) return;
  gtk_widget_show_all(create_screendump_dbox());
}


void
on_directory_list1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(cb_dirlist() != 0)
    return;
  
  refresh_ctree(main_window);
  refresh_info(main_window);
}


void
on_send_backup1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int ret;

  if(is_active) return; 

  /* Information box */
  ret = user2_box(_("Warning"), 
		  _("You are going to restore the calculator content with your backup. The whole memory will be erased. Are you sure you want to do that ?"),
		  _("Next >"), 
		  _("Cancel"));
  if(ret != BUTTON1)
    return;

  gtk_widget_show(create_fileselection_2());
}


void
on_receive_backup1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(cb_receive_backup() != 0)
	  return;

  gtk_widget_show(create_fileselection_3());
}


void
on_send_variable1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(cb_send_var() != 0)
	  return;

  clist_selection_destroy(); // GUI independant
  clist_selection_refresh(); // GUI dependant
}


void
on_receive_variable1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int to_save;

  if(cb_receive_var(&to_save) != 0)
	  return;
  
  if(to_save)
    {
      switch(options.lp.calc_type)
	{
	case CALC_TI83:
	case CALC_TI83P:
	case CALC_TI86:
	case CALC_TI89:
	case CALC_TI92:
	case CALC_TI92P:
	  gtk_widget_show(create_fileselection_4());
	  break;
	case CALC_TI82:
	case CALC_TI85:
	  /*
	  if(varname[0] != '\0')
	    break;
	  */
	  gtk_widget_show(create_fileselection_4());
	  break;
	}
    }
  
  ctree_selection_destroy();
  ctree_selection_refresh();
  l_directory_list();
  refresh_clist(main_window);
  refresh_info(main_window);
}


void
on_send__free__application1_activate   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  char *msg = _("You are going to send a FLASH application on your calculator.\nHe is strongly recommended for Windows users to close any application and eventually turn off your screen saver (this makes the transfer rate decrease !). Tests have been made on a PC350 Mhz and all link cables without any problems.");
  gint ret;
  
  if(is_active) 
    return;  

  ret=user2_box(_("Warning"), msg,
		_("Continue"), _("Cancel"));
  if(ret == BUTTON2)
    return;
  
  gtk_widget_show(create_fileselection_8());
}


void
on_send_operating_system1_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  char *msg =_("You are going to FLASH the Operating System of your calculator.\nHe is strongly recommended for Windows users to close any application and to turn off your screen saver (this makes the transfer rate decrease !). Tests have been made on a PC350 Mhz and all link cables without any problems. If the transfer crashes, wait until the TI92+ displays 'Waiting to receive' and try the transfer again.");
  gint ret;

  if(is_active) 
    return;  
  
  ret=user2_box(_("Warning"), msg,
		_("Continue"), _("Cancel"));
  if(ret == BUTTON2)
    return;
  
  gtk_widget_show(create_fileselection_9());
}


void
on_get_idlist1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(cb_id_list() != 0)
    return;
}


void
on_receive__free__application1_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"),
	  _("This function is not yet available."));
}


void
on_rom_dump1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gint ret;
  FILE *dump;
  int err=0;
  gchar tmp_filename[MAXCHARS];

  if(is_active) return;

  /* Information box */
  ret = user2_box(_("Warning"), 
		  _("An assembly program is going to be sent on your calculator. You should do a backup before that..."),
		  _("Next >"), 
		  _("Cancel"));
  if(ret != BUTTON1)
    return;
  
  switch(options.lp.calc_type)
    {
    case CALC_TI83:
    case CALC_TI83P:
      /* Display an information dialog box */
      ret = user2_box(_("Information"), 
		      _("You must have AShell on your calculator in order to do a ROM dump.\nTiLP wil transfer the ROM dump program and it will wait until you launch it from the calculator."),
		      _("Next >"), 
		      _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  /* Ask for the ROM size */
	  create_pbar_type5(_("ROM dump"), 
			    _("Receiving bytes"));
	  
	  strcpy(tmp_filename, g_get_tmp_dir());
	  strcat(tmp_filename, DIR_SEPARATOR);
	  strcat(tmp_filename, "tilp.ROMdump");
	  do
	    {
	      while( gtk_events_pending() ) { gtk_main_iteration(); }
	      if(info_update.cancel) break;
	      err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
	      if(tilp_error(err)) return;
	      err=ti_calc.dump_rom(dump, ret);
	      fclose(dump);
	    }
	  while( ((err == 35) || (err == 3)) );
	  
	  destroy_pbar();
	  if(tilp_error(err)) return;	      
	  gtk_widget_show(create_fileselection_7());
	  break;
	default: // Cancel */
	  return; 
	  break;
	}
      break;
    case CALC_TI85:
      /* Display an information dialog box */
      ret = user2_box(_("Information"), 
		      _("You must have Zshell or Usgard on your calculator in order to do a ROM dump.\nTiLP wil transfer the ROM dump program and it will wait until you launch it from the calculator."),
		      _("Next >"), 
		      _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  /* Ask for the shell type */
	  ret = user3_box("Shell type", 
			  "Select a shell", 
			  "Zshell", "Usgard", "Cancel");
	  if(ret == 3)
	    return;
	  else
	    {
	      /* Ask for the ROM size */
	      create_pbar_type5(_("ROM dump"), 
				_("Receiving bytes"));
	      
	      strcpy(tmp_filename, g_get_tmp_dir());
	      strcat(tmp_filename, DIR_SEPARATOR);
	      strcat(tmp_filename, "tilp.ROMdump");
	      do
		{
		  while( gtk_events_pending() ) { gtk_main_iteration(); }
		  if(info_update.cancel) break;
		  err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
		  if(tilp_error(err)) return;
		  err=ti_calc.dump_rom(dump, (ret == 1) ? 
				       SHELL_ZSHELL : SHELL_USGARD);
		  fclose(dump);
		}
	      while( ((err == 35) || (err == 3)) );
	      
	      destroy_pbar();
	      if(tilp_error(err)) return;	      
	  gtk_widget_show(create_fileselection_7());
	    }
	  break;
	default: // Cancel */
	  return; 
	  break;
	}
      break;
    case CALC_TI86:
      /* Display an information dialog box */
      ret = user2_box(_("Information"), 
		      _("You must have a shell (any) on your calculator in order to do a ROM dump.\nTiLP wil transfer the ROM dump program and it will wait until you launch it from the calculator."),
		      _("Next >"), 
		      _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  /* Ask for the ROM size */
	  create_pbar_type5(_("ROM dump"), 
			    _("Receiving bytes"));
	  
	  strcpy(tmp_filename, g_get_tmp_dir());
	  strcat(tmp_filename, DIR_SEPARATOR);
	  strcat(tmp_filename, "tilp.ROMdump");
	  do
	    {
	      while( gtk_events_pending() ) { gtk_main_iteration(); }
	      if(info_update.cancel) break;
	      err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
	      if(tilp_error(err)) return;
	      err=ti_calc.dump_rom(dump, ret);
	      fclose(dump);
	    }
	  while( ((err == 35) || (err == 3)) );
	  
	  destroy_pbar();
	  if(tilp_error(err)) return;	      
	  gtk_widget_show(create_fileselection_7());
	  break;
	default: // Cancel */
	  return; 
	  break;
	}
      break;
    case CALC_TI89:
    case CALC_TI92P:
      create_pbar_type5(_("ROM dump"), 
			_("Receiving bytes"));

      strcpy(tmp_filename, g_get_tmp_dir());
      strcat(tmp_filename, DIR_SEPARATOR);
      strcat(tmp_filename, "tilp.ROMdump");
      do
	{
	  while( gtk_events_pending() ) { gtk_main_iteration(); }
	  if(info_update.cancel) break;
	  err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
	  if(tilp_error(err)) return;
	  err=ti_calc.dump_rom(dump, ret);
	  fclose(dump);
	}
      while( ((err == 35) || (err == 3)) );
	      
      destroy_pbar();
      if(tilp_error(err)) return;	      
      gtk_widget_show(create_fileselection_7());
      break;
    case CALC_TI92:
      /* Display an information dialog box */
      ret = user2_box(_("Information"), 
		      _("You must have the FargoII shell on your calculator in order to do a ROM dump."),
		      _("Next >"), 
		      _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  /* Ask for the ROM size */
	  ret = user3_box("ROM size", 
			  "Select the size of your ROM or cancel", 
			  "1Mb", "2 Mb", "Cancel");
	  //ret = rom_dump_choose_size();
	  if(ret == 3)
	    return;
	  else
	    {
	      printf("ROM size: %i Mb\n", ret);
	      create_pbar_type5(_("ROM dump"), 
				_("Receiving bytes"));

	      strcpy(tmp_filename, g_get_tmp_dir());
	      strcat(tmp_filename, DIR_SEPARATOR);
	      strcat(tmp_filename, "tilp.ROMdump");
	      do
		{
		  while( gtk_events_pending() ) { gtk_main_iteration(); }
		  if(info_update.cancel) break;
		  err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
		  if(tilp_error(err)) return;
		  err=ti_calc.dump_rom(dump, ret);
		  fclose(dump);
		}
	      while( ((err == 35) || (err == 3)) );
	      
	      destroy_pbar();
	      if(tilp_error(err)) return;	      
	      gtk_widget_show(create_fileselection_7());
	    }	  
	  break;
	default: // Cancel */
	  return;
	  break;
	}
      break;
    default:
      DISPLAY("Unsupported ROM dump\n");
      break;
    }
}


void
on_rom_version1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  if(cb_rom_version() != 0)
    return;
}


void
on_install_a_shell1_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"),
	  _("In a next release..."));
}


void
on_options1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gtk_widget_show_all(create_plugins_dbox());
#endif
}


void
on_load_list1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gint err;
  gchar buffer[MAXCHARS];
  
  err = tiffep_registry_get_pointer(&plugin_registry);
  if(!err)
    registry_allowed = TRUE;
  else
    {
      registry_allowed = FALSE;
      
      tiffep_get_error(err, buffer);
      msg_box(_("Error"), buffer);
    }
#endif
}


void
on_list1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gtk_widget_show_all(create_registry_dbox()); 
#endif
}


void
on_register_files1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cb_registry_register();
}


void
on_unregister_files1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cb_registry_unregister();
}


void
on_external_programs1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_extprgms_dbox());
}


void
on_help2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_help_dbox());
}


void
on_manpage1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  /*
    fprintf(stdout, "manpage !!!\n");
    fprintf(stderr, "manpage2 !!\n");
    execute_command("ls -l\n");
*/  
  gtk_widget_show_all(create_manpage_dbox());
}


void
on_thanks1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_thanks_dbox());
}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_about_dbox());
}

/* Ready buton */
void
on_tilp_button4_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  if(cb_calc_is_ready() != 0)
    return;
}

/* Screendump button */
void
on_tilp_button5_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_screendump_dbox());
}

/* Dirlist button */
void
on_tilp_button6_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  if(cb_dirlist() != 0)
    return;
  
  refresh_ctree(main_window);
  refresh_info(main_window);
}

/* Backup button */
void
on_tilp_button7_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  if(cb_receive_backup() != 0)
	  return;

  gtk_widget_show(create_fileselection_3());
}

/* Restore button */
void
on_tilp_button8_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  int ret;

  /* Information box */
  ret = user2_box(_("Warning"), 
		  _("You are going to restore the calculator content with your backup. The whole memory will be erased. Are you sure you want to do that ?"),
		  _("Next >"), 
		  _("Cancel"));
  if(ret != BUTTON1)
    return;

  gtk_widget_show(create_fileselection_2());
}

/* Send/Receive button */
void
on_tilp_button9_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  if(ctree_win.selection != NULL)
    {
      on_receive_variable1_activate(NULL, NULL);
    }
  else if(clist_win.selection != NULL)
    {
      on_send_variable1_activate(NULL, NULL);
    }
  else if( (options.lp.calc_type == CALC_TI82) | 
	   (options.lp.calc_type == CALC_TI85) )
    {
      on_receive_variable1_activate(NULL, NULL);
    }
}

/* Mkdir button */
void
on_tilp_button10_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *dirname;

  dirname=dlgbox_entry(_("Make a new directory"), 
		       _("Name: "), 
		       _("new_directory"));
  if(dirname == NULL) return;

  { /* [X91] temporarily drop root privileges */
#ifdef __LINUX__
    uid_t effective;
    
    effective = geteuid();
    seteuid(getuid());
#endif
    if (mkdir(dirname, 255))
      {
	msg_box(_("Information"), _("Unable to create the directory.\n\n"));
	g_free(dirname);
      }
#ifdef __LINUX__
    seteuid(effective);
#endif
  }

  g_free(dirname);
  l_directory_list();
  refresh_clist(main_window);
  refresh_info(main_window);
}

/* Trash button */
void
on_tilp_button11_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  GList *ptr;
  struct file_info *f = NULL;
  gint ret;

  if(clist_win.file_selection != NULL)
    {
      /* Destroy the file selection */
      if(clist_win.file_selection != NULL)
	{
	  g_list_foreach(clist_win.file_selection, (GFunc) g_free, NULL);
	  g_list_free(clist_win.file_selection);
	  clist_win.file_selection=NULL;
	}
    }

  if(clist_win.selection==NULL) return;
  if(g_list_length(clist_win.selection)==1)
    {
      ret=user2_box(_("Warning"),
		    _("Are you sure you want to remove this file ?\n\n"),
		    _("Yes"), _("No"));
    }
  else
    {
      ret=user2_box(_("Warning"),
		    _("Are you sure you want to remove these files ?\n\n"), _("Yes"), _("No"));
    }
  if(ret == BUTTON2) return; 

  ptr=clist_win.selection;
  while(ptr!=NULL)
    {

      { /* [X91] temporarily drop root privileges */
#ifdef __LINUX__
	uid_t	effective;
	
	effective = geteuid();
	seteuid(getuid());
#endif
	if (unlink(f->filename))
	  msg_box(_("Information"),
		  _("Unable to remove a file.\n\n"));
#ifdef __LINUX__
	seteuid(effective);
#endif
      }
      ptr=ptr->next;
    }
  l_directory_list();
  refresh_clist(main_wnd);
  refresh_info(main_wnd);
}

/* Refresh button */
void
on_tilp_button12_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  l_directory_list();
  refresh_clist(button);
  refresh_info(button);
}

/*******************/
/* CTree callbacks */
/*******************/

gint last_status = 0;

/* A button has been pressed in the CTree */
gboolean
on_ctree1_button_press_event           (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkCList *clist;
  GtkCTree *ctree;
  GtkCTreeNode *node;
  gint x;
  gint y;
  gint row;
  gint column;
  static GList *selected_dir=NULL;

  x = event->x;
  y = event->y;

  clist = GTK_CLIST (widget);
  ctree = GTK_CTREE (widget);
  if (!gtk_clist_get_selection_info (clist, x, y, &row, &column)) 
    return FALSE;
  node=GTK_CTREE_NODE (g_list_nth (clist->row_list, row));

  /* printf("Button pressed on column %i\n", column); */
  //printf("<<%i>>\n", GTK_CTREE_ROW(node)->expanded);

  if( (GTK_CTREE_ROW(node)->children != NULL) && (last_status == 0) )
    {
      if(g_list_find(selected_dir, (gpointer)node)!=NULL)
	{
	  selected_dir=g_list_remove(selected_dir, (gpointer)node);
	  gtk_ctree_unselect_recursive(ctree, node);
	}
      else
	{
	  gtk_ctree_select_recursive(ctree, node);
	  selected_dir=g_list_append(selected_dir, (gpointer)node);
	}
    }
  last_status=0;
  /*
  printf("<<%p %p %p>>\n", GTK_CTREE_ROW(node)->parent, 
	 GTK_CTREE_ROW(node)->sibling,
	 GTK_CTREE_ROW(node)->children);
  */

  return FALSE;
}

/* A row have been selected */
void
on_ctree1_tree_select_row              (GtkCTree        *ctree,
                                        GList           *node,
                                        gint             column,
                                        gpointer         user_data)
{
  clist_selection_destroy();
  clist_selection_refresh();
  if(GTK_CTREE_ROW(node)->children == NULL)
    {
      ctree_win.selection = g_list_append(ctree_win.selection, 
        gtk_ctree_node_get_row_data(ctree, GTK_CTREE_NODE(node)));
    }
  //printf("data: <%p>\n", gtk_ctree_node_get_row_data(ctree, node));
  //printf("Row selected\n");
  /*  
  printf("<<%p %p %p>>\n", GTK_CTREE_ROW(node)->parent, 
	 GTK_CTREE_ROW(node)->sibling,
	 GTK_CTREE_ROW(node)->children);
  */
  refresh_info(main_window);
}

/* A row of the tree has been unselected */
void
on_ctree1_tree_unselect_row            (GtkCTree        *ctree,
                                        GList           *node,
                                        gint             column,
                                        gpointer         user_data)
{
  //printf("Row unselected\n");
  /*
    printf("Unselection on column: %i, id: %i\n", column, 
    *(gint *)gtk_ctree_node_get_row_data (ctree, node));
    */
  if(GTK_CTREE_ROW(node)->children == NULL)
    {
      ctree_win.selection=g_list_remove(ctree_win.selection, 
        gtk_ctree_node_get_row_data(ctree, GTK_CTREE_NODE(node)));
    }
  refresh_info(main_window);
}

/* A column has been clicked in the CTree */
void
on_ctree1_click_column                 (GtkCList        *clist,
                                        gint             column,
                                        gpointer         user_data)
{
  //printf("Column clicked\n");
  switch(column)
    {
    case 0:
      options.ctree_sort=SORT_BY_NAME;
      break;
    case 1:
      options.ctree_sort=SORT_BY_INFO;
      break;
    case 2:
      options.ctree_sort=SORT_BY_TYPE;
      break;
    case 3:
      options.ctree_sort=SORT_BY_SIZE;
      break;
    }

  refresh_ctree();
}



/* A node has been expanded */
void
on_ctree1_tree_expand                  (GtkCTree        *ctree,
                                        GList           *node,
                                        gpointer         user_data)
{
  //printf("CTree expanded\n");
  last_status = 1;
}

/* A node has been collapsed */
void
on_ctree1_tree_collapse                (GtkCTree        *ctree,
                                        GList           *node,
                                        gpointer         user_data)
{
  //printf("CTree collapsed\n");
  last_status=1;
}


/*******************/
/* CList callbacks */
/*******************/

static gint last_status2=0;

/* A button has been pressed in the CList */
gboolean
on_tilp_clist1_button_press_event      (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  gchar *name, *attrib;
  gint row, column;
  GdkEventButton *bevent;
  char *home_dir;
  
  if (!gtk_clist_get_selection_info (GTK_CLIST (widget), 
				     event->x, event->y, &row, &column)) 
    return FALSE; // FALSE ??
  gtk_clist_get_text(GTK_CLIST(widget), row, 1, &name);
  gtk_clist_get_text(GTK_CLIST(widget), row, 6, &attrib);
  switch(event->type)
    {
    case GDK_BUTTON_PRESS: // third button clicked
      if(event->button==3)
	{
	  //gtk_clist_select_row(GTK_CLIST(widget), row, column);
	  bevent=(GdkEventButton *)(event);
	  gtk_menu_popup(GTK_MENU(create_clist_rbm ()), 
			 NULL, NULL, NULL, NULL, 
			 bevent->button, bevent->time);
	}
      break;
    case GDK_2BUTTON_PRESS: // double click
      if(attrib[1]=='d')
	{
	  last_status2=1;
	  //gtk_clist_freeze(GTK_CLIST (widget));

	  { /* [X91] temporarily drop root privileges */
#ifdef __LINUX__
	    uid_t	effective;
	    
	    effective = geteuid();
	    seteuid(getuid());
#endif
	    if (chdir(name))
	      msg_box(_("Error"),
		      _("Unable to change of directory."));
#ifdef __LINUX__
	    seteuid(effective);
#endif
	  }
	  
	  /* Retrieve current working directory */
	  g_free(clist_win.cur_dir);
	  clist_win.cur_dir = g_get_current_dir();
	  
	  // do not allow UNIX users to go outside their HOME dir
	  // unless user forces it at compilation time (thanks to K. Kofler
	  // for this suggestion)
#if defined(__UNIX__) && !defined(ALLOW_EXIT_HOMEDIR) 
	  get_home_path(&home_dir);

	  /* If clist_win.cur_dir does not begin with "home_dir"
	   * or strlen(clist_win.cur_dir) < strlen(home_dir)
	   * then the user is trying to escape its home directory.
	   */

	  if ((strlen(clist_win.cur_dir) < strlen(home_dir)) || (strncmp (clist_win.cur_dir, home_dir, strlen (home_dir)) != 0))
	    {
	      chdir(home_dir);
	      g_free(clist_win.cur_dir);
	      clist_win.cur_dir = g_get_current_dir();
	      
	      msg_box(_("Error"),
		      _("You can not go outside of your HOME directory."));
	      return FALSE;
            }
	  g_free(home_dir);
#endif

	  l_directory_list();
	  refresh_clist();
	  refresh_info();
	}
      break;
    default:
      break;        
    }

  return FALSE;
}


/* A row has been selected in the CList */
void
on_tilp_clist1_select_row              (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gchar *name, *attrib;
  gchar *full_name;

  gtk_clist_get_text(clist, row, 1, &name);
  gtk_clist_get_text(clist, row, 6, &attrib);
  
  //printf("Selected row %i: <%s> <%s>, selectable: %i\n", row, name, attrib, gtk_clist_get_selectable(clist, row));

  //gtk_clist_thaw(clist);
  ctree_selection_destroy();
  ctree_selection_refresh();

  if(gtk_clist_get_selectable(clist, row))
    {
      clist_win.selection = 
	g_list_append(clist_win.selection, gtk_clist_get_row_data(clist, row));
      
      full_name=(gchar *)g_malloc((strlen(clist_win.cur_dir)+1+strlen(name)+1)*sizeof(gchar));
      strcpy(full_name, clist_win.cur_dir);
      strcpy(full_name, DIR_SEPARATOR);
      strcat(full_name, name);
      //printf("<%s>\n", full_name);
      clist_win.file_selection=g_list_append(clist_win.file_selection, 
					      (gpointer)full_name);
    }

  if(last_status2)
    {
      last_status2=0;
      gtk_clist_unselect_row(clist, row, 1);
    }
  refresh_info();
}

static gint GCompareStrings (gconstpointer a, gconstpointer b)
{
  return strcmp((gchar *)a, (gchar *)b);
}

/* A row has been unselected in the CList */
void
on_tilp_clist1_unselect_row            (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  gchar *name, *attrib;
  gchar *full_name;

  //gtk_clist_thaw(clist);  
  gtk_clist_get_text(clist, row, 1, &name);
  gtk_clist_get_text(clist, row, 6, &attrib);
  
  //printf("Unselected row %i: <%s> <%s>, selectable: %i\n", row, name, attrib, gtk_clist_get_selectable(clist, row));

  if(gtk_clist_get_selectable(clist, row))
    {
      clist_win.selection=g_list_remove(clist_win.selection, gtk_clist_get_row_data(clist, row));
      
      full_name=(gchar *)g_malloc((strlen(clist_win.cur_dir)+1+strlen(name)+1)*sizeof(gchar));
      strcpy(full_name, clist_win.cur_dir);
      strcpy(full_name, DIR_SEPARATOR);
      strcat(full_name, name);
      //printf("<%s>\n", full_name);
      //printf("<<%s>>\n", (char *)(g_list_find_custom(clist_win.file_selection, full_name, GCompareStrings)->data));
      clist_win.file_selection=g_list_remove(clist_win.file_selection, g_list_find_custom(clist_win.file_selection, full_name, GCompareStrings)->data);
      g_free(full_name);
    }
  refresh_info();
}


/* A column button has been clicked in the CList */
void
on_tilp_clist1_click_column            (GtkCList        *clist,
                                        gint             column,
                                        gpointer         user_data)
{
  switch(column)
    {
    case 0:
      options.clist_sort_order=!options.clist_sort_order; 
      break;
    case 1:
      options.clist_sort=SORT_BY_NAME;
      break;
    case 2:
      options.clist_sort=SORT_BY_DATE;
      break;
    case 3:
      options.clist_sort=SORT_BY_SIZE;
      break;
    case 4:
      options.clist_sort=SORT_BY_USER;
      break;
    case 5:
      options.clist_sort=SORT_BY_GROUP;
      break;
    case 6:
      options.clist_sort=SORT_BY_ATTRB;
      break; 
    }

  refresh_clist();
  refresh_info();
}

void
on_changelog1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show(create_startup_dbox());
}

void
on_tilp_dbox_show_sb                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  guint id;
  gchar buffer[MAXCHARS];

  g_snprintf(buffer, MAXCHARS, "Version %s", TILP_VERSION);

  id = gtk_statusbar_get_context_id(GTK_STATUSBAR(user_data), buffer);
  gtk_statusbar_push(GTK_STATUSBAR(user_data), id, buffer);
}


void
on_language1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show(create_lang_dbox());
}


void
on_associations1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_advanced1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_advanced_dbox());
}


void
on_group_file_manager1_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"),
	  _("This function is currently being implemented via TiFFEP."));
}

void
on_convert_flash_to_rom1_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show(create_fileselection_10());
}

