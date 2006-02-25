/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TILP_SLCT__
#define __TILP_SLCT__

void tilp_clist_selection_destroy(void);
void tilp_ctree_selection_destroy(void);

void tilp_clist_file_selection_destroy(void);
void tilp_add_file_to_file_selection(const char *filename);

void tilp_delete_selected_files(void);
void tilp_rename_selected_files(void);

int  tilp_clist_selection_ready(void);
int  tilp_ctree_selection_ready(void);
int  tilp_ctree_selection2_ready(void);

void tilp_clist_selection_display(void);

void tilp_slct_load_contents(void);
void tilp_slct_unload_contents(void);

void tilp_slct_change_folder(const char *target);
void tilp_slct_update_dirlist(void);

void tilp_add_file_to_selection(const char *filename);
void tilp_clist_add_file_to_selection(const char* filename);

#endif
