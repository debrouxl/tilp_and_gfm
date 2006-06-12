/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_gif.c 1198 2005-06-12 17:30:33Z roms $ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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

/*
	Default callbacks for GUI Independant Functions
*/

#include <stdio.h>
#include <string.h>

#include "pbars.h"
#include "dboxes.h"
#include "gstruct.h"
#include "tilp_core.h"

void tilp_gif_set_gtk(void)
{
	static TilpGuiFncts gtk_gif;

	gtk_gif.msg_box  = msg_box;
	gtk_gif.msg_box1 = msg_box1;
	gtk_gif.msg_box2 = msg_box2;
	gtk_gif.msg_box3 = msg_box3;
	gtk_gif.msg_box4 = msg_box4;

	gtk_gif.msg_entry = msg_entry;

	gtk_gif.create_pbar_type1 = create_pbar_type1;
	gtk_gif.create_pbar_type2 = create_pbar_type2;
	gtk_gif.create_pbar_type3 = create_pbar_type3;
	gtk_gif.create_pbar_type4 = create_pbar_type4;
	gtk_gif.create_pbar_type5 = create_pbar_type5;

	gtk_gif.create_pbar = create_pbar;
	gtk_gif.destroy_pbar = destroy_pbar;


	tilp_gui_set_fncts(&gtk_gif);
}
