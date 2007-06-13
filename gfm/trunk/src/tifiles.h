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

// Structures
typedef struct
{
	char		*filename;	// Name of file
	FileClass	type;		// TiGroup or Regular (single/group)
	CalcModel	model;		// Hand-held model

	union
	{
		TigContent	*tigroup;	// TiGroup or NULL
		FileContent	*group;		// Group or NULL
	} contents;

	struct
	{
		TNode		*vars;		// Variables tree
		TNode		*apps;		// Applications tree
	} trees;
} GFileStruct;


// Prototypes
int	tigfile_create(CalcModel model);
int tigfile_load(const char *filename);
int tigfile_save(const char *filename);
int tigfile_destroy(void);

int	group_create(CalcModel model);
int group_load(const char *filename);
int group_save(const char *filename);
int group_destroy(void);

#endif
