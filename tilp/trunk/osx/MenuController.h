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

@interface MenuController : NSObject
{
    IBOutlet id dirlistTree;
    IBOutlet id mainWindow;
    IBOutlet id screendumpWindow;
    IBOutlet id screendumpImage;
    IBOutlet id thanksPanel;
    IBOutlet id thanksPanelText;
    IBOutlet id msgSheetText;
    IBOutlet id msgSheetWindow;
    IBOutlet id remoteControlTextArea;
    IBOutlet id remoteControlWindow;
 
    IBOutlet id myBoxesController;
    IBOutlet id myPrefsController;
    IBOutlet id myTilpController;
    IBOutlet id mySheetsController;
    IBOutlet id myTransfersController;

    NSMutableDictionary *toolbarItems;
}

// toolbar

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;

- (void)getVars:(id)sender;

// Application menu
- (IBAction)showAbout:(id)sender;

// file

- (IBAction)saveConfig:(id)sender;
- (IBAction)defaultConfig:(id)sender;

// link

- (IBAction)probeCalc:(id)sender;

// functions 1

- (IBAction)isReady:(id)sender;
- (IBAction)remoteControl:(id)sender;
- (IBAction)getScreen:(id)sender;
- (IBAction)getDirlist:(id)sender;
- (IBAction)doRestore:(id)sender;
- (IBAction)doBackup:(id)sender;

// functions 2

- (IBAction)sendFLASHApp:(id)sender;
- (IBAction)sendAMS:(id)sender;
- (IBAction)getIDList:(id)sender;
- (IBAction)romDump:(id)sender;
- (IBAction)romVersion:(id)sender;
- (IBAction)installShell:(id)sender;

// window

- (IBAction)newWindow:(id)sender;
- (IBAction)closeWindow:(id)sender;

// help

- (IBAction)showThanks:(id)sender;
@end
