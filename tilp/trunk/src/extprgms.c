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

#include "extprgms.h"
#include "tilp_core.h"
static GtkWidget *dbox;
static GtkWidget *unzip_entry;
static GtkWidget *unzip_entry2;
static GtkWidget *untar_entry;
static GtkWidget *untar_entry2;
static GtkWidget *appsign_entry;
static GtkWidget *appsign_entry2;
static GtkWidget *web_entry;
static GtkWidget *web_entry2;
gint display_extprgms_dbox()
{
	GladeXML *xml;
	GtkWidget *data;
	xml = glade_xml_new
	    (tilp_paths_build_glade("extprgms-2.glade"), "extprgms_dbox",
	     PACKAGE);
	if (!xml)
		g_error("extprgms.c: GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);
	dbox = glade_xml_get_widget(xml, "extprgms_dbox");
	data = glade_xml_get_widget(xml, "entry1");
	gtk_entry_set_text(GTK_ENTRY(data), options.unzip_location);
	unzip_entry = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry2");
	gtk_entry_set_text(GTK_ENTRY(data), options.unzip_options);
	unzip_entry2 = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry3");
	gtk_entry_set_text(GTK_ENTRY(data), options.tar_location);
	untar_entry = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry4");
	gtk_entry_set_text(GTK_ENTRY(data), options.tar_options);
	untar_entry2 = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry5");
	gtk_entry_set_text(GTK_ENTRY(data), options.appsign_location);
	appsign_entry = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry6");
	gtk_entry_set_text(GTK_ENTRY(data), options.appsign_options);
	appsign_entry2 = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry7");
	gtk_entry_set_text(GTK_ENTRY(data), options.web_location);
	web_entry = GTK_WIDGET(data);
	data = glade_xml_get_widget(xml, "entry8");
	gtk_entry_set_text(GTK_ENTRY(data), options.web_options);
	web_entry2 = GTK_WIDGET(data);
	while (gtk_events_pending())
		gtk_main_iteration();
	gtk_widget_show_all(dbox);
	return 0;
}
GLADE_CB void on_extprgms_ok_button1_clicked(GtkButton * button,
					     gpointer user_data)
{
	g_free(options.unzip_location);
	options.unzip_location = g_strdup(gtk_editable_get_chars
					  (GTK_EDITABLE(unzip_entry), 0,
					   -1));
	g_free(options.unzip_options);
	options.unzip_options = g_strdup(gtk_editable_get_chars
					 (GTK_EDITABLE(unzip_entry2), 0,
					  -1));
	g_free(options.tar_location);
	options.tar_location = g_strdup(gtk_editable_get_chars
					(GTK_EDITABLE(untar_entry), 0,
					 -1));
	g_free(options.tar_options);
	options.tar_options = g_strdup(gtk_editable_get_chars
				       (GTK_EDITABLE(untar_entry2), 0,
					-1));
	g_free(options.appsign_location);
	options.appsign_location = g_strdup(gtk_editable_get_chars
					    (GTK_EDITABLE(appsign_entry),
					     0, -1));
	g_free(options.appsign_options);
	options.appsign_options = g_strdup(gtk_editable_get_chars
					   (GTK_EDITABLE(appsign_entry2),
					    0, -1));
	g_free(options.web_location);
	options.web_location = g_strdup(gtk_editable_get_chars
					(GTK_EDITABLE(web_entry), 0, -1));
	g_free(options.web_options);
	options.web_options = g_strdup(gtk_editable_get_chars
				       (GTK_EDITABLE(web_entry2), 0, -1));
	gtk_widget_destroy(dbox);
} GLADE_CB void on_extprgms_cancel_button1_clicked(GtkButton * button,
						   gpointer user_data)
{
	gtk_widget_destroy(dbox);
} static void on_ok_button1_clicked(GtkButton * button, gpointer user_data)
{
	G_CONST_RETURN gchar *filename;
	filename =
	    gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	gtk_entry_set_text(GTK_ENTRY(unzip_entry), filename);
} static void on_ok_button2_clicked(GtkButton * button, gpointer user_data)
{
	G_CONST_RETURN gchar *filename;
	filename =
	    gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	gtk_entry_set_text(GTK_ENTRY(untar_entry), filename);
} static void on_ok_button3_clicked(GtkButton * button, gpointer user_data)
{
	G_CONST_RETURN gchar *filename;
	filename =
	    gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	gtk_entry_set_text(GTK_ENTRY(appsign_entry), filename);
} static void on_ok_button4_clicked(GtkButton * button, gpointer user_data)
{
	G_CONST_RETURN gchar *filename;
	filename =
	    gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	gtk_entry_set_text(GTK_ENTRY(web_entry), filename);
} GLADE_CB void on_button3_clicked(GtkButton * button, gpointer user_data)
{
	GtkWidget *fs;
	fs = gtk_file_selection_new("Select a File");
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_button1_clicked),
			 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->ok_button),
				 "clicked",
				 G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	gtk_widget_show(fs);
} GLADE_CB void on_button4_clicked(GtkButton * button, gpointer user_data)
{
	GtkWidget *fs;
	fs = gtk_file_selection_new("Select a File");
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_button2_clicked),
			 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->ok_button),
				 "clicked",
				 G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	gtk_widget_show(fs);
} GLADE_CB void on_button5_clicked(GtkButton * button, gpointer user_data)
{
	GtkWidget *fs;
	fs = gtk_file_selection_new("Select a File");
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_button3_clicked),
			 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->ok_button),
				 "clicked",
				 G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	gtk_widget_show(fs);
} GLADE_CB void on_button6_clicked(GtkButton * button, gpointer user_data)
{
	GtkWidget *fs;
	fs = gtk_file_selection_new("Select a File");
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_button4_clicked),
			 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->ok_button),
				 "clicked",
				 G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	gtk_widget_show(fs);
}
