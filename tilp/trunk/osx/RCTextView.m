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

#import "RCTextView.h"

#import "TransfersController.h"

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;


@implementation NSTextView (MyExtensions)

- (void)insertTextFromCalc:(NSString *)aString
{
    // FIXME OS X
    // The terminal mode is not implemented in libticalcs at the moment.
    // This method will be written when the libticalcs will support terminal mode.

}

- (void)insertTextStatus:(NSString *)aString
{
    [self setString:[[self string] stringByAppendingString:aString]];
    
    [self didChangeText];
    
    [self display];
}

@end


@implementation RCTextView

- (void)insertText:(id)aString
{
    NSString *string;
    unichar c;
    id myTransfersController;

    unsigned int i;
    int ret;

    string = (NSString *)aString;
    myTransfersController = objects_ptr->myTransfersController;

    fprintf(stderr, "DEBUG: insert text (length : %d, %d) %s\n", [string cStringLength], [string length], [string cString]);
    
    for (i = 0; i < [string length]; i++)
        {
            c = [string characterAtIndex:i];
        
            ret = [myTransfersController sendChar:[NSString stringWithCharacters:&c length:1]];
            
            if (ret)
                {
                    [self setString:[[self string] stringByAppendingString:[NSString stringWithCString:"\n\n*** Communication Error. Aborted. ***\n"]]];
                    
                    break;
                }
            else
                {
                    [self setString:[[self string] stringByAppendingString:string]];
                    
                    [self didChangeText];
    
                    [self display];
                }
        }
    
    [self didChangeText];
    
    [self display];
}

@end
