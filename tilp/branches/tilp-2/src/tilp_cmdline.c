/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TILP_CALCS__
#define __TILP_CALCS__

#include <stdio.h>
#include <glib.h>

#include "tilp_core.h"

static gchar* calc;
static gchar* cable;
static gchar** array;
static gint use_gui;

static GOptionEntry entries[] = 
{
	{ "calc", 0, 0, G_OPTION_ARG_STRING, &calc, "Hand-held model", NULL },
	{ "cable", 0, 0, G_OPTION_ARG_STRING, &cable, "Link cable model", NULL },
	{ "port", 0, 0, G_OPTION_ARG_INT, &options.device.cable_port, "Link cable port", NULL },
	{ "timeout", 0, 0, G_OPTION_ARG_INT, &options.device.cable_timeout, "Link cable timeout", NULL },
	{ "delay", 0, 0, G_OPTION_ARG_INT, &options.device.cable_delay, "Link cable delay", NULL },
	{ "no-gui", 0, 0, G_OPTION_ARG_NONE, &use_gui, "Does not use GUI", NULL },
	{ G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &array, "filename(s)", NULL },
	{ NULL }
};

void tilp_cmdline_version(void)
{
	fprintf(stdout, _("TiLP - Version %s, (C) 1999-2005 Romain Lievin\n"), TILP_VERSION);
#ifdef __BSD__
	fprintf(stdout, _("FreeBSD port, (c) 2003-2004 Tijl Coosemans\n"));
#endif
#ifdef __MACOSX__
	fprintf(stdout, _("Mac OS X port Version %s (%s), (C) 2001-2003 Julien Blache <jb@tilp.info>\n"), TILP_OSX_VERSION, SVN_REV);
#endif
	fprintf(stdout, _("THIS PROGRAM COMES WITH ABSOLUTELY NO WARRANTY\n"));
	fprintf(stdout, _("PLEASE READ THE DOCUMENTATION FOR DETAILS\n"));
        fprintf(stdout, _("built on %s %s\n"), __DATE__, __TIME__);
}

int tilp_cmdline_scan(int argc, char **argv)
{
	GOptionContext* context;
	GError *error = NULL;

	context = g_option_context_new ("- Ti Linking Program");
	g_option_context_add_main_entries(context, entries, ""/*GETTEXT_PACKAGE*/);
	g_option_context_set_help_enabled(context, TRUE);
	g_option_context_set_ignore_unknown_options(context, FALSE);
	g_option_context_parse(context, &argc, &argv, &error);
	g_option_context_free(context);

	options.device.calc_model = ticalcs_string_to_model(calc);
	options.device.cable_model = ticalcs_string_to_model(cable);

	return 0;
}

#if 0

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
						G_DIR_SEPARATOR_S, p, NULL);
			} else {
				filename_on_cmdline = g_strdup(p);
			}

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
			if (!strcmp(q, "ti89t"))
				options.lp.calc_type = CALC_TI89T;
			if (!strcmp(q, "ti89"))
				options.lp.calc_type = CALC_TI89;
			if (!strcmp(q, "ti86"))
				options.lp.calc_type = CALC_TI86;
			if (!strcmp(q, "ti85"))
				options.lp.calc_type = CALC_TI85;
			if (!strcmp(q, "ti84+"))
				options.lp.calc_type = CALC_TI84P;
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
		if (strstr(arg, "port=")) {
			int port = USER_PORT;
			port = (int) atol(&arg[5]) - 1;
			switch(options.lp.link_type)
			{
			case LINK_PAR: 
				options.lp.port = PARALLEL_PORT_1 + port;
				break;
			case LINK_SER:
			case LINK_TGL: 
				options.lp.port = SERIAL_PORT_1 + port;
				break;
			case LINK_SLV: 
				options.lp.port = USB_PORT_1 + port;
				break;
			case LINK_TIE:
			case LINK_VTI:
				options.lp.port = VIRTUAL_PORT_1 + port;
				break;
			default:
				break;
			}
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
  This function send files passed on the command line and place them in
  the ClistWin linked list.
  Manage file type, calculator detection and some other things...
*/
int tilp_cmdline_send(void)
{
	TilpFileInfo *fi;
	int last = options.confirm;
	gchar *ext = NULL;
	
	if (clist_win.selection == NULL)
		return -1;

	// Check for a valid file
	fi = (TilpFileInfo *) (g_list_first(clist_win.selection))->data;
	ext = tifiles_get_extension(fi->name);
	if (ext == NULL) {
		printl(2, _
			      ("Invalid filename. There is no extension !\n"));
		exit(-1);
	}

	// Determine calculator type and override current settings
	options.lp.calc_type = tifiles_which_calc_type(fi->name);
	ticalc_set_calc(options.lp.calc_type, &ti_calc);

	// Send file(s)
	if (g_list_length(clist_win.selection) == 1) {

		// One file
		if (tifiles_is_a_flash_file(fi->name)) {
			if (!g_strcasecmp
			    (ext, tifiles_flash_app_file_ext()))
				tilp_calc_send_flash_app(fi->name);

			else if (!g_strcasecmp
				 (ext, tifiles_flash_os_file_ext()))
				tilp_calc_send_flash_os(fi->name);
		} else if (tifiles_is_a_regular_file(fi->name)) {
			options.confirm = FALSE;	// remove dirlist
			tilp_calc_send_var(0);
			options.confirm = last;
			return 0;
		} else if (tifiles_is_a_backup_file(fi->name)) {
			tilp_calc_send_backup(fi->name);
		} else {
			fprintf(stdout, _("Unknown file type.\n"));
		}
	} else {

		// More than one file
		if (clist_win.selection != NULL) {
			options.confirm = FALSE;
			tilp_calc_send_var(0);
			options.confirm = last;
			return 0;
		}
	}
	return 0;
}

#endif

#endif