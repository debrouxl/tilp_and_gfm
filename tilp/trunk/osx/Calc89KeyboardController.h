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

#import <Cocoa/Cocoa.h>

@interface Calc89KeyboardController : NSObject
{
    IBOutlet id Key89Alpha;
    IBOutlet id Key89Applications;
    IBOutlet id Key89Backspace;
    IBOutlet id Key89Catalog;
    IBOutlet id Key89Clear;
    IBOutlet id Key89Comma;
    IBOutlet id Key89Diamond;
    IBOutlet id Key89Divide;
    IBOutlet id Key89Dot;
    IBOutlet id Key89Down;
    IBOutlet id Key89Eight;
    IBOutlet id Key89Enter;
    IBOutlet id Key89Equal;
    IBOutlet id Key89Escape;
    IBOutlet id Key89F1;
    IBOutlet id Key89F2;
    IBOutlet id Key89F3;
    IBOutlet id Key89F4;
    IBOutlet id Key89F5;
    IBOutlet id Key89Five;
    IBOutlet id Key89Four;
    IBOutlet id Key89Home;
    IBOutlet id Key89Left;
    IBOutlet id Key89LeftParent;
    IBOutlet id Key89Minus;
    IBOutlet id Key89Mode;
    IBOutlet id Key89Multiply;
    IBOutlet id Key89Nine;
    IBOutlet id Key89NumericMinus;
    IBOutlet id Key89On;
    IBOutlet id Key89One;
    IBOutlet id Key89Pipe;
    IBOutlet id Key89Plus;
    IBOutlet id Key89Power;
    IBOutlet id Key89PowerTen;
    IBOutlet id Key89Right;
    IBOutlet id Key89RightParent;
    IBOutlet id Key89Second;
    IBOutlet id Key89Seven;
    IBOutlet id Key89Shift;
    IBOutlet id Key89Six;
    IBOutlet id Key89Store;
    IBOutlet id Key89T;
    IBOutlet id Key89Three;
    IBOutlet id Key89Two;
    IBOutlet id Key89Up;
    IBOutlet id Key89X;
    IBOutlet id Key89Y;
    IBOutlet id Key89Z;
    IBOutlet id Key89Zero;
    
    IBOutlet id keyboardWindow;
    
    IBOutlet id myTransfersController;
    
    int mode;
}

- (IBAction)key89Function:(id)sender;
- (IBAction)key89Regular:(id)sender;

- (void)showKeyboard89:(id)sender;

@end
