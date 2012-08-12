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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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
#include <glib.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#ifdef __WIN32__
#include <windows.h>
#endif
#include "tilibs.h"

#ifdef _MSC_VER
# include "../build/msvc/dirent.h"	// for S_ISDIR use
#endif

#include "dialog.h"
#include "file.h"
#include "paths.h"
#include "support.h"

#if !GLIB_CHECK_VERSION(2, 8, 0)
#include <errno.h>
//#include <direct.h>
// Code taken from Glib
int g_chdir (const gchar *path)
{
#ifdef __WIN32__
  if (G_WIN32_HAVE_WIDECHAR_API ())
    {
      wchar_t *wpath = g_utf8_to_utf16 (path, -1, NULL, NULL, NULL);
      int retval;
      int save_errno;

      if (wpath == NULL)
	{
	  errno = EINVAL;
	  return -1;
	}

      retval = _wchdir (wpath);
      save_errno = errno;

      g_free (wpath);
      
      errno = save_errno;
      return retval;
    }
  else
    {
      gchar *cp_path = g_locale_from_utf8 (path, -1, NULL, NULL, NULL);
      int retval;
      int save_errno;

      if (cp_path == NULL)
	{
	  errno = EINVAL;
	  return -1;
	}

      retval = chdir (cp_path);
      save_errno = errno;

      g_free (cp_path);

      errno = save_errno;
      return retval;
    }
#else
  return chdir (path);
#endif
}
#endif

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

#ifndef __WIN32__
int file_copy(const char *src, const char *dst)
{
	FILE *in, *out;
	int c;

	if ((in = g_fopen(src, "rb")) == NULL) 
	{
		return -1;
	}

	if ((out = g_fopen(dst, "wb")) == NULL) 
	{
		return -2;
	}

	while (!feof(in)) 
	{
		c = fgetc(in);
		if (feof(in))
			break;
		fputc(c, out);
	}

	fclose(in);
	fclose(out);

	return 0;
}

#else				

int file_copy(const char *src, const char *dst)
{
	int ret = 0;
	gchar *src_utf8 = g_filename_to_utf8(src, -1, NULL, NULL, NULL);
	gchar *dst_utf8 = g_filename_to_utf8(dst, -1, NULL, NULL, NULL);

	if(G_WIN32_HAVE_WIDECHAR_API())
	{
		gunichar2 *src_utf16 = g_utf8_to_utf16(src_utf8,-1,NULL,NULL,NULL);
		gunichar2 *dst_utf16 = g_utf8_to_utf16(dst_utf8,-1,NULL,NULL,NULL);
		
		if(src_utf16 && dst_utf16)
			if (!CopyFileW(src_utf16, dst_utf16, FALSE))
				ret = 1;
		
		g_free(src_utf16);
		g_free(dst_utf16);
	}
	else
	{
		gchar *src_loc = g_locale_from_utf8(src_utf8, -1, NULL, NULL, NULL);
		gchar *dst_loc = g_locale_from_utf8(dst_utf8, -1, NULL, NULL, NULL);	
		
		if(src_loc && dst_loc)
			if (!CopyFile(src_loc, dst_loc, FALSE))
				ret = 1;
		
		g_free(src_loc);
		g_free(dst_loc);
	}

	g_free(src_utf8);
	g_free(dst_utf8);

	return ret;
}
#endif

int file_chdir(const char *path)
{
	if (g_chdir(path)) 
	{
		msgbox_one(MSGBOX_ERROR, _("Unable to change directory."));
		return -1;
	}

	return 0;
}

int file_mkdir(const char *pathname)
{
	int mode;

#ifdef __WIN32__
	mode = S_IRWXU;
#else
	mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
#endif
	if(g_mkdir(pathname, mode) < 0)
	{
		msgbox_one(MSGBOX_ERROR, _("Unable to create the directory.\n\n"));
		return -1;
	}

	return 0;
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
        if (!file_exists((const char *)paths_build_glade(glade_files[i])))
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
		sprintf(buffer, _("%i KB"), (int) vi->size >> 10);

	else if (vi->size > 1024 * 1024)
		sprintf(buffer, _("%i MB"), (int) vi->size >> 20);

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
