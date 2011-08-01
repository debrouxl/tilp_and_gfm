/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  04/06/06 17:04 - gui.h
  
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

#ifndef __GFMGUI_H__
#define __GFMGUI_H__

/* Structures */
typedef struct 
{
	GtkWidget *tree;
	GtkWidget *model;
	GtkWidget *entries;
	GtkWidget *comment;
	GtkWidget *ram;
	GtkWidget *flash;
	GtkWidget *save;
	GtkWidget *pbar;

	GList	*sel1;	// vars
	GList	*sel2;	// apps
} GFMWidget; 
extern GFMWidget gfm_widget;

/* Prototypes */
int launch_gfmgui(void);

void enable_save(int state);
void enable_tree(int state);

#endif
