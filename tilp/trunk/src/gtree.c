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
#include <strings.h>

#include "includes.h"

/* Refresh the ctree */
void refresh_ctree()
{
  GdkPixmap *pixmap1, *pixmap2, *pixmap3, *pixmap4, *pixmap5, *pixmap6, *pixmap7;
  GdkBitmap *mask1, *mask2, *mask3, *mask4, *mask5, *mask6, *mask7;
  GtkCTreeNode *tifs_node, *parent_node, *child_node;
  GList *p;
  GtkStyle *style;
  struct varinfo *q;
  gchar *tab[4];
  char buffer[16];
  int i;
  GdkFont *font = NULL;
  GtkWidget *widget = main_wnd;
  gchar *screen[] = { N_("Screen"), "", "" , "" };
  gchar *mem[] = { N_("Memory"), N_(""), N_(""), N_("") };
  gchar *kbd[] = { N_("Keyboard"), N_(""), N_(""), N_("") };
  gchar *tifs[] = { N_("TI variables"), N_(""), N_(""), N_("") };
  tab[1]=NULL;
    
  style = gtk_style_copy(GTK_WIDGET(ctree_wnd)->style);
#if defined(__UNIX__)
  font = gdk_font_load("-lpg-tixx-calc-r-expanded--10-100-75-75-m-80-iso8859-1");
#elif defined(__WIN32__)
  /*
    Thank to Timothy Singer for her fonts. Timothy Singer is the developper 
    of FastLink, another linking program for Windows.
  */
  /*
    switch(options.lp.calc_type)
    {
    case CALC_TI82:
    case CALC_TI83:
    case CALC_TI83P:
    font = gdk_font_load("-*-Fastlink TI%2d83-normal-r-normal--*-13-*-*-m-*-iso8859-1");
    break;
    case CALC_TI85:
    case CALC_TI86:
    font = gdk_font_load("-*-Fastlink TI%2d86-normal-r-normal--*-13-*-*-m-*-iso8859-1");
    break;
    case CALC_TI89:
    case CALC_TI92:
    case CALC_TI92P:
    font = gdk_font_load("-*-Fastlink TI%2d89-normal-r-normal--*-13-*-*-m-*-iso8859-1");
    break;
    }
  */
#endif
  if(font != NULL)
    style->font = font;
  else
    fprintf(stdout, "** Warning: unable to load the TIcalc font. Use default font instead\n");  

  switch(options.ctree_sort)
    {
    case SORT_BY_NAME:
      //sort_cfiles_by_name(ctree_win.varlist);
    case SORT_BY_INFO:
      sort_cfiles_by_info(ctree_win.varlist);
      break;
    case SORT_BY_TYPE:
      sort_cfiles_by_type(ctree_win.varlist);
      break;
    case SORT_BY_SIZE:
      sort_cfiles_by_size(ctree_win.varlist);
      break;
    }

  gtk_clist_freeze(GTK_CLIST (ctree_wnd));
  gtk_clist_clear(GTK_CLIST (ctree_wnd));

  gtk_widget_realize(widget);
  open_xpm("dir_c.xpm", widget, &pixmap1, &mask1);
  open_xpm("dir_o.xpm", widget, &pixmap3, &mask3);
  open_xpm("doc.xpm", widget, &pixmap2, &mask2);
  open_xpm("locked.xpm", widget, &pixmap4, &mask4);
  open_xpm("archived.xpm", widget, &pixmap5, &mask5);
  open_xpm("screen_mini.xpm", widget, &pixmap6, &mask6);
  open_xpm("keyboard_mini.xpm", widget, &pixmap7, &mask7);

  tifs_node=gtk_ctree_insert_node (GTK_CTREE (ctree_wnd), NULL, NULL, screen, 5, 
				   pixmap1, mask1, pixmap6, mask6, FALSE, TRUE);
  gtk_ctree_node_set_row_data (GTK_CTREE(ctree_wnd), tifs_node, (gpointer)NULL);
  gtk_ctree_node_set_selectable(GTK_CTREE(ctree_wnd), tifs_node, 0);

  tifs_node=gtk_ctree_insert_node (GTK_CTREE (ctree_wnd), NULL, NULL, mem, 5, 
				   pixmap1, mask1, pixmap5, mask5, FALSE, TRUE);
  gtk_ctree_node_set_row_data (GTK_CTREE(ctree_wnd), tifs_node, (gpointer)NULL);
  gtk_ctree_node_set_selectable(GTK_CTREE(ctree_wnd), tifs_node, 0);

  tifs_node=gtk_ctree_insert_node (GTK_CTREE (ctree_wnd), NULL, NULL, kbd, 5, 
				   pixmap1, mask1, pixmap7, mask7, FALSE, TRUE);
  gtk_ctree_node_set_row_data (GTK_CTREE(ctree_wnd), tifs_node, (gpointer)NULL);
  gtk_ctree_node_set_selectable(GTK_CTREE(ctree_wnd), tifs_node, 0);

  tifs_node=gtk_ctree_insert_node (GTK_CTREE (ctree_wnd), NULL, NULL, tifs, 5, 
				   pixmap1, mask1, pixmap2, mask2, FALSE, TRUE);
  gtk_ctree_node_set_row_data (GTK_CTREE(ctree_wnd), tifs_node, (gpointer)NULL);
  gtk_ctree_node_set_selectable(GTK_CTREE(ctree_wnd), tifs_node, 0);
  
  p=ctree_win.varlist;
  parent_node=tifs_node;
  //printf("tifs node: %p\n", tifs_node);
  while(p != NULL)
    {
      q=(struct varinfo *)(p->data);
      //printf("--> <%s>\n", q->translate);
      //printf("--> <0x%02x>\n", q->vartype);
      /* Skip varnames with FLASH apps */
      if( (options.lp.calc_type != CALC_TI83P) && 
	  ((q->vartype) ==  ti_calc.tixx_flash(options.lp.calc_type)) )
	{
	  p=p->next;
	  continue;
	}
      //printf("--> <%8s>\n", q->translate);
      tab[0]=(gchar *)g_malloc((strlen(q->translate)+1)*sizeof(gchar));
      strcpy(tab[0], q->translate);
      //printf("<%8s> ", tab[0]);
      sprintf(buffer, "%s", ti_calc.byte2type(q->vartype));
      //printf("<%02X %8s>\n", q->vartype, buffer);
      //if( (q->vartype) == ti_calc.tixx_dir(options.lp.calc_type))
      if(q->is_folder == FOLDER)
	{
	  /*
	  tab[2]=(gchar *)g_malloc((strlen(buffer)+1)*sizeof(gchar));
	  strcpy(tab[2], buffer);
	  */
	  tab[2]=NULL;
	  tab[3]=NULL;
	  parent_node=gtk_ctree_insert_node (GTK_CTREE (ctree_wnd), tifs_node, NULL, tab, 5, 
				 pixmap1, mask1, pixmap3, mask3, FALSE, TRUE);
	  //printf("dir node: %p\n", parent_node);
	  gtk_ctree_node_set_row_data (GTK_CTREE(ctree_wnd), parent_node, (gpointer)q);
	  gtk_ctree_node_set_selectable(GTK_CTREE(ctree_wnd), tifs_node, 0);
	}
      else
	{
	  tab[2]=(gchar *)g_malloc((strlen(buffer)+1)*sizeof(gchar));
	  strcpy(tab[2], buffer);
	  sprintf(buffer, "%u", (int)(q->varsize));
	  tab[3]=(gchar *)g_malloc((strlen(buffer)+1)*sizeof(gchar));
	  strcpy(tab[3], buffer);	  
	  child_node=gtk_ctree_insert_node (GTK_CTREE (ctree_wnd), parent_node, NULL, tab, 5, 
				 pixmap1, mask1, pixmap2, mask2, FALSE, TRUE);
	  //printf("child node: %p\n", child_node);
	  switch(q->varlocked)
	    {
	    case 1:
	      gtk_ctree_node_set_pixmap(GTK_CTREE (ctree_wnd), 
					child_node, 1, pixmap4, mask4);
	      break;
	    case 3:
	      gtk_ctree_node_set_pixmap(GTK_CTREE (ctree_wnd), 
					child_node, 1, pixmap5, mask5);
	      break;
	    }
	  gtk_ctree_node_set_row_data (GTK_CTREE(ctree_wnd), 
				       child_node, (gpointer)q);
	  //#ifdef __UNIX__
	  gtk_ctree_node_set_cell_style(GTK_CTREE(ctree_wnd), 
					child_node, 0, style);
	  //#endif
	}
      
      p=p->next;
      for(i=0; i<4; i++) g_free(tab[i]);
    }

  gdk_pixmap_unref(pixmap1);
  gdk_pixmap_unref(pixmap2);
  gdk_pixmap_unref(pixmap3);
  gdk_pixmap_unref(pixmap4);
  gdk_pixmap_unref(pixmap5);

  gtk_clist_thaw(GTK_CLIST (ctree_wnd));
}



