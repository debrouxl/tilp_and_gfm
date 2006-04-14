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
  This file contains utility functions about variables, sorting routines
  for selection, and conversion routines between dirlist and glists.
  Mainly used by the left window.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tilp_core.h"

/* Get a dirlist  */
int tilp_dirlist_remote(void)
{
	int err;

	// delete old trees
	ticalcs_dirlist_destroy(&remote.var_tree);
	ticalcs_dirlist_destroy(&remote.app_tree);
	
	// get new trees
	gif->create_pbar_type2(_("Directory list"), _("Reading variables"));
	err = ticalcs_calc_get_dirlist(calc_handle, &remote.var_tree, &remote.app_tree);

	if(tilp_err(err))
	{
		gif->destroy_pbar();
		return -1;
	}
	gif->destroy_pbar();

	remote.memory.n_vars = ticalcs_dirlist_num_vars(remote.var_tree);
	remote.memory.n_apps = ticalcs_dirlist_num_vars(remote.app_tree);
	
	remote.memory.ram_used = ticalcs_dirlist_mem_used(remote.var_tree);
	remote.memory.flash_used = ticalcs_dirlist_mem_used(remote.app_tree);

	if(ticalcs_calc_features(calc_handle) & FTS_MEMFREE)
	{
		TreeInfo *info = (TreeInfo *)((remote.var_tree)->data);
		remote.memory.ram_free = info->mem_free;
	}
	else
		remote.memory.ram_free = -1;

	ticalcs_dirlist_display(remote.var_tree);
	ticalcs_dirlist_display(remote.app_tree);

	return 0;
}

/* Sorting functions */
#if 0
static gint sort_by_name(GNode* node, gpointer data)
{
	VarEntry* ve = node->data;

	printf("<%s>\n", ve->name);

	return 0;
}
#endif

void tilp_vars_sort_by_name(void)
{
	if(ticalcs_calc_features(calc_handle) & FTS_FOLDER)
		return;
	//g_node_children_foreach((GNode *)remote.var_tree, G_TRAVERSE_ALL, sort_by_name, NULL);
}

/* Sort variables by attribute */
static gint sort_by_attrib(gconstpointer a, gconstpointer b)
{

	/*
	   VarEntry *fi_a = (VarEntry *)a;
	   VarEntry *fi_b = (VarEntry *)b;

	   if( !strcmp((fi_a->folder)->translate, (fi_b->folder)->translate) && 
	   (fi_a->is_folder != FOLDER) && (fi_b->is_folder != FOLDER) )
	   {
	   if(options.ctree_sort_order == SORT_UP)
	   return (fi_b->varattr - fi_a->varattr);
	   else
	   return (fi_a->varattr - fi_b->varattr);
	   }
	   else
	   return -1;
	 */
	return 0;
}

void tilp_vars_sort_by_info(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_attrib);
}

/* Sort variables by type */
static gint sort_by_type(gconstpointer a, gconstpointer b)
{
	/*
	   VarEntry *fi_a = (VarEntry *)a;
	   VarEntry *fi_b = (VarEntry *)b;

	   if( !strcmp((fi_a->folder)->translate, (fi_b->folder)->translate) &&
	   (fi_a->is_folder != FOLDER) && (fi_b->is_folder != FOLDER) )
	   {
	   if(options.ctree_sort_order == SORT_UP)
	   return (fi_b->vartype - fi_a->vartype);
	   else
	   return (fi_a->vartype - fi_b->vartype);
	   }
	   else
	   return -1;
	 */

	return 0;
}

void tilp_vars_sort_by_type(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_type);
}

/* Sort variables by size */
static gint sort_by_size(gconstpointer a, gconstpointer b)
{
	/*
	   VarEntry *fi_a = (VarEntry *)a;
	   VarEntry *fi_b = (VarEntry *)b;

	   if( !strcmp((fi_a->folder)->translate, (fi_b->folder)->translate) &&
	   (fi_a->is_folder != FOLDER) && (fi_b->is_folder != FOLDER) )
	   {
	   if(options.ctree_sort_order == SORT_UP)
	   return (fi_a->varsize - fi_b->varsize);
	   else
	   return (fi_b->varsize - fi_a->varsize);
	   }
	   else
	   return -1;
	 */

	return 0;
}

void tilp_vars_sort_by_size(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_size);
}

/* Misc */

void tilp_var_get_size(VarEntry* vi, char **buf)
{
	char buffer[256];

	if (vi->size < 1024)
		sprintf(buffer, "  %i", (int) vi->size);

	else if ((vi->size > 1024) && (vi->size < 1024 * 1024))
		sprintf(buffer, "%i KB", (int) vi->size >> 10);

	else if (vi->size > 1024 * 1024)
		sprintf(buffer, "%i MB", (int) vi->size >> 20);

	*buf = g_strdup(buffer);
}
