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
#include "cocoa_outline_refresh.h"

extern struct cocoa_objects_ptr *objects_ptr;
extern struct cocoa_pbars_ptr *pbars_ptr;

#import "TilpController.h"
#import "ImageAndTextCell.h"

#define NODE(n)			((SimpleTreeNode*)n)
#define NODE_DATA(n) 		((SimpleNodeData*)[NODE((n)) nodeData])
#define SAFENODE(n) 		((SimpleTreeNode*)((n)?(n):(dirlistData)))

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
    
    [dirlistData release];
    dirlistData = nil;
    objects_ptr->dirlistData = NULL;
    
    // at this time, nobody uses these structs anymore (hopefully...)
    // if you get any segfault/sigbus problem on exiting, rank this #1 :)
    free(objects_ptr);
    free(pbars_ptr);
    
    [super dealloc];
}

- (void)awakeFromNib
{   
    NSTableColumn *column;
    ImageAndTextCell *imageAndTextCell;

    fprintf(stderr, "tilp => got awakeFromNib\n");

    // Init the classes pointers
    objects_ptr->BoxesController = BoxesController;
    objects_ptr->MenuController = MenuController;
    objects_ptr->PrefsController = PrefsController;
    objects_ptr->TilpController = self;
  
    objects_ptr->mainWindow = mainWindow;
    
    objects_ptr->dirlistTree = dirlistTree;
    
    objects_ptr->currentFolder = currentFolder;
    objects_ptr->numberOfFolders = numberOfFolders;
    objects_ptr->numberOfVars = numberOfVars;
    objects_ptr->memoryUsed = memoryUsed;
      
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
    
    // init the outline view
    [dirlistTree setDelegate:self];
    
    column = [dirlistTree tableColumnWithIdentifier:@"Varname"];
    imageAndTextCell = [[[ImageAndTextCell alloc] init] autorelease];
    [imageAndTextCell setEditable:NO];
    [column setDataCell:imageAndTextCell];
    
    // we need to display an image
    column = [dirlistTree tableColumnWithIdentifier:@"Attributes"];
    [column setDataCell:imageAndTextCell];
    
    
    // init the content of the NSOutlineView
    refresh_outline();
        
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
    // this method is the first called by the NSOutlineView, so it
    // sets the dirlistData variable -- this is a workaround
    dirlistData = objects_ptr->dirlistData;

    return [SAFENODE(item) numberOfChildren];
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
    return [NODE_DATA(item) isGroup];
}

- (id)outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item
{
    return [SAFENODE(item) childAtIndex:index];
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
    if ([[tableColumn identifier] isEqualToString:@"Varname"])
        return [NODE_DATA(item) name];
    else if ([[tableColumn identifier] isEqualToString:@"Attributes"])
        return nil; // there's no text to display (could be an option ?)
    else if ([[tableColumn identifier] isEqualToString:@"Type"])
        return [NODE_DATA(item) vartype];
    else if ([[tableColumn identifier] isEqualToString:@"Size"])
        return [NODE_DATA(item) varsize];
        
    return nil;
}


// delegate methods of NSOutlineView

- (void)outlineView:(NSOutlineView *)olv willDisplayCell:(NSCell *)cell forTableColumn:(NSTableColumn *)tableColumn item:(id)item
{    
    if ([[tableColumn identifier] isEqualToString:@"Varname"])
        {
            // Make sure there is an image set. If not, it's a folder for sure
            // so set the image to what it should be
            if (item && ![NODE_DATA(item) iconRep])
                [NODE_DATA(item) setIconRep:[NSImage imageNamed:@"dir_c.tiff"]];
            // Set the image here since the value returned from outlineView:objectValueForTableColumn:... didn't specify the image part...
            [(ImageAndTextCell *)cell setImage:[NODE_DATA(item) iconRep]];
        }
    else if ([[tableColumn identifier] isEqualToString:@"Attributes"])
        {
            [(ImageAndTextCell *)cell setImage:[NODE_DATA(item) attribute]];
        }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView shouldExpandItem:(id)item
{
    [NODE_DATA(item) setIconRep:[NSImage imageNamed:@"dir_o.tiff"]];
    
    return YES;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView shouldCollapseItem:(id)item
{
    [NODE_DATA(item) setIconRep:[NSImage imageNamed:@"dir_c.tiff"]];
    
    return YES;
}

@end
