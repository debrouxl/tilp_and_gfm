/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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

#ifdef __MACOSX__
#include <libticalcs/calc_int.h>
#endif

#include "struct.h"
#include "intl.h"

static void cmdline_start()
{
  info_update.prev_percentage = info_update.percentage = 0.0;
  info_update.start_time = clock();
}

static void cmdline_stop()
{
  info_update.prev_percentage = info_update.percentage = 0.0;
  //fprintf(stdout, "\n");
}

static void cmdline_pbar()
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
  if( (info_update.percentage - info_update.prev_percentage) < 0.05)
    {
      if( (info_update.percentage - info_update.prev_percentage) < 0)
	info_update.prev_percentage = info_update.percentage;
    }
  else
    {
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
}

static void cmdline_refresh(void)
{
}

static void cmdline_msgbox(const char *t, char *s)
{
}

static int cmdline_choose(char *cur_varname, char *new_varname)
{
  strcpy(new_varname, "");
  return 0;
}

void cmdline_init_refresh_functions(void)
{
  ticalc_set_update(&info_update,
		    cmdline_start,
		    cmdline_stop,
		    cmdline_refresh,
		    cmdline_msgbox,
		    cmdline_pbar,
		    cmdline_label,
		    cmdline_choose
		    );
  fprintf(stdout, _("Initialized in command line mode.\n"));
  
  return;
}
