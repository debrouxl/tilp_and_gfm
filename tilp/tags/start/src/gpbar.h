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

#ifndef GPBAR_H
#define GPBAR_H

#include <gtk/gtk.h>

/* Create a window with 1 pbar */
void create_pbar_type1(const gchar *title);
void destroy_pbar_type1(void);
/* Create a window with 1 label */
void create_pbar_type2(const gchar *title, gchar *text);
void destroy_pbar_type2(void);
/* Create a window with 2 pbars */
void create_pbar_type3(const gchar *title);
void destroy_pbar_type3(void);
/* Create a window with 1 pbar and 1 label */
void create_pbar_type4(const gchar *title, gchar *text);
void destroy_pbar_type4(void);
/* Create a window with 2 pbars and 1 label */
void create_pbar_type5(const gchar *title, gchar *text);
void destroy_pbar_type5(void);
/* Destroy a pbar windows: replaces the previous functions */
void destroy_pbar(void);

#endif




