/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

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

#include "tilp_core.h"

TilpGuiFncts *gif;

int default_msg_box(const char *title, const char *message, int action)
{
	tilp_info("msg_box: [%s] [%s]", title, message);
	return 0;
}

int default_msg_box1(const char *title, const char *message)
{
	tilp_info("msg_box: [%s] [%s]", title, message);
	return 0;
}

int default_msg_box2(const char *title, const char *message)
{
	tilp_info("user1_box: [%s] [%s]", title, message);
	return 0;
}

int default_msg_box3(const char *title, const char *message, 
		     const char *b1, const char *b2, const char *b3)
{
	tilp_info("user1_box: [%s] [%s]", title, message);
	return 0;
}

int default_msg_box4(const char *title, const char *message)
{
	tilp_info("user1_box: [%s] [%s]", title, message);
	return 0;
}
char *default_msg_entry(const char *title, const char *message, const char *content)
{
	return NULL;
}
void default_create_pbar_type1(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type2(const char *title, char *text)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type3(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type4(const char *title, char *text)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type5(const char *title, char *text)
{
	tilp_info("%s: ", title);
}

void default_destroy_pbar(void)
{
}

/*
  Initialize the internal structure
*/
void tilp_gui_set_fncts(TilpGuiFncts* gf)
{
	gif = gf;
}

void tilp_gif_set_default(void)
{
	static TilpGuiFncts default_gif;

	default_gif.msg_box  = default_msg_box;
	default_gif.msg_box1 = default_msg_box1;
	default_gif.msg_box2 = default_msg_box2;
	default_gif.msg_box3 = default_msg_box3;
	default_gif.msg_box4 = default_msg_box4;
	default_gif.msg_entry = default_msg_entry;
	default_gif.create_pbar_type1 = default_create_pbar_type1;
	default_gif.create_pbar_type2 = default_create_pbar_type2;
	default_gif.create_pbar_type3 = default_create_pbar_type3;
	default_gif.create_pbar_type4 = default_create_pbar_type4;
	default_gif.create_pbar_type5 = default_create_pbar_type5;
	default_gif.destroy_pbar = default_destroy_pbar;

	tilp_gui_set_fncts(&default_gif);
}
