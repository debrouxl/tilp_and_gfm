/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Tilp Is a Linking Program
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
#include <string.h>

#include "tilp_core.h"

static gchar* calc;
static gchar* cable;
static gchar** array;
static gchar** flist;
static gint dont_use_gui;
       gint silent = 0;
static gint show_version;

static GOptionEntry entries[] = 
{
    { "version", 0, 0, G_OPTION_ARG_NONE, &show_version, N_("Version"), NULL},
	{ "calc", 0, 0, G_OPTION_ARG_STRING, &calc, N_("Hand-held model"), NULL },
	{ "cable", 0, 0, G_OPTION_ARG_STRING, &cable, N_("Link cable model"), NULL },
	{ "port", 'p', 0, G_OPTION_ARG_INT, &options.cable_port, N_("Link cable port"), NULL },
	{ "timeout", 't', 0, G_OPTION_ARG_INT, &options.cable_timeout, N_("Link cable timeout"), NULL },
	{ "delay", 'd', 0, G_OPTION_ARG_INT, &options.cable_delay, N_("Link cable delay"), NULL },
	{ "no-gui", 'n', 0, G_OPTION_ARG_NONE, &dont_use_gui, N_("Does not use GUI"), NULL },
	{ "silent", 's', 0, G_OPTION_ARG_NONE, &silent, N_("Silent mode (NO-GUI mode only"), NULL },
	{ G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &array, N_("filename(s)"), NULL },
	{ NULL, 0, 0, 0, NULL, NULL, NULL }
};

void tilp_cmdline_version(void)
{
	fprintf(stdout, _("TiLP2 - Version %s, (C) 1999-2008 Romain Lievin\n"), TILP_VERSION);
#ifdef __BSD__
	fprintf(stdout, _("FreeBSD port, (c) 2003-2004 Tijl Coosemans\n"));
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
	gint ret = 0;

	// parse command line
	context = g_option_context_new ("- Tilp Is a Linking Program");
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

	if(show_version)
	  {
	    exit(0);
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

	// look for short-options
        if(array != NULL)
          {
            gchar **p;
	    gint len;
            int i;

            // check for no extensions
            for(p = array, len = 0; *p != NULL; p++, len++)
              {
                if(strrchr(*p, '.') == NULL)
                  {
                    for(i = 0; i < CABLE_MAX; i++)
                      {
                        if(!g_strcasecmp(ticables_model_to_string(i), *p))
                          options.cable_model = i;
                      }

		    for(i = 0; i < CALC_MAX; i++)
                      {
                        if(!g_strcasecmp(ticalcs_model_to_string(i), *p))
                          options.calc_model = i;
                      }
                  }
	      }
	  }

	// remap for USB hand-helds
	options.calc_model = tilp_remap_to_usb(options.cable_model,
                                               options.calc_model);

	if(!options.cable_port)
	{
		switch(options.cable_model)
		{
		case CABLE_VTI:
		case CABLE_TIE:
			options.cable_port = PORT_0;
			break;
		default:
			options.cable_port = PORT_1;
			break;
		}
	}

	// are files passed ?
	if(array != NULL)
	{
		gchar **p, **q;
		gint len;

		working_mode = MODE_CMD;

		// count files
		for(p = array, len = 0; *p != NULL; p++, len++);

		// allocate list of files
		flist = g_malloc0((len + 1) * sizeof(gchar *));

		// rebuild a list of file with full path
		for(p = array, q = flist; *p != NULL; p++, q++)
		{
		  // skip short-options
		  if(strrchr(*p, '.') == NULL)
		    {
		      q--;
		      continue;
		    }

		  // check whether path is local or absolute
			if (!g_path_is_absolute(*p))
				*q = g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S, *p, NULL);
			else
				*q = g_strdup(*p);
		}

       		// build a pseudo file selection for TiLP
		for(q = flist; *q != NULL; q++)
		  {
			if(g_file_test(*q, G_FILE_TEST_EXISTS))
			{
				tilp_local_selection_add(*q);
			}
			else
			{
				gchar *str;

				str = g_strdup_printf(_("The file <%s> does not exist."), *q);
				gif->msg_box1(_("Error"), str);
				g_free(str);
				ret = -1;
			}
		  }

		g_strfreev(array);
		g_strfreev(flist);
	}

	// don't use GUI ?
	if(dont_use_gui)
		working_mode &= ~MODE_GUI;
	else
		working_mode |= MODE_GUI;

	return ret;
}

/* Send files passed on the command line in no-gui mode */
int tilp_cmdline_send(void)
{
	int ret = 0;
	int over = options.overwrite;

	// Check for valid selection
	if (local.selection0 == NULL && local.selection2 == NULL && 
	    local.selection4 == NULL)
		return -1;

	tilp_local_contents_load();

	// Send vars
	if(local.selection1)
	{
		options.overwrite = FALSE;
		ret = tilp_calc_send_var();
		options.overwrite = over;
		return ret;
	}

	// Send OS or apps
	if(local.selection3)
	{
		FileEntry *fe = (local.selection2)->data;

		if(g_list_length(local.selection2) == 1 && 
			tifiles_file_test(fe->name, TIFILE_OS, 
					  options.calc_model))
		{
			ret = tilp_calc_send_os(fe->name);
			return ret;
		}
		else
		{
			options.overwrite = FALSE;
			ret = tilp_calc_send_app();
			options.overwrite = over;
			return ret;
		}
	}

	// Send backup
	if(local.selection4)
	{
		FileEntry *fe = (local.selection4)->data;

		ret = tilp_calc_send_backup(fe->name);
		return ret;
	}

	return ret;
}

