/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
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

/*
	Manage vars/files selections
*/

//#fixme#: change naming scheme because incorrect !
// tilp_selection_delete_local/remote

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tilp_core.h"
#include "dboxes.h"

// -----------------------------

/* Destroy the selection of the local window */
void tilp_clist_selection_destroy(void)
{
	if (local.selection0 != NULL)	// Variables
	{
		g_list_free(local.selection0);
		local.selection0 = NULL;
	}

	if (local.selection1 != NULL)	// Variables
	{
		g_list_free(local.selection1);
		local.selection1 = NULL;
	}

	if (local.selection2 != NULL)	// Applications
	{
		g_list_free(local.selection2);
		local.selection2 = NULL;
	}

	if (local.selection3 != NULL)	// Backups
	{
		g_list_free(local.selection3);
		local.selection3 = NULL;
	}
}

/* Check for files in the list */
int tilp_clist_selection_ready(void)
{
	if (local.selection1 == NULL && local.selection2 == NULL && 1) 
	{
		gif->msg_box1(_("Information"), _
			     ("A file must have been selected in the right window."));
		return 0;
	}

	return !0;
}

void tilp_clist_selection_display(void)
{
	GList *ptr;

	if (local.selection1 == NULL && local.selection2 == NULL && local.selection3)
		return;

	for(ptr = local.selection0; ptr; ptr = ptr->next)
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
	}
	for(ptr = local.selection1; ptr; ptr = ptr->next)
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
	}
	for(ptr = local.selection2; ptr; ptr = ptr->next)
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
	}
	for(ptr = local.selection3; ptr; ptr = ptr->next)
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
	}
}

void tilp_clist_selection_add(const char* filename)
{
	FileEntry* fe = g_malloc0(sizeof(FileEntry));

	fe->name = g_strdup(filename);

	if(tifiles_file_is_regular(fe->name))
		local.selection0 = g_list_prepend(local.selection0, fe);

	else if(tifiles_file_is_flash(fe->name))
		local.selection2 = g_list_prepend(local.selection2, fe);

	else if(tifiles_file_is_backup(fe->name))
		local.selection3 = g_list_prepend(local.selection3, fe);	
}

/* Preload TI variables belonging with the selection */
void tilp_clist_contents_load(void)
{
	GList *ptr;
	int err;

	// Variables
	if (local.selection0 != NULL)
	{
		for(ptr = local.selection0; ptr; ptr = ptr->next)
		{
			FileEntry *f = ptr->data;

			if(tifiles_file_is_regular(f->name) && tifiles_file_is_single(f->name))
			{
				FileEntry *fe = g_memdup(ptr->data, sizeof(FileEntry));

				fe->content1 = tifiles_content_create_regular(options.calc_model);
				err = tifiles_file_read_regular(fe->name, fe->content1);
				if(err)
				{
					tifiles_content_delete_regular(fe->content1);
					fe->content1 = NULL;
				}

				local.selection1 = g_list_append(local.selection1, fe);
			}
			else if(tifiles_file_is_regular(f->name) && tifiles_file_is_group(f->name))
			{
				// explode group files so that we have 1 VarEntry per item (skip/retry/cancel)
				FileContent **dst, **p;
				FileContent *src;

				src = tifiles_content_create_regular(options.calc_model);
				err = tifiles_file_read_regular(f->name, src);
				if(err)
				{
					tifiles_content_delete_regular(src);
					src = NULL;
					break;
				}
				
				tifiles_ungroup_content(src, &dst);
				for(p = dst; *p; p++)
				{
					FileEntry *fe = g_memdup(ptr->data, sizeof(FileEntry));					

					fe->content1 = *p;
				
					local.selection1 = g_list_append(local.selection1, fe);
				}

				tifiles_content_delete_regular(src);
			}
		}

		// replaced "" folder by "main"
		if(!tifiles_has_folder(options.calc_model))
			return;

		for(ptr = local.selection1; ptr; ptr = ptr->next)
		{
			FileEntry *fe = ptr->data;
			FileContent *fc = fe->content1;
			int i;

			if(fc == NULL)
				continue;

			for(i = 0; i < fc->num_entries; i++)
			{
				VarEntry *ve = (fc->entries)[i];

				if(!strcmp(ve->folder , ""))
					strcpy(ve->folder, "main");
			}
		}
	}

	// Applications
	if(local.selection2 != NULL)
	{
		for(ptr = local.selection2; ptr; ptr = ptr->next)
		{
			FileEntry *fe = ptr->data;

			if(tifiles_file_is_flash(fe->name))
			{
				fe->content2 = tifiles_content_create_flash(options.calc_model);
				err = tifiles_file_read_flash(fe->name, fe->content2);
				if(err)
				{
					tifiles_content_delete_flash(fe->content2);
					fe->content2 = NULL;
				}
			}
			/*else if(tifiles_file_is_tigroup(fe->name))
			{
				fe->content3 = tifiles_content_create_tigroup(options.calc_model, 0);
				err = tifiles_file_read_tigroup(fe->name, fe->content3);
				if(err)
				{
					tifiles_content_delete_tigroup(fe->content3);
					fe->content3 = NULL;
				}
			}*/
			else
			{
				fe->content1 = NULL;
			}
		}
	}
}

void tilp_clist_contents_unload(void)
{
	GList *ptr;

	if (local.selection1 != NULL)
	{
		for(ptr = local.selection1; ptr; ptr = ptr->next)
		{
			FileEntry *fe = ptr->data;

			if(fe->content1)
				tifiles_content_delete_regular(fe->content1);
		}
	}

	if (local.selection2 != NULL)
	{
		for(ptr = local.selection2; ptr; ptr = ptr->next)
		{
			FileEntry *fe = ptr->data;

			if(fe->content2)
				tifiles_content_delete_flash(fe->content2);
		}
	}
}

void tilp_clist_change_folder(const char *target)
{
	GList *ptr;

	if (local.selection1 == NULL)
		return;

	for(ptr = local.selection1; ptr; ptr = ptr->next)
	{
		FileEntry *fe = ptr->data;
		FileContent *c = fe->content1;
		int i;

		for(i = 0; i < c->num_entries; i++)
			strcpy(((c->entries)[i])->folder, target);	
	}
}

void tilp_clist_update_varlist(void)
{
	GList *ptr;

	if (local.selection1 == NULL)
		return;

	if((options.calc_model == CALC_TI82) || (options.calc_model == CALC_TI85))
		return;

	for(ptr = local.selection1; ptr; ptr = ptr->next)
	{
		FileEntry *fe = ptr->data;
		FileContent *c = fe->content1;
		int i;

		for(i = 0; i < c->num_entries; i++)
			ticalcs_dirlist_ve_add(remote.var_tree, (c->entries)[i]);
	}
	remote.memory.ram_used = ticalcs_dirlist_ram_used(remote.var_tree);
	remote.memory.flash_used = ticalcs_dirlist_flash_used(remote.var_tree, remote.app_tree);
}

void tilp_clist_update_applist(void)
{
	GList *ptr;

	if (local.selection2 == NULL)
		return;

	if((options.calc_model == CALC_TI82) || (options.calc_model == CALC_TI85))
		return;

	if(!remote.var_tree || !remote.app_tree)
		return;

	for(ptr = local.selection2; ptr; ptr = ptr->next)
	{
		FileEntry *fe = ptr->data;
		FlashContent *c = fe->content2;
#ifdef _MSC_VER
		VarEntry ve = {0};
#else
		VarEntry ve = {};
#endif

		strcpy(ve.name, c->name);
		ve.size = c->data_length;
		ve.type = tifiles_flash_type(calc_handle->model);

		ticalcs_dirlist_ve_add(remote.app_tree, &ve);
	}
	remote.memory.flash_used = ticalcs_dirlist_flash_used(remote.var_tree, remote.app_tree);
}

// -----------------------------

/* Destroy the selection of the remote window */
void tilp_ctree_selection_destroy(void)
{
	if (remote.selection1 != NULL) 
	{
		g_list_free(remote.selection1);
		remote.selection1 = NULL;
	}

	if (remote.selection2 != NULL) 
	{
		g_list_free(remote.selection2);
		remote.selection2 = NULL;
	}
}

int tilp_ctree_selection_ready(void)
{
	if (remote.selection1 == NULL) 
	{
		gif->msg_box1(_("Information"), _
			     ("An item must have been selected in the left window."));
		return 0;
	}
	return !0;
}

int tilp_ctree_selection2_ready(void)
{
	if (remote.selection2 == NULL) 
	{
		gif->msg_box1(_("Information"), _
			     ("An item must have been selected in the left window."));
		return 0;
	}
	return !0;
}

void tilp_ctree_selection_display(void)
{
	GList *ptr;

	if (remote.selection1 == NULL)
		return;

	for(ptr = remote.selection1; ptr; ptr = ptr->next)
	{
		VarEntry *ve = ptr->data;
		printf("<%s>\n", ve->name);
	}
}

// -----------------------------

/* Destroy the selection of the clist window */
void tilp_file_selection_destroy(void)
{
	if (local.file_selection != NULL) 
	{
		g_list_foreach(local.file_selection, (GFunc) g_free, NULL);
		g_list_free(local.file_selection);
		local.file_selection = NULL;
	}
}

/* Add a file to the file_selection (if it does not exist in the list) */
void tilp_file_selection_add(const char *filename)
{
	GList *ptr;

	for(ptr = local.file_selection; ptr; ptr = ptr->next)
	{
		if (!strcmp((char *)ptr->data, filename))
			return;
	}
	local.file_selection = g_list_append(local.file_selection, (gpointer) filename);
}

/* Delete files which are in local.file_selection */
void tilp_file_selection_delete()
{
	GList *ptr;
	gint ret;

	if (local.file_selection == NULL)
		return;

	if(options.overwrite) 
	{
		ret = gif->msg_box2(_("Warning"), _
				    ("Are you sure you want to remove these file(s) ?\n\n"));
		if (ret == BUTTON2)
		return;
	}	

	for(ptr = local.file_selection; ptr; ptr = ptr->next) 
	{
		tilp_file_delete((char *)ptr->data);
	}
}

/* Rename files which are in local.file_selection */
void tilp_file_selection_rename()
{
	gchar *filename;
	GList *ptr;

	if (local.file_selection == NULL)
		return;

	for(ptr = local.file_selection; ptr; ptr = ptr->next)
	{
		gchar *utf8;

		utf8 = gif->msg_entry(_("Rename the file"), _("Name: "), (char *)ptr->data);
		if (utf8 == NULL)
			return;

		filename = g_filename_from_utf8(utf8, -1, NULL, NULL, NULL);
		g_free(utf8);

		if (tilp_file_move((char *)ptr->data, filename) < 0) 
		{
			gif->msg_box1(_("Information"), _
				     ("Unable to rename the file or directory."));
			g_free(filename);
		}
		g_free(filename);
	}
}

// -----------------------------

