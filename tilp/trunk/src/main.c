/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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

#include "tilp_core.h"

#include "gstruct.h"
#include "support.h"
#include "toolbar.h"
#include "tilp.h"
#include "gtk_refresh.h"
#include "pbars.h"
#include "dboxes.h"
#include "ctree.h"
#include "clist.h"
#include "labels.h"
#include "release.h"
#include "splash.h"
#include "wizard.h"

/**************/
/* My widgets */
/**************/
GtkWidget *main_wnd = NULL;
GtkWidget *clist_wnd = NULL;
GtkWidget *ctree_wnd = NULL;
struct gfm_window gfm_win = { 0 };
TilpGuiFncts gui_functions = {
	0
};


/******************/
/* Ctrl+C handler */
/******************/
void signal_handler(int sig_no)
{
	printl(0, "Signal SIGINT (Ctrl+C) caught...\n");
	printl(0, "Trying to destroy ressources... ");
	link_cable.exit();
	ticalc_exit();
	ticable_exit();
	printl(0, _("Done.\n"));
	exit(0);
}

/*****************/
/* Main function */
/*****************/
int main(int argc, char *argv[], char **arge)
{
	char rc_version[32];
	GdkPixbuf *icon;
	//uint8_t varname[20], utf8[35];

	/* Catch 'Ctrl-C' */
	signal(SIGINT, signal_handler);

	/* Init the tilp core */
	tilp_main(argc, (const char **)argv, arge);

	/* Init GTK+ */
	//gtk_set_locale();
	gtk_init(&argc, &argv);
	add_pixmap_directory(inst_paths.pixmap_dir);
	add_pixmap_directory(inst_paths.icon_dir);
	splash_screen_start();

	/* Init the GUI independant functions */
	gui_functions.msg_box = msg_box;
	gui_functions.msg_box2 = msg_box2;
	gui_functions.msg_box3 = msg_box3;
	gui_functions.msg_box4 = msg_box4;
	gui_functions.msg_entry = msg_entry;
	gui_functions.create_pbar_type1 = create_pbar_type1;
	gui_functions.create_pbar_type2 = create_pbar_type2;
	gui_functions.create_pbar_type3 = create_pbar_type3;
	gui_functions.create_pbar_type4 = create_pbar_type4;
	gui_functions.create_pbar_type5 = create_pbar_type5;
	gui_functions.destroy_pbar = destroy_pbar;
	tilp_gui_set_fncts(&gui_functions);
	tilp_guigtk_set_refresh();

	/* Create the main window */
	splash_screen_set_label(_("Loading GUI..."));
	main_wnd = display_tilp_dbox();
	working_mode = MODE_GUI | MODE_GTK;
	tilp_error(0);		// display console mode errors

	/* In cmdline, does not display the entire window, only the pbar */
	if (options.show_gui) {
		gtk_widget_show_all(main_wnd);
		toolbar_refresh_buttons();
		icon = create_pixbuf("icon.xpm");
		gtk_window_set_icon(GTK_WINDOW(main_wnd), icon);
		gdk_window_set_icon_name(main_wnd->window, _("TiLP"));
	}

	/* Do a local directory list */
	g_free(clist_win.current_dir);
	clist_win.current_dir = g_get_current_dir();

	/* 
	   If variables have been passed on the command line in GUI mode then
	   send them 
	 */
	/*
	   if ((working_mode & ~MODE_GUI) == MODE_GTK) {
	   splash_screen_set_label(_("Command line..."));
	   tilp_cmdline_send();
	   }
	 */

	/* Update right list */
	tilp_dirlist_local();
	clist_refresh();
	labels_refresh();

	/* Display an informational dbox at startup */
	tilp_rcfile_get_version(rc_version);
	if (!strcmp(rc_version, "")
	    || (strcmp(rc_version, TILP_VERSION) > 0)) {
		display_release_dbox();
	}

	/* Scan plug-ins */
	splash_screen_set_label(_("Scanning plugins..."));
	tilp_plugins_scan();

	/* 
	   If variables have been passed on the command line in GUI mode then
	   open them 
	 */
	/*
	   if ((working_mode & ~MODE_GUI) == MODE_GTK) {
	   splash_screen_set_label(_("Command line..."));
	   tilp_cmdline_send();
	   }
	 */

	/* GTK main loop */
	splash_screen_stop();

	//strcpy(varname, "group/");
	//tifiles_translate_varname(varname, utf8, 0);

	gtk_main();
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
		g_error("WinMain: TiLP is already running.");
	}
	return main(__argc, __argv, NULL);
}


#endif				/*  */
