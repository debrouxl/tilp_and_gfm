/*  ti_link - link program for TI calculators
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
#include <glib.h>

#include "includes.h"

struct clist_window clist_win;

/* Refresh the clist */
void refresh_clist()
{
  GdkPixmap *pixmap1, *pixmap2;
  GdkBitmap *mask1, *mask2;
  GdkPixmap *pixmap;
  GdkBitmap *mask;
  GtkWidget *pixmapwid;
  GtkStyle *style;
  GdkFont *font = NULL;
  GtkWidget *widget = main_wnd;

  char *row_text[7];
  int i;
  char buffer[MAXCHARS];
  int row=0;
  struct file_info *fi;
  GList *dirlist;
#ifdef __WIN32__
  gchar *utf8 = NULL;	// Unicode-8
#endif
  
  style = gtk_style_copy(GTK_WIDGET(clist_wnd)->style);
  font = gdk_font_load(options.right_font_name);
  /*
    #if defined(__UNIX__)
    //font = gdk_font_load("-adobe-courier-medium-r-*-*-*-125-*-*-*-*-*-*");
    #elif defined(__WIN32__)
    //font = gdk_font_load("-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
    #endif
  */
  if(font != NULL)
    style->font = font;
  else
    fprintf(stdout, "** Warning: unable to load the fixed font. Use default font instead\n");  
  
  gtk_clist_freeze((GtkCList *)clist_wnd);
  gtk_clist_clear((GtkCList *)clist_wnd);
  // disabled !
  /*
  gtk_signal_handler_block_by_func(GTK_OBJECT (clist_wnd), clist_select_row, NULL);
  */
  switch(options.clist_sort)
    {
    case SORT_BY_NAME:
      sort_lfiles_by_name(clist_win.dirlist);
      break;
    case SORT_BY_DATE:
      sort_lfiles_by_date(clist_win.dirlist);
      break;
    case SORT_BY_SIZE:
      sort_lfiles_by_size(clist_win.dirlist);
      break;
    case SORT_BY_USER:
      sort_lfiles_by_user(clist_win.dirlist);
      break;
    case SORT_BY_GROUP:
      sort_lfiles_by_group(clist_win.dirlist);
      break;
    case SORT_BY_ATTRB:
      sort_lfiles_by_attrib(clist_win.dirlist);
      break; 
    }

  pixmapwid = gtk_clist_get_column_widget (GTK_CLIST (clist_wnd), 0);
  gtk_widget_destroy (pixmapwid);
  
  if(options.clist_sort_order)
    {
      clist_win.dirlist=g_list_reverse(clist_win.dirlist);
      pixmapwid = create_pixmap(widget, "down.xpm");
      //open_xpm ("down.xpm", widget, &pixmap, &mask);
      gtk_clist_set_column_widget (GTK_CLIST (clist_wnd), 0, pixmapwid);
    }
  else
    {
      pixmapwid = create_pixmap(widget, "up.xpm");
      //gtk_widget_show(pixmapwid);
      gtk_clist_set_column_widget (GTK_CLIST (clist_wnd), 0, pixmapwid);
    }
  
  open_xpm("dir.xpm", widget, &pixmap1, &mask1);
  open_xpm("doc.xpm", widget, &pixmap2, &mask2);
  open_xpm("dotdot.xpm", widget, &pixmap, &mask);

  dirlist=clist_win.dirlist;
  while(dirlist!=NULL)
    {
      fi=dirlist->data;
      for(i=0; i<7; i++) { row_text[i]=NULL; }

#ifdef __LINUX__
      row_text[1]=(char *)g_malloc((strlen(fi->filename)+1)*sizeof(char));
      strcpy(row_text[1], fi->filename);
#else // WIN32
      // Use Unicode for char such as "é, à, ..."
      utf8 = g_filename_to_utf8(fi->filename, NULL);
      row_text[1]=(char *)g_malloc((strlen(utf8)+1)*sizeof(char));
      strcpy(row_text[1], utf8);
      g_free(utf8);
#endif
      get_date(*fi, &row_text[2]);
      sprintf(buffer, "%ld", fi->size);
      row_text[3]=(char *)g_malloc((strlen(buffer)+1)*sizeof(char));
      strcpy(row_text[3], buffer);
      get_user_name(*fi, &row_text[4]);
      get_group_name(*fi, &row_text[5]);
      row_text[6]=get_attributes(*fi);
      gtk_clist_append((GtkCList *)clist_wnd, row_text);
      gtk_clist_set_row_data(GTK_CLIST (clist_wnd), row, (gpointer)fi);
      gtk_clist_set_row_style((GtkCList *)clist_wnd, row, style);       

      if(row_text[6][1]=='d' && strcmp(fi->filename, ".."))
	{
	  gtk_clist_set_pixmap((GtkCList *)clist_wnd, row, 0, pixmap1, mask1);
	  gtk_clist_set_selectable(GTK_CLIST (clist_wnd), row, FALSE);
	}      
      else if(strcmp(fi->filename, ".."))
	{
	  gtk_clist_set_pixmap((GtkCList *)clist_wnd, row, 0, pixmap2, mask2);
	}
      else
	{
	  gtk_clist_set_pixmap((GtkCList *)clist_wnd, row, 0, pixmap, mask);
	  gtk_clist_set_selectable(GTK_CLIST (clist_wnd), row, FALSE);
	}
      row++;
      for(i=0; i<7; i++) { g_free(row_text[i]); }

      dirlist=dirlist->next;
    }
  clist_selection_refresh();
  // disabled !
  /*
  gtk_signal_handler_unblock_by_func(GTK_OBJECT (clist_wnd), clist_select_row, NULL);
  */
  gtk_clist_thaw((GtkCList *)clist_wnd);
  gdk_pixmap_unref(pixmap);
  gdk_pixmap_unref(pixmap1);
  gdk_pixmap_unref(pixmap2);

}
