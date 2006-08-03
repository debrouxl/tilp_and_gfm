/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  10/06/06 20:23 - ftree_sort.c

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <tilp2/tifiles.h>

#include "folder_tree.h"
#include "gfm.h"

/* Sort by Filename Routine */
static gint ftree_sort_name(gpointer a, gpointer b)
{
    FileEntry *fe_a = (FileEntry *)a;
    FileEntry *fe_b = (FileEntry *)b;

    // Lets compare
    if ((((fe_a->attrib & S_IFMT) == S_IFDIR) && ((fe_b->attrib & S_IFMT) == S_IFDIR)) ||
		(((fe_a->attrib & S_IFMT) != S_IFDIR) && ((fe_b->attrib & S_IFMT) != S_IFDIR)))
		return strcmp(fe_a->name, fe_b->name);
	else if (((fe_b->attrib & S_IFMT) == S_IFDIR) && strcmp(fe_a->name, fe_b->name))
		return !0;


    // Return
	return 0;
}

/* Sort by Type Routine */
static gint ftree_sort_type(gpointer a, gpointer b)
{
    FileEntry* fi_b = (FileEntry *)b;

	// Compare & Return
	return ((fi_b->attrib & S_IFMT) == S_IFDIR);
}

/* Sort by Size Routine */
static gint ftree_sort_size(gpointer a, gpointer b)
{
    FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;

    // Compare
	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR)))
		return (fa->size > fb->size);
	else if (((fb->attrib & S_IFMT) == S_IFDIR) && (fa->size > fb->size))
		return !0;

    // Return
	return 0;
}
#include <time.h>
/* Sort by Date Routine */
static gint ftree_sort_date(gpointer a, gpointer b)
{
    FileEntry* fa = (FileEntry *)a;
	FileEntry* fb = (FileEntry *)b;

    // Compare
	if ((((fa->attrib & S_IFMT) == S_IFDIR) && ((fb->attrib & S_IFMT) == S_IFDIR)) ||
		(((fa->attrib & S_IFMT) != S_IFDIR) && ((fb->attrib & S_IFMT) != S_IFDIR)))
        return (fa->date > fb->date);
	else if (((fb->attrib & S_IFMT) == S_IFDIR) && (fa->date > fb->date))
		return !0;

    // Return
	return 0;
}

/* Sort the Tree */
int ftree_sort_list(int sort_order)
{
    // Sort
    switch(sort_order)
    {
        case FTREE_SORT_NAME: // Sort by Name
             ftree_info.dir_list = g_list_sort(ftree_info.dir_list, (GCompareFunc)ftree_sort_name);
        break;
        case FTREE_SORT_TYPE: // Sort by Type
             ftree_info.dir_list = g_list_sort(ftree_info.dir_list, (GCompareFunc)ftree_sort_type);
        break;
        case FTREE_SORT_SIZE: // Sort by Size
             ftree_info.dir_list = g_list_sort(ftree_info.dir_list, (GCompareFunc)ftree_sort_size);
        break;
        case FTREE_SORT_DATE: // Sort by Date
             ftree_info.dir_list = g_list_sort(ftree_info.dir_list, (GCompareFunc)ftree_sort_date);
        break;
        default:
             break; // Nothing
    }

    // Reverse the List?
    if (ftree_info.sort_order)
        ftree_info.dir_list = g_list_reverse(ftree_info.dir_list); // Flipped List

    // Return
    return 0;
}
