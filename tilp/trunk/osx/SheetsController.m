/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Julien BLACHE <jb@tilp.info>
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

#include <libticables/cabl_def.h>

#include "cocoa_structs.h"

#include "../src/tilp_struct.h"
#include "../src/tilp_defs.h"
#include "../src/intl.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import <Cocoa/Cocoa.h>

#import "SheetsController.h"

@implementation SheetsController

// we could use NSbeep(); on some boxes (dlgboxEntry maybe ?)
// and also request the user attention (ie. the app's icon will jump on the screen)
// see requestUserAttention()

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
  fprintf(stderr, "sheets => got awakeFromNib\n");
#endif

  // Init instance pointer
  objects_ptr->mySheetsController = self;
}


- (void)showCurrentPBar
{
  if (pbarWindow != nil)
  {
    [NSApp beginSheet:pbarWindow
       modalForWindow:[myBoxesController keyWindow]
        modalDelegate:nil
       didEndSelector:nil
          contextInfo:nil];
    
    [NSApp endSheet:pbarWindow];
  }
}

- (void)hideCurrentPBar
{
  if (pbarWindow != nil)
  {
    [pbarWindow orderOut:self];
  }
}


- (void)msgSheet:(NSString *)title message:(NSString *)message
{
  [self hideCurrentPBar];

#ifdef TILP_USES_SHEETS
  NSBeginAlertSheet(title, nil, nil, nil, [myBoxesController keyWindow], nil, nil, nil, nil, message);
#else
  NSRunAlertPanel(title, message, @"OK", nil, nil);
#endif

  [self showCurrentPBar];
}

/* user boxes */

- (int)msg2Sheet:(NSString *)title message:(NSString *)message
{
#ifndef TILP_USES_SHEETS
    NSModalSession session;
#endif

    NSRect oldFrame, newFrame, windowFrame;

    objects_ptr->user2_return = 0;

    [self hideCurrentPBar];

    [user2Text setStringValue:message];


    // begin window resizing
    oldFrame = newFrame = [user2Text frame];
    windowFrame = [user2Window frame];

    newFrame.size.height = 10000.0;  // a large number
    newFrame.size = [[user2Text cell] cellSizeForBounds:newFrame];

    if (newFrame.size.height > oldFrame.size.height)
        windowFrame.size.height += (newFrame.size.height - oldFrame.size.height);
    else if (newFrame.size.height < oldFrame.size.height)
        windowFrame.size.height -= (oldFrame.size.height - newFrame.size.height);

    [user2Window setFrame:windowFrame display:NO];
    // end of window resizing

    [user2Button1 setTitle:@"OK"];
    [user2Button2 setTitle:@"Cancel"];

    [user2Window setExcludedFromWindowsMenu:YES];

#ifdef TILP_USES_SHEETS
    [NSApp beginSheet:user2Window
       modalForWindow:[myBoxesController keyWindow]
        modalDelegate:nil
       didEndSelector:nil
          contextInfo:nil];

    [NSApp runModalForWindow:user2Window];

    [NSApp endSheet:user2Window];
#else
    [user2Window setTitle:title];

    session = [NSApp beginModalSessionForWindow:user2Window];

    [user2Window makeKeyAndOrderFront:self];

    for (;;)
    {
        if([NSApp runModalSession:session] != NSRunContinuesResponse)
            break;
    }

    [NSApp endModalSession:session];
#endif

    [user2Window orderOut:self];

    [self showCurrentPBar];

    return objects_ptr->user2_return;
}

- (int)msg3Sheet:(NSString *)title message:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2 button3:(NSString *)button3
{
#ifndef TILP_USES_SHEETS
    NSModalSession session;
#endif

    NSRect oldFrame, newFrame, windowFrame;

    [self hideCurrentPBar];

    [user3Text setStringValue:message];

    // begin window resizing
    oldFrame = newFrame = [user3Text frame];
    windowFrame = [user3Window frame];

    newFrame.size.height = 10000.0;  // a large number
    newFrame.size = [[user3Text cell] cellSizeForBounds:newFrame];

    if (newFrame.size.height > oldFrame.size.height)
        windowFrame.size.height += (newFrame.size.height - oldFrame.size.height);
    else if (newFrame.size.height < oldFrame.size.height)
        windowFrame.size.height -= (oldFrame.size.height - newFrame.size.height);

    [user3Window setFrame:windowFrame display:NO];
    // end of window resizing

    [user3Button1 setTitle:button1];
    [user3Button2 setTitle:button2];
    [user3Button3 setTitle:button3];

    [user3Window setExcludedFromWindowsMenu:YES];

#ifdef TILP_USES_SHEETS
    [NSApp beginSheet:user3Window
       modalForWindow:[myBoxesController keyWindow]
        modalDelegate:nil
       didEndSelector:nil
          contextInfo:nil];

    [NSApp runModalForWindow:user3Window];

    [NSApp endSheet:user3Window];
#else
    [user3Window setTitle:title];

    session = [NSApp beginModalSessionForWindow:user3Window];

    [user3Window makeKeyAndOrderFront:self];

    for (;;)
    {
        if([NSApp runModalSession:session] != NSRunContinuesResponse)
            break;
    }

    [NSApp endModalSession:session];
#endif

    [user3Window orderOut:self];

    [self showCurrentPBar];

    return objects_ptr->user3_return;
}

- (int)msg4Sheet:(NSString *)title message:(NSString *)message
{
#ifndef TILP_USES_SHEETS
    NSModalSession session;
#endif

    NSRect oldFrame, newFrame, windowFrame;

    objects_ptr->user2_return = 0;

    [self hideCurrentPBar];

    [user2Text setStringValue:message];


    // begin window resizing
    oldFrame = newFrame = [user2Text frame];
    windowFrame = [user2Window frame];

    newFrame.size.height = 10000.0;  // a large number
    newFrame.size = [[user2Text cell] cellSizeForBounds:newFrame];

    if (newFrame.size.height > oldFrame.size.height)
        windowFrame.size.height += (newFrame.size.height - oldFrame.size.height);
    else if (newFrame.size.height < oldFrame.size.height)
        windowFrame.size.height -= (oldFrame.size.height - newFrame.size.height);

    [user2Window setFrame:windowFrame display:NO];
    // end of window resizing

    [user2Button1 setTitle:@"Next"];
    [user2Button2 setTitle:@"Cancel"];

    [user2Window setExcludedFromWindowsMenu:YES];

#ifdef TILP_USES_SHEETS
    [NSApp beginSheet:user2Window
       modalForWindow:[myBoxesController keyWindow]
        modalDelegate:nil
       didEndSelector:nil
          contextInfo:nil];

    [NSApp runModalForWindow:user2Window];

    [NSApp endSheet:user2Window];
#else
    [user2Window setTitle:title];

    session = [NSApp beginModalSessionForWindow:user2Window];

    [user2Window makeKeyAndOrderFront:self];

    for (;;)
    {
        if([NSApp runModalSession:session] != NSRunContinuesResponse)
            break;
    }

    [NSApp endModalSession:session];
#endif

    [user2Window orderOut:self];

    [self showCurrentPBar];

    return objects_ptr->user2_return;
}


/* dialog box w/entry field */

- (NSString *)msgEntrySheet:(NSString *)title message:(NSString *)message content:(NSString *)content
{
#ifndef TILP_USES_SHEETS
  NSModalSession session;
#endif

  NSRect oldFrame, newFrame, windowFrame;
  
  if ([dlgboxentryWindow isVisible])
    return NULL;

  [dlgboxentryEntry setStringValue:content];
  [dlgboxentryEntry selectText:nil];
  [dlgboxentryText setStringValue:message];

  // begin window resizing
  oldFrame = newFrame = [dlgboxentryText frame];
  windowFrame = [dlgboxentryWindow frame];

  newFrame.size.height = 10000.0;  // a large number
  newFrame.size = [[dlgboxentryText cell] cellSizeForBounds:newFrame];

  if (newFrame.size.height > oldFrame.size.height)
    windowFrame.size.height += (newFrame.size.height - oldFrame.size.height);
  else if (newFrame.size.height < oldFrame.size.height)
    windowFrame.size.height -= (oldFrame.size.height - newFrame.size.height);

  [dlgboxentryWindow setFrame:windowFrame display:NO];
  // end of window resizing
 
  [dlgboxentryWindow setExcludedFromWindowsMenu:YES];

#ifdef TILP_USES_SHEETS
  [NSApp beginSheet:dlgboxentryWindow
     modalForWindow:[myBoxesController keyWindow]
      modalDelegate:nil
     didEndSelector:nil
        contextInfo:nil];

  [NSApp runModalForWindow:dlgboxentryWindow];

  [NSApp endSheet:dlgboxentryWindow];
#else
  [dlgboxentryWindow setTitle:title];

  session = [NSApp beginModalSessionForWindow:dlgboxentryWindow];

  [dlgboxentryWindow makeKeyAndOrderFront:self];

  for (;;)
  {
    if([NSApp runModalSession:session] != NSRunContinuesResponse)
      break;
  }

  [NSApp endModalSession:session];
#endif

  [dlgboxentryWindow orderOut:self];

  return objects_ptr->dlgbox_data;
}

/* pbars */

- (void)pbarType2:(NSString *)message
{
  [self hideCurrentPBar];

  pbar_text = pbar2Text;

  [pbar2Text setStringValue:message];

  [pbar2Window setExcludedFromWindowsMenu:YES];

  [pbar2PBar setUsesThreadedAnimation:YES];
  [pbar2PBar startAnimation:self];

  [NSApp beginSheet:pbar2Window
     modalForWindow:[myBoxesController keyWindow]
      modalDelegate:nil
     didEndSelector:nil
        contextInfo:nil];

  [NSApp endSheet:pbar2Window];

  [self showCurrentPBar];
}

- (void)pbarType1
{
  if (pbar1 != nil)
    return;

  pbar1 = pbar1PBar;
  pbar_rate = pbar1Rate;

  pbarWindow = pbar1Window;

  [pbar1Window setExcludedFromWindowsMenu:YES];

  [self showCurrentPBar];
}

- (void)pbarType3
{
  if (pbar1 != nil)
    return;

  pbar1 = pbar3PBar1;
  pbar2 = pbar3PBar2;
  pbar_rate = pbar3Rate;

  pbarWindow = pbar3Window;

  [pbar3Window setExcludedFromWindowsMenu:YES];

  [self showCurrentPBar];
}

- (void)pbarType4:(NSString *)message
{
  if (pbar1 != nil)
    return;

  pbar1 = pbar4PBar;
  pbar_rate = pbar4Rate;
  pbar_text = pbar4Text;

  pbarWindow = pbar4Window;

  [pbar4Window setExcludedFromWindowsMenu:YES];

  [pbar4Text setStringValue:message];

  [self showCurrentPBar];
}

- (void)pbarType5:(NSString *)message
{
  if (pbar1 != nil)
    return;

  pbar1 = pbar5PBar1;
  pbar2 = pbar5PBar2;
  pbar_rate = pbar5Rate;
  pbar_text = pbar5Text;

  pbarWindow = pbar5Window;

  [pbar5Text setStringValue:message];

  [pbar5Window setExcludedFromWindowsMenu:YES];

  [self showCurrentPBar];
}


// destroy pbars

- (void)destroyPbar
{
  if ([pbar1Window isVisible])
  {
    [pbar1Window orderOut:self];
    pbarWindow = nil;
  }

  if ([pbar2Window isVisible])
  {
    [pbar2Window orderOut:self];
    [pbar2PBar stopAnimation:self];
  }

  if ([pbar3Window isVisible])
  {
    [pbar3Window orderOut:self];
    pbarWindow = nil;
  }

  if ([pbar4Window isVisible])
  {
    [pbar4Window orderOut:self];
    pbarWindow = nil;
  }

  if ([pbar5Window isVisible])
  {
    [pbar5Window orderOut:self];
    pbarWindow = nil;
  }

  // reset the pbars, in case the transfer has crashed
  if (pbar1 != nil)
  {
    [pbar1 setDoubleValue:0.0];
    [pbar1 displayIfNeeded];
  }

  if (pbar2 != nil)
  {
    [pbar2 setDoubleValue:0.0];
    [pbar2 displayIfNeeded];
  }

  if (pbar_rate != nil)
  {
    [pbar_rate setStringValue:@"Rate : 0.00 KB/s"];
  }

  if (pbar_text != nil)
  {
    [pbar_text setStringValue:@""];
  }

  pbar1 = nil;
  pbar2 = nil;
  pbar_rate = nil;
  pbar_text = nil;

  // reset, in case the transfer has crashed
  info_update.percentage = 0.0;
  info_update.prev_percentage = 0.0;
}

// this is the refresh part of the stuff :-)

// in cocoa_refresh.m
extern TicableDataRate *dr;

- (void)refreshPbar1
{
  static gfloat rate;
  
  if(pbar1 != nil)
  {
    // refresh only if necessary
    if((info_update.percentage - info_update.prev_percentage) < 0.05) // was 0.01 originally on OS X, 0.05  in GTK code
    {
      if((info_update.percentage - info_update.prev_percentage) < 0)
        info_update.prev_percentage = info_update.percentage;
      else
        return;
    }
    else
      info_update.prev_percentage = info_update.percentage;

    rate = dr->count/toCURRENT(dr->start);

    // set pbar value and textField text

    [pbar1 setDoubleValue:(double)(info_update.percentage * 100)];

    [pbar_rate setStringValue:[NSString stringWithFormat:@"Rate : %3.2f KBytes/s", (rate / 1000)]];
  }
}

- (void)refreshPbar2
{
  if(pbar2 != nil)
  {
    // refresh only if necessary, not too often (works well with 0.01, too, but consumes CPU I guess)
    if((info_update.main_percentage - info_update.prev_main_percentage) < 0.05)
      return;
    else
      info_update.prev_main_percentage = info_update.main_percentage;

    [pbar2 setDoubleValue:(double)(info_update.main_percentage * 100)];

    [pbar2 displayIfNeeded];
  }
}

- (void)refreshLabel
{
  if (pbar_text == nil)
    return;

  [pbar_text setStringValue:[NSString stringWithCString:info_update.label_text]];
  [pbar_text displayIfNeeded];
}

@end
