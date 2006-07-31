/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  08/06/06 17:49 - gfm.h
  
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

#ifndef __GFM_H__
#define __GFM_H__

#include <glib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tilp2/tifiles.h>

/* Used by the local directory list function */
typedef struct 
{
    char *name; // Filename
    char *path; // Full path to file, including file
    time_t date; // Date
    off_t size; // Size
    
    // OS Issues
    #ifdef __WIN32__
    int user;
    int group;
    int attrib;
    #else
    uid_t user;
    gid_t group;
    mode_t attrib;
    #endif

	// Actions
	FileContent *content;	// File Content to Handle
	int *selected;	// entry/entries is/are selected
} FileEntry;

/* Current GFM Settings */
typedef struct
{
    gboolean confirm, show_all; // Confirm Deletion, Show all files
    gchar *cur_dir; // Current Directory
    gchar *cur_file; // Current Group File
} SettingsStruct;

// Globalize a Structure
extern SettingsStruct settings;

#endif
