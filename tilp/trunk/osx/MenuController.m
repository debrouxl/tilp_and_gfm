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

#include <glib/glib.h>
#include <libticalcs/calc_int.h>

#include "../src/tilp_core.h"
#include "../src/tilp_struct.h"
#include "../src/tilp_indep.h"
#include "../src/tilp_defs.h"
#include "../src/intl.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"
#include "cocoa_sheets.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "MenuController.h"
#import "TilpController.h"
#import "TransfersController.h"
#import "SheetsController.h"
#import "BoxesController.h"
#import "RCTextView.h"
#import "CalcKeyboardController.h"
#import "ClockController.h"


static void addToolbarItem(NSMutableDictionary *theDict, NSString *identifier, NSString *label, NSString *paletteLabel, NSString *toolTip, id target, SEL settingSelector, id itemContent, SEL action)
{
    NSToolbarItem *item;
    
    item = [[[NSToolbarItem alloc] initWithItemIdentifier:identifier] autorelease];
    
    [item setLabel:label];
    [item setPaletteLabel:paletteLabel];
    [item setToolTip:toolTip];
    [item setTarget:target];
    
    [item performSelector:settingSelector withObject:itemContent];
    [item setAction:action];
  
    [theDict setObject:item forKey:identifier];
}


@implementation MenuController

// the toolbar

-(void)awakeFromNib
{
    NSToolbar *toolbar;

#ifdef OSX_DEBUG
    fprintf(stderr, "menu => got awakeFromNib\n");
#endif

    // Init the instance pointer
    objects_ptr->myMenuController = self;
    
    toolbar = [[[NSToolbar alloc] initWithIdentifier:@"myToolbar"] autorelease];
    
    toolbarItems = [[NSMutableDictionary dictionary] retain];

    addToolbarItem(toolbarItems, @"isReady", @"Ready ?", @"Ready ?", @"Test if the calculator is ready", self, @selector(setImage:), [NSImage imageNamed:@"ready.tiff"], @selector(isReady:));

    addToolbarItem(toolbarItems, @"getDirlist", @"Dirlist", @"Dirlist", @"Obtain dirlist", self, @selector(setImage:), [NSImage imageNamed:@"dirlist.tiff"], @selector(getDirlist:));

    addToolbarItem(toolbarItems, @"getScreen", @"Screen", @"Screen", @"Request screendump", self, @selector(setImage:), [NSImage imageNamed:@"screen.tiff"], @selector(getScreen:));
    
    addToolbarItem(toolbarItems, @"getVars", @"Get vars", @"Get vars", @"Retrieve selected variable(s)", self, @selector(setImage:), [NSImage imageNamed:@"calc.tiff"], @selector(getVars:));

    addToolbarItem(toolbarItems, @"doBackup", @"Backup", @"Backup", @"Perform a backup", self, @selector(setImage:), [NSImage imageNamed:@"memory.tiff"], @selector(doBackup:));

    addToolbarItem(toolbarItems, @"doRestore", @"Restore", @"Restore", @"Restore a backup", self, @selector(setImage:), [NSImage imageNamed:@"memory.tiff"], @selector(doRestore:));

    [toolbar setDelegate:self];

    [toolbar setAllowsUserCustomization:YES];

    [toolbar setAutosavesConfiguration: YES]; 
 
    [toolbar setDisplayMode:NSToolbarDisplayModeIconAndLabel];
    
    [mainWindow setToolbar:toolbar];
}

- (void) dealloc
{
    [toolbarItems release];

    [super dealloc];
}

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag
{
    NSToolbarItem *newItem;
    NSToolbarItem *item;
    
    newItem = [[[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier] autorelease];
    item = [toolbarItems objectForKey:itemIdentifier];
    
    [newItem setLabel:[item label]];
    [newItem setPaletteLabel:[item paletteLabel]];

    [newItem setImage:[item image]];

    [newItem setToolTip:[item toolTip]];
    [newItem setTarget:[item target]];
    [newItem setAction:[item action]];
    [newItem setMenuFormRepresentation:[item menuFormRepresentation]];

    return newItem;
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:@"isReady", @"getDirlist", @"getScreen", @"getVars", @"doBackup", @"doRestore", nil];
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:@"isReady", @"getDirlist", @"getScreen", @"getVars", @"doBackup", @"doRestore" ,nil];
}

// FIXME OS X : Waiting for Apple to produce some code...
// THIS WILL BE REMOVED WHEN APPLE WILL IMPLEMENT
// A WORKING DRAG'N'DROP WITH NSContentOfFilePBoardType
- (IBAction)getVars:(id)sender
{
    NSOpenPanel *op;

    if ((options.single_or_group == RECV_AS_SINGLE) || ([dirlistTree numberOfSelectedRows] == 1))
    {
        op = [NSOpenPanel openPanel];

        [op setTitle:@"Save variables in directory..."];
        [op setAllowsMultipleSelection:NO];

        [op setCanChooseFiles:NO];
        [op setCanChooseDirectories:YES];

        [op beginSheetForDirectory:NSHomeDirectory()
                              file:nil
                             types:nil
                    modalForWindow:[myBoxesController keyWindow]
                     modalDelegate:myBoxesController
                    didEndSelector:@selector(getVarsDidEnd:returnCode:contextInfo:)
                       contextInfo:nil];
    }
    else
    {
        [NSThread detachNewThreadSelector:@selector(getVarsThreaded:)
                                 toTarget:myTransfersController
                               withObject:self];        
    }
}

// Application menu

- (IBAction)showAbout:(id)sender
{
    NSMutableDictionary *aboutOptions;
    
    aboutOptions = [[NSMutableDictionary alloc] init];
    
    [aboutOptions setObject:@"TiLP for Mac OS X" forKey:@"ApplicationName"];
    [aboutOptions setObject:[NSString stringWithFormat:@"%s - %s", TILP_OSX_VERSION, SVN_REV] forKey:@"Version"];
    [aboutOptions setObject:@"Copyright © 1999-2003 Romain LIÉVIN, Julien BLACHE   <roms@tilp.info>, <jb@tilp.info>" forKey:@"Copyright"];
    [aboutOptions setObject:@"6.62" forKey:@"ApplicationVersion"];

    [NSApp orderFrontStandardAboutPanelWithOptions:aboutOptions];
    
    [aboutOptions release];
}

// file

- (IBAction)saveConfig:(id)sender
{
    NSUserDefaults *myPrefs;

    rc_save_user_prefs();
    
    myPrefs = objects_ptr->prefs;
    
    [myPrefs synchronize];
}

- (IBAction)defaultConfig:(id)sender
{
    rc_init_with_default();
    rc_fill_dictionary();
}

// functions

- (IBAction)isReady:(id)sender
{
    tilp_calc_isready();
}

- (IBAction)remoteControl:(id)sender
{
    TicalcType calc;

    ticalc_get_calc(&calc);
    
    if ((calc == CALC_TI89) ||(calc == CALC_TI92) || (calc == CALC_TI92P))
        {
            [myCalcKeyboardController loadKeyboard];
        }
    else
        {
            [mySheetsController msgSheet:@"Unsupported !"
                                message:@"The remote control is not supported by this model of calculator. Sorry !"];
        }
}

- (IBAction)getScreen:(id)sender
{
    [NSThread detachNewThreadSelector:@selector(getScreenThreaded:)
              toTarget:myTransfersController
              withObject:self];
}

- (IBAction)getDirlist:(id)sender
{
    if (tilp_calc_dirlist() != 0)
        return;

    [myTilpController refreshOutline];
}

- (IBAction)doRestore:(id)sender
{
    NSOpenPanel *op;
    NSDictionary *calcDict;
        
    int result;

    result = gif->msg_box2(_("Warning"),
                           _("You are going to restore the calculator content with your backup. The whole memory will be erased.\nAre you sure you want to do that ?"));
                            
    if (result != BUTTON1)
        return;

    op = [NSOpenPanel openPanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [op setTitle:@"Choose the file to restore"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[calcDict objectForKey:@"extBackup"]
        modalForWindow:[myBoxesController keyWindow]
        modalDelegate:myBoxesController
        didEndSelector:@selector(doRestoreDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)doBackup:(id)sender
{
    [NSThread detachNewThreadSelector:@selector(doBackupThreaded:)
              toTarget:myTransfersController
              withObject:self];
}

- (IBAction)sendFLASHApp:(id)sender
{
    NSOpenPanel *op;
    NSDictionary *calcDict;

    op = [NSOpenPanel openPanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [op setTitle:@"Choose the Flash Application to send"];
    [op setAllowsMultipleSelection:YES];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[calcDict objectForKey:@"extFLASHApp"]
        modalForWindow:[myBoxesController keyWindow]
        modalDelegate:myBoxesController
        didEndSelector:@selector(sendFlashAppDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)sendAMS:(id)sender
{
    NSOpenPanel *op;
    NSDictionary *calcDict;
    
    int result;
    
    result = gif->msg_box2(_("Warning"),
                           _("You're going to install a new Operating System on your calculator. This process can take up to 45 minutes. Make sure your batteries are OK before continuing. If, for any reason, the transfer must be interrupted, wait until the calc displays \"Waiting to receive...\" then retart the transfer."));
                            
    if (result != BUTTON1)
        return;
          
    op = [NSOpenPanel openPanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [op setTitle:@"Choose the file containing AMS"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[calcDict objectForKey:@"extAMS"]
        modalForWindow:[myBoxesController keyWindow]
        modalDelegate:myBoxesController
        didEndSelector:@selector(sendAMSDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)getIDList:(id)sender
{
    tilp_calc_idlist();
}

- (IBAction)setClock:(id)sender
{
    if (options.clock_mode == CLOCK_MANUAL)
        [myClockController showClock];
    else
        [myClockController clockSyncMenu];
}

- (IBAction)romDump:(id)sender
{
    [NSThread detachNewThreadSelector:@selector(romDumpThreaded:)
              toTarget:myTransfersController
              withObject:self];
}

- (IBAction)installShell:(id)sender
{
    // FIXME OS X : Implemented in Tiffep.
    // So, wait until the Tiffep is ported to Mac OS X :)
}


// window

- (IBAction)newWindow:(id)sender
{
    if ([mainWindow isVisible] == NO)
        [mainWindow makeKeyAndOrderFront:self];
}

- (IBAction)closeWindow:(id)sender
{
    id window;
    
    if ((window = [NSApp keyWindow]) != nil)
        [window orderOut:nil];
}

// used to enable/disable the "New Window" menu item
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    if ([[menuItem title] isEqualToString:@"New Window"] && ([mainWindow isVisible] == YES))
        return NO;
    else
        return YES;
}

// help

- (IBAction)showThanks:(id)sender
{
    [thanksPanelText readRTFDFromFile:[[NSBundle mainBundle] pathForResource:@"Thanks" ofType:@"rtf"]];
    
    [thanksPanel makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:thanksPanel title:@"Thanks" filename:NO];
}

@end
