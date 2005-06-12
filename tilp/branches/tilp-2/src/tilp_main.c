/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

#ifdef __WIN32__
# include <locale.h>
# include <windows.h>
#endif

#include "tilp_core.h"

/* Global variables */
CableHandle* cable_handle = NULL;
CalcHandle*  calc_handle  = NULL;

//TicalcInfoUpdate info_update;
TilpOptions options = { 0 };
TilpLocal clist_win = { 0 };
TilpRemote ctree_win = { 0 };

gint working_mode = MODE_INI;

/*
  This function must be the first function to call in your function 'main'.
  It initializes the TiLP core engine.
*/
int tilp_main(int argc, char *argv[], char **arge)
{
	int err;

	/* Display program version */
	tilp_cmdline_version();

#ifndef __MACOSX__
	/* Initialize platform independant paths */
	tilp_paths_init();
#endif

	/* 
	   Do some initializations and load config 
	 */
	// At first, initialize the GUI independant functions with some 
	// defaults values to avoid NULL pointers.
	// Initialization made with console mode functions.
	tilp_indep_set_gui_cmdline();

	// Init refresh functions (libticalcs)
	tilp_refresh_set_update_cmdline();

#ifndef __MACOSX__
	// Initialize options with default values
	tilp_config_default();

	// Parse the config file
	tilp_config_read();
#else
    rc_init_with_default();
	rc_get_user_prefs();
#endif /* !__MACOSX__ */
	tilp_file_chdir(options.working_dir);

	// Scan the command line (passed as an argument)
	tilp_cmdline_scan(argc, argv);

	// Init locale & internationalization
#ifdef ENABLE_NLS
	tilp_info( "setlocale: <%s>\n", setlocale(LC_ALL, ""));
  	tilp_info( "bindtextdomain: <%s>\n", bindtextdomain(PACKAGE, inst_paths.locale_dir));
  	bind_textdomain_codeset(PACKAGE, "UTF-8"/*"ISO-8859-15"*/);
  	tilp_info( "textdomain: <%s>\n", textdomain(PACKAGE));
#endif /* ENABLE_NLS */

	/* 
	   Check the version of libraries and init
	 */
	if (strcmp(tifiles_version_get(), TILP_REQUIRES_LIBFILES_VERSION) < 0) 
	{
		tilp_info(_("libtifiles library version <%s> mini required.\n"), TILP_REQUIRES_LIBFILES_VERSION);
		gif->msg_box(_("Error"), _("Libtifiles: version mismatches."));
		exit(-1);
	}
	
	if (strcmp(ticables_version_get(), TILP_REQUIRES_LIBCABLES_VERSION) < 0) 
	{
		tilp_info(_("libticables library version <%s> mini required.\n"), TILP_REQUIRES_LIBCABLES_VERSION);
		gif->msg_box(_("Error"), _("Libticables: version mismatches."));
		exit(-1);
	}
	
	if (strcmp(ticalcs_version_get(), TILP_REQUIRES_LIBCALCS_VERSION) < 0) 
	{
		tilp_info(_("libticalcs library version <%s> mini required.\n"), TILP_REQUIRES_LIBCALCS_VERSION);
		gif->msg_box(_("Error"), _("Libticalcs: version mismatches."));
		exit(-1);
	}

	ticables_library_init();
	tifiles_library_init();
	ticalcs_library_init();

	/* 
	   Set cable & calc
	*/	
	cable_handle = ticables_handle_new(options.device.cable_model, 
		options.device.cable_port);
	if(cable_handle == NULL)
	{
		gif->msg_box("Error", "Can't set cable");
	}

	calc_handle = ticalcs_handle_new(options.device.calc_model);
	if(cable_handle == NULL)
	{
		gif->msg_box("Error", "Can't set cable");
	}

	err = ticalcs_cable_attach(calc_handle, cable_handle);
	tilp_error(err);

	/*
	   Display the working mode
	 */
	switch (working_mode & ~MODE_GUI) 
	{
	case MODE_CMD:
		tilp_info( _("Working mode: command line.\n"));
		break;
	case MODE_CON:
		tilp_info( _("Working mode: console (prompt).\n"));
		break;
	case MODE_GTK:
		tilp_info( _("Working mode: GTK+.\n"));
		break;
	case MODE_MFC:
		tilp_info( _("Working mode: MFC.\n"));
		break;
	case MODE_OSX:
		tilp_info( _("Working mode: Cocoa OS X GUI.\n"));
		break;
	}

	/* 
	   If we are in command line mode, does the required operation
	   and exit else fallback on a graphic interface.
	 */
#ifndef __MACOSX__
	if (working_mode & MODE_CMD) 
	{
		//tilp_cmdline_send();
		exit(0);
	}
#endif				/* !__MACOSX__ */

	return 0;
}
