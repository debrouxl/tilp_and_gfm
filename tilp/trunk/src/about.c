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
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "about.h"
#include "support.h"
#include "tilp_core.h"

static const char* authors[] =  
{
	"Romain Lievin (Linux/Win32) <roms@tilp.info>", 
	"Julien Blache (Mac OS-X) <jb@jblache.org>", 
	"Tijl Coosemans (*BSD) <tijl@ulyssis.org>", 
	NULL 
};	

static const char* documenters[] = 
{
	"Romain Lievin (Linux/Win32) <roms@tilp.info>", 
	NULL
};

static const char* artists[] = 
{
	"Jesse Palmer (icon design) <jp@jp3d.net>",
	NULL
};

gint display_about_dbox(void)
{
	GtkWidget* widget;
	GtkAboutDialog* dlg;
	GdkPixbuf *pix;

	struct stat stbuf;
	FILE *fd;
	gchar *filename;
	int len = 0;
	gchar buffer[32768];
	gchar *version;

#ifdef _MSC_VER /* MSVC builds. MinGW builds use Linux file structures. */
	filename = g_strconcat(inst_paths.base_dir, "License.txt", NULL);
#else				/*  */
	filename = g_strconcat(inst_paths.base_dir, "COPYING", NULL);
#endif				/*  */

	if (access(filename, F_OK) == 0) 
	{
		if (stat(filename, &stbuf) != -1) 
		{
			len = stbuf.st_size;
			len -= 2;
		}
		if ((fd = fopen(filename, "r")) != NULL) 
		{
			memset(buffer, 0, sizeof(buffer));
			len = fread(buffer, 1, len, fd);
			fclose(fd);
		}
	}

	version = g_strdup_printf(_("Framework version (cables=%s, files=%s, calcs=%s, ticonv=%s)"),
	     ticables_version_get(), tifiles_version_get(), ticalcs_version_get(), ticonv_version_get());

	//---

	widget = gtk_about_dialog_new();
	dlg = GTK_ABOUT_DIALOG(widget);
	pix = create_pixbuf("logo.xpm");

	gtk_about_dialog_set_name(dlg, "TiLP - Tilp Is a Linking Program - ");
	gtk_about_dialog_set_version(dlg, TILP_VERSION);
	gtk_about_dialog_set_comments(dlg, version);
	gtk_about_dialog_set_copyright(dlg, "Copyright (c) 2001-2006 The TiLP Team");
	gtk_about_dialog_set_license(dlg, buffer);
	gtk_about_dialog_set_website(dlg, "http://www.tilp.info");
	gtk_about_dialog_set_authors(dlg, authors);
	gtk_about_dialog_set_documenters(dlg, documenters);
	gtk_about_dialog_set_artists(dlg, artists);
	gtk_about_dialog_set_logo(dlg, pix);

	//gtk_show_about_dialog(NULL, "");
	gtk_widget_show_all(widget);

	return 0;
}
