//
//  cocoa_config.m
//  TiLP
//
//  Created by julien on Sat Oct 20 2001.
//  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
//

#include "cocoa_config.h"
#include "cocoa_structs.h"

#include "../src/struct.h"

#import <Cocoa/Cocoa.h>

extern struct cocoa_objects_ptr *objects_ptr;

void
read_rc_file(void)
{
    NSUserDefaults *prefs;
    NSMutableDictionary *tilpConfig;
    NSNumber *value;

    prefs = [[NSUserDefaults standardUserDefaults] retain];

    if ([prefs objectForKey:@"tilpConfig"] != nil)
        {
            tilpConfig = [[NSMutableDictionary alloc] initWithDictionary:[prefs objectForKey:@"tilpConfig"]];
        }	
    else
        {
            tilpConfig = [[NSMutableDictionary alloc] init];
            // init_with_default_values();
            return;
        }
  
    [tilpConfig retain];
    
    // init the pointers
    objects_ptr->tilpConfig = tilpConfig;
    objects_ptr->prefs = prefs;
    
    if ((value = [tilpConfig objectForKey:@"path_mode"]))
    {
        options.path_mode = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"transfer_mode"]))
    {
        options.transfer_mode = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"ctree_sort"]))
    {
        options.ctree_sort = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"ctree_sort_order"]))
    {
        options.ctree_sort_order = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"screen_format"]))
    {
        options.screen_format = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"screen_clipping"]))
    {
        options.screen_clipping = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"auto_detect"]))
    {
        options.auto_detect = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"link_type"]))
    {
        options.lp.link_type = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"calc_type"]))
    {
        options.lp.calc_type = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"timeout"]))
    {
        options.lp.timeout = [value intValue];
    }
    
    // set_unused_items();
}
    
    
void
write_rc_file(void)
{
    NSUserDefaults *prefs;
    NSMutableDictionary *tilpConfig;
    NSNumber *value;

    prefs = objects_ptr->prefs;
    tilpConfig = objects_ptr->tilpConfig;
    
    value = [[NSNumber alloc] initWithInt:options.path_mode];
    [tilpConfig setObject:value forKey:@"path_mode"];
    
    value = [[NSNumber alloc] initWithInt:options.transfer_mode];
    [tilpConfig setObject:value forKey:@"transfer_mode"];
    
    value = [[NSNumber alloc] initWithInt:options.ctree_sort];
    [tilpConfig setObject:value forKey:@"ctree_sort"];
    
    value = [[NSNumber alloc] initWithInt:options.ctree_sort_order];
    [tilpConfig setObject:value forKey:@"ctree_sort_order"];
    
    value = [[NSNumber alloc] initWithInt:options.screen_format];
    [tilpConfig setObject:value forKey:@"screen_format"];
    
    value = [[NSNumber alloc] initWithInt:options.screen_clipping];
    [tilpConfig setObject:value forKey:@"screen_clipping"];
    
    value = [[NSNumber alloc] initWithInt:options.auto_detect];
    [tilpConfig setObject:value forKey:@"auto_detect"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.link_type];
    [tilpConfig setObject:value forKey:@"link_type"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.calc_type];
    [tilpConfig setObject:value forKey:@"calc_type"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.timeout];
    [tilpConfig setObject:value forKey:@"timeout"];

    [prefs setObject:tilpConfig forKey:@"tilpConfig"];
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

