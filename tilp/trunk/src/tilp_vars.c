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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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

#ifdef __WIN32__
#include <windows.h>
#define PAUSE(x) Sleep(x)
#else
#include <unistd.h>
#define PAUSE(x) usleep(1000*(x))
#endif

/* Get a dirlist  */
int tilp_dirlist_remote(void)
{
	int err;
	TreeInfo *ti;

	// delete old trees
	ticalcs_dirlist_destroy(&remote.var_tree);
	ticalcs_dirlist_destroy(&remote.app_tree);
	
	// get new trees
	gif->create_pbar_type2(_("Directory list"));
	err = ticalcs_calc_get_dirlist(calc_handle, &remote.var_tree, &remote.app_tree);

	if(tilp_err(err))
	{
		gif->destroy_pbar();
		return -1;
	}
	gif->destroy_pbar();

	// count entries
	remote.memory.n_vars = ticalcs_dirlist_ve_count(remote.var_tree);
	remote.memory.n_apps = ticalcs_dirlist_ve_count(remote.app_tree);

	// get mem used stats
	ti = remote.var_tree->data;
	remote.memory.ram_used = ti->mem_used;
	ti = remote.app_tree->data;
	remote.memory.flash_used = ti->mem_used;
	
	// get mem free stats
	if(ticalcs_calc_features(calc_handle) & FTS_MEMFREE)
	{
		PAUSE(100);	// needed by TI84+/USB
		ticalcs_calc_get_memfree(calc_handle, &remote.memory.ram_free, &remote.memory.flash_free);
	}
	else
	{
		remote.memory.flash_free = -1;
		remote.memory.ram_free = -1;
	}

	ticalcs_dirlist_display(remote.var_tree);
	ticalcs_dirlist_display(remote.app_tree);

	return 0;
}

/* Sorting functions */

#if 0
// use comp_func to sort node siblings
static void sort_nodes(GNode *tree, GCompareFunc comp_func)
{
	int j, k;
	int p = g_node_n_children(tree);

	do
	{
		k = p-1;

		for(j = 1; j <= k; j++)
		{
			GNode *node1 = g_node_nth_child(tree, j);
			GNode *node2 = g_node_nth_child(tree, j+1);

			GNode *tmp_p, *tmp_n;

			if(comp_func(node1->data, node2->data) > 0)
			{
				tmp_p = node1->previous; tmp_n = node1->next;

				tempValue := topDest[j];
				topDest[j] := topDest[j+1];
		        topDest[j+1] := tempValue;
				
				p = j;
			}
		}
	} while(p <= k);
}
#endif

#if 0
static gint sort_by_name(GNode* node, gpointer data)
{
	VarEntry* ve = node->data;
	printf("%p %p %p %p\n", node->next, node->prev, node->parent, node->children);
	if(ve)
		printf("<%s>\n", ve->name);

	return 0;
}
#endif

/* Sort variables by name */
void tilp_vars_sort_by_name(void)
{
	if(ticalcs_calc_features(calc_handle) & FTS_FOLDER)
		return;

	//printf("n = %i\n", g_node_n_children(remote.var_tree->children));
	//g_node_children_foreach((GNode *)remote.var_tree->children, G_TRAVERSE_ALL, sort_by_name, NULL);
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

	else if ((vi->size >= 1024) && (vi->size < 1024 * 1024))
		sprintf(buffer, "%i KB", (int) vi->size >> 10);

	else if (vi->size >= 1024 * 1024)
		sprintf(buffer, "%i MB", (int) vi->size >> 20);

	*buf = g_strdup(buffer);
}

void tilp_vars_translate(char *utf8)
{
#ifdef __WIN32__
	int i;

	// Scan for lowerscript
	for(i = 0; utf8[i] && i < (int)strlen(utf8)-2; i++)
	{
		if((unsigned char)utf8[i+0] == 0xE2)
			if((unsigned char)utf8[i+1] == 0x82)
				if((unsigned char)utf8[i+2] >= 0x80 && 
					(unsigned char)utf8[i+2] <= 0x89)
				{
					int c = (unsigned char)utf8[i+2];

					utf8[i] = utf8[i+2] - 0x80 + '0';
					memmove(utf8+i+1, utf8+i+3, strlen(utf8+i)-2);
					break;
				}
	}

	// Scan for 't'
	for(i = 0; utf8[i] && i < (int)strlen(utf8)-2; i++)
	{
		if((unsigned char)utf8[i+0] == 0xE2)
			if((unsigned char)utf8[i+1] == 0x8A)
				if((unsigned char)utf8[i+2] == 0xBA)
				{
					int c = (unsigned char)utf8[i+2];

					utf8[i] = 't';
					memmove(utf8+i+1, utf8+i+3, strlen(utf8+i)-2);
					break;
				}
	}
#endif
}
