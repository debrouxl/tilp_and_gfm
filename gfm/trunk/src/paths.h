/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef __GFMPATHS_H__
#define __GFMPATHS_H__

// MSVC Definition
#if defined(__WIN32__) && defined(_MSC_VER)
#define SHARE_DIR ""
#endif

/* Missing of Definitions */
#ifndef SHARE_DIR
#error "Maybe trying to define a SHARE_DIR definition to GCC to where you shared stuff for GFM will be located before compiling."
#endif

/* Structures */
typedef struct
{
    gchar *base_dir;   // Main Directory
    gchar *help_dir;   // Help Directory
    gchar *pixmap_dir; // Pixmaps Directory
    gchar *glade_dir;  // Directory with Glade Files
    gchar *tmp_dir;    // Temporary File Directory
    gchar *home_dir;   // Home Directory
    gchar *locale_dir; // Translations Directory
} GFMInstPaths;

// Lets Prototype the Structure
extern GFMInstPaths inst_paths;

int paths_init(void);                            // Setup The Installation Paths for GFM
const char *paths_build_glade(const char *name); // Used to return exact path to Glade File

#endif
