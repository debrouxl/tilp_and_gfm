/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __screen__
#define __screen__

typedef struct 
{
    uint8_t*	bitmap;
    int			width;
    int			height;
} TilpScreen;

extern TilpScreen screen;

int      screen_capture(void);
uint8_t* screen_convert(void);
uint8_t* screen_blurry(void);

gboolean screen_write_eps(const gchar *filename, GError **error);
gboolean screen_write_pdf(const gchar *filename, GError **error);

#endif
