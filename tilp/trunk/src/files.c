/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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
  sorting routines for selection.
  These functions are mainly used by the right window.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <sys/stat.h>
//#include <dirent.h>
#include <unistd.h>

#ifndef __MACOSX__
#include <glib.h>
#include "platform.h"
#else
#include <dirent.h>
#include <glib/glib.h>
#endif

#include "struct.h"
#include "defs.h"
#include "intl.h"
#include "gui_indep.h"
#include "error.h"
#include "vars.h"

/*******************************/
/* File manipulation functions */
/*******************************/

/*
  Copy a file from src to dst 
 */
int copy_file(char *src, char *dst)
{
#ifndef __WIN32__
  FILE *in, *out;
  int c;

   if((in=fopen(src, "rb")) == NULL)
    {
      return -1;
    }
   if((out=fopen(dst, "wb")) == NULL)
     {
      return -2;
    }
   while(!feof(in))
     {
	   c=fgetc(in);
	   if(feof(in)) break;
       fputc(c, out);
     }
   fclose(in);
   fclose(out);
#else
	if(!CopyFile(src, dst, FALSE))
		return -1;
#endif

  return 0;
}

/*
  Move the file
 */
int move_file(char *src, char *dst)
{
#ifndef __WIN32__
  int ret;

  ret=copy_file(src, dst);
  if(ret) return ret;
  unlink(src);
#else
	if(!MoveFile(src, dst))
		return -1;
#endif

  return 0;
}

int delete_file(char *f)
{
  if(unlink(f) == -1)
    {
#ifdef __WIN32__
      if(!RemoveDirectory(f))
#else
	/* [X91] temporarily drop root privileges */
#ifdef __LINUX__
	uid_t	effective;
      
      effective = geteuid();
      seteuid(getuid());
#endif
      if(remove(f) == -1)
#endif
	{
	  gif->msg_box(_("Information"),
		       _("Unable to remove the file. You can not delete non empty folders !"));
	  return -1;
	}
#ifdef __LINUX__
      seteuid(effective);
#endif
    }
  return 0;
}

/* Remove '\r' characters for GtkText */
void process_buffer(gchar *buf)
{
  gint i;
  
  for(i=0; i<strlen(buf); i++)
  {
    if(buf[i]=='\r') buf[i]=' ';
  }
}

/* Replace a '\r\n' or a '\n' by '\r' */
void process_unix2dos(gchar *buf)
{
	int i;
	int l = strlen(buf);

	for(i=0; i<l; i++)
	{/*
		if( (buf[i] == '\r') && (buf[i+1] == '\n') )
		{
			buf[i] = '\r';
			buf[i+1] = '\n';
		}
		if( (buf[i] == '\n') && (buf[i+1] == '\r') )
		{
			buf[i] = '\r';
			buf[i+1] = '\n';
		}
		if(buf[i] == '\r') buf[i] = '\n';
		*/
		if( (buf[i] == '\r') || (buf[i] == '\n') )
		{
			buf[i]='\r';
			buf[i+1]='\n';
			i++;
		}
	}
	buf[i]='\0';

}


/*************************************/
/* Extracting informations functions */
/*************************************/

/*
  Retrieve informations about attributes from a file info structure
  and returns a string
 */
char *get_attributes(TilpFileInfo f_info)
{
  char *s;

  s=g_strdup(" ---------- ");

  if(f_info.attrib & S_IRUSR) s[2]='r';
  if(f_info.attrib & S_IWUSR) s[3]='w';
  if(f_info.attrib & S_ISUID) 
    {
      if(f_info.attrib & S_IXUSR) s[4]='s';
      else s[4]='S';
    }
  else if(f_info.attrib & S_IXUSR) s[4]='x';
  
  if(f_info.attrib & S_IRGRP) s[5]='r';
  if(f_info.attrib & S_IWGRP) s[6]='w';
  if(f_info.attrib & S_ISGID) 
    {
      if(f_info.attrib & S_IXGRP) s[7]='s';
      else s[7]='S';
    }
  else if(f_info.attrib & S_IXGRP) s[7]='x';
  
  if(f_info.attrib & S_IROTH) s[8]='r';
  if(f_info.attrib & S_IWOTH) s[9]='w';
  if(f_info.attrib & S_ISVTX) 
    {
      if(f_info.attrib & S_IXOTH) s[10]='t';
      else s[10]='T';
    }
  else if(f_info.attrib & S_IXOTH) s[10]='x';
#ifndef __WIN32__
  if(S_ISLNK(f_info.attrib)) 
    {
      s[1]='l';
      return s;
    }
#endif

  switch(S_IFMT & f_info.attrib)  
    {
    case S_IFBLK:	s[1]='b';
      break;
    case S_IFDIR:	s[1]='d';
      break;
    case S_IFCHR:	s[1]='c';
      break;
    case S_IFIFO:	s[1]='p';
      break;
    case S_IFSOCK:	s[1]='s';
      break;
    }

  return s;
}

/*
  Returns the user's name
*/
void get_user_name(TilpFileInfo f_info, char **name)
{
#if defined(__LINUX__)
  struct passwd *pwuid;
  
  if((pwuid=getpwuid(f_info.user)) == NULL)
    {
      *name=NULL;
    }
  else
    {
      *name=g_strdup(pwuid->pw_name);
    }
#else
  *name = NULL;
#endif
}

/*
  Returns the group's name
 */
void get_group_name(TilpFileInfo f_info, char **name)
{
#if defined(__LINUX__)
  struct group *grpid;
  
  if((grpid=getgrgid(f_info.group)) == NULL)
    {
      *name=NULL;
    }
  else
    {
      *name=g_strdup(grpid->gr_name);
    }
    #else
          *name = NULL;
    #endif
}

/*
	Return the date of file
*/
void get_date(TilpFileInfo f_info, char **s)
{
  char *p;
  char buffer[32];
  int i;

  p=ctime(&(f_info.date));
  for(i=4; i<11; i++)
    {
      buffer[i-4]=*(p+i);
    }
  for(i=20; i<24; i++)
    {
      buffer[i-13]=*(p+i);
    }
  buffer[i-13]='\0';
  *s=g_strdup(buffer);
}

/*
  Returns the user's home directory
*/
int get_home_path(char **path)
{
#if defined(__LINUX__)
  uid_t uid;
  struct passwd *p;
  
  uid = getuid();
  //fprintf(stderr, "UID: %i\n", uid);
  
  if((p = getpwuid(uid)) == NULL)
    {
      *path=NULL;
      return 0;
    }
  else
    {
      *path = g_strdup(p->pw_dir);
      return 1;
    }
#endif
  return 0;
}


/****************************/
/* Directory list functions */
/****************************/

/* Used by the function below */
void free_file_info_struct(gpointer data)
{
  g_free(((TilpFileInfo *)data)->filename);
  g_free(data);
}

/* Make a directory listing of the current directory and place the result 
   in the clist_win.dirlist GList 
*/
void l_directory_list()
{
  DIR *dir;
  struct dirent *file;
  struct stat f_info;
  TilpFileInfo *fi;

  if(clist_win.dirlist!=NULL)
    {
      g_list_foreach(clist_win.dirlist, (GFunc) free_file_info_struct, NULL);
      g_list_free(clist_win.dirlist);
      clist_win.dirlist=NULL;
    }  
  
  if( (dir=opendir(clist_win.cur_dir)) == NULL) 
    {
      fprintf(stderr, _("Opendir error\n"));
    }
  while( (file=readdir(dir)) != NULL) 
    {
      if(strcmp(file->d_name, ".")==0) { continue; }
      if(strcmp(file->d_name, ".."))
	 {
	   if( ((file->d_name)[0]=='.') && (options.show == HIDE) ) { continue; }
	 }
      fi=(TilpFileInfo *)g_malloc(sizeof(TilpFileInfo));
      fi->filename=g_strdup(file->d_name);
      if(stat(file->d_name, &f_info)!=0)
	{
	  fi->date=0;
	  fi->size=0;
	  fi->user=0;
	  fi->group=0;
	  fi->attrib=0;
	}
      else
	{
	  fi->date=f_info.st_mtime;
	  fi->size=f_info.st_size;
	  fi->user=f_info.st_uid;
	  fi->group=f_info.st_gid;
	  fi->attrib=f_info.st_mode;
	}
      clist_win.dirlist=g_list_prepend(clist_win.dirlist, (gpointer)fi);
    }
  if(closedir(dir)==-1)
    {
      fprintf(stderr, _("Closedir error\n"));
    }
}

int c_directory_list(void)
{
  TicalcVarInfo varlist;
  int n;
  int ret = 0;

  gif->create_pbar_type2(_("Directory list"), 
			 _("Reading variables"));
  if(tilp_error(ti_calc.directorylist(&varlist, &n)))
    {
      varlist.next=NULL;
      n=0;
      ret = -1;
    }
  gif->destroy_pbar();

  varlist_to_glist(varlist);
  
  return ret;
}

/*********************/
/* Sorting functions */
/*********************/

/* 
   For these routines I have used the worst sorting method but the easiest: 
   the bubble sort algorithm !!! 
*/


void sort_lfiles_by_type(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (fi_q->attrib & S_IFMT) == S_IFDIR  )
	    {
	      end=j;
	      tmp=p->data;
	      p->data=q->data;
	      q->data=tmp;
	    }
	}
    }
}

void sort_lfiles_by_name(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  sort_lfiles_by_type(list);

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) || 
	      (((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR)) )
	    {
	      if(strcmp(fi_p->filename, fi_q->filename) > 0)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else
	    {
	      if( ((fi_q->attrib & S_IFMT) == S_IFDIR) && (strcmp(fi_p->filename, fi_q->filename) > 0) )
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	}
    }
}

/* Sort files by date (smallest to biggest size) */
void sort_lfiles_by_date(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) || 
	      (((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR)) )
	    {
	      if(fi_p->date > fi_q->date)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else
	    {
	      if( ((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->date > fi_q->date) )
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	}
    }
}

void sort_lfiles_by_size2(GList *list);

void sort_lfiles_by_size(GList *list)
{
  sort_lfiles_by_size2(list);
  //g_list_sort(list, GCompareComputerSizes);
}

void sort_lfiles_by_size2(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (((fi_p->attrib & S_IFMT) == S_IFDIR) && 
	       ((fi_q->attrib & S_IFMT) == S_IFDIR)) || 
	      (((fi_p->attrib & S_IFMT) != S_IFDIR) && 
	       ((fi_q->attrib & S_IFMT) != S_IFDIR)) )
	    {
	      if(fi_p->size > fi_q->size)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else if( ((fi_q->attrib & S_IFMT) == S_IFDIR))
	    {
	      if(fi_p->size > fi_q->size)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	}
    }
}

/* Sort files by user (smallest to biggest size) */
void sort_lfiles_by_user(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) || 
	      (((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR)) )
	    {
	      if(fi_p->user > fi_q->user)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else
	    {
	      if( ((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->user > fi_q->user) )
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	}
    }
}

/* Sort files by group (smallest to biggest size) */
void sort_lfiles_by_group(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) || 
	      (((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR)) )
	    {
	      if(fi_p->group > fi_q->group)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else
	    {
	      if( ((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->group > fi_q->group) )
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	}
    }
}

/* Sort files by attributes (smallest to biggest size) */
void sort_lfiles_by_attrib(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  TilpFileInfo *fi_p, *fi_q;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  if( (((fi_p->attrib & S_IFMT) == S_IFDIR) && ((fi_q->attrib & S_IFMT) == S_IFDIR)) || 
	      (((fi_p->attrib & S_IFMT) != S_IFDIR) && ((fi_q->attrib & S_IFMT) != S_IFDIR)) )
	    {
	      if(fi_p->attrib > fi_q->attrib)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else
	    {
	      if( ((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->attrib > fi_q->attrib) )
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	}
    }
}

/* Return the filename or its extension if it has one */
char *file_extension(char *filename)
{
  int i;
  char *p;
  
  for(i=strlen(filename); i > 0; i--)
    {
      if(filename[i] == '.') break;
    }
  p=filename+i+1;
  
  return p;
}
