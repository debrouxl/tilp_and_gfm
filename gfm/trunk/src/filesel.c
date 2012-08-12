/* Hey EMACS -*- linux-c -*- */
/* $Id: filesel.c 3358 2007-05-06 07:34:42Z kevinkofler $ */

/*  TiLP - Tilp Is a Linking Program
 *
 *  Copyright (c) 2000-2001, Thomas Corvazier, Romain Lievin
 *  Copyright (c) 2001-2003, Romain Lievin
 *  Copyright (c) 2003, Julien Blache
 *  Copyright (c) 2004, Romain Liévin
 *  Copyright (c) 2005-2007, Romain Liévin, Kevin Kofler
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details. *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 */

/* 
	Some information about these file selectors: starting at tifiles2-v0.0.6, we
	use the 'glib filename encoding' scheme for charset encoding of filenames:
	- UTF-8 charset on Windows,
	- locale charset on Linux (usually UTF-8 but this is not always true).

	GTK+ always uses UTF-8 for widgets (label, file selectors, ...) thus some conversions
	may be needed.
*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#ifdef __WIN32__
#include <windows.h>
#include <wchar.h>
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)))
	typedef OPENFILENAME OPENFILENAME_MAYALIAS __attribute__((may_alias));
#else
	typedef OPENFILENAME OPENFILENAME_MAYALIAS;
#endif
#endif

#if WITH_KDE
#include "kde.h"
#endif

#include "support.h"
#include "filesel.h"

static int fs_type = 2;

/* Single file selectors */

static gchar *fname = NULL;

// GTK >= 2.4
static const gchar* create_fsel_2(const gchar *dirname, const gchar *filename, const gchar *ext, gboolean save)
{
	GtkWidget *dialog;
	GtkFileFilter *filter;
	gchar *path, *tmp;
	gchar **sarray;
	gint i;
	gchar *sfilename, *sext;

	// gtk_file_chooser_set_current_name and gtk_file_filter_add_pattern ALWAYS want UTF-8.
	sfilename = filename ? g_filename_to_utf8(filename,-1,NULL,NULL,NULL) : NULL;
	sext = ext ? g_filename_to_utf8(ext,-1,NULL,NULL,NULL) : NULL;
    
	// create box
	dialog = gtk_file_chooser_dialog_new (
					  save ? "Save File" : "Open File",
				      NULL,
					  save ? GTK_FILE_CHOOSER_ACTION_SAVE : GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

	// set default folder
	tmp = g_strconcat(dirname, G_DIR_SEPARATOR_S, NULL);	// add leading '/' otherwise get_dirname is confused
	path = g_path_get_dirname(tmp);
	g_free(tmp);

	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), path);
	g_free(path);

	// set default name
	if(filename)
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), sfilename);

	// set wildcards
	filter = gtk_file_filter_new();
	sarray = g_strsplit(sext, ";", -1);
	for(i = 0; sarray[i] != NULL; i++)
		gtk_file_filter_add_pattern (filter, sarray[i]);
	g_strfreev(sarray);
	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

	// get result
	g_free(fname);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
		fname = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	else
		fname = NULL;
	gtk_widget_destroy (dialog);

	g_free(sfilename);
	g_free(sext);

	return fname;
}

// WIN32
static const gchar* create_fsel_3(const gchar *dirname, const gchar *filename, const gchar *ext, gboolean save)
{
#ifdef WIN32
	OPENFILENAME_MAYALIAS o;
	char lpstrFile[2048] = "\0";
	char lpstrFilter[512];
	char *p;
	gchar **sarray;
	int i, n;
	int have_widechar = G_WIN32_HAVE_WIDECHAR_API();
	void *sdirname;

	// clear structure
	memset (&o, 0, sizeof(OPENFILENAME));

	// set default filename
	if(filename)
	{
		void *temp;
		if (have_widechar)
		{
			temp = g_utf8_to_utf16(filename,-1,NULL,NULL,NULL);
			if(!temp) return NULL;
			wcsncpy((wchar_t *)lpstrFile, temp, sizeof(lpstrFile)>>1);
		}
		else
		{
			temp = g_locale_from_utf8(filename,-1,NULL,NULL,NULL);
			if(!temp) return NULL;
			strncpy(lpstrFile, temp, sizeof(lpstrFile));
		}
		g_free(temp);
	}

	// format filter
	sarray = g_strsplit(ext, "|", -1);
	for(n = 0; sarray[n] != NULL; n++);

	for(i = 0, p = lpstrFilter; i < n; i++)
	{
		void *temp;
		if (have_widechar)
		{
			temp = g_utf8_to_utf16(sarray[i],-1,NULL,NULL,NULL);
			wcscpy((wchar_t *)p,temp);
			p += (wcslen(temp)<<1);
			*p++ = '\0';
			*p++ = '\0';
			wcscpy((wchar_t *)p,temp);
			p += (wcslen(temp)<<1);
			*p++ = '\0';
			*p++ = '\0';
		}
		else
		{
			temp = g_locale_from_utf8(sarray[i],-1,NULL,NULL,NULL);
			strcpy(p,temp);
			p += strlen(temp);
			*p++ = '\0';
			strcpy(p,temp);
			p += strlen(temp);
			*p++ = '\0';
		}
		g_free(temp);
	}
	*p++ = '\0';
	if (have_widechar)
		*p++ = '\0';
	g_strfreev(sarray);

	// set structure
	o.lStructSize = sizeof (o);	
	o.lpstrFilter = lpstrFilter;	//"All\0*.*\0Text\0*.TXT\0";
	o.lpstrFile = lpstrFile;
	if (have_widechar)
	{
		o.nMaxFile = sizeof(lpstrFile) >> 1;
		sdirname = g_utf8_to_utf16(dirname,-1,NULL,NULL,NULL);
	}
	else
	{
		o.nMaxFile = sizeof(lpstrFile);
		sdirname = g_locale_from_utf8(dirname,-1,NULL,NULL,NULL);
	}
	o.lpstrInitialDir = sdirname;
	o.Flags = 0x02000000 | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
				 OFN_NOCHANGEDIR | OFN_EXPLORER | OFN_LONGNAMES | OFN_NONETWORKBUTTON;

	// open/close
	if(save)
	{
		if(!(have_widechar ? GetSaveFileNameW((OPENFILENAMEW *)&o) : GetSaveFileName((OPENFILENAME *)&o)))
		{
			g_free(sdirname);
			return fname = NULL;
		}
	}
	else
	{
		if(!(have_widechar ? GetOpenFileNameW((OPENFILENAMEW *)&o) : GetOpenFileName((OPENFILENAME *)&o)))
		{
			g_free(sdirname);
			return fname = NULL;
		}
	}

	g_free(sdirname);

	if (have_widechar)
		fname = g_utf16_to_utf8((wchar_t *)lpstrFile,-1,NULL,NULL,NULL);
	else
		fname = g_locale_to_utf8(lpstrFile,-1,NULL,NULL,NULL);
	return fname;
#endif

	return NULL;
}

// KDE
static const gchar* create_fsel_4(const gchar *dirname, const gchar *filename, const gchar *ext, gboolean save)
{
#if WITH_KDE
	gchar *p;
	gchar *extspaces = g_strdup(ext);

	p = extspaces;
	while ((p = strchr(p, ';'))) *p = ' ';

	if(save)
	{
		if (filename)
			dirname = g_strconcat(dirname, "/", filename, NULL);
		fname = sp_kde_get_write_filename(dirname, extspaces, _("Save file"));
	}
	else
		fname = sp_kde_get_open_filename(dirname, extspaces, _("Open file"));

	g_free(extspaces);
	return fname;
#endif

	return NULL;
}

// Front-end
const gchar *create_fsel(const gchar *dirname, const gchar *filename, const gchar *ext, gboolean save)
{
#ifndef __WIN32__
	if(fs_type == 2)
	{
#if WITH_KDE
		const char *p = getenv("KDE_FULL_SESSION");
		if (p && *p) // KDE is running
			fs_type = 3;
		else
#endif
			fs_type = 1;
	}
#endif
#if !WITH_KDE
	if(fs_type == 3)
		fs_type = 1;
#endif
	//printf("%i: <%s> <%s> <%s> %i\n", fs_type, dirname, filename, ext, save);

	switch(fs_type)
	{
	case 0:
	case 1:	return create_fsel_2(dirname, filename, ext, save);
	case 2: return create_fsel_3(dirname, filename, ext, save);
	case 3: return create_fsel_4(dirname, filename, ext, save);
	default: return NULL;
	}

	return NULL;
}

/* Multiple files selectors */

static gchar** filenames = NULL;

// GTK >= 2.4
static gchar** create_fsels_2(const gchar *dirname, const gchar *filename, const gchar *ext)
{
	GtkWidget *dialog;
	GtkFileFilter *filter;
	gchar *path;
	gchar **sarray;
	gint i;
	gchar *sfilename, *sext;

	// gtk_file_chooser_set_current_name and gtk_file_filter_add_pattern ALWAYS want UTF-8.
	sfilename = filename ? g_filename_to_utf8(filename,-1,NULL,NULL,NULL) : NULL;
	sext = ext ? g_filename_to_utf8(ext,-1,NULL,NULL,NULL) : NULL;
    
	// create box
	dialog = gtk_file_chooser_dialog_new ("Open File",
				      NULL,
					  GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

	// set default folder
	path = g_path_get_dirname(dirname);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), path);
	g_free(path);

	// set multiple selection
	gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);

	// set default name
	if(filename)
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), sfilename);

	// set wildcards
	filter = gtk_file_filter_new();
	sarray = g_strsplit(sext, ";", -1);
	for(i = 0; sarray[i] != NULL; i++)
		gtk_file_filter_add_pattern (filter, sarray[i]);
	g_strfreev(sarray);
	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

	// get result
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		GSList *list, *p;
		gchar **q;

		// convert list into string array
		list=gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER (dialog));
	      
		filenames = (gchar **)g_malloc0((g_slist_length(list)+1) * 
						sizeof(gchar *));
		for(p = list, q = filenames; p; p = g_slist_next(p), q++)
			*q = p->data;
		*q = NULL;
		     
		g_slist_free(list);
	}
	else
		filenames = NULL;
	gtk_widget_destroy (dialog);

	g_free(sfilename);
	g_free(sext);

	return filenames;
}

// WIN32
static gchar** create_fsels_3(const gchar *dirname, const gchar *filename, const gchar *ext)
{
#ifdef WIN32
	OPENFILENAME_MAYALIAS o;
	char lpstrFile[2048] = "\0";
	char lpstrFilter[512];
	char *p;
	gchar **sarray;
	int i, n;
	int have_widechar = G_WIN32_HAVE_WIDECHAR_API();
	void *sdirname;
	gchar *temp1;

	// clear structure
	memset (&o, 0, sizeof(OPENFILENAME));

	// set default filename
	if(filename)
	{
		void *temp;
		if (have_widechar)
		{
			temp = g_utf8_to_utf16(filename,-1,NULL,NULL,NULL);
			if(!temp) return NULL;
			wcsncpy((wchar_t *)lpstrFile, temp, sizeof(lpstrFile)>>1);
		}
		else
		{
			temp = g_locale_from_utf8(filename,-1,NULL,NULL,NULL);
			if(!temp) return NULL;
			strncpy(lpstrFile, temp, sizeof(lpstrFile));
		}
		g_free(temp);
	}

	// format filter
	sarray = g_strsplit(ext, "|", -1);
	for(n = 0; sarray[n] != NULL; n++);

	for(i = 0, p = lpstrFilter; i < n; i++)
	{
		void *temp;
		if (have_widechar)
		{
			temp = g_utf8_to_utf16(sarray[i],-1,NULL,NULL,NULL);
			wcscpy((wchar_t *)p,temp);
			p += (wcslen(temp)<<1);
			*p++ = '\0';
			*p++ = '\0';
			wcscpy((wchar_t *)p,temp);
			p += (wcslen(temp)<<1);
			*p++ = '\0';
			*p++ = '\0';
		}
		else
		{
			temp = g_locale_from_utf8(sarray[i],-1,NULL,NULL,NULL);
			strcpy(p,temp);
			p += strlen(temp);
			*p++ = '\0';
			strcpy(p,temp);
			p += strlen(temp);
			*p++ = '\0';
		}
		g_free(temp);
	}
	*p++ = '\0';
	if (have_widechar)
		*p++ = '\0';
	g_strfreev(sarray);

	// set structure
	o.lStructSize = sizeof (o);	
	o.lpstrFilter = lpstrFilter;	//"All\0*.*\0Text\0*.TXT\0";
	o.lpstrFile = lpstrFile;		//"C:\msvc\tilp\0foo.txt\0bar.txt"
	if (have_widechar)
	{
		o.nMaxFile = sizeof(lpstrFile) >> 1;
		sdirname = g_utf8_to_utf16(dirname,-1,NULL,NULL,NULL);
	}
	else
	{
		o.nMaxFile = sizeof(lpstrFile);
		sdirname = g_locale_from_utf8(dirname,-1,NULL,NULL,NULL);
	}
	o.lpstrInitialDir = sdirname;
	o.Flags = 0x02000000 | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
				 OFN_NOCHANGEDIR | OFN_EXPLORER | OFN_LONGNAMES | OFN_NONETWORKBUTTON |
				 OFN_ALLOWMULTISELECT;

	// open selector
	if(!(have_widechar ? GetOpenFileNameW((OPENFILENAMEW *)&o) : GetOpenFileName((OPENFILENAME *)&o)))
	{
		g_free(sdirname);
		return NULL;
	}
	filenames = NULL;

	// converts resulting string
	if (have_widechar)
		temp1 = g_utf16_to_utf8((wchar_t *)lpstrFile,-1,NULL,NULL,NULL);
	else
		temp1 = g_locale_to_utf8(lpstrFile,-1,NULL,NULL,NULL);
	for(p = lpstrFile, i=0; *p;
	    p += have_widechar?((wcslen((wchar_t *)p)+1)<<1):(strlen(p)+1), i++)
	{
		if(i)	// skip directory
		{
			gchar *temp;
			filenames = g_realloc(filenames, (i+1) * sizeof(gchar *));
			if (have_widechar)
				temp = g_utf16_to_utf8((wchar_t *)p,-1,NULL,NULL,NULL);
			else
				temp = g_locale_to_utf8(p,-1,NULL,NULL,NULL);
			filenames[i-1] = g_strconcat(temp1, G_DIR_SEPARATOR_S, temp, NULL);
			g_free(temp);
		}
	}
	g_free(temp1);

	// one file selected ?
	if(i == 1)
	{
		filenames = g_malloc(2 * sizeof(gchar *));
		if (have_widechar)
			filenames[0] = g_utf16_to_utf8((wchar_t *)lpstrFile,-1,NULL,NULL,NULL);
		else
			filenames[0] = g_locale_to_utf8(lpstrFile,-1,NULL,NULL,NULL);
		filenames[1] = NULL;
	}
	else
		filenames[i-1] = NULL;

	g_free(sdirname);

	return filenames;
#endif

	return NULL;
}

static gchar** create_fsels_4(const gchar *dirname, const gchar *filename, const gchar *ext)
{
#if WITH_KDE
	gchar *p;
	gchar *extspaces = g_strdup(ext);
	p = extspaces;
	while ((p = strchr(p, ';'))) *p = ' ';
	filenames = sp_kde_get_open_filenames(dirname, extspaces, _("Open file"));
	g_free(extspaces);
	return filenames;
#endif

	return NULL;
}

// Front-end
gchar** create_fsels(const gchar *dirname, const gchar *filename, const gchar *ext)
{
#ifndef __WIN32__
	if(fs_type == 2)
	{
#if WITH_KDE
		const char *p = getenv("KDE_FULL_SESSION");
		if (p && *p) // KDE is running
			fs_type = 3;
		else
#endif
			fs_type = 1;
	}
#endif
#if !WITH_KDE
	if(fs_type == 3)
		fs_type = 1;
#endif
	//printf("%i: <%s> <%s> <%s>\n", options.fs_type, dirname, filename, ext);

	switch(fs_type)
	{
	case 0:
	case 1:	return create_fsels_2(dirname, filename, ext);
	case 2: return create_fsels_3(dirname, filename, ext);
	case 3: return create_fsels_4(dirname, filename, ext);
	default: return NULL;
	}

	return NULL;
}
