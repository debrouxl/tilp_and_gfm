/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  29/05/06 17:51 - file.c

  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/*
	File Selector and GLADE checks.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include "tilibs.h"

#include "dialog.h"
#include "file.h"
#include "paths.h"
#include "support.h"

/* File Exist Function */
int file_exists(const char *filename)
{
    FILE *fpointer;

    // Does it exist?
    if ((fpointer = fopen(filename, "r")) == NULL)
        return 0;
    else
        fclose(fpointer);

    return 1;
}

/* Check to see if we have all of our Glade Files */
void glade_files_check(void)
{
    const char *glade_files[] = {
        "dialogs.glade",
        "gfm.glade",
    };
    short i, num_files;
    gchar *msg;
    num_files = sizeof(glade_files) / sizeof(char *);

    // Loop em all up!
    for (i=0; i<num_files; i++)
    {
        if (!file_exists((const char *)gfm_paths_build_glade(glade_files[i])))
        {
            msg = g_strconcat("Could not find: <b>",
                              glade_files[i],
                              "</b> GUI File in '",
                              inst_paths.glade_dir,
                              "' directory!", NULL);
            msgbox_error(msg);
            g_free(msg);
            exit(-1); // Exit
        }
    }

    // Return
    return;
}

static gchar *fname = NULL;
static gint action = 0;

static void store_filename(GtkFileSelection * file_selector,
			   gpointer user_data)
{
	fname = g_strdup((gchar *)gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data)));
	action = 1;
} 

static void cancel_filename(GtkButton * button, gpointer user_data)
{
	fname = NULL;
	action = 2;
} 

// GTK 1.x/2.x (x < 4)
const gchar* file_selector(gchar *dirname, gchar *filename, gchar *ext, gboolean save)
{
	GtkWidget *fs;
	gchar *sfilename, *sext, *path;

	// gtk_file_selection_complete ALWAYS wants UTF-8.
	sfilename = filename ? g_filename_to_utf8(filename,-1,NULL,NULL,NULL) : NULL;
	sext = ext ? g_filename_to_utf8(ext,-1,NULL,NULL,NULL) : NULL;
    
	if(save)
		fs = gtk_file_selection_new(_("Save a file..."));
	else
		fs = gtk_file_selection_new(_("Open a file..."));

	// set default folder
	path = g_strconcat(dirname, G_DIR_SEPARATOR_S, NULL);
	gtk_file_selection_set_filename (GTK_FILE_SELECTION(fs), path);
	g_free(path);

	// set default name
	gtk_file_selection_complete(GTK_FILE_SELECTION(fs), sfilename ? sfilename : sext);

	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked", G_CALLBACK(store_filename), fs);

	g_signal_connect(GTK_OBJECT
			 (GTK_FILE_SELECTION(fs)->cancel_button),
			 "clicked", G_CALLBACK(cancel_filename), fs);

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

	g_free(fname);
	for(action = 0; !action; )
		GTK_REFRESH();

	g_free(sfilename);
	g_free(sext);

	return fname;
}

/* Replace any invalid chars in the filename by an underscore '_' */
char *tilp_file_underscorize(char *s)
{
	int i, j;
	char tokens[] = "/\\:*?\"<>|- ";
	for (i = 0; i < (int)strlen(s); i++) {
		for (j = 0; j < (int)strlen(tokens); j++) {
			if (s[i] == tokens[j])
				s[i] = '_';
		}
	}
	return s;
}

/* Misc */

void tilp_var_get_size(VarEntry* vi, char **buf)
{
	char buffer[256];

	if (vi->size < 1024)
		sprintf(buffer, "  %i", (int) vi->size);

	else if ((vi->size > 1024) && (vi->size < 1024 * 1024))
		sprintf(buffer, "%i KB", (int) vi->size >> 10);

	else if (vi->size > 1024 * 1024)
		sprintf(buffer, "%i MB", (int) vi->size >> 20);

	*buf = g_strdup(buffer);
}

void tilp_vars_translate(char *utf8)
{
#ifdef __WIN32__
	int i;

	// Scan for lowerscript
	for(i = 0; utf8[i] && i < (int)strlen(utf8)-2; i++)
	{
		if((unsigned char)utf8[i+0] == 0xE2)
			if((unsigned char)utf8[i+1] == 0x82)
				if((unsigned char)utf8[i+2] >= 0x80 && 
					(unsigned char)utf8[i+2] <= 0x89)
				{
					int c = (unsigned char)utf8[i+2];

					utf8[i] = utf8[i+2] - 0x80 + '0';
					memmove(utf8+i+1, utf8+i+3, strlen(utf8+i)-2);
					break;
				}
	}

	// Scan for 't'
	for(i = 0; utf8[i] && i < (int)strlen(utf8)-2; i++)
	{
		if((unsigned char)utf8[i+0] == 0xE2)
			if((unsigned char)utf8[i+1] == 0x8A)
				if((unsigned char)utf8[i+2] == 0xBA)
				{
					int c = (unsigned char)utf8[i+2];

					utf8[i] = 't';
					memmove(utf8+i+1, utf8+i+3, strlen(utf8+i)-2);
					break;
				}
	}
#endif
}
