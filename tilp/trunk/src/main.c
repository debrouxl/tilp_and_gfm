/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
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
#  include <config.h>
#endif				/*  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>		// for managing some signals

#include <glade/glade.h>
#include <gtk/gtk.h>
#include <glib.h>

#ifdef __WIN32__
# include <windows.h>
#endif				/*  */

#include "support.h"
#include "splash.h"
#include "tilp.h"
#include "toolbar.h"
#include "labels.h"
#include "clist.h"
#include "tilp_core.h"
#include "gtk_update.h"

static void my_log_handler                  (const gchar *log_domain,
                                             GLogLevelFlags log_level,
                                             const gchar *message,
                                             gpointer user_data) {}

int main(int argc, char *argv[])
{
	GdkPixbuf *icon;

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
		my_log_handler, NULL);
	g_log_set_handler ("Gdk", 
		G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
		my_log_handler, NULL);
	g_log_set_handler ("Gtk", 
		G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
		my_log_handler, NULL);

	g_log_set_handler ("GLib", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION, 
		my_log_handler, NULL);
#endif

	/* Init the GUI independant functions */
	tilp_gif_set_gtk();
	tilp_update_set_gtk();

	/* Create the main window */
	if(!(working_mode & MODE_CMD))
	{
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
		icon = create_pixbuf("icon.xpm");
		gtk_window_set_icon(GTK_WINDOW(main_wnd), icon);
		gdk_window_set_icon_name(main_wnd->window, _("TiLP-2"));
	}

	/* 
	   If variables have been passed on the command line in GUI mode then
	   send them 
	 */
	if((working_mode & MODE_GUI) && (working_mode & MODE_CMD)) 
	{
		extern int on_tilp_send(char *);

		splash_screen_set_label(_("Command line..."));

		if(local.selection1 || local.selection2)
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
