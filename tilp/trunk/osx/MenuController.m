#include <glib/glib.h>

#include "../src/cb_misc.h"
#include "../src/cb_calc.h"
#include "../src/struct.h"
#include "../src/gui_indep.h"
#include "../src/error.h"
#include "../src/intl.h"
#include "../src/defs.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"
#include "cocoa_sheets.h"

extern struct cocoa_objects_ptr *objects_ptr;

extern struct screenshot ti_screen;

extern int is_active;

#import "MenuController.h"

static void addToolbarItem(NSMutableDictionary *theDict, NSString *identifier, NSString *label, NSString *paletteLabel, NSString *toolTip, id target, SEL settingSelector, id itemContent, SEL action)
{
    NSToolbarItem *item;
    
    item = [[[NSToolbarItem alloc] initWithItemIdentifier:identifier] autorelease];
    
    [item setLabel:label];
    [item setPaletteLabel:paletteLabel];
    [item setToolTip:toolTip];
    [item setTarget:target];
    
    [item performSelector:settingSelector withObject:itemContent];
    [item setAction:action];
  
    [theDict setObject:item forKey:identifier];
}


@implementation MenuController

// the toolbar

-(void)awakeFromNib
{
    NSToolbar *toolbar;
    
    toolbar = [[[NSToolbar alloc] initWithIdentifier:@"myToolbar"] autorelease];
    
    fprintf(stderr, "menu => got awakeFromNib\n");
    
    toolbarItems = [[NSMutableDictionary dictionary] retain];

    addToolbarItem(toolbarItems, @"isReady", @"Ready ?", @"Ready ?", @"Test if the calculator is ready", self, @selector(setImage:), [NSImage imageNamed:@"ready.tiff"], @selector(isReady:));

    addToolbarItem(toolbarItems, @"getScreen", @"Screen", @"Screen", @"Request screendump", self, @selector(setImage:), [NSImage imageNamed:@"screen.tiff"], @selector(getScreen:));
    
    addToolbarItem(toolbarItems, @"getDirlist", @"Dirlist", @"Dirlist",@"Obtain dirlist", self, @selector(setImage:), [NSImage imageNamed:@"dirlist.tiff"], @selector(getDirlist:));

    addToolbarItem(toolbarItems, @"doBackup", @"Backup", @"Backup", @"Perform a backup", self, @selector(setImage:), [NSImage imageNamed:@"memory.tiff"], @selector(doBackup:));

    addToolbarItem(toolbarItems, @"doRestore", @"Restore", @"Restore", @"Restore a backup", self, @selector(setImage:), [NSImage imageNamed:@"memory.tiff"], @selector(doRestore:));

    [toolbar setDelegate:self];

    [toolbar setAllowsUserCustomization:YES];

    [toolbar setAutosavesConfiguration: YES]; 
 
    [toolbar setDisplayMode:NSToolbarDisplayModeIconAndLabel];
    
    [mainWindow setToolbar:toolbar];
}

- (void) dealloc
{
    [toolbarItems release];

    [super dealloc];
}

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag
{
    NSToolbarItem *newItem;
    NSToolbarItem *item;
    
    newItem = [[[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier] autorelease];
    item = [toolbarItems objectForKey:itemIdentifier];
    
    [newItem setLabel:[item label]];
    [newItem setPaletteLabel:[item paletteLabel]];

    [newItem setImage:[item image]];

    [newItem setToolTip:[item toolTip]];
    [newItem setTarget:[item target]];
    [newItem setAction:[item action]];
    [newItem setMenuFormRepresentation:[item menuFormRepresentation]];

    return newItem;
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:@"isReady", @"getDirlist", @"getScreen", @"doBackup", @"doRestore", nil];
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:@"isReady", @"getDirlist", @"getScreen", @"doBackup", @"doRestore" ,nil];
}


// file

- (IBAction)saveConfig:(id)sender
{
    NSUserDefaults *myPrefs;

    rc_save_user_prefs();
    
    myPrefs = objects_ptr->prefs;
    
    [myPrefs synchronize];
}

- (IBAction)defaultConfig:(id)sender
{
    cb_default_config();
    
    rc_init_with_default();
    rc_fill_dictionary();
}


// link

- (IBAction)probeCalc:(id)sender
{
    cb_probe_calc();
}


// functions 1

- (IBAction)isReady:(id)sender
{
    cb_calc_is_ready();
}

- (IBAction)remoteControl:(id)sender
{
    // FIXME OS X
    // fix the text (keys <=> TI ops)
    // need to find how to catch certain key combos...
    // maybe use the Command key...

    id remoteControlWindow;
    id remoteControlTextArea;
    
    if (is_active)
        return;
    
    remoteControlWindow = objects_ptr->remoteControlWindow;
    
    if ([remoteControlWindow isVisible])
        {
            [remoteControlWindow orderFront:self];
            return;
        }
    
    remoteControlTextArea = objects_ptr->remoteControlTextArea;
    
    [remoteControlTextArea setStringValue:@"\nYou are in remote control mode.\nPress any key, but, for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n"];
    
    [remoteControlWindow makeKeyAndOrderFront:self];
}

- (IBAction)getScreen:(id)sender
{
    NSData *bitmap;
    NSImage *screen;

    if (is_active)
        return;

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

- (IBAction)getDirlist:(id)sender
{
    // FIXME OS X
    // see gtk code, I believe it's not so simple...
    // Plus, we must update the NSOutlineView

    if (is_active)
        return;

    if (cb_dirlist() != 0)
        return;
        
    // send a reloadData message to the outline view
}

- (IBAction)doRestore:(id)sender
{
    NSOpenPanel *op;
        
    int result;
    
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

    op = [NSOpenPanel openPanel];
    
    [op setTitle:@"Choose the file to restore"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[NSArray arrayWithObject:@"fixmecuzidontknowtheextension"]
        modalForWindow:mainWindow
        modalDelegate:BoxesController
        didEndSelector:@selector(doRestoreDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)doBackup:(id)sender
{
    // FIXME OS X : propose a default filename w/appropriate extension
        
    NSSavePanel *sp;
    
    if (is_active)
        return;
    
    if (cb_receive_backup() != 0)
        return;
    
    sp = [NSSavePanel savePanel];
    
    [sp beginSheetForDirectory:NSHomeDirectory()
        file:@""
        modalForWindow:mainWindow
        modalDelegate:BoxesController
        didEndSelector:@selector(doBackupDidEnd:returnCode:contextInfo:)
        contextInfo:sp];
}


// functions 2

- (IBAction)sendFLASHApp:(id)sender
{
    NSOpenPanel *op;

    // FIXME OS X
    // find the extension of the file to pass as an argument to the NSOpenPanel
    
    if (is_active)
        return;
    
    op = [NSOpenPanel openPanel];
    
    [op setTitle:@"Choose the Flash Application to send"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[NSArray arrayWithObject:@"fixmecuzidontknowtheextension"]
        modalForWindow:mainWindow
        modalDelegate:BoxesController
        didEndSelector:@selector(sendFlashAppDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)sendAMS:(id)sender
{
    NSOpenPanel *op;
    
    int result;

    // FIXME OS X
    // find the extension of the file to pass as an argument to the NSOpenPanel
    
    if (is_active)
        return;
    
    result = gif->user2_box(_("Warning"), 
                            _("You're going to install a new Operating System on your calculator. This process will take up to 45 minutes. Make sure your batteries are OK before continuing. If, for anyh reason, the transfer should be interrupted, wait until the calc displays \"Wainting to receive...\" than retart the transfer."),
		            _("Proceed"), 
		            _("Cancel"));
                            
    if(result != BUTTON1)
        return;
    
    op = [NSOpenPanel openPanel];
    
    [op setTitle:@"Choose the file containing AMS"];
    [op setAllowsMultipleSelection:NO];
    
    [op beginSheetForDirectory:NSHomeDirectory()
        file:nil
        types:[NSArray arrayWithObject:@"fixmecuzidontknowtheextension"]
        modalForWindow:mainWindow
        modalDelegate:BoxesController
        didEndSelector:@selector(sendAMSDidEnd:returnCode:contextInfo:)
        contextInfo:nil];
}

- (IBAction)getIDList:(id)sender
{
    cb_id_list();
}

- (IBAction)romDump:(id)sender
{
    // FIXME OS X
    // file extensions, proposed filenames...
    
    // we need a fileselection here
    // then call cb_ams_to_rom(char *filename) from cb_calc.c
    
    NSSavePanel *sp;
    NSString *proposedFile;
    
    int ret;
    int err = 0;
    gchar tmp_filename[MAXCHARS]; // I don't like that...
    
    if (is_active)
        return;
 
    ret = gif->user2_box(_("Warning"), 
                         _("An assembly program will be sent to your calc if you decide to continue. Consider doing a backup before."),
                         _("Proceed"), 
                         _("Cancel"));
    if(ret != BUTTON1)
        return;
  
    switch(options.lp.calc_type)
        {
            case CALC_TI83:
            case CALC_TI83P:
                ret = gif->user2_box(_("Information"), 
                                     _("An assembly program is needed to perform a ROM dump. You must AShell installed on your calc to run this program.\nTiLP will transfer the ROM dump program on your calc, then wait until you run it on your calc."),
                                     _("Proceed"), 
                                     _("Cancel"));
                switch(ret)
                    {
                        case BUTTON1:
                            gif->create_pbar_type5(_("ROM dump"), 
                                                   _("Receiving bytes"));
	  
                            strcpy(tmp_filename, g_get_tmp_dir());
                            strcat(tmp_filename, DIR_SEPARATOR);
                            strcat(tmp_filename, "tilp.ROMdump");

                            destroy_pbar();
                            if(tilp_error(err))
                                return;	      

                            [sp setRequiredFileType:@"dunno"];
                            [sp setTitle:@"Save ROM dump as..."];
                            proposedFile = @"romdump.dunno";

                            [sp beginSheetForDirectory:NSHomeDirectory()
                                    file:proposedFile
                                    modalForWindow:mainWindow
                                    modalDelegate:BoxesController
                                    didEndSelector:@selector(romDumpDidEnd:returnCode:contextInfo:)
                                    contextInfo:sp];
                                    
                            break;
                        default:
                            return; 
                    }
                break;
            case CALC_TI85:
                ret = gif->user2_box(_("Information"), 
                                     _("An assembly program is needed to perform a ROM dump. You must have ZShell or Usgard installed on your calc to run this program.\nTiLP will transfer the ROM dump program on your calc, then wait until you run this program."),
                                     _("Proceed"), 
                                     _("Cancel"));
                switch(ret)
                    {	
                        case BUTTON1:
                            ret = gif->user3_box(_("Shell type"), 
                                                 _("Select a shell"), 
                                                 _("ZShell"), _("Usgard"), _("Cancel"));
                            if(ret == 3)
                                return;
                            else	
                                {
                                    gif->create_pbar_type5(_("ROM dump"), 
                                                           _("Receiving bytes"));
	      
                                    strcpy(tmp_filename, g_get_tmp_dir());
                                    strcat(tmp_filename, DIR_SEPARATOR);
                                    strcat(tmp_filename, "tilp.ROMdump");

                                    destroy_pbar();
                                    if(tilp_error(err))
                                        return;
                                        
                                    [sp setRequiredFileType:@"dunno"];
                                    [sp setTitle:@"Save ROM dump as..."];
                                    proposedFile = @"romdump.dunno";

                                    [sp beginSheetForDirectory:NSHomeDirectory()
                                        file:proposedFile
                                        modalForWindow:mainWindow
                                        modalDelegate:BoxesController
                                        didEndSelector:@selector(romDumpDidEnd:returnCode:contextInfo:)
                                        contextInfo:sp];
                                }
                            break;	
                        default:
                            return; 
                    }
                break;
            case CALC_TI86:
                ret = gif->user2_box(_("Information"), 
                                     _("An assembly program is required to perform a ROM dump. You must have a shell installed on your calculator to run this program.\nTiLP will transfer this program on your calc, then wait until you run it."),
                                     _("Procced"), 
                                     _("Cancel"));
                switch(ret)
                    {
                        case BUTTON1:
                            gif->create_pbar_type5(_("ROM dump"), 
                                                   _("Receiving bytes"));
	  
                            strcpy(tmp_filename, g_get_tmp_dir());
                            strcat(tmp_filename, DIR_SEPARATOR);
                            strcat(tmp_filename, "tilp.ROMdump");
	  
                            destroy_pbar();
                            if(tilp_error(err))
                                return;
                                
                            
                            [sp setRequiredFileType:@"dunno"];
                            [sp setTitle:@"Save ROM dump as..."];
                            proposedFile = @"romdump.dunno";

                            [sp beginSheetForDirectory:NSHomeDirectory()
                                file:proposedFile
                                modalForWindow:mainWindow
                                modalDelegate:BoxesController
                                didEndSelector:@selector(romDumpDidEnd:returnCode:contextInfo:)
                                contextInfo:sp];

                            break;
                        default:
                            return; 
                    }
                break;
            case CALC_TI89:
            case CALC_TI92P:
                gif->create_pbar_type5(_("ROM dump"), 
                                       _("Receiving bytes"));

                strcpy(tmp_filename, g_get_tmp_dir());
                strcat(tmp_filename, DIR_SEPARATOR);
                strcat(tmp_filename, "tilp.ROMdump");
   	      
                destroy_pbar();
                if(tilp_error(err))
                    return;	      
                    
                [sp setRequiredFileType:@"dunno"];
                [sp setTitle:@"Save ROM dump as..."];
                proposedFile = @"romdump.dunno";
                
                [sp beginSheetForDirectory:NSHomeDirectory()
                    file:proposedFile
                    modalForWindow:mainWindow
                    modalDelegate:BoxesController
                    didEndSelector:@selector(romDumpDidEnd:returnCode:contextInfo:)
                    contextInfo:sp];

                break;
            case CALC_TI92:
                ret = gif->user2_box(_("Information"), 
                                     _("The FargoII shell must be installed on your calc to perform a ROM dump."),
                                     _("Proceed"), 
                                     _("Cancel"));
                switch(ret)
                    {
                        case BUTTON1:
                            ret = gif->user3_box(_("ROM size"), 
                                                 _("Select the size of your ROM or cancel"), 
                                                 _("1Mb"), _("2 Mb"), _("Cancel"));
                        if(ret == 3)
                            return;
                        else
                            {
                                printf(_("ROM size: %i Mb\n"), ret);
                                gif->create_pbar_type5(_("ROM dump"), 
                                                       _("Receiving bytes"));

                                strcpy(tmp_filename, g_get_tmp_dir());
                                strcat(tmp_filename, DIR_SEPARATOR);
                                strcat(tmp_filename, "tilp.ROMdump");
	      
                                destroy_pbar();
                                if(tilp_error(err))
                                    return;	      
                                    
                                [sp setRequiredFileType:@"dunno"];
                                [sp setTitle:@"Save ROM dump as..."];
                                proposedFile = @"romdump.dunno";

                                [sp beginSheetForDirectory:NSHomeDirectory()
                                    file:proposedFile
                                    modalForWindow:mainWindow
                                    modalDelegate:BoxesController
                                    didEndSelector:@selector(romDumpDidEnd:returnCode:contextInfo:)
                                    contextInfo:sp];
                            }	  
                        break;
                    default: 
                        return;
                    }
                break;
            default:
                DISPLAY(_("Unsupported ROM dump\n"));
                break;
        }
}

- (IBAction)romVersion:(id)sender
{
    cb_rom_version();
}

- (IBAction)installShell:(id)sender
{
    // FIXME OS X
    // Implemented in Tiffep.
    // So, wait until the Tiffep is ported to Mac OS X :)
}


// window

- (IBAction)newWindow:(id)sender
{
    // FIXME OS X
    // a bit of Cocoa coding is required here. Later.
    // could be tricky... see Cocoa's docs.
    // maybe NSWindowController... ?
}


// help

- (IBAction)showThanks:(id)sender
{
    [thanksPanelText readRTFDFromFile:[[NSBundle mainBundle] pathForResource:@"Thanks" ofType:@"rtf"]];
    
    [thanksPanel makeKeyAndOrderFront:self];
}

@end
