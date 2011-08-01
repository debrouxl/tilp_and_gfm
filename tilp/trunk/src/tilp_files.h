/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __TILP_FILES__
#define __TILP_FILES__

#include "tilp_struct.h"

int tilp_file_copy(const char *src, const char *dst);
int tilp_file_move(const char *src, const char *dst);
int tilp_file_delete(const char *f);
int tilp_file_mkdir(const char *pathname);
int tilp_file_exist(const char* filename);
int tilp_file_check(const char *src, char **dst);
int tilp_file_move_with_check(const char *src, const char *dst);
int tilp_file_chdir(const char *path);

char *tilp_file_underscorize(char *s);

const char* tilp_file_get_attributes(FileEntry* fi);
void        tilp_file_get_user_name(FileEntry* fi, char **name);
void        tilp_file_get_group_name(FileEntry* fi, char **name);
const char* tilp_file_get_date(FileEntry* fi);
const char* tilp_file_get_size(FileEntry* fi);
const char* tilp_file_get_type(FileEntry* fi);


int tilp_file_dirlist(void);
int tilp_dirlist_local(void);

void tilp_file_sort_by_type(void);
void tilp_file_sort_by_name(void);
void tilp_file_sort_by_date(void);
void tilp_file_sort_by_size(void);
void tilp_file_sort_by_attrib(void);


#endif
