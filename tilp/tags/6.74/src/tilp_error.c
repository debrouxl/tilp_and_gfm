//* Hey EMACS -*- linux-c -*- */
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

#include <stdio.h>
#include <string.h>

#ifndef __MACOSX__
#include "tilibs.h"
#else				/*  */
#include <libticalcs/calc_int.h>
#endif				/*  */

#include "tilp_core.h"

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
	char s[512] = "code not found. This is a bug. Please report it.\n";
#ifndef __MACOSX__
	char *utf;
	gsize bw;
#endif /* !__MACOSX__ */
	if (!errcode)
		return 0;

	/* Close the link cable port */
	link_cable.close();

	/* Push error messages */
	stack = g_list_append(stack, GINT_TO_POINTER(errcode));

	/* Pop error messages */
	if (working_mode & MODE_GUI) {
		int i;
		for (i = 0; i < (int)g_list_length(stack); i++) {
			int err =
			    GPOINTER_TO_INT((g_list_nth(stack, i))->data);

			/* Retrieve the error message */
			err = ticable_get_error(err, s);
			if (err) {
				err = tifiles_get_error(err, s);
				if (err) {
					err = ticalc_get_error(err, s);
					if (err) {

						// next level: error for TiLP
					}
				}
			}
            // FIXME OS X : we'll need to go full-UTF8 at some point
#ifndef __MACOSX__
			utf = g_locale_to_utf8(s, -1, NULL, &bw, NULL);
			gif->msg_box(_("Error"), utf);
#else
            gif->msg_box(_("Error"), s);
#endif /* !__MACOSX__ */
		}
		g_list_free(stack);
		stack = NULL;
	} else {
		int err = errcode;

		/* Retrieve the error message */
		err = ticable_get_error(err, s);
		if (!err)
			return 0;

		else {
			err = ticalc_get_error(err, s);
			if (!err)
				return 0;
		}
		printl(2, "%s\n", s);
	}
	return errcode;
}
