/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Julien BLACHE <jb@tilp.info>
 *
 *  $Id$
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
 
#include <stdint.h>

#define SKIN_KEYS 80

struct cocoa_objects_ptr
{
    // our classes
    id myBoxesController;
    id myMenuController;
    id myPrefsController;
    id myTilpController;
    id mySheetsController;
    id myTransfersController;

    id myCalcKeyboardController;

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
 
// not really tied to cocoa, but I don't want to make another header file
typedef struct tagRECT_
{
  uint32_t left;
  uint32_t top;
  uint32_t right;
  uint32_t bottom;
} RECT_;
 
#endif /* !__COCOA_STRUCTS_H__ */