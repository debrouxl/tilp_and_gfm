/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
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
  sorting routines for selection, conversion routines between dirlist
  and glists.
 */

/* FIXME OSX : this is not really needed, we use the finder... */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#ifdef __MACOSX__
#include <glib/glib.h>
#endif

#include "defs.h"
#include "struct.h"
#include "intl.h"
#include "gui_indep.h"
#include "error.h"
#include "select.h"

/*******************************/
/* File manipulation functions */
/*******************************/

/*
  Copy a file from src to dst 
 */
int copy_file(char *src, char *dst)
{
  FILE *in, *out;
  int c;

   if((in=fopen(src, "rb")) == NULL)
    {
      return 1;
    }
   if((out=fopen(dst, "wb")) == NULL)
     {
      return 2;
    }
   while(!feof(in))
     {
	   c=fgetc(in);
	   if(feof(in)) break;
       fputc(c, out);
     }
   fclose(in);
   fclose(out);

  return 0;
}

/*
  Move the file
 */
int move_file(char *src, char *dst)
{
  int ret;

  ret=copy_file(src, dst);
  if(ret) return ret;
  unlink(src);

  return 0;
}

/*************************************/
/* Extracting informations functions */
/*************************************/

/*
  Retrieve informations about attributes from a file info structure
  and returns a string
 */
char *get_attributes(struct file_info f_info)
{
  char *s;

  s=(char *)g_malloc((12+1)*sizeof(char));
  strcpy(s, " ---------- ");

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
  /*
#else
	if(f_info.attrib & _S_IREAD) s[5]='r';
	if(f_info.attrib & _S_IWRITE) s[6]='w';
	if(f_info.attrib & _S_IEXEC) s[7]='x';

	switch(_S_IFMT & f_info.attrib)  
    {
	case _S_IFDIR:	s[1]='d';
      break;
    case _S_IFCHR:	s[1]='c';
      break;
    case _S_IFIFO:	s[1]='p';
      break;
    }
#endif
	*/

  return s;
}

/*
  Returns the user's name
*/
void get_user_name(struct file_info f_info, char **name)
{
#if defined(__UNIX__)
  struct passwd *pwuid;
  
  if((pwuid=getpwuid(f_info.user)) == NULL)
    {
      *name=NULL;
    }
  else
    {
      *name=(char *)g_malloc((strlen(pwuid->pw_name)+1)*sizeof(char));
      strcpy(*name, pwuid->pw_name);
    }
#else
  *name = NULL;
#endif
}

/*
  Returns the group's name
 */
void get_group_name(struct file_info f_info, char **name)
{
#if defined(__UNIX__)
  struct group *grpid;
  
  if((grpid=getgrgid(f_info.group)) == NULL)
    {
      *name=NULL;
    }
  else
    {
      *name=(char *)g_malloc((strlen(grpid->gr_name)+1)*sizeof(char));
      strcpy(*name, grpid->gr_name);
    }
    #else
          *name = NULL;
    #endif
}

/*

 */
void get_date(struct file_info f_info, char **s)
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
  *s=(char *)g_malloc((strlen(buffer)+1)*sizeof(char));
  strcpy(*s, buffer);
}

/*
  Returns the user's home directory
*/
int get_home_path(char **path)
{
#if defined(__UNIX__)
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
      //fprintf(stderr, "User login name: %s\n", p->pw_name);
      //fprintf(stderr, "User's home directory: %s\n", p->pw_dir);
      *path = (char *)g_malloc((strlen(p->pw_dir)+1)*sizeof(char));
      strcpy(*path, p->pw_dir);
      return 1;
    }
#endif
  return 0;
}

/*********************/
/* Convert functions */
/*********************/

void display_dirlist(struct varinfo *varlist)
{
  int i;
  struct varinfo *ptr;

  ptr=varlist;
  while(ptr != NULL)
    {
      for(i=0; i<8; i++)
	{
	  if(isprint((ptr->varname)[i]))
	    fprintf(stdout, "%c", (ptr->varname)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, "|");
      for(i=0; i<8; i++)
	{
	  fprintf(stdout, "%02X", (byte)(ptr->varname)[i]);
	}
      fprintf(stdout, "¦");
      for(i=0; i<8; i++)
	{
	  if(isprint((ptr->translate)[i]))
	    fprintf(stdout, "%c", (ptr->translate)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, "|");
      fprintf(stdout, "%i  ", (int)(ptr->varlocked));
      fprintf(stdout, "|");
      fprintf(stdout, "%02X ", ptr->vartype);
      fprintf(stdout, "|");
      fprintf(stdout, "%08X ", ptr->varsize);
      fprintf(stdout, "|");
      fprintf(stdout, "%s", (ptr->folder)->varname);
      fprintf(stdout, "\n");

      ptr=ptr->next;
    }
}

//#define VDIR  /* For test/debug purpose */
/* 
   Convert the struct varinfo list supplied by calc_directorylist into a GList
*/ 
void varlist_to_glist(struct varinfo varlist)
{
  struct varinfo *p;
#ifdef VDIR
  int i;
  struct varinfo *ptr;
#endif

  /* Free the previous list */
  if(ctree_win.varlist != NULL)
    {
      g_list_foreach(ctree_win.varlist, (GFunc) g_free, NULL);
      g_list_free(ctree_win.varlist);
      ctree_win.varlist=NULL;
    }
  strcpy(ctree_win.cur_folder, varlist.varname);
#ifdef VDIR
  fprintf(stdout, _("Name    |Name bin        |Name tr |Lk|Ty|Size     |Parent\n"));
#endif
  
  p=&varlist;
  p=p->next;
  while(p != NULL)
    {
#ifdef VDIR
      ptr=p;
      for(i=0; i<8; i++)
	{
	  if(isprint((ptr->varname)[i]))
	    fprintf(stdout, "%c", (ptr->varname)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, " ");
      for(i=0; i<8; i++)
	{
	  fprintf(stdout, "%02X", (byte)(ptr->varname)[i]);
	}
      fprintf(stdout, " ");
      for(i=0; i<8; i++)
	{
	  if(isprint((ptr->translate)[i]))
	    fprintf(stdout, "%c", (ptr->translate)[i]);
	  else
	    fprintf(stdout, " ");
	}
      fprintf(stdout, " ");
      fprintf(stdout, "%i  ", (int)(ptr->varlocked));
      fprintf(stdout, "%02X ", ptr->vartype);
      fprintf(stdout, "%08X ", ptr->varsize);
      fprintf(stdout, "%s\n", (ptr->folder)->varname);
#endif      
      ctree_win.varlist = g_list_append(ctree_win.varlist, (gpointer)p);

      p=p->next;
    }
}

/* 
   Convert a GList (a directory list or a selection) into a struct 
   varinfo list such as the same supplied by calc_directorylist but 
   without the first element.
   Remove also the last folder if it is empty (else group will send 'bit time out').
*/ 
struct varinfo *glist_to_varlist(GList *glist)
{
  GList *ptr;
  struct varinfo *v;
  struct varinfo *p;
  struct varinfo varlist;
  
  ptr=glist;
  p=&varlist;
  p->next = NULL;
  if(ptr == NULL) return NULL;
  while(ptr != NULL)
    {
      /* Get element */
      v=(struct varinfo *)ptr->data;
      printf("Varname: %s, vartype: %s\n", v->varname, ti_calc.byte2type(v->vartype));
      printf("Parent folder: %s\n", (v->folder)->varname);

      /* If the LAST element is just a folder, skip it */
      if( (v->is_folder == FOLDER) && (ptr->next == NULL) )
		break;

      /* Allocate a new structure */
      (p->next) = (struct varinfo *)g_malloc(sizeof(struct varinfo));
      p=p->next;
      p->next = NULL;

      /* Copy the structure */
      strcpy(p->varname, v->varname);
      p->vartype=v->vartype;
      p->varlocked=v->varlocked;
      p->varsize=v->varsize;
      strcpy(p->translate, v->translate);
      p->folder=v->folder;

      ptr=ptr->next;
    }

  return varlist.next;
}

void free_varlist(struct varinfo *vlist)
{
  struct varinfo *p, *q;

  p=vlist;
  do
    {
      q=p->next;
	  //printf("free: varname=%s\n", p->varname);
      g_free(p); // a bug ?!
      p=q;
    }
  while(p != NULL);
}

/* 
   This function will become obsolete: replaced by 
   generate..._header_from_varlist 
*/
void generate_group_file_header(FILE *file, int mask_mode, 
				const char *id, struct varinfo *v, 
				int calc_type)
{
  struct varinfo *vi;

  vi = glist_to_varlist(ctree_win.selection);
  //display_dirlist(vi);
  //fprintf(stderr, "<%p>\n", file);
  ti_calc.generate_group_file_header(file, mask_mode, id, vi, 
				     options.lp.calc_type);
  free_varlist(vi);

  /* Code below no longer used */
  /*  
  longword index=0x52;
  int i;
  char desc[43] = _("Group received by tilp");
  char variable_name[9];
  char folder_name[9];
  char previous_folder[9];
  int j=0;
  GList *ptr;
  long file_offset=0;
  word num_vars=0;
  
  fprintf(file, id);
  fprintf(file, "%c%c", 0x01, 0x00);
  for(i=0; i<8; i++) fprintf(file, "%c", '\0');
  for(i=0; i<40; i++) fprintf(file, "%c", desc[i]);  
 
  
  strcpy(previous_folder, "");
  j=0;
  index=0x52;
  ptr=ctree_win.selection;
  while(ptr!=NULL)
    {
      v=(struct varinfo *)ptr->data;
      strcpy(folder_name, (v->folder)->varname);
      strcpy(variable_name, v->varname);
      if(strcmp(previous_folder, folder_name)) j++;
      j++;
      
      strcpy(previous_folder, (v->folder)->varname);
      ptr=ptr->next;
    }
  fprintf(file, "%c%c", LSW(j), MSW(j));
  j--;
  
  strcpy(previous_folder, "");
  index+=j*16;
  ptr=ctree_win.selection; 
  while(ptr!=NULL)
    {
      v=(struct varinfo *)ptr->data;
      strcpy(folder_name, (v->folder)->varname);
      strcpy(variable_name, v->varname);
      if(strcmp(previous_folder, folder_name))
	{
	
	  fprintf(file, "%c%c%c%c", (index & 0xFF),(index & 0x0000FF00)>>8, 
		  (index & 0x00FF0000)>>16, (index & 0xFF000000)>>24);
	  for(i=0; i<strlen(folder_name); i++) fprintf(file, "%c", folder_name[i]);
	  for(i=strlen(folder_name); i<8; i++) fprintf(file, "%c", '\0');
	  fprintf(file, "%c%c", tixx_dir(options.lp.calc_type), 0x00);
	  if(file_offset != 0)
	    {
	      fseek(file, file_offset, SEEK_SET);
	      fprintf(file, "%c%c", LSW(num_vars), MSW(num_vars));
	      fseek(file, 0L, SEEK_END);
	      num_vars=0;
	    }
	  file_offset=ftell(file);
	  fprintf(file, "%c%c", 0x00, 0x00);
	}
      
      fprintf(file, "%c%c%c%c", (index & 0xFF),(index & 0x0000FF00)>>8, 
	      (index & 0x00FF0000)>>16, (index & 0xFF000000)>>24);
      index+=v->varsize+6;
      for(i=0; i<strlen(variable_name); i++) fprintf(file, "%c", variable_name[i]);
      for(i=strlen(variable_name); i<8; i++) fprintf(file, "%c", '\0');
      fprintf(file, "%c", v->vartype);
      if(mask_mode &  MODE_KEEP_ARCH_ATTRIB)
	fprintf(file, "%c", v->varlocked); // extended group file
      else
	fprintf(file, "%c", 0x00); // standard group file
      fprintf(file, "%c%c", 0x00, 0x00);
      num_vars++;

      strcpy(previous_folder, folder_name);
      ptr=ptr->next;
    }
  fseek(file, file_offset, SEEK_SET);
  fprintf(file, "%c%c", LSW(num_vars), MSW(num_vars));
  fseek(file, 0L, SEEK_END);
  
  fprintf(file, "%c%c%c%c", (index & 0xFF),(index & 0x0000FF00)>>8, 
	  (index & 0x00FF0000)>>16, (index & 0xFF000000)>>24);
  fprintf(file, "%c%c", 0xA5, 0x5A);
*/
  return;

}

/****************************/
/* Directory list functions */
/****************************/

/* Used by the function below */
void free_file_info_struct(gpointer data)
{
  g_free(((struct file_info *)data)->filename);
  g_free(data);
}

/* Make a directory listing of the current directory and place the result in the clist_win.dirlist GList */
void l_directory_list()
{
  DIR *dir;
  struct dirent *file;
  struct stat f_info;
  struct file_info *fi;

  if(clist_win.dirlist!=NULL)
    {
      g_list_foreach(clist_win.dirlist, (GFunc) free_file_info_struct, NULL);
      g_list_free(clist_win.dirlist);
      clist_win.dirlist=NULL;
    }  
  clist_selection_destroy();
  
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
      //if(strcmp(file->d_name, ".")==0 || strcmp(file->d_name, "..")==0) { continue; }
      fi=(struct file_info *)g_malloc(sizeof(struct file_info));
      fi->filename=(char *)g_malloc((strlen(file->d_name)+1)*sizeof(char));
      strcpy(fi->filename, file->d_name);
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

// MODIFIED OS X
int c_directory_list(void)
{
  struct varinfo varlist;
  int n;
  int ret = 0;

  ctree_selection_destroy();

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

/* For these routines I have used the worst sorting method but the easiest: the bubble sort algorithm !!! */
/* Sort files by directory/files */
void sort_lfiles_by_type(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  struct file_info *fi_p, *fi_q;

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
  struct file_info *fi_p, *fi_q;

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
  struct file_info *fi_p, *fi_q;

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

/* Sort files by size (smallest to biggest size) */
void sort_lfiles_by_size(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  struct file_info *fi_p, *fi_q;

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
	      if(fi_p->size > fi_q->size)
		{
		  end=j;
		  tmp=p->data;
		  p->data=q->data;
		  q->data=tmp;
		}
	    }
	  else
	    {
	      if( ((fi_q->attrib & S_IFMT) == S_IFDIR) && (fi_p->size > fi_q->size) )
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
  struct file_info *fi_p, *fi_q;

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
  struct file_info *fi_p, *fi_q;

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
  struct file_info *fi_p, *fi_q;

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

void sort_cfiles_by_name(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  struct varinfo *fi_p, *fi_q;

  if (list == NULL)
    return;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  /*
	    if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate) && 
	    fi_p->vartype != ti_calc.tixx_dir(options.lp.calc_type) && fi_q->vartype != ti_calc.tixx_dir(options.lp.calc_type))
	  */
	  if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate) && 
	      (fi_p->is_folder != FOLDER) && (fi_q->is_folder != FOLDER) )
	    {
	      if(strcmp(fi_p->translate, fi_q->translate))
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

void sort_cfiles_by_info(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  struct varinfo *fi_p, *fi_q;

  if (list == NULL)
    return;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  /*
	    if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate) && 
	    fi_p->vartype != ti_calc.tixx_dir(options.lp.calc_type) && fi_q->vartype != ti_calc.tixx_dir(options.lp.calc_type))
	  */
	  if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate) 
	      && (fi_p->is_folder != FOLDER) && (fi_q->is_folder != FOLDER) )
	    {
	      if(fi_p->varlocked < fi_q->varlocked)
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

void sort_cfiles_by_type(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  struct varinfo *fi_p, *fi_q;

  if (list == NULL)
    return;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  /*
	    if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate) && 
	    fi_p->vartype != ti_calc.tixx_dir(options.lp.calc_type) && fi_q->vartype != ti_calc.tixx_dir(options.lp.calc_type))
	  */
	  if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate)
	      && (fi_p->is_folder != FOLDER) && (fi_q->is_folder) )
	    {
	      if(fi_p->vartype < fi_q->vartype)
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

void sort_cfiles_by_size(GList *list)
{
  GList *p, *q;
  int i, j, end, max;
  gpointer tmp;
  struct varinfo *fi_p, *fi_q;

  if (list == NULL)
    return;

  max=g_list_length(list);
  for (i=max-1; i>0; i=end)
    {
      end=0;
      for(j=0, p=list; j<i; j++, p=p->next)
	{
	  q=p->next;
	  fi_p=p->data;
	  fi_q=q->data;
	  /*
	    if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate) && 
	    fi_p->vartype != ti_calc.tixx_dir(options.lp.calc_type) && fi_q->vartype != ti_calc.tixx_dir(options.lp.calc_type))
	  */
	  if( !strcmp((fi_p->folder)->translate, (fi_q->folder)->translate)
	      && (fi_p->is_folder != FOLDER) && (fi_q->is_folder != FOLDER) )
	    {
	      if(fi_p->varsize < fi_q->varsize)
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
