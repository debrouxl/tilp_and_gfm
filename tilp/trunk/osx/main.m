#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <libticables/verbose.h>
#include <libticables/cabl_int.h>
#include <libticalcs/calc_int.h>

#import <Cocoa/Cocoa.h>

#include "../src/main.h"
#include "../src/defs.h"
#include "../src/gui_indep.h"
#include "../src/struct.h"
#include "../src/cb_misc.h"

#include "cocoa_structs.h"

struct cocoa_objects_ptr *objects_ptr;

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
    
  objects_ptr = (struct cocoa_objects_ptr *)malloc(sizeof(struct cocoa_objects_ptr));
    
  /* Init the classes pointers */
  objects_ptr->BoxesController = nil;
  objects_ptr->MenuController = nil;
  objects_ptr->PrefsController = nil;
  objects_ptr->ToolbarController = nil;
  objects_ptr->TilpController = nil;
  objects_ptr->tilpConfig = nil;
  objects_ptr->prefs = nil;
     
  /* Install a signal handler */
  signal(SIGINT, signal_handler);

  ticable_DISPLAY_settings(DSP_ON);
  
  /* Init the tilp core */
  main_init(argc, argv, arge); // general

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
      /* this won't work on Mac OS X as is */
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


  if(working_mode != MODE_OSX)
    {
      fprintf(stderr, "Trying to use an unsupported Graphical User Interface.\n");
      fprintf(stderr, "Program halted.\n");
      exit(-1);
    }
    
    return NSApplicationMain(argc, argv);
}
