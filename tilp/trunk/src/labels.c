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

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"
struct clabel_window clabel_win = { 0 };

static void format(char *s, char *buf)
{
  gchar *i = NULL;
  gchar *j = NULL;
  
  i = (gchar *) strchr(s, DIR_SEPARATOR_C);	// first slash
  j = (gchar *) strrchr(s, DIR_SEPARATOR_C);	// last slash
  
  if (i == j)
    {
      strcpy(buf, s);
      return;
    }
  
  i = (gchar *) strchr(i + 1, DIR_SEPARATOR_C);	// second slash
  *i = '\0';
  strcpy(s, DIR_SEPARATOR_S);
  strcat(s, "...");
  strcat(s, ((*j != '\0') ? j : j++)); // in case there are only 2 slashes in the string
  return;
}


#ifdef __WIN32__
#define snprintf _snprintf
#endif				/*  */

/* Refresh the info window */
void labels_refresh(void)
{
	gchar buffer[MAXCHARS];
	gsize br, bw;
	gchar *utf8;

	switch (ti_calc.memory) {
	case MEMORY_FREE:
		snprintf(buffer, MAXCHARS, _("Memory free: %u bytes"),
			 ctree_win.memory);
		break;
	case MEMORY_USED:
		snprintf(buffer, MAXCHARS, _("Memory used: %u bytes"),
			 ctree_win.memory);
		break;
	case MEMORY_NONE:
		snprintf(buffer, MAXCHARS, _("Memory used: %s"), _("N/A"));
		break;
	}

	gtk_label_set_text(GTK_LABEL(clabel_win.label21), buffer);
	snprintf(buffer, MAXCHARS, _("Current directory: %s"),
		 clist_win.current_dir);

	utf8 = g_filename_to_utf8(buffer, -1, &br, &bw, NULL);
	format(utf8, buffer);
	gtk_label_set_text(GTK_LABEL(clabel_win.label22), buffer);
}
