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

#import "Calc89KeyboardController.h"

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

@implementation Calc89KeyboardController

- (void)awakeFromNib
{
    mode = K_MODE_NONE;
}

- (IBAction)key89Function:(id)sender
{

    if (sender == Key89Alpha)
        {

        }
    else if (sender == Key89Applications)
        {

        }
    else if (sender == Key89Backspace)
        {

        }
    else if (sender == Key89Catalog)
        {

        }
    else if (sender == Key89Clear)
        {

        }
    else if (sender == Key89Up)
        {

        }
    else if (sender == Key89Diamond)
        {

        }
    else if (sender == Key89Down)
        {

        }
    else if (sender == Key89Enter)
        {

        }
    else if (sender == Key89Escape)
        {

        }
    else if (sender == Key89F1)
        {

        }
    else if (sender == Key89F2)
        {

        }
    else if (sender == Key89F3)
        {

        }
    else if (sender == Key89F4)
        {

        }
    else if (sender == Key89F5)
        {

        }
    else if (sender == Key89Home)
        {

        }
    else if (sender == Key89Left)
        {

        }
    else if (sender == Key89Mode)
        {

        }
    else if (sender == Key89Right)
        {

        }
    else if (sender == Key89Shift)
        {

        }
    else if (sender == Key89Second)
        {

        }
    else if (sender == Key89On)
        {

        }
}

- (IBAction)key89Regular:(id)sender
{

    if (sender == Key89Comma)
        {

        }
    else if (sender == Key89Divide)
        {

        }
    else if (sender == Key89Dot)
        {

        }
    else if (sender == Key89Eight)
        {

        }
    else if (sender == Key89Equal)
        {

        }
    else if (sender == Key89Five)
        {

        }
    else if (sender == Key89Four)
        {

        }
    else if (sender == Key89LeftParent)
        {

        }
    else if (sender == Key89Minus)
        {

        }
    else if (sender == Key89Multiply)
        {

        }
    else if (sender == Key89Nine)
        {

        }
    else if (sender == Key89NumericMinus)
        {

        }
    else if (sender == Key89One)
        {

        }
    else if (sender == Key89Pipe)
        {

        }
    else if (sender == Key89Plus)
        {

        }
    else if (sender == Key89Power)
        {

        }
    else if (sender == Key89PowerTen)
        {

        }
    else if (sender == Key89RightParent)
        {

        }
    else if (sender == Key89Seven)
        {

        }
    else if (sender == Key89Six)
        {

        }
    else if (sender == Key89Store)
        {

        }
    else if (sender == Key89T)
        {

        }
    else if (sender == Key89Three)
        {

        }
    else if (sender == Key89Two)
        {

        }
    else if (sender == Key89X)
        {

        }
    else if (sender == Key89Y)
        {

        }
    else if (sender == Key89Z)
        {

        }
    else if (sender == Key89Zero)
        {

      }
}

- (void)showKeyboard89:(id)sender
{
    [keyboardWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:keyboardWindow title:@"TI89 Keyboard" filename:NO];
}

@end
