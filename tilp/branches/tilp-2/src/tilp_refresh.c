/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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
	Default command line mode callbacks for ticalcs library.
*/

#include <stdio.h>

#include "tilp_core.h"

extern CalcUpdate cmdline_update;

static void cmdline_start(void)
{
	cmdline_update.cnt1 = cmdline_update.max1 = 0;
} 

static void cmdline_stop(void)
{
	cmdline_update.cnt1 = cmdline_update.max1 = 0;
} 

static void cmdline_pbar(void)
{

	/*
	   static int i;
	   static char bargraph[MAXCHARS] = "[....................] 100%";

	   strcpy(bargraph, "[                   ] 100%");
	   for(i=0; i<20; i++)
	   fprintf(stdout, "\b");
	   for(i=1; i<20*cmdline_update.percentage; i++)
	   bargraph[i] = '=';
	   fprintf(stdout, "%s", bargraph);
	 */
	/*
	   if(cmdline_update.percentage == 0.0)
	   fprintf(stdout, "[");
	 */
	/*
	if ((cmdline_update.percentage - cmdline_update.prev_percentage) < 0.05) {
		if ((cmdline_update.percentage -
		     cmdline_update.prev_percentage) < 0)
			cmdline_update.prev_percentage =
			    cmdline_update.percentage;
	} else {
		cmdline_update.prev_percentage = cmdline_update.percentage;
		fprintf(stdout, ".");
		fflush(stdout);
	}
	*/

	/*
	   if(cmdline_update.percentage > 0.99)
	   fprintf(stdout, "]\n", cmdline_update.percentage);
	 */
}

static void cmdline_label(void)
{
	return;
}

static void cmdline_refresh(void)
{
	return;
}

CalcUpdate cmdline_update =
{
	"", 0,
	0.0, 0, 0, 0, 0,
	cmdline_start,
	cmdline_stop,
	cmdline_refresh,
	cmdline_pbar,
	cmdline_label,
};

void tilp_refresh_set_update_cmdline(void)
{
	ticalcs_update_set(calc_handle, &cmdline_update);
}
