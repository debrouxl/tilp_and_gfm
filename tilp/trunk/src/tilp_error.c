//* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
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
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef __MACOSX__
#include "tilibs.h"
#else				/*  */
#include <libticalcs/calc_int.h>
#endif				/*  */

#include "tilp_core.h"

#ifdef __WIN32__
#include <windows.h>
#define PAUSE(x) Sleep(x)
#else
#define PAUSE(x) usleep(1000*(x))
#endif

extern int working_mode;
static GList *stack = NULL;

/*
  This function take as input parameter an error code and displays it
  in a message box.

  This function is 'buffered': if one or more error messages appear 
  during startup (console or terminal), they will be displayed in the GUI.
 */
int tilp_err(int errcode)
{
	char *s = NULL;	
#ifndef __MACOSX__
	char *utf;
	gsize bw;
#endif /* !__MACOSX__ */

	/* Push error messages (if any)*/
	if(errcode)
		stack = g_list_append(stack, GINT_TO_POINTER(errcode));

	/* Pop error messages */
	if (!(working_mode & MODE_INI)) 
	{
		int i;
		for (i = 0; i < (int)g_list_length(stack); i++) 
		{
			int err = GPOINTER_TO_INT((g_list_nth(stack, i))->data);

			/* Retrieve the error message */
			err = ticables_error_get(err, &s);
			if (err) 
			{
				g_free(s);
				err = tifiles_error_get(err, &s);
				if (err) 
				{
					g_free(s);
					err = ticalcs_error_get(err, &s);
					if (err) 
					{
						// next level: error for TiLP
						g_free(s);
					}
					else
					{
						// ticalcs error => reset
						//gif->msg_box("Information", "Connection is being reset...", !0);
						ticables_cable_reset(cable_handle);
						PAUSE(1000);
						//gif->msg_box("", "", 0);
					}
				}
			}
			else
			{
				// ticables error => reset
				//gif->msg_box("Information", "Connection is being reset...", !0);
				ticables_cable_reset(cable_handle);
				PAUSE(1000);
				//gif->msg_box("", "", 0);
			}			

            // FIXME OS X : we'll need to go full-UTF8 at some point
#ifndef __MACOSX__
			utf = g_locale_to_utf8(s, -1, NULL, &bw, NULL);
			gif->msg_box1(_("Error"), utf);
#else
			if(s)
				gif->msg_box1(_("Error"), s);
#endif /* !__MACOSX__ */
		}
		g_list_free(stack);
		stack = NULL;
	} 
	else 
	{
		int err = errcode;

		/* Retrieve the error message */
		err = ticables_error_get(err, &s);
		if (err)
		{
			g_free(s);
			err = ticalcs_error_get(err, &s);
			if (err)
			{
				g_free(s);
				err = ticalcs_error_get(err, &s);
				if (err) 
				{
					// next level: error for TiLP
					g_free(s);
				}
			}
		}

		if(s)
			tilp_info("%s\n", s);
	}

	//free(s);
	return errcode;
}

