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
  
#ifndef __COCOA_STRUCTS_H__
#define __COCOA_STRUCTS_H__
 
#import <Cocoa/Cocoa.h>
#import <SimpleTreeNode.h>
 
struct cocoa_objects_ptr
{
    // our classes
    id myBoxesController;
    id myMenuController;
    id myPrefsController;
    id myTilpController;
    id mySheetsController;

    // return values for some dialog sheets
    // this is a quick hack to workaround the C way-of-life ;-)
    int user1_return;
    int user2_return;
    int user3_return;
    NSString *dlgbox_data;
      
    // used by the preferences system
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
};
 
#endif /* !__COCOA_STRUCTS_H__ */