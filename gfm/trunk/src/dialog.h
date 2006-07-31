/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  04/06/06 16:35 - dialog.h
  
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

/* Enumerations */
enum gfm_dialog_enum {MSGBOX_YES=1, MSGBOX_NO=0,
                      MSGBOX_ERROR=1, MSGBOX_INFO=2,
                      MSGBOX_CONTINUE=3, MSGBOX_YESNO=4, MSGBOX_TWO=5};

/* Prototypes */
int msgbox_error(const char *message);
int msgbox_one(int type, const char *message);
int msgbox_two(int type, const char *message);
