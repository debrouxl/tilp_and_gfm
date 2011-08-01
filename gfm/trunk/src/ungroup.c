/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_misc.c 3061 2006-11-10 23:57:23Z kevinkofler $ */

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
#include <glib.h>

#include "ungroup.h"
#include "dialog.h"
#include "support.h"
#include "file.h"
#include "tilibs.h"

int gfm_tifiles_ungroup(const char *filename, int type)
{
	gchar *dirname = g_path_get_dirname(filename);
	gchar *basename = g_path_get_basename(filename);
	
	gchar *src_file;
	gchar *dst_file;
	
	gchar *folder, *tmp;
	gchar *input;	
	gchar *e;
	int err = 0;

	// Ask for folder
	folder = g_strdup(basename);
	e = strrchr(folder, '.');
	if(e) *e = '\0';

	input = msgbox_input(_("Create new directory"), folder, _("Directory where files will be ungrouped: "));
	g_free(folder);
	if (input == NULL)
		return -1;

	tmp = g_filename_from_utf8(input, -1, NULL, NULL, NULL);
	g_free(input);

	folder = g_strconcat(dirname, G_DIR_SEPARATOR_S, tmp, NULL);
	g_free(tmp);

	// Check for folder existence
	if(!strcmp(dirname, ".") || !strcmp(dirname, ""))
	{
		msgbox_one(MSGBOX_ERROR, _("You can't ungroup in this folder."));
		g_free(basename);
		g_free(dirname);
		return -1;
	}
   
	// Create folder
	if(file_mkdir(folder))
	{
		g_free(basename);
		g_free(dirname);
		return -1;
	}
	file_chdir(folder);

	// Copy file to target
	src_file = g_strdup(filename);	
	dst_file = g_strconcat(folder, G_DIR_SEPARATOR_S, basename, NULL);
	file_copy(src_file, dst_file);
	
	// Ungroup
	if(type == TIFILE_GROUP)
		err = tifiles_ungroup_file(dst_file, NULL);
	else if(type == TIFILE_TIGROUP)
		err = tifiles_untigroup_file(dst_file, NULL);
	if(err)
	{
		gchar *str;

		tifiles_error_get(err, &str);
		msgbox_one(MSGBOX_ERROR, str);
		g_free(str);
	}
	file_chdir("..");

	// And release
	g_free(basename);
	g_free(dirname);
	g_free(src_file);
	g_free(dst_file);

	return 0;
}

int gfm_tifiles_group(const char **filenames, int type)
{
	char **ptr;
	gchar *input;
	gchar *target = NULL;
	gchar *dirname = g_path_get_dirname(filenames[0]);
	//	gchar *basename = g_path_get_basename(filenames[0]);
	int err = 0;

	// Check for selection consistency
	for(ptr = (char **)filenames; *ptr; ptr++)
	{
		if(tifiles_file_is_group(*ptr) || tifiles_file_is_tigroup(*ptr))
		{
			msgbox_one(MSGBOX_ERROR, _("Group files are not allowed in selection."));
			return -1;
		}

		if(tifiles_file_is_flash(*ptr) && type != TIFILE_TIGROUP)
		{
			msgbox_one(MSGBOX_ERROR, _("FLASH files are not allowed in group files."));
			return -1;
		}
	}

	// Ask for group name
	input = msgbox_input(_("Group files"), "group", _("Group name: "));
	if(input == NULL)
		return -1;

	// And group
	if(type == TIFILE_GROUP)
	{
		target = g_strconcat(dirname, G_DIR_SEPARATOR_S, input,	".", 
			tifiles_fext_of_group(tifiles_file_get_model(filenames[0])), NULL);
		g_free(input);

		err = tifiles_group_files((char **)filenames, target);
	}
	else if(type == TIFILE_TIGROUP)
	{
		target = g_strconcat(dirname, G_DIR_SEPARATOR_S, input,	".tig", NULL);
		g_free(input);

		err = tifiles_tigroup_files((char **)filenames, target);
	}

	if(err)
	{
		gchar *str;

		tifiles_error_get(err, &str);
		msgbox_one(MSGBOX_ERROR, str);
		g_free(str);
	}
	g_free(target);

	return 0;
}
