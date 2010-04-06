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
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         
*/

#ifndef __GFMVERSION_H__
#define __GFMVERSION_H__

/* TiLibs2 version dependencies */
#define LIBTICONV_REQUIRE_VERSION	"1.0.4"
#define LIBTIFILES2_REQUIRE_VERSION "1.0.7"
#define LIBTICALCS2_REQUIRE_VERSION "1.0.7"

/* Group File Manager Version */
#ifdef __WIN32__
# define GFM_VERSION "1.04"
#else
# define GFM_VERSION VERSION
#endif

#endif
