/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __CLIST_RBM_H__
#define __CLIST_RBM_H__

#include "tilp_defs.h"

GtkWidget *create_clist_rbm(void);

TILP_EXPORT void rbm_cut1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void rbm_copy1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void rbm_paste1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void rbm_opengfm_activate(GtkMenuItem* menuitem, gpointer user_data);
TILP_EXPORT void rbm_rename1_activate(GtkMenuItem* menuitem, gpointer user_data);
TILP_EXPORT void rbm_delete_file1_activate(GtkMenuItem * menuitem, gpointer user_data);
TILP_EXPORT void rbm_set_as_working_dir1_activate(GtkMenuItem* menuitem, gpointer user_data);
TILP_EXPORT void rbm_show_all_files1_activate(GtkCheckMenuItem *menuitem, gpointer user_data);
TILP_EXPORT void rbm_confirm_delete_activate(GtkCheckMenuItem *action, gpointer user_data);
TILP_EXPORT void rbm_properties1_activate(GtkMenuItem *menuitem, gpointer user_data);

#endif
