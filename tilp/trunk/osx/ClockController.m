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
#include <libticalcs/calc_err.h>
#include <libticalcs/calc_int.h>

#include "../src/tilp_core.h"
#include "../src/tilp_defs.h"

#import "ClockController.h"
#import "SheetsController.h"

@implementation ClockController

- (void)showClock
{
    if (!(ti_calc.supported_operations() & OPS_CLOCK))
    {
        tilp_error(ERR_VOID_FUNCTION);
        return;
    }

    if (tilp_calc_isready() != 0)
        return;

    if (tilp_error(ti_calc.get_clock(&clk, 0)) != 0)
        return;

    [self updateFields];

    [clockSetStatus setStringValue:@""];
    
    [NSApp beginSheet:clockWindow
       modalForWindow:[myBoxesController keyWindow]
        modalDelegate:nil
       didEndSelector:nil
          contextInfo:nil];

    [NSApp endSheet:clockWindow];
}

- (void)updateFields
{
    [clockDayStepper setIntValue:clk.day];
    [self clockStep:clockDayStepper];
    [clockMonthStepper setIntValue:clk.month];
    [self clockStep:clockMonthStepper];
    [clockYearStepper setIntValue:(clk.year - 2000)];
    [self clockStep:clockYearStepper];
    [clockMinutesStepper setIntValue:clk.minutes];
    [self clockStep:clockMinutesStepper];
    [clockSecondsStepper setIntValue:clk.seconds];
    [self clockStep:clockSecondsStepper];
    
    if (clk.time_format == 12)
    {
        [clockFormatMatrix setState:NSOnState atRow:0 column:0];
        [clockHoursStepper setMaxValue:12];
    }
    else
    {
        [clockFormatMatrix setState:NSOnState atRow:0 column:1];
        [clockHoursStepper setMaxValue:24];
    }

    [clockHoursStepper setIntValue:clk.hours];
    [self clockStep:clockHoursStepper];

    [clockDateFormat selectItemAtIndex:clk.date_format - 1];
}

- (IBAction)clockCancel:(id)sender
{
    [clockWindow orderOut:self];
}

- (IBAction)clockSet:(id)sender
{
    clk.day = [clockDayStepper intValue];
    clk.month = [clockMonthStepper intValue];
    clk.year = [clockYearStepper intValue] + 2000;
    clk.hours = [clockHoursStepper intValue];
    clk.minutes = [clockMinutesStepper intValue];
    clk.seconds = [clockSecondsStepper intValue];
    clk.date_format = [clockDateFormat indexOfSelectedItem] + 1;

    if (tilp_calc_isready() != 0)
        return;

    if (tilp_error(ti_calc.set_clock(&clk, 0)) != 0)
        return;

    [clockWindow orderOut:self];
}

- (void)clockSyncMenu
{
    NSCalendarDate *now;

    if (!(ti_calc.supported_operations() & OPS_CLOCK))
    {
        tilp_error(ERR_VOID_FUNCTION);
        return;
    }
    
    now = [NSCalendarDate calendarDate];

    clk.time_format = options.time_format;
    clk.date_format = options.date_format;
    
    clk.day = [now dayOfMonth];
    clk.month = [now monthOfYear];
    clk.year = [now yearOfCommonEra];
    if ((clk.time_format == 12) && ([now hourOfDay] > 12))
        clk.hours = [now hourOfDay] - 12;
    else
        clk.hours = [now hourOfDay];

    clk.minutes = [now minuteOfHour];
    clk.seconds = [now secondOfMinute];

    if (tilp_calc_isready() != 0)
        return;

    if (tilp_error(ti_calc.set_clock(&clk, 0)) != 0)
        return;

    [mySheetsController msgSheet:@"Success" message:@"The time is set on your calc."];
}

- (IBAction)clockSync:(id)sender
{
    NSCalendarDate *now;

    now = [NSCalendarDate calendarDate];

    clk.day = [now dayOfMonth];
    clk.month = [now monthOfYear];
    clk.year = [now yearOfCommonEra];
    if ((clk.time_format == 12) && ([now hourOfDay] > 12))
        clk.hours = [now hourOfDay] - 12;
    else
        clk.hours = [now hourOfDay];
        
    clk.minutes = [now minuteOfHour];
    clk.seconds = [now secondOfMinute];

    clk.date_format = [clockDateFormat indexOfSelectedItem] + 1;

    [self updateFields];

    if (tilp_calc_isready() != 0)
    {
        [clockSetStatus setTextColor:[NSColor redColor]];
        [clockSetStatus setStringValue:@"Time not set !"];
        return;
    }

    if (tilp_error(ti_calc.set_clock(&clk, 0)) != 0)
    {
        [clockSetStatus setTextColor:[NSColor redColor]];
        [clockSetStatus setStringValue:@"Time not set !"];
        return;
    }
    
    [clockSetStatus setTextColor:[NSColor greenColor]];
    [clockSetStatus setStringValue:@"Time set !"];
}

- (IBAction)clockTimeFormat:(id)sender
{
    if (NSOnState == [clockFormat12 state])
    {
        clk.time_format = 12;
        if ([clockHoursStepper intValue] > 12)
            [clockHoursStepper setIntValue:([clockHoursStepper intValue] - 12)];
        [clockHoursStepper setMaxValue:12];
    }
    else
    {
        clk.time_format = 24;
        [clockHoursStepper setMaxValue:24];
    }
}

- (IBAction)clockStep:(id)sender
{
    // This definitely needs to be improved.
    
    char *months[12] = { "Jan", "Feb", "Mar", "Apr",
        "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    
    if (sender == clockDayStepper)
        [clockDay setStringValue:[NSString stringWithFormat:@"%02d", [sender intValue]]];
    else if (sender == clockMonthStepper)
        [clockMonth setStringValue:[NSString stringWithCString:months[[sender intValue] - 1]]];
    else if (sender == clockYearStepper)
        [clockYear setStringValue:[NSString stringWithFormat:@"%02d", [sender intValue]]];
    else if (sender == clockHoursStepper)
        [clockHours setStringValue:[NSString stringWithFormat:@"%02d", [sender intValue]]];
    else if (sender == clockMinutesStepper)
        [clockMinutes setStringValue:[NSString stringWithFormat:@"%02d", [sender intValue]]];
    else if (sender == clockSecondsStepper)
        [clockSeconds setStringValue:[NSString stringWithFormat:@"%02d", [sender intValue]]];
}

@end
