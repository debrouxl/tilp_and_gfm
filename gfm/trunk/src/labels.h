/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  12/08/06 17:12 - labels.h

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

#ifndef __GFMLABELS_H__
#define __GFMLABELS_H__

#include "tilibs.h"

// Prototypes
void labels_set_model(CalcModel model);
void labels_set_entries(int n);
void labels_set_comment(const char* comment);
void labels_set_ram(uint32_t ram);
void labels_set_flash(uint32_t flash);

void labels_refresh(void);

#endif
