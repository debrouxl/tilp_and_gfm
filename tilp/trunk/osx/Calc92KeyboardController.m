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
extern const struct ti_key TI92_KEYS[];

#import "Calc92KeyboardController.h"
#import "TransfersController.h"

#define K_MODE_NONE 			0
#define K_MODE_SECOND 			1
#define K_MODE_DIAMOND 			2
#define K_MODE_SHIFT 			3
#define K_MODE_ALPHA 			4
#define K_MODE_A_LOCK 			5
#define K_MODE_A_S_LOCK 		6

#define K_MODE_SECOND_WAS_A_LOCK	11
#define K_MODE_SECOND_WAS_A_S_LOCK	21

#define K_MODE_DIAMOND_WAS_A_LOCK	12
#define K_MODE_DIAMOND_WAS_A_S_LOCK	22

@implementation Calc92KeyboardController

- (id)init
{
    self = [super init];
    
    if (self == nil)
        return nil;

    mode = K_MODE_NONE;
    
    return self;
}

- (IBAction)key92Alpha:(id)sender
{

    if (sender == Key92A)
        {

        }
    else if (sender == Key92B)
        {

        }
    else if (sender == Key92C)
        {

        }
    else if (sender == Key92D)
        {

        }
    else if (sender == Key92E)
        {

        }
    else if (sender == Key92F)
        {

        }
    else if (sender == Key92G)
        {

        }
    else if (sender == Key92H)
        {

        }
    else if (sender == Key92I)
        {

        }
    else if (sender == Key92J)
        {

        }
    else if (sender == Key92K)
        {

        }
    else if (sender == Key92L)
        {

        }
    else if (sender == Key92M)
        {

        }
    else if (sender == Key92N)
        {

        }
    else if (sender == Key92O)
        {

        }
    else if (sender == Key92P)
        {

        }
    else if (sender == Key92Q)
        {

        }
    else if (sender == Key92R)
        {

        }
    else if (sender == Key92S)
        {

        }
    else if (sender == Key92T)
        {

        }
    else if (sender == Key92U)
        {

        }
    else if (sender == Key92V)
        {

        }
    else if (sender == Key92W)
        {

        }
    else if (sender == Key92X)
        {

        }
    else if (sender == Key92Y)
        {

        }
    else if (sender == Key92Z)
        {

        }
}

- (IBAction)key92Function:(id)sender
{

    if (sender == Key92Applications)
        {

        }
    else if (sender == Key92Backspace)
        {

        }
    else if (sender == Key92Clear)
        {

        }
    else if (sender == Key92Diamond)
        {
        
        }
    else if (sender == Key92Down)
        {

        }
    else if (sender == Key92Enter1)
        {

        }
    else if (sender == Key92Enter2)
        {

        }
    else if (sender == Key92Enter3)
        {

        }
    else if (sender == Key92Escape)
        {

        }
    else if (sender == Key92F1)
        {

        }
    else if (sender == Key92F2)
        {

        }
    else if (sender == Key92F3)
        {

        }
    else if (sender == Key92F4)
        {

        }
    else if (sender == Key92F5)
        {

        }
    else if (sender == Key92F6)
        {

        }
    else if (sender == Key92F7)
        {

        }
    else if (sender == Key92F8)
        {

        }
    else if (sender == Key92Hand)
        {

        }
    else if (sender == Key92Left)
        {

        }
    else if (sender == Key92Mode)
        {

        }
    else if (sender == Key92On)
        {

        }
    else if (sender == Key92Right)
        {

        }
    else if (sender == Key92Second1)
        {

        }
    else if (sender == Key92Second2)
        {

        }
    else if (sender == Key92Shift)
        {

        }
    else if (sender == Key92Up)
        {

      }
}

- (IBAction)key92Regular:(id)sender
{

    if (sender == Key92Comma)
        {

        }
    else if (sender == Key92Cos)
        {

        }
    else if (sender == Key92Divide)
        {

        }
    else if (sender == Key92Dot)
        {

        }
    else if (sender == Key92Eight)
        {

        }
    else if (sender == Key92Equal)
        {

        }
    else if (sender == Key92Five)
        {	

        }
    else if (sender == Key92Four)
        {

        }
    else if (sender == Key92LeftParent)
        {

        }
    else if (sender == Key92Ln)
        {

        }
    else if (sender == Key92Minus)
        {

        }
    else if (sender == Key92Multiply)
        {

        }
    else if (sender == Key92Nine)
        {

        }
    else if (sender == Key92NumericMinus)
        {

        }
    else if (sender == Key92One)
        {

        }
    else if (sender == Key92Plus)
        {

        }
    else if (sender == Key92Power)
        {

        }
    else if (sender == Key92RightParent)
        {

        }
    else if (sender == Key92Seven)
        {

        }
    else if (sender == Key92Sin)
        {

        }
    else if (sender == Key92Six)
        {

        }
    else if (sender == Key92Space)
        {

        }
    else if (sender == Key92Store)
        {

        }
    else if (sender == Key92Tan)
        {

        }
    else if (sender == Key92Theta)
        {

        }
    else if (sender == Key92Three)
        {

        }
    else if (sender == Key92Two)
        {

        }
    else if (sender == Key92Zero)
        {

        }
}

- (void)showKeyboard92:(id)sender
{
    [keyboardWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:keyboardWindow title:@"TI92/TI92+ Keyboard" filename:NO];
}

@end
