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

#import <Cocoa/Cocoa.h>

@interface TransfersController : NSObject
{
    IBOutlet id dirlistTree;
    IBOutlet id screendumpWindow;
    IBOutlet id screendumpImage;

    IBOutlet id myBoxesController;
    IBOutlet id myMenuController;
    IBOutlet id myPrefsController;
    IBOutlet id mySheetsController;
    IBOutlet id myTilpController;
}


// THREADED
- (void)getVarsThreaded:(id)sender;
- (void)getScreenThreaded:(id)sender;
- (void)doBackupThreaded:(id)sender;
- (void)romDumpThreaded:(id)sender;

- (void)sendVarsThreaded:(id)sender;
- (void)doRestoreThreaded:(id)files;
- (void)sendFlashAppThreaded:(id)files;
- (void)sendAMSThreaded:(id)files;

// NOT THREADED
- (void)getScreen:(id)sender;
- (void)romDump:(id)sender;
- (void)doBackup:(id)sender;
- (int)sendChar:(uint16_t)tikey;

@end
