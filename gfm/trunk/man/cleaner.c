/*  manpage_cleaner - remove the repetition of characters
 *  Copyright (C) 2000 Romain Liévin
 *  Copyright (C) 2009 Kevin Kofler
 *  Copyright (C) 2009 Lionel Debroux
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *filename = NULL;
  char *filename2 = NULL;
  FILE *in;
  FILE *out;
  char buffer[3];
  size_t len;
  int retval = 0;

  /* Retrieve the command line argument */
  if(argc < 2)
    {
      fprintf(stderr, "You must give a filename on the command line.\n");
      retval = 1;
      goto end;
    }

  len = strlen(argv[1]);
  filename = malloc(len+1);
  filename2 = malloc(len+5);
  if(filename == NULL || filename2 == NULL)
    {
      fprintf(stderr, "Cannot allocate memory.\n");
      retval = 1;
      goto end;
    }
  strcpy(filename, argv[1]);
  strcpy(filename2, filename);
  strcat(filename2 + len, ".txt");

  fprintf(stdout, "Processing file <%s>:\n", filename);
  fprintf(stdout, "Pass 1... ");

  /* Open input file */
  in = fopen(filename, "rb");
  if(in == NULL)
    {
      fprintf(stderr, "Unable to open this file: <%s>\n", filename);
      retval = 1;
      goto end;
    }

  /* Open output file */
  out = fopen(filename2, "wb");
  if(out == NULL)
    {
      fclose(in);
      fprintf(stderr, "Unable to open this file: <%s>\n", filename2);
      retval = 1;
      goto end;
    }

  /* Process the file for removing backspace sequences */
  while(!feof(in))
    {
      buffer[0] = fgetc(in);
      if(feof(in)) break;
      buffer[1] = fgetc(in);
      if(feof(in))
        {
          fputc(buffer[0], out);
          break;
        }
  
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

end:
  free(filename2);
  free(filename);

  return retval;
}
