#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../src/gui_indep.h"
#include "../src/defs.h"
#include "../src/cb_misc.h"
#include "../src/main.h"

#include "cocoa_sheets.h"
#include "cocoa_structs.h"
#include "cocoa_refresh.h"

extern struct cocoa_objects_ptr *objects_ptr;
extern struct cocoa_pbars_ptr *pbars_ptr;

#import "TilpController.h"

@implementation TilpController

struct gui_fncts gui_functions;

- (void)dealloc
{
    NSUserDefaults *myPrefs;
    NSMutableDictionary *myTilpConfig;
    
    myPrefs = objects_ptr->prefs;
    myTilpConfig = objects_ptr->tilpConfig;
    
    [myPrefs synchronize];
    [myPrefs release];
    myPrefs = nil;
    objects_ptr->prefs = NULL;
    
    [myTilpConfig release];
    myTilpConfig = nil;
    objects_ptr->tilpConfig = NULL;
    
    // at this time, nobody uses these structs anymore (hopefully...)
    // if you get any segfault/sigbus problem on exiting, rank this #1 :)
    free(objects_ptr);
    free(pbars_ptr);
    
    [super dealloc];
}

- (void)awakeFromNib
{   
    fprintf(stderr, "tilp => got awakeFromNib\n");

    // Init the classes pointers
    objects_ptr->BoxesController = BoxesController;
    objects_ptr->MenuController = MenuController;
    objects_ptr->PrefsController = PrefsController;
    objects_ptr->TilpController = self;
  
    objects_ptr->mainWindow = mainWindow;
      
    objects_ptr->dlgbox_data = NULL;
    objects_ptr->box_button = -1;
    
    // Init the GUI independant functions
    gui_functions.msg_box = create_cocoa_msg_sheet;
    gui_functions.user1_box = create_cocoa_user1_sheet;
    gui_functions.user2_box = create_cocoa_user2_sheet;
    gui_functions.user3_box = create_cocoa_user3_sheet;
    gui_functions.dlgbox_entry = create_cocoa_dlgbox_entry;
    gui_functions.create_pbar_type1 = create_cocoa_pbar_type1_sheet;
    gui_functions.create_pbar_type2 = create_cocoa_pbar_type2_sheet;
    gui_functions.create_pbar_type3 = create_cocoa_pbar_type3_sheet;
    gui_functions.create_pbar_type4 = create_cocoa_pbar_type4_sheet;
    gui_functions.create_pbar_type5 = create_cocoa_pbar_type5_sheet;
    gui_functions.destroy_pbar = destroy_pbar;
    set_gui_fncts(&gui_functions);
  
    gt_init_refresh_functions();
    
    /* 
     * If variables have been passed on the command line in GUI mode then
     * send them 
     */
    if(working_mode == MODE_OSX)
        {
            cb_send_cmdline();
        }
}

// required to be a valid dataSource for NSOutlineView
// more methods are available, see the docs...

- (int)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item
{
    // FIXME OS X
    return 0;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
    // FIXME OS X
    return YES;
}

- (id)outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item
{
    // FIXME OS X
    return NULL;
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
    // FIXME OS X
    return NULL;
}

@end
