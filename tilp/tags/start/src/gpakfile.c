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

/* Explode a PAK file into several files */
int explode_pak_file(char *pak_name)
{
  FILE *pak;
  FILE *out;
  char buffer[MAXCHARS];
  char filename[MAXCHARS];
  gint nfiles;
  gint i, j;
  gint ret;
  gint skip=0;
  gchar *dirname;
  char calc_type[8];
  char l_varname[9];
  char f_varname[18];
  longword varsize;
  char vartype[8];
  int varlock;
  char translate[9];

  if((pak=fopen(pak_name, "rb")) == NULL)
    {
      fprintf(stderr, _("Unable to open this file: %s\n"), pak_name);
    }
  fscanf(pak, "%s\n", buffer);
  if(!strstr(buffer, "_PAK"))
    {
      msg_box(_("Error"), 
	      _("This is not a valid PAK file.\n\n"));
      return -1;
    }
  fscanf(pak, "%i\n", &nfiles);
  for(i=0; i<nfiles; i++)
    {
      fscanf(pak, "%s\n", calc_type);
      fscanf(pak, "%s\n", l_varname);
      fscanf(pak, "%s\n", f_varname);
      fscanf(pak, "%s\n", vartype);
      fscanf(pak, "%08X\n", &varsize);
      fgets(buffer, 4, pak);
      sscanf(buffer, "%02X\n", &varlock);
      strcpy(filename, l_varname);
      /* Some varnames should be translated */
      if(!strcmp(calc_type, "TI82"))
	strcpy(filename, ti_calc.translate_varname(l_varname, translate, 0));
      else if(!strcmp(calc_type, "TI83"))
	strcpy(filename, ti_calc.translate_varname(l_varname, translate, 0));
      strcat(filename, ".");
      strcat(filename, vartype);

      skip=0;
      if(options.confirm == CONFIRM_YES)
	{
	  if( access(filename, F_OK) == 0 ) 
	    {
	      sprintf(buffer, _("The file %s already exists.\n\n"), 
		      filename);
	      ret=user3_box(_("Warning"), buffer, 
			    _(" Overwrite "), _(" Rename "),
			    _(" Skip "));
	      switch(ret)
		{
		case BUTTON1:
		  skip=0;
		  break;
		case BUTTON2:
		  dirname=dlgbox_entry(_("Rename the file"), 
				       _("New name: "), filename);
		  if(dirname == NULL) return 1;
		  strcpy(filename, dirname);
		  g_free(dirname);
		  skip=0;
		  break;
		case BUTTON3:
		  skip=1;
		  break;
		}
	    }
	}
      if((out=fopen(filename, "wb")) == NULL)
	{
	  fprintf(stderr, _("Unable to open this file: %s\n"), filename);
	}  
      fprintf(out, "%s\n", calc_type);
      fprintf(out, "%s\n", l_varname);
      fprintf(out, "%s\n", f_varname);
      fprintf(out, "%s\n", vartype);
      fprintf(out, "%08X\n", varsize);
      fprintf(out, "%02X\n", varlock);
      for(j=0; j<varsize; j++)
	{
	  if(skip)
	    fgetc(pak);
	  else
	    fputc(fgetc(pak), out);
	}
      fgetc(pak);
      
      fclose(out);
    } 
  fclose(pak);
  
  return 0;
}
