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

#include <glib/glib.h>
#include <libticalcs/calc_int.h>

#include "../src/cb_misc.h"
#include "../src/cb_calc.h"
#include "../src/struct.h"
#include "../src/gui_indep.h"
#include "../src/error.h"
#include "../src/intl.h"
#include "../src/defs.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"
#include "cocoa_sheets.h"

extern struct cocoa_objects_ptr *objects_ptr;

extern struct screenshot ti_screen;

extern int is_active;

#import "MenuController.h"
#import "TilpController.h"
#import "TransfersController.h"
#import "SheetsController.h"
#import "RCTextView.h"

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


// THIS WILL BE REMOVED WHEN APPLE WILL IMPLEMENT
// A WORKING DRAG'N'DROP WITH NSContentOfFilePBoardType
- (IBAction)getVars:(id)sender
{
    [NSThread detachNewThreadSelector:@selector(getVarsThreaded:)
              toTarget:myTransfersController
              withObject:self];
}

// Application menu

- (IBAction)showAbout:(id)sender
{
    NSMutableDictionary *aboutOptions;
    
    aboutOptions = [[NSMutableDictionary alloc] init];
    
    [aboutOptions setObject:@"TiLP for Mac OS X" forKey:@"ApplicationName"];
    [aboutOptions setObject:@"0.3.6" forKey:@"Version"];
    [aboutOptions setObject:@"Copyright © 1999-2002 Romain LIÉVIN, Julien BLACHE\n<rlievin@mail.com>, <jb@technologeek.org>" forKey:@"Copyright"];
    [aboutOptions setObject:@"4.82" forKey:@"ApplicationVersion"];

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
    cb_default_config();
    
    rc_init_with_default();
    rc_fill_dictionary();
}


// link

- (IBAction)probeCalc:(id)sender
{
    cb_probe_calc();
}


// functions 1

- (IBAction)isReady:(id)sender
{
    cb_calc_is_ready();
}

- (IBAction)remoteControl:(id)sender
{
    // FIXME OS X
    // fix the text (keys <=> TI ops)
    // need to find how to catch certain key combos...
    // maybe use the Command key...
    // forget key combos, will make a keyboard...

    NSSize scrollSize;

    if ((options.lp.calc_type != CALC_TI89) && (options.lp.calc_type != CALC_TI92) && (options.lp.calc_type != CALC_TI92P))
        {
            [mySheetsController msgSheet:@"The remote control is not supported by this model of calculator. Sorry !"
                                title:@"Unsupported !"];
                                
            return;
        }

    if (is_active)
        return;
        
    if ([remoteControlWindow isVisible])
        {
            [remoteControlWindow orderFront:self];
            
            // FIXME OS X
            // pop the keyboard up, too.
            
            return;
        }
        
    //[remoteControlTextArea setStringValue:@"\nYou are in remote control mode.\nPress any key, but, for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n"];
    
    scrollSize = [remoteControlScrollView contentSize];
    
    remoteControlTextArea = [[RCTextView alloc] initWithFrame:NSMakeRect(0, 0, scrollSize.width, scrollSize.height)
                                                textContainer:[[remoteControlScrollView documentView] textContainer]];
        
    [remoteControlTextArea setEditable:YES];
    
    [remoteControlScrollView setDocumentView:remoteControlTextArea];
    
    [remoteControlTextArea insertText:@"NOT IMPLEMENTED"];
    
    [remoteControlScrollView display];
    
    [remoteControlWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:remoteControlWindow title:@"Terminal - Remote Control" filename:NO];
}

- (IBAction)getScreen:(id)sender
{
    [NSThread detachNewThreadSelector:@selector(getScreenThreaded:)
              toTarget:myTransfersController
              withObject:self];
}

- (IBAction)getDirlist:(id)sender
{
    if (is_active)
        return;

    if (cb_dirlist() != 0)
        return;
        
    [myTilpController refreshOutline];
    [myTilpController refreshInfos];
}

- (IBAction)doRestore:(id)sender
{
    NSOpenPanel *op;
    NSDictionary *calcDict;
        
    int result;

    if (is_active)
        return;
            
    result = gif->user2_box(_("Warning"), 
                            _("You are going to restore the calculator content with your backup. The whole memory will be erased. Are you sure you want to do that ?"),
		            _("Proceed"), 
		            _("Cancel"));
                            
    if (result != BUTTON1)
        return;

    op = [NSOpenPanel openPanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [op setTitle:@"Choose the file to restore"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[calcDict objectForKey:@"extBackup"]
        modalForWindow:mainWindow
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


// functions 2

- (IBAction)sendFLASHApp:(id)sender
{
    NSOpenPanel *op;
    NSDictionary *calcDict;
    
    if (is_active)
        return;
    
    op = [NSOpenPanel openPanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [op setTitle:@"Choose the Flash Application to send"];
    [op setAllowsMultipleSelection:YES];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[calcDict objectForKey:@"extFLASHApp"]
        modalForWindow:mainWindow
        modalDelegate:myBoxesController
        didEndSelector:@selector(sendFlashAppDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)sendAMS:(id)sender
{
    NSOpenPanel *op;
    NSDictionary *calcDict;
    
    int result;
    
    if (is_active)
        return;
    
    result = gif->user2_box(_("Warning"), 
                            _("You're going to install a new Operating System on your calculator. This process will take up to 45 minutes. Make sure your batteries are OK before continuing. If, for anyh reason, the transfer should be interrupted, wait until the calc displays \"Wainting to receive...\" than retart the transfer."),
		            _("Proceed"), 
		            _("Cancel"));
                            
    if (result != BUTTON1)
        return;
          
    op = [NSOpenPanel openPanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [op setTitle:@"Choose the file containing AMS"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[calcDict objectForKey:@"extAMS"]
        modalForWindow:mainWindow
        modalDelegate:myBoxesController
        didEndSelector:@selector(sendAMSDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)getIDList:(id)sender
{
    cb_id_list();
}

- (IBAction)romDump:(id)sender
{
    [NSThread detachNewThreadSelector:@selector(romDumpThreaded:)
              toTarget:myTransfersController
              withObject:self];
}

- (IBAction)romVersion:(id)sender
{
    cb_rom_version();
}

- (IBAction)installShell:(id)sender
{
    // FIXME OS X
    // Implemented in Tiffep.
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
