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

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#include "win32/unistd.h"
#endif

#include <libticables/typedefs.h>
#include <libticables/macros.h>
#include <libticables/verbose.h>

#include "img_fmt.h"


/***********/
/* Writing */
/***********/

/* Beware: the number of columns must be an EVEN number */
int write_pcx_2_colors(FILE *file, Image *img) //tested: OK (12/05)
{
  int i, j;
  unsigned char count;
  unsigned char data;
  unsigned char last_data;

  DISPLAY("write_pcx_2_colors\n");
  /* Write the PCX header (128 bytes) */
  fputc(0x0A, file);                      // Signature of image format
  fputc(0x00, file);                      // Version
  fputc(0x01, file);                      // RLE compression
  fputc(0x01, file);                      // 1 bit by pixel
  for(i=0; i<4; i++) fputc(0x00, file);   // Left top corner: (0,0)
  fputc(LSB((img->width)-1), file);       // Right bottom corner: (x,y)
  fputc(MSB((img->width)-1), file);
  fputc(LSB((img->height)-1), file);
  fputc(MSB((img->height)-1), file);
  fputc(LSB(300), file);                       // Horizontal resolution in dpi
  fputc(MSB(300), file);
  fputc(LSB(300), file);                       // Vertical resolution in dpi
  fputc(MSB(300), file);
  for(i=0; i<3; i++) fputc(0x00, file);   // Palette
  for(i=0; i<3; i++) fputc(0xFF, file);
  for(i=0; i<42; i++) fputc(0xFF, file);
  fputc(0x00, file);                      // Reserved
  fputc(0x01, file);                      // Number of layers
  fputc(LSB((img->width) >> 3), file);    // Number of bytes by rows
  fputc(MSB((img->width) >> 3), file);
  fputc(0x01, file);                      // Palette type: B&W
  fputc(0x00, file);
  for(i=0; i<58; i++) fputc(0x00, file);  // Reserved
  
  /* Compress and write data line by lines */
  for(j=0; j<(img->height); j++)
    {
      last_data = *((img->bitmap)+((img->width) >> 3)*j);
      if(img->inverted)
	last_data = ~last_data;
	
      count=0;
      for(i=0; i<((img->width) >> 3); i++)  // Data
        { 
	  data = *((img->bitmap)+((img->width) >> 3)*j+i);
	  if(img->inverted)
	    data = ~data;
	  if(data == last_data)
	    { // if data repeated, count
	      count++;
	      if(count == 63) // if max reached, write counter and data
		{
		  fputc(0xC0 | count, file);
		  fputc(last_data, file);
		  count=0;
		}
	    }
	  else
	    { // the first byte or data > 64, write it.
	      if((count) || (last_data & 0xC0))
		{
		  fputc(0xC0 | count, file);
		  fputc(last_data, file);
		  last_data=data;
		  count=1;
		}
	      else
		{
		  fputc(last_data, file);
		  last_data=data;
		}
	    }
        }
      // flush
      if((count) || (last_data & 0xC0))
	{
	  fputc(0xC0 | count, file);
	  fputc(last_data, file);
	  last_data=data;
	  count=1;
        }
      else
        {
	  fputc(last_data, file);
	  last_data=data;
        }
    }
  
  return 0;
}

int write_pcx_256_colors(FILE *file, Image *img) //tested: OK (12/05)
{
  int i, j;
  unsigned char count;
  unsigned char data;
  unsigned char last_data;

  DISPLAY("write_pcx_256_colors\n");
  /* Write the PCX header (128 bytes) */
  fputc(0x0A, file);                      // Signature of image format
  fputc(0x05, file);                      // Version: there is a palette
  fputc(0x01, file);                      // RLE compression
  fputc(0x08, file);                      // 8 bits by pixel
  for(i=0; i<4; i++) fputc(0x00, file);   // Left top corner: (0,0)
  fputc(LSB((img->width)-1), file);            // Right bottom corner: (x,y)
  fputc(MSB((img->width)-1), file);
  fputc(LSB((img->height)-1), file);
  fputc(MSB((img->height)-1), file);
  fputc(LSB(300), file);                  // Horizontal resolution in dpi
  fputc(MSB(300), file);
  fputc(LSB(300), file);                  // Vertical resolution in dpi
  fputc(MSB(300), file);
  for(i=0; i<48; i++) fputc(img->colormap[i], file); // Palette
  fputc(0x00, file);                      // Reserved
  fputc(0x01, file);                      // Number of layers (1 color plane)
  fputc(LSB((img->width)), file);         // Number of bytes by rows
  fputc(MSB((img->width)), file);
  fputc(0x01, file);                      // Palette type: color
  fputc(0x00, file);
  for(i=0; i<58; i++) fputc(0x00, file);  // Reserved
  
  /* Compress and write data line by lines */
  for(j=0; j<(img->height); j++)
    {
      last_data = *((img->bytemap)+(img->width)*j);
      count=0;
      for(i=0; i<(img->width); i++)  // Data
        { 
	  data=*((img->bytemap)+(img->width)*j+i);
	  if(data == last_data)
	    { // if data repeated, count
	      count++;
	      if(count == 63) // if max reached, write counter and data
		{
		  fputc(0xC0 | count, file);
		  fputc(last_data, file);
		  count=0;
		}
	    }
	  else
	    { // the first byte or data > 64, write it.
	      if((count) || (last_data & 0xC0))
		{
		  fputc(0xC0 | count, file);
		  fputc(last_data, file);
		  last_data=data;
		  count=1;
		}
	      else
		{
		  fputc(last_data, file);
		  last_data=data;
		}
	    }
        }
      // flush
      if((count) || (last_data & 0xC0))
	{
	  fputc(0xC0 | count, file);
	  fputc(last_data, file);
	  last_data=data;
	  count=1;
        }
      else
        {
	  fputc(last_data, file);
	  last_data=data;
        }
    }
  
  /* Write the palette (256 colors in rrggbb format) */
  fputc(12, file);	// palette ID
  for(i=0; i<3*256; i++)
    fputc(img->colormap[i], file);

  return 0;
}

int write_pcx_format(FILE *file, Image *img)
{
  DISPLAY("write_pcx_format\n");
  //DISPLAY("%i %i %i\n", img->width, img->height, img->depth);
  if(img->depth > 2)
    return write_pcx_256_colors(file, img);
  else
    return write_pcx_2_colors(file, img);
}


/***********/
/* Reading */
/***********/

int read_pcx_2_colors(FILE *file, Image *img) //tested: NOK! (12/05)
{
  int i, j;
  unsigned char count;
  unsigned char data = 0;
  //unsigned char last_data;
  int c;
  byte *p;

  DISPLAY("read_pcx_2_colors\n");
  /* Write the PCX header (128 bytes) */
  c = fgetc(file);                      // Signature of image format
  c = fgetc(file);                      // Version
  c = fgetc(file);                      // No compression
  c = fgetc(file);                      // 1 bit by pixel
  for(i=0; i<4; i++) {c=fgetc(file);}   // Left top corner: (0,0)
  (img->width)=1+BYTE2WORD(fgetc(file), 
			   fgetc(file));// Right bottom corner: (x,y)
  
  (img->height)=1+BYTE2WORD(fgetc(file),
			    fgetc(file));

  fgetc(file);                          // Horizontal resolution in dpi
  fgetc(file);
  fgetc(file);                          // Vertical resolution in dpi
  fgetc(file);
  for(i=0; i<3; i++) fgetc(file);       // Palette
  for(i=0; i<3; i++) fgetc(file);
  for(i=0; i<42; i++) fgetc(file);
  fgetc(file);                          // Reserved
  fgetc(file);                          // Number of layers
  (img->width)=BYTE2WORD(fgetc(file),
			 fgetc(file)) << 3; // Number of bytes by rows
  fgetc(file);                          // Palette type: B&W
  fgetc(file);
  for(i=0; i<58; i++) fgetc(file);      // Reserved

  DISPLAY("offset: %i\n", ftell(file));
  DISPLAY("Width: %i, Height: %i\n", img->width, img->height);
  DISPLAY("Number of bytes: %i\n", (img->width) * (img->height) >> 3);
  
  /* Initialize some variables */
  img->depth = 2;
  (img->bitmap) = (byte *)malloc((img->width) * (img->height) >> 3);
  if(img->bitmap == NULL)
    return -1;
  p = img->bitmap;

  /* Read and decompress data line by lines */
  for(j=0; j<(img->height) * (img->width) >> 3; )
    {
      if((data & 0xC0) == 0xC0)
	{ // compressed data
	  count = (data & 0x3F);
	  for(i=0; i<count; i++)
	    {
	      *p = data;
	      p++;
	    }
	}
      else
	{ // not compressed
	  count = 1;
	  if(img->inverted)
	    *p = ~data;
	  else
	    *p = data;
	  p++;
	}
      j += count;
    }
  DISPLAY("Number of bytes read: %i\n", j);
  DISPLAY("Reading PCX 2 colors: done.\n");

  return 0;
}


int read_pcx_256_colors(FILE *file, Image *img) // to do ...
{
  DISPLAY("read_pcx_256_colors\n");
  return 0;
}

int read_pcx_format(FILE *file, Image *img)
{
  DISPLAY("read_pcx_format\n");
  if(img->depth > 2)
    return read_pcx_256_colors(file, img);
  else
    return read_pcx_2_colors(file, img);
}

/*******************************/
/* Obsolete, for compatibility */
/*******************************/

/* Write the image stored in the '(img->bytemap)' variable  */
/* PCX format with 1 bit/pixel and with compression */
int write_pcx_compressed(FILE *file, Image *img)
{
  DISPLAY("write_pcx_compressed\n");
  if(img->depth > 2)
    return write_pcx_256_colors(file, img);
  else
    return write_pcx_2_colors(file, img);
}
