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

#ifndef GSTRUCT_H
#define GSTRUCT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

//extern struct link_cable link_cable;
//extern struct ti_calc ti_calc;
extern struct ticalc_info_update info_update;

/* The main window */
extern GtkWidget *main_window;
extern GtkWidget *main_wnd;
extern GtkWidget *clist_wnd;
extern GtkWidget *ctree_wnd;

/* This struct is used by the toolbar */
extern struct toolbar_window
{
  GtkWidget *toolbar;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *button4;
  GtkWidget *button5;
  GtkWidget *button6;
  GtkWidget *button7;
  GtkWidget *button8;
  GtkWidget *button9;
  GtkWidget *button10;
  GtkWidget *button11;
} toolbar_win;

/* This struct is used by the CLabel window */
extern struct clabel_window
{
  GtkWidget *widget;
  GtkWidget *label11;
  GtkWidget *label12;
  GtkWidget *label13;
  GtkWidget *label14;
  GtkWidget *label15;
  GtkWidget *label21;
  GtkWidget *label22;
  GtkWidget *label23;
  GtkWidget *label24;
  GtkWidget *label25;
} clabel_win;

/* This struct is used to display and manage the progress bar dialog box */
extern struct progress_window
{
  GtkWidget *window;
  GtkWidget *pbar;
  GtkWidget *pbar2;
  GtkWidget *label;
  GtkWidget *label2;
  GtkWidget *label_rate;
} p_win;


/* Used by the delay and timeout config dialog box */
struct dtdb
{
  GtkWidget *dialog;
  GtkWidget *spinbutton;
};

/* Used by the setup screen dialog box */
struct ssdb
{
  GtkWidget *dialog;
  gint image_format;
  gint clipping;
};

/* Used by the entry dialog box */
struct edb
{
  GtkWidget *dialog;
  GtkWidget *entry;
  gchar *text;
  gint button;
};

/* Used by the user dialog boxes */
struct udb
{
  GtkWidget *dialog;
  gint button;
};

/* Used by the general config dialog box */
struct gdb
{
  gint xsize;
  gint ysize;
  gint clist_sort;
  gint clist_sort_order;
  gint ctree_sort;
  gint ctree_sort_order;
  gint confirm;
  gint path_mode;
  gint show;
  gint file_mode;  

  GtkWidget *dialog;
  GtkWidget *spinbutton1;
  GtkWidget *spinbutton2;
};

/* Used by the link speed dialog box */
struct lsdb
{
  GtkWidget *dialog;
  gint baud_rate;
  GtkWidget *combo_entry1;
};

#endif
