/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
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

/*
  This file contains contains some global definitions
*/

#ifndef DEFS_H
#define DEFS_H

/* The sorting order */
#define SORT_BY_NAME  1
#define SORT_BY_DATE  2
#define SORT_BY_SIZE  4
#define SORT_BY_USER  8
#define SORT_BY_GROUP 16
#define SORT_BY_ATTRB 32
#define SORT_DOWN     0
#define SORT_UP       1
#define SORT_BY_INFO  64
#define SORT_BY_TYPE  128

/* Confirm or not confirm, that is the question ... */
#define CONFIRM_NO  0
#define CONFIRM_YES 1

/* Show or hide */
#define SHOW 1
#define HIDE 0

/* ?? */
#define UNLOCK 0
#define LOCK   1

/* Server or not */
#define NO_SERVER  0
#define USE_SERVER 1

/* 'tidev' kernel module or not */
#define NO_TIDEV 0
#define USE_TIDEV 1

/* PCX or XPM image format */
#define JPG 2
#define PCX 1
#define XPM 0

/* Cut or copy selected file */
#define CUT_FILE  1
#define COPY_FILE 2

/* Plugins at startup or manually */
#define PLUGINS_AUTO   1
#define PLUGINS_MANUAL 0

/* Values returned by the msg_box function */
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3

/* Different working modes */
#define MODE_CMD 1 /* Console mode */
#define MODE_CON 2 /* Command line mode */
#define MODE_GTK 3 /* GTK gui mode (Linux/Win32) */
#define MODE_MFC 4 /* MFC gui mode (WiN32 only) */
#define MODE_INT 5 /* Interactive mode (Linux only) */
#define MODE_OSX 6 /* Cocoa GUI mode (Mac OS X) */

/* Cmd line operation to perform */
#define OP_BACKUP    1
#define OP_FLASH_APP 2
#define OP_FLASH_OS  3
#define OP_FILE      4

/* Transfer mode */
#define SILENT_MODE 1
#define MANUAL_MODE 2

/* File checking */
#define FILE_CHECKING_OFF 0
#define FILE_CHECKING_MID 1
#define FILE_CHECKING_ON  2



#endif



