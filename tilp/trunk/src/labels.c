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

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"

struct clabel_window clabel_win = { 0 };

#ifdef __WIN32__
#define snprintf _snprintf
#endif				/*  */

static char* format(char *src, char *dst)
{
	char header[5];		// "C:\" as Win32 or "/" as Linux)
	char *path;			// leading path
	char *p;
	int n;

	char *left = NULL;	// left part
	char *right = NULL;	// right part

	char str[8];

	// remove header to be platform independant
#ifdef __WIN32__
	strncpy(header, src, 3);
	header[3] = '\0';
	path = &src[3];
#else
	strcpy(header, "/");
	path = &src[1];
#endif
  
	// count number of path elements (slashes)
	for(n = 0, p = src; ; n++) {
		p = (char *)strchr(p, DIR_SEPARATOR_C);	
		if(!p)
			break;
		p++;
	}

	if(n <= 2)
		strcpy(dst, src);
	else {
		left = strdup(path);
		right = strdup(path);

		p = (char *)strchr(left, DIR_SEPARATOR_C);		// first slash (head)
		*p = '\0';

		p = (char *)strrchr(right, DIR_SEPARATOR_C);	// last slash (tail)

		strcpy(dst, header);
		strcat(dst, left);
		strcat(dst, DIR_SEPARATOR_S);
		strcat(dst, "...");
		strcat(dst, p);
		
		snprintf(str, 8, " (%i)", n);
		strcat(dst, str);

		free(left);
		free(right);
	}

	return dst;
}

/* Refresh the info window */
void labels_refresh(void)
{
	gchar buffer[256];
	gsize br, bw;
	gchar *utf8;
	gchar path[256];

	switch (ti_calc.memory) {
	case MEMORY_FREE:
		snprintf(buffer, MAXCHARS, _("Memory free: %u bytes"),
			 ctree_win.memory);
		break;
	case MEMORY_USED:
		snprintf(buffer, MAXCHARS, _("Memory used: %u bytes"),
			 ctree_win.memory);
		break;
	case MEMORY_NONE:
		snprintf(buffer, MAXCHARS, _("Memory used: %s"), _("N/A"));
		break;
	}
	gtk_label_set_text(GTK_LABEL(clabel_win.label21), buffer);
	
	utf8 = g_filename_to_utf8(clist_win.current_dir, -1, &br, &bw, NULL);
	format(utf8, path);
	snprintf(buffer, MAXCHARS, _("Current directory: %s"), path);
	gtk_label_set_text(GTK_LABEL(clabel_win.label22), buffer);
}
