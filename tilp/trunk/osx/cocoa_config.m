/*
 * TiLP Cocoa GUI for Mac OS X
 */

#include "cocoa_config.h"
#include "cocoa_structs.h"

#include "../src/struct.h"
#include "../src/defs.h"

#import <Cocoa/Cocoa.h>

extern struct cocoa_objects_ptr *objects_ptr;

// This code cannot go into the PrefsController class
// because it is used before the application is completely
// initialized, so no classes are available.

void
rc_set_unused_items(void)
{
    // what we do not use
    options.xsize = UNUSED;
    options.ysize = UNUSED;
    options.clist_sort = UNUSED;
    options.clist_sort_order = UNUSED;
    options.confirm = UNUSED;
    options.show = UNUSED;
    options.file_mode = UNUSED;
    options.plugins_loading = UNUSED;
    options.unzip_location = NULL;
    options.unzip_options = NULL;
    options.tar_location = NULL;
    options.tar_options = NULL;
}

void
rc_init_with_default(void)
{
    // what we use
    options.ctree_sort = SORT_BY_NAME;
    options.ctree_sort_order = SORT_UP;
    options.path_mode = FULL_PATH;
    options.screen_format = TIFF;
    options.screen_clipping = CLIPPED_SCREEN;
    options.transfer_mode = SILENT_MODE;
    options.file_checking = UNUSED;
    // verbosity of libticables (DISPLAY() function)
    options.console_mode = DSP_OFF;
    options.auto_detect = TRUE;
    options.show_gui = TRUE;
    options.force_dirlist = TRUE;
    
    options.lp.link_type = LINK_UGL;
    options.lp.timeout = 150;
    options.lp.port = USB_PORT_1;
    options.lp.calc_type = CALC_TI92P;
    options.lp.method = IOM_AUTO;
    
    rc_set_unused_items();
}

void
rc_fill_dictionary(void)
{
    NSMutableDictionary *tilpConfig;
    NSNumber *value;

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

    value = [[NSNumber alloc] initWithInt:options.console_mode];
    [tilpConfig setObject:value forKey:@"console_mode"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.link_type];
    [tilpConfig setObject:value forKey:@"link_type"];
    
    value = [[NSNumber alloc] initWithInt:options.lp.calc_type];
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
    
    if ((value = [tilpConfig objectForKey:@"console_mode"]))
    {
        options.console_mode = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"link_type"]))
    {
        options.lp.link_type = [value intValue];
        
            if ((options.lp.link_type == LINK_UGL) || (options.lp.link_type == LINK_TPU))
                options.lp.port = USB_PORT_1;
            else if ((options.lp.link_type == LINK_TIE) || (options.lp.link_type == LINK_VTI))
                options.lp.port = VIRTUAL_PORT_1; // FIXME OS X : dunno if it's the good one
    }
    
    if ((value = [tilpConfig objectForKey:@"calc_type"]))
    {
        options.lp.calc_type = [value intValue];
    }
    
    if ((value = [tilpConfig objectForKey:@"timeout"]))
    {
        options.lp.timeout = [value intValue];
    }
    
    rc_set_unused_items();
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

