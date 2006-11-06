/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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
extern GtkWidget* main_wnd;
extern GtkWidget* clist_wnd;
extern GtkWidget* ctree_wnd;
extern GtkWidget* screen_wnd;
extern GtkWidget* status;

/* This struct is used by the toolbar */
extern struct toolbar_window 
{
	GtkWidget* toolbar;
	GtkWidget* button10;
	GtkWidget* button11;
	GtkWidget* button12;
	GtkWidget* button13;
	GtkWidget* button14;
	GtkWidget* button15;

	GtkWidget* button20;
	GtkWidget* button21;
	GtkWidget* button22;
} toolbar_wnd;

/* This struct is used by the CLabel window */
extern struct label_window 
{
	GtkWidget* label11;
	GtkWidget* label12;
	GtkWidget* label13;
	GtkWidget* label14;

	GtkWidget* label21;
} label_wnd;

/* This struct is used to display and manage the progress bar dialog box */
extern struct pbar_window 
{
	GtkWidget* window;
	GtkWidget* pbar1;
	GtkWidget* pbar2;
	GtkWidget* label;
	GtkWidget* label_rate;
	GtkWidget* label_part;
} pbar_wnd;

#endif
