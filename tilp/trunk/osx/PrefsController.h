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

@interface PrefsController : NSObject
{
    IBOutlet id calcType73;
    IBOutlet id calcType82;
    IBOutlet id calcType83;
    IBOutlet id calcType83p;
    IBOutlet id calcType85;
    IBOutlet id calcType86;
    IBOutlet id calcType89;
    IBOutlet id calcType92;
    IBOutlet id calcType92p;
    IBOutlet id calcTypeV200;
    IBOutlet id calcTypeProbe;
    IBOutlet id consoleModeMatrix;
    IBOutlet id consoleSilent;
    IBOutlet id consoleVerbose;
    IBOutlet id linkCableUGL;
    IBOutlet id linkCableTPU;
    IBOutlet id linkCableTIE;
    IBOutlet id linkCableTGL;
    IBOutlet id linkCableVTI;
    IBOutlet id portCombo;
    IBOutlet id portType;
    IBOutlet id portWarning;
    IBOutlet id linkTimeoutField;
    IBOutlet id linkTimeoutValueStepper;
    IBOutlet id multipleVarsSingle;
    IBOutlet id multipleVarsGroup;
    IBOutlet id orderDecreasing;
    IBOutlet id orderIncreasing;
    IBOutlet id pathModeFull;
    IBOutlet id pathModeLocal;
    IBOutlet id prefsWindow;
    IBOutlet id screenFormatPDF;
    IBOutlet id screenFormatTIFF;
    IBOutlet id screenModeClipped;
    IBOutlet id screenModeFull;
    IBOutlet id screenRenderingBlurry;
    IBOutlet id screenRenderingBW;
    IBOutlet id sortByInfo;
    IBOutlet id sortByName;
    IBOutlet id sortBySize;
    IBOutlet id sortByType;
    IBOutlet id clockModeManual;
    IBOutlet id clockModeSync;
    IBOutlet id clockTimeFormat12;
    IBOutlet id clockTimeFormat24;
    IBOutlet id clockDateFormat;

    IBOutlet id multipleVarsMatrix;
    IBOutlet id pathModeMatrix;
    IBOutlet id orderMatrix;
    IBOutlet id sortByMatrix;
    IBOutlet id linkTypeMatrix;
    IBOutlet id calcTypeMatrix;
    IBOutlet id screenFormatMatrix;
    IBOutlet id screenModeMatrix;
    IBOutlet id screenRenderingMatrix;
    IBOutlet id clockModeMatrix;
    IBOutlet id clockTimeFormatMatrix;
    
    IBOutlet id myBoxesController;
    IBOutlet id myMenuController;
    IBOutlet id myTilpController;
    IBOutlet id mySheetsController;
    IBOutlet id myTransfersController;
    
    NSMutableArray *portNameArray;
    NSMutableArray *portTypeArray;
}
- (IBAction)prefsAdvanced:(id)sender;
- (IBAction)prefsClose:(id)sender;
- (IBAction)showPrefsSheet:(id)sender;

- (BOOL)getSerialPortsList;

// NSComboBox datasource
- (id)comboBox:(NSComboBox *)combo objectValueForItemAtIndex:(int)index;
- (int)numberOfItemsInComboBox:(NSComboBox *)combo;

// NSComboBox delegate
- (void)comboBoxSelectionDidChange:(NSNotification *)notification;
@end
