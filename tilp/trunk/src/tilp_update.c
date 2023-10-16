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
	Default callbacks for ticalcs library (console)
*/

#include <stdio.h>

#include "tilp_core.h"

static CalcUpdate	default_update;

static void default_start(void)
{
} 

static void default_stop(void)
{
} 

static void default_pbar(void)
{

	/*
	   static int i;
	   static char bargraph[MAXCHARS] = "[....................] 100%";

	   strcpy(bargraph, "[                   ] 100%");
	   for(i=0; i<20; i++)
	   fprintf(stdout, "\b");
	   for(i=1; i<20*default_update.percentage; i++)
	   bargraph[i] = '=';
	   fprintf(stdout, "%s", bargraph);
	 */
	/*
	   if(default_update.percentage == 0.0)
	   fprintf(stdout, "[");
	 */
	/*
	if ((default_update.percentage - default_update.prev_percentage) < 0.05) {
		if ((default_update.percentage -
		     default_update.prev_percentage) < 0)
			default_update.prev_percentage =
			    default_update.percentage;
	} else {
		default_update.prev_percentage = default_update.percentage;
		fprintf(stdout, ".");
		fflush(stdout);
	}
	*/

	/*
	   if(default_update.percentage > 0.99)
	   fprintf(stdout, "]\n", default_update.percentage);
	 */
}

static void default_label(void)
{
}

static void default_refresh(void)
{
}

static CalcUpdate default_update =
{
	"", 0,
	0.0, 0, 0, 0, 0, 0, 0, (1 << 0), 0,
	default_start,
	default_stop,
	default_refresh,
	default_pbar,
	default_label,
};

void tilp_update_set_default(void)
{
	ticalcs_update_set(calc_handle, &default_update);
}
