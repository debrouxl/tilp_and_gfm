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

- (void)insertCalcText:(NSString *)aString
{
    // FIXME OS X
    // The terminal mode is not implemented in libticalcs at the moment.
    // This method will be written when the libticalcs will support terminal mode.

}

- (void)insertStatusText:(NSString *)aString
{
#if 0
    [self setString:[[self string] stringByAppendingString:aString]];

    [self didChangeText];
    
    [self display];
#endif

    [self insertText:aString]; // we should not override insertText
    
    [self setTextColor:[NSColor redColor] range:NSMakeRange([[self string] length] - [aString length], [[self string] length])];
}

@end


@implementation RCTextView

// ensure we always reply YES
- (BOOL)acceptsFirstResponder
{
    return YES;
}

// get the key pressed
// then process it
// finally pass it to super if we don't handle it (?)
- (void)keyDown:(NSEvent *)event
{
// The calc seems to be using UNICODE, hopefully we won't have to remap
// a whole bunch of chars, only backspace and some others.

    unsigned int toSend;
    int ret;
    int i;
    
    BOOL send = NO;
    BOOL process = YES;
    NSString *eventChars;
    unichar uchar;
    id myTransfersController;

    myTransfersController = objects_ptr->myTransfersController;
    
    [event retain];
    
    eventChars = [event characters];
    [eventChars retain]; // retain in case of a link problem, prevents a SIGBUS

#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: keyDown EVENT !\n");
#endif
     
    for (i = 0; i < [eventChars length]; i++)
        { 
            process = YES;
            send = NO;
            
            uchar = [eventChars characterAtIndex:i];

#ifdef OSX_DEBUG        
            fprintf(stderr, "DEBUG: UNICODE '%c' val = %d\n", uchar, uchar);   
#endif

            if (uchar == 127) // backspace
                {
                    toSend = 257; // backspace keycode wrt calc
                    
                    send = YES;
                }
            else if ((uchar > 0) && (uchar < 256)) // the calc seems to be using UNICODE in this range
                {
                    toSend = uchar;

                    send = YES;
                }
            
        
            if (send == YES)
                {
#ifdef OSX_DEBUG
                    fprintf(stderr, "DEBUG: sending char to TI\n");
#endif
        
                    ret = [myTransfersController sendChar:toSend];

                    if (ret < 0)
                        {
                            [self insertStatusText:@"*** Communication Error. Aborted. ***\n"];
                    
                            process = NO;
                    
                            return;
                        }
                }
          }
    
    if (process == YES)
        {
#ifdef OSX_DEBUG
            fprintf(stderr, "DEBUG: processing event\n");
#endif        
            [super keyDown:event];
        }
    
    [event release];
    [eventChars release];
}

@end
