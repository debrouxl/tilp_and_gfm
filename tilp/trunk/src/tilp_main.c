/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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

#ifdef __WIN32__
# include <locale.h>
# include <windows.h>
#endif

#include "tilp_core.h"

/* Global variables */
CableHandle* cable_handle = NULL;
CalcHandle*  calc_handle  = NULL;

TilpOptions options    = { 0 };
TilpLocal   local  = { 0 };	// I will change these names into local & remote
TilpRemote  remote = { 0 };

int working_mode = MODE_INI;

/* Ctrl+C signal handler */
static void signal_handler(int sig_no)
{
	tilp_info(_("Signal SIGINT (Ctrl+C) caught...\n"));
	tilp_exit();
	tilp_info(_("Done.\n"));

	exit(0);
}

/*
  This function must be the first function to call in your function 'main'.
  It initializes the TiLP core engine.
*/
int tilp_init(int *argc, char ***argv)
{
	/* Display program version */
	tilp_cmdline_version();

	/* Initialize platform independant paths */
	tilp_paths_init();

	/* Init i18n support */
#ifdef ENABLE_NLS
	tilp_info("setlocale: <%s>", setlocale(LC_ALL, ""));
  	tilp_info("bindtextdomain: <%s>", bindtextdomain(PACKAGE, inst_paths.locale_dir));
  	bind_textdomain_codeset(PACKAGE, "UTF-8"/*"ISO-8859-15"*/);
  	tilp_info("textdomain: <%s>", textdomain(PACKAGE));
#endif

	/* Initialize callbacks with default functions */ 
	tilp_gif_set_default();

	/* Initialize/reload config */
	tilp_config_default();
	tilp_config_read();

	/* Scan and modify command line and change to working folder*/
	tilp_cmdline_scan(argc, argv);
	tilp_file_chdir(options.working_dir);

	/* Catch 'Ctrl-C' */
	signal(SIGINT, signal_handler);

	/* Check the version of libraries and init framework */
	if (strcmp(ticonv_version_get(), TILP_REQUIRES_LIBCONV_VERSION) < 0) 
		tilp_error(_("libticonv library version <%s> mini required.\n"), TILP_REQUIRES_LIBCONV_VERSION);

	if (strcmp(tifiles_version_get(), TILP_REQUIRES_LIBFILES_VERSION) < 0) 
		tilp_error(_("libtifiles library version <%s> mini required.\n"), TILP_REQUIRES_LIBFILES_VERSION);
	
	if (strcmp(ticables_version_get(), TILP_REQUIRES_LIBCABLES_VERSION) < 0) 
		tilp_error(_("libticables library version <%s> mini required.\n"), TILP_REQUIRES_LIBCABLES_VERSION);
	
	if (strcmp(ticalcs_version_get(), TILP_REQUIRES_LIBCALCS_VERSION) < 0) 
		tilp_error(_("libticalcs library version <%s> mini required.\n"), TILP_REQUIRES_LIBCALCS_VERSION);

	ticables_library_init();
	tifiles_library_init();
	ticalcs_library_init();

	/* Check for USB support */
	options.usb_avail = ticables_is_usb_enabled();

	/* Set cable & calc */
	if(options.auto_detect && options.usb_avail)
	{
		int ret;
		CableModel cable;
		CalcModel calc;
		CablePort port;

		ret = tilp_device_probe_usb(&cable, &port, &calc);
		if(!ret)
		{
			options.cable_model = cable;
			options.cable_port = port;
			options.calc_model = calc;
		}
	}

	tilp_device_open();

	/* 
	   If we are in command line mode, does the required operation
	   and exit else fallback on a graphic interface.
	 */
	if((working_mode & MODE_CMD) && !(working_mode & MODE_GUI))
	{
		tilp_cmdline_send();
		exit(0);
	}
	else if(working_mode == MODE_INI)
		exit(0);

	return 0;
}

int tilp_exit(void)
{
	tilp_device_close();

	ticables_library_exit();
	tifiles_library_exit();
	ticalcs_library_exit();

	return 0;
}
