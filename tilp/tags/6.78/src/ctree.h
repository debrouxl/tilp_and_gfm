/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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

#ifndef __CTREE_H__
#define __CTREE_H__

enum {
  CTREE_NAME, CTREE_ATTR, CTREE_TYPE, CTREE_SIZE,
  CTREE_DATA, CTREE_FONT, CTREE_ICON,
  CTREE_NUMBER
};
#define CTREE_NCOLS CTREE_DATA

#define NODE1 _("Screen")
#define NODE2 _("Operating System")
#define NODE3 _("Variables")
#define NODE4 _("Applications")
#define NODEx _("Any Folder")

void ctree_init(void);
void ctree_refresh(void);
void ctree_selection_refresh(void);
void ctree_set_basetree(void);

#endif
