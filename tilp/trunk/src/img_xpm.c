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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img_fmt.h"


/***********/
/* Writing */
/***********/

int write_xpm_2_colors(FILE *file, Image *img) //tested: OK! (12/05)
{
  int i;

  //DISPLAY("write_xpm_2_colors\n");
  convert_bitmap_to_pixmap(img);
  
  fprintf(file, "/* XPM */\n");
  fprintf(file, "static char * screen_xpm[] = {\n");
  fprintf(file, "\"%s\"", (img->pixmap)[0]);
  for(i=1; (img->pixmap)[i] != NULL; i++)
    {
      fprintf(file, ",\n\"%s\"", (img->pixmap)[i]);
    }
  fprintf(file, "};");
  
  delete_pixmap(img);

  return 0;
}

int write_xpm_256_colors(FILE *file, Image *img) //tested: OK (12/05)
{
  int i;

  //DISPLAY("write_xpm_256_colors\n");
  convert_bytemap_to_pixmap(img);
  
  fprintf(file, "/* XPM */\n");
  fprintf(file, "static char * screen_xpm[] = {\n");
  fprintf(file, "\"%s\"", (img->pixmap)[0]);
  for(i=1; (img->pixmap)[i] != NULL; i++)
    {
      fprintf(file, ",\n\"%s\"", (img->pixmap)[i]);
    }
  fprintf(file, "};");

  delete_pixmap(img);

  return 0;
}

int write_xpm_format(FILE *file, Image *img)
{
  //DISPLAY("write_xpm_format\n");
  if(img->depth > 2)
    return write_xpm_256_colors(file, img);
  else
    return write_xpm_2_colors(file, img);

  return 0;
}


/***********/
/* Reading */
/***********/

int read_xpm_256_colors(FILE *file, Image *img);

int read_xpm_2_colors(FILE *file, Image *img) // tested: OK ! (12/05)
{
  //DISPLAY("read_xpm_2_colors\n");
  read_xpm_256_colors(file, img);
  convert_bytemap_to_bitmap(img);
  img->depth = 2;

  return 0;
}

int read_xpm_256_colors(FILE *file, Image *img) // not tested
{
  char buffer[MAXCHARS];
  int fg, bg;
  char *line;
  byte index;
  byte rr, gg, bb;
  int i, j, k;

  //DISPLAY("read_xpm_256_colors\n");
  fgets(buffer, MAXCHARS, file);
  if(!strstr(buffer, "/* XPM */")) // check header
    fprintf(stdout, "XPM: invalid header");
  fgets(buffer, MAXCHARS, file);
  fgets(buffer, MAXCHARS, file); // get image size
  //fprintf(stdout, "XPM info: <%s>\n", buffer);
  sscanf(buffer, "\"%i %i %i %i\",", &(img->width), &(img->height), 
	 &(img->depth), &bg);
  fg = img->depth - bg;
  if(img->depth > 256)
    {
      fprintf(stdout, "Too many colors (> 256).\n");
      return -1;
    }
  //fprintf(stdout, "rows: %i, cols: %i\n", img->width, img->height);

  // Allocate pointer
  img->bytemap = (byte *)malloc(img->width * img->height * sizeof(byte));
  if(img->bytemap == NULL)
    fprintf(stdout, "Malloc error.\n");
  line = (char *)malloc((img->width + 10) * sizeof(char));
  if(line == NULL)
    fprintf(stdout, "Malloc error.\n");

  // Load palette (rrggbb format)
  img->colormap = (byte *)malloc(3*256 * sizeof(byte));
  if(img->colormap == NULL)
    fprintf(stdout, "Malloc error.\n");
  for(i=0; i<img->depth; i++)
  {
    fgets(buffer, MAXCHARS, file); // example: "+      c #00FF00",
    //fprintf(stdout, "pal: <%s>\n", buffer);
    if(strstr(buffer, "None")) continue;
    index = buffer[1];
    if(index > 256)
      fprintf(stdout, "Image error\n");

    if(sscanf(buffer, "\"%c\tc #%02X%02X%02X\",", (byte *)&index, 
	      (int *)(&rr), (int *)(&gg), (int *)(&bb)) < 4)
      continue;
    //fprintf(stdout, "index: %i\n", index);
    (img->colormap)[3*index+0] = rr;
    (img->colormap)[3*index+1] = gg;
    (img->colormap)[3*index+2] = bb;
  }

  // Load image
  i = j = k = 0;
  do
  {
    fgets(line, img->width + 10, file); // example: <" .++.   .++.    ",>
    //fprintf(stdout, "j=%i, line: <%s>\n", j, line);

    for(i=1; i<img->width+1; i++)
      (img->bytemap)[img->height * j + i] = line[i];
    j++;

    if(feof(file)) break;
    //fprintf(stdout, "last char: <%c>\n", line[*cols+2]);
  }
  while(line[img->width + 2] != '}');

  return 0;
}

int read_xpm_format(FILE *file, Image *img)
{
  //DISPLAY("read_xpm_format\n");
  if(img->depth > 2)
    return read_xpm_256_colors(file, img);
  else
    return read_xpm_2_colors(file, img);
}


/**********************************/
/* Conversion & utility functions */ 
/**********************************/

//#define DEBUG

/* Convert the image stored in the 'bitmap' variable into a pixmap */
int convert_bitmap_to_pixmap(Image *img) //tested: OK (12/05)
{
  char buffer[256]; // primary buffer
  char *line;       // image buffer
  int col, row, bit;
  unsigned char mask, data;
  int pixel;
#ifdef DEBUG
  FILE *out;
#endif

  //DISPLAY("convert_bitmap_to_pixmap\n");
#ifdef DEBUG
  out=fopen("test.xpm", "wt");
  if(out == NULL) 
    fprintf(stdout, "Unable to open the file test.xpm\n");
#endif

  /* Header */
  (img->pixmap) = (char **)malloc((img->height + 5)*sizeof(char *));
  if(img->pixmap == NULL) fprintf(stdout, "Malloc error.\n");
  sprintf(buffer, "%i %i %i %i", img->width, img->height, 3, 1);
  (img->pixmap)[0]=(char *)malloc((strlen(buffer)+1)*sizeof(char));
  if((img->pixmap)[0] == NULL) fprintf(stdout, "Malloc error.\n");
  //fprintf(stdout, "pixmap[0] %p\n", (img->pixmap[0]));
  strcpy((img->pixmap)[0], buffer);
#ifdef DEBUG
  fprintf(out, "/* XPM */\n");
  fprintf(out, "static char *img_xpm[] = \n");
  fprintf(out, "\"%s\",\n", buffer);
#endif

  /* Colormap */
  sprintf(buffer, " \tc None");
  (img->pixmap)[1]=(char *)malloc((strlen(buffer)+1)*sizeof(char));
  if((img->pixmap)[1] == NULL) fprintf(stdout, "Malloc error.\n");
  strcpy((img->pixmap)[1], buffer);
#ifdef DEBUG
  fprintf(out, "\"%s\",\n", buffer);
#endif

  if(img->inverted)
    sprintf(buffer, ".\tc #FFFFFF");
  else
    sprintf(buffer, ".\tc #000000");
  (img->pixmap)[2]=(char *)malloc((strlen(buffer)+1)*sizeof(char));
  if((img->pixmap)[2] == NULL) fprintf(stdout, "Malloc error.\n");
  strcpy((img->pixmap)[2], buffer);
#ifdef DEBUG
  fprintf(out, "\"%s\",\n", buffer);
#endif

  if(img->inverted)
    sprintf(buffer, "+\tc #000000");
  else
    sprintf(buffer, "+\tc #FFFFFF");
  (img->pixmap)[3]=(char *)malloc((strlen(buffer)+1)*sizeof(char));
  if((img->pixmap)[3] == NULL) fprintf(stdout, "Malloc error.\n");
  strcpy((img->pixmap)[3], buffer);
#ifdef DEBUG
  fprintf(out, "\"%s\",\n", buffer);
#endif

  /* Image */
  line = (char *)malloc(((img->width) + 10) * sizeof(char));
  if(line == NULL)
    fprintf(stdout, "Malloc error.\n");

  for(row=0; row<img->height; row++)
    {
      for(col=0; col<(img->width)>>3; col++)
	{
	  data = (img->bitmap)[((img->width) >> 3) * row + col];
	  mask=0x80;
	  for(bit=0; bit<8; bit++)
	    {
	      pixel=data & mask;
	      if(pixel) line[8*col+bit]='+'; else line[8*col+bit]='.';
	      mask>>=1;
	    }
	}
      buffer[img->width]='\0';
      (img->pixmap)[row+4]=(char *)malloc((strlen(line)+1)*sizeof(char));
      if((img->pixmap)[row+4] == NULL) fprintf(stdout, "Malloc error.\n");
      strcpy((img->pixmap)[row+4], line);
#ifdef DEBUG
      fprintf(out, "\"%s\",\n", line);
#endif
    }
  (img->pixmap)[img->height+4]=NULL;
  free(line);

#ifdef DEBUG
  fclose(out);
#endif

  return 0;
}

/* Utility function */
char* byte_to_string(byte b)
{
  static char buffer[3];
  //static int c = 0;

  //fprintf(stdout, "byte: %02X %i ", b, c++);
  if(b < 64)
    {
      buffer[0] = b + '#';
      buffer[1] = '(';
    }
  else
    {
      buffer[0] = '#' + (b & 63);
      buffer[1] = '(' + (b >> 6);
    }
  buffer[2] = '\0';
  //fprintf(stdout, "string: %s\n", buffer);

  return buffer;
}

/* Convert the image stored in the 'bytemap' variable into a pixmap */
int convert_bytemap_to_pixmap(Image *img) // tested: OK (12/05)
{
  char buffer[2*256+1]; //primary buffer
  char *line;           //image buffer
  int col, row;
  //int bit;
  unsigned char data;
  //unsigned char mask;
  //int pixel;
  int i;
  //int j;
  char *s;
#ifdef DEBUG
  FILE *out;
#endif

  //DISPLAY("convert_bytemap_to_pixmap\n");
#ifdef DEBUG
  out=fopen("test.xpm", "wt");
  if(out==NULL)
    fprintf(stdout, "Unable to open the file 'test.xpm'.\n");
#endif

  /* Header */
  (img->pixmap) = (char **)malloc((img->height + 2 + img->depth + 1) *
				    sizeof(char *));
  if((img->pixmap) == NULL) fprintf(stdout, "Malloc error.\n");
  sprintf(buffer, "%i %i %i %i", img->width, img->height, 
	  img->depth + 1, 2);
  (img->pixmap)[0]=(char *)malloc((strlen(buffer)+1)*sizeof(char));
  if((img->pixmap)[0] == NULL) fprintf(stdout, "Malloc error.\n");
  //fprintf(stdout, "pixmap[0] %p\n", (img->pixmap[0]));
  strcpy((img->pixmap)[0], buffer);
#ifdef DEBUG
  fprintf(out, "/* XPM */\n");
  fprintf(out, "static char *img_xpm[] = \n");
  fprintf(out, "\"%s\",\n", buffer);
 #endif

  /* Colormap */
  sprintf(buffer, " \tc None");
  (img->pixmap)[1]=(char *)malloc((strlen(buffer)+1)*sizeof(char));
  if((img->pixmap)[1] == NULL) fprintf(stdout, "Malloc error.\n");
  strcpy((img->pixmap)[1], buffer);
#ifdef DEBUG
  fprintf(out, "\"%s\",\n", buffer);
#endif

  //fprintf(stdout, "depth: %i\n", img->depth);
  for(i=0; i<img->depth; i++)
    {
      //fprintf(stdout, "colormap: %i, %p\n", i, img->colormap);
      sprintf(buffer, "%s\tc #%02X%02X%02X", byte_to_string(i),
	      (img->colormap)[3*i+0],
	      (img->colormap)[3*i+1],
	      (img->colormap)[3*i+2]);
      (img->pixmap)[2+i] = (char *)malloc((strlen(buffer)+1) * 
					    sizeof(char));
      if((img->pixmap)[2+i] == NULL) fprintf(stdout, "Malloc error.\n");
      strcpy((img->pixmap)[2+i], buffer);
#ifdef DEBUG
  fprintf(out, "\"%s\",\n", buffer);
#endif
    }

  /* Image */
  line = (char *)malloc((2*(img->width) + 10) * sizeof(char));
  if(line == NULL)
    fprintf(stdout, "Malloc error.\n");

  for(row=0; row<img->height; row++)
    {
      for(col=0; col<img->width; col++)
	{
	  //fprintf(stdout, "row, col: %i, %i\n", row, col);
	  data = (img->bytemap)[(img->width) * row + col];
	  //fprintf(stdout, "%02X ", data);
	  s = byte_to_string(data);
	  line[2*col+0] = s[0];
	  line[2*col+1] = s[1];
	}
      line[2*(img->width)]='\0';
      (img->pixmap)[2 + img->depth + row]=
	(char *)malloc((strlen(line)+1) * sizeof(char));
      if((img->pixmap)[2+img->depth+row] == NULL) fprintf(stdout, "Malloc error.\n");
      strcpy((img->pixmap)[2 + img->depth + row], line);
#ifdef DEBUG
      fprintf(out, "\"%s\",\n", line);
#endif
    }
  (img->pixmap)[2 + img->depth + img->height] = NULL;
  free(line);

#ifdef DEBUG
  fprintf(out, "};");
  fclose(out);
#endif

  return 0;
}
