/*  tilp - linking program for TI calculators
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

/*
  This file contains a function for initializing the structure which
  contains the GUI independant functions
*/

#include <stdio.h>
#include <string.h>

#include "gui_indep.h"

GUI_FNCTS *gif = NULL;

/*
  Initialize the internal structure
*/
void set_gui_fncts(GUI_FNCTS *gf)
{
  gif = gf;
}





