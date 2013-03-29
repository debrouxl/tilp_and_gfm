/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2008  Romain Lievin
 *  Copyright (C) 2007  Kevin Kofler
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif                          /*  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>             // for managing some signals

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>

#ifdef __WIN32__
# include <windows.h>
#endif                          /*  */

#if WITH_KDE
#include "kde.h"
#endif

#include "support.h"
#include "splash.h"
#include "tilp.h"
#include "toolbar.h"
#include "labels.h"
#include "clist.h"
#include "tilp_core.h"
#include "gtk_update.h"

static void my_blackhole_log_handler (const gchar *log_domain,
                            GLogLevelFlags log_level,
                            const gchar *message,
                            gpointer user_data)
{
	// Do nothing.
}

#ifdef __WIN32__
static void default_log_handler(const gchar *log_domain,
                                GLogLevelFlags log_level,
                                const gchar *message,
                                gpointer user_data)
{
	FILE *log_file = user_data;

	if (log_domain)
		fprintf(log_file, "%s-", log_domain);

	switch (log_level & G_LOG_LEVEL_MASK) {
	case G_LOG_LEVEL_ERROR:
		fprintf(log_file, "ERROR: ");
		break;
	case G_LOG_LEVEL_CRITICAL:
		fprintf(log_file, "CRITICAL: ");
		break;
	case G_LOG_LEVEL_WARNING:
		fprintf(log_file, "WARNING: ");
		break;
	case G_LOG_LEVEL_MESSAGE:
		fprintf(log_file, "MESSAGE: ");
		break;
	case G_LOG_LEVEL_INFO:
		fprintf(log_file, "INFO: ");
		break;
	case G_LOG_LEVEL_DEBUG:
		fprintf(log_file, "DEBUG: ");
		break;
	default:
		fprintf(log_file, "???: ");
	}
	fprintf(log_file, "%s\n", message);
}
#endif

#define LOG_FILE ".tilp.log"

int main(int argc, char *argv[])
{
	GdkPixbuf *icon;

	/* Redirect standard output to a file - printing to the Windows terminal slows operation down way too much */
#ifdef __WIN32__
	gchar *tmp;
	FILE *log_file;

	tmp = g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, LOG_FILE, NULL);
	log_file = g_fopen(tmp, "wt");
	g_free(tmp);

	if (log_file != NULL)
		g_log_set_default_handler(&default_log_handler, log_file);
#endif

	// Force GLib 2.32+ to print info and debug messages like older versions did, unless this variable is already set.
	// No effect on earlier GLib versions.
	g_setenv("G_MESSAGES_DEBUG", "all", /* overwrite = */ FALSE);

	/* Init the tilp core */
	tilp_init(&argc, &argv);

	/* Init GTK+ */
	gtk_init(&argc, &argv);
	add_pixmap_directory(inst_paths.pixmap_dir);
	add_pixmap_directory(inst_paths.icon_dir);
	splash_screen_start();

	/*
		Get rid of glib, gdk, gtk warnings when compiled in Release mode
	*/
#if !defined(_DEBUG)
	g_log_set_handler ("GLib", 
		G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
		my_blackhole_log_handler, NULL);
	g_log_set_handler ("Gdk", 
		G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
		my_blackhole_log_handler, NULL);
	g_log_set_handler ("Gtk", 
		G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
		my_blackhole_log_handler, NULL);

	g_log_set_handler ("GLib", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, 
		my_blackhole_log_handler, NULL);
#endif

	/* Init the GUI-independent functions */
	tilp_gif_set_gtk();
	tilp_update_set_gtk();

	/* Create the main window */
	if(!(working_mode & MODE_CMD))
	{
#if WITH_KDE
		splash_screen_set_label(_("Initializing KDE..."));
		sp_kde_init(argc, argv, "tilp", _("TiLP"), VERSION, _("Tilp Is a Linking Program"), "Copyright (c) 1999-2008 Romain Lievin", "http://lpg.ticalc.org/prj_tilp/", "tilp-users@lists.sf.net");
		atexit(sp_kde_finish);
		// Not needed unless we want to add a DCOP interface.
		// g_timeout_add(26, sp_kde_process_qt_events, NULL);
#endif

		splash_screen_set_label(_("Loading GUI..."));
		main_wnd = display_tilp_dbox();
	}

	/* Do a local directory list */
	g_free(local.cwdir);
	local.cwdir = g_get_current_dir();

	/* Update the local view (not visible yet) */
	if(!(working_mode & MODE_CMD))
	{
		clist_refresh();
		labels_refresh();
	}

	/* Inits are done ! */
	working_mode &= ~MODE_INI;
	tilp_err(0);		// pop errors (display console mode)

	/* In cmdline, does not display the entire window, only the pbar */
	if(!(working_mode & MODE_CMD))
	{
		gtk_widget_show(main_wnd);
		toolbar_refresh_buttons();
		icon = create_pixbuf("tilp.xpm");
		gtk_window_set_icon(GTK_WINDOW(main_wnd), icon);
		gdk_window_set_icon_name(main_wnd->window, _("TiLP2"));
	}

	/* 
	   If variables have been passed on the command line in GUI mode then
	   send them 
	 */
	if((working_mode & MODE_GUI) && (working_mode & MODE_CMD)) 
	{
		extern int on_tilp_send(const char *);

		splash_screen_set_label(_("Command line..."));

		if(local.selection0 || local.selection2 || local.selection5)
			on_tilp_send("");
		else if(local.selection4)
			tilp_cmdline_send();
	}

	/* GTK main loop */
	splash_screen_stop();
	if(!(working_mode & MODE_CMD))
		gtk_main();
	tilp_exit();

	return 0;
}


/* 
   If TiLP is compiled in console mode (_CONSOLE), 
   then we use the 'main' entry point.
   If TiLP is compiled as a windowed application (_WINDOWS), 
   then we use the 'WinMain' entry point.
*/
#if defined(__WIN32__) && defined(_WINDOWS)	// && !defined(_CONSOLE)
int APIENTRY WinMain(HINSTANCE hInstance,
		     HINSTANCE hPrevInstance,
		     LPSTR lpCmdLine, int nCmdShow)
{
	HANDLE hMutex;

	/* Check whether a TiLP session is already running */
	hMutex = CreateMutex(NULL, TRUE, "TiLP");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBox(NULL, _("An TiLP session is already running. Check the task list."), _("Error"), MB_OK);
	}

	return main(__argc, __argv, NULL);
}


#endif				/*  */
