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

/*
  libticalcs update functions in GTK mode
*/

#include <stdio.h>
#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"

TicableDataRate *dr;

static void gtkgui_start()
{
  info_update.prev_percentage = info_update.percentage = 0.0;
  ticable_get_datarate(&dr);
} 

static void gtkgui_stop()
{
  info_update.prev_percentage = info_update.percentage = 0.0;
} 

static void refresh_pbar1()
{
  gchar buffer[32];
  gfloat rate;
  
  info_update.percentage = (float) info_update.count / info_update.total;

  if (p_win.pbar1 != NULL) 
    {
      
      /* Refresh if necessary (for speeding up !) */
      if ((info_update.percentage - info_update.prev_percentage) < 0.05) 
	{
	  if ((info_update.percentage - info_update.prev_percentage) < 0)
	    info_update.prev_percentage = info_update.percentage;
	  else
	    return;
	} 
      else
	info_update.prev_percentage = info_update.percentage;
      
      rate = dr->count / toCURRENT(dr->start);
      g_snprintf(buffer, 32, "Rate: %1.1f Kbytes/s", rate / 1000);
      gtk_label_set_text(GTK_LABEL(p_win.label_rate), buffer);
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_win.pbar1),
				    info_update.percentage);
      while (gtk_events_pending()) 
	{
	  gtk_main_iteration();
	}
    }
}

static void refresh_pbar2()
{
  if (p_win.pbar2 != NULL) 
    {
      /* Refresh if necessary (for speeding up !) */
      if ((info_update.main_percentage - 
	   info_update.prev_main_percentage) < 0.05)
	return;
      else
	info_update.prev_main_percentage = info_update.main_percentage;
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_win.pbar2),
				    info_update.main_percentage);
      while (gtk_events_pending()) 
	{
	  gtk_main_iteration();
	}
    }
}

static void gtkgui_pbar()
{
  refresh_pbar1();
  refresh_pbar2();
} 

// note: info_update.label_text is encoded in UTF8 but variable names ('%s')
// are encoded according to tifiles_translate_set_encoding().
// This should be treated here but given that encoding is set to UTF8, there
// nothing to do...
static void gtkgui_label()
{
  if (p_win.label == NULL)
    return;

  gtk_label_set_text(GTK_LABEL(p_win.label), info_update.label_text);
  while (gtk_events_pending()) 
    {
      gtk_main_iteration();
    }
}

static void gtkgui_refresh()
{
  while (gtk_events_pending()) 
    {
      gtk_main_iteration();
    }
}

void tilp_guigtk_set_refresh(void)
{
  ticalc_set_update(&info_update, gtkgui_start, gtkgui_stop,
		    gtkgui_refresh, gtkgui_pbar, gtkgui_label);
  fprintf(stdout, _("Initialized in GTK+ mode.\n"));
  return;
}
