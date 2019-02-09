/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
 *  Copyright (C) 2005-2006  Kevin Kofler
 *  Copyright (C) 2018-2019  Lionel Debroux
 *  Copyright (C) 2018-2019  Adrien Bertrand
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif
#include <gtk/gtk.h>

#include "dboxes.h"
#include "intl.h"
#include "support.h"
#include "bookmark.h"

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
	// Kevin/Adrien/Lionel's list:
	// These ones should be first, as they will honor the user's choice rather
	// than guessing an arbitrary one:
	// * /usr/bin/xdg-open (runs the default browser of the desktop environment
	// currently in use, this is the best solution)
	// * /usr/bin/gnome-open (GNOME 2.6+ default browser, user-configurable)
	// * /usr/bin/open (macOS user-configurable default browser)
	// Distro-specific browser wrapper scripts:
	// * /usr/bin/sensible-browser (Debian's browser script)
	// * /usr/bin/htmlview (old RHL/Fedora default browser script, current
	// versions will honor the GNOME browser preference)
	// Fallbacks to a hardcoded list of browsers.
	//
	gboolean result;
	static const char *apps[] = { 
			"/usr/bin/xdg-open",
			"/usr/bin/gnome-open",
			"/usr/bin/open",
			"/usr/bin/sensible-browser",
			"/usr/bin/htmlview",
			"/usr/bin/firefox",
			"/usr/bin/firefox-esr",
			"/usr/bin/chromium",
			"/usr/bin/chromium-browser",
			"/usr/bin/google-chrome",
			"/usr/bin/google-chrome-stable",
			"/usr/bin/google-chrome-beta",
			"/usr/bin/google-chrome-unstable",
			"/usr/bin/falkon",
			"/usr/bin/midori",
			"/usr/bin/seamonkey",
			"/usr/bin/konqueror",
			"/usr/bin/mozilla",
			"/usr/bin/epiphany",
			"/usr/bin/epiphany-browser",		
	};
	gint i, n;

	n = sizeof(apps) / sizeof(apps[0]);
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
		msg_box1("Error", "Spawn error: could not open the default browser...");
		return -1;
	} 
#endif
	else 
	{
		const gchar *message = _("A web browser has been launched: this may take a while before it appears. If it is already launched, the page may be opened in the existing frame.");
		GTimer *timer;

		msg_box("Information", message, !0);

		for(timer = g_timer_new(); g_timer_elapsed(timer, NULL) < 3.0;);
		g_timer_destroy(timer);

		msg_box("", "", 0);
	}

	return 0;
}
