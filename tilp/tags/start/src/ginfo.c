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
#include <gtk/gtk.h>

#include "includes.h"
#include "str.h"

char *format(char *s, int max)
{
  gchar buf[MAXCHARS];
  gchar *i=NULL;
  gchar *j=s+strlen(s);

  //fprintf(stdout, "s=<%s>\n", s);
  i = (gchar*)strchr(s, DIR_SEPARATOR_C); // first slash
  //fprintf(stdout, "i=%p\n", i);
  j = (gchar *)strrchr(s, DIR_SEPARATOR_C); // last slash
  //fprintf(stdout, "j=%p\n", j);
  strcpy(buf, j);
  //fprintf(stdout, "buf=<%s>\n", buf);
  if(i == j) return s;
  i = (gchar *)strchr(i+1, DIR_SEPARATOR_C); // second slash
  //fprintf(stdout, "i=%p\n", i);

  *i = '\0';
  strcat(s, DIR_SEPARATOR_S);
  strcat(s, "...");
  strcat(s, buf);
  //fprintf(stdout, "\n");
  return s;
}

/* Refresh the info window */
void refresh_info()
{
  gchar buffer[MAXCHARS];
  gint d=0, v=0;
  longword m=0;
  GtkTooltips *tips = gtk_tooltips_new();

  if(ctree_win.varlist != NULL)
    snprintf(buffer, MAXCHARS, _("Current folder: %s"), ctree_win.cur_folder);
  else
    snprintf(buffer, MAXCHARS, _("Current folder:"));
  gtk_label_set(GTK_LABEL (clabel_win.label11), buffer);

  /*
  p=ctree_win.varlist;
  d=0; v=0; m=0;
  while(p != NULL)
    {
      vi=(struct varinfo *)(p->data);
      //if( (vi->vartype) == ti_calc.tixx_dir(options.lp.calc_type))
      if(vi->is_folder == FOLDER)
	d++;
      else 
	v++;
      m+=(vi->varsize);

      p=p->next;
    }
  */

  number_of_folders_vars_and_mem(&d, &v, &m);
  snprintf(buffer, MAXCHARS, _("Number of folders: %i"), d);
  gtk_label_set(GTK_LABEL (clabel_win.label12), buffer);
  snprintf(buffer, MAXCHARS, _("Number of variables: %i"),v );
  gtk_label_set(GTK_LABEL (clabel_win.label13), buffer);
  snprintf(buffer, MAXCHARS, _("Memory used: %i"), m);
  gtk_label_set(GTK_LABEL (clabel_win.label14), buffer);
  //snprintf(buffer, MAXCHARS, _("Memory selected: %i"), 
  //g_list_length(ctree_win.selection));
  //gtk_label_set(GTK_LABEL (clabel_win.label15), buffer);

  /*
  p=clist_win.dirlist;
  d=0; v=0; m=0; 
  while(p != NULL)
    {
      fi=(struct file_info *)(p->data);
      if( (fi->attrib & S_IFMT) == S_IFDIR ) d++;
      else v++;
      m+=(fi->size);      

      p=p->next;
    }
  d--;
  */

  number_of_directories_vars_and_mem(&d, &v, &m);
  snprintf(buffer, MAXCHARS, _("Current directory: %s"), clist_win.cur_dir);
  gtk_tooltips_set_tip(GTK_TOOLTIPS(tips), clabel_win.label21,
		       "tip_text", "tip_private");
  gtk_label_set(GTK_LABEL (clabel_win.label21), format(buffer, 45));
  snprintf(buffer, MAXCHARS, _("Number of directories: %i"), d);
  gtk_label_set(GTK_LABEL (clabel_win.label22), buffer);
  snprintf(buffer, MAXCHARS, _("Number of files: %i"), v);
  gtk_label_set(GTK_LABEL (clabel_win.label23), buffer);
  snprintf(buffer, MAXCHARS, _("Disk used: %i"), m);
  gtk_label_set(GTK_LABEL (clabel_win.label24), buffer);
  //snprintf(buffer, MAXCHARS, _("Memory selected: %i"), g_list_length(clist_win.selection));
  //gtk_label_set(GTK_LABEL (clabel_win.label25), buffer);
}
