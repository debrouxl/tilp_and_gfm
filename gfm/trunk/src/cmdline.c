/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  28/05/06 20:33 - cmdline.c
  
  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "cmdline.h"
#include "support.h"
#include "version.h"

static void my_log_handler(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data) { }

static gchar** array = NULL;
static gint show_version = 0;

static GOptionEntry entries[] = 
{
  { "version", 0, 0, G_OPTION_ARG_NONE, &show_version, N_("Version"), NULL},
  { G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &array, N_("filename(s)"), NULL },
  { 0 }
};

static void gfm_version(void)
{
	fprintf(stdout, _("GFM - Version %s, (C) 2006-2007 Tyler Cassidy & Romain Lievin\n"), GFM_VERSION);
	fprintf(stdout, _("THIS PROGRAM COMES WITH ABSOLUTELY NO WARRANTY\n"));
	fprintf(stdout, _("PLEASE READ THE DOCUMENTATION FOR DETAILS\n"));
    fprintf(stdout, _("built on %s %s\n"), __DATE__, __TIME__);
}

void cmdline_scan(int *argc, char ***argv)
{
	GOptionContext* context;
	GError *error = NULL;

	gfm_version();

  // Get rid of GTK+ Logging if need-be (GTK, GDK, GLib, libglade)
#if !defined(_DEBUG)
  g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING | 
                           G_LOG_LEVEL_MESSAGE | 
                           G_LOG_LEVEL_INFO | 
                           G_LOG_LEVEL_DEBUG,
	  	                     my_log_handler, NULL); // GTK
  g_log_set_handler("Gdk", G_LOG_LEVEL_WARNING | 
                           G_LOG_LEVEL_MESSAGE | 
                           G_LOG_LEVEL_INFO | 
                           G_LOG_LEVEL_DEBUG,
  		                     my_log_handler, NULL); // Gdk
  g_log_set_handler("GLib", G_LOG_LEVEL_WARNING | 
                            G_LOG_LEVEL_MESSAGE | 
                            G_LOG_LEVEL_INFO | 
                            G_LOG_LEVEL_MASK |
							G_LOG_FLAG_FATAL | 
                            G_LOG_FLAG_RECURSION | 
                            G_LOG_LEVEL_DEBUG,
                            my_log_handler, NULL); // GLib
#endif

	// parse command line
	context = g_option_context_new ("- Group File Manager");
	g_option_context_add_main_entries(context, entries, ""/*GETTEXT_PACKAGE*/);
	g_option_context_set_help_enabled(context, TRUE);
	g_option_context_set_ignore_unknown_options(context, FALSE);
	g_option_context_parse(context, argc, argv, &error);
	g_option_context_free(context);

	// show version if needed
	if(show_version)
	{
	    exit(0);
	}

	return;
}

const char* cmdline_get(void)
{
	if(array)
		return array[0];
	else
		return NULL;
}