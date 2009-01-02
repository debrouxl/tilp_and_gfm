/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
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
#if !defined(_WINDOWS)
	tilp_info("msg_box1: [%s] [%s]", title, message);
	tilp_info("msg_box1: press ENTER for OK");
	fflush(stdin);

	fgetc(stdin);
#endif

	return 0;
}

int default_msg_box2(const char *title, const char *message)
{
#if !defined(_WINDOWS)
    int c;

	tilp_info("msg_box2: [%s] [%s]", title, message);
	tilp_info("msg_box2: press 1 for OK, 2 for CANCEL");

	fflush(stdin);
	c = fgetc(stdin);
	
	switch(c)
	{
	case '1': return BUTTON1;
	default: return BUTTON2;
	}
#endif
	return 0;
}

int default_msg_box3(const char *title, const char *message, 
		     const char *b1, const char *b2, const char *b3)
{
#if !defined(_WINDOWS)
    int c;

	tilp_info("msg_box3: [%s] [%s]", title, message);
	tilp_info("msg_box3: press 1 for %s, 2 for %s, 3 for %s", b1, b2, b3);

	fflush(stdin);
	c = fgetc(stdin);

	switch(c)
	{
	case '1': return BUTTON1;
    case '2': return BUTTON2;
	default: return BUTTON3;
	}
#endif
	return 0;
}

int default_msg_box4(const char *title, const char *message)
{
#if !defined(_WINDOWS)
    int c;
    
	tilp_info("msg_box4: [%s] [%s]", title, message);
	tilp_info("msg_box4: press 1 for FORWARD, press 2 for CANCEL");

	fflush(stdin);
	c = fgetc(stdin);

    switch(c)
    {
    case '1': return BUTTON1;
    default: return BUTTON2;
    }	
#endif
	return 0;
}

char *default_msg_entry(const char *title, const char *message, const char *content)
{
#if !defined(_WINDOWS)
    char buffer[1024];
    int ret;

    tilp_info("msg_entry: [%s] [%s] <%s>", title, message, content);
    tilp_info("msg_entry: type new content or nothing to cancel ");
    
	fflush(stdin);
    ret = fscanf(stdin, "%s", buffer);
    if(ret > 0)
	return g_strdup(buffer);
    else
	return NULL;
#else
	return g_strdup("");
#endif
}

void default_create_pbar_type1(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type2(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type3(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type4(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar_type5(const char *title)
{
	tilp_info("%s: ", title);
}

void default_create_pbar(int type, const char *title)
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

	default_gif.create_pbar = default_create_pbar;
	default_gif.destroy_pbar = default_destroy_pbar;

	tilp_gui_set_fncts(&default_gif);
}
