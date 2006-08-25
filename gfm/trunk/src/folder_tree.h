/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  06/06/06 19:45 - folder_tree.h
  
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

#ifndef __GFMFTREE_H__
#define __GFMFTREE_H__

#include <gtk/gtk.h>

enum { FTREE_SORT_NAME=100, FTREE_SORT_TYPE=101, FTREE_SORT_SIZE=102,
       FTREE_SORT_DATE=103 };
enum { FTREE_SORT_ASC=FALSE, FTREE_SORT_DESC=TRUE };
enum { WORKING_ACT_CUT=200, WORKING_ACT_COPY=201 };
			 
// Stores information to public about certain stuff about Folder Tree
typedef struct
{
    GList *dir_list; // List of Files in Directory
    GList *selection; // List of Selected Files
    gboolean sort_order; // Which Order
    int column; // Which Column to sort on
		int working_act; // Working Action
		GList *selected_files; // List of Selected File Paths
} FolderTreeData;

// Export Structure
extern FolderTreeData ftree_info;

int folder_tree_init(void);
int folder_tree_refresh(void);
int ftree_sort_list(int sort_order);

#endif
