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


#include <libticalcs/calc_int.h>
#include <libticalcs/calc_def.h>

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "CalcKeyboardController.h"

#import "TiKeyboardView.h"

@implementation TiKeyboardView

- (void)drawRect:(NSRect)rect
{
  [super drawRect:rect];

  [myCalcKeyboardController skinViewResizes];
}


- (void)mouseDown:(NSEvent *)event
{
  NSPoint mouseClick;

#ifdef OSX_DEBUG
  fprintf(stderr, "DEBUG: mouseDown event on Imageview\n");
#endif

  if ([event type] == NSLeftMouseDown)
      {
          mouseClick = [self convertPoint:[event locationInWindow] fromView:nil];
#ifdef OSX_DEBUG
          fprintf(stderr, "Coordinates : x %f, y %f\n", mouseClick.x, mouseClick.y);
#endif
          if ([self mouse:mouseClick inRect:[self bounds]])
              {
                  if (ticalc_get_calc2() == CALC_TI89)
                      {
                          [myCalcKeyboardController sendKey89:mouseClick];
                      }
                  else
                      {
                          [myCalcKeyboardController sendKey92:mouseClick];
                      }
              }
      }
}

@end
