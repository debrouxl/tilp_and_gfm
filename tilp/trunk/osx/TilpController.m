/*
 * TiLP Cocoa GUI for Mac OS X
 *
 * The code for the toolbar is derived from Apple Sample Code (ToolbarSample)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../src/struct.h"
#include "../src/gui_indep.h"
#include "../src/defs.h"
#include "../src/cb_misc.h"
#include "../src/main.h"
#include "../src/cb_calc.h"

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

- (id)init
{
    self = [super init];
    
    if (self == nil)
        return nil;
        
    tiTypes73 = [NSArray arrayWithObjects:@"73c", @"73g", @"73i", @"73l",
                                          @"73n", @"73p", @"73t", @"73v",
                                          @"73w", @"73y", nil];
    [tiTypes73 retain];
    
    tiTypes82 = [NSArray arrayWithObjects:@"82b", @"82d", @"82g", @"82i",
                                          @"82l", @"82m", @"82n", @"82p",
                                          @"82t", @"82w", @"82y", @"82z", nil];
    [tiTypes82 retain];
                                          
    tiTypes83 = [NSArray arrayWithObjects:@"83b", @"83c", @"83d", @"83g",
                                          @"83i", @"83l", @"83m", @"83n",
                                          @"83p", @"83s", @"83y", nil];
    [tiTypes83 retain];
    // 83+
    tiTypes8x = [NSArray arrayWithObjects:@"8xb", @"8xc", @"8xd", @"8xg",
                                          @"8xi", @"8xl", @"8xm", @"8xn",
                                          @"8xp", @"8xs", @"8xy", nil];
    [tiTypes8x retain];

    tiTypes85 = [NSArray arrayWithObjects:@"85b", @"85c", @"85d", @"85e",
                                          @"85g", @"85i", @"85k", @"85l",
                                          @"85m", @"85n", @"85p", @"85r",
                                          @"85s", @"85v", nil];
    [tiTypes85 retain];
    
    tiTypes86 = [NSArray arrayWithObjects:@"86c", @"86d", @"86e", @"86g",
                                          @"86i", @"86k", @"86l", @"86m",
                                          @"86n", @"86p", @"86r", @"86s",
                                          @"86v", @"86w", nil];
    [tiTypes86 retain];
    
    tiTypes89 = [NSArray arrayWithObjects:@"89a", @"89b", @"89c", @"89d",
                                          @"89e", @"89f", @"89g", @"89i",
                                          @"89k", @"89l", @"89m", @"89p",
                                          @"89s", @"89t", @"89u", @"89x",
                                          @"89z", nil];
    [tiTypes89 retain];

    tiTypes92 = [NSArray arrayWithObjects:@"92a", @"92b", @"92c", @"92d",
                                          @"92e", @"92f", @"92g", @"92i",
                                          @"92l", @"92m", @"92p", @"92s",
                                          @"92t", @"92x", nil];
    [tiTypes92 retain];
    // 92+
    tiTypes9x = [NSArray arrayWithObjects:@"9xa", @"9xb", @"9xc", @"9xd",
                                          @"9xe", @"9xf", @"9xg", @"9xi",
                                          @"9xk", @"9xl", @"9xm", @"9xp",
                                          @"9xs", @"9xt", @"9xu", @"9xx",
                                          @"9xz", nil];
    [tiTypes9x retain];

    return self;
}

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
    
    [tiTypes73 release];
    [tiTypes82 release];
    [tiTypes83 release];
    [tiTypes8x release];
    [tiTypes85 release];
    [tiTypes86 release];
    [tiTypes89 release];
    [tiTypes92 release];
    [tiTypes9x release];
    
    tiTypes73 = nil;
    tiTypes82 = nil;
    tiTypes83 = nil;
    tiTypes8x = nil;
    tiTypes85 = nil;
    tiTypes86 = nil;
    tiTypes89 = nil;
    tiTypes92 = nil;
    tiTypes9x = nil;
    
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
    
    // register for dragging
    [dirlistTree registerForDraggedTypes:[NSArray arrayWithObjects:@"NSFilenamesPboardType", nil]];
    
    //If variables have been passed on the command line in GUI mode then
    //send them
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
            // Set the image here since the value returned from outlineView:objectValueForTableColumn:...
            // didn't specify the image part...
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

// delegate methods of NSOutlineView, dragging-related

// This method validates whether or not the proposal is a valid one.
// Returns NO if the drop should not be allowed.
- (unsigned int)outlineView:(NSOutlineView*)olv validateDrop:(id <NSDraggingInfo>)info proposedItem:(id)item proposedChildIndex:(int)childIndex
{
    BOOL filenameIsValid = NO;

    NSPasteboard *pboard;
    NSArray *filenames;
    NSEnumerator *filesEnum;
    NSString *file;
    
    NSArray *tiTypes;
    NSString *tiType;
    NSEnumerator *tiTypesEnum;
    
    pboard = [info draggingPasteboard];
    
    if ([[pboard types] indexOfObject:@"NSFilenamesPboardType"] != NSNotFound)
        {
            fprintf(stderr, "DEBUG: DRAG: NSFilenamesPboardType is AVAILABLE\n");
            
            filenames = [pboard propertyListForType:@"NSFilenamesPboardType"];
    
            if (filenames != nil)
                {
                    filesEnum = [filenames objectEnumerator];

                    switch (options.lp.calc_type)
                        {
                            case CALC_TI73:
                                tiTypes = tiTypes73;
                                break;
                            case CALC_TI83:
                                tiTypes = tiTypes83;
                                break;
                            case CALC_TI83P:
                                tiTypes = tiTypes8x;
                                break;
                            case CALC_TI85:
                                tiTypes = tiTypes85;
                                break;
                            case CALC_TI86:
                                tiTypes = tiTypes86;
                                break;
                            case CALC_TI89:
                                tiTypes = tiTypes89;
                                break;
                            case CALC_TI92:
                                tiTypes = tiTypes92;
                                break;
                            case CALC_TI92P:
                                tiTypes = tiTypes9x;
                                break;
                            default:
                                return NO;
                        }
                        
                    tiTypesEnum = [tiTypes objectEnumerator];
                    
                    while ((file = [filesEnum nextObject]) != nil)
                        {
                            fprintf(stderr, "DEBUG: FILE : %s", [file cString]);
                            
                            while ((tiType = [tiTypesEnum nextObject]) != nil)
                                {
                                    if ([[[file pathExtension] lowercaseString] isEqualToString:tiType])
                                        {
                                            fprintf(stderr, " should be a TI file\n");
                                            filenameIsValid = YES;
                                            break;
                                        }
                                }
                                
                            if (filenameIsValid == NO)
                                {
                                    fprintf(stderr, " is probably not a TI file, rejecting DROP\n");
                                    break;
                                }
                        }
                }
        }
        
    return filenameIsValid ? NSDragOperationGeneric : NO;
}

- (BOOL)outlineView:(NSOutlineView*)olv acceptDrop:(id <NSDraggingInfo>)info item:(id)targetItem childIndex:(int)childIndex
{
    GList *filelist = NULL;
    struct file_info *fi = NULL;

    NSPasteboard *pboard;
    NSArray *filenames;
    NSEnumerator *filesEnum;
    NSString *file;

    // maybe we could thread cb_send_var() here...
    fprintf(stderr, "Building filelist...\n");
    
    // get a GList
    //filelist = g_list_alloc();
    
    pboard = [info draggingPasteboard];
    
    if ([[pboard types] indexOfObject:@"NSFilenamesPboardType"] != NSNotFound)
        {
            filenames = [pboard propertyListForType:@"NSFilenamesPboardType"];
    
            if (filenames != nil)
                {
                    filesEnum = [filenames objectEnumerator];

                    while ((file = [filesEnum nextObject]) != nil)
                        {
                            fi = (struct file_info *)malloc(sizeof(struct file_info));
                            
                            if (fi == NULL)
                                {
                                    fprintf(stderr, "DEBUG: fi is NULL !!\n");
                                    return NO;
                                }
                            
                            fi->filename = (char *)malloc([file cStringLength] + 1);
                            [file getCString:fi->filename];
                            
                            filelist = g_list_append(filelist, fi);
                        }
                }
        }
    
    clist_win.selection = filelist;
    
    cb_send_var();
    
    return YES;
}

@end
