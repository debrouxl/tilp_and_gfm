/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
  This file contains contains some global definitions
*/

#ifndef __TILP_DEFS_H__
#define __TILP_DEFS_H__

/* The sorting order */
#define SORT_BY_NAME  (1 << 0)
#define SORT_BY_DATE  (1 << 1)
#define SORT_BY_SIZE  (1 << 2)
#define SORT_BY_USER  (1 << 3)
#define SORT_BY_GROUP (1 << 4)
#define SORT_BY_ATTRB (1 << 5)
#define SORT_BY_INFO  (1 << 6)
#define SORT_BY_TYPE  (1 << 7)

#define SORT_DOWN     0
#define SORT_UP       1

/* Confirm or not confirm, that's question ;-) */
#define CONFIRM_NO    0
#define CONFIRM_YES (!0)

/* Show or hide */
#define SHOW (!0)
#define HIDE   0

/* File receiving */
#define RECV_AS_SINGLE   0
#define RECV_AS_GROUP  (!0)

/* File displaying */
#define SHOW_ALL (!0)
#define SHOW_TIF   0

/* Transfer in progress (mutex locking) */
#define UNLOCK   0
#define LOCK   (!0)

/* Image format */
#define EPS  7   /* Encapsulated PostScript   */
#define PDF  6   /* Portable Document Format  */
#define PNG  5   /* Portable Network Graphics */
#define TIFF 4   /* Tagged Image File Format  */
#define BMP  3   /* Bitmap					  */
#define JPG  2   /* JPEG format				  */
#define XPM  1   /* pixmap					  */

/* Cut or copy selected file */
#define CUT_FILE	1
#define COPY_FILE	2

/* Values returned by the msg_box function */
#define BUTTON1		1
#define BUTTON2		2
#define BUTTON3		3

/* Several working modes */
#define MODE_INI (1<<0)		/* Startup phase                 */
#define MODE_CMD (1<<1)		/* Command line mode             */

#define MODE_GUI (1<<4)		/* GUI mode (GTK, MFC, Cocoa)    */
#define MODE_TXT (1<<5)		/* no GUI (unused)				 */

#define GTK_WIN_POS_TYPE		GTK_WIN_POS_CENTER

// GTK+ only (export callbacks for GtkBuilder linking at runtime)
#if defined(__WIN32__) && !defined(HAVE_FVISIBILITY)
# define TILP_EXPORT __declspec(dllexport)
#elif defined(HAVE_FVISIBILITY)
# define TILP_EXPORT __attribute__ ((visibility("default")))
#else
# define TILP_EXPORT
#endif

#endif
