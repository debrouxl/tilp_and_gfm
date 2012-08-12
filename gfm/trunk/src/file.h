/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  29/05/06 17:51 - file.h
  
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

#ifndef __GFMFILE_H__
#define __GFMFILE_H__

#include "tilibs.h"

/* Prototypes */
int file_exists(const char *filename);
int file_copy(const char *src, const char *dst);
int file_chdir(const char *path);
int file_mkdir(const char *pathname);
void glade_files_check(void);

char *tilp_file_underscorize(char *s);
void tilp_var_get_size(VarEntry* vi, char **buf);
void tilp_vars_translate(char *utf8);

#endif
