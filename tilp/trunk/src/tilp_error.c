//* Hey EMACS -*- linux-c -*- */
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "tilibs.h"

#include "tilp_core.h"

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
	char *utf;
	gsize bw;

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
					    tilp_device_reset();
					}
				}
			}
			else
			{
			    // ticables error => reset
			    tilp_device_reset();
			}			

			utf = g_locale_to_utf8(s, -1, NULL, &bw, NULL);
			gif->msg_box1(_("Error"), utf);
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
			}
		}

		if(s)
			tilp_info("%s\n", s);
	}

	//free(s);
	return errcode;
}

