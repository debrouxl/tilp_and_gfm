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

#ifndef __CLIST_RBM__
#define __CLIST_RBM__

GtkWidget *create_clist_rbm(void);

GLADE_CB void rbm_delete_file1_activate(GtkMenuItem * menuitem,
				       gpointer user_data);

GLADE_CB void rbm_cut1_activate(GtkMenuItem * menuitem, gpointer user_data);
GLADE_CB void rbm_copy1_activate(GtkMenuItem * menuitem,
				gpointer user_data);
GLADE_CB void rbm_paste1_activate(GtkMenuItem * menuitem,
				 gpointer user_data);


#endif
