/*  tilp - linking program for TI calculators
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

/*
  This file contains the function used to manage error codes.
*/

#include <stdio.h>
#include <string.h>

#ifdef __MACOSX__
#include <libticalcs/calc_int.h>
#endif

#include "intl.h"
#include "struct.h"
#include "gui_indep.h"

/*
  This function take as input parameter an error code and displays both
  in a message box and to stderr an error message.
 */
int tilp_error(int err_num)
{
  int err;
  char s[1024] = N_("Error code not found. This is a bug. Please report it.\n");  

  if(err_num == 0)
    return 0;

  /* Close the link cable port */
  link_cable.close_port();
  if(err_num)
    {
      fprintf(stderr, _("Error code %i: "), err_num);
    }

  /* Retrieve the error message */
  err = ticable_get_error(err_num, s);
  //printf("err_num: %i, err: %i, msg: %s\n", err_num, err, s);
  if(err)
    {
      err = ticalc_get_error(err_num, s);
      if(err)
	{
	  // nothing
	}
    }

  fprintf(stderr, "%s\n", s);
  gif->msg_box(_("Error"), s);
  
  return err_num;
}
