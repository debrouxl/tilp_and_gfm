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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "release.h"
#include "tilp_core.h"
gint display_release_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkTextBuffer *txtbuf;
	GtkWidget *text;
	FILE *fd;
	gchar *filename;
	gchar buffer[32768];
	gint len = 0;
	struct stat stbuf;
	gint result;

#ifdef __WIN32__
	filename = g_strconcat(inst_paths.base_dir, "Release.txt", NULL);

#else				/*  */
	filename = g_strconcat(inst_paths.base_dir, "RELEASE", NULL);

#endif				/*  */
	if (access(filename, F_OK) == 0) {
		if (stat(filename, &stbuf) != -1) {
			len = stbuf.st_size;
			len -= 2;
		}
		if ((fd = fopen(filename, "r")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			len = fread(buffer, 1, len, fd);
			fclose(fd);
		}
	}
	xml = glade_xml_new
	    (tilp_paths_build_glade("release-2.glade"), "release_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);
	dbox = glade_xml_get_widget(xml, "release_dbox");
	text = glade_xml_get_widget(xml, "textview1");
	txtbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	gtk_text_buffer_set_text(txtbuf, buffer, len);
	while (gtk_events_pending())
		gtk_main_iteration();
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) {
	case GTK_RESPONSE_OK:
		break;
	default:
		break;
	}
	gtk_widget_destroy(dbox);
	return 0;
}
