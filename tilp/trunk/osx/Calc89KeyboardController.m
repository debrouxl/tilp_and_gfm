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

#include <libticalcs/calc_def.h>

// built in libticalcs
extern const struct ti_key TI89_KEYS[];

#import "Calc89KeyboardController.h"
#import "TransfersController.h"

#define K_MODE_NONE 			0
#define K_MODE_SECOND 			1
#define K_MODE_DIAMOND 			2
#define K_MODE_SHIFT 			3
#define K_MODE_ALPHA 			4
#define K_MODE_A_LOCK 			5
#define K_MODE_A_S_LOCK 		6

@implementation Calc89KeyboardController

- (id)init
{
    self = [super init];
    
    if (self == nil)
        return nil;

    mode = K_MODE_NONE;
    
    return self;
}

- (IBAction)key89Function:(id)sender
{
    unsigned int toSend = 0;

    if (sender == Key89Alpha)
        {
            switch(mode)
                {
                    case K_MODE_SECOND:
                        mode = K_MODE_A_LOCK;
                        break;
                    case K_MODE_SHIFT:
                        mode = K_MODE_A_S_LOCK;
                        break;
                    case K_MODE_ALPHA:
                        mode = K_MODE_A_LOCK;
                        break;
                    case K_MODE_A_LOCK:
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_A_S_LOCK:
                        mode = K_MODE_NONE;
                        break;
                    default:
                        mode = K_MODE_ALPHA;
                        break;
                }
        }
    else if (sender == Key89Diamond)
        {
            switch(mode)
                {
                    case K_MODE_DIAMOND:
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_SHIFT:
                        mode = K_MODE_NONE;
                        break;
                    default:
                        mode = K_MODE_DIAMOND;
                        break;
                }
        }
    else if (sender == Key89Shift)
        {
            switch(mode)
                {
                    case K_MODE_DIAMOND:
                        [myTransfersController sendChar:24576];
                        mode = K_MODE_NONE;
                        return;
                    case K_MODE_SHIFT:
                        mode = K_MODE_NONE;
                        break;
                    default:
                        mode = K_MODE_SHIFT;
                        break;
                }
        }
    else if (sender == Key89Second)
        {
            switch(mode)
                {
                    case K_MODE_SECOND:
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_DIAMOND:
                        mode = K_MODE_NONE;
                        break;
                    default:
                        mode = K_MODE_SECOND;
                        break;
                }
        }


        
    if (sender == Key89Applications)
        {
            [myTransfersController sendChar:265];
        }
    else if (sender == Key89Backspace)
        {
            [myTransfersController sendChar:257];
        }
    else if (sender == Key89Catalog)
        {
            [myTransfersController sendChar:278];
        }
    else if (sender == Key89Clear)
        {
            [myTransfersController sendChar:263];
        }
    else if (sender == Key89Up)
        {
            [myTransfersController sendChar:337];
        }
    else if (sender == Key89Down)
        {
            [myTransfersController sendChar:340];
        }
    else if (sender == Key89Enter)
        {
            [myTransfersController sendChar:13];
        }
    else if (sender == Key89Escape)
        {
            [myTransfersController sendChar:264];
        }
    else if (sender == Key89F1)
        {
            [myTransfersController sendChar:268];
        }
    else if (sender == Key89F2)
        {
            [myTransfersController sendChar:269];
        }
    else if (sender == Key89F3)
        {
            [myTransfersController sendChar:270];
        }
    else if (sender == Key89F4)
        {
            [myTransfersController sendChar:271];
        }
    else if (sender == Key89F5)
        {
            [myTransfersController sendChar:272];
        }
    else if (sender == Key89Home)
        {
            [myTransfersController sendChar:277];
        }
    else if (sender == Key89Left)
        {
            [myTransfersController sendChar:338];
        }
    else if (sender == Key89Mode)
        {
            [myTransfersController sendChar:266];
        }
    else if (sender == Key89Right)
        {
            [myTransfersController sendChar:344];
        }
    else if (sender == Key89On)
        {
            // no code ?
        }
}

- (IBAction)key89Regular:(id)sender
{
    int toSend = 0;
    int baseKey = 0;

    if (sender == Key89Comma)
        {
            [myTransfersController sendChar:','];
        }
    else if (sender == Key89Divide)
        {
            [myTransfersController sendChar:'/'];
        }
    else if (sender == Key89Dot)
        {
            [myTransfersController sendChar:'.'];
        }
    else if (sender == Key89Eight)
        {
            baseKey = '8';
                    
            [myTransfersController sendChar:'8'];
        }
    else if (sender == Key89Equal)
        {
            [myTransfersController sendChar:'='];
        }
    else if (sender == Key89Five)
        {
            [myTransfersController sendChar:'5'];
        }
    else if (sender == Key89Four)
        {
            [myTransfersController sendChar:'4'];
        }
    else if (sender == Key89LeftParent)
        {
            [myTransfersController sendChar:'('];
        }
    else if (sender == Key89Minus)
        {
            [myTransfersController sendChar:'-'];
        }
    else if (sender == Key89Multiply)
        {
            [myTransfersController sendChar:'*'];
        }
    else if (sender == Key89Nine)
        {
            [myTransfersController sendChar:'9'];
        }
    else if (sender == Key89NumericMinus)
        {
            [myTransfersController sendChar:173];
        }
    else if (sender == Key89One)
        {
            [myTransfersController sendChar:'1'];
        }
    else if (sender == Key89Pipe)
        {
            [myTransfersController sendChar:'|'];
        }
    else if (sender == Key89Plus)
        {
            [myTransfersController sendChar:'+'];
        }
    else if (sender == Key89Power)
        {
            [myTransfersController sendChar:'^'];
        }
    else if (sender == Key89PowerTen)
        {
            [myTransfersController sendChar:149];
        }
    else if (sender == Key89RightParent)
        {
            [myTransfersController sendChar:')'];
        }
    else if (sender == Key89Seven)
        {
            [myTransfersController sendChar:'7'];
        }
    else if (sender == Key89Six)
        {
            [myTransfersController sendChar:'6'];
        }
    else if (sender == Key89Store)
        {
            [myTransfersController sendChar:258];
        }
    else if (sender == Key89T)
        {
            [myTransfersController sendChar:'t'];
        }
    else if (sender == Key89Three)
        {
            [myTransfersController sendChar:'3'];
        }
    else if (sender == Key89Two)
        {
            [myTransfersController sendChar:'2'];
        }
    else if (sender == Key89X)
        {
            [myTransfersController sendChar:'x'];
        }
    else if (sender == Key89Y)
        {
            [myTransfersController sendChar:'y'];
        }
    else if (sender == Key89Z)
        {
            [myTransfersController sendChar:'z'];
        }
    else if (sender == Key89Zero)
        {
            [myTransfersController sendChar:'0'];
        }
        
    if (baseKey > 0)
        {
            switch(mode)
                {
                    case K_MODE_SECOND:
                        toSend = TI89_KEYS[baseKey].second;
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_DIAMOND:
                        toSend = TI89_KEYS[baseKey].diamond;
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_SHIFT:
                        toSend = TI89_KEYS[baseKey].shift;
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_ALPHA:
                        toSend = TI89_KEYS[baseKey].alpha;
                        mode = K_MODE_NONE;
                        break;
                    case K_MODE_A_LOCK:
                        toSend = TI89_KEYS[baseKey].alpha;
                        break;
                    case K_MODE_A_S_LOCK:
                        toSend = TI89_KEYS[baseKey].shift;
                        break;
                    default:
                        toSend = TI89_KEYS[baseKey].nothing;
                        break;
                }
        }
    else
        return;
        
    fprintf(stderr, "DEBUG: => %c\n", toSend);
}

- (void)showKeyboard89:(id)sender
{
    [keyboardWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:keyboardWindow title:@"TI89 Keyboard" filename:NO];
}

@end
