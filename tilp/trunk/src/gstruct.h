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

#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <gtk/gtk.h>


/* The main window */
extern GtkWidget *main_wnd;
extern GtkWidget *clist_wnd;
extern GtkWidget *ctree_wnd;
extern GtkWidget *scrn_wnd;
extern GtkWidget *status;

/* This struct is used by the toolbar */
extern struct toolbar_window {
	GtkWidget *toolbar;
	GtkWidget *button10;
	GtkWidget *button11;
	GtkWidget *button12;
	GtkWidget *button13;
	GtkWidget *button14;
	GtkWidget *button20;
	GtkWidget *button21;
	GtkWidget *button22;
} toolbar_win;

/* This struct is used by the CLabel window */
extern struct clabel_window {
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
extern struct progress_window {
	GtkWidget *window;
	GtkWidget *pbar1;
	GtkWidget *pbar2;
	GtkWidget *label;
	GtkWidget *label_rate;
} p_win;

/* This struct is used by the Group File Manager */
extern struct gfm_window {
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
} gfm_win;

#endif
