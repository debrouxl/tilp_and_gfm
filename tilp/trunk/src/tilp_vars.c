/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
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

#include "tilibs.h"
#include "tilp_core.h"

/*********************/
/* Directory listing */
/*********************/

/* Convert a dirlist v1 into two dirlists v2 */
/* Beware: tree is no longer valid !!! */
#ifdef DIRLIST_TRANS
static void dirlist_v1_to_v2(TNode * tree, TNode ** vars, TNode ** apps)
{
	TNode *var_node, *app_node;

	var_node = t_node_nth_child(tree, 0);
	var_node->data = strdup(VAR_NODE_NAME); // so that it can be freed !

	app_node = t_node_nth_child(tree, 1);
	app_node->data = strdup(APP_NODE_NAME);

	t_node_unlink(var_node);
	t_node_unlink(app_node);
	t_node_destroy(tree);

	*vars = var_node;
	*apps = app_node;
}
#endif				/* DIRLIST_TRANS */

/* Get a dirlist (currently v1; should be switched soon) */
int tilp_dirlist_remote(void)
{
	uint32_t mem;

#if defined(DIRLIST_FORM1)
	// delete old tree  
	ticalc_dirlist_destroy(&ctree_win.dirlist);

	// get new tree
	gif->create_pbar_type2(_("Directory list"),
			       _("Reading variables"));
	if (tilp_error(ti_calc.directorylist(&ctree_win.dirlist, &mem))) {
		gif->destroy_pbar();
		return -1;
	}
#elif defined(DIRLIST_TRANS)    /* DIRLIST_FORM1 */
	// delete old trees
	ticalc_dirlist_destroy(&ctree_win.var_tree);
	ticalc_dirlist_destroy(&ctree_win.app_tree);

	// get new tree
	gif->create_pbar_type2(_("Directory list"),
			       _("Reading variables"));
	if (tilp_error(ti_calc.directorylist(&ctree_win.dirlist, &mem))) {
		gif->destroy_pbar();
		return -1;
	}
#elif defined(DIRLIST_FORM2)    /* DIRLIST_TRANS */
	// delete old trees
	ticalc_dirlist_destroy(&ctree_win.var_tree);
	ticalc_dirlist_destroy(&ctree_win.app_tree);
	
	// get new trees
	gif->create_pbar_type2(_("Directory list"),
			       _("Reading variables"));
	if (tilp_error(ti_calc.directorylist2(&ctree_win.var_tree, 
					      &ctree_win.app_tree,
					      &mem))) {
		gif->destroy_pbar();
		return -1;
	}

#endif                          /* DIRLIST_FORM2 */
	ctree_win.memory = mem;
	gif->destroy_pbar();

#if defined(DIRLIST_FORM1)
	ticalc_dirlist_display(ctree_win.dirlist);
#elif defined(DIRLIST_TRANS)    /* DIRLIST_FORM1 */
	dirlist_v1_to_v2(ctree_win.dirlist, 
			 &ctree_win.var_tree,
			 &ctree_win.app_tree);
	ticalc_dirlist_display(ctree_win.var_tree);
	ticalc_dirlist_display(ctree_win.app_tree);
#elif defined(DIRLIST_FORM2)    /* DIRLIST_TRANS */
	ticalc_dirlist_display(ctree_win.var_tree);
	ticalc_dirlist_display(ctree_win.app_tree);
#endif				/* DIRLIST_FORM2 */
	return 0;
}


/*********************/
/* Sorting functions */
/*********************/

/* Sort variables by name */
gint GCompareCalculatorNames(gconstpointer a, gconstpointer b)
{

	/*
	   TicalcVarInfo *fi_a = (TicalcVarInfo *)a;
	   TicalcVarInfo *fi_b = (TicalcVarInfo *)b;

	   if( !strcmp((fi_a->folder)->translate, (fi_b->folder)->translate) && 
	   (fi_a->is_folder != FOLDER) && (fi_b->is_folder != FOLDER) )
	   {
	   if(options.ctree_sort_order == SORT_UP)
	   return strcmp(fi_b->translate, fi_a->translate);
	   else
	   return strcmp(fi_a->translate, fi_b->translate);
	   }
	   else
	   return -1;
	 */
	return 0;
}
void tilp_sort_vars_by_name(void)
{

	//g_list_sort(ctree_win., GCompareCalculatorNames);
}

/* Sort variables by attribute */
gint GCompareCalculatorAttributes(gconstpointer a, gconstpointer b)
{

	/*
	   TicalcVarInfo *fi_a = (TicalcVarInfo *)a;
	   TicalcVarInfo *fi_b = (TicalcVarInfo *)b;

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
void tilp_sort_vars_by_info(void)
{
	g_list_sort(clist_win.dirlist, GCompareCalculatorAttributes);
}

/* Sort variables by type */
static gint GCompareCalculatorTypes(gconstpointer a, gconstpointer b)
{

	/*
	   TicalcVarInfo *fi_a = (TicalcVarInfo *)a;
	   TicalcVarInfo *fi_b = (TicalcVarInfo *)b;

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
void tilp_sort_vars_by_type(void)
{
	g_list_sort(clist_win.dirlist, GCompareCalculatorTypes);
}

/* Sort variables by size */
static gint GCompareCalculatorSizes(gconstpointer a, gconstpointer b)
{

	/*
	   TicalcVarInfo *fi_a = (TicalcVarInfo *)a;
	   TicalcVarInfo *fi_b = (TicalcVarInfo *)b;

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
void tilp_sort_vars_by_size(void)
{
	g_list_sort(clist_win.dirlist, GCompareCalculatorSizes);
}

/********/
/* Misc */
/********/

/*
  Returns the var size
*/
void tilp_var_get_size(TiVarEntry * vi, char **buf)
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
