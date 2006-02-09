/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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
#include <string.h>
#include <unistd.h>

#include "tilp_core.h"
#include "dboxes.h"
#include "clist.h"
#include "labels.h"

/* 
   Open a backup to send 
*/
static void on_ok_fsel2(GtkFileSelection * file_selector,
			gpointer user_data)
{
	const gchar *filename;
	filename = (gchar *)
	    gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	gtk_widget_destroy(user_data);
	if (tilp_calc_send_backup((char *) filename) != 0)
		return;
}


/* 
   Save the received backup 
*/
static void on_ok_fsel3(GtkFileSelection * file_selector,
			gpointer user_data)
{
	gchar *tmp_filename;
	G_CONST_RETURN gchar *s;
	gchar *dst_filename;
	s = gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	if (tifiles_get_extension(s) == NULL)
		dst_filename =
		    g_strconcat(s, ".", tifiles_backup_file_ext(), NULL);

	else
		dst_filename = g_strdup(s);
	tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S,
			TMPFILE_BACKUP, NULL);
	tilp_file_move_with_check(tmp_filename, dst_filename);
	g_free(dst_filename);

	/*tilp_dirlist_local();
	   clist_refresh();
	   labels_refresh(); */
}
static void on_cancel_fsel3(GtkFileSelection * file_selector,
			    gpointer user_data)
{
	gchar *tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S,
			TMPFILE_BACKUP, NULL);
	if (unlink(tmp_filename))
		printl(2, _("Unable to remove the temporary file.\n"));
}


/* 
   Save received var(s) 
*/
static void on_ok_fsel4(GtkFileSelection * file_selector,
			gpointer user_data)
{
	gchar *tmp_filename;
	G_CONST_RETURN gchar *s;
	gchar *dst_filename;
	s = gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	if (tifiles_get_extension(s) == NULL)
		dst_filename =
		    g_strconcat(s, ".", tifiles_group_file_ext(), NULL);

	else
		dst_filename = g_strdup(s);
	tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP,
			NULL);
	tilp_file_move_with_check(tmp_filename, dst_filename);
	g_free(dst_filename);

	/*tilp_dirlist_local();
	   clist_refresh();
	   labels_refresh(); */
}
static void on_cancel_fsel4(GtkFileSelection * file_selector,
			    gpointer user_data)
{
	char *tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S,
			TMPFILE_GROUP, NULL);
	if (unlink(tmp_filename))
		printl(2, _("Unable to remove the temporary file.\n"));
}


/* 
   Save the received ROM dump 
*/
static void on_ok_fsel7(GtkFileSelection * file_selector,
			gpointer user_data)
{
	gchar *tmp_filename;
	G_CONST_RETURN gchar *s;
	gchar *dst_filename;
	s = gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
	if (tifiles_get_extension(s) == NULL)
		dst_filename = g_strconcat(s, ".rom", NULL);

	else
		dst_filename = g_strdup(s);
	tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S,
			TMPFILE_ROMDUMP, NULL);
	tilp_file_move_with_check(tmp_filename, dst_filename);
	g_free(dst_filename);

	/*tilp_dirlist_local();
	   clist_refresh();
	   labels_refresh(); */
}
static void on_cancel_fsel7(GtkFileSelection * file_selector,
			    gpointer user_data)
{
	char *tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S,
			TMPFILE_ROMDUMP, NULL);
	if (unlink(tmp_filename))
		printl(2, _("Unable to remove the temporary file.\n"));
}
gint display_fileselection_1(void)
{
	return 0;
}


/* Send backup */
gint display_fileselection_2(void)
{
	GtkWidget *fs;
	gchar *mask;
	fs = gtk_file_selection_new("Select a File.");
	mask = g_strconcat("*.", tifiles_backup_file_ext(), NULL);
	gtk_file_selection_complete(GTK_FILE_SELECTION(fs), mask);
	g_free(mask);
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_fsel2), fs);
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
	return 0;
}


/* Receive backup */
gint display_fileselection_3(void)
{
	GtkWidget *fs;
	gchar *mask;
	fs = gtk_file_selection_new("Select a File.");
	mask = g_strconcat("*.", tifiles_backup_file_ext(), NULL);
	gtk_file_selection_complete(GTK_FILE_SELECTION(fs), mask);
	g_free(mask);
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_fsel3), fs);
	g_signal_connect(GTK_OBJECT
			 (GTK_FILE_SELECTION(fs)->cancel_button),
			 "clicked", G_CALLBACK(on_cancel_fsel3), fs);
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
	return 0;
}


/* Group */
gint display_fileselection_4(void)
{
	GtkWidget *fs;
	gchar *mask;
	fs = gtk_file_selection_new("Select a File.");
	mask = g_strconcat("*.", tifiles_group_file_ext(), NULL);
	gtk_file_selection_complete(GTK_FILE_SELECTION(fs), mask);
	g_free(mask);
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_fsel4), fs);
	g_signal_connect(GTK_OBJECT
			 (GTK_FILE_SELECTION(fs)->cancel_button),
			 "clicked", G_CALLBACK(on_cancel_fsel4), fs);
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
	return 0;
}

gint display_fileselection_5(void)
{
	return 0;
}

gint display_fileselection_6(void)
{
	return 0;
}


/* ROM dumping */
gint display_fileselection_7(void)
{
	GtkWidget *fs;
	fs = gtk_file_selection_new("Select a File.");
	gtk_file_selection_complete(GTK_FILE_SELECTION(fs), "*.rom");
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(on_ok_fsel7), fs);
	g_signal_connect(GTK_OBJECT
			 (GTK_FILE_SELECTION(fs)->cancel_button),
			 "clicked", G_CALLBACK(on_cancel_fsel7), fs);
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
	return 0;
}

gint display_fileselection_8(void)
{
	return 0;
}

gint display_fileselection_9(void)
{
	return 0;
}

gint display_fileselection_10(void)
{
	return 0;
}


/* */
