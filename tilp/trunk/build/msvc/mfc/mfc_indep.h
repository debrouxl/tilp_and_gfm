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

#ifndef MFC_INDEP_H
#define MFC_INDEP_H

/*
  GUI independant functions for the command line mode
*/

void  mfc_msg_box(const char *title, char *message);
int   mfc_user1_box(const char *title, char *message, 
			const char *b1);
int   mfc_user2_box(const char *title, char *message, 
			const char *b1, const char *b2);
int   mfc_user3_box(const char *title, char *message, 
			const char *b1, const char *b2, const char *b3);
char* mfc_dlgbox_entry(const char *title, 
			   const char *message, 
			   const char * content);

void mfc_create_pbar_type1(const char *title);
void mfc_create_pbar_type2(const char *title, char *text);
void mfc_create_pbar_type3(const char *title);
void mfc_create_pbar_type4(const char *title, char *text);
void mfc_create_pbar_type5(const char *title, char *text);
void mfc_destroy_pbar(void);

#endif




