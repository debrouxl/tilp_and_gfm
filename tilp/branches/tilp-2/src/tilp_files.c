/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#ifndef __MACOSX__
# include <glib.h>
#else
# include <glib/glib.h>
#endif

#ifndef __WIN32__
# include <pwd.h>
# include <grp.h>
#endif

#ifdef __WIN32__
#include "dirent.h"	// for S_ISDIR use
#endif

#include "tilp_core.h"

/* File operations */

#ifndef __WIN32__
int tilp_file_copy(const char *src, const char *dst)
{
	FILE *in, *out;
	int c;

	if ((in = fopen(src, "rb")) == NULL) 
	{
		return -1;
	}

	if ((out = fopen(dst, "wb")) == NULL) 
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
	if (!CopyFile(src, dst, FALSE))
		return -1;

	return 0;
}
#endif				

int tilp_file_move(const char *src, const char *dst)
{
#ifndef __WIN32__
	int ret = tilp_file_copy(src, dst);
	if (ret)
		return ret;
	unlink(src);
#else				
	//if (!MoveFile(src, dst))
	if(!CopyFile(src, dst, FALSE))
		return -1;
	if(!DeleteFile(src))
		return -1;
#endif				/*  %USERPROFILE%\Local Settings\Temp */
	return 0;
}


#ifdef __WIN32__
int tilp_file_delete(const char *f)
{
	if (!DeleteFile(f)/*RemoveDirectory(f)*/) 
	{
		gif->msg_box1(_("Information"), _
			     ("Unable to remove the file !"));
		return -1;
	}

	return 0;
}

#else	
			
int tilp_file_delete(const char *f)
{
	if (unlink(f) == -1) 
	{
		uid_t effective = geteuid();
		seteuid(getuid());

		if (remove(f) == -1) 
		{
			gif->msg_box1(_("Information"), _
				     ("Unable to remove the file. You can not delete non empty folders !"));
			return -1;
		}

		seteuid(effective);
	}

	return 0;
}
#endif				

#if defined(__LINUX__) || defined(__BSD__)
int tilp_file_mkdir(const char *pathname)
{
	uid_t effective = geteuid();
	seteuid(getuid());

	if (mkdir(pathname, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) 
	{
		gif->msg_box1(_("Information"), _("Unable to create the directory.\n\n"));
	}
	seteuid(effective);

	return 0;
}

#else

int tilp_file_mkdir(const char *pathname)
{
	_mkdir(pathname);
	return 0;
}
#endif				

/* 
   Check for file existence. If file already exists, ask for an
   action (skip, overwrite or rename).
   Return 0 if skipped. 
*/
int tilp_file_check(const char *src, char **dst)
{
	int ret;
	char buffer[256];
	char *dirname;
	*dst = NULL;

	if (options.overwrite == CONFIRM_YES) 
	{
		if (access(src, F_OK) == 0) 
		{
			sprintf(buffer, _("The file %s already exists.\nOverwrite ?"), src);
			ret =
			    gif->msg_box3(_("Warning"), buffer,
					  _("Overwrite "), _("Rename "),
					  _("Skip "));

			switch (ret) 
			{
			case BUTTON1:
				*dst = g_strdup(src);
				return !0;
				break;
			case BUTTON2:
				dirname =
				    gif->msg_entry(_("Rename the file"),
						   _("New name: "), src);
					if (dirname == NULL)
						return 0;
					*dst = g_strdup(dirname);
					g_free(dirname);
				return !0;
				break;
			case BUTTON3:
				return 0;
				break;
			default:
				return 0;
				break;
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
  (skip, overwrite or rename)
  Return 0 if skipped. 
*/
int tilp_file_move_with_check(const char *src, const char *dst)
{
	char *dst2;

	if (tilp_file_check(dst, &dst2)) 
	{
		if (tilp_file_move(src, dst2)) 
		{
			gif->msg_box1(_("Error"),
				     _
				     ("Unable to move the temporary file.\n"));
			g_free(dst2);
			return 0;
		}
	} 
	else 
	{
		g_free(dst2);
		return 0;
	}
	g_free(dst2);

	return !0;
}


/*
  Change directory. This functions is a wrapper for chdir.
  It manages privileges and ensure that the user can not exit from the
  HOME directory
*/
#if defined(__LINUX__) || defined(__MACOSX__)
int tilp_file_chdir(const char *path)
{
#ifndef ALLOW_EXIT_HOMEDIR
	const gchar *home_dir;
#endif /* !ALLOW_EXIT_HOMEDIR */
	gchar *curr_dir;
	uid_t effective;

	effective = geteuid();
	seteuid(getuid());

	if (chdir(path)) 
	{
		tilp_warning(_("Chdir error.\n"));
		gif->msg_box1(_("Error"), _("Unable to change directory."));
		return -1;
	}
	seteuid(effective);
	curr_dir = g_get_cwdir();

#ifndef ALLOW_EXIT_HOMEDIR
	home_dir = g_get_home_dir();

	/* If curr_dir does not begin with "home_dir"
	 * or strlen(curr_dir) < strlen(home_dir)
	 * then the user is trying to escape its home directory.
	 */
	if ((strlen(curr_dir) < strlen(home_dir)) ||
	    (strncmp(curr_dir, home_dir, strlen(home_dir)) != 0)) 
	{
		if (strcmp(curr_dir, g_get_tmp_dir())) 
		{
			chdir(home_dir);
			g_free(curr_dir);

			if (gif != NULL) 
			{
				gif->msg_box1(_("Error"), _
					     ("You can not go outside of your HOME directory."));
			} 
			else 
			{
				DISPLAY_ERROR
				    ("You can not go outside of your HOME directory.");
			}

			return -1;
		}
	}
#endif /* !ALLOW_EXIT_HOMEDIR */
	return 0;
}

#else

int tilp_file_chdir(const char *path)
{
	if (chdir(path)) 
	{
		tilp_warning(_("Chdir error.\n"));
		if (gif)
			gif->msg_box1(_("Error"), _("Unable to change directory."));
		return -1;
	}
	return 0;
}
#endif /* __LINUX__ || __MACOSX__ */

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
#if defined(__LINUX__) || defined(__BSD__)
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
#if defined(__LINUX__) || defined(__BSD__)
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


#ifdef __WIN32__
#define snprintf _snprintf
#endif

const char *tilp_file_get_size(FileEntry * fi)
{
	static char buffer[32];

	if (fi->size < 1024)
		snprintf(buffer, 32, "  %i", (int) fi->size);

	else if ((fi->size > 1024) && (fi->size < 1024 * 1024))
		snprintf(buffer, 32, "%i KB", (int) fi->size >> 10);

	else if (fi->size > 1024 * 1024)
		snprintf(buffer, 32, "%i MB", (int) fi->size >> 20);

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

#ifndef __MACOSX__
static void free_file_info_struct(gpointer data)
{
	FileEntry *fi = data;

	g_free(fi->name);
	//ticalc_destroy_action_array(fi->actions);
	g_free(fi);
}

/* 
Make a directory listing of the current directory and place the result 
   in the local_win.dirlist GList 
*/
int tilp_file_dirlist(void)
{
	GDir *dir;
	GError *error;
	G_CONST_RETURN gchar *dirname;
	struct stat f_info;
	FileEntry *fi;

	dir = g_dir_open(local_win.cwdir, 0, &error);
	if (dir == NULL) 
	{
		gif->msg_box1("Error", "Unable to open directory !");
		return -1;
	}

	if (local_win.dirlist != NULL) 
	{
		g_list_foreach(local_win.dirlist,
			       (GFunc) free_file_info_struct, NULL);
		g_list_free(local_win.dirlist);
		local_win.dirlist = NULL;
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

	local_win.dirlist = g_list_prepend(local_win.dirlist, (gpointer) fi);

	while ((dirname = g_dir_read_name(dir)) != NULL) 
	{
		if (dirname[0] == '.')
			continue;

		fi = (FileEntry *) g_malloc0(sizeof(FileEntry));
		fi->name = g_strdup(dirname);
		if (!stat(fi->name, &f_info)) 
		{
			fi->date = f_info.st_mtime;
			fi->size = f_info.st_size;
			fi->attrib = f_info.st_mode;
		}
		//process_filename(fi->name);
		//printf("<<%s>>\n", fi->name);
		local_win.dirlist = g_list_prepend(local_win.dirlist, (gpointer) fi);
	}

	g_dir_close(dir);

	return 0;
}
#endif /* !__MACOSX__ */

int tilp_dirlist_local(void)
{
	return tilp_file_dirlist();
}

/* Sorting */

static gint sort_by_type(gconstpointer a, gconstpointer b)
{
	FileEntry* fi_a = (FileEntry *)a;
	FileEntry* fi_b = (FileEntry *)b;
	
	return ((fi_b->attrib & S_IFMT) == S_IFDIR);
}

void tilp_file_sort_by_type(void)
{
	GList *list = local_win.dirlist;
	list = g_list_sort(list, sort_by_type);
}

static gint sort_by_name(gconstpointer a, gconstpointer b)
{
	FileEntry* fi_p = (FileEntry *)a;
	FileEntry* fi_q = (FileEntry *)b;
	
	if ((((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) ||
		(((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR))) 
	{
		if (strcmp(fi_p->name, fi_q->name) > 0)
			return !0;
	}
	else 
	{
			if (((fi_q->attrib & S_IFMT) == S_IFDIR) && (strcmp(fi_p->name, fi_q->name) > 0)) 
				return !0;
	}

	return 0;
}

void tilp_sort_files_by_name(void)
{
	GList *list = local_win.dirlist;
	list = g_list_sort(list, sort_by_name);
}

static gint sort_by_date(gconstpointer a, gconstpointer b)
{
	FileEntry* fi_p = (FileEntry *)a;
	FileEntry* fi_q = (FileEntry *)b;

	if ((((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) ||
		(((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR)))
	{
		if (fi_p->date > fi_q->date)
			return !0;
	}
	else
	{
		if (((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->date > fi_q->date)) 
			return !0;
	}

	return 0;
}

void tilp_sort_files_by_date(void)
{
	GList *list = local_win.dirlist;
	list = g_list_sort(list, sort_by_date);
}

static gint sort_by_size(gconstpointer a, gconstpointer b)
{
	FileEntry* fi_p = (FileEntry *)a;
	FileEntry* fi_q = (FileEntry *)b;

	if ((((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) ||
		(((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR))) 
	{
		if (fi_p->size > fi_q->size)
			return !0;
	}
	else
	{
		if (((fi_q->attrib & S_IFMT) == S_IFDIR))
		{
			if (fi_p->size > fi_q->size)
				return !0;
		}
	}

	return 0;
}

void tilp_sort_files_by_size(void)
{
	GList *list = local_win.dirlist;
	list = g_list_sort(list, sort_by_size);
}

static gint sort_by_attrib(gconstpointer a, gconstpointer b)
{
	FileEntry* fi_p = (FileEntry *)a;
	FileEntry* fi_q = (FileEntry *)b;

	if ((((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) ||
		(((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR))) 
	{
		if (fi_p->attrib > fi_q->attrib)
			return !0;
	}
	else 
	{
		if (((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->attrib > fi_q->attrib)) 
			return !0;
	}

	return 0;
}

void tilp_sort_files_by_attrib(void)
{
	GList *list = local_win.dirlist;
	list = g_list_sort(list, sort_by_attrib);
}


