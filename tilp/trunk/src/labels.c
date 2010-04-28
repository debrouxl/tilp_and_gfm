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
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"

struct label_window label_wnd = { 0 };

#define PATH_LEVEL	10

static char* format_path(char *src, char *dst)
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
	for(n = 0, p = src; ; n++) 
	{
		p = (char *)strchr(p, G_DIR_SEPARATOR);	
		if(!p)
			break;
		p++;
	}

	if(n < PATH_LEVEL)
		strcpy(dst, src);
	else {
		left = strdup(path);
		right = strdup(path);

		p = (char *)strchr(left, G_DIR_SEPARATOR);		// first slash (head)
		*p = '\0';

		p = (char *)strrchr(right, G_DIR_SEPARATOR);	// last slash (tail)

		strcpy(dst, header);
		strcat(dst, left);
		strcat(dst, G_DIR_SEPARATOR_S);
		strcat(dst, "...");
		strcat(dst, p);
		
		g_snprintf(str, 8, " (%i)", n);
		strcat(dst, str);

		free(left);
		free(right);
	}

	return dst;
}

extern const char* format_bytes(unsigned long value);

/* Refresh the info window */
void labels_refresh(void)
{
	gsize br, bw;
	gchar *utf8;
	gchar path[1024];
	gchar *str, *str1, *str2;

	if(working_mode & MODE_CMD)
		return;

	/* path */
	utf8 = g_filename_to_utf8(local.cwdir, -1, &br, &bw, NULL);
	format_path(utf8, path);
	g_free(utf8);
	gtk_label_set_text(GTK_LABEL(label_wnd.label21), path);

	/* RAM used */
	str1 = g_strdup(format_bytes(remote.memory.ram_used));
	str = g_strdup_printf(_("used: %s"), str1);
	gtk_label_set_text(GTK_LABEL(label_wnd.label11), str);
	
	g_free(str1);
	g_free(str);

	/* RAM free */
	str2 = g_strdup(format_bytes(remote.memory.ram_free));

	if(remote.memory.ram_free == -1U)
		str = g_strdup_printf(_("free: N/A"));
	else
		str = g_strdup_printf(_("free: %s"), str2);
	gtk_label_set_text(GTK_LABEL(label_wnd.label13), str);

	g_free(str2);
	g_free(str);

	/* FLASH used */
	str1 = g_strdup(format_bytes(remote.memory.flash_used));
	str = g_strdup_printf(_("used: %s"), str1);
	gtk_label_set_text(GTK_LABEL(label_wnd.label12), str);

	g_free(str1);
	g_free(str);

	/* FLASH free */
	str2 = g_strdup(format_bytes(remote.memory.flash_free));

	if(remote.memory.flash_free == -1U)
		str = g_strdup_printf(_("free: N/A"));
	else
		str = g_strdup_printf(_("free: %s"), str2);
	gtk_label_set_text(GTK_LABEL(label_wnd.label14), str);
}
