/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif
#include <gtk/gtk.h>

#include "dboxes.h"

int go_to_bookmark(const char *link)
{
#ifdef __WIN32__
	HINSTANCE hInst;

	// Windows do the whole work for us, let's go...
	hInst = ShellExecute(NULL, "open", link, NULL, NULL, SW_SHOWNORMAL);
	if((int)hInst <= 32)
	{
		//msg_box("Error", "Unable to run ShellExecute extension.");
		return -1;
	}
#else
	// Kevin's list:
	// * /usr/bin/gnome-open (GNOME 2.6+ default browser, this really should be
	// first on the list to try, as this will honor the user's choice rather than
	// guessing an arbitrary one)
	// * /usr/bin/sensible-browser (Debian's browser script)
	// * /usr/bin/htmlview (old RHL/Fedora default browser script)
	// * /usr/bin/firefox (Mozilla Firefox)
	// * /usr/bin/mozilla (Mozilla Seamonkey)
	// * /usr/bin/konqueror (Konqueror)
	//
	gboolean result;
	char *apps[] = 
	{ 
			"/usr/bin/gnome-open",
			"/usr/bin/sensible-browser",
			"/usr/bin/htmlview",
			"/usr/bin/firefox",
			"/usr/bin/mozilla",
			"/usr/bin/konqueror",
	};
	gint i, n;

	n = sizeof(apps) / sizeof(char *);
	for(i = 0; i < n; i++)
	{
		gchar **argv = g_malloc0(3 * sizeof(gchar *));

		argv[0] = g_strdup(apps[i]);
		argv[1] = g_strdup(link);
		argv[2] = NULL;

		result = g_spawn_async(NULL, argv, NULL, 0, NULL, NULL, NULL, NULL);
		g_strfreev(argv);

		if(result != FALSE)
			break;
	}

	if (i == n) 
	{
		msg_box1("Error", "Spawn error: do you have Mozilla installed ?");
		return -1;
	} 
#endif
	else 
	{
		GtkWidget *dialog;
		GTimer *timer;
		const gchar *message = "A web browser has been launched: this may take a while before it appears. If it is already launched, the page will be opened in the existing frame.";

		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
					   GTK_MESSAGE_INFO,
					   GTK_BUTTONS_CLOSE, message);
		g_signal_connect_swapped(GTK_OBJECT(dialog), "response",
					 G_CALLBACK(gtk_widget_destroy),
					 GTK_OBJECT(dialog));
		gtk_widget_show_all(GTK_WIDGET(dialog));
		
		while(gtk_events_pending()) gtk_main_iteration();
		for(timer = g_timer_new(); g_timer_elapsed(timer, NULL) < 3.0;);

		g_timer_destroy(timer);
		gtk_widget_destroy(GTK_WIDGET(dialog));
	}

	return 0;
}