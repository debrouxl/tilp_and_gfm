/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  04/10/06 19:56 - gtree.h

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

#ifndef __GFM_GTREE_H__
#define __GFM_GTREE_H__

#include <gtk/gtk.h>

enum { GTREE_SORT_NAME=100, GTREE_SORT_TYPE=101, GTREE_SORT_SIZE=102 };
enum { GTREE_SORT_ASC=FALSE, GTREE_SORT_DESC=TRUE };

// Stores information to public about certain stuff about the Group Tree
typedef struct
{
  GList *selection; // List of Selected Files
  gboolean sort_order; // Which Order
  int column; // Which Column to sort on
} GroupTreeData;

// Export Structure
extern GroupTreeData gtree_info;

int group_tree_init(void);
int group_tree_clear(void);

#endif
