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

/*
	GTK callbacks for ticalcs library (gui)
*/

#include <stdio.h>
#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"
#include "gtk_update.h"

//#define DISABLE_UPDATE	// for testing purposes

static void gtk_start(void)
{
	gtk_update.cnt1 = gtk_update.max1 = 0;
	gtk_update.cnt2 = gtk_update.max2 = 0;
	gtk_update.cnt3 = gtk_update.max3 = 0;
} 

static void gtk_stop(void)
{
	gtk_update.cnt1 = gtk_update.max1 = 0;
	gtk_update.cnt2 = gtk_update.max2 = 0;
	gtk_update.cnt3 = gtk_update.max3 = 0;
} 

static void filter_shift(void);
static gfloat filter_compute(gfloat input);

static void refresh_pbar1(void)
{
	gchar buffer[32];
	gfloat rate, avg;

	if (pbar_wnd.pbar1 != NULL) 
	{
		if(gtk_update.cnt1 > gtk_update.max1)
			gtk_update.cnt1 = gtk_update.max1;

		if(gtk_update.max1 != 0)
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar_wnd.pbar1), 
				(gdouble)gtk_update.cnt1 / gtk_update.max1);

		rate = gtk_update.rate;
		filter_shift();
		avg = filter_compute(rate);

		g_snprintf(buffer, 32, "Rate: %1.1f Kbytes/s", avg);
		gtk_label_set_text(GTK_LABEL(pbar_wnd.label_rate), buffer);

		GTK_REFRESH();
	}
}

static void refresh_pbar2(void)
{
	if (pbar_wnd.pbar2 != NULL) 
	{
		if(gtk_update.cnt2 > gtk_update.max2)
			gtk_update.cnt2 = gtk_update.max2;

		if(gtk_update.max2 != 0)
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar_wnd.pbar2), 
				(gdouble)gtk_update.cnt2 / gtk_update.max2);

		GTK_REFRESH();
	}
}

static void refresh_pbar3(void)
{
	gchar buffer[32];

	if(pbar_wnd.label_part != NULL)
	{
		g_snprintf(buffer, 32, "%i/%i: ", gtk_update.cnt3, gtk_update.max3);
		gtk_label_set_text(GTK_LABEL(pbar_wnd.label_part), buffer);

		GTK_REFRESH();
	}
}

static void gtk_pbar(void)
{
#ifndef DISABLE_UPDATE
	refresh_pbar1();
	refresh_pbar2();
	refresh_pbar3();
#endif
} 

// note: info_update.label_text is encoded in UTF8 but variable names ('%s')
// are encoded according to tifiles_translate_set_encoding().
// This should be treated here but given that encoding is set to UTF8, there
// is nothing to do...
static void gtk_label(void)
{
#ifndef DISABLE_UPDATE
	if (pbar_wnd.label == NULL)
		return;

	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), gtk_update.text);

	GTK_REFRESH();
#endif
}

static void gtk_refresh(void)
{
#ifndef DISABLE_UPDATE
	GTK_REFRESH();
#endif
}

CalcUpdate gtk_update =
{
	"", 0,
	0.0, 0, 0, 0, 0, 0, 0,  (1 << 0) | (1 << 1), 0,
	gtk_start,
	gtk_stop,
	gtk_refresh,
	gtk_pbar,
	gtk_label,
};

void tilp_update_set_gtk(void)
{
	ticalcs_update_set(calc_handle, &gtk_update);
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
