/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  12/10/06 20:39 - group_file.c

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "dialog.h"
#include "file.h"
#include "gui.h"
#include "labels.h"
#include "tilibs.h"
#include "tifiles.h"

GFileStruct GFile;

int	tigfile_create(CalcModel model)
{
	GFile.contents.tigroup = tifiles_content_create_tigroup(model, 0);
	GFile.type = TIFILE_TIGROUP;
  
	return 0;
}

int tigfile_load(const char *filename)
{
	int ret;

	g_free(GFile.filename);
	GFile.filename = g_strdup(filename);

	ret = tifiles_file_read_tigroup(GFile.filename, GFile.contents.tigroup);
	if(ret)
	{
		msgbox_error("Failed to load TiGroup file!");
		tifiles_content_delete_tigroup(GFile.contents.tigroup);
		g_free(GFile.filename);
		return -1;
	}

	return 0;
}

int tigfile_save(const char *filename)
{
	int ret;

	ret = tifiles_file_write_tigroup(GFile.filename, GFile.contents.tigroup);
	if(ret)
	{
		msgbox_error("Failed to save TiGroup file!");
		tifiles_content_delete_tigroup(GFile.contents.tigroup);
		g_free(GFile.filename);
		return -1;
	}

	return 0;
}

int tigfile_destroy(void)
{
	if(GFile.contents.tigroup)
		tifiles_content_delete_tigroup(GFile.contents.tigroup);

	return 0;
}


int	group_create(CalcModel model)
{
	GFile.contents.group = tifiles_content_create_regular(model);
	GFile.type = TIFILE_GROUP;

	return 0;
}

int group_load(const char *filename)
{
	int ret;

	g_free(GFile.filename);
	GFile.filename = g_strdup(filename);

	ret = tifiles_file_read_regular(GFile.filename, GFile.contents.group);
	if(ret)
	{
		msgbox_error("Failed to load Group file!");
		tifiles_content_delete_regular(GFile.contents.group);
		g_free(GFile.filename);
		return -1;
	}

	return 0;
}

int group_save(const char *filename)
{
	int ret;

	ret = tifiles_file_write_regular(GFile.filename, GFile.contents.group, NULL);
	if(ret)
	{
		msgbox_error("Failed to save Group file!");
		tifiles_content_delete_regular(GFile.contents.group);
		g_free(GFile.filename);
		return -1;
	}

	return 0;
}

int group_destroy(void)
{
	if(GFile.contents.group)
		tifiles_content_delete_regular(GFile.contents.group);
    
	return 0;
}
