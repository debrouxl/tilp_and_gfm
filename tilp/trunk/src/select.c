/*  tilp - link program for TI calculators
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

#include <stdio.h>

#include "struct.h"

/* Destroy the selection of the clist window */
void clist_selection_destroy(void)
{
  if(clist_win.selection != NULL)
    {
      g_list_free(clist_win.selection);
      clist_win.selection=NULL;
    }

  return;
}

/* Destroy the selection of the ctree window */
void ctree_selection_destroy(void)
{
//printf("<<%p>>\n", ctree_win.selection);
  if(ctree_win.selection != NULL)
    {
      g_list_free(ctree_win.selection);
      ctree_win.selection=NULL;
    }

  return;
}
