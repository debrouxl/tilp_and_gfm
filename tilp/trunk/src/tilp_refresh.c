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
  libticables update functions in command line mode
*/

#include <stdio.h>

#ifndef __MACOSX__
#include "tilibs.h"
#else				/*  */
#include <libticalcs/calc_int.h>
#endif				/*  */

#include "tilp_core.h"
static void cmdline_start()
{
	info_update.prev_percentage = info_update.percentage = 0.0;
} static void cmdline_stop()
{
	info_update.prev_percentage = info_update.percentage = 0.0;

	//fprintf(stdout, "\n");
} static void cmdline_pbar()
{

	/*
	   static int i;
	   static char bargraph[MAXCHARS] = "[....................] 100%";

	   strcpy(bargraph, "[                   ] 100%");
	   for(i=0; i<20; i++)
	   fprintf(stdout, "\b");
	   for(i=1; i<20*info_update.percentage; i++)
	   bargraph[i] = '=';
	   fprintf(stdout, "%s", bargraph);
	 */
	/*
	   if(info_update.percentage == 0.0)
	   fprintf(stdout, "[");
	 */
	if ((info_update.percentage - info_update.prev_percentage) < 0.05) {
		if ((info_update.percentage -
		     info_update.prev_percentage) < 0)
			info_update.prev_percentage =
			    info_update.percentage;
	} else {
		info_update.prev_percentage = info_update.percentage;
		fprintf(stdout, ".");
		fflush(stdout);
	}

	/*
	   if(info_update.percentage > 0.99)
	   fprintf(stdout, "]\n", info_update.percentage);
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
void tilp_cmdline_set_refresh(void)
{
	ticalc_set_update(&info_update, cmdline_start, cmdline_stop,
			  cmdline_refresh, cmdline_pbar, cmdline_label);
	printl(0, _("Initialized in command line mode.\n"));
	return;
}
