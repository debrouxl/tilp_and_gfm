/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2002 Julien BLACHE <jb@technologeek.org>
 *
 *  skinedit - a skin editor for TiEmu v2.00
 *  Copyright (C) 2002 Julien BLACHE <jb@technologeek.org>
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

#import <Cocoa/Cocoa.h>

#include <stdint.h>

#include "cocoa_structs.h"

@interface SkinController : NSObject
{
    IBOutlet id skinView;
    IBOutlet id keyboardWindow;
}

// skin loading methods
- (int)loadSkin:(NSString *)path skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys;
- (int)loadSkinVTi:(NSData *)skin skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys;
- (int)loadSkinOldVTi:(NSData *)skin skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys;
- (int)loadSkinTiEmu:(NSData *)skin skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys;
- (int)loadJPEG:(NSData *)skin atOffset:(uint32_t)jpeg_offset skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys;

@end
