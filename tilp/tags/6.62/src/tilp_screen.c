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
TilpScreen ti_screen = {
	0
};


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
  Save the current screen in the right format according to
  the current tilp options.
  Returns 0 if successful
*/
/*
int tilp_screen_save(char *filename)
{
	FILE *image;

	if ((image = fopen(filename, "wb")) == NULL) {
		DISPLAY(_("Unable to open this file: %s\n"), filename);
	}

	ti_screen.img.depth = 2;	// 2 colors
	ti_screen.img.encoding = IMG_BW_TYPE;	// B&W

	if (options.screen_blurry)
		blurry_bitmap(&(ti_screen.img));

	switch (options.screen_format) {
	case XPM:
		write_xpm_format(image, &(ti_screen.img));
		break;
	case PCX:
		write_pcx_format(image, &(ti_screen.img));
		break;
#ifndef __MACOSX__
	case JPG:
		write_jpg_format(image, &(ti_screen.img));
		break;
#endif
	case BMP:
		write_bmp_format(image, &(ti_screen.img));
		break;
	}
	fclose(image);

	return 0;
}
*/
