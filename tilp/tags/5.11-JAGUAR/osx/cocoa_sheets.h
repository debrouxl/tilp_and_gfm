/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2002 Julien BLACHE <jb@technologeek.org>
 *
 *  Cocoa GUI for Mac OS X
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
  
#ifndef __COCOA_MSG_SHEETS_H__
#define __COCOA_MSG_SHEETS_H__

void
create_cocoa_msg_sheet		(const char *title,
                                 char *message);

int
create_cocoa_user1_sheet	(const char *title,
                                 char *message,
                                 const char *button1);
                                                    
void
create_cocoa_pbar_type2_sheet	(const char *title,
                                 char *message);
 
 
int
create_cocoa_user2_sheet	(const char *title,
                                 char *message,
                                 const char *button1,
                                 const char *button2);
 
int
create_cocoa_user3_sheet	(const char *title,
                                 char *message,
                                 const char *button1,
                                 const char *button2,
                                 const char *button3);

char *
create_cocoa_dlgbox_entry	(const char *title,
                                 const char *message,
                                 const char *content);
 
void
create_cocoa_pbar_type1_sheet	(const char *title);
 
void
create_cocoa_pbar_type3_sheet	(const char *title);
 
void
create_cocoa_pbar_type4_sheet	(const char *title,
                                 char *text);
 
void
create_cocoa_pbar_type5_sheet	(const char *title,
                                 char *text);

void
destroy_pbar			(void);

#endif /* !__COCOA_MSG_SHEETS_H__ */
 