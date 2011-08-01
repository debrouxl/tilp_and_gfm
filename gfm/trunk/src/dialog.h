/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef __GFMDIALOG_H__
#define __GFMDIALOG_H__

/* Enumerations */
enum gfm_dialog_enum {
  MSGBOX_NO=0, MSGBOX_YES=1,
  MSGBOX_BUTTON1=2, MSGBOX_BUTTON2=3,
  MSGBOX_ERROR=1, MSGBOX_INFO=2,
  MSGBOX_CONTINUE=3, MSGBOX_YESNO=4, MSGBOX_TWO=5
};

/* Prototypes */
int msgbox_one(int type, const char *message);
int msgbox_two(int type, const char *message);
int msgbox_three(const char *button1, const char *button2, const char *message);
char *msgbox_input(const char *title, const char *input, const char *question);
int msgbox_model(void);

// Definitions
#define msgbox_error(message) msgbox_one(MSGBOX_ERROR, message)

#endif
