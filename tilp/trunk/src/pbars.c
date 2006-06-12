/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
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
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				

#include <gtk/gtk.h>
#include <glade/glade.h>

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
	gtk_update.cnt3 = gtk_update.max3 = 0;
	gtk_update.cancel = 0;
}

/* Create a window with 1 progress bar */
void create_pbar_type1(const gchar * title)
{
	GladeXML *xml;

	reset_counters();

	xml = glade_xml_new(tilp_paths_build_glade("pbars-2.glade"), "pbar1_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	window = glade_xml_get_widget(xml, "pbar1_dbox");
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.pbar1 = glade_xml_get_widget(xml, "progressbar10");
	pbar_wnd.label_rate = glade_xml_get_widget(xml, "label11");

	gtk_widget_show_all(window);
}


/* Create a window with 1 label */
void create_pbar_type2(const gchar * title, gchar * text)
{
	GladeXML *xml;

	reset_counters();

	xml = glade_xml_new(tilp_paths_build_glade("pbars-2.glade"), "pbar2_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	window = glade_xml_get_widget(xml, "pbar2_dbox");
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.label = glade_xml_get_widget(xml, "label20");
	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), text);

	gtk_widget_show_all(window);
}


/* Create a window with 2 progress bars */
void create_pbar_type3(const gchar * title)
{
	GladeXML *xml;

	reset_counters();

	xml = glade_xml_new(tilp_paths_build_glade("pbars-2.glade"), "pbar3_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	window = glade_xml_get_widget(xml, "pbar3_dbox");
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.pbar2 = glade_xml_get_widget(xml, "progressbar30");
	pbar_wnd.pbar1 = glade_xml_get_widget(xml, "progressbar31");
	pbar_wnd.label_rate = glade_xml_get_widget(xml, "label32");

	gtk_widget_show_all(window);
}


/* Create a window with a 1 progress bar and 1 label */
void create_pbar_type4(const gchar * title, gchar * text)
{
	GladeXML *xml;

	reset_counters();

	xml = glade_xml_new(tilp_paths_build_glade("pbars-2.glade"), "pbar4_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	window = glade_xml_get_widget(xml, "pbar4_dbox");
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.label_part = glade_xml_get_widget(xml, "label41");
	pbar_wnd.label = glade_xml_get_widget(xml, "label42");
	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), text);
	pbar_wnd.pbar1 = glade_xml_get_widget(xml, "progressbar40");
	pbar_wnd.label_rate = glade_xml_get_widget(xml, "label43");

	gtk_widget_show_all(window);
}


/* Create a window with 2 progress bars and 1 label */
void create_pbar_type5(const gchar * title, gchar * text)
{
	GladeXML *xml;

	reset_counters();

	xml = glade_xml_new(tilp_paths_build_glade("pbars-2.glade"), "pbar5_dbox", PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	window = glade_xml_get_widget(xml, "pbar5_dbox");
	gtk_window_set_title(GTK_WINDOW(window), title);

	pbar_wnd.label_part = glade_xml_get_widget(xml, "label52");
	pbar_wnd.label = glade_xml_get_widget(xml, "label53");
	gtk_label_set_text(GTK_LABEL(pbar_wnd.label), text);
	pbar_wnd.pbar2 = glade_xml_get_widget(xml, "progressbar50");
	pbar_wnd.pbar1 = glade_xml_get_widget(xml, "progressbar51");
	pbar_wnd.label_rate = glade_xml_get_widget(xml, "label54");

	gtk_widget_show_all(window);
}


/* Destroy a pbar window */
void destroy_pbar(void)
{
	pbar_wnd.pbar1 = NULL;
	pbar_wnd.pbar2 = NULL;
	pbar_wnd.label = NULL;

	if (window != NULL)
	{
		gtk_widget_destroy(window);
		window = NULL;
	}
}


GLADE_CB void on_pbar_okbutton1_pressed(GtkButton * button, gpointer user_data)
{
	gtk_update.cancel = 1;
}
