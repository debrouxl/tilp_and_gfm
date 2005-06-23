/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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
#endif				

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "dboxes.h"
#include "support.h"
#include "tilp_core.h"

static gint ret_val = 0;

int msg_box1(const gchar * title, gchar * message)
{
	GtkWidget *dialog, *label;
	gint result;
	gint msg_type = -1;

	if (!strcmp(title, _("Information")))
		msg_type = GTK_MESSAGE_INFO;
	else if (!strcmp(title, _("Warning")))
		msg_type = GTK_MESSAGE_WARNING;
	else if (!strcmp(title, _("Question")))
		msg_type = GTK_MESSAGE_QUESTION;
	else if (!strcmp(title, _("Error")))
		msg_type = GTK_MESSAGE_ERROR;

	if (msg_type != -1) 
	{
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
					   msg_type, GTK_BUTTONS_CLOSE,
					   message);
		gtk_dialog_run(GTK_DIALOG(dialog));
	} 
	else 
	{
		dialog = gtk_dialog_new_with_buttons(title, GTK_WINDOW(NULL),
						(GtkDialogFlags)
						(GTK_DIALOG_MODAL),
						GTK_STOCK_OK,
						GTK_RESPONSE_OK, NULL);
		gtk_dialog_set_default_response(GTK_DIALOG(dialog),
						GTK_RESPONSE_OK);
		label = gtk_label_new(message);
		gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
				  label);
		gtk_widget_show(label);

		result = gtk_dialog_run(GTK_DIALOG(dialog));
		switch (result) 
		{
		case GTK_RESPONSE_OK:
			break;
		default:
			break;
		}
	}
	gtk_widget_destroy(dialog);

	return 0;
}

gint msg_box2(const char *title, char *message)
{
	GtkWidget *dialog;
	gint result;
	gint msg_type = -1;

	if (!strcmp(title, _("Information")))
		msg_type = GTK_MESSAGE_INFO;
	else if (!strcmp(title, _("Warning")))
		msg_type = GTK_MESSAGE_WARNING;
	else if (!strcmp(title, _("Question")))
		msg_type = GTK_MESSAGE_QUESTION;
	else if (!strcmp(title, _("Error")))
		msg_type = GTK_MESSAGE_ERROR;
	else
		msg_type = GTK_MESSAGE_INFO;

	dialog =
	    gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, msg_type,
				   GTK_BUTTONS_OK_CANCEL, message);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog),
					GTK_RESPONSE_CANCEL);

	result = gtk_dialog_run(GTK_DIALOG(dialog));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		gtk_widget_destroy(dialog);
		return BUTTON1;
		break;
	default:
		gtk_widget_destroy(dialog);
		return BUTTON2;
		break;
	}

	return 0;
}

gint msg_box3(const char *title, char *message, const char *button1,
	      const char *button2, const char *button3)
{
	GtkWidget *dialog, *label;
	gint result;

	dialog = gtk_dialog_new_with_buttons(title, GTK_WINDOW(NULL),
					     (GtkDialogFlags)
					     (GTK_DIALOG_MODAL),
					     GTK_STOCK_YES,
					     GTK_RESPONSE_YES,
					     GTK_STOCK_NO,
					     GTK_RESPONSE_NO,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL, NULL);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog),
					GTK_RESPONSE_CANCEL);
	label = gtk_label_new(message);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
	gtk_widget_show(label);

	result = gtk_dialog_run(GTK_DIALOG(dialog));
	switch (result) 
	{
	case GTK_RESPONSE_YES:
		gtk_widget_destroy(dialog);
		return BUTTON1;
		break;
	case GTK_RESPONSE_NO:
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

gint msg_box4(const char *title, char *message)
{
	GtkWidget *dialog, *label;
	gint result;

	dialog = gtk_dialog_new_with_buttons(title, GTK_WINDOW(NULL),
					     (GtkDialogFlags)
					     (GTK_DIALOG_MODAL),
					     GTK_STOCK_GO_FORWARD,
					     GTK_RESPONSE_OK,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL, NULL);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog),
					GTK_RESPONSE_CANCEL);
	label = gtk_label_new(message);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
	gtk_widget_show(label);

	result = gtk_dialog_run(GTK_DIALOG(dialog));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		gtk_widget_destroy(dialog);
		return BUTTON1;
		break;
	default:
		gtk_widget_destroy(dialog);
		return BUTTON2;
		break;
	}

	return 0;
}


/* Create the dialog box entry and wait */
char *msg_entry(const char *title, const char *message,
		const char *content)
{
	GladeXML *xml;
	GtkWidget *data;
	GtkWidget *dbox;
	GtkWidget *entry = NULL;
	gchar *ret = NULL;
	gint result;
	ret_val = 0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("user_boxes-2.glade"), "entry_dbox",
	     PACKAGE);
	if (!xml)
		g_error("dboxes.c: GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	dbox = data = glade_xml_get_widget(xml, "entry_dbox");
	gtk_window_set_title(GTK_WINDOW(data), title);

	data = glade_xml_get_widget(xml, "frame1");
	gtk_frame_set_label(GTK_FRAME(data), message);

	data = glade_xml_get_widget(xml, "entry1");
	entry = GTK_WIDGET(data);
	gtk_entry_set_text(GTK_ENTRY(data), content);

	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		ret = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
		break;
	default:
		break;
	}
	gtk_widget_destroy(dbox);

	return ret;
}
