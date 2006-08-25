/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
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
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.         
*/

#ifndef __GFMFILE_H__
#define __GFMFILE_H__

#include <gtk/gtk.h>
#include "gfm.h"

/* Prototypes */
int file_exists(const char *filename);
void glade_files_check(void);
int file_get_dirlist(void);
char *file_fix_letters(char *string);
const char *file_get_type(FileEntry *fe);
const char *file_get_size(FileEntry *fe);
const char *file_get_date(FileEntry *fe);
int gfm_change_cwd(const char *path);
int gfm_copy_file(const char *source, const char *destination);
int gfm_move_file(const char *source, const char *destination);
int gfm_delete_file(const gchar *filename);

#endif
