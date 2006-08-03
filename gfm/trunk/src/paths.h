/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  28/05/06 20:40 - paths.h
  
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

/* Structures */
#ifndef __MACOSX__
typedef struct
{
        gchar *base_dir; // Main Directory
        gchar *help_dir; // Help Directory
        gchar *pixmap_dir; // Pixmaps Directory
        gchar *glade_dir; // Directory with Glade Files
        gchar *tmp_dir; // Temporary File Directory
        gchar *home_dir; // Home Directory
} GFMInstPaths;

// Lets Prototype the Structure
extern GFMInstPaths inst_paths;
#endif /* No MacOSX! */

int gfm_paths_init(void); // Setup The Installation Paths for GFM
const char *gfm_paths_build_glade(const char *name); // Used to return exact path to Glade File
