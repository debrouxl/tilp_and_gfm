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

@interface Calc92KeyboardController : NSObject
{
    IBOutlet id Key92A;
    IBOutlet id Key92Applications;
    IBOutlet id Key92B;
    IBOutlet id Key92Backspace;
    IBOutlet id Key92C;
    IBOutlet id Key92Clear;
    IBOutlet id Key92Comma;
    IBOutlet id Key92Cos;
    IBOutlet id Key92D;
    IBOutlet id Key92Diamond;
    IBOutlet id Key92Divide;
    IBOutlet id Key92Dot;
    IBOutlet id Key92Down;
    IBOutlet id Key92E;
    IBOutlet id Key92Eight;
    IBOutlet id Key92Enter1;
    IBOutlet id Key92Enter2;
    IBOutlet id Key92Enter3;
    IBOutlet id Key92Equal;
    IBOutlet id Key92Escape;
    IBOutlet id Key92F;
    IBOutlet id Key92F1;
    IBOutlet id Key92F2;
    IBOutlet id Key92F3;
    IBOutlet id Key92F4;
    IBOutlet id Key92F5;
    IBOutlet id Key92F6;
    IBOutlet id Key92F7;
    IBOutlet id Key92F8;
    IBOutlet id Key92Five;
    IBOutlet id Key92Four;
    IBOutlet id Key92G;
    IBOutlet id Key92H;
    IBOutlet id Key92Hand;
    IBOutlet id Key92I;
    IBOutlet id Key92J;
    IBOutlet id Key92K;
    IBOutlet id Key92L;
    IBOutlet id Key92Left;
    IBOutlet id Key92LeftParent;
    IBOutlet id Key92Ln;
    IBOutlet id Key92M;
    IBOutlet id Key92Minus;
    IBOutlet id Key92Mode;
    IBOutlet id Key92Multiply;
    IBOutlet id Key92N;
    IBOutlet id Key92Nine;
    IBOutlet id Key92NumericMinus;
    IBOutlet id Key92O;
    IBOutlet id Key92On;
    IBOutlet id Key92One;
    IBOutlet id Key92P;
    IBOutlet id Key92Plus;
    IBOutlet id Key92Power;
    IBOutlet id Key92Q;
    IBOutlet id Key92R;
    IBOutlet id Key92Right;
    IBOutlet id Key92RightParent;
    IBOutlet id Key92S;
    IBOutlet id Key92Second1;
    IBOutlet id Key92Second2;
    IBOutlet id Key92Seven;
    IBOutlet id Key92Shift;
    IBOutlet id Key92Sin;
    IBOutlet id Key92Six;
    IBOutlet id Key92Space;
    IBOutlet id Key92Store;
    IBOutlet id Key92T;
    IBOutlet id Key92Tan;
    IBOutlet id Key92Theta;
    IBOutlet id Key92Three;
    IBOutlet id Key92Two;
    IBOutlet id Key92U;
    IBOutlet id Key92Up;
    IBOutlet id Key92V;
    IBOutlet id Key92W;
    IBOutlet id Key92X;
    IBOutlet id Key92Y;
    IBOutlet id Key92Z;
    IBOutlet id Key92Zero;
    
    IBOutlet id keyboardWindow;
    
    int mode;
}

- (IBAction)key92Alpha:(id)sender;
- (IBAction)key92Function:(id)sender;
- (IBAction)key92Regular:(id)sender;

- (void)showKeyboard92:(id)sender;

@end
