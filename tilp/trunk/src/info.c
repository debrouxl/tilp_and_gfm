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

#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>

#ifdef __MACOSX__
#include <glib/glib.h>
#include <libticables/typedefs.h>
#include <libticalcs/calc_int.h>
#endif

#include "struct.h"

void get_calc_mem_info(struct calc_mem_info *cmi)
{
  GList *p;
  struct varinfo *vi;
  
  p = ctree_win.varlist;

  cmi->vars = 0;
  cmi->folders = 0;
  cmi->mem = 0;
  cmi->archivemem = 0;
  
  cmi->flash = 0;
  cmi->flashmem = 0;
  
  cmi->freemem = 0;
  
// FIXME OS X : ENABLE ONCE LIBTICALCS SUPPORTS IT !
#if 0
  if (p != NULL) // the first item is bogus, for historical reasons
      {
          vi = (struct varinfo *)(p->data);
          
          cmi->freemem = vi->varsize; // but it provides the amount of free memory :)
          
          p = p->next;
      }
#endif
  
  while (p != NULL)
      {
          vi = (struct varinfo *)(p->data);

          if (vi->is_folder)
              {
                  cmi->folders++;
              }
          else
              {
                  if (vi->vartype != ti_calc.tixx_flash(ticalc_get_calc()))
                      {
                          cmi->vars++;
                                            
                          if (vi->varlocked == 3) // variable is archived
                              {
                                  cmi->archivemem += vi->varsize;
                              }
                          else
                              {
                                  cmi->mem += vi->varsize;
                              }
                      }
                  // remember the FLASH apps are listed in all folders... so cmi->folders must not be > 1
                  else if ((vi->vartype == ti_calc.tixx_flash(ticalc_get_calc())) && (cmi->folders == 1))
                      {
                          cmi->flash++;
                      
                          cmi->flashmem += vi->varsize;
                      }
              }
          p = p->next;
      }

    // return mem stats in KiloBytes
    cmi->mem = cmi->mem / 1024;
    cmi->archivemem = cmi->archivemem / 1024;
    cmi->flashmem = cmi->flashmem / 1024;
    cmi->freemem = cmi->freemem / 1024;
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
