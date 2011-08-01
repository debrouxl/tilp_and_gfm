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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <gtk/gtk.h>

#ifndef GLADE_CB
#if defined(__WIN32__) && !defined(HAVE_FVISIBILITY)
# define GLADE_CB __declspec(dllexport)
#elif defined(HAVE_FVISIBILITY)
# define GLADE_CB __attribute__ ((visibility("default")))
#else
# define GLADE_CB
#endif
#endif

void create_pbar_type1(const gchar* title);
void create_pbar_type2(const gchar* title);
void create_pbar_type3(const gchar* title);
void create_pbar_type4(const gchar* title);
void create_pbar_type5(const gchar* title);

void create_pbar(int type, const gchar * title);
void destroy_pbar(void);

GLADE_CB void on_pbar_okbutton1_pressed(GtkButton* button, gpointer user_data);
