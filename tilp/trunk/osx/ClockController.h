/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2003 Julien BLACHE <jb@tilp.info>
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

#include <libticalcs/calc_def.h>

#import <Cocoa/Cocoa.h>

@interface ClockController : NSObject
{
    IBOutlet id clockWindow;

    IBOutlet id clockDay;
    IBOutlet id clockDayStepper;
    IBOutlet id clockMonth;
    IBOutlet id clockMonthStepper;
    IBOutlet id clockYear;
    IBOutlet id clockYearStepper;
    
    IBOutlet id clockHours;
    IBOutlet id clockHoursStepper;
    IBOutlet id clockMinutes;
    IBOutlet id clockMinutesStepper;
    IBOutlet id clockSeconds;
    IBOutlet id clockSecondsStepper;
    
    IBOutlet id clockFormat12;
    IBOutlet id clockFormat24;
    IBOutlet id clockDateFormat;
    IBOutlet id clockFormatMatrix;

    IBOutlet id clockStateOff;
    IBOutlet id clockStateOn;
    IBOutlet id clockStateMatrix;

    IBOutlet id clockSetStatus;

    IBOutlet id myBoxesController;
    IBOutlet id mySheetsController;
    
    TicalcClock clk;
}

- (void)showClock;
- (void)updateFields;

- (IBAction)clockCancel:(id)sender;
- (IBAction)clockSet:(id)sender;
- (void)clockSyncMenu;
- (IBAction)clockSync:(id)sender;
- (IBAction)clockTimeFormat:(id)sender;
- (IBAction)clockStep:(id)sender;

@end
