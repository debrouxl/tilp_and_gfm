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

#include "cocoa_structs.h"
 
#include "../src/struct.h"
#include "../src/intl.h"
#include "../src/defs.h"
 
extern struct cocoa_objects_ptr *objects_ptr;
 
extern struct ticalc_info_update info_update;
 
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
 
- (void)msgSheet:(NSString *)message title:(NSString *)title
{
    // No delegate for this one, we don't care.
    // keep NSBeginAlertSheet here for the moment ; I think we'll have to use a modal sheet, too.
    
    if (pbarWindow != nil)
        [pbarWindow orderOut:nil];
    
    NSBeginAlertSheet(title, nil, nil, nil, mainWindow, nil, nil, nil, nil, message);
                      
    if (pbarWindow != nil)
        {
            [NSApp beginSheet:pbarWindow
                   modalForWindow:mainWindow
                   modalDelegate:nil
                   didEndSelector:nil
                   contextInfo:nil];

            [NSApp endSheet:pbarWindow];
        }
}
 
/* user boxes */
 
- (int)user1Sheet:(NSString *)message button1:(NSString *)button1
{
    if (pbarWindow != nil)
        [pbarWindow orderOut:nil];
    
    [user1Text setStringValue:message];
    [user1Button setTitle:button1];
    
    [user1Window setExcludedFromWindowsMenu:YES];
    
    [NSApp beginSheet:user1Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:user1Window];
    
    [NSApp endSheet:user1Window];
    [user1Window orderOut:nil];

    if (pbarWindow != nil)
        {
            [NSApp beginSheet:pbarWindow
                   modalForWindow:mainWindow
                   modalDelegate:nil
                   didEndSelector:nil
                   contextInfo:nil];

            [NSApp endSheet:pbarWindow];
        }

    return objects_ptr->user1_return;
}
                                                      
- (int)user2Sheet:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2
{        
    if (pbarWindow != nil)
        [pbarWindow orderOut:nil];
    
    [user2Text setStringValue:message];
    [user2Button1 setTitle:button1];
    [user2Button2 setTitle:button2];
    
    [user2Window setExcludedFromWindowsMenu:YES];
    
    [NSApp beginSheet:user2Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:user2Window];
    
    [NSApp endSheet:user2Window];
    [user2Window orderOut:nil];
    
    if (pbarWindow != nil)
        {
            [NSApp beginSheet:pbarWindow
                   modalForWindow:mainWindow
                   modalDelegate:nil
                   didEndSelector:nil
                   contextInfo:nil];

            [NSApp endSheet:pbarWindow];
        }

    return objects_ptr->user2_return;
}
 
- (int)user3Sheet:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2 button3:(NSString *)button3
{
    if (pbarWindow != nil)
        [pbarWindow orderOut:nil];
    
    [user3Text setStringValue:message];
    [user3Button1 setTitle:button1];
    [user3Button2 setTitle:button2];
    [user3Button3 setTitle:button3];
    
    [user3Window setExcludedFromWindowsMenu:YES];
    
    [NSApp beginSheet:user3Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:user3Window];
    
    [NSApp endSheet:user3Window];
    [user3Window orderOut:nil];

    if (pbarWindow != nil)
        {
            [NSApp beginSheet:pbarWindow
                   modalForWindow:mainWindow
                   modalDelegate:nil
                   didEndSelector:nil
                   contextInfo:nil];

            [NSApp endSheet:pbarWindow];
        }

    return objects_ptr->user3_return;
}
 
/* dialog box w/entry field */
 
- (NSString *)dlgboxEntry:(NSString *)message content:(NSString *)content
{
    // This sheet is modal for the main window
    if ([dlgboxentryWindow isVisible])
        return NULL;
          
    [dlgboxentryEntry setStringValue:content];
    [dlgboxentryEntry selectText:nil];
    [dlgboxentryText setStringValue:message];
          
    [dlgboxentryWindow setExcludedFromWindowsMenu:YES];
          
    [NSApp beginSheet:dlgboxentryWindow
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:dlgboxentryWindow];
            
    [NSApp endSheet:dlgboxentryWindow];
    [dlgboxentryWindow orderOut:nil];
    
    return objects_ptr->dlgbox_data;
}
 
/* pbars */

- (void)pbarType2:(NSString *)message
{
    if (pbarWindow != nil)
        [pbarWindow orderOut:nil];

    [pbar2Text setStringValue:message];

    [pbar2Window setExcludedFromWindowsMenu:YES];

    [NSApp beginSheet:pbar2Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
   
    [NSApp endSheet:pbar2Window];
    
    if (pbarWindow != nil)
        {
            [NSApp beginSheet:pbarWindow
                   modalForWindow:mainWindow
                   modalDelegate:nil
                   didEndSelector:nil
                   contextInfo:nil];

            [NSApp endSheet:pbarWindow];
        }
}

- (void)pbarType1
{
    if (pbar1 != nil)
        return;
    
    pbar1 = pbar1PBar;
    pbar_rate = pbar1Rate;

    pbarWindow = pbar1Window;
  
    [pbar1Window setExcludedFromWindowsMenu:YES];
    
    [NSApp beginSheet:pbar1Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp endSheet:pbar1Window];
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

    [NSApp beginSheet:pbar3Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];

    [NSApp endSheet:pbar3Window];
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
   
    [NSApp beginSheet:pbar4Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];

    [NSApp endSheet:pbar4Window];
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

    [NSApp beginSheet:pbar5Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp endSheet:pbar5Window]; 
}
 

// destroy pbars

- (void)destroyPbar
{
    if ([pbar1Window isVisible])
        {
            [pbar1Window orderOut:nil];
            pbarWindow = nil;
        }
        
    if ([pbar2Window isVisible])
        [pbar2Window orderOut:nil];

    if ([pbar3Window isVisible])
        {
            [pbar3Window orderOut:nil];
            pbarWindow = nil;
        }
        
    if ([pbar4Window isVisible])
        {
            [pbar4Window orderOut:nil];
            pbarWindow = nil;
        }
        
    if ([pbar5Window isVisible])
        {
            [pbar5Window orderOut:nil];
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

    pbar1 = nil;
    pbar2 = nil;
    pbar_rate = nil;
    pbar_text = nil;
    
    // reset, in case the transfer has crashed
    info_update.percentage = 0.0;
    info_update.prev_percentage = 0.0;
}

// this is the refresh part of the stuff :-)

// FIXME OS X
// find a mean to allow cocoa to process its events between pbar refresh...

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

            rate = info_update.count / ((float)(clock() - info_update.start_time)/CLOCKS_PER_SEC);
     
            // set pbar value and textField text
                        
            [pbar1 setDoubleValue:(double)(info_update.percentage * 100)];
            [pbar_rate setStringValue:[NSString stringWithFormat:@"Rate : %3.2f KBytes/s", (rate / 1000)]];
                        
            [pbar1 displayIfNeeded];
            [pbar_rate displayIfNeeded];
  
            // FIXME OS X
            // HERE WE NEED TO PASS THE BALL TO COCOA AGAIN TO PROCESS ITS EVENTS !!!
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
      
            // FIXME OS X
            // HERE WE NEED TO PASS THE BALL TO COCOA, TOO.
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
