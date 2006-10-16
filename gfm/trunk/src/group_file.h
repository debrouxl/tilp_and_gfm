/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  12/10/06 20:39 - group_file.h

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

#ifndef __GFM_GFILE_H__
#define __GFM_GFILE_H__

#include <glib.h>

#include "tilibs.h"

// Modified Structure for easier use in GFM
typedef struct
{
  char *name; // Name of file
  FileClass type; // Type of File
  int size; // Size of File
  int loc_top, loc_bot; // Where is it located in TigContent?
  CalcModel model; // Calculator model for file
} tigfview;

// Main TI Group File Data Structure
typedef struct
{
  tigfview **list; // The list of Files in the TiG File
  int file_size; // Size of files within TiG
  int num_entries; // Number of entries
  TigContent *TigFile; // The Contents of the TiG File
} GFileStruct;

extern GFileStruct GFile;

// Prototypes
int tigfile_create(gboolean globaltize);
int tigfile_open(const char *filename);

#endif
