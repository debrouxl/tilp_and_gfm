/*  ti_link - link program for TI calculators
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

#ifndef __IMAGE_FORMAT__
#define __IMAGE_FORMAT__

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
//#include <glib.h>

#ifdef HAVE_TILP_TYPEDEFS_H
# include <tilp/typedefs.h>
#else
# include "typedefs.h"
#endif

/*******************/
/* Image structure */
/*******************/

/*
  The image structure contains several pointers, only of them is allocated
  at a given time.
  If the pointer has been freed, it contains NULL.
*/
struct Image_
{
  byte *rgbmap;    // a raw buffer (rrggbb for instance)
  byte *bitmap;    // the image (1 bit per pixel)
  byte *bytemap;   // the image (1 byte per pixel)
  char **pixmap;   // the image in XPM format
  byte *colormap;  // the colormap (up to 256 colors)
  int depth;       // the number of colors (B&W or 256 colors/greyscales)
  int width;       // width (# of columns) of image
  int height;      // height (# of rows) of image
  int inverted;    // invert or not the the pixel color
};
typedef struct Image_ Image;


/*****************************/
/* PCX file format functions */
/*****************************/

int write_pcx_format(FILE *file, Image *img);
int read_pcx_format (FILE *file, Image *img);


/*****************************/
/* JPG file format functions */
/*****************************/

int write_jpg_format(FILE *file, Image *img);
int read_jpg_format (FILE *file, Image *img);

int write_jpg_true_colors(FILE *file, Image *img);

/*****************************/
/* XPM file format functions */
/*****************************/

int write_xpm_format(FILE *file, Image *img);
int read_xpm_format (FILE *file, Image *img);


/*********************/
/* Utility functions */
/*********************/

int convert_pixmap_to_bytemap(Image *img);
int convert_bytemap_to_pixmap(Image *img);
int convert_bitmap_to_pixmap(Image *img);
int convert_bitmap_to_bytemap(Image *img);
int convert_bytemap_to_bitmap(Image *img);

int compute_colormap(Image *img);
int convert_bytemap_to_rgbmap(Image *img);
int convert_rgbmap_to_bytemap(Image *img);
int convert_rgbmap_to_bytemap(Image *img);

void delete_bitmap(Image *img);
void delete_bytemap(Image *img);
void delete_colormap(Image *img);
void delete_pixmap(Image *img);
void delete_rgbmap(Image *img);
void delete_image(Image *img);

void alloc_bitmap(Image *img);
void alloc_colormap(Image *img);
void alloc_bytemap(Image *img);
void alloc_rgbmap(Image *img);

void invert_bitmap(Image *img);
void invert_bytemap(Image *img);

#endif

