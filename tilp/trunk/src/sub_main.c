/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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
#include <fcntl.h>

#ifdef __MACOSX__
#include <glib/glib.h>
#include <libticalcs/calc_int.h>
#endif

#ifdef __WIN32__
# include <locale.h>
# include <windows.h>
#endif


#include "sub_main.h"
#include "defs.h"
#include "intl.h"
#include "struct.h"
#include "version.h"
#include "cmdinterface.h"
#include "cl_indep.h"
#include "gui_indep.h"
#include "error.h"
#include "cb_misc.h"

#ifndef __MACOSX__
#include "rcfile.h"
#else
#include "../osx/cocoa_config.h"
#endif

#include "version.h"
#include "cl_refresh.h"

/***************************************/
/* Some tilink variables and functions */
/***************************************/

LinkCable link_cable;
TicalcFncts ti_calc;

InfoUpdate info_update;
GuiFncts indep_functions;

struct goptions options; /* General options */

gint   is_active = 0;    /* Set if a transfer is active */
 
#if defined(__LINUX__)
gint working_mode = MODE_GTK;
#elif defined(__MACOSX__)
gint working_mode = MODE_OSX;
#elif defined(__WIN32__) && defined(USE_MFC)
gint working_mode = MODE_MFC;
#elif defined(__WIN32__) && !defined(USE_MFC)
gint working_mode = MODE_GTK;
#endif


struct clist_window clist_win = { NULL, NULL, NULL, NULL, 0 };
struct ctree_window ctree_win = { NULL, "", 0, NULL, NULL, NULL };

// Default relative path for Windows
#ifdef __WIN32__
struct installation_paths inst_paths = 
{ 
  "", "\\locale", "\\manpages", "\\help", "\\pixmaps"
}; 
#endif

#ifdef HAVE_TIFFEP
TiffepRegistry *plugin_registry = NULL;
gint registry_allowed = FALSE;
#endif

#ifndef __MACOSX__
int initialize_paths(void);
#endif

/*
  This function must be the first function to call in your function 'main'.
  It inits some variables and eventually, loads plugins.
*/
int sub_main(int argc, char *argv[], char **arge)
{
#ifdef HAVE_TIFFEP
  gchar buffer[MAXCHARS];
#endif

  /* Display program version */
  version();

#ifndef __MACOSX__
  /* Initialize platform independant paths */
  initialize_paths();
#endif

  /* 
     Do some initializations and load config 
  */
  // At first, initialize the GUI independant functions with some defaults 
  // values to avoid NULL pointers.
  // Initialization made with console mode functions.
  
  indep_functions.msg_box      = cmdline_msg_box;
  indep_functions.user1_box    = cmdline_user1_box;
  indep_functions.user2_box    = cmdline_user2_box;
  indep_functions.user3_box    = cmdline_user3_box;
  indep_functions.dlgbox_entry = cmdline_dlgbox_entry;
  indep_functions.create_pbar_type1 = cmdline_create_pbar_type1;
  indep_functions.create_pbar_type2 = cmdline_create_pbar_type2;
  indep_functions.create_pbar_type3 = cmdline_create_pbar_type3;
  indep_functions.create_pbar_type4 = cmdline_create_pbar_type4;
  indep_functions.create_pbar_type5 = cmdline_create_pbar_type5;
  indep_functions.destroy_pbar      = cmdline_destroy_pbar;
  
  set_gui_fncts(&indep_functions);  // Init indep functions
  cmdline_init_refresh_functions(); // Init refresh functions

  // Initialize options with default values
  cb_default_config();

#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: default config done.\n");
#endif

  // Parse the config file
#ifndef __MACOSX__
  read_rc_file();
#else
  rc_get_user_prefs();
#endif

#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: read rc done.\n");
#endif

  ticable_DISPLAY_settings(options.console_mode);

  // Scan the command line (passed as an argument)
  scan_cmdline(argc, argv);
  
#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: scan cmdline done.\n");
#endif
  
  /* 
     Initialize i18n support 
  */
#ifndef __MACOSX__
  // Init locale & internationalization
  bindtextdomain ("tilp", inst_paths.locale_dir);
  textdomain ("tilp");
#endif

  /* 
     Display library version 
  */
  DISPLAY(_("libticables library, version %s\n"),
	  ticable_get_version());
  DISPLAY(_("libticalcs library, version %s\n"),
          ticalc_get_version());
#ifdef HAVE_LIBTIFFEP
  DISPLAY(_("libtiffep library, version %s\n"),
	  tiffep_get_version());
#endif

  /* 
     Check the version of libraries 
  */
  if(strcmp(ticable_get_version(), LIB_CABLE_VERSION_REQUIRED) < 0)
    {
      DISPLAY(_("Library version <%s> mini required.\n"), 
	      LIB_CABLE_VERSION_REQUIRED);
      gif->msg_box(_("Error"), _("Libticables: version mismatches."));
      exit(-1);
    }
  if(strcmp(ticalc_get_version(), LIB_CALC_VERSION_REQUIRED) < 0)
    {
      DISPLAY(_("Library version <%s> mini required.\n"),
              LIB_CALC_VERSION_REQUIRED);
      gif->msg_box(_("Error"), _("Libticalcs: version mismatches."));      
      exit(-1);
    }
#ifdef HAVE_TIFFEP
  if(strcmp(tiffep_get_version(), LIB_TIFFEP_VERSION_REQUIRED) < 0)
    {
      DISPLAY(_("Library version <%s> mini required.\n"),
              LIB_TIFFEP_VERSION_REQUIRED);
      gif->msg_box(_("Error"), _("Libtiffep: version mismatches."));
      exit(-1);
    }
	*/
#endif

#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: libs version test done.\n");
#endif

  /* 
     Initialize the libTIcable library 
  */
	ticable_init();
	ticable_set_param2(options.lp);
	tilp_error(ticable_set_cable(options.lp.link_type, &link_cable));
	tilp_error(link_cable.init());

#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: ticable init done.\n");
#endif

  /* 
     Initialize the libTIcalc library 
  */
  ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);

#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: ticalc init done.\n");
#endif

  /* 
     List and load plugins 
  */
#ifdef HAVE_TIFFEP
  if(options.plugins_loading == PLUGINS_AUTO)
    {
      err = tiffep_registry_get_pointer(&plugin_registry);
      if(!err)
	registry_allowed = TRUE;
      else
	{
	  registry_allowed = FALSE;
	  tiffep_get_error(err, buffer);
	  DISPLAY(_("TiFFEP error: %s\n"), buffer);
	  gif->msg_box(_("Error"), buffer);
	}
    } 
#endif

  /*
    Display the working mode
  */
  switch(working_mode)
    {
    case MODE_CMD:
      DISPLAY(_("Working mode: command line.\n"));
      break;
    case MODE_CON: // not implemented yet
      DISPLAY(_("Working mode: console.\n"));
      break;
    case MODE_GTK:
      DISPLAY(_("Working mode: Gtk+ GUI.\n"));
      break;
    case MODE_INT:
      DISPLAY(_("Working mode: interactive (prompt).\n"));
      break;
    case MODE_OSX:
      DISPLAY(_("Working mode: Cocoa OS X GUI.\n"));
      break;
    }

  /* 
     If we are in command line mode, do the required operation
     and exit else go on to a graphic interface.
  */
// FIXME OS X : try it out...
#ifndef __MACOSX__
  if(working_mode == MODE_CMD)
    {
      cb_send_cmdline();
      return 0;
    }

  /*
    Enter in interactive mode (prompt)
  */
  if(working_mode == MODE_INT)
    {
      enter_command();
      return 0;
    }
#endif /* !__MACOSX__ */

  return 0;
}

/*
  Display a short help
*/
int help(void)
{
  DISPLAY(_("\n"));
  DISPLAY(_("TiLP - Version %s, (C) 1999-2002 Romain LIEVIN, Julien BLACHE\n"), TILP_VERSION);
#ifdef __MACOSX__
  DISPLAY(_("Mac OS X port Version %s, (C) 2001-2002 Julien BLACHE\n"), TILP_OSX_VERSION);
#endif
  DISPLAY(_("THIS PROGRAM COMES WITH ABSOLUTELY NO WARRANTY\n"));
  DISPLAY(_("PLEASE READ THE DOCUMENTATION FOR DETAILS\n"));
  DISPLAY(_("Usage: tilp [-options] [filename]\n"));
  DISPLAY("\n");
  DISPLAY(_("-h, --help    display this information page and exit\n"));
  DISPLAY(_("-v, --version display the version information and exit\n"));
  DISPLAY(_("-cmdline      use command line and stop\n"));
  DISPLAY(_("-gui=...      use the specified GUI (prompt, console, gtk)\n"));
  DISPLAY(_("-calc=...     give the calculator type\n"));
  DISPLAY(_("-link=...     give the link cable type\n"));
  DISPLAY(_("-dev_port=... give the device port (TI Graph Link cable only)\n"));
  DISPLAY(_("-adr_port=... give the address of the port (parallel or serial link cable only)\n"));
  DISPLAY(_("-timeout=...  give the time out in seconds\n"));
  DISPLAY(_("-delay=...    give the delay in microseconds\n"));
  DISPLAY("\n");
  DISPLAY(_("filename      a filename to send (console or GTK+)\n"));
  DISPLAY("\n");

  exit(0);
  return 0;
}

/*
  Display the program version
*/
int version(void)
{
  ticable_DISPLAY_settings(DSP_ON);

  DISPLAY(_("TiLP - Version %s, (C) 1999-2002 Romain LIEVIN, Julien BLACHE\n"), 
	  TILP_VERSION);
#ifdef __MACOSX__
  DISPLAY(_("Mac OS X port Version %s, (C) 2001-2002 Julien BLACHE\n"),
          TILP_OSX_VERSION);
#endif
  DISPLAY(_("Built on %s %s\n"), __DATE__, __TIME__);
  DISPLAY(_("THIS PROGRAM COMES WITH ABSOLUTELY NO WARRANTY\n"));
  DISPLAY(_("PLEASE READ THE DOCUMENTATION FOR DETAILS\n"));

  ticable_DISPLAY_settings(options.console_mode);

  return 0;
}

static int strexact(char *p1, char *p2)
{
  return (strstr(p1,p2) && strstr(p2,p1));
}

/*
  Scan the command line, extract arguments and init variables
*/
int scan_cmdline(int argc, char **argv)
{
  int cnt;
  char *p;
  char *q;
  char msg[80];
  struct file_info *fi;
  
  for(cnt=1; cnt<argc; cnt++)
    {
      p=argv[cnt];
      if(*p=='-' ) 
	{
	  // an option
	  p++;
	}
      else
	{
	  gchar* filename_on_cmdline;
	  // a filename to send

	  if(!g_path_is_absolute(p))
#ifndef __MACOSX__
	    filename_on_cmdline = g_strconcat(inst_paths.startup_dir, p, NULL);
#else
            {
                filename_on_cmdline = g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S, NULL);
                filename_on_cmdline = g_strconcat(filename_on_cmdline, p, NULL);
            }
#endif
	  else
	    filename_on_cmdline = g_strdup(p);
	  DISPLAY("Full filename to send: <%s>\n", filename_on_cmdline);
	  fi = (struct file_info *)g_malloc(sizeof(struct file_info));
	  fi->filename = g_strdup(filename_on_cmdline);
	  clist_win.selection = g_list_prepend(clist_win.selection, 
					       (gpointer)fi);
	  options.show_gui = FALSE;
	}
      strcpy(msg, p);

      if(strstr  (msg, "cmdline"   ))
        {
          working_mode = MODE_CMD;
        }

      if(strstr  (msg, "gui="      ))
	{
	  q = msg+4;
	  if(!strcmp(q, "console")) working_mode = MODE_CON;
	  if(!strcmp(q, "gtk")) working_mode = MODE_GTK;
	  if(!strcmp(q, "mfc")) working_mode = MODE_MFC;
	  if(!strcmp(q, "prompt")) working_mode = MODE_INT;
	}

      if(strstr  (msg, "calc="     ))
	{
	  q=msg+5;
	  if(!strcmp(q, "ti92+")) options.lp.calc_type=CALC_TI92P;
	  if(!strcmp(q, "ti92"))  options.lp.calc_type=CALC_TI92;
	  if(!strcmp(q, "ti89"))  options.lp.calc_type=CALC_TI89;
	  if(!strcmp(q, "ti86"))  options.lp.calc_type=CALC_TI86;
	  if(!strcmp(q, "ti85"))  options.lp.calc_type=CALC_TI85;
	  if(!strcmp(q, "ti83+")) options.lp.calc_type=CALC_TI83P;
	  if(!strcmp(q, "ti83"))  options.lp.calc_type=CALC_TI83;
	  if(!strcmp(q, "ti82"))  options.lp.calc_type=CALC_TI82;
	  if(!strcmp(q, "ti73"))  options.lp.calc_type=CALC_TI73;
	}

      if(strstr  (msg, "link="     )) 
	{
	  q=msg+5;
	  if(!strcmp(q, "par")) options.lp.link_type = LINK_PAR;
	  if(!strcmp(q, "ser")) options.lp.link_type = LINK_SER;
	  if(!strcmp(q, "tgl")) options.lp.link_type = LINK_TGL;
	  if(!strcmp(q, "avr")) options.lp.link_type = LINK_AVR;
	  if(!strcmp(q, "tie")) options.lp.link_type = LINK_TIE;
	  if(!strcmp(q, "vti")) options.lp.link_type = LINK_VTI;
	  if(!strcmp(q, "tpu")) options.lp.link_type = LINK_TPU;
	  if(!strcmp(q, "ugl")) options.lp.link_type = LINK_UGL;
	  if(!strcmp(q, "vtl")) options.lp.link_type = LINK_VTL;
	}

      if(strstr  (msg, "dev_port=" )) strcpy(options.lp.device, msg+9);
      if(strstr  (msg, "adr_port=" )) options.lp.io_addr = (int) strtol(msg+9, &q, 16);
      if(strstr  (msg, "timeout="  )) options.lp.timeout = (int) atol(&msg[8]);
      if(strstr  (msg, "delay="    )) options.lp.delay = (int) atol(&msg[6]);
      if(strexact(msg, "-help"     )) help();
      if(strexact(msg, "-version"  )) { version(); exit(0); }
    }

  return 0;
}
