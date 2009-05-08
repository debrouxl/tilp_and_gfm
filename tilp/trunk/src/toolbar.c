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
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"
#include "support.h"

struct toolbar_window toolbar_wnd = { 0 };

/* Put some buttons of the toolbar as sensitive according to some options */
void toolbar_refresh_buttons(void)
{
	CalcFeatures features;

	if (toolbar_wnd.toolbar == NULL)
		return;

	features = ticalcs_calc_features(calc_handle);

	gtk_widget_set_sensitive(toolbar_wnd.button10, features & OPS_ISREADY);
	gtk_widget_set_sensitive(toolbar_wnd.button11, features & OPS_DIRLIST);
	gtk_widget_set_sensitive(toolbar_wnd.button12, features & OPS_BACKUP);
	gtk_widget_set_sensitive(toolbar_wnd.button13, features & OPS_BACKUP);
	gtk_widget_set_sensitive(toolbar_wnd.button14, !(features & FTS_SILENT) || !options.full_gui);

	if(options.full_gui)
		gtk_widget_hide(toolbar_wnd.button15);
	else
		gtk_widget_show(toolbar_wnd.button15);
}
