/* Hey EMACS -*- linux-c -*- */
/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "support.h"
#include "tilp_core.h"
gint display_step_1(void)
{
	GtkWidget *dialog, *label;
	gint result;
	dialog =
	    gtk_dialog_new_with_buttons("TiLP wizard", GTK_WINDOW(NULL),
					(GtkDialogFlags)
					(GTK_DIALOG_MODAL),
					GTK_STOCK_GO_FORWARD,
					GTK_RESPONSE_OK,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL, NULL);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog),
					GTK_RESPONSE_CANCEL);
	label =
	    gtk_label_new(_
			  ("Welcome to TiLP\n\nThis box will help you to configure TiLP for your first use. If you need to re-launch the Wizard, go to Help->Wizard."));
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
	gtk_widget_show(label);

	//display_comm_dbox();
	result = gtk_dialog_run(GTK_DIALOG(dialog));
	switch (result) {
	case GTK_RESPONSE_OK:
		gtk_widget_destroy(dialog);
		return BUTTON2;
		break;
	default:
		gtk_widget_destroy(dialog);
		return BUTTON3;
		break;
	}
	return 0;
}

gint display_step_2(void)
{
	return 0;
}

gint display_step_3(void)
{
	return 0;
}

gint display_step_4(void)
{
	return 0;
}

gint display_wizard_dbox()
{
	gint ret;
	ret = display_step_1();
	ret = display_step_2();
	ret = display_step_3();
	ret = display_step_4();
	return 0;
}
