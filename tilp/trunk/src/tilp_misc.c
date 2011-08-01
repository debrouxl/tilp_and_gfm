/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tilp_core.h"			

/* Change the current drive (Win32 only) */
int tilp_drive_change(char drive_letter)
{
#ifdef __WIN32__
	gchar *s;
	g_snprintf(local.cwdir, 8, "%c:\\", (char) drive_letter);

	s = g_strdup(local.cwdir);
	if (tilp_file_chdir(s) == -1) 
	{
		gif->msg_box1(_("Error"), _("Unable to change directory."));
	}
	g_free(s);
#else				
	gif->msg_box1(_("Information"), _("This function is only available in the Windows version."));

#endif				
	return 0;
}
