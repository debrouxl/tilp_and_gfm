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

#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>

#ifdef __MACOSX__
#include <glib/glib.h>
#include <libticables/typedefs.h>
#endif

#include "struct.h"

int number_of_folders_vars_and_mem(int *d, int *v, longword *m)
{
  GList *p;
  struct varinfo *vi;
  
  p=ctree_win.varlist;
  *d=0; *v=0; *m=0;
  while(p != NULL)
    {
      vi=(struct varinfo *)(p->data);
      //if( (vi->vartype) == ti_calc.tixx_dir(options.lp.calc_type))
      if(vi->is_folder == FOLDER)
	(*d)++;
      else 
	(*v)++;
      (*m) += (vi->varsize);

      p=p->next;
    }
  
  return 0;
}

int number_of_directories_vars_and_mem(int *d, int *v, longword *m)
{
  GList *p;
  struct file_info *fi;

  p=clist_win.dirlist;
  *d=0; *v=0; *m=0; 
  while(p != NULL)
    {
      fi=(struct file_info *)(p->data);
      if( (fi->attrib & S_IFMT) == S_IFDIR ) (*d)++;
      else (*v)++;
      (*m) += (fi->size);      

      p=p->next;
    }
  (*d)--;

  return 0;
}
