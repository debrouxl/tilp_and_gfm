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

/*
	Manage vars/files selections
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tilp_core.h"
#include "dboxes.h"

// -----------------------------

/* Destroy the selection of the local window */
void tilp_local_selection_destroy(void)
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

	if (local.selection3 != NULL)	// Applications
	{
		g_list_free(local.selection3);
		local.selection3 = NULL;
	}

	if (local.selection4 != NULL)	// Backups
	{
		g_list_free(local.selection4);
		local.selection4 = NULL;
	}

	if (local.selection5 != NULL)	// TiGroups
	{
		g_list_free(local.selection5);
		local.selection5 = NULL;
	}
}

/* Check for files in the list */
int tilp_local_selection_ready(void)
{
	if (local.selection0 == NULL && local.selection2 == NULL &&
		local.selection1 == NULL && local.selection3 == NULL && 1 && local.selection5 == NULL) 
	{
		gif->msg_box1(_("Information"), _
			     ("A file must have been selected in the right window."));
		return 0;
	}

	return !0;
}

void tilp_local_selection_display(void)
{
	GList *ptr;

	if (local.selection1 == NULL && local.selection3 == NULL && local.selection4 == NULL && local.selection5 == NULL)
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
	for(ptr = local.selection4; ptr; ptr = ptr->next)
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
	}
	for(ptr = local.selection5; ptr; ptr = ptr->next)
	{
		FileEntry *fi = ptr->data;
		printf("<%s>\n", fi->name);
	}
}

void tilp_local_selection_add(const char* filename)
{
	FileEntry* fe = g_malloc0(sizeof(FileEntry));

	fe->name = g_strdup(filename);

	if(tifiles_file_is_regular(fe->name))
		local.selection0 = g_list_prepend(local.selection0, fe);

	else if(tifiles_file_is_flash(fe->name))
		local.selection2 = g_list_prepend(local.selection2, fe);

	else if(tifiles_file_is_backup(fe->name))
		local.selection4 = g_list_prepend(local.selection4, fe);	

	else if(tifiles_file_is_tigroup(fe->name))
		local.selection5 = g_list_prepend(local.selection5, fe);
}

/* Preload TI variables belonging with the selection */
void tilp_local_contents_load(void)
{
	GList *ptr;
	int err;

	// TiGroups
	if (local.selection5 != NULL)
	{
		for(ptr = local.selection5; ptr; ptr = ptr->next)
		{
			FileEntry *fe5 = ptr->data;

			if(tifiles_file_is_tigroup(fe5->name))
			{
				TigContent *content = NULL;
				FileContent **p, **contents1 = NULL;
				FlashContent **q, **contents2 = NULL;
				
				content = tifiles_content_create_tigroup(options.calc_model, 0);
				err = tifiles_file_read_tigroup(fe5->name, content);
				if(err)
				{
					tilp_err(err);
					continue;
				}
				err = tifiles_untigroup_content(content, &contents1, &contents2);
				if(err)
				{
					tilp_err(err);
					tifiles_content_delete_tigroup(content);
					continue;
				}
				tifiles_content_delete_tigroup(content);
				
				for(p = contents1; *p; p++)
				{
					FileEntry *fe1 = g_memdup(ptr->data, sizeof(FileEntry));					
					fe1->name = g_memdup(fe1->name, strlen(fe1->name)+1);

					fe1->content1 = *p;
					//g_free(fe1->name);
					//fe1->name = tifiles_build_filename(options.calc_model, (*p)->entries[0]);
				
					local.selection1 = g_list_append(local.selection1, fe1);
				}
				
				for(q = contents2; *q; q++)
				{
					FileEntry *fe3 = g_memdup(ptr->data, sizeof(FileEntry));					
					fe3->name = g_memdup(fe3->name, strlen(fe3->name)+1);

					fe3->content2 = *q;
					/*
					{
						VarEntry ve;
						g_free(fe3->name);
						strcpy(ve.name, (*q)->name);
						ve.type = (*q)->data_type;
						fe3->name = tifiles_build_filename(options.calc_model, &ve);
					}*/					
				
					local.selection3 = g_list_append(local.selection3, fe3);
				}
			}
		}
	}

	// Variables
	if (local.selection0 != NULL)
	{
		for(ptr = local.selection0; ptr; ptr = ptr->next)
		{
			FileEntry *fe0 = ptr->data;

			if(tifiles_file_is_single(fe0->name))
			{
				FileEntry *fe1 = g_memdup(ptr->data, sizeof(FileEntry));

				fe1->content1 = tifiles_content_create_regular(options.calc_model);
				err = tifiles_file_read_regular(fe1->name, fe1->content1);
				if(err)
				{
					tifiles_content_delete_regular(fe1->content1);
					g_free(fe1);
					continue;
				}

				local.selection1 = g_list_append(local.selection1, fe1);
			}
			else if(tifiles_file_is_group(fe0->name))
			{
				// explode group files so that we have 1 VarEntry per item (skip/retry/cancel)
				FileContent **p, **dst = NULL;
				FileContent *src = NULL;

				src = tifiles_content_create_regular(options.calc_model);
				err = tifiles_file_read_regular(fe0->name, src);
				if(err)
				{
					tifiles_content_delete_regular(src);
					continue;
				}
				
				err = tifiles_ungroup_content(src, &dst);
				if(err)
				{
					tifiles_content_delete_regular(src);
					continue;
				}

				for(p = dst; *p; p++)
				{
					FileEntry *fe = g_memdup(ptr->data, sizeof(FileEntry));					

					fe->content1 = *p;
				
					local.selection1 = g_list_append(local.selection1, fe);
				}

				tifiles_content_delete_regular(src);
			}
		}
	}

	// Applications
	if(local.selection2 != NULL)
	{
		for(ptr = local.selection2; ptr; ptr = ptr->next)
		{
			FileEntry *fe2 = ptr->data;

			if(tifiles_file_is_app(fe2->name) || tifiles_file_test(fe2->name, TIFILE_OS, options.calc_model))
			{
				FileEntry *fe3 = g_memdup(ptr->data, sizeof(FileEntry));

				fe3->content2 = tifiles_content_create_flash(options.calc_model);
				err = tifiles_file_read_flash(fe2->name, fe3->content2);
				if(err)
				{
					tifiles_content_delete_flash(fe3->content2);
					g_free(fe3);
					continue;
				}

				local.selection3 = g_list_append(local.selection3, fe3);
			}
		}
	}

	// Reparse variables and change target folder
	if (local.selection1)
	{
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
}

void tilp_local_contents_unload(void)
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

	if (local.selection3 != NULL)
	{
		for(ptr = local.selection3; ptr; ptr = ptr->next)
		{
			FileEntry *fe = ptr->data;

			if(fe->content2)
				tifiles_content_delete_flash(fe->content2);
		}
	}
}

void tilp_local_change_folder(const char *target)
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

void tilp_local_update_varlist(void)
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

void tilp_local_update_applist(void)
{
	GList *ptr;

	if (local.selection3 == NULL)
		return;

	if((options.calc_model == CALC_TI82) || (options.calc_model == CALC_TI85))
		return;

	if(!remote.var_tree || !remote.app_tree)
		return;

	for(ptr = local.selection3; ptr; ptr = ptr->next)
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
void tilp_remote_selection_destroy(void)
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

int tilp_remote_selection_ready(void)
{
	if (remote.selection1 == NULL) 
	{
		gif->msg_box1(_("Information"), _
			     ("An item must have been selected in the left window."));
		return 0;
	}
	return !0;
}

int tilp_remote_selection2_ready(void)
{
	if (remote.selection2 == NULL) 
	{
		gif->msg_box1(_("Information"), _
			     ("An item must have been selected in the left window."));
		return 0;
	}
	return !0;
}

void tilp_remote_selection_display(void)
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

void tilp_file_selection_display(void)
{
	GList *ptr;

	if (local.file_selection == NULL)
		return;

	for(ptr = local.file_selection; ptr; ptr = ptr->next)
	{
		gchar *str = ptr->data;
		printf("<%s>\n", str);
	}
}

// -----------------------------

