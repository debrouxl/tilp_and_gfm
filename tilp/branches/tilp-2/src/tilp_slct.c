/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

/*
	Manage vars/files selections
*/

//#fixme#: change naming scheme because incorrect !
// tilp_selection_delete_local/remote

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tilp_core.h"

/* Destroy the selection of the local window */
void tilp_clist_selection_destroy(void)
{
	if (local.selection != NULL) 
	{
		g_list_free(local.selection);
		local.selection = NULL;
	}
}

/* Check for files in the list */
int tilp_clist_selection_ready(void)
{
	if (local.selection == NULL) 
	{
#ifndef __MACOSX__
		gif->msg_box1(_("Information"), _
			     ("A file must have been selected in the right window."));
#endif /* !__MACOSX__ */
		return 0;
	}
	return !0;
}

#ifndef __MACOSX__
void tilp_clist_selection_display(void)
{
	GList *ptr = local.selection;

	if (local.selection == NULL)
		return;

	while (ptr != NULL) 
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
		ptr = ptr->next;
	}
}
#endif /* !__MACOSX__ */

/* Add a file to the file_selection (if it does not exist in the list) */
void tilp_add_file_to_selection(const char *filename)
{
	local.selection = g_list_append(local.selection, (gpointer) filename);
}

/* Destroy the selection of the clist window */
void tilp_clist_file_selection_destroy(void)
{
	if (local.file_selection != NULL) 
	{
		g_list_foreach(local.file_selection, (GFunc) g_free, NULL);
		g_list_free(local.file_selection);
		local.file_selection = NULL;
	}
}

/* Add a file to the file_selection (if it does not exist in the list) */
void tilp_add_file_to_file_selection(const char *filename)
{
	GList *ptr = local.file_selection;

	while (ptr != NULL) 
	{
		if (!strcmp((char *) ptr->data, filename))
			return;
		ptr = g_list_next(ptr);
	}
	local.file_selection = g_list_append(local.file_selection, (gpointer) filename);
}

#ifndef __MACOSX__
/* Delete files which are in local.file_selection */
void tilp_delete_selected_files()
{
	GList *ptr = local.selection;
	gint ret;

	if (local.selection == NULL)
		return;

	if(options.overwrite) 
	{
		ret = gif->msg_box2(_("Warning"), _
				    ("Are you sure you want to remove these file(s) ?\n\n"));
		if (ret == BUTTON2)
		return;
	}	

	while (ptr != NULL) 
	{
		FileEntry *fi = ptr->data;
		tilp_file_delete(fi->name);
		ptr = ptr->next;
	}

	tilp_dirlist_local();
}

/* Rename files which are in local.file_selection */
void tilp_rename_selected_files()
{
	gchar *filename;
	GList *ptr = local.selection;

	if (local.selection == NULL)
		return;

	while (ptr != NULL) 
	{
		FileEntry *fi = ptr->data;
		printf("<<%s>>\n", fi->name);
		filename =
		    gif->msg_entry(_("Rename the file"), _("Name: "),
				   fi->name);

		if (filename == NULL)
			return;

		if (tilp_file_move(fi->name, filename) < 0) 
		{
			gif->msg_box1(_("Information"), _
				     ("Unable to rename the file or directory."));
			g_free(filename);
		}
		g_free(filename);
		ptr = ptr->next;
	}
}
#endif /* !__MACOSX__ */

/* Preload TI variables belonging with the selection */
void tilp_slct_load_contents(void)
{
	GList *ptr;
	int err;

	if (local.selection == NULL)
		return;

	for(ptr = local.selection; ptr; ptr = ptr->next)
	{
		FileEntry *fe = ptr->data;
		FileContent *c;

		if(tifiles_file_is_regular(fe->name))
		{
			fe->content = c = tifiles_content_create_regular();
			err = tifiles_file_read_regular(fe->name, fe->content);
			if(err)
			{
				tifiles_content_delete_regular(fe->content);
				fe->content = NULL;
			}
			fe->selected = (int *)calloc(c->num_entries + 1, sizeof(int));
		}
		else
		{
			fe->content = NULL;
			free(fe->selected);
		}
	}
}

void tilp_slct_unload_contents(void)
{
	GList *ptr;

	if (local.selection == NULL)
		return;

	for(ptr = local.selection; ptr; ptr = ptr->next)
	{
		FileEntry *fe = ptr->data;

		tifiles_content_delete_regular(fe->content);
	}
}

//-----------

/* Destroy the selection of the remote window */
void tilp_ctree_selection_destroy(void)
{
	if (remote.selection != NULL) 
	{
		g_list_free(remote.selection);
		remote.selection = NULL;
	}

	if (remote.selection2 != NULL) 
	{
		g_list_free(remote.selection2);
		remote.selection2 = NULL;
	}
}

int tilp_ctree_selection_ready(void)
{
	if (remote.selection == NULL) 
	{
#ifndef __MACOSX__
		gif->msg_box1(_("Information"), _
			     ("A variable must have been selected in the left window."));
#endif /* !__MACOSX__ */
		return 0;
	}
	return !0;
}

int tilp_ctree_selection2_ready(void)
{
	if (remote.selection2 == NULL) 
	{
#ifndef __MACOSX__
		gif->msg_box1(_("Information"), _
			     ("A variable must have been selected in the left window."));
#endif /* !__MACOSX__ */
		return 0;
	}
	return !0;
}

void tilp_ctree_selection_display(void)
{
	GList *ptr;

	if (remote.selection == NULL)
		return;

	for(ptr = remote.selection; ptr; ptr = ptr->next)
	{
		VarEntry *ve = ptr->data;

		printf("<%s>\n", ve->name);
	}
}
