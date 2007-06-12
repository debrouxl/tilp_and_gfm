/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  12/08/06 17:12 - labels.c

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "labels.h"

#ifdef __WIN32__
#define snprintf _snprintf
#endif

#define PATH_LEVEL 10

static char* format_path(char *src, char *dst)
{
	char header[5]; // "C:\" as Win32 or "/" as Linux)
	char *path;	// leading path
	char *p;
	int n;
	char *left = NULL;	// left part
	char *right = NULL;	// right part
	char str[8];
	
	// count number of path elements (slashes)
	for(n=0, p=src; ; n++) 
	{
		p = (char *)strchr(p, G_DIR_SEPARATOR);	
		if(!p)
			break;
		p++;
	}

	// Less than 10
	if(n < PATH_LEVEL)
		strcpy(dst, src);
	
	// Clean it up
	else
	{
		// remove header to be platform independant
#ifdef __WIN32__
	  strncpy(header, src, 3);
	  header[3] = '\0';
	  path = &src[3];
#else
	  strcpy(header, "/");
	  path = &src[1];
#endif
		
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
		
		snprintf(str, 8, " (%i)", n);
		strcat(dst, str);

		free(left);
		free(right);
	}
  
	// Return
	return dst;
}

/* Refresh the Labels in the window */
void labels_refresh(void)
{
	/*
  gsize br, bw;
  gchar size[48], num_files[12];
  gchar *utf8_size, *utf8_num_files;
  
  // Parse File Size and place into a string
  if (GFile.file_size < 1024)
    snprintf(size, 48, "File Size: %d bytes", GFile.file_size);
  if (GFile.file_size >= 1024 && GFile.file_size < 1048576)
    snprintf(size, 48, "File Size: %.2f kilobytes", (float)(GFile.file_size / 1024));
  if (GFile.file_size >= 1048576)
    snprintf(size, 48, "File Size: %.2f megabytes", (float)(GFile.file_size / 1048576));

  // Convert number of files to string
  snprintf(num_files, 12, "Files: %d", GFile.num_entries);

  // Convert to UTF-8
  utf8_size = g_locale_to_utf8(size, -1, &br, &bw, NULL);
  utf8_num_files = g_locale_to_utf8(num_files, -1, &br, &bw, NULL);

  // Update labels
  gtk_label_set_text(GTK_LABEL(gfm_widget.group_filesize), utf8_size);
  gtk_label_set_text(GTK_LABEL(gfm_widget.group_files), utf8_num_files);
  */
}