/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
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
#endif				/*  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __MACOSX__
#include <glib.h>
#include "tilibs.h"
#else				/*  */
#include <glib/glib.h>
#include <libticalcs/calc_int.h>
#include "../osx/cocoa_config.h"
#endif				/*  */

#ifdef __WIN32__
# include <locale.h>
# include <windows.h>
#endif				/*  */

#include "tilp_core.h"
#include "tilp_prompt.h"

/***************************************/
/* Some tilink variables and functions */
/***************************************/
TicableLinkCable link_cable;
TicalcFncts ti_calc;
TicalcInfoUpdate info_update;
TilpOptions options;
gint working_mode = MODE_INI;
TilpClistWin clist_win = {
	0
};

TilpCtreeWin ctree_win = {
	0
};


#ifndef __MACOSX__
TilpInstPaths inst_paths = {
	"", "\\locale", "\\manpages", "\\help", "\\pixmaps"
};


#endif				/*  */
void help(void)
{
	DISPLAY("\n");
	DISPLAY(_("Usage: tilp [-options] [filename]\n"));
	DISPLAY("\n");
	DISPLAY(_
		("-h, --help    display this information page and exit\n"));
	DISPLAY(_
		("-v, --version display the version information and exit\n"));
	DISPLAY(_("-cmdline      use command line and stop\n"));
	DISPLAY(_("-gui=...      use the specified GUI (console, gtk)\n"));
	DISPLAY(_("-calc=...     give the calculator type\n"));
	DISPLAY(_("-link=...     give the link cable type\n"));
	DISPLAY(_("-dev_port=... give the device port\n"));
	DISPLAY(_("-adr_port=... give the address of the port\n"));
	DISPLAY(_("-timeout=...  give the time out in seconds\n"));
	DISPLAY(_("-delay=...    give the delay in microseconds\n"));
	DISPLAY("\n");
	DISPLAY(_("filename      a filename to send (console or GTK+)\n"));
	DISPLAY("\n");
	DISPLAY(_("See the manpage for more informations...\n"));
	DISPLAY("\n");
	exit(0);
}

/*
  Display the program version
*/
void version(void)
{

#ifndef __WIN32__
	ticable_DISPLAY_settings(DSP_ON);
#endif
	DISPLAY(_
		("TiLP - Version %s, (C) 1999-2003 Romain Lievin <roms@tilp.info>\n"),
		TILP_VERSION);

#ifdef __BSD__
	DISPLAY(_("FreeBSD port, (c) 2003 Tijl Coosemans\n"));
#endif
    
#ifdef __MACOSX__
	DISPLAY(_
		("Mac OS X port Version %s (%s), (C) 2001-2003 Julien Blache <jb@tilp.info>\n"),
		TILP_OSX_VERSION, SVN_REV);
#endif

	DISPLAY(_("Built on %s %s\n"), __DATE__, __TIME__);
	DISPLAY(_("THIS PROGRAM COMES WITH ABSOLUTELY NO WARRANTY\n"));
	DISPLAY(_("PLEASE READ THE DOCUMENTATION FOR DETAILS\n"));
	ticable_DISPLAY_settings(options.console_mode);
}

static int strexact(char *p1, char *p2)
{
	return (strstr(p1, p2) && strstr(p2, p1));
}


/*
  Scan the command line, extract arguments and init variables
*/
int scan_cmdline(int argc, const char **argv)
{
	int cnt;
	const char *p;
	char *q;
	char arg[80];
	TilpFileInfo *fi;
	for (cnt = 1; cnt < argc; cnt++) {
		p = argv[cnt];
		if (*p == '-') {

			// an option
			p++;
		} else {

			// a filename to send/open
			gchar *filename_on_cmdline = NULL;

			// check whether path is local or absolute
			if (!g_path_is_absolute(p)) {
				filename_on_cmdline =
				    g_strconcat(g_get_current_dir(),
						G_DIR_SEPARATOR_S, NULL);
				filename_on_cmdline =
				    g_strconcat(filename_on_cmdline, p,
						NULL);
			} else
				filename_on_cmdline = g_strdup(p);

			//printf("<<%s>\n", filename_on_cmdline);

			// build a pseudo-selection for the TiLP core
			fi = (TilpFileInfo *)
			    g_malloc0(sizeof(TilpFileInfo));
			fi->name = g_strdup(filename_on_cmdline);
			clist_win.selection =
			    g_list_prepend(clist_win.selection,
					   (gpointer) fi);
			options.show_gui = FALSE;
		}
		strcpy(arg, p);
		if (strstr(arg, "cmdline")) {
			working_mode = MODE_CMD;
		}
		if (strstr(arg, "gui=")) {
			q = arg + 4;
			if (!strcmp(q, "console"))
				working_mode = MODE_CON;

			else if (!strcmp(q, "gtk"))
				working_mode = MODE_GTK;

			else if (!strcmp(q, "mfc"))
				working_mode = MODE_MFC;

			else
				exit(0);
		}
		if (strstr(arg, "calc=")) {
			q = arg + 5;
			if (!strcmp(q, "v200"))
				options.lp.calc_type = CALC_V200;
			if (!strcmp(q, "ti92+"))
				options.lp.calc_type = CALC_TI92P;
			if (!strcmp(q, "ti92"))
				options.lp.calc_type = CALC_TI92;
			if (!strcmp(q, "ti89"))
				options.lp.calc_type = CALC_TI89;
			if (!strcmp(q, "ti86"))
				options.lp.calc_type = CALC_TI86;
			if (!strcmp(q, "ti85"))
				options.lp.calc_type = CALC_TI85;
			if (!strcmp(q, "ti83+"))
				options.lp.calc_type = CALC_TI83P;
			if (!strcmp(q, "ti83"))
				options.lp.calc_type = CALC_TI83;
			if (!strcmp(q, "ti82"))
				options.lp.calc_type = CALC_TI82;
			if (!strcmp(q, "ti73"))
				options.lp.calc_type = CALC_TI73;
		}
		if (strstr(arg, "link=")) {
			q = arg + 5;
			if (!strcmp(q, "par"))
				options.lp.link_type = LINK_PAR;
			if (!strcmp(q, "ser"))
				options.lp.link_type = LINK_SER;
			if (!strcmp(q, "tgl"))
				options.lp.link_type = LINK_TGL;
			if (!strcmp(q, "avr"))
				options.lp.link_type = LINK_AVR;
			if (!strcmp(q, "tie"))
				options.lp.link_type = LINK_TIE;
			if (!strcmp(q, "vti"))
				options.lp.link_type = LINK_VTI;
			if (!strcmp(q, "ugl"))
				options.lp.link_type = LINK_UGL;
			if (!strcmp(q, "slv"))
				options.lp.link_type = LINK_SLV;
		}
		if (strstr(arg, "dev_port="))
			strcpy(options.lp.device, arg + 9);
		if (strstr(arg, "adr_port="))
			options.lp.io_addr = (int) strtol(arg + 9, &q, 16);
		if (strstr(arg, "timeout="))
			options.lp.timeout = (int) atol(&arg[8]);
		if (strstr(arg, "delay="))
			options.lp.delay = (int) atol(&arg[6]);
		if (strexact(arg, "-help") || strexact(arg, "h"))
			help();
		if (strexact(arg, "-version") || strexact(arg, "v"))
			exit(0);
	}
	return 0;
}


/*
  This function must be the first function to call in your function 'main'.
  It initializes the TiLP core engine.
*/
int tilp_main(int argc, const char *argv[], char **arge)
{

	/* Change name of default logging file */
#ifdef __WIN32__
	ticable_verbose_set_file("C:\\tilp.log");
#else
	ticable_verbose_set_file("/tmp/tilp.log");
#endif

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
	ticable_DISPLAY_settings(options.console_mode);

	// Scan the command line (passed as an argument)
	scan_cmdline(argc, argv);

	// Init locale & internationalization
#ifdef ENABLE_NLS
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, inst_paths.locale_dir /*LOCALEDIR*/);
	DISPLAY("%s: bindtextdomain to %s\n", PACKAGE,
		inst_paths.locale_dir);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
	textdomain(PACKAGE);

#endif /* ENABLE_NLS */

	/* 
	   Check the version of libraries 
	 */
	if (strcmp(ticable_get_version(), LIB_CABLE_VERSION_REQUIRED) < 0) {
		DISPLAY(_
			("libticables library version <%s> mini required.\n"),
			LIB_CABLE_VERSION_REQUIRED);
		gif->msg_box(_("Error"),
			     _("Libticables: version mismatches."));
        fprintf(stderr, "%s\n", ticable_get_version());
		exit(-1);
	}
	if (strcmp(ticalc_get_version(), LIB_CALC_VERSION_REQUIRED) < 0) {
		DISPLAY(_
			("libticalcs library version <%s> mini required.\n"),
			LIB_CALC_VERSION_REQUIRED);
		gif->msg_box(_("Error"),
			     _("Libticalcs: version mismatches."));
		exit(-1);
	}

	/* 
	   Initialize the libticables library 
	 */
	ticable_init();
	ticable_set_param(&options.lp);
	tilp_error(ticable_set_cable(options.lp.link_type, &link_cable));
	tilp_error(link_cable.init());

	/* 
	   Initialize the libticalcs library 
	 */
	ticalc_init();
	ticalc_set_cable(&link_cable);
	ticalc_set_calc(options.lp.calc_type, &ti_calc);

	/*
	   Display the working mode
	 */
	switch (working_mode & ~MODE_GUI) {
	case MODE_CMD:
		DISPLAY(_("Working mode: command line.\n"));
		break;
	case MODE_CON:
		DISPLAY(_("Working mode: console (prompt).\n"));
		break;
	case MODE_GTK:
		DISPLAY(_("Working mode: GTK+.\n"));
		break;
	case MODE_MFC:
		DISPLAY(_("Working mode: MFC.\n"));
		break;
	case MODE_OSX:
		DISPLAY(_("Working mode: Cocoa OS X GUI.\n"));
		break;
	}

	/* 
	   If we are in command line mode, does the required operation
	   and exit else fallback on a graphic interface.
	 */
#ifndef __MACOSX__
	if (working_mode == MODE_CMD) {
		tilp_cmdline_send();
		exit(0);
	}

	/*
	   Enter in console mode (prompt)
	 */
	if (working_mode == MODE_CON) {
		tilp_prompt();
		exit(0);
	}
#endif				/* !__MACOSX__ */
	return 0;
}
