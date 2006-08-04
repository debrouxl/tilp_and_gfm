/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
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

/* OS Defintion Checker */
#if !defined(__LINUX__) && !defined(__WIN32__) && !defined(__MACOSX__) && !defined(__BSD__)
#error You should define an operating with GCC so I know what to compile! __LINUX__ => Linux, __WIN32__ => Windows, __MACOSX__ => MacOSX, __BSD__ => BSD
#endif

/* tilibs2 version dependencies */
#define LIBTICABLES2_REQUIRE_VERSION "0.1.1"
#define LIBTICONV_REQUIRE_VERSION "0.0.4"
#define LIBTIFILES2_REQUIRE_VERSION "0.1.5"

/* Group File Manager Version */
#define GFM_VERSION "0.01" // Main Version
#define VERSION GFM_VERSION // Copy

#endif
