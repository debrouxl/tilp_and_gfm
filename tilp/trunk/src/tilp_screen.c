/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
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

#include "tilp_core.h"
TilpScreen ti_screen = { 0 };


/*
  Do a screen capture
*/
int tilp_screen_capture(void)
{
	int err;
	TicalcScreenCoord sc;

	/* Place a progress bar */
	gif->create_pbar_type1(_("Screendump"));

	/* 
	   Get a screen capture
	 */
	err =
	    ti_calc.screendump(&(ti_screen.bitmap),
			       options.screen_clipping, &sc);
	if (options.screen_clipping == FULL_SCREEN) {
		ti_screen.width = sc.width;
		ti_screen.height = sc.height;
	} else {
		ti_screen.width = sc.clipped_width;
		ti_screen.height = sc.clipped_height;
	}
	gif->destroy_pbar();
	if (tilp_error(err))
		return -1;
	return 0;
}


/*
  Convert the bitmap into a B&W bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t *tilp_screen_convert(void)
{
	guchar *bitmap, *bytemap, data, mask;
	gint w;
	gint h;
	int row, col, bit, pixel, pos;

	bitmap = ti_screen.bitmap;
	w = ti_screen.width;
	h = ti_screen.height;

	bytemap = g_malloc(3 * w * h);

	for (row = 0; row < h; row++) {
		for (col = 0; col < (w >> 3); col++) {
			data = bitmap[(w >> 3) * row + col];
			mask = 0x80;

			for (bit = 0; bit < 8; bit++) {
				pixel = data & mask;
				pos = row * w + 8 * col + bit;
				if (pixel) {
					bytemap[3 * pos + 0] = 0;
					bytemap[3 * pos + 1] = 0;
					bytemap[3 * pos + 2] = 0;
				} else {
					bytemap[3 * pos + 0] = 255;
					bytemap[3 * pos + 1] = 255;
					bytemap[3 * pos + 2] = 255;
				}
				mask >>= 1;
			}
		}
	}

	return bytemap;
}

/*
  Convert the bitmap into a 2-colors bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t *tilp_screen_blurry(void)
{
	guchar *bitmap, *bytemap, data, mask;
	gint w;
	gint h;
	int row, col, bit, pixel, pos;

	bitmap = ti_screen.bitmap;
	w = ti_screen.width;
	h = ti_screen.height;

	bytemap = g_malloc(3 * w * h);

	for (row = 0; row < h; row++) {
		for (col = 0; col < (w >> 3); col++) {
			data = bitmap[(w >> 3) * row + col];
			mask = 0x80;

			for (bit = 0; bit < 8; bit++) {
				pixel = data & mask;
				pos = row * w + 8 * col + bit;
				if (pixel) {
					bytemap[3 * pos + 0] = 0x00;
					bytemap[3 * pos + 1] = 0x00;
					bytemap[3 * pos + 2] = 0x34;
				} else {
					bytemap[3 * pos + 0] = 0xa8;
					bytemap[3 * pos + 1] = 0xb4;
					bytemap[3 * pos + 2] = 0xa8;
				}
				mask >>= 1;
			}
		}
	}

	return bytemap;
}
