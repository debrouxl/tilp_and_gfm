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
 
/*
 * This code is derived from Apple Sample Code (DragNDropOutlineView)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */
 
#import "NSArray_Extensions.h"


@implementation NSArray (MyExtensions)

- (BOOL) containsObjectIdenticalTo: (id)obj { 
    return [self indexOfObjectIdenticalTo: obj]!=NSNotFound; 
}

@end

@implementation NSMutableArray (MyExtensions)

- (void) insertObjectsFromArray:(NSArray *)array atIndex:(int)index {
    NSObject *entry = nil;
    NSEnumerator *enumerator = [array objectEnumerator];
    while ((entry=[enumerator nextObject])) {
        [self insertObject:entry atIndex:index++];
    }
}

@end
