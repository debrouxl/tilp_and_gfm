/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001 Julien BLACHE <jb@technologeek.org>
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
 
#include "cocoa_sheets.h"
#include "cocoa_structs.h"
 
extern struct cocoa_objects_ptr *objects_ptr;

#import <Cocoa/Cocoa.h>
#import "SheetsController.h"
 
// we could use NSbeep(); on some boxes (dlgboxEntry maybe ?)
// and also request the user attention (ie. the app's icon will jump on the screen)
// see requestUserAttention()
 
void
create_cocoa_msg_sheet(const char *title, char *message)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;

    [mySheetsController msgSheet:[NSString stringWithCString:message]
                      title:[NSString stringWithCString:title]];
}

int
create_cocoa_user1_sheet(const char *title, char *message, const char *button1)
{
    int ret;

    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    ret = [mySheetsController user1Sheet:[NSString stringWithCString:message]
                        button1:[NSString stringWithCString:button1]];
                        
    return ret;
}
                                                    
 
int
create_cocoa_user2_sheet(const char *title, char *message, const char *button1, const char *button2)
{
    int ret;

    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    ret = [mySheetsController user2Sheet:[NSString stringWithCString:message]
                              button1:[NSString stringWithCString:button1]
                              button2:[NSString stringWithCString:button2]];

    return ret;
}
 
int
create_cocoa_user3_sheet(const char *title, char *message, const char *button1, const char *button2, const char *button3)
{
    int ret;

    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    ret = [mySheetsController user3Sheet:[NSString stringWithCString:message]
                              button1:[NSString stringWithCString:button1]
                              button2:[NSString stringWithCString:button2]
                              button3:[NSString stringWithCString:button3]];
                              
    return ret;
}

char *
create_cocoa_dlgbox_entry(const char *title, const char *message, const char *content)
{
    char *ret;

    id mySheetsController;
    NSString *data;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    data = [mySheetsController dlgboxEntry:[NSString stringWithCString:message]
                               content:[NSString stringWithCString:content]];
                               
    ret = (char *)malloc(([data cStringLength] + 1) * sizeof(char));
    
    [data getCString:ret];
    
    [data release];
    objects_ptr->dlgbox_data = nil;
    
    return ret;
}
 
void
create_cocoa_pbar_type2_sheet(const char *title, char *message)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController pbarType2:[NSString stringWithCString:message]];
}
 
 
void
create_cocoa_pbar_type1_sheet(const char *title)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController pbarType1];
}
 
void
create_cocoa_pbar_type3_sheet(const char *title)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController pbarType3];
}
 
void
create_cocoa_pbar_type4_sheet(const char *title, char *text)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController pbarType4:[NSString stringWithCString:text]];
}
 
void
create_cocoa_pbar_type5_sheet(const char *title, char *text)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController pbarType5:[NSString stringWithCString:text]];
}

void
destroy_pbar(void)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController destroyPbar];
}
