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

#include "struct.h"
#include "main.h"
#include "gui_indep.h"
#include "intl.h"
#include "error.h"
#include "defs.h"
#include "cb_calc.h"

struct screenshot ti_screen = { { NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0 }, 
				{ 0, 0, 0, 0 } };

/*
  Do a screen capture
*/
int cb_screen_capture(void)
{
  int err;

  if(is_active) 
    return -1;

  err = cb_calc_is_ready();
  if(err) return err;
  
  /* Place a progress bar */
  gif->create_pbar_type1(_("Screendump"));
  info_update.refresh();

  /* Get a screen capture */
  // We do not destroy the bitmap also because memory screen has been 
  // allocated by the libticables.
  // If we attempt to free it here, we will provoke a memory violation 
  //under Windows.
  delete_image(&(ti_screen.img));
  err = ti_calc.screendump(&(ti_screen.img.bitmap), 
			   options.screen_clipping, 
			   &(ti_screen.sc));
  ti_screen.img.depth = 2;
  if(options.screen_clipping == FULL_SCREEN)
    {
      ti_screen.img.width = ti_screen.sc.width;
      ti_screen.img.height = ti_screen.sc.height;
    }
  else
    {
      ti_screen.img.width = ti_screen.sc.clipped_width;
      ti_screen.img.height = ti_screen.sc.clipped_height;
    }

  gif->destroy_pbar();
  if(tilp_error(err)) 
    {
      return 1;
    }
  
  return 0;
}

/*
  Save the current screen capture the right format according to
  the current tilp options.
  Returns 0 if successful
*/
int cb_screen_save(char *filename)
{
  FILE *image;

  if((image=fopen(filename, "wt")) == NULL)
    {
      fprintf(stderr, _("Unable to open this file: %s\n"), filename);
    }

  ti_screen.img.depth = 2; // 2 colors: B&W
  switch(options.screen_format)
    {
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
    }
  fclose(image);  
  
  return 0;
}
