/*  tilp - linking program for TI calculators
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

/*
  This file contains the function used to manage error codes.
*/

#include <stdio.h>
#include <string.h>

#ifndef __MACOSX__
#include "tilibs.h"
#else
#include <libticalcs/calc_int.h>
#endif

#include "intl.h"
#include "struct.h"
#include "gui_indep.h"
#include "defs.h"

extern int working_mode;
static GList *stack = NULL;

/*
  This function take as input parameter an error code and displays it
  in a message box.

  This function is 'buffered': if error messages appear during startup
  (console or terminal), they will be displayed in the GUI.
 */
int tilp_error(int errcode)
{
  char s[1024] = N_("code not found. This is a bug. Please report it.\n");  

  if(!errcode) return 0;
  
  /* Close the link cable port */
  link_cable.close();

  /* Push error messages */
  stack = g_list_append(stack, GINT_TO_POINTER(errcode));

  /* Pop error messages */
  if(working_mode & MODE_GUI)
    {
      int i;
      int err;
      
      for(i=0; i<g_list_length(stack); i++)
	{
	  err = GPOINTER_TO_INT((g_list_nth(stack, i))->data);
 
	  /* Retrieve the error message */
	  err = ticable_get_error(err, s);
	  if(err)
	    {
	      err = ticalc_get_error(err, s);
	      if(err)
		{
		  // nothing: error for TiLP
		}
	    }

	  gif->msg_box(_("Error"), s);
	}

      g_list_free(stack);
      stack = NULL;
    }
  else
    {
      int err = errcode;
      /* Retrieve the error message */
      err = ticable_get_error(err, s);
      if(!err) 
	return 0;
      else
	{
	  err = ticalc_get_error(err, s);
	  if(!err) return 0;
	}
      
      DISPLAY_ERROR("%s\n", s);
    }
  
  return 0;
}
