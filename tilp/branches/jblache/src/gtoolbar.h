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

#ifndef GTOOLBAR_H
#define GTOOLBAR_H

#include <gtk/gtk.h>

GtkWidget *append_toolbar_button(GtkWidget *button, GtkWidget **toolbar, 
				 char *filename, const char *text, 
				 const char *tooltip_text, GtkSignalFunc callback,
				 gpointer data);

void refresh_sensitive_toolbar_buttons();

#endif




