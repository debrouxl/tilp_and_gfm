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
#ifdef HAVE_LIBJPEG
# include <jpeglib.h>
#endif

#include "includes.h"


/***********/
/* Writing */
/***********/

int write_jpg_2_colors(FILE *file, Image *img) // tested: OK (14/05)
{
  #ifdef HAVE_LIBJPEG
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  unsigned char *c;

  DISPLAY("write_jpg_2_colors\n");
  convert_bitmap_to_bytemap(img);
  if(!(img->inverted)) invert_bytemap(img);
  // Initialize JPEG library
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, file);
  
  cinfo.image_width = img->width;
  cinfo.image_height = img->height;
  cinfo.input_components = 1; // # of color components per pixel
  cinfo.in_color_space = JCS_GRAYSCALE; // gray scales

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 100, TRUE); // quality = 100% (better)
  jpeg_start_compress(&cinfo, TRUE);
  
  //fprintf(stdout, "output_scanline: %i\n", cinfo.output_scanline);
  c = img->bytemap;
  while(cinfo.next_scanline < cinfo.image_height) // save jpeg image
    {
      jpeg_write_scanlines(&cinfo, &c, 1);
      c += (img->width);
    }

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
#endif
    
  return 0;
}

int write_jpg_256_colors(FILE *file, Image *img)
{
  DISPLAY("write_jpg_256_colors\n");

  convert_bytemap_to_rgbmap(img);
  write_jpg_true_colors(file, img);

  return 0;
}

int write_jpg_true_colors(FILE *file, Image *img)
{
#ifdef HAVE_LIBJPEG
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  unsigned char *c;

  DISPLAY("write_jpg_true_colors\n");
  // Initialize JPEG library
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, file);
  
  cinfo.image_width = img->width;
  cinfo.image_height = img->height;
  cinfo.input_components = 3; // # of color components per pixel
  cinfo.in_color_space = JCS_RGB; // rrggbb

  jpeg_set_defaults(&cinfo);
  //jpeg_set_quality(&cinfo, quality, TRUE); // base-line
  jpeg_start_compress(&cinfo, TRUE);
  
  //fprintf(stdout, "output_scanline: %i\n", cinfo.output_scanline);
  c = img->rgbmap;
  while(cinfo.next_scanline < cinfo.image_height) // save jpeg image
    {
      jpeg_write_scanlines(&cinfo, &c, 1);
      c += 3*(img->width);
    }

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
#endif
  return 0;
}

int write_jpg_format(FILE *file, Image *img)
{
  DISPLAY("write_jpg_format\n");
  if(img->depth > 2)
    {
      if(img->depth < 257)
	return write_jpg_256_colors(file, img);
      else
	return write_jpg_true_colors(file, img);
    }
  else
    return write_jpg_2_colors(file, img);
}


/***********/
/* Reading */
/***********/

int read_jpg_2_colors(FILE *file, Image *img)
{
  DISPLAY("read_jpg_2_colors\n");

  return 0;
}

int read_jpg_256_colors(FILE *file, Image *img) //tested: OK
{
#ifdef HAVE_LIBJPEG
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  unsigned char *c;
  //int x, y;
  int j; 

  DISPLAY("read_jpg_256_colors\n");
  // Initialize JPEG library
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  // Get image size
  fprintf(stdout, "JPEG image_width: %i\n", cinfo.image_width);
  fprintf(stdout, "JPEG image_height: %i\n", cinfo.image_height);
  img->width = cinfo.image_width;
  img->height = cinfo.image_height;

  // Initialize color mapping
  cinfo.quantize_colors = TRUE; // colormapped output wanted
  cinfo.desired_number_of_colors = 255; // decrease color depth

  // Read and decompress image
  jpeg_start_decompress(&cinfo);

  fprintf(stdout, "JPEG output_width: %i\n", cinfo.output_width);
  fprintf(stdout, "JPEG output_height: %i\n", cinfo.output_height);
  fprintf(stdout, "JPEG output_components: %i\n", cinfo.output_components);
  fprintf(stdout, "JPEG out_color_components: %i\n", cinfo.out_color_components);

  fprintf(stdout, "JPEG actual_number_of_colors: %i\n", cinfo.actual_number_of_colors);
  img->depth = cinfo.actual_number_of_colors;

  // Copy colormap into palette
  (img->colormap) = (byte *)malloc(3 * 256 * sizeof(byte));
  for(j=0; j<cinfo.actual_number_of_colors; j++) // copy the colormap
    {
      (img->colormap)[3*j+0] = cinfo.colormap[0][j];
      (img->colormap)[3*j+1] = cinfo.colormap[1][j];
      (img->colormap)[3*j+2] = cinfo.colormap[2][j];
    }

  if (cinfo.output_components != 1) // 1: palettized, 3: rrggbb
    return -1;

  // Allocate image
  img->bytemap = c = (byte *)malloc(img->width * img->height);
  if(c == NULL) g_error("Malloc error.\n");

  //fprintf(stdout, "output_scanline: %i\n", cinfo.output_scanline);
  while(cinfo.output_scanline < cinfo.output_height) // load jpeg image
    {
      c += img->width;
      jpeg_read_scanlines(&cinfo, &c, 1);
    }
  //fprintf(stdout, "jpeg_start, img->bytemap = %p\n", img->bytemap);
  //fprintf(stdout, "jpeg_end, img->bytemap = %p\n", c);

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);


#endif
  return 0;
}

int read_jpg_format (FILE *file, Image *img)
{
  DISPLAY("read_jpg_format\n");
  if(img->depth > 2)
    return read_jpg_256_colors(file, img);
  else
    return read_jpg_2_colors(file, img);
}
