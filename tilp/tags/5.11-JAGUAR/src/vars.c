/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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
  This file contains utility functions about vars, 
  sorting routines for selection, conversion routines between dirlist
  and glists.
  Mainly used by the left window.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
//#include <dirent.h>
//#include <unistd.h>

#ifndef __MACOSX__
#include <glib.h>
#include "platform.h"
#else
#include <glib/glib.h>
#endif

#include "struct.h"
#include "defs.h"
#include "intl.h"
#include "gui_indep.h"
#include "error.h"


/*********************/
/* Convert functions */
/*********************/

void display_varlist(TicalcVarInfo *varlist)
{
  int i;
  TicalcVarInfo *ptr;

  ptr=varlist;
  while(ptr != NULL)
    {
      for(i=0; i<8; i++)
	{
	  if(isprint((ptr->varname)[i]))
	    fprintf(stdout, "%c", (ptr->varname)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, "|");
      for(i=0; i<8; i++)
	{
	  fprintf(stdout, "%02X", (byte)(ptr->varname)[i]);
	}
      fprintf(stdout, "¦");
      for(i=0; i<8; i++)
	{
	  if(isprint((ptr->translate)[i]))
	    fprintf(stdout, "%c", (ptr->translate)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, "|");
      fprintf(stdout, "%i  ", (int)(ptr->varattr));
      fprintf(stdout, "|");
      fprintf(stdout, "%02X ", ptr->vartype);
      fprintf(stdout, "|");
      fprintf(stdout, "%08X ", ptr->varsize);
      fprintf(stdout, "|");
      fprintf(stdout, "%s", (ptr->folder)->varname);
      fprintf(stdout, "\n");

      ptr=ptr->next;
    }
}

void display_dirlist()
{
  GList *ptr = ctree_win.varlist;
  int i;

  fprintf(stdout, _("Name    |Name bin        |Name tr |Lk|Ty|Size     |Parent\n"));
  while(ptr != NULL)
    {
      TicalcVarInfo *vi = ptr->data;

      for(i=0; i<8; i++)
	{
	  if(isprint((vi->varname)[i]))
	    fprintf(stdout, "%c", (vi->varname)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, " ");
      for(i=0; i<8; i++)
	{
	  fprintf(stdout, "%02X", (byte)(vi->varname)[i]);
	}
      fprintf(stdout, " ");
      for(i=0; i<8; i++)
	{
	  if(isprint((vi->translate)[i]))
	    fprintf(stdout, "%c", (vi->translate)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, " ");
      fprintf(stdout, "%i  ", (int)(vi->varattr));
      fprintf(stdout, "%02X ", vi->vartype);
      fprintf(stdout, "%08X ", vi->varsize);
      fprintf(stdout, "%s\n", (vi->folder)->varname);

      ptr = g_list_next(ptr);
    }
}

/* 
   Convert the TicalcVarInfo list supplied by calc_directorylist into a GList
*/ 
void varlist_to_glist(TicalcVarInfo varlist)
{
  TicalcVarInfo *p;

  /* Free the previous list */
  if(ctree_win.varlist != NULL)
    {
      g_list_foreach(ctree_win.varlist, (GFunc) g_free, NULL);
      g_list_free(ctree_win.varlist);
      ctree_win.varlist=NULL;
    }
  strcpy(ctree_win.cur_folder, varlist.varname);
  ctree_win.memory = varlist.varsize;
  
  p = &varlist;
  p = p->next;
  while(p != NULL)
    {
      ctree_win.varlist = g_list_append(ctree_win.varlist, 
					(gpointer)p);
      p = p->next;
    }
}

/* 
   Convert a GList (a directory list or a selection) into a struct 
   varinfo list such as the same supplied by calc_directorylist but 
   without the first element.
   Remove also the last folder if it is empty (else group will send 'bit time out').
*/ 
TicalcVarInfo *glist_to_varlist(GList *glist)
{
  GList *ptr;
  TicalcVarInfo *v;
  TicalcVarInfo *p;
  TicalcVarInfo varlist;
  
  ptr=glist;
  p=&varlist;
  p->next = NULL;
  if(ptr == NULL) return NULL;
  while(ptr != NULL)
    {
      /* Get element */
      v=(TicalcVarInfo *)ptr->data;
      printf("Varname: %s, vartype: %s\n", v->varname, ti_calc.byte2type(v->vartype));
      printf("Parent folder: %s\n", (v->folder)->varname);

      /* If the LAST element is just a folder, skip it */
      if( (v->is_folder == FOLDER) && (ptr->next == NULL) )
		break;

      /* Allocate a new structure */
      (p->next) = (TicalcVarInfo *)g_malloc(sizeof(TicalcVarInfo));
      p=p->next;
      p->next = NULL;

      /* Copy the structure */
      strcpy(p->varname, v->varname);
      p->vartype=v->vartype;
      p->varattr=v->varattr;
      p->varsize=v->varsize;
      strcpy(p->translate, v->translate);
      p->folder=v->folder;

      ptr=ptr->next;
    }

  return varlist.next;
}

void free_varlist(TicalcVarInfo *vlist)
{
  TicalcVarInfo *p, *q;

  p=vlist;
  do
    {
      q=p->next;
	  //printf("free: varname=%s\n", p->varname);
      g_free(p); // a bug ?!
      p=q;
    }
  while(p != NULL);
}

/* 
   This function generates the header of the TI file when a group
   is received.
*/
void generate_group_file_header(FILE *file, int mask_mode, 
				const char *id, TicalcVarInfo *v, 
				int calc_type)
{
  TicalcVarInfo *vi;

  vi = glist_to_varlist(ctree_win.selection);
  //display_dirlist(vi);
  ti_calc.generate_group_file_header(file, mask_mode, id, vi, 
				     options.lp.calc_type);
  free_varlist(vi);

  return;

}


/*********************/
/* Sorting functions */
/*********************/

/* Sort variables by name */
static gint GCompareCalculatorNames (gconstpointer a, gconstpointer b)
{
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
}

void sort_cfiles_by_name(GList *list)
{
  g_list_sort(list, GCompareCalculatorNames);
}

/* Sort variables by attribute */
static gint GCompareCalculatorAttributes (gconstpointer a, gconstpointer b)
{
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
}

void sort_cfiles_by_info(GList *list)
{
  g_list_sort(list, GCompareCalculatorAttributes);
}

/* Sort variables by type */
static gint GCompareCalculatorTypes (gconstpointer a, gconstpointer b)
{
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
}

void sort_cfiles_by_type(GList *list)
{
  g_list_sort(list, GCompareCalculatorTypes);
}

/* Sort variables by size */
static gint GCompareCalculatorSizes (gconstpointer a, gconstpointer b)
{
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
}

void sort_cfiles_by_size(GList *list)
{
  g_list_sort(list, GCompareCalculatorSizes);
}
