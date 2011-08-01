/* Hey EMACS -*- linux-c -*- */
/* $Id: unistd.h 366 2004-03-22 18:04:07Z roms $ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef __WIN32__

#ifndef UNISTD_H
#define UNISTD_H

#include <direct.h> //for mkdir, chdir, getcwd
#include <io.h>		//for access

#define F_OK 0
#define mkdir(dir,mode) _mkdir(dir)

void usleep(int ms);

#endif

#endif
