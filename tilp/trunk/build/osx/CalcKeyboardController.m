/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2002-2003 Julien BLACHE <jb@tilp.info>
 *
 *  $Id$
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

#import "CalcKeyboardController.h"
#import "TransfersController.h"
#import "RCTextView.h"
#import "SkinController.h"

#include <stdint.h>

#include <libticalcs/calc_int.h>
#include <libticalcs/calc_def.h>

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#include "keys89.h"
#include "keys92.h"

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


unsigned short sknKey92[] =
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


#define K_MODE_NONE 			0
#define K_MODE_SECOND 			1
#define K_MODE_DIAMOND 			2
#define K_MODE_SHIFT 			3
#define K_MODE_ALPHA 			4
#define K_MODE_A_LOCK 			5
#define K_MODE_A_S_LOCK 		6
#define K_MODE_GREEK			7
#define K_MODE_GREEK_CAPS		8
#define K_MODE_GRAB                     9


@implementation CalcKeyboardController

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
  fprintf(stderr, "CalcKeyboardController => got awakeFromNib\n");
#endif

  objects_ptr->myCalcKeyboardController = self;
}

- (id)init
{
  self = [super init];

  if (self == nil)
    return nil;

  mode = K_MODE_NONE;

  scrollView = nil;
  textArea = nil;
  
  return self;
}

- (void)skinViewResizes
{
  //return;
  
  viewFrame = [skinView frame];

  xRatio = viewFrame.size.width / skinSize.width;
  yRatio = viewFrame.size.height / skinSize.height;
  
  [scrollView setFrame:NSMakeRect((float)(lcd.left * xRatio),
                                  (float)((skinSize.height - lcd.bottom) * yRatio),
                                  (float)((lcd.right - lcd.left) * xRatio),
                                  (float)((lcd.bottom - lcd.top) * yRatio))];
  
  [scrollView setNeedsDisplay:YES];
}


- (void)loadKeyboard
{
  NSSize scrollSize;

  if ([keyboardWindow isVisible])
  {
    [keyboardWindow orderFront:self];

    return;
  }

  
  if (ticalc_return_calc() == CALC_TI89)
  {
    [mySkinController loadSkin:[[NSBundle mainBundle] pathForResource:@"ti89" ofType:@"skn"]
                      skinSize:&skinSize
                      lcd:&lcd
                      keys:keys];
  }
  else
  {
    [mySkinController loadSkin:[[NSBundle mainBundle] pathForResource:@"ti92" ofType:@"skn"]
                      skinSize:&skinSize
                      lcd:&lcd
                      keys:keys];
  }

  viewFrame = [skinView frame];

  xRatio = viewFrame.size.width / skinSize.width;
  yRatio = viewFrame.size.height / skinSize.height;

  if (scrollView != nil)
    [scrollView release];
  
  scrollView = [[NSScrollView alloc] initWithFrame:NSMakeRect((float)(lcd.left * xRatio),
                                                              (float)((skinSize.height - lcd.bottom) * yRatio),
                                                              (float)((lcd.right - lcd.left) * xRatio),
                                                              (float)((lcd.bottom - lcd.top) * yRatio))];

  scrollSize = [scrollView contentSize];

  [scrollView setBorderType:NSBezelBorder];
  [scrollView setHasVerticalScroller:YES];
  [scrollView setHasHorizontalScroller:NO];
  [scrollView setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];

  if (textArea != nil)
    [textArea release];

  textArea = [[RCTextView alloc] initWithFrame:NSMakeRect(0, 0,
                                                          scrollSize.width, scrollSize.height)];

  [textArea setMinSize:NSMakeSize(0.0, scrollSize.height)];
  [textArea setMaxSize:NSMakeSize(1e7, 1e7)];
  [textArea setVerticallyResizable:YES];
  [textArea setHorizontallyResizable:NO];
  [textArea setAutoresizingMask:NSViewWidthSizable];

  [[textArea textContainer] setWidthTracksTextView:YES];

  [scrollView setDocumentView:textArea];
  [skinView addSubview:scrollView];
  [keyboardWindow makeFirstResponder:textArea];
  
  [textArea setString:@""];
  [textArea insertStatusText:@"Insert your text below.\nBeware, not all the keys are mapped.\n"];
  [textArea insertText:@"\n"];
  
  if (ticalc_return_calc() == CALC_TI89)
    [keyboardWindow setTitle:@"TI-89 Remote Control"];
  else
    [keyboardWindow setTitle:@"TI-92 Remote Control"];
  
  // finally show the window
  [keyboardWindow makeKeyAndOrderFront:self];
}


// TI 89 specific

- (void)sendKey89:(NSPoint)point
{
  int i;
  int ret;
  unsigned int key = 0;

  // we have a _little_ coordinates problem :)
  point.y = viewFrame.size.height - point.y;

  point.x = point.x / xRatio;
  point.y = point.y / yRatio;
  
  for(i = 0; i < 80; i++)
  {
    if ((point.x >= keys[i].left) && (point.x < keys[i].right) && (point.y >= keys[i].top) && (point.y < keys[i].bottom))
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
          [textArea insertStatusText:@"\n*** Communication Error. Aborted. ***\n"];
        }
      }
      break;
  }
}


// TI 92 specific
- (void)sendKey92:(NSPoint)point
{
  int i;
  int ret;
  unsigned int key = 0;

  // we have a _little_ coordinates problem :)
  point.y = viewFrame.size.height - point.y;

  point.x = point.x / xRatio;
  point.y = point.y / yRatio;
  
  for(i = 0; i < 80; i++)
  {
    if ((point.x >= keys[i].left) && (point.x < keys[i].right) && (point.y >= keys[i].top) && (point.y < keys[i].bottom))
    {
      key = sknKey92[i];
#ifdef OSX_DEBUG
      fprintf(stderr, "DEBUG: matched key %d\n", key);
#endif
      break;
    }
  }

  switch(key)
  {
    case TIKEY92_GRAB:
      mode = K_MODE_GRAB;
      break;
    case TIKEY92_SHIFT:
      if (mode != K_MODE_GREEK)
        mode = K_MODE_SHIFT;
      else
        mode = K_MODE_GREEK_CAPS;
      break;
    case TIKEY92_2ND:
      mode = K_MODE_SECOND;
      break;
    case TIKEY92_DIAMOND:
      mode = K_MODE_DIAMOND;
      break;
    case TIKEY92_G:
      if (mode == K_MODE_SECOND)
      {
        mode = K_MODE_GREEK;

        break;
      }
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
        case K_MODE_GREEK:
          switch(key)
          {
            case TIKEY92_A:
              key = 128;
              break;
            case TIKEY92_B:
              key = 129;
              break;
            case TIKEY92_D:
              key = 133;
              break;
            case TIKEY92_E:
              key = 134;
              break;
            case TIKEY92_F:
              key = 145;
              break;
            case TIKEY92_G:
              key = 131;
              break;
            case TIKEY92_L:
              key = 137;
              break;
            case TIKEY92_M:
              key = 181;
              break;
            case TIKEY92_P:
              key = 140;
              break;
            case TIKEY92_R:
              key = 141;
              break;
            case TIKEY92_S:
              key = 143;
              break;
            case TIKEY92_T:
              key = 144;
              break;
            case TIKEY92_W:
              key = 148;
              break;
            case TIKEY92_X:
              key = 138;
              break;
            case TIKEY92_Y:
              key = 146;
              break;
            case TIKEY92_Z:
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
            case TIKEY92_D:
              key = 132;
              break;
            case TIKEY92_G:
              key = 130;
              break;
            case TIKEY92_P:
              key = 139;
              break;
            case TIKEY92_S:
              key = 142;
              break;
            case TIKEY92_W:
              key = 147;
              break;
            default:
              key = 0;
              break;
          }

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
          [textArea insertStatusText:@"\n*** Communication Error. Aborted. ***\n"];
        }
      }
      break;
  }
}

@end
