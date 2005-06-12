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

#if 0

/*
  This function must be the first function to call in your function 'main'.
  It initializes the TiLP core engine.
*/
int tilp_main(int argc, const char *argv[], char **arge)
{
	/* Display program version */
	version();

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
	tilp_gui_set_default_fncts();

	// Init refresh functions (libticalcs)
	tilp_cmdline_set_refresh();

#ifndef __MACOSX__
	// Initialize options with default values
	tilp_config_default();

	// Parse the config file
	tilp_rcfile_read();
#else
    	rc_init_with_default();
	rc_get_user_prefs();
#endif /* !__MACOSX__ */
	tilp_chdir(options.working_dir);

	// Scan the command line (passed as an argument)
	scan_cmdline(argc, argv);

	// Init locale & internationalization
#ifdef ENABLE_NLS
	printl(0, "setlocale: <%s>\n", setlocale(LC_ALL, ""));
  	printl(0, "bindtextdomain: <%s>\n", bindtextdomain(PACKAGE, inst_paths.locale_dir));
  	bind_textdomain_codeset(PACKAGE, "UTF-8"/*"ISO-8859-15"*/);
  	printl(0, "textdomain: <%s>\n", textdomain(PACKAGE));
#endif /* ENABLE_NLS */

	/* 
	   Check the version of libraries 
	 */
	if (strcmp(tifiles_get_version(), TILP_REQUIRES_LIBFILES_VERSION) < 0) {
		printl(0, _
			("libtifiles library version <%s> mini required.\n"),
			TILP_REQUIRES_LIBFILES_VERSION);
		gif->msg_box(_("Error"),
			     _("Libtifiles: version mismatches."));
		exit(-1);
	}
	
	if (strcmp(ticable_get_version(), TILP_REQUIRES_LIBCABLES_VERSION) < 0) {
		printl(0, _
			("libticables library version <%s> mini required.\n"),
			TILP_REQUIRES_LIBCABLES_VERSION);
		gif->msg_box(_("Error"),
			     _("Libticables: version mismatches."));
		exit(-1);
	}
	
	if (strcmp(ticalc_get_version(), TILP_REQUIRES_LIBCALCS_VERSION) < 0) {
		printl(0, _
			("libticalcs library version <%s> mini required.\n"),
			TILP_REQUIRES_LIBCALCS_VERSION);
		gif->msg_box(_("Error"),
			     _("Libticalcs: version mismatches."));
		exit(-1);
	}

	/* 
	   Initialize the libticables library 
	 */
        ticable_set_printl(ticables_printl);
	ticable_init();
	ticable_set_param(&options.lp);
	tilp_error(ticable_set_cable(options.lp.link_type, &link_cable));
	tilp_error(link_cable.init());
	
	/* 
	   Initialize the libtifiles library 
	 */
        tifiles_set_printl(tifiles_printl);
	tifiles_init();
	tifiles_set_calc(options.lp.calc_type);

	/* 
	   Initialize the libticalcs library 
	 */
        ticalc_set_printl(ticalcs_printl);
	ticalc_init();
	ticalc_set_cable(&link_cable);
	ticalc_set_calc(options.lp.calc_type, &ti_calc);

	/*
	   Display the working mode
	 */
	switch (working_mode & ~MODE_GUI) {
	case MODE_CMD:
		printl(0, _("Working mode: command line.\n"));
		break;
	case MODE_CON:
		printl(0, _("Working mode: console (prompt).\n"));
		break;
	case MODE_GTK:
		printl(0, _("Working mode: GTK+.\n"));
		break;
	case MODE_MFC:
		printl(0, _("Working mode: MFC.\n"));
		break;
	case MODE_OSX:
		printl(0, _("Working mode: Cocoa OS X GUI.\n"));
		break;
	}

	/* 
	   If we are in command line mode, does the required operation
	   and exit else fallback on a graphic interface.
	 */
#ifndef __MACOSX__
	if (working_mode & MODE_CMD) {
		tilp_cmdline_send();
		exit(0);
	}

	/*
	   Enter in console mode (prompt)
	 */
	if (working_mode & MODE_CON) {
		tilp_prompt();
		exit(0);
	}
#endif				/* !__MACOSX__ */
	return 0;
}

#endif