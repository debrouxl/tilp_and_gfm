
#include "../src/cb_calc.h"
#include "../src/struct.h"
#include "../src/gui_indep.h"
#include "../src/intl.h"
#include "../src/defs.h"

extern struct screenshot ti_screen;

extern int is_active;

#import "ToolbarController.h"

static void addToolbarItem(NSMutableDictionary *theDict,NSString *identifier,NSString *label,NSString *paletteLabel,NSString *toolTip,id target,SEL settingSelector, id itemContent,SEL action)
{
    // here we create the NSToolbarItem and setup its attributes in line with the parameters
    NSToolbarItem *item = [[[NSToolbarItem alloc] initWithItemIdentifier:identifier] autorelease];
    [item setLabel:label];
    [item setPaletteLabel:paletteLabel];
    [item setToolTip:toolTip];
    [item setTarget:target];
    // the settingSelector parameter can either be @selector(setView:) or @selector(setImage:).  Pass in the right
    // one depending upon whether your NSToolbarItem will have a custom view or an image, respectively
    // (in the itemContent parameter).  Then this next line will do the right thing automatically.
    [item performSelector:settingSelector withObject:itemContent];
    [item setAction:action];
    // Now that we've setup all the settings for this new toolbar item, we add it to the dictionary.
    // The dictionary retains the toolbar item for us, which is why we could autorelease it when we created
    // it (above).
    [theDict setObject:item forKey:identifier];
}

@implementation ToolbarController


-(void)awakeFromNib
{
    NSToolbar *toolbar=[[[NSToolbar alloc] initWithIdentifier:@"myToolbar"] autorelease];
    
    fprintf(stderr, "toolbar => got awakeFromNib\n");
    
    // Here we create the dictionary to hold all of our "master" NSToolbarItems.
    toolbarItems=[[NSMutableDictionary dictionary] retain];

    addToolbarItem(toolbarItems,@"isReady",@"Ready ?",@"Ready ?",@"Test if the calculator is ready",self,@selector(setImage:),[NSImage imageNamed:@"ready.tiff"],@selector(isReady:));

    addToolbarItem(toolbarItems,@"getScreen",@"Screen",@"Screen",@"Request screendump",self,@selector(setImage:),[NSImage imageNamed:@"screen.tiff"],@selector(getScreen:));
    
    addToolbarItem(toolbarItems,@"getDirlist",@"Dirlist",@"Dirlist",@"Obtain dirlist",self,@selector(setImage:),[NSImage imageNamed:@"dirlist.tiff"],@selector(getDirlist:));

    addToolbarItem(toolbarItems,@"doBackup",@"Backup",@"Backup",@"Perform a backup",self,@selector(setImage:),[NSImage imageNamed:@"memory.tiff"],@selector(doBackup:));

    addToolbarItem(toolbarItems,@"doRestore",@"Restore",@"Restore",@"Restore a backup",self,@selector(setImage:),[NSImage imageNamed:@"memory.tiff"],@selector(doRestore:));

     
    // the toolbar wants to know who is going to handle processing of NSToolbarItems for it.  This controller will.
    [toolbar setDelegate:self];
    // If you pass NO here, you turn off the customization palette.  The palette is normally handled automatically
    // for you by NSWindow's -runToolbarCustomizationPalette: method; you'll notice that the "Customize Toolbar"
    // menu item is hooked up to that method in Interface Builder.  Interface Builder currently doesn't automatically 
    // show this action (or the -toggleToolbarShown: action) for First Responder/NSWindow (this is a bug), so you 
    // have to manually add those methods to the First Responder in Interface Builder (by hitting return on the First Responder and 
    // adding the new actions in the usual way) if you want to wire up menus to them.
    [toolbar setAllowsUserCustomization:YES];

    // tell the toolbar that it should save any configuration changes to user defaults.  ie. mode changes, or reordering will persist. 
    // specifically they will be written in the app domain using the toolbar identifier as the key. 
    [toolbar setAutosavesConfiguration: YES]; 
    
    // tell the toolbar to show icons only by default
    [toolbar setDisplayMode: NSToolbarDisplayModeIconAndLabel];
    // install the toolbar.
    [mainWindow setToolbar:toolbar];
}


// This method is required of NSToolbar delegates.  It takes an identifier, and returns the matching NSToolbarItem.
// It also takes a parameter telling whether this toolbar item is going into an actual toolbar, or whether it's
// going to be displayed in a customization palette.
- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag
{
    // We create and autorelease a new NSToolbarItem, and then go through the process of setting up its
    // attributes from the master toolbar item matching that identifier in our dictionary of items.
    NSToolbarItem *newItem = [[[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier] autorelease];
    NSToolbarItem *item=[toolbarItems objectForKey:itemIdentifier];
    
    [newItem setLabel:[item label]];
    [newItem setPaletteLabel:[item paletteLabel]];

    [newItem setImage:[item image]];

    [newItem setToolTip:[item toolTip]];
    [newItem setTarget:[item target]];
    [newItem setAction:[item action]];
    [newItem setMenuFormRepresentation:[item menuFormRepresentation]];

    return newItem;
}

// This method is required of NSToolbar delegates.  It returns an array holding identifiers for the default
// set of toolbar items.  It can also be called by the customization palette to display the default toolbar.    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:@"isReady",@"getDirlist",@"getScreen",@"doBackup",@"doRestore",nil];
}

// This method is required of NSToolbar delegates.  It returns an array holding identifiers for all allowed
// toolbar items in this toolbar.  Any not listed here will not be available in the customization palette.
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:@"isReady",@"getDirlist",@"getScreen",@"doBackup",@"doRestore",nil];
}

// throw away our toolbar items dictionary
- (void) dealloc
{
    [toolbarItems release];
    [super dealloc];
}


- (IBAction)doBackup:(id)sender
{
    cb_receive_backup();
}

- (IBAction)doRestore:(id)sender
{
    NSOpenPanel *op;
    NSString *nsfile;
    
    int result;
    char *file;

    // FIXME OS X
    // find the extension of the file to pass as an argument to the NSOpenPanel
    
    if (is_active)
        return;
    
    result = gif->user2_box(_("Warning"), 
                            _("You are going to restore the calculator content with your backup. The whole memory will be erased. Are you sure you want to do that ?"),
		            _("Proceed"), 
		            _("Cancel"));
                            
    if(result != BUTTON1)
        return;

    result = -1; // neutral value
    
    op = [NSOpenPanel openPanel];
    
    [op setTitle:@"Choose the file to restore"];
    [op setAllowsMultipleSelection:NO];
    
    result = [op runModalForDirectory:NSHomeDirectory() file:nil
              types:[NSArray arrayWithObject:@"fixmecuzidontknowtheextension"]];
                                      
    if (result == NSOKButton)
        {
            nsfile = [[op filenames] objectAtIndex:0];
            
            file = (char *)malloc([nsfile cStringLength] + 1);
            
            [nsfile getCString:file];
            
            cb_send_backup(file);
            
            [nsfile release];
            
            free(file);
        }
    
    [op release];
}

- (IBAction)getDirlist:(id)sender
{
    cb_dirlist();
}

- (IBAction)getScreen:(id)sender
{
    NSData *bitmap;
    NSImage *screen;

    if (cb_screen_capture() != 0)
        return;
    
    [screendumpWindow makeKeyAndOrderFront:self];
    
    bitmap = [[NSData alloc] initWithBytes:ti_screen.img.bitmap length:strlen(ti_screen.img.bitmap)];
    [bitmap autorelease];
 
    // FIXME OS X
    // maybe we need to tell the NSImage to render our bitmap...   
    screen = [[NSImage alloc] initWithData:bitmap];
    [screen autorelease];
    
    [screendumpImage setImage:screen];
}

- (IBAction)isReady:(id)sender
{
    cb_calc_is_ready();
}

@end
