/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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

#define SPEED_UP	// do'nt do too many pbar refresh

static TicableDataRate *dr;

static void gtkgui_start()
{
	info_update.prev_percentage = info_update.percentage = 0.0;
	ticable_get_datarate(&dr);
} 

static void gtkgui_stop()
{
	info_update.prev_percentage = info_update.percentage = 0.0;
} 


static void filter_shift(void);
static gfloat filter_compute(gfloat input);

static void refresh_pbar1()
{
	gchar buffer[32];
	gfloat rate, avg;
  
	info_update.percentage = (float) info_update.count / info_update.total;

	if (p_win.pbar1 != NULL) 
    {
#ifdef SPEED_UP
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
#endif
		rate = dr->count / toCURRENT(dr->start);
		
		filter_shift();
		avg = filter_compute(rate);

		g_snprintf(buffer, 32, "Rate: %1.1f Kbytes/s", avg / 1000);
		gtk_label_set_text(GTK_LABEL(p_win.label_rate), buffer);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_win.pbar1), info_update.percentage);

		GTK_REFRESH();
	}
}

static void refresh_pbar2()
{
	if (p_win.pbar2 != NULL) 
    {
#ifdef SPEED_UP
		/* Refresh if necessary (for speeding up !) */
		if ((info_update.main_percentage - info_update.prev_main_percentage) < 0.05)
			return;
		else
			info_update.prev_main_percentage = info_update.main_percentage;
#endif

		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_win.pbar2), info_update.main_percentage);

		GTK_REFRESH();
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

	GTK_REFRESH();
}

static void gtkgui_refresh()
{
	GTK_REFRESH();
}

void tilp_guigtk_set_refresh(void)
{
	ticalc_set_update(&info_update, gtkgui_start, gtkgui_stop,
		    gtkgui_refresh, gtkgui_pbar, gtkgui_label);
	printl(0, _("initialized in GTK+ mode.\n"));
	return;
}


///// misc

static gfloat filter[8] = { 0 };

static void filter_shift(void)
{
	int i;

	for(i=7; i>0; i--)
		filter[i] = filter[i-1];
}

static gfloat filter_compute(gfloat input)
{
	int i;
	gfloat avg, min, max;
	
	avg = min = max = 0.0;

	filter[0] = input;
	for(i=0; i<7; i++) {
		if(filter[i] < min) min = filter[i];
		if(filter[i] > max) max = filter[i];

		avg += filter[i];
	}

	avg -= min;
	avg -= max;
	
	return (avg / 6);
}