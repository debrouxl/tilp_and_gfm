/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
	This file contains utility functions about files, attributes,
	sorting routines for selection, ...
	These functions are mainly used by the right window.
*/

/* 
	Some informations about these file selectors: starting at tifiles2-v0.0.6, we
	use the 'glib filename encoding' scheme for charset encoding of filenames:
	- UTF-8 charset on Windows,
	- locale charset on Linux (usually UTF-8 but this is not always true).

	GTK+ always uses UTF-8 for widgets (label, file selectors, ...) thus some conversions
	may be needed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#ifdef __WIN32__
#include <windows.h>
#endif

#include <glib.h>
#include <glib/gstdio.h>

#ifndef __WIN32__
# include <pwd.h>
# include <grp.h>
#endif

#ifdef _MSC_VER
# include "../build/msvc/dirent.h"	// for S_ISDIR use
#endif

#include "tilp_core.h"

/* File operations */

#ifndef __WIN32__
int tilp_file_copy(const char *src, const char *dst)
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

int tilp_file_copy(const char *src, const char *dst)
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

int tilp_file_move(const char *src, const char *dst)
{
	if(tilp_file_copy(src, dst) < 0)	//if(g_rename(src, dst) < 0)
	{
		gif->msg_box1(_("Information"), _("Unable to move file.\n\n"));
		return -1;
	}
	tilp_file_delete(src);

	return 0;
}


int tilp_file_delete(const char *f)
{
	if(g_unlink(f) < 0)
	{
		gif->msg_box1(_("Information"), _("Unable to remove the file !"));
		return -1;
	}

	return 0;
}


int tilp_file_mkdir(const char *pathname)
{
	int mode;

#ifdef __WIN32__
	mode = S_IRWXU;
#else
	mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
#endif
	if(g_mkdir(pathname, mode) < 0)
	{
		gif->msg_box1(_("Information"), _("Unable to create the directory.\n\n"));
		return -1;
	}

	return 0;
}

int tilp_file_exist(const char* filename)
{
	return g_file_test(filename, G_FILE_TEST_EXISTS);
}

/* 
   Check for file existence. If file already exists, ask for an
   action (skip, overwrite/rename or exit).
   Return 0 if skipped, 1 if renamed/overwritten, -1 if exited.
*/
int tilp_file_check(const char *src, char **dst)
{
	int ret;
	char buffer[2048];
	char *dirname;
	*dst = NULL;

	if (options.overwrite == CONFIRM_YES) 
	{
		if (tilp_file_exist(src)) 
		{
			sprintf(buffer, _("The file %s already exists.\nOverwrite ?"), src);
			ret =
			    gif->msg_box3(_("Warning"), buffer,
					_("Overwrite "), _("Rename "), _("Skip "));

			switch (ret) 
			{
			case BUTTON1:	// overwrite
				*dst = g_strdup(src);
				return 1;
			case BUTTON2:	// rename
				dirname =
				    gif->msg_entry(_("Rename the file"),
						   _("New name: "), src);
					if (dirname == NULL)
						return 0;
					*dst = g_strdup(dirname);
					g_free(dirname);
				return 1;
			case BUTTON3:	// skip
				return 0;
			default:		// close
				return -1;
			}
		} 
		else 
		{
			*dst = g_strdup(src);
			return !0;
		}
	} 
	else 
	{
		*dst = g_strdup(src);
		return !0;
	}

	return !0;
}


/*
  Try and move a file. If file already exists, ask for an action
  (skip, overwrite/rename or exit)
  Return 0 if skipped, 1 if renamed/overwritten, -1 if exited.
*/
int tilp_file_move_with_check(const char *src, const char *dst)
{
	char *dst2;

	switch(tilp_file_check(dst, &dst2))
	{
	case 1:
		if (tilp_file_move(src, dst2)) 
		{
			gif->msg_box1(_("Error"), _("Unable to move the temporary file.\n"));
			g_free(dst2);
			return 0;
		}
	case -1:
		return -1;
	case 0:
		g_free(dst2);
		return 0;
	}

	g_free(dst2);
	return -1;
}

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

int tilp_file_chdir(const char *path)
{
	if (g_chdir(path)) 
	{
		gif->msg_box1(_("Error"), _("Unable to change directory."));
		return -1;
	}

	return 0;
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

/* Attributes */

#ifndef __WIN32__
const char *tilp_file_get_attributes(FileEntry * fi)
{
	static char buffer[16];
	char *s;
	s = g_strdup(" ---------- ");
	if (fi->attrib & S_IRUSR)
		s[2] = 'r';
	if (fi->attrib & S_IWUSR)
		s[3] = 'w';
	if (fi->attrib & S_ISUID) {
		if (fi->attrib & S_IXUSR)
			s[4] = 's';
		else
			s[4] = 'S';
	}

	else if (fi->attrib & S_IXUSR)
		s[4] = 'x';
	if (fi->attrib & S_IRGRP)
		s[5] = 'r';
	if (fi->attrib & S_IWGRP)
		s[6] = 'w';
	if (fi->attrib & S_ISGID) {
		if (fi->attrib & S_IXGRP)
			s[7] = 's';

		else
			s[7] = 'S';
	}

	else if (fi->attrib & S_IXGRP)
		s[7] = 'x';
	if (fi->attrib & S_IROTH)
		s[8] = 'r';
	if (fi->attrib & S_IWOTH)
		s[9] = 'w';
	if (fi->attrib & S_ISVTX) {
		if (fi->attrib & S_IXOTH)
			s[10] = 't';

		else
			s[10] = 'T';
	}

	else if (fi->attrib & S_IXOTH)
		s[10] = 'x';

#ifndef __WIN32__
	if (S_ISLNK(fi->attrib)) {
		s[1] = 'l';
		strncpy(buffer, s, 16);
		return buffer;
	}
#endif				
	switch (S_IFMT & fi->attrib) {
	case S_IFBLK:
		s[1] = 'b';
		break;
	case S_IFDIR:
		s[1] = 'd';
		break;
	case S_IFCHR:
		s[1] = 'c';
		break;
	case S_IFIFO:
		s[1] = 'p';
		break;
	case S_IFSOCK:
		s[1] = 's';
		break;
	}
	strncpy(buffer, s, 16);
	return buffer;
}


#endif				
void tilp_file_get_user_name(FileEntry * fi, char **name)
{
#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
	struct passwd *pwuid;

	if ((pwuid = getpwuid(fi->user)) == NULL) 
	{
		*name = NULL;
	}
	else 
	{
		*name = g_strdup(pwuid->pw_name);
	}
#else				
	*name = NULL;

#endif				
} 

void tilp_file_get_group_name(FileEntry * fi, char **name)
{
#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
	struct group *grpid;

	if ((grpid = getgrgid(fi->group)) == NULL) 
	{
		*name = NULL;
	}
	else 
	{
		*name = g_strdup(grpid->gr_name);
	}

#else				
	*name = NULL;
#endif				
} 

const char *tilp_file_get_date(FileEntry * fi)
{
	static char buffer[32];
	int i;
	char *p;

	p = ctime(&(fi->date));

	for (i = 4; i < 11; i++) 
	{
		buffer[i - 4] = *(p + i);
	}

	for (i = 20; i < 24; i++) 
	{
		buffer[i - 13] = *(p + i);
	}
	buffer[i - 13] = '\0';

	return buffer;
}


const char *tilp_file_get_size(FileEntry * fi)
{
	static char buffer[32];

	if (fi->size < 1024)
		g_snprintf(buffer, 32, "  %i", (int) fi->size);

	else if ((fi->size > 1024) && (fi->size < 1024 * 1024))
		g_snprintf(buffer, 32, "%i KB", (int) fi->size >> 10);

	else if (fi->size > 1024 * 1024)
		g_snprintf(buffer, 32, "%i MB", (int) fi->size >> 20);

	return buffer;
}

const char *tilp_file_get_type(FileEntry * fi)
{
	static char buffer[32];

    if (S_ISDIR(fi->attrib))
        return "";

	strncpy(buffer, tifiles_file_get_type(fi->name), 32);

	return buffer;
}

/* Directory listing */

static void free_file_info_struct(gpointer data)
{
	FileEntry *fi = data;

	g_free(fi->name);
	//ticalc_destroy_action_array(fi->actions);
	g_free(fi);
}

/* 
Make a directory listing of the current directory and place the result 
   in the local.dirlist GList 
*/
int tilp_file_dirlist(void)
{
	GDir *dir;
	GError *error;
	G_CONST_RETURN gchar *dirname;
	struct stat f_info;
	FileEntry *fi;

	dir = g_dir_open(local.cwdir, 0, &error);
	if (dir == NULL) 
	{
		gif->msg_box1("Error", "Unable to open directory !");
		return -1;
	}

	if (local.dirlist != NULL) 
	{
		g_list_foreach(local.dirlist,
			       (GFunc) free_file_info_struct, NULL);
		g_list_free(local.dirlist);
		local.dirlist = NULL;
	}

	// add the ".." entry (b/c stripped by g_dir_read_name
	fi = (FileEntry *) g_malloc0(sizeof(FileEntry));
	fi->name = g_strdup("..");
	if (!stat(fi->name, &f_info)) 
	{
		fi->date = f_info.st_mtime;
		fi->size = f_info.st_size;
		fi->attrib = f_info.st_mode;
	}

	local.dirlist = g_list_prepend(local.dirlist, (gpointer) fi);

	while ((dirname = g_dir_read_name(dir)) != NULL) 
	{
		if (dirname[0] == '.')
			continue;

		fi = (FileEntry *) g_malloc0(sizeof(FileEntry));
		fi->name = g_strdup(dirname);

		if (!g_stat(fi->name, &f_info)) 
		{
			fi->date = f_info.st_mtime;
			fi->size = f_info.st_size;
			fi->attrib = f_info.st_mode;
		}

		local.dirlist = g_list_prepend(local.dirlist, (gpointer) fi);
	}

	g_dir_close(dir);

	return 0;
}

int tilp_dirlist_local(void)
{
	return tilp_file_dirlist();
}

/* Sorting */

#ifdef __WIN32__
# define str_cmp	_stricmp
#else
# define str_cmp	strcasecmp
#endif

static gint sort_by_name(gconstpointer a, gconstpointer b)
{
	FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;

	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR))) 
		return str_cmp(fa->name, fb->name);
	else if (((fb->attrib & S_IFMT) == S_IFDIR) && str_cmp(fa->name, fb->name)) 
		return !0;

	return 0;
}

void tilp_file_sort_by_name(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_name);
	if(!options.local_sort_order)
		local.dirlist = g_list_reverse(local.dirlist);
}

static gint sort_by_type(gconstpointer a, gconstpointer b)
{
	FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;
#if 1
	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR))) 
		return strcmp(tifiles_file_get_type(fa->name), tifiles_file_get_type(fb->name));
	else if (((fb->attrib & S_IFMT) == S_IFDIR) && strcmp(tifiles_file_get_type(fa->name), tifiles_file_get_type(fb->name)))
		return !0;

	return 0;
#else
	return ((fb->attrib & S_IFMT) == S_IFDIR);
#endif
}

void tilp_file_sort_by_type(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_type);

	if(!options.local_sort_order)
		local.dirlist = g_list_reverse(local.dirlist);
}

static gint sort_by_date(gconstpointer a, gconstpointer b)
{
	FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;

	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR))) 
		return (fa->date > fb->date);
	else if (((fb->attrib & S_IFMT) == S_IFDIR) && (fa->date > fb->date)) 
		return !0;

	return 0;
}

void tilp_file_sort_by_date(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_date);
	if(!options.local_sort_order)
		local.dirlist = g_list_reverse(local.dirlist);
}

static gint sort_by_size(gconstpointer a, gconstpointer b)
{
	FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;

	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR))) 
		return (fa->size > fb->size);
	else if (((fb->attrib & S_IFMT) == S_IFDIR) && (fa->size > fb->size)) 
		return !0;

	return 0;
}

void tilp_file_sort_by_size(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_size);
	if(!options.local_sort_order)
		local.dirlist = g_list_reverse(local.dirlist);
}

static gint sort_by_attrib(gconstpointer a, gconstpointer b)
{
	FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;

	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR))) 
	{
		if (fa->attrib > fb->attrib)
			return !0;
	}
	else 
	{
		if (((fb->attrib & S_IFMT) == S_IFDIR) && (fa->attrib > fb->attrib)) 
			return !0;
	}

	return 0;
}

void tilp_file_sort_by_attrib(void)
{
	local.dirlist = g_list_sort(local.dirlist, sort_by_attrib);
	if(!options.local_sort_order)
		local.dirlist = g_list_reverse(local.dirlist);
}
