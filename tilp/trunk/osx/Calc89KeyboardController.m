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

#include <libticables/typedefs.h>

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#include "keys89.h"

unsigned short sknKey89[] =
{
  TIKEY89_F1, TIKEY89_F2, TIKEY89_F3, TIKEY89_F4, TIKEY89_F5,
  TIKEY89_2ND, TIKEY89_SHIFT, TIKEY89_ESCAPE, TIKEY89_LEFT, TIKEY89_RIGHT,
  TIKEY89_UP, TIKEY89_DOWN, TIKEY89_DIAMOND, TIKEY89_ALPHA, TIKEY89_APPS,
  TIKEY89_HOME, TIKEY89_MODE, TIKEY89_CATALOG, TIKEY89_BACKSPACE, TIKEY89_CLEAR,
  TIKEY89_X, TIKEY89_Y, TIKEY89_Z, TIKEY89_T, TIKEY89_POWER,
  TIKEY89_EQUALS, TIKEY89_PALEFT, TIKEY89_PARIGHT, TIKEY89_COMMA, TIKEY89_DIVIDE,
  TIKEY89_PIPE, TIKEY89_7, TIKEY89_8, TIKEY89_9, TIKEY89_MULTIPLY,
  TIKEY89_EE, TIKEY89_4, TIKEY89_5, TIKEY89_6, TIKEY89_MINUS,
  TIKEY89_STORE, TIKEY89_1, TIKEY89_2, TIKEY89_3, TIKEY89_PLUS,
  TIKEY89_ON, TIKEY89_0, TIKEY89_PERIOD, TIKEY89_NEGATE, TIKEY89_ENTER1
};


#import "Calc89KeyboardController.h"
#import "TransfersController.h"
#import "RCTextView.h"

// in main.m
uint32_t swap_bytes(uint32_t a);

#define K_MODE_NONE 			0
#define K_MODE_SECOND 			1
#define K_MODE_DIAMOND 			2
#define K_MODE_SHIFT 			3
#define K_MODE_ALPHA 			4
#define K_MODE_A_LOCK 			5
#define K_MODE_A_S_LOCK 		6
#define K_MODE_GREEK			7
#define K_MODE_GREEK_CAPS		8

@implementation Calc89KeyboardController

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
    fprintf(stderr, "Calc89KeyboardController => got awakeFromNib\n");
#endif

    objects_ptr->myCalc89KeyboardController = self;
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
  word key = 0;
  
  // we have a _little_ coordinates problem :)
  // our ImageView is 222 * 503
  point.y = 503 - point.y;
  
  for(i = 0; i < 80; i++)
      {
          if ((point.x >= rcKeys89[i].left) && (point.x < rcKeys89[i].right) && (point.y >= rcKeys89[i].top) && (point.y < rcKeys89[i].bottom))
              {
                  key = sknKey89[i];
#ifdef OSX_DEBUG
                  fprintf(stderr, "DEBUG: matched key %d\n", key);
#endif
                  break;
              }
      }

  switch(key)
      {
          case TIKEY89_SHIFT:
              if (mode != K_MODE_GREEK)
                  mode = K_MODE_SHIFT;
              else
                  mode = K_MODE_GREEK_CAPS;
              break;
          case TIKEY89_2ND:
              mode = K_MODE_SECOND;
              break;
          case TIKEY89_DIAMOND:
              mode = K_MODE_DIAMOND;
              break;
          case TIKEY89_ALPHA:
              if ((mode == K_MODE_SECOND) || (mode == K_MODE_ALPHA))
                  mode = K_MODE_A_LOCK;
              else if ((mode == K_MODE_ALPHA) || (mode == K_MODE_A_LOCK) || (mode == K_MODE_A_S_LOCK))
                  mode = K_MODE_NONE;
              else if (mode == K_MODE_SHIFT)
                  mode = K_MODE_A_S_LOCK;
              else if (mode != K_MODE_GREEK)
                  mode = K_MODE_ALPHA;
              break;
          case TIKEY89_PALEFT:
              if (mode == K_MODE_DIAMOND)
                  {
                      mode = K_MODE_GREEK;
                      break;
                  }
          default:
              switch(mode)
                  {
                      case K_MODE_ALPHA:
                          key = TI89KEYS[key].alpha;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_SECOND:
                          key = TI89KEYS[key].second;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_DIAMOND:
                          key = TI89KEYS[key].diamond;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_SHIFT:
                          key = TI89KEYS[key].shift;
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_A_LOCK:
                          key = TI89KEYS[key].alpha;
                          break;
                      case K_MODE_A_S_LOCK:
                          key = TI89KEYS[key].shift;
                          break;
                      case K_MODE_GREEK:
                          switch(key)
                              {
                                  case TIKEY89_EQUALS:
                                      key = 128;
                                      break;
                                  case TIKEY89_PALEFT:
                                      key = 129;
                                      break;
                                  case TIKEY89_COMMA:
                                      key = 133;
                                      break;
                                  case TIKEY89_DIVIDE:
                                      key = 134;
                                      break;
                                  case TIKEY89_PIPE:
                                      key = 145;
                                      break;
                                  case TIKEY89_7:
                                      key = 131;
                                      break;
                                  case TIKEY89_4:
                                      key = 137;
                                      break;
                                  case TIKEY89_5:
                                      key = 181;
                                      break;
                                  case TIKEY89_STORE:
                                      key = 140;
                                      break;
                                  case TIKEY89_2:
                                      key = 141;
                                      break;
                                  case TIKEY89_3:
                                      key = 143;
                                      break;
                                  case TIKEY89_T:
                                      key = 144;
                                      break;
                                  case TIKEY89_PERIOD:
                                      key = 148;
                                      break;
                                  case TIKEY89_X:
                                      key = 138;
                                      break;
                                  case TIKEY89_Y:
                                      key = 146;
                                      break;
                                  case TIKEY89_Z:
                                      key = 135;
                                      break;
                                  default:
                                      key = 0;
                                      break;
                              }
                          
                          mode = K_MODE_NONE;
                          break;
                      case K_MODE_GREEK_CAPS:
                          switch(key)
                              {
                                  case TIKEY89_COMMA:
                                      key = 132;
                                      break;
                                  case TIKEY89_7:
                                      key = 130;
                                      break;
                                  case TIKEY89_STORE:
                                      key = 139;
                                      break;
                                  case TIKEY89_3:
                                      key = 142;
                                      break;
                                  case TIKEY89_PERIOD:
                                      key = 147;
                                      break;
                                  default:
                                      key = 0;
                                      break;
                              }
                          
                          mode = K_MODE_NONE;
                          break;
                      default:
                          key = TI89KEYS[key].none;
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

- (void)showKeyboard89:(id)sender
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

    skinData = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ti89" ofType:@"skn"]];

    // Load key coordinates here
    
    memcpy(&rcKeys89, [skinData bytes] + (152 + sizeof(RECT_)), 80 * sizeof(RECT_));
    
    for (i = 0; i < 80; i++)
        {
            rcKeys89[i].top = swap_bytes(rcKeys89[i].top) >> 1;
            rcKeys89[i].bottom = swap_bytes(rcKeys89[i].bottom) >> 1;
            rcKeys89[i].left = swap_bytes(rcKeys89[i].left) >> 1;
            rcKeys89[i].right = swap_bytes(rcKeys89[i].right) >> 1;
        }

    // JPEG data begins at 152 + (1 + 80) * sizeof(RECT_)  (VTi v2.5)
    // there's something strange with NSData and range handling, thus the second argument...
    jpegRange = NSMakeRange(152 + 81 * sizeof(RECT_), [skinData length] - (152 + 81 * sizeof(RECT_)));
    
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
    
    [textArea setString:@""];
    [textArea insertStatusText:@"Insert your text below.\nBeware, not all the keys are mapped.\n\n"];
    
    // finally show the window and add an entry to the Windows menu
    [keyboardWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:keyboardWindow title:@"TI-89 Remote Control" filename:NO];
}

- (IBAction)clearText:(id)sender
{
    [textArea setString:@""];
}

@end
