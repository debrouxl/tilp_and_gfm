/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
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


#include <gtk/gtk.h>
#include <stdio.h>

#include "includes.h"

/* Refresh the selection of the clist window */
void clist_selection_refresh(void)
{
  GList *p;
  gint row;

  if(clist_wnd == NULL) return;
  gtk_clist_unselect_all(GTK_CLIST (clist_wnd));
  p=clist_win.selection;
  while(p != NULL)
    {
      row=gtk_clist_find_row_from_data(GTK_CLIST (clist_wnd), p->data);
      if(row==-1)
	{
	  printf("Context debugging:\n");
          printf("Filename: %s\n", ((struct file_info *)(p->data))->filename);
	  fprintf(stderr, "Selection error: please report this bug.\n");
	}
      gtk_clist_select_row(GTK_CLIST (clist_wnd), row, 1);
      p=p->next;
    }

  return;
}

/* Refresh the selection of the ctree window */
void ctree_selection_refresh(void)
{
  GList *p;
  gint row;

  if(ctree_wnd==NULL) return;
  gtk_clist_unselect_all(GTK_CLIST (ctree_wnd));
  p=ctree_win.selection;
  while(p!=NULL)
    {
      row=gtk_clist_find_row_from_data(GTK_CLIST (ctree_wnd), p->data);
      if(row==-1)
	{
	  printf("Context debugging:\n");
          printf("Filename: %s\n", ((struct file_info *)(p->data))->filename);
	  fprintf(stderr, "Selection error: please report this bug.\n");
	}
      gtk_clist_select_row(GTK_CLIST (ctree_wnd), row, 1);
      p=p->next;
    }

  return;
}
