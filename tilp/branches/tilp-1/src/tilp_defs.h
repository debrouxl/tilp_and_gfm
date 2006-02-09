/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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
#define SORT_BY_INFO  64
#define SORT_BY_TYPE  128

#define SORT_DOWN     0
#define SORT_UP       1

/* Confirm or not confirm, that's question ... */
#define CONFIRM_NO    0
#define CONFIRM_YES (!0)

/* Show or hide */
#define SHOW (!0)
#define HIDE   0


/* Transfer in progress (mutex locking) */
#define UNLOCK   0
#define LOCK   (!0)


/* Image format */
#define EPS  7   /* Encapsulated PostScript */
#define PDF  6   /* Portable Document Format */
#define PNG  5   /* Portable Network Graphics */
#define TIFF 4   /* Tagged Image File Format */
#define BMP  3   /* Bitmap */
#define JPG  2   /* JPEG format */
#define PCX  1   /* PCX */
#define XPM  0   /* pixmap */


/* Cut or copy selected file */
#define CUT_FILE  1
#define COPY_FILE 2


/* Values returned by the msg_box function */
#define BUTTON1  1
#define BUTTON2  2
#define BUTTON3  3


/* Several working modes */
#define MODE_INI     0		/* Startup phase                 */
#define MODE_CON (1<<0)		/* Console mode                  */
#define MODE_CMD (1<<1)		/* Command line mode             */
#define MODE_GTK (1<<2)		/* GTK gui mode (Linux/Win32)    */
#define MODE_MFC (1<<3)		/* MFC gui mode (WiN32 only)     */
#define MODE_OSX (1<<4)		/* Cocoa GUI mode (Mac OS X)     */
#define MODE_GUI (1<<5)		/* GUI mode (GTK, MFC, Cocoa)    */


/* Cmd line operation to perform */
#define OP_BACKUP    1
#define OP_FLASH_APP 2
#define OP_FLASH_OS  3
#define OP_FILE      4


/* Terminal/remote control operating mode */
#define REMOTE 1
#define TERM   2

/* Calculator state */
#define READY_NOK -1


/* File receiving */
#define RECV_AS_SINGLE   0
#define RECV_AS_GROUP  (!0)


/* Checksum */
#define USE_CHECKSUM   (!0)
#define NOUSE_CHECKSUM   0


/* File displaying */
#define SHOW_ALL (!0)
#define SHOW_TIF   0


/* Transfer way */
#define CALC_TO_COMP 1
#define COMP_TO_CALC 2


/* Clock update mode */
#define CLOCK_MANUAL 1
#define CLOCK_SYNC   2

#endif
