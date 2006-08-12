/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "tilp_core.h"

static gchar* calc;
static gchar* cable;
static gchar** array;
static gchar** flist;
static gint dont_use_gui;
extern int working_mode;

static GOptionEntry entries[] = 
{
	{ "calc", 0, 0, G_OPTION_ARG_STRING, &calc, "Hand-held model", NULL },
	{ "cable", 0, 0, G_OPTION_ARG_STRING, &cable, "Link cable model", NULL },
	{ "port", 0, 0, G_OPTION_ARG_INT, &options.cable_port, "Link cable port", NULL },
	{ "timeout", 0, 0, G_OPTION_ARG_INT, &options.cable_timeout, "Link cable timeout", NULL },
	{ "delay", 0, 0, G_OPTION_ARG_INT, &options.cable_delay, "Link cable delay", NULL },
	{ "no-gui", 0, 0, G_OPTION_ARG_NONE, &dont_use_gui, "Does not use GUI", NULL },
	{ G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &array, "filename(s)", NULL },
	{ NULL }
};

void tilp_cmdline_version(void)
{
	fprintf(stdout, _("TiLP - Version %s, (C) 1999-2006 Romain Lievin\n"), TILP_VERSION);
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

/* Search for command line options and build file list (pseudo-selection) */
int tilp_cmdline_scan(int *argc, char ***argv)
{
	GOptionContext* context;
	GError *error = NULL;

	// parse command line
	context = g_option_context_new ("- Ti Linking Program");
	g_option_context_add_main_entries(context, entries, ""/*GETTEXT_PACKAGE*/);
	g_option_context_set_help_enabled(context, TRUE);
	g_option_context_set_ignore_unknown_options(context, FALSE);
	g_option_context_parse(context, argc, argv, &error);
	g_option_context_free(context);

	// report error
	if (error) 
	{
		tilp_warning("Failed to parse cmdline: %s\n", error->message);
		g_error_free(error);
	}

	// convert name to value
	if(calc != NULL)
	{
		options.calc_model = ticalcs_string_to_model(calc);
		g_free(calc);
	}

	// convert name to value
	if(cable != NULL)
	{
		options.cable_model = ticables_string_to_model(cable);
		g_free(cable);
	}

	// are files passed ?
	if(array != NULL)
	{
		gchar **p, **q;
		gint len;

		working_mode = MODE_CMD;

		// check whether path is local or absolute
		for(p = array, len = 0; *p != NULL; p++, len++);

		flist = g_malloc0((len + 1) * sizeof(gchar *));

		// rebuild a list of file with full path
		for(p = array, q = flist; *p != NULL; p++, q++)
		{
			if (!g_path_is_absolute(*p))
				*q = g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S, *p, NULL);
			else
				*q = g_strdup(*p);
		}

		// build a pseudo file selection for TiLP
		for(q = flist; *q != NULL; q++)
			tilp_clist_selection_add(*q);
		tilp_clist_contents_load();

		g_strfreev(array);
		g_strfreev(flist);
	}

	// don't use GUI ?
	if(dont_use_gui)
		working_mode &= ~MODE_GUI;
	else
		working_mode |= MODE_GUI;

	return 0;
}

/* Send files passed on the command line in no-gui mode */
int tilp_cmdline_send(void)
{
	int over = options.overwrite;
	gchar *ext = NULL;
	
	// Check for valid selection
	if (local.selection1 == NULL && local.selection2 == NULL && local.selection3 == NULL)
		return -1;

	// Send vars
	if(local.selection1)
	{
		options.overwrite = FALSE;
		tilp_calc_send_var();
		options.overwrite = over;
		return 0;
	}

	// Send OS or apps
	if(local.selection2)
	{
		FileEntry *fe = (local.selection2)->data;

		if(g_list_length(local.selection2) == 1 && 
			tifiles_file_is_flash(fe->name) && !g_strcasecmp(ext, tifiles_fext_of_flash_os(options.calc_model)))
		{
			tilp_calc_send_os(fe->name);
			return 0;
		}
		else
		{
			options.overwrite = FALSE;
			tilp_calc_send_app();
			options.overwrite = over;
			return 0;
		}
	}

	// Send backup
	if(local.selection3)
	{
		FileEntry *fe = (local.selection3)->data;

		tilp_calc_send_backup(fe->name);
		return 0;
	}

	return 0;
}

