/*  ti_link - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#ifdef __WIN32__
#  include <windows.h>
#endif
#include <signal.h> // for managing some signals

#include "includes.h"
//#include "perror.h"

/**************/
/* My widgets */
/**************/
GtkWidget *main_window = NULL; //unused
GtkWidget *main_wnd = NULL;
GtkWidget *clist_wnd = NULL;
GtkWidget *ctree_wnd = NULL;

struct toolbar_window toolbar_win={ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
struct clabel_window clabel_win={ NULL, NULL, NULL, NULL,
				  NULL, NULL, NULL, NULL };
struct progress_window p_win={ NULL, NULL, NULL, NULL, NULL, NULL };

/**********************************************************/
/* Structure which contains the GUI independant functions */
/**********************************************************/
struct gui_fncts gui_functions;

/*
  This signal handler catch the 'Ctrl-C' action
  for freeing some ressources
*/
#ifdef HAVE_TIFFEP
Shm s;
#endif
void signal_handler(int sig_no)
{
  DISPLAY("Signal SIGINT (Ctrl+C) caught...\n");
  DISPLAY("Trying to destroy ressources... ");
  
  link_cable.term_port();
#ifdef HAVE_TIFFEP
  shm_detach(&s);
  shm_destroy(&s);
#endif
  DISPLAY("Done.\n");

  exit(0);
}


/*********************/
/* The main function */
/*********************/
int main(int argc, char *argv[], char **arge)
{
#ifdef HAVE_TIFFEP
  TiffepMsg msg;
#endif

  /* Install a signal handler */
  signal(SIGINT, signal_handler);

#ifdef __LINUX__
  ticable_DISPLAY_settings(DSP_ON);
#endif
  
  /* Init the tilp core */
  main_init(argc, argv, arge); // general

  if(working_mode != MODE_GTK)
    {
      fprintf(stderr, "Trying to use an unsupported Graphic User Interface.\n");
      fprintf(stderr, "Program halted.\n");
      exit(-1);
    }
  
  /* Init GTK+ */
  gtk_set_locale ();
  gtk_init(&argc, &argv); // GTK specific
  add_pixmap_directory(inst_paths.pixmap_dir);

  /* Init the GUI independant functions */
  gui_functions.msg_box = msg_box;
  gui_functions.user1_box = user1_box;
  gui_functions.user2_box = user2_box;
  gui_functions.user3_box = user3_box;
  gui_functions.dlgbox_entry = dlgbox_entry;
  gui_functions.create_pbar_type1 = create_pbar_type1;
  gui_functions.create_pbar_type2 = create_pbar_type2;
  gui_functions.create_pbar_type3 = create_pbar_type3;
  gui_functions.create_pbar_type4 = create_pbar_type4;
  gui_functions.create_pbar_type5 = create_pbar_type5;
  gui_functions.destroy_pbar = destroy_pbar;
  set_gui_fncts(&gui_functions);
  gt_init_refresh_functions();

  /* Create the main window */
  main_wnd = create_tilp_dbox();
  main_window = main_wnd; // for compatibility
  
  /* In cmdline, does display the entire window, only the pbar */
  if(options.show_gui)
    {
      gtk_widget_show_all(main_wnd);
      refresh_sensitive_toolbar_buttons();
    }

  /* Do a local directory list */
  g_free(clist_win.cur_dir);
  clist_win.cur_dir = g_get_current_dir();
  
  /* 
     If variables have been passed on the command line in GUI mode then
     send them 
  */
  if(working_mode == MODE_GTK)
    {
      cb_send_cmdline();
    }
  
  /* Update right list */
  l_directory_list();
  refresh_clist();
  
  /* Display informations */
  refresh_info();

  /* Display an informational dbox at startup */
  display_startup_dbox();

  /* Listen TiFFEP commands */
#ifdef HAVE_TIFFEP
  if(tiffep_server_is_running())
    {
      /* Connect to server */
      if(err = tiffep_connect(&s))
	{
	  msg_box(_("Error"), 
		  _("The TiFFEP server can not be connected."));
	}
      id = gtk_idle_add(listen_tiffep, (gpointer)(&s));
      DISPLAY(_("The TiFFEP is running. Listening activated.\n"));

      /* Send a simple echo */
      cmd_send_echo(s);
      tiffep_cmd_recv_ok(s);
    }
  else
    {
      DISPLAY(_("The TiFFEP is not running. Listening deactivated.\n"));
    }
#endif

  /* GTK main loop */
  gtk_main();

  return 0;
}

/* 
   If TiLP is compiled in console mode (_CONSOLE), 
   then we use the 'main' entry point.
   If TiLP is compiled as a windowed application (_WINDOWS), 
   then we use the 'WinMain' entry point.
*/
#if defined(__WIN32__) && defined(_WINDOWS)// && !defined(_CONSOLE)
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
  HANDLE hMutex;

  /* Check whether a TiLP session is already running */
  hMutex = CreateMutex(NULL, TRUE, "TiLP");
  if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
      g_error("TiLP is already running.");
    }

  /* Turn off verbosity */
  ticable_DISPLAY_settings(DSP_OFF);
  //ticable_make_verbose(options.console_mode);
  
  return main(__argc, __argv, NULL);
}
#endif
