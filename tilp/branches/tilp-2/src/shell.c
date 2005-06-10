/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <string.h>
#include <glib.h>

#include "tilp_core.h"
#include "dboxes.h"

#ifndef __WIN32__
static gint execute_linux_command(gchar * cmdline)
{
	gboolean result;
	gchar **argv = g_malloc0(3 * sizeof(gchar *));
	GError *error = NULL;

	argv[0] = g_strdup("/usr/X11R6/bin/xterm");
	if (!strcmp(cmdline, ""))
	  argv[1] = NULL;
	else
	  argv[1] = g_strconcat("-e ", cmdline, NULL);

	result = g_spawn_async(clist_win.current_dir, argv, NULL, 0, NULL,
			       NULL, NULL, &error);
	if (result == FALSE) {
		msg_box("Error",
			"Spawn error: do you have the 'xterm' program ?");
		g_warning("Failed to exec xterm: %s\n", error->message);
		g_error_free(error);
	}
	g_strfreev(argv);

	return 0;
}


#endif				/*  */

#ifdef __WIN32__
static gint execute_win32_command(gchar * cmdline)
{
	gboolean result;
	gchar **argv = g_malloc0(3 * sizeof(gchar *));
	GError *error = NULL;
	char *os_type;

	ticable_detect_os(&os_type);
	if (!strcmp(os_type, "Windows9x"))
	  argv[0] = g_strdup("command.com");
	else
	  argv[0] = g_strdup("C:\\Windows\\system32\\cmd.exe");

	if (!strcmp(cmdline, ""))
		argv[1] = NULL;
	else
		argv[1] = g_strconcat("-e ", cmdline, NULL);

	result = g_spawn_async(NULL/*clist_win.current_dir*/, argv, NULL, 0, NULL,
			       NULL, NULL, &error);
	if (result == FALSE) {
		msg_box("Error",
			"Spawn error: do you have the 'command.com'/'cmd.exe' program ?");
		g_warning("Failed to exec xterm: %s\n", error->message);
		g_error_free(error);
	}
	g_strfreev(argv);
	
	return 0;
}


#endif				/*  */
gint execute_command(gchar * cmdline)
{

#ifdef __WIN32__
	return execute_win32_command(cmdline);
#else				/*  */
	return execute_linux_command(cmdline);
#endif				/*  */
	return 0;
}

gint display_shell_dbox(void)
{
	return execute_command("");
}
