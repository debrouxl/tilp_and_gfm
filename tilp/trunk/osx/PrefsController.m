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
 
/*
 * The code for establishing a list of available serial devices is derived from
 * Apple Sample Code (SerialPortSample). Apple is not liable for anything regarding
 * this code, according to the Apple Sample Code License.
 */

#include <CoreFoundation/CoreFoundation.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/serial/IOSerialKeys.h>
#include <IOKit/IOBSD.h>

#include <paths.h>
#include <sys/param.h>

#include <libticalcs/calc_int.h>

#include "../src/struct.h"
#include "../src/defs.h"
#include "../src/error.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "PrefsController.h"

@implementation PrefsController

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
    fprintf(stderr, "prefs => got awakeFromNib\n");
#endif
    
    // Init instance pointer
    objects_ptr->myPrefsController = self;
}

- (IBAction)prefsAdvanced:(id)sender
{
    if (sender == linkTimeoutValueStepper)
        {
            [linkTimeoutField takeIntValueFrom:linkTimeoutValueStepper];
            options.lp.timeout = [linkTimeoutField intValue];
        }
    else if (sender == linkTimeoutField)
        {
            [linkTimeoutValueStepper takeIntValueFrom:linkTimeoutField];
            options.lp.timeout = [linkTimeoutField intValue];
        }
}

- (IBAction)prefsClose:(id)sender
{
    NSString *portName;
    
    // general
    
    if (NSOnState == [orderIncreasing state])
        options.ctree_sort_order = SORT_UP;
    else if (NSOnState == [orderDecreasing state])
        options.ctree_sort_order = SORT_DOWN;

    if (NSOnState == [sortByInfo state])
        options.ctree_sort = SORT_BY_INFO;
    else if (NSOnState == [sortByName state])
        options.ctree_sort = SORT_BY_NAME;
    else if (NSOnState == [sortBySize state])
        options.ctree_sort = SORT_BY_SIZE;
    else if (NSOnState == [sortByType state])
        options.ctree_sort = SORT_BY_TYPE;

    if (NSOnState == [pathModeFull state])
        options.path_mode = FULL_PATH;
    else if (NSOnState == [pathModeLocal state])
        options.path_mode = LOCAL_PATH;

    if (NSOnState == [transferModeManual state])
        options.transfer_mode = MANUAL_MODE;
    else if (NSOnState == [transferModeSilent state])
        options.transfer_mode = SILENT_MODE;

    // hardware
    
    if (NSOnState == [linkCableUGL state])
        {
            options.lp.link_type = LINK_UGL;
            
            options.lp.port = OSX_USB_PORT;
            memset(options.lp.device, 0, sizeof(options.lp.device));
        }
    else if (NSOnState == [linkCableTPU state])
        {
            options.lp.link_type = LINK_TPU;
         
            options.lp.port = OSX_USB_PORT;
            memset(options.lp.device, 0, sizeof(options.lp.device));
        }
    else if (NSOnState == [linkCableTIE state])
        {
            options.lp.link_type = LINK_TIE;
        
            options.lp.port = VIRTUAL_PORT_1;
            memset(options.lp.device, 0, sizeof(options.lp.device));
        }
    else if (NSOnState == [linkCableVTI state])
        {
            options.lp.link_type = LINK_VTI;
         
            options.lp.port = VIRTUAL_PORT_1;
            memset(options.lp.device, 0, sizeof(options.lp.device));
        }
    else if (NSOnState == [linkCableTGL state]) // beta support
        {
            options.lp.link_type = LINK_TGL;
            options.lp.port = OSX_SERIAL_PORT;
        
            portName = [portNameArray objectAtIndex:[portCombo indexOfSelectedItem]];

            [portName getCString:options.lp.device];
        }

    // calculator

    if (NSOnState == [calcType92p state])
        options.lp.calc_type = CALC_TI92P;
    else if (NSOnState == [calcType92 state])
        options.lp.calc_type = CALC_TI92;
    else if (NSOnState == [calcType89 state])
        options.lp.calc_type = CALC_TI89;
    else if (NSOnState == [calcType86 state])
        options.lp.calc_type = CALC_TI86;
    else if (NSOnState == [calcType85 state])
        options.lp.calc_type = CALC_TI85;
    else if (NSOnState == [calcType83p state])
        options.lp.calc_type = CALC_TI83P;
    else if (NSOnState == [calcType83 state])
        options.lp.calc_type = CALC_TI83;
    else if (NSOnState == [calcType82 state])
        options.lp.calc_type = CALC_TI82;
    else if (NSOnState == [calcType73 state])
        options.lp.calc_type = CALC_TI73;
                          
    options.auto_detect = [calcTypeProbe state];
    
    // screendump
    
    if (NSOnState == [screenFormatPCX state])
        options.screen_format = PCX;
    else if (NSOnState == [screenFormatTIFF state])
        options.screen_format = TIFF;
    else if (NSOnState == [screenFormatXPM state])
        options.screen_format = XPM;

    if (NSOnState == [screenModeClipped state])
        options.screen_clipping = TRUE;
    else if (NSOnState == [screenModeFull state])
        options.screen_clipping = FALSE;
        
    // advanced
    
    if (NSOnState == [consoleVerbose state])
        options.console_mode = DSP_ON;
    else if (NSOnState == [consoleSilent state])
        options.console_mode = DSP_OFF;
            
    ticable_set_param2(options.lp);
        
    ticable_set_cable(options.lp.link_type, &link_cable);
    
    ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);

    rc_save_user_prefs();

    [NSApp stopModal];

    if (portNameArray != nil)
        {
            [portNameArray release];
            portNameArray = nil;
        }
        
    if (portTypeArray != nil)
        {
            [portTypeArray release];
            portTypeArray = nil;
        }
}

- (IBAction)showPrefsSheet:(id)sender
{
    NSEnumerator *portEnumerator;
    NSString *portName;
    BOOL gotListing;
    BOOL deviceMatched = NO;

    // get the list of all serial ports
    gotListing = [self getSerialPortsList];

    if (options.path_mode == FULL_PATH)
        [pathModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [pathModeMatrix setState:NSOnState atRow:0 column:1];
    
    if (options.transfer_mode == SILENT_MODE)
        [transferModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [transferModeMatrix setState:NSOnState atRow:0 column:1];
        
    switch(options.ctree_sort)
        {
            case SORT_BY_NAME:
                [sortByMatrix setState:NSOnState atRow:0 column:0];
                break;
            case SORT_BY_TYPE:
                [sortByMatrix setState:NSOnState atRow:0 column:1];
                break;
            case SORT_BY_INFO:
                [sortByMatrix setState:NSOnState atRow:1 column:0];
                break;
            case SORT_BY_SIZE:
                [sortByMatrix setState:NSOnState atRow:1 column:1];
                break;
        }
        
    if (options.ctree_sort_order == SORT_UP)
        [orderMatrix setState:NSOnState atRow:0 column:0];
    else
        [orderMatrix setState:NSOnState atRow:0 column:1];

    if ((portNameArray == nil) || (gotListing != YES))
        {
            [portWarning setStringValue:@"Something wicked happened while listing your serial ports..."];
        }
    else
        {
            [portCombo reloadData];
            [portWarning setStringValue:@""];
        }

    switch(options.lp.link_type)
        {
            case LINK_UGL:
                [linkTypeMatrix setState:NSOnState atRow:0 column:0];
                break;
            case LINK_TPU:
                [linkTypeMatrix setState:NSOnState atRow:0 column:1];
                break;
            case LINK_TIE:
                [linkTypeMatrix setState:NSOnState atRow:1 column:0];
                break;
            case LINK_VTI:
                [linkTypeMatrix setState:NSOnState atRow:1 column:1];
                break;
            case LINK_TGL: // beta support
                [linkTypeMatrix setState:NSOnState atRow:2 column:0];
                
                    if ((portNameArray == nil) || (gotListing != YES))
                        {
                            [portWarning setStringValue:@"Something wicked happened while listing your serial ports..."];
                            break;
                        }
                        
                portEnumerator = [portNameArray objectEnumerator];
                
                [portWarning setStringValue:@""];
                
                while ((portName = [portEnumerator nextObject]) != nil)
                    {
                        if ((options.lp.device != NULL) && ([portName isEqualToString:[NSString stringWithCString:options.lp.device]]))
                            {
                                [portCombo selectItemAtIndex:[portNameArray indexOfObject:portName]];
                                [portCombo setObjectValue:portName];
                                
                                deviceMatched = YES;
                                
                                break;
                            }
                    }
                break;
        }

        if ((gotListing == YES) && (portNameArray != nil) && (deviceMatched == NO))
            {
                [portCombo selectItemAtIndex:0];
                [portCombo setObjectValue:[portNameArray objectAtIndex:0]];
            }

    switch(ticalc_get_calc2())
        {
            case CALC_TI92P:
                [calcTypeMatrix setState:NSOnState atRow:0 column:0];
                break;
            case CALC_TI92:
                [calcTypeMatrix setState:NSOnState atRow:1 column:0];
                break;
            case CALC_TI89:
                [calcTypeMatrix setState:NSOnState atRow:2 column:0];
                break;
            case CALC_TI86:
                [calcTypeMatrix setState:NSOnState atRow:0 column:1];
                break;
            case CALC_TI85:
                [calcTypeMatrix setState:NSOnState atRow:1 column:1];
                break;
            case CALC_TI83P:
                [calcTypeMatrix setState:NSOnState atRow:2 column:1];
                break;
            case CALC_TI83:
                [calcTypeMatrix setState:NSOnState atRow:0 column:2];
                break;
            case CALC_TI82:
                [calcTypeMatrix setState:NSOnState atRow:1 column:2];
                break;
            case CALC_TI73:
                [calcTypeMatrix setState:NSOnState atRow:2 column:2];
                break;
        }
                
    if (options.auto_detect == TRUE)
        [calcTypeProbe setState:NSOnState];
    else
        [calcTypeProbe setState:NSOffState];
    
    switch(options.screen_format)
        {
            case TIFF:
                [screenFormatMatrix setState:NSOnState atRow:0 column:0];
                break;
            case PCX:
                [screenFormatMatrix setState:NSOnState atRow:1 column:0];
                break;
            case XPM:
                [screenFormatMatrix setState:NSOnState atRow:2 column:0];
                break;
        }
        
    if (options.screen_clipping == FULL_SCREEN)
        [screenModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [screenModeMatrix setState:NSOnState atRow:1 column:0];
        
    if ((options.lp.timeout > 0) && (options.lp.timeout <= 50))
        [linkTimeoutField setIntValue:options.lp.timeout];
    else // defaults to 5 (tenth of seconds -- half a second)
        [linkTimeoutField setIntValue:5];
        
    if (options.console_mode == DSP_ON)
        [consoleModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [consoleModeMatrix setState:NSOnState atRow:0 column:1];
        
    [NSApp beginSheet:prefsWindow
           modalForWindow:[myBoxesController keyWindow]
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:prefsWindow];
    
    [NSApp endSheet:prefsWindow];
    [prefsWindow orderOut:self];
}

- (BOOL)getSerialPortsList
{
    mach_port_t			masterPort;
    kern_return_t 		kr = KERN_FAILURE;
    io_object_t 		serialService;
    io_iterator_t 		serialIterator;
    
    CFTypeRef			portNameAsCFString;
    CFTypeRef			bsdPathAsCFString;
    CFMutableDictionaryRef 	classesToMatch;

    char portName[128];
    char bsdPath[MAXPATHLEN];

    Boolean result;
    
#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: getting serial ports listing...\n");
#endif

    kr = IOMasterPort(MACH_PORT_NULL, &masterPort);
        
    if (KERN_SUCCESS != kr)
        {
#ifdef OSX_DEBUG
            fprintf(stderr, "IOMasterPort returned %d\n", kr);
#endif
            return NO;
        }

    // Serial devices are instances of class IOSerialBSDClient
    classesToMatch = IOServiceMatching(kIOSerialBSDServiceValue);
    
    if (classesToMatch != NULL)
        {
            CFDictionarySetValue(classesToMatch,
                                CFSTR(kIOSerialBSDTypeKey),
                                CFSTR(kIOSerialBSDAllTypes)); // all serial...
        }
#ifdef OSX_DEBUG
    else
        fprintf(stderr, "IOServiceMatching returned a NULL dictionary.\n");
#endif
    
    kr = IOServiceGetMatchingServices(masterPort, classesToMatch, &serialIterator);    
    
    if (KERN_SUCCESS != kr)
        {
#ifdef OSX_DEBUG
            fprintf(stderr, "IOServiceGetMatchingServices returned %d\n", kr);
#endif
            return NO;
        }
        
    if (portNameArray != nil)
        [portNameArray release];
        
    portNameArray = [[NSMutableArray alloc] init];
    [portNameArray retain];
        
    if (portTypeArray != nil)
        [portTypeArray release];
        
    portTypeArray = [[NSMutableArray alloc] init];
    [portTypeArray retain];
        
    while ((serialService = IOIteratorNext(serialIterator)))
        {
            bsdPathAsCFString = IORegistryEntryCreateCFProperty(serialService,
                                                                CFSTR(kIOCalloutDeviceKey),
                                                                kCFAllocatorDefault,
                                                                0);
            if (bsdPathAsCFString)
                {
                    result = CFStringGetCString(bsdPathAsCFString,
                                                bsdPath,
                                                sizeof(bsdPath), 
                                                kCFStringEncodingASCII);
                    CFRelease(bsdPathAsCFString);
            
                    if (result)
                        {
#ifdef OSX_DEBUG
                            fprintf(stderr, "BSD path: %s, ", bsdPath);
#endif                            
                            [portNameArray addObject:[NSString stringWithCString:bsdPath]];
                        }
                }


            portNameAsCFString = IORegistryEntryCreateCFProperty(serialService,
                                                                CFSTR(kIOTTYDeviceKey),
                                                                kCFAllocatorDefault,
                                                                0);
            if (portNameAsCFString)
                {
                    result = CFStringGetCString(portNameAsCFString,
                                                portName,
                                                sizeof(portName), 
                                                kCFStringEncodingASCII);
                    CFRelease(portNameAsCFString);
            
                    if (result)
                        {
#ifdef OSX_DEBUG
                            fprintf(stderr, "Serial stream name: %s", portName);
#endif
                            [portTypeArray addObject:[NSString stringWithFormat:@"Type : %s", portName]];
                            
                            kr = KERN_SUCCESS;
                        }
                }
#ifdef OSX_DEBUG
            fprintf(stderr, "\n");
#endif
            IOObjectRelease(serialService);
        }

    IOObjectRelease(serialIterator);

#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: got listing...\n");
#endif

    return (kr == KERN_SUCCESS) ? YES : NO;
}

// NSComboBox datasource
- (id)comboBox:(NSComboBox *)combo objectValueForItemAtIndex:(int)index
{
#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: asking object value\n");
#endif

    if (portNameArray != nil)
        return [portNameArray objectAtIndex:index];
    else
        return nil;
}
- (int)numberOfItemsInComboBox:(NSComboBox *)combo;
{
#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: asking number of elements\n");
#endif

    if (portNameArray != nil)
        return [portNameArray count];
    else
        return 0;
}

// NSComboBox delegate
- (void)comboBoxSelectionDidChange:(NSNotification *)notification
{
    NSString *type;

#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: SELECTION CHANGED\n");
#endif

    type = [portTypeArray objectAtIndex:[portCombo indexOfSelectedItem]];
    
    [portType setStringValue:type];
}

@end
