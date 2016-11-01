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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __TILP_VERSION__
#define __TILP_VERSION__

/*
  This file contains version number
  and library requirements.
*/

/* TiLibs2 version dependencies */
#define TILP_REQUIRES_LIBTICONV_VERSION   "1.1.6"
#define TILP_REQUIRES_LIBTIFILES2_VERSION  "1.1.8"
#define TILP_REQUIRES_LIBTICABLES2_VERSION "1.3.6"
#define TILP_REQUIRES_LIBTICALCS2_VERSION  "1.1.10"

/* TILP version */
#ifdef __WIN32__
# define TILP_VERSION "1.19"
#else
# define TILP_VERSION VERSION
#endif

#endif
