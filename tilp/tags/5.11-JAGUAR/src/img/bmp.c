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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#include "win32/unistd.h"
#endif

#ifdef __MACOSX__
#include <libticables/typedefs.h>
#include <libticables/macros.h>
#include <libticables/verbose.h>
#include <glib/glib.h>
#else
#include "tilibs.h"
#include <glib.h>
#endif

#include "fmt.h"
#include "bmpfile.h"


/***********/
/* Writing */
/***********/

int write_bmp_2_colors(FILE *file, Image *img) //tested: OK (09/04/2002)
{
  int           ImageHeight, ImageWidth;
  int           RowBytes, PixelDepth, BytesPerLine;
  int           *ColorTable, NbBytesColorTable, NbColors;
  int           NbBytesImage;
  unsigned char *BitsImage, *TrueBitsImage;
  int           Err;
  int           i;     
  unsigned char *PtrSource, *PtrTarget, *PtrDummy;
  
  BITMAPFILEHEADER    BmpFileHeader;  
  BITMAPINFOHEADER    BmpInfoHeader; 

  FILE *Stream = file;
  
  /* Invert bitmap */
  invert_bitmap(img);
  
  /* Image characteristics */
  PixelDepth = 1;
  ImageWidth = img->width;
  ImageHeight = img->height;
  
  /* Compute parameters */
  NbBytesImage = (ImageWidth * ImageHeight) / 8;
  RowBytes = ImageWidth / 8;
  NbColors = pow(2,PixelDepth);
  NbBytesColorTable = NbColors * sizeof(int);
  BytesPerLine = 4*((RowBytes+3)/4);	/* Z! Modulo 4 */
  
  /* Alloc mermory */
  BitsImage = img->bitmap;
  ColorTable = (int*)malloc(NbBytesColorTable);
  
  /* Fill */
  ColorTable[0] = 0x00ffffff;
  ColorTable[1] = 0x00000000;
  
  /* Initialize the fields in the BITMAPINFO structure */
  BmpInfoHeader.biSize              = sizeof(BITMAPINFOHEADER);
  BmpInfoHeader.biWidth             = ImageWidth;
  BmpInfoHeader.biHeight            = ImageHeight; /* I can't use negative number, why ????  */
  BmpInfoHeader.biPlanes            = 1;
  BmpInfoHeader.biBitCount          = PixelDepth;
  BmpInfoHeader.biCompression   = BI_RGB;
  BmpInfoHeader.biSizeImage         = BytesPerLine*ImageHeight; 
  BmpInfoHeader.biXPelsPerMeter = 0;
  BmpInfoHeader.biYPelsPerMeter = 0;
  BmpInfoHeader.biClrUsed = NbColors;
  BmpInfoHeader.biClrImportant = 0; /* All of the device colors are important.  */
  
  BmpFileHeader.bfType = 0x4d42;  /* Signature 0x42="B" 0x4d="M"   */
  BmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 
    NbBytesColorTable + BmpInfoHeader.biSizeImage;
  BmpFileHeader.bfReserved1 = 0;
  BmpFileHeader.bfReserved2 = 0;
  BmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + NbBytesColorTable;
  
  
  Err = fwrite ((void*)&BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, Stream); 
  Err = fwrite ((void*)&BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, Stream);
  Err = fwrite ((void*)ColorTable, sizeof(int), NbColors , Stream);
  
  /* Create (in memory) the image to be copied on file */
  /* Working that way allow us tro save the array with fwrite function */
  TrueBitsImage = (unsigned char*)calloc(BmpInfoHeader.biSizeImage+BytesPerLine,sizeof(unsigned char)); 
  
  /* We copy each scan line already filled with 0 */
  PtrSource = BitsImage;
  PtrTarget = TrueBitsImage;
  for (i=0; i<ImageHeight; i++){
    memcpy (PtrTarget, PtrSource, RowBytes);
    PtrTarget+=BytesPerLine;
    PtrSource+=RowBytes; 
  }
  
  /* I should not do the next few line but I'm not able to use negative value */
  /* for biHeight property so I need to upside down the array by hand ...     */
  /* This code should be remove as soon as I can understand what happen       */
  /* with biHeight                                                            */
  
  /* PtrSource points to the beginning of the last scan line                  */
  PtrSource = TrueBitsImage + ((ImageHeight-1)*BytesPerLine);
  /* PtrTarget points to the beginning of the first scan line                 */
  PtrTarget = TrueBitsImage;
  PtrDummy = (unsigned char*)malloc(BytesPerLine);   
  for (i=0; i<ImageHeight/2; i++){
    memcpy (PtrDummy, PtrTarget, BytesPerLine);
    memcpy (PtrTarget, PtrSource, BytesPerLine);
    memcpy (PtrSource, PtrDummy, BytesPerLine);  
    PtrTarget+=BytesPerLine;
    PtrSource-=BytesPerLine;
  }
  free(PtrDummy);
  
  /* Copy the array of color indices into the BMP file. */
  Err = fwrite ((void*)TrueBitsImage, sizeof(unsigned char), BmpInfoHeader.biSizeImage, Stream);  
  
  free(TrueBitsImage);
  free(ColorTable);   
  
  return 0;
}

/*
  Write a 256 colors bytemap
*/
int write_bmp_256_colors(FILE *file, Image *img) //tested: NOK (09/04/2002)
{
  int           ImageHeight, ImageWidth;
  int           RowBytes, PixelDepth, BytesPerLine;
  int           *ColorTable, NbBytesColorTable, NbColors;
  int           NbBytesImage;
  unsigned char *BitsImage, *TrueBitsImage;
  int           Err;
  int           i;     
  unsigned char *PtrSource, *PtrTarget, *PtrDummy;
  
  BITMAPFILEHEADER    BmpFileHeader;  
  BITMAPINFOHEADER    BmpInfoHeader; 

  FILE *Stream = file;
  
  /* Image characteristics */
  PixelDepth = 8;
  ImageWidth = img->width;
  ImageHeight = img->height;
  
  /* Compute parameters */
  NbBytesImage = (ImageWidth * ImageHeight);
  RowBytes = ImageWidth;
  NbColors = pow(2,PixelDepth);
  NbBytesColorTable = NbColors * sizeof(int);
  BytesPerLine = 4*((RowBytes+3)/4);	/* Z! Modulo 4 */
  
  /* Alloc mermory */
  BitsImage = img->bytemap;
  ColorTable = (int*)malloc(NbBytesColorTable);
  
  /* Fill color map */
	for(i=0; i<256; i++) {
    int r, g, b;
    unsigned char *cmp = img->colormap;
    
    r = cmp[3*i+0];
    g = cmp[3*i+1];
    b = cmp[3*i+2];
    
    ColorTable[i] = (r << 16) | (g << 8) | b;
  }

	//ColorTable[0] = 0x000000;
	//ColorTable[1] = 0xffffff;
  
  /* Initialize the fields in the BITMAPINFO structure */
  BmpInfoHeader.biSize              = sizeof(BITMAPINFOHEADER);
  BmpInfoHeader.biWidth             = ImageWidth;
  BmpInfoHeader.biHeight            = ImageHeight; /* I can't use negative number, why ????  */
  BmpInfoHeader.biPlanes            = 1;
  BmpInfoHeader.biBitCount          = PixelDepth;
  BmpInfoHeader.biCompression   = BI_RGB;
  BmpInfoHeader.biSizeImage         = BytesPerLine*ImageHeight; 
  BmpInfoHeader.biXPelsPerMeter = 0;
  BmpInfoHeader.biYPelsPerMeter = 0;
  BmpInfoHeader.biClrUsed = NbColors;
  BmpInfoHeader.biClrImportant = 0; /* All of the device colors are important.  */
  
  BmpFileHeader.bfType = 0x4d42;  /* Signature 0x42="B" 0x4d="M"   */
  BmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 
    NbBytesColorTable + BmpInfoHeader.biSizeImage;
  BmpFileHeader.bfReserved1 = 0;
  BmpFileHeader.bfReserved2 = 0;
  BmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + NbBytesColorTable;
  
  
  Err = fwrite ((void*)&BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, Stream); 
  Err = fwrite ((void*)&BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, Stream);
  Err = fwrite ((void*)ColorTable, sizeof(int), NbColors , Stream);
  
  /* Create (in memory) the image to be copied on file */
  /* Working that way allow us tro save the array with fwrite function */
  TrueBitsImage = (unsigned char*)calloc(BmpInfoHeader.biSizeImage+BytesPerLine,sizeof(unsigned char)); 
  
  
  /* We copy each scan line already filled with 0 */
  PtrSource = BitsImage;
  PtrTarget = TrueBitsImage;
  for (i=0; i<ImageHeight; i++){
    memcpy (PtrTarget, PtrSource, RowBytes);
    PtrTarget+=BytesPerLine;
    PtrSource+=RowBytes; 
  }
  
  /* I should not do the next few line but I'm not able to use negative value */
  /* for biHeight property so I need to upside down the array by hand ...     */
  /* This code should be remove as soon as I can understand what happen       */
  /* with biHeight                                                            */
  
    /* PtrSource points to the beginning of the last scan line                  */
  PtrSource = TrueBitsImage + ((ImageHeight-1)*BytesPerLine);
  /* PtrTarget points to the beginning of the first scan line                 */
  PtrTarget = TrueBitsImage;
  PtrDummy = (unsigned char*)malloc(BytesPerLine);   
  for (i=0; i<ImageHeight/2; i++){
    memcpy (PtrDummy, PtrTarget, BytesPerLine);
    memcpy (PtrTarget, PtrSource, BytesPerLine);
    memcpy (PtrSource, PtrDummy, BytesPerLine);  
    PtrTarget+=BytesPerLine;
    PtrSource-=BytesPerLine;
  }
  free(PtrDummy);
  
  /* Copy the array of color indices into the BMP file. */
  Err = fwrite ((void*)TrueBitsImage, sizeof(unsigned char), BmpInfoHeader.biSizeImage, Stream);  
  
  free(TrueBitsImage);
  free(ColorTable);
  
  return 0;
}

int write_bmp_format(FILE *file, Image *img)
{
  if(img->encoding == IMG_COL_TYPE)
    return write_bmp_256_colors(file, img);
  else
    return write_bmp_2_colors(file, img);
}


/***********/
/* Reading */
/***********/

int read_bmp_2_colors(FILE *file, Image *img) //tested: NOK! (12/05)
{
  return 0;
}


int read_bmp_256_colors(FILE *file, Image *img) // to do ...
{
  return 0;
}

int read_bmp_format(FILE *file, Image *img)
{
  if(img->encoding == IMG_COL_TYPE)
    return read_bmp_256_colors(file, img);
  else
    return read_bmp_2_colors(file, img);
}
