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
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "includes.h"

/* Open the pixmap stored on the file 'filename' and put it in the 'pixmap' 
variable according to the 'mask' variable */
void open_xpm (char *filename, GtkWidget *parent, 
	       GdkPixmap **pixmap, GdkBitmap **mask)
{
  char str[MAXCHARS];
  GtkStyle *style;

  style = gtk_widget_get_style (parent);
  strcpy(str, inst_paths.base_dir);
  //g_warning("inst_path.base_dir: %s\n", inst_paths.base_dir);
#ifndef WIN32
  strcat(str, SHARE_DIR "/pixmaps/");
#else
  strcat(str, SHARE_DIR "\\pixmaps\\");
#endif
  strcat(str, filename);
  //g_warning("pixmap to load: %s\n", str);
  
  if (access (str, F_OK) != 0) 
    {
      g_error("Error: unable to access this file: '%s'\n", str);
      exit (1);
    }
  *pixmap = gdk_pixmap_create_from_xpm (parent->window, mask, &style->bg[GTK_STATE_NORMAL], str);
  if (*pixmap == NULL) 
    {
      fprintf(stderr, "Error: unable to load this file into a pixmap: '%s'\n", str);
      exit (1);
    }
}


