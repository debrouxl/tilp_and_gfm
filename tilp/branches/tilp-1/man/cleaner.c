/*  manpage_cleaner - remove the repetition of characters
 *  Copyright (C) 2000  Romain Lievin
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
#include <strings.h>
#include <unistd.h>

#define MAXCHARS 256

int main(int argc, char **argv)
{
  char filename[MAXCHARS];
  char filename2[MAXCHARS];
  char filename3[MAXCHARS];
  FILE *in;
  FILE *tmp;
  FILE *out;
  char buffer[3];
  
  /* Retrieve the command line argument */
  if(argc < 2)
    {
      fprintf(stderr, "You must give a filename on the command line.\n");
      exit(1);
    }
  strcpy(filename, argv[1]);
  strcpy(filename2, filename);
  strcat(filename2, ".tmp");
  strcpy(filename3, filename);
  strcat(filename3, ".txt");
  
  fprintf(stdout, "Processing file <%s>:\n", filename);
  fprintf(stdout, "Pass 1... ");
  
  /* Open the file for reading */
  in = fopen(filename, "rb");
  if(in == NULL)
    {
      fprintf(stderr, "Unable to open this file: <%s>\n", filename);
      exit(1);
    }
  
  /* Open a temporary file fpr writing */
  out = fopen(filename2, "wb");
  if(out == NULL)
    {
      fprintf(stderr, "Unable to open this file: <%s>\n", filename2);
      exit(1);
    }
  
  /* Process the file for removing backspace sequences */
  while(!feof(in))
    {
      buffer[0] = fgetc(in);
      if(feof(in))
	{
	  fputc(buffer[0], out);
	  break;
	}
      buffer[1]= fgetc(in);
  
      if(buffer[0] == '\b')
	{
	  continue; // Skip the char and BS
	}
      if(buffer[1] == '\b')
	{
	  fputc(fgetc(in), out); // Skip the 2 previous chars
	  continue;
	}
      fputc(buffer[0], out);
      fputc(buffer[1], out);
    }
  fprintf(stdout, "Done.\n");
  
  /* Close the files */
  fclose(in);
  fclose(out);
  
  fprintf(stdout, "Pass 2... ");
  
  /* Open the temporary file and another file */
  in = fopen(filename2, "rb");
  if(in == NULL)
    {
      fprintf(stderr, "Unable to open this file: <%s>\n", filename);
      exit(1);
    }
  
  out = fopen(filename3, "wb");
  if(out == NULL)
    {
      fprintf(stderr, "Unable to open this file: <%s>\n", filename2);
      exit(1);
    }
  
  /* Copy the file */
  while(!feof(in))
    {
      if(feof(in)) break;
      fputc(fgetc(in), out);
    }
  
  /* Close files */
  fclose(in);
  fclose(out);
  unlink(filename2);
  fprintf(stdout, "Done.\n");
  
  return 0;
}
