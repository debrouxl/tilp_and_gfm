#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include <sys/types.h> /* needed for seteuid */
#include <unistd.h>

#include "gtk_clist_cb.h"
#include "gtk_clist_rbm.h"
#include "support.h"

#include "includes.h"

void
on_cut1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  clist_win.copy_cut = CUT_FILE;
}


void
on_copy1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  clist_win.copy_cut = COPY_FILE;
}


void
on_paste1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GList *ptr;
  gchar *src;
  gchar *dest;
  
  /* If no selection, quits */
  if(clist_win.file_selection == NULL) return;
  /* Move every file */
  ptr=clist_win.file_selection;
  while(ptr != NULL)
    {
      src=(gchar *)(ptr->data);
      dest = (gchar *)g_malloc((strlen(clist_win.cur_dir)+1+strlen(src)+1)*sizeof(gchar));
      strcpy(dest, clist_win.cur_dir);
      strcpy(dest, DIR_SEPARATOR);
      strcat(dest, g_basename(src));

      if(clist_win.copy_cut == COPY_FILE)
	{
	  copy_file(src, dest);
	}
      else
	{
	  move_file(src, dest); 
	}
      g_free(dest);

      ptr=ptr->next;
    }
  /* Destroy the file selection */
  if(clist_win.file_selection != NULL)
    {
      g_list_foreach(clist_win.file_selection, (GFunc) g_free, NULL);
      g_list_free(clist_win.file_selection);
      clist_win.file_selection=NULL;
    }
  l_directory_list();
  refresh_clist();
  refresh_info();
}


void
on_move_to_parent_dir1_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  char *home_dir;

  { /* [X91] temporarily drop root privileges */
    uid_t effective;
#ifdef __LINUX__
    effective = geteuid();
    seteuid(getuid());
#endif
    if(chdir(".."))
      fprintf(stderr, _("Chdir error.\n"));
#ifdef __LINUX__
    seteuid(effective);
#endif
  }

  g_free(clist_win.cur_dir);
  clist_win.cur_dir = g_get_current_dir();

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
      return;// FALSE;
    }
  g_free(home_dir);
#endif
  
  l_directory_list();
  refresh_clist();
  refresh_info();
}


void
on_select_all1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_clist_select_all(GTK_CLIST(clist_wnd));
}


void
on_unselect_all1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_clist_unselect_all(GTK_CLIST(clist_wnd));
}


void
on_unzip1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  on_unzip_archive1_activate(NULL, user_data);
}


void
on_untar1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  on_untar_archive1_activate(NULL, user_data);
}


void
on_ungroup1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"), 
	  _("The 'TI file format & plugin proxy kit' is going to be developped..."));
}


void
on_unpack1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  //item_file_unpack(NULL, user_data);
  on_unpack__obsolete_1_activate(NULL, user_data);
}


void
on_view1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gint err;
  GList *ptr;
  struct file_info *fi;
  gchar buffer[MAXCHARS];
  gchar *app_path;
  gchar *full_path;

  if(clist_win.selection==NULL) return;
  ptr=clist_win.selection;
  while(ptr!=NULL)
    {
      fi = (struct file_info *)ptr->data;
      full_path = g_strconcat(clist_win.cur_dir, 
			      DIR_SEPARATOR, fi->filename, NULL);
      
      err = tiffep_load_plugin(full_path, &app_path);
      if(err)
	{
	  tiffep_get_error(err, buffer);
	  msg_box(_("Error"), buffer);
	}
      else
	{
	  fprintf(stdout, "path: %s\n", app_path);
	}
      
      ptr=ptr->next;
    }
  clist_selection_destroy();
  clist_selection_refresh();
#endif
  
  /*
  msg_box(_("Information"), 
	  _("The 'TI file format & plugin proxy kit' is going to be developped..."));
  return;
  */
}


void
on_rename1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gchar *filename;
  GList *ptr;
  struct file_info *f;
  uid_t effective;
  
  if(clist_win.selection == NULL) 
    return;
  ptr=clist_win.selection;
  while(ptr!=NULL)
    {
      f=(struct file_info *)ptr->data;
      
      filename = dlgbox_entry(_("Rename the file"), _("Name: "), _("new_name"));
      if(filename == NULL) 
	return;

      /* [X91] temporarily drop root privileges before renaming */
#ifdef __LINUX__
      effective = geteuid();
      if (seteuid(getuid()))
	{
	  g_error(_("Could not drop privileges, aborting\n"));
	  exit(-1);
	}
#endif
      if(rename(f->filename, filename) == -1)
	{
	  msg_box(_("Information"), _("Unable to rename the file."));
	  g_free(filename);
	}
#ifdef __LINUX__
      if (seteuid(effective))
	{
	  g_error(_("Could not regain privileges, aborting\n"));
	  exit(-1);
	}
#endif
    }
      g_free(filename);

      ptr = ptr->next;
 
/* I've been able to trace a SIGSEGV till the first g_malloc()
 * of the function below. It seems that a part of the software
 * corrupts the heap, given that after the call to malloc(), the
 * code (which is normally protected) is written. */

      l_directory_list();
      refresh_clist(main_window);
      refresh_info(main_window);
}


void
on_properties1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gint err;
  GList *ptr;
  struct file_info *fi;
  gchar buffer[MAXCHARS];
  gchar *full_filename = NULL;

  if(clist_win.selection==NULL) return;
  ptr=clist_win.selection;
  while(ptr!=NULL)
    {
      fi = (struct file_info *)ptr->data;

      full_filename = g_strconcat(clist_win.cur_dir, 
				  DIR_SEPARATOR, fi->filename, NULL);

      err = display_ti_file_info(full_filename);
      if(err)
	{
	  tiffep_get_error(err, buffer);
	  msg_box(_("Error"), buffer);
	}
      
      ptr=ptr->next;
    }
  clist_selection_destroy();
  clist_selection_refresh();
#endif

  //gtk_widget_show_all(create_tifileinfo_dbox());
  /*
  msg_box(_("Information"), 
	_("This function is not yet available."));
  */
}


void
on_update_window1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  //refresh_clist(clist_wnd);
}


void
on_make_a_new_dir1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gchar *dirname;

  dirname=dlgbox_entry(_("Make a new directory"), _("Name: "), _("new_directory"));
  if(dirname == NULL) return;

  { /* [X91] temporarily drop root privileges */
#ifdef __LINUX__
    uid_t effective;
    
    effective = geteuid();
    seteuid(getuid());
#endif
    if(mkdir(dirname, 255))
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
  refresh_clist();
  refresh_info();
}


void
on_delete_file1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  //toolbar_button_07(main_wnd, user_data);
  on_tilp_button11_clicked(NULL, NULL);
}


void
on_fargo_ii1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  msg_box(_("Information"), 
	  _("This function is not yet available."));
}


void
on_change_drive1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef __WIN32__
  //fprintf(stdout, "drive: %c\n", (char)GPOINTER_TO_INT(user_data));
  
  cb_change_drive((char)GPOINTER_TO_INT(user_data));
  
  l_directory_list();
  refresh_clist(main_window);
  refresh_info(main_window);
#endif
}

void
rbm_change_drive_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef __WIN32__
  //fprintf(stdout, "drive: %c\n", (char)GPOINTER_TO_INT(user_data));
  
  cb_change_drive((char)GPOINTER_TO_INT(user_data));
  
  l_directory_list();
  refresh_clist(main_window);
  refresh_info(main_window);
#endif
}

void
on_clist_rbm_show                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *menu = GTK_WIDGET(user_data);
  GtkWidget *change_drive;
#ifdef __WIN32__
  GtkWidget *change_drive_menu;
  GtkAccelGroup *change_drive_menu_accels;
  GtkWidget *c_drive;
  int ch, drive, curdrive;
  gchar buffer[8];
  gint available_drives[27]; // A..Z -> 26 letters
#endif
  
  //fprintf(stdout, "show\n");
  change_drive = gtk_menu_item_new_with_label (_("Change _drive"));
  gtk_widget_ref (change_drive);
  gtk_object_set_data_full (GTK_OBJECT (menu), "change_drive", change_drive,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (change_drive);
  gtk_container_add (GTK_CONTAINER (menu), change_drive);
#ifdef __WIN32__
  change_drive_menu = gtk_menu_new ();
  gtk_widget_ref (change_drive_menu);
  gtk_object_set_data_full (GTK_OBJECT (menu), "change_drive_menu", change_drive_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (change_drive), change_drive_menu);
  change_drive_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (change_drive_menu));
  
  curdrive = _getdrive();
  for(drive=1; drive<= 26; drive++) 
    available_drives[drive]=0;
  for( drive = 3; drive <= 26; drive++ )
    {
      if( !_chdrive( drive ) )
	{
	  g_snprintf(buffer, 8, "%c:", drive + 'A' - 1);
	  available_drives[drive] = drive + 'A' - 1;
	  c_drive = gtk_menu_item_new_with_label (buffer);
	  gtk_widget_ref (c_drive);
	  gtk_object_set_data_full (GTK_OBJECT (menu), "c_drive", c_drive,
				    (GtkDestroyNotify) gtk_widget_unref);
	  gtk_widget_show (c_drive);
	  gtk_container_add (GTK_CONTAINER (change_drive_menu), c_drive);
	  
	  gtk_signal_connect (GTK_OBJECT (c_drive), "activate",
			      GTK_SIGNAL_FUNC (rbm_change_drive_activate),
			      GINT_TO_POINTER(available_drives[drive]));
	}
    }
  _chdrive( curdrive );
#else
  gtk_signal_connect (GTK_OBJECT (change_drive), "activate",
		      GTK_SIGNAL_FUNC (rbm_change_drive_activate),
		      NULL);
#endif
}


void
on_plugins1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  
}


void
on_shell1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#if defined(__LINUX__)
  gtk_widget_show_all(create_shell_dbox());
#elif defined(__WIN32__)
  msg_box(_("Information"),
	  _("In a next release (Win32 only)..."));
#endif
}

/* */
