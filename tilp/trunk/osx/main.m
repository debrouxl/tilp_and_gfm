/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Romain Lievin, Julien BLACHE
 *
 *  $Id$
 *
 *  Cocoa GUI for Mac OS X -- from gtk/gtk_main.c
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>

#include <libticables/verbose.h>
#include <libticables/cabl_int.h>
#include <libticalcs/calc_int.h>

#import <Cocoa/Cocoa.h>

#include "../src/tilp_core.h"
#include "../src/tilp_defs.h"
#include "../src/tilp_indep.h"
#include "../src/tilp_struct.h"

// a utility function
uint32_t swap_bytes(uint32_t a)
{
  return (a >> 24) | ((a & 0xff0000) >> 16) << 8 | ((a & 0xff00) >> 8) << 16 | (a & 0xff) << 8;
}

#include "cocoa_structs.h"

struct cocoa_objects_ptr *objects_ptr;

void signal_handler(int sig_no)
{
  DISPLAY("Signal SIGINT (Ctrl+C) caught...\n");
  DISPLAY("Trying to destroy ressources... ");
  
  link_cable.exit();
  ticalc_exit();
  ticable_exit();
  DISPLAY("Done.\n");

  exit(0);
}

// FIXME OS X : need to resync'ed with tilp v6.62 main.c
int main(int argc, const char *argv[], char **arge)
{
  NSAutoreleasePool *prefsPool;
    
  objects_ptr = (struct cocoa_objects_ptr *)malloc(sizeof(struct cocoa_objects_ptr));
    
  /* Init the classes pointers */
  objects_ptr->myBoxesController = nil;
  objects_ptr->myMenuController = nil;
  objects_ptr->myPrefsController = nil;
  objects_ptr->myTilpController = nil;
  objects_ptr->mySheetsController = nil;
  objects_ptr->tilpConfig = nil;
  objects_ptr->prefs = nil;
     
  /* Install a signal handler */
  signal(SIGINT, signal_handler);

  // mandatory to get the prefs in main_init()
  // because Cocoa is not yet initialized  
  prefsPool = [[NSAutoreleasePool alloc] init];
#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: autorelease pool initialized\n");
#endif
  
  /* Init the tilp core */
  tilp_main(argc, argv, arge);

  working_mode = MODE_GUI | MODE_OSX;

  // we no longer need the pool
  [prefsPool release];
#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: autorelease pool released\n");
#endif
  prefsPool = nil;

  // FIXME OS X : cmdline gui
  if(working_mode != (MODE_GUI | MODE_OSX))
    {
      fprintf(stderr, "Trying to use an unsupported User Interface.\n");
      fprintf(stderr, "Program halted.\n");
      exit(-1);
    }
    
  /* Probing */
  DISPLAY("probing: %i\n", link_cable.probe());
    
  return NSApplicationMain(argc, argv);
}
