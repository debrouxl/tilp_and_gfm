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

#include <gtk/gtk.h>

enum { FTREE_SORT_NAME=100, FTREE_SORT_TYPE=101, FTREE_SORT_SIZE=102,
       FTREE_SORT_DATE=103 };

// Stores information to public about certain stuff about Folder Tree
typedef struct
{
    GList *dir_list; // List of Files in Directory
    GList *selection; // Selected Files
    int sort_order; // Which Order
    int column; // Which Column to sort on
} FolderTreeData;

// Export Structure
extern FolderTreeData ftree_info;

int folder_tree_init(void);
int folder_tree_refresh(void);
int ftree_sort_list(int sort_order);
