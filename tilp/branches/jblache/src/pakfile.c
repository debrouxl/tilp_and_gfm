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

#include <stdio.h>
#include <string.h>

#include "includes.h"

/* Check whether filename is a PAK file */
int is_pak_file(char *pak_name)
{
  FILE *pak;
  gchar buffer[MAXCHARS];

  if((pak=fopen(pak_name, "rb")) == NULL)
    {
      fprintf(stderr, gettext("Unable to open this file: %s\n"), pak_name);
    }
  fscanf(pak, "%s\n", buffer);
  if(!strstr(buffer, "_PAK"))
    {
      return 0;
    }
  //fscanf(pak, "%i\n", &nfiles);
  return 1;
}

/* Return the number of variables contained in the PAK file or 0 if the file is not a PAK file */
int number_of_files(char *pak_name)
{
  FILE *pak;
  gchar buffer[MAXCHARS];
  gint nfiles;
  
  if((pak=fopen(pak_name, "rb")) == NULL)
    {
      fprintf(stderr, gettext("Unable to open this file: %s\n"), pak_name);
    }
  fscanf(pak, "%s\n", buffer);
  if(!strstr(buffer, "_PAK"))
    {
      return 0;
    }
  fscanf(pak, "%i\n", &nfiles);
  fclose(pak);  

  return nfiles;
}

/* Return the varname of the variable contained in the file */
gchar *varname_in_file(FILE *f, gchar *varname)
{
  long offset;
  gchar buffer[MAXCHARS];

  offset=ftell(f);
  fscanf(f, "%s\n", buffer);
  fscanf(f, "%s\n", buffer);
  fscanf(f, "%s\n", buffer);
  strcpy(varname, buffer);
  fseek(f, offset, SEEK_SET);

  return varname;
}

/* Test whether the (full) varname is in the ctree list */
gint is_varname_in_ctree(char *varname)
{
  GList *p;
  struct varinfo *q;
  gchar buffer[MAXCHARS];

  if(ctree_win.varlist == NULL) return -1;
  p=ctree_win.varlist;
  while(p!=NULL)
    {
      q=(struct varinfo *)(p->data);
      if(options.path_mode == FULL_PATH)
	{
	  strcpy(buffer, (q->folder)->varname);
	  strcat(buffer, "\\");
	  strcat(buffer, q->varname);
	}
      else
	{
	  strcpy(buffer, q->varname);
	}
      if(!strcmp(buffer, varname))
	//if( (q->vartype) != ti_calc.tixx_dir(options.lp.calc_type))
	if(q->is_folder != FOLDER)
	  break;

      p=p->next;
    }
   if(!strcmp(buffer, varname)) return 1;

  return 0;
}

/* Rename the variable according to the path mode (full or local)
   Beware: the old file is not closed
*/
void rename_variable(FILE *old, gchar *new_filename, gchar *varname)
{
  gchar buffer[256];
  FILE *new;
  gint i;
  longword nbytes;
  
  if((new=fopen(new_filename, "wb")) == NULL)
    {
      fprintf(stderr, gettext("Unable to open this file: %s.\n"), 
	      new_filename);
     }

  fscanf(old, "%s\n", buffer);
  fprintf(new, "%s\n", buffer);
  switch(options.path_mode)
    {
    case FULL_PATH:
      fscanf(old, "%s\n", buffer);
      fprintf(new, "%s\n", buffer);
      fscanf(old, "%s\n", buffer);
      fprintf(new, "%s\n", varname);
      break;
    case LOCAL_PATH:
      fscanf(old, "%s\n", buffer);
      fprintf(new, "%s\n", varname);
      fscanf(old, "%s\n", buffer);
      fprintf(new, "%s\n", buffer);
    default:
      break;
    }
  fscanf(old, "%s\n", buffer);
  fprintf(new, "%s\n", buffer);
  fscanf(old, "%08X\n", &nbytes);
  fprintf(new, "%08X\n", nbytes);
  fscanf(old, "%s\n", buffer);
  fprintf(new, "%s\n", buffer);
  for(i=0; i<nbytes; i++)
    {
      fputc(fgetc(old), new);
    }
  fclose(new);
}

/*
struct file_char
{
  char *filename;	// Name of the file
  char *name;		// Name of the file without extension
  char *extension;	// and its extension
  gint file_type;	// Type: tilp or TIGL
  gint calc_type;	// Type: calculator (82, 83, ...)
  gint nvars;		// Numbers of variables if group or PAK file
  // These fields are defined only if not a PAK or group file
  char local_varname[9];	// Name of the var (local path)
  char full_varname[18];	// Name of the var (full path)
  char parent_folder[9];	// Parent folder of the var
  char vartype[9];			// Type of the var
  byte varlocked;			// Var is locked/archived ?
  longword varsize;			// Size of the var
};
*/

#undef AZERTY // Not finished
#ifdef AZERTY
/* This function get some informations about the file: see the file_char struct */
/* Return a value different of zero if it is not a valid file */
int get_file_informations(char *filename, struct file_char *sfc)
{
  FILE *f;
  int i;
  char buffer[MAXCHARS];
  const int next=6;
  const char *valid_extension[]={ "82", "83", "85", "86", "89", "92" };
  const char calc_type[]={ CALC_TI82, CALC_TI83, CALC_TI85, CALC_TI86, CALC_TI89, CALC_TI92 };

  strcpy(sfc->filename, filename);
  //printf("filename: <%s>\n", sfc->filename);
  /* Open the file */
  f=fopen(filename, "rb");
  if(f == NULL) return 1;

  /* Retrieve the filename extension */
  for(i=strlen(filename); filename[i] != '.'; i--) {}
  strcpy(sfc->extension, filename+i+1);
  strncpy(sfc->name, filename, i);
  (sfc->name)[i]='\0';
  //printf("name: <%s>\n", sfc->name);
  //printf("extension: <%s>\n", sfc->extension);
  for(i=0; i<6; i++)
  {
	if(!strstr(sfc->extension, valid_extension[i])) break;
  }
  if(i<6)
  {
	printf("valid_extension: <%s>\n", valid_extension[i]);
	sfc->calc_type=TIGL_FILES;
	sfc->calc_type=calc_type[i];
	f=fopen(filename, "rb");
	if(f == NULL) return 1;
	switch(sfc->extension[2])
	{
		/* Backup file */
	case 'b':
		break;
		/* Group file */
	case 'g':
		break;
		/* Normal file */
	default:
		switch(sfc->calc_type)
		{
		case CALC_TI82:
			for(i=0; i<57; i++) fgetc(f);
			sfc->varsize=fgetc(f);
			sfc->varsize+=fgetc(f) << 8;
			sfc->vartype=ti82_byte2type(fgetc(f));
		break;
		}
		break;
	}
  }
  else
  {
	sfc->file_type=GTK_FILES;
  }
}
#endif
