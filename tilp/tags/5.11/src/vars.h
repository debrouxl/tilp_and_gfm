/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef CVARS_H
#define CVARS_H

#include "struct.h"

#ifdef __cplusplus
extern "C" {
#endif

  //debug only
  void display_varlist(TicalcVarInfo *varlist);
  void dislpay_dirlist(void);

void varlist_to_glist(struct varinfo varlist);
struct varinfo *glist_to_varlist(GList *glist);
void generate_group_file_header(FILE *file, int mask_mode, 
				const char *id, struct varinfo *v, 
				int calc_type);

int c_directory_list(void);
#define remote_directory_list c_directory_list

void sort_cfiles_by_name(GList *list);
void sort_cfiles_by_info(GList *list);
void sort_cfiles_by_type(GList *list);
void sort_cfiles_by_size(GList *list);

#ifdef __cplusplus
}
#endif

#endif





