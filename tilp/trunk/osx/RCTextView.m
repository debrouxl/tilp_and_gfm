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

#warning Compiling RCTextView

@implementation NSTextView (MyExtensions)

@end




@implementation RCTextView

- (void)insertText:(id)aString
{
    NSString *string;
    unichar c;

    unsigned int i;

    string = (NSString *)aString;

    fprintf(stderr, "DEBUG: insert text (length : %d, %d) %s\n", [string cStringLength], [string length], [string cString]);

    if ([string length] > 1)
        {
            fprintf(stderr, "DEBUG: processing string char by char\n");
            
            for (i = 0; i < [string length]; i++)
                {
                    c = [string characterAtIndex:i];
                    [self insertText:[NSString stringWithCharacters:&c length:1]];
                }
        }
    else
        {
            // FIXME OS X
            // process input HERE !!
            
            // Try to send to the calc, then display.
        
            [self setString:[[self string] stringByAppendingString:string]];
        }
    
    [self display];
}

@end
