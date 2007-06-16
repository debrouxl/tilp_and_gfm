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

/*
	Manage refresh of labels.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "labels.h"
#include "groups.h"

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

void labels_set_model(CalcModel model)
{
	gtk_label_set_text(GTK_LABEL(gfm_widget.model),
		tifiles_model_to_string(model));
}

void labels_set_entries(int n)
{
	gchar *str;
	
	str = g_strdup_printf("%i", n);
	gtk_label_set_text(GTK_LABEL(gfm_widget.entries), str);
	g_free(str);
}

void labels_set_comment(const char* comment)
{
	gtk_label_set_text(GTK_LABEL(gfm_widget.comment), comment);
}

void labels_set_ram(uint32_t ram)
{
	gchar *str;

	if (ram < 1024)
		str = g_strdup_printf("%d bytes", ram);
	if (ram >= 1024 && ram < 1048576)
		str = g_strdup_printf("%.2f kilobytes", (float)(ram / 1024));
	if (ram >= 1048576)
		str = g_strdup_printf("%.2f megabytes", (float)(ram / 1048576));

	gtk_label_set_text(GTK_LABEL(gfm_widget.ram), str);
	g_free(str);
}

void labels_set_flash(uint32_t flash)
{
	gchar *str;

	if (flash < 1024)
		str = g_strdup_printf("%d bytes", flash);
	if (flash >= 1024 && flash < 1048576)
		str = g_strdup_printf("%.2f kilobytes", (float)(flash / 1024));
	if (flash >= 1048576)
		str = g_strdup_printf("%.2f megabytes", (float)(flash / 1048576));

	gtk_label_set_text(GTK_LABEL(gfm_widget.flash), str);
	g_free(str);
}

void labels_refresh(void)
{
	int n;
	int ram;
	int flash;

	n = ticalcs_dirlist_ve_count((TNode *)GFile.trees.vars) +
		ticalcs_dirlist_ve_count((TNode *)GFile.trees.apps);
	ram = ticalcs_dirlist_ram_used((TNode *)GFile.trees.vars);
	flash = ticalcs_dirlist_flash_used((TNode *)GFile.trees.vars, (TNode *)GFile.trees.apps);

	labels_set_model(GFile.model);
	labels_set_entries(n);
	labels_set_comment(GFile.contents.group->comment);
	labels_set_ram(ram);
	labels_set_flash(flash);
}