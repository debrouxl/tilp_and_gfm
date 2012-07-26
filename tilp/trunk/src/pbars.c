/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				

#include <gtk/gtk.h>

#include "tilp_core.h"
#include "gstruct.h"
#include "pbars.h"
#include "gtk_update.h"

struct pbar_window pbar_wnd = { 0 };

static GtkWidget *window = NULL;

static void reset_counters(void)
{
	gtk_update.cnt1 = gtk_update.max1 = 0;
	gtk_update.cnt2 = gtk_update.max2 = 0;
	gtk_update.cnt3 = gtk_update.max3 = 1;
	gtk_update.cancel = 0;
}

/* Create a window with 1 progress bar */
void create_pbar_type1(const gchar * title)
{
	GtkBuilder *builder;
	GError* error = NULL;

	reset_counters();

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("pbar1.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "pbar1_dbox"));
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.pbar1 = GTK_WIDGET (gtk_builder_get_object (builder, "progressbar10"));
	pbar_wnd.label_rate = GTK_WIDGET (gtk_builder_get_object (builder, "label11"));

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_TYPE);
	gtk_widget_show_all(window);
}


/* Create a window with 1 label */
void create_pbar_type2(const gchar * title)
{
	GtkBuilder *builder;
	GError* error = NULL;

	reset_counters();

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("pbar2.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "pbar2_dbox"));
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.label = GTK_WIDGET (gtk_builder_get_object (builder, "label20"));
	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), "");

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_TYPE);
	gtk_widget_show_all(window);
}


/* Create a window with 2 progress bars */
void create_pbar_type3(const gchar * title)
{
	GtkBuilder *builder;
	GError* error = NULL;

	reset_counters();

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("pbar3.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "pbar3_dbox"));
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.pbar2 = GTK_WIDGET (gtk_builder_get_object (builder, "progressbar30"));
	pbar_wnd.pbar1 = GTK_WIDGET (gtk_builder_get_object (builder, "progressbar31"));
	pbar_wnd.label_rate = GTK_WIDGET (gtk_builder_get_object (builder, "label32"));

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_TYPE);
	gtk_widget_show_all(window);
}


/* Create a window with a 1 progress bar and 1 label */
void create_pbar_type4(const gchar * title)
{
	GtkBuilder *builder;
	GError* error = NULL;

	reset_counters();

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("pbar4.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "pbar4_dbox"));
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.label_part = GTK_WIDGET (gtk_builder_get_object (builder, "label41"));
	pbar_wnd.label = GTK_WIDGET (gtk_builder_get_object (builder, "label42"));
	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), "");
	pbar_wnd.pbar1 = GTK_WIDGET (gtk_builder_get_object (builder, "progressbar40"));
	pbar_wnd.label_rate = GTK_WIDGET (gtk_builder_get_object (builder, "label43"));

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_TYPE);
	gtk_widget_show_all(window);
}


/* Create a window with 2 progress bars and 1 label */
void create_pbar_type5(const gchar * title)
{
	GtkBuilder *builder;
	GError* error = NULL;

	reset_counters();

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("pbar5.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "pbar5_dbox"));
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.label_part = GTK_WIDGET (gtk_builder_get_object (builder, "label52"));
	pbar_wnd.label = GTK_WIDGET (gtk_builder_get_object (builder, "label53"));
	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), "");
	pbar_wnd.pbar2 = GTK_WIDGET (gtk_builder_get_object (builder, "progressbar50"));
	pbar_wnd.pbar1 = GTK_WIDGET (gtk_builder_get_object (builder, "progressbar51"));
	pbar_wnd.label_rate = GTK_WIDGET (gtk_builder_get_object (builder, "label54"));

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_TYPE);
	gtk_widget_show_all(window);
}

/* Create a pbar window */
void create_pbar(int type, const gchar * title)
{
	switch(type)
	{
	case 1: create_pbar_type1(title); break;
	case 2: create_pbar_type2(title); break;
	case 3: create_pbar_type3(title); break;
	case 4: create_pbar_type4(title); break;
	case 5: create_pbar_type5(title); break;
	default: break;
	}
		
}

/* Destroy a pbar window */
void destroy_pbar(void)
{
	pbar_wnd.pbar1 = NULL;
	pbar_wnd.pbar2 = NULL;
	pbar_wnd.label = NULL;
	pbar_wnd.label_rate = NULL;
	pbar_wnd.label_part = NULL;

	if (window != NULL)
	{
		gtk_widget_destroy(window);
		window = NULL;
	}
}


TILP_EXPORT void on_pbar_okbutton1_pressed(GtkButton * button, gpointer user_data)
{
	gtk_update.cancel = 1;
}
