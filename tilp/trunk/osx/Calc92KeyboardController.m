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

#include <stdint.h>

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#include "keys92.h"


unsigned char sknKey92[] = 
{
  TIKEY92_GRAB,
  TIKEY92_F1,TIKEY92_F2,TIKEY92_F3,TIKEY92_F4,TIKEY92_F5,TIKEY92_F6,TIKEY92_F7,TIKEY92_F8,
  TIKEY92_Q,TIKEY92_W,TIKEY92_E,TIKEY92_R,TIKEY92_T,TIKEY92_Y,TIKEY92_U,TIKEY92_I,TIKEY92_O,
  TIKEY92_P,
  TIKEY92_A,TIKEY92_S,TIKEY92_D,TIKEY92_F,TIKEY92_G,TIKEY92_H,TIKEY92_J,TIKEY92_K,TIKEY92_L,
  TIKEY92_Z,TIKEY92_X,TIKEY92_C,TIKEY92_V,TIKEY92_B,TIKEY92_N,TIKEY92_M,TIKEY92_THETA,
  TIKEY92_SHIFT,TIKEY92_ON,TIKEY92_DIAMOND,TIKEY92_2ND,TIKEY92_STORE,TIKEY92_SPACE,
  TIKEY92_EQUALS,
  TIKEY92_BACKSPACE,TIKEY92_ENTER1,TIKEY92_2ND,TIKEY92_ESCAPE,TIKEY92_MODE,TIKEY92_CLEAR,
  TIKEY92_LN,
  TIKEY92_APPS,TIKEY92_ENTER2,TIKEY92_LEFT,TIKEY92_RIGHT,TIKEY92_UP,TIKEY92_DOWN,
  TIKEY92_SIN,TIKEY92_COS,TIKEY92_TAN,TIKEY92_POWER,TIKEY92_PALEFT,TIKEY92_PARIGHT,
  TIKEY92_COMMA,
  TIKEY92_DIVIDE,TIKEY92_7,TIKEY92_8,TIKEY92_9,TIKEY92_MULTIPLY,TIKEY92_4,TIKEY92_5,TIKEY92_6,
  TIKEY92_MINUS,
  TIKEY92_1,TIKEY92_2,TIKEY92_3,TIKEY92_PLUS,TIKEY92_0,TIKEY92_DOT,TIKEY92_NEGATE,TIKEY92_ENTER1
};


#import "Calc92KeyboardController.h"
#import "TransfersController.h"
#import "RCTextView.h"


#define K_MODE_NONE 			0
#define K_MODE_SECOND 			1
#define K_MODE_DIAMOND 			2
#define K_MODE_SHIFT 			3
#define K_MODE_GRAB			4

// in main.m
uint32_t swap_bytes(uint32_t a);

@implementation Calc92KeyboardController

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
    fprintf(stderr, "Calc92KeyboardController => got awakeFromNib\n");
#endif

    objects_ptr->myCalc92KeyboardController = self;
}

- (id)init
{
    self = [super init];
    
    if (self == nil)
        return nil;

    mode = K_MODE_NONE;
    
    return self;
}


- (void)sendKey:(NSPoint)point
{
  int i;
  int ret;
  unsigned char key = 0;
  
  // we have a _little_ coordinates problem :)
  // our ImageView is 571 * 329
  point.y = 329 - point.y;
  
  for(i = 0; i < 80; i++)
      {
          if ((point.x >= rcKeys92[i].left) && (point.x < rcKeys92[i].right) && (point.y >= rcKeys92[i].top) && (point.y < rcKeys92[i].bottom))
              {
                  key = sknKey92[i];
              
                  break;
              }
      }

  switch(key)
      {
          case TIKEY92_GRAB:
              mode = K_MODE_GRAB;
              break;
          case TIKEY92_SHIFT:
              mode = K_MODE_SHIFT;
              break;
          case TIKEY92_2ND:
              mode = K_MODE_SECOND;
              break;
          case TIKEY92_DIAMOND:
              mode = K_MODE_DIAMOND;
              break;
          default:
              switch(mode)
                  {
                      case K_MODE_GRAB:
                          key = TI92KEYS[key].grab;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_SECOND:
                          key = TI92KEYS[key].second;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_DIAMOND:
                          key = TI92KEYS[key].diamond;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_SHIFT:
                          key = TI92KEYS[key].shift;
                          
                          mode = K_MODE_NONE;
                          break;
                      default:
                          key = TI92KEYS[key].none;
                          break;
                  }
          
              if (key > 0)
                  {
                      ret = [myTransfersController sendChar:key];

                      if (ret < 0)
                          {
                              [textArea insertStatusText:@"*** Communication Error. Aborted. ***\n"];
                          }
                  }                  
              break;
      }
}

- (void)showKeyboard92:(id)sender
{
    NSImage *skinImage;
    NSData *skinData;
    NSData *jpegData;
    NSRange jpegRange;
    
    NSSize scrollSize;
    
    int i;

    if ([keyboardWindow isVisible])
        {
            [keyboardWindow orderFront:self];
            
            return;
        }

    skinData = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ti92" ofType:@"skn"]];

    // Load key coordinates here

    memcpy(&rcKeys92, [skinData bytes] + (88 + sizeof(RECT_)), 80 * sizeof(RECT_));
    
    for (i = 0; i < 80; i++)
        {
            rcKeys92[i].top = swap_bytes(rcKeys92[i].top) >> 1;
            rcKeys92[i].bottom = swap_bytes(rcKeys92[i].bottom) >> 1;
            rcKeys92[i].left = swap_bytes(rcKeys92[i].left) >> 1;
            rcKeys92[i].right = swap_bytes(rcKeys92[i].right) >> 1;
        }

    // JPEG data begins at 88 + (1 + 80) * sizeof(RECT_) (VTi v2.1)
    // there's something strange with NSData and range handling, thus the second argument...
    jpegRange = NSMakeRange(88 + 81 * sizeof(RECT_), [skinData length] - (88 + 81 * sizeof(RECT_)));
    
    jpegData = [skinData subdataWithRange:jpegRange];
    
    skinImage = [[NSImage alloc] initWithData:jpegData];
    
    if (skinImage == nil)
      fprintf(stderr, "DEBUG: skinImage is nil, invalid data\n");

    [skinView setImage:skinImage];
    
    // change the textView for an RCTextView

    scrollSize = [scrollView contentSize];
    
    textArea = [[RCTextView alloc] initWithFrame:NSMakeRect(0, 0, scrollSize.width, scrollSize.height)
                                   textContainer:[[scrollView documentView] textContainer]];
    
    [textArea setMinSize:NSMakeSize(0.0, scrollSize.height)];
    [textArea setMaxSize:NSMakeSize(1e7, 1e7)];
    [textArea setVerticallyResizable:YES];
    [textArea setHorizontallyResizable:NO];
    [textArea setAutoresizingMask:NSViewWidthSizable];
    
    [scrollView setDocumentView:textArea];
    
    [textArea setEditable:YES]; 
       
    [textArea insertStatusText:@"Insert your text below.\nBeware, not all the keys are mapped.\n\n"];
    
    // finally show the window and add an entry to the Windows menu
    [keyboardWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:keyboardWindow title:@"TI-92/TI-92+ Remote Control" filename:NO];
}


- (IBAction)clearText:(id)sender
{
    [textArea setString:@""];
}

@end
