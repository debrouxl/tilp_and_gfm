#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../src/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#import <Cocoa/Cocoa.h>

/**********************************************************/
/* Structure which contains the GUI independant functions */
/**********************************************************/
struct gui_fncts gui_functions;

/*
  This signal handler catches the 'Ctrl-C' action
  to free some ressources
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


int main(int argc, const char *argv[], char **arge)
{
#ifdef HAVE_TIFFEP
  TiffepMsg msg;
#endif

  /* Install a signal handler */
  signal(SIGINT, signal_handler);

  ticable_DISPLAY_settings(DSP_ON);
  
  /* Init the tilp core */
  main_init(argc, argv, arge); // general

  if(working_mode != MODE_OSX)
    {
      fprintf(stderr, "Trying to use an unsupported Graphical User Interface.\n");
      fprintf(stderr, "Program halted.\n");
      exit(-1);
    }
  
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
    
  /* 
     If variables have been passed on the command line in GUI mode then
     send them 
  */
  if(working_mode == MODE_OSX)
    {
      cb_send_cmdline();
    }
  
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

    return NSApplicationMain(argc, argv);
}
