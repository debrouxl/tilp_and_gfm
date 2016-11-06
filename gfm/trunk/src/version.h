/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  29/05/06 17:20 - version.h
  
  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef __GFM_VERSION_H__
#define __GFM_VERSION_H__

/*
  This file contains version number
  and library requirements.
*/

/* TiLibs2 version dependencies */
#define GFM_REQUIRES_LIBTICONV_VERSION   "1.1.6"
#define GFM_REQUIRES_LIBTIFILES2_VERSION "1.1.8"
#define GFM_REQUIRES_LIBTICALCS2_VERSION "1.1.10"
#define GFM_REQUIRES_LIBTIOPERS_VERSION  "1.0.0"

/* Group File Manager version */
#ifdef __WIN32__
# define GFM_VERSION "1.09"
#else
# define GFM_VERSION VERSION
#endif

#endif
