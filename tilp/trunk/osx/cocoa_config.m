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

#include "cocoa_config.h"
#include "cocoa_structs.h"

#include "../src/tilp_struct.h"
#include "../src/tilp_defs.h"

#include <libticalcs/calc_int.h>

#import <Cocoa/Cocoa.h>

extern struct cocoa_objects_ptr *objects_ptr;

// This code cannot go into the PrefsController class
// because it is used before the application is completely
// initialized, so no classes are available.

void
rc_init_with_default(void)
{
    // what we use
    options.ctree_sort = SORT_BY_NAME;
    options.ctree_sort_order = SORT_UP;
    options.path_mode = FULL_PATH;
    options.screen_format = TIFF;
    options.screen_clipping = CLIPPED_SCREEN;
    options.screen_blurry = FALSE;
    // verbosity of libticables (DISPLAY() function)
    options.console_mode = DSP_OFF;
    options.auto_detect = TRUE;
    options.show_gui = TRUE;
    options.confirm = TRUE;
    options.single_or_group = RECV_AS_GROUP;
    options.working_dir = strdup(g_get_home_dir());
    
    options.lp.link_type = LINK_UGL;
    options.lp.timeout = 15;
    options.lp.port = OSX_USB_PORT;
    options.lp.calc_type = CALC_TI92P;
    options.lp.method = IOM_AUTO;
    memset(options.lp.device, 0, sizeof(options.lp.device));
}

void
rc_fill_dictionary(void)
{
    NSMutableDictionary *tilpConfig;
    NSNumber *value;

    tilpConfig = objects_ptr->tilpConfig;
        
    value = [[NSNumber alloc] initWithInt:options.path_mode];
    [tilpConfig setObject:value forKey:@"path_mode"];
    
    value = [[NSNumber alloc] initWithInt:options.ctree_sort];
    [tilpConfig setObject:value forKey:@"ctree_sort"];
    
    value = [[NSNumber alloc] initWithInt:options.ctree_sort_order];
    [tilpConfig setObject:value forKey:@"ctree_sort_order"];
    
    value = [[NSNumber alloc] initWithInt:options.screen_format];
    [tilpConfig setObject:value forKey:@"screen_format"];
    
    value = [[NSNumber alloc] initWithInt:options.screen_clipping];
    [tilpConfig setObject:value forKey:@"screen_clipping"];

    value = [[NSNumber alloc] initWithInt:options.screen_blurry];
    [tilpConfig setObject:value forKey:@"screen_blurry"];
    
    value = [[NSNumber alloc] initWithInt:options.auto_detect];
    [tilpConfig setObject:value forKey:@"auto_detect"];

    value = [[NSNumber alloc] initWithInt:options.console_mode];
    [tilpConfig setObject:value forKey:@"console_mode"];

    value = [[NSNumber alloc] initWithInt:options.single_or_group];
    [tilpConfig setObject:value forKey:@"single_or_group"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.link_type];
    [tilpConfig setObject:value forKey:@"link_type"];
    
    if (options.lp.link_type == LINK_TGL)
        {
            [tilpConfig setObject:[NSString stringWithCString:options.lp.device] forKey:@"serial_device"];
        
            value = [[NSNumber alloc] initWithInt:options.lp.port];
            [tilpConfig setObject:value forKey:@"link_port"];
        }
    
    value = [[NSNumber alloc] initWithInt:ticalc_return_calc()];
    [tilpConfig setObject:value forKey:@"calc_type"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.timeout];
    [tilpConfig setObject:value forKey:@"timeout"];
}

void
rc_get_user_prefs(void)
{
    NSUserDefaults *prefs;
    NSMutableDictionary *tilpConfig;
    NSNumber *value;

    prefs = [[NSUserDefaults standardUserDefaults] retain];

    if ([prefs objectForKey:@"Config"])
        {
#ifdef OSX_DEBUG
            printf("DEBUG: got user prefs\n");
#endif
            tilpConfig = [[[NSMutableDictionary alloc] initWithDictionary:[prefs objectForKey:@"Config"]] retain];
        }	
    else
        {
            tilpConfig = [[NSMutableDictionary alloc] init];
            [tilpConfig retain];
            
            objects_ptr->tilpConfig = tilpConfig;
            objects_ptr->prefs = prefs;
            
            rc_init_with_default();
            rc_fill_dictionary();
            return;
        }
      
    // init the pointers
    objects_ptr->tilpConfig = tilpConfig;
    objects_ptr->prefs = prefs;
    
    if ((value = [tilpConfig objectForKey:@"path_mode"]))
        options.path_mode = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"ctree_sort"]))
        options.ctree_sort = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"ctree_sort_order"]))
        options.ctree_sort_order = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"screen_format"]))
        options.screen_format = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"screen_clipping"]))
        options.screen_clipping = [value intValue];

    if ((value = [tilpConfig objectForKey:@"screen_blurry"]))
        options.screen_blurry = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"auto_detect"]))
        options.auto_detect = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"console_mode"]))
        options.console_mode = [value intValue];

    if ((value = [tilpConfig objectForKey:@"single_or_group"]))
        options.single_or_group = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"link_type"]))
    {
        options.lp.link_type = [value intValue];
        
            if ((options.lp.link_type == LINK_UGL) || (options.lp.link_type == LINK_TPU))
                options.lp.port = OSX_USB_PORT;
            else if ((options.lp.link_type == LINK_TIE) || (options.lp.link_type == LINK_VTI))
                options.lp.port = VIRTUAL_PORT_1; // FIXME OS X : dunno if it's the good one
            else if (options.lp.link_type == LINK_TGL)
                {
                    if ([tilpConfig objectForKey:@"serial_device"] != nil)
                        [[tilpConfig objectForKey:@"serial_device"] getCString:options.lp.device];
                                                
                    if ((value = [tilpConfig objectForKey:@"link_port"]))
                        {
                            options.lp.port = [value intValue];
                        }
                }
    }
    
    if ((value = [tilpConfig objectForKey:@"calc_type"]))
        options.lp.calc_type = [value intValue];
    
    if ((value = [tilpConfig objectForKey:@"timeout"]))
        options.lp.timeout = [value intValue];
}
    
    
void
rc_save_user_prefs(void)
{
    NSUserDefaults *prefs;
    NSMutableDictionary *tilpConfig;
    
    prefs = objects_ptr->prefs;
    tilpConfig = objects_ptr->tilpConfig;
  
    rc_fill_dictionary();
    
    [prefs setObject:tilpConfig forKey:@"Config"];
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

