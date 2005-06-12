/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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
	This file contains a function for initializing the structure which
	contains the GUI independant functions (GIF)
*/

#include <stdio.h>
#include <string.h>

#include "tilp_core.h"

TilpGuiFncts *gif;

void cmdline_msg_box(const char *title, char *message)
{
	tilp_info("msg_box: %s, %s", title, message);
}

int cmdline_msg_box2(const char *title, char *message)
{
	tilp_info("user1_box: %s, %s", title, message);
	return 0;
}

int cmdline_msg_box3(const char *title, char *message, const char *b1, const char *b2, const char *b3)
{
	tilp_info("user1_box: %s, %s", title, message);
	return 0;
}

int cmdline_msg_box4(const char *title, char *message)
{
	tilp_info("user1_box: %s, %s", title, message);
	return 0;
}
char *cmdline_msg_entry(const char *title, const char *message, const char *content)
{
	return NULL;
}
void cmdline_create_pbar_type1(const char *title)
{
	tilp_info("%s: ", title);
}

void cmdline_create_pbar_type2(const char *title, char *text)
{
	tilp_info("%s: ", title);
}

void cmdline_create_pbar_type3(const char *title)
{
	tilp_info("%s: ", title);
}

void cmdline_create_pbar_type4(const char *title, char *text)
{
	tilp_info("%s: ", title);
}

void cmdline_create_pbar_type5(const char *title, char *text)
{
	tilp_info("%s: ", title);
}

void cmdline_destroy_pbar(void)
{
	tilp_info("");
}

/*
  Initialize the internal structure
*/
void tilp_gui_set_fncts(TilpGuiFncts * gf)
{
	gif = gf;
}

void tilp_indep_set_gui_cmdline(void)
{
	static TilpGuiFncts indep_functions;

	indep_functions.msg_box = cmdline_msg_box;
	indep_functions.msg_box2 = cmdline_msg_box2;
	indep_functions.msg_box3 = cmdline_msg_box3;
	indep_functions.msg_box4 = cmdline_msg_box4;
	indep_functions.msg_entry = cmdline_msg_entry;
	indep_functions.create_pbar_type1 = cmdline_create_pbar_type1;
	indep_functions.create_pbar_type2 = cmdline_create_pbar_type2;
	indep_functions.create_pbar_type3 = cmdline_create_pbar_type3;
	indep_functions.create_pbar_type4 = cmdline_create_pbar_type4;
	indep_functions.create_pbar_type5 = cmdline_create_pbar_type5;
	indep_functions.destroy_pbar = cmdline_destroy_pbar;

	tilp_gui_set_fncts(&indep_functions);
}
