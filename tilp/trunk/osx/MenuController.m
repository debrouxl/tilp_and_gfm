/*
 * TiLP Cocoa GUI for Mac OS X
 */

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
#import "TilpController.h"

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
    
    fprintf(stderr, "menu => got awakeFromNib\n");
    
    // Init the instance pointer
    objects_ptr->myMenuController = self;
    
    toolbar = [[[NSToolbar alloc] initWithIdentifier:@"myToolbar"] autorelease];
    
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

// Application menu

- (IBAction)showAbout:(id)sender
{
    NSMutableDictionary *aboutOptions;
    
    aboutOptions = [[NSMutableDictionary alloc] init];
    
    [aboutOptions setObject:@"TiLP for Mac OS X" forKey:@"ApplicationName"];
    [aboutOptions setObject:@"0.1.7" forKey:@"Version"];
    [aboutOptions setObject:@"Copyright © 1999-2001 Romain LIÉVIN, Julien BLACHE\n<rlievin@mail.com>, <jb@technologeek.org>" forKey:@"Copyright"];
    [aboutOptions setObject:@"4.51" forKey:@"ApplicationVersion"];

    [NSApp orderFrontStandardAboutPanelWithOptions:aboutOptions];
    
    [aboutOptions release];
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
    // forget key combos, will make a keyboard...

    if (is_active)
        return;
        
    if ([remoteControlWindow isVisible])
        {
            [remoteControlWindow orderFront:self];
            return;
        }
        
    [remoteControlTextArea setStringValue:@"\nYou are in remote control mode.\nPress any key, but, for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n"];
    
    [remoteControlWindow makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:remoteControlWindow title:@"Terminal - Remote Control" filename:NO];
}

- (IBAction)getScreen:(id)sender
{
    // Ol, a big THANK YOU for this one

    NSImage *screen;
    NSBitmapImageRep *bitmap;
    NSSize size;
    
    int row;
    int col;

    unsigned char *pixels;
    byte *data;
    
    if (is_active)
        return;

    if (cb_screen_capture() != 0)
        return;
        
    if ([screendumpWindow isVisible] == NO)
        {
            [screendumpWindow makeKeyAndOrderFront:self];
            [NSApp addWindowsItem:screendumpWindow title:@"Screendump" filename:NO];
        }
        
    convert_bitmap_to_bytemap(&(ti_screen.img));
    
    bitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:nil
                                       pixelsWide:ti_screen.img.width
                                       pixelsHigh:ti_screen.img.height
                                       bitsPerSample:8
                                       samplesPerPixel:4
                                       hasAlpha:YES
                                       isPlanar:NO
                                       colorSpaceName:NSDeviceRGBColorSpace
                                       bytesPerRow:0
                                       bitsPerPixel:0];
    
    pixels = [bitmap bitmapData];
    
    data = ti_screen.img.bytemap;

    // speed-up things : set a white width * height area (* 4 => 4 bytes per pixel)
    memset(pixels, 0xFF, (ti_screen.img.width * ti_screen.img.height * 4)); 

    for(row = 0; row < ti_screen.img.height; row++)
        {
            for(col = 0; col < ti_screen.img.width; col++)
                {
                    if (*data == 0xFF) // black => set R/G/B to 0
                        {
                            *pixels++ = 0; // red
                            *pixels++ = 0; // blue
                            *pixels++ = 0; // green
                            pixels++; // alpha, but already set to 0xFF
                        }
                    else // white, increment the pixels pointer
                        {
                            pixels += 4;
                        }
                    data++;
                }
        }

    size = NSMakeSize(ti_screen.img.width, ti_screen.img.height);

    screen = [[NSImage alloc] initWithSize:size];
    
    [screen addRepresentation:bitmap];
    
    [screendumpImage setImage:screen];
}

- (IBAction)getDirlist:(id)sender
{
    if (is_active)
        return;

    if (cb_dirlist() != 0)
        return;
        
    [myTilpController refreshOutline];
    [myTilpController refreshInfos];
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
        modalDelegate:myBoxesController
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
        modalDelegate:myBoxesController
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
        modalDelegate:myBoxesController
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
        modalDelegate:myBoxesController
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
    
    // 'k... we must call cb_ams_to_rom() otherwise nothing will happen...
    // well, it's contained in these wonderful loops using gtk_events_pending()
    // for now, I don't care, I'll have a look once the USB driver will be OK.
    
    NSSavePanel *sp;
    NSString *proposedFile;
    
    int ret;
    int err = 0;
    
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
                                                   
                            destroy_pbar();
                            if(tilp_error(err))
                                return;	      

                            sp = [NSSavePanel savePanel];

                            [sp setRequiredFileType:@"dunno"];
                            [sp setTitle:@"Save ROM dump as..."];
                            proposedFile = @"romdump.dunno";

                            [sp beginSheetForDirectory:NSHomeDirectory()
                                    file:proposedFile
                                    modalForWindow:mainWindow
                                    modalDelegate:myBoxesController
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
	      
                                    destroy_pbar();
                                    if(tilp_error(err))
                                        return;
                                        
                                    sp = [NSSavePanel savePanel];
                                        
                                    [sp setRequiredFileType:@"dunno"];
                                    [sp setTitle:@"Save ROM dump as..."];
                                    proposedFile = @"romdump.dunno";

                                    [sp beginSheetForDirectory:NSHomeDirectory()
                                        file:proposedFile
                                        modalForWindow:mainWindow
                                        modalDelegate:myBoxesController
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
	  
                            destroy_pbar();
                            if(tilp_error(err))
                                return;
                                
                            sp = [NSSavePanel savePanel];
                            
                            [sp setRequiredFileType:@"dunno"];
                            [sp setTitle:@"Save ROM dump as..."];
                            proposedFile = @"romdump.dunno";

                            [sp beginSheetForDirectory:NSHomeDirectory()
                                file:proposedFile
                                modalForWindow:mainWindow
                                modalDelegate:myBoxesController
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

                destroy_pbar();
                if(tilp_error(err))
                    return;	      
                    
                sp = [NSSavePanel savePanel];
                
                [sp setRequiredFileType:@"dunno"];
                [sp setTitle:@"Save ROM dump as..."];
                proposedFile = @"romdump.dunno";
                
                [sp beginSheetForDirectory:NSHomeDirectory()
                    file:proposedFile
                    modalForWindow:mainWindow
                    modalDelegate:myBoxesController
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

                                destroy_pbar();
                                if(tilp_error(err))
                                    return;	      
                                    
                                sp = [NSSavePanel savePanel];
                                    
                                [sp setRequiredFileType:@"dunno"];
                                [sp setTitle:@"Save ROM dump as..."];
                                proposedFile = @"romdump.dunno";

                                [sp beginSheetForDirectory:NSHomeDirectory()
                                    file:proposedFile
                                    modalForWindow:mainWindow
                                    modalDelegate:myBoxesController
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
    if ([mainWindow isVisible] == NO)
        [mainWindow makeKeyAndOrderFront:self];
}

- (IBAction)closeWindow:(id)sender
{
    id window;
    
    if ((window = [NSApp keyWindow]) != nil)
        [window orderOut:nil];
}

// used to enable/disable the "New Window" menu item
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    if ([[menuItem title] isEqualToString:@"New Window"] && ([mainWindow isVisible] == YES))
        return NO;
    else
        return YES;
}

// help

- (IBAction)showThanks:(id)sender
{
    [thanksPanelText readRTFDFromFile:[[NSBundle mainBundle] pathForResource:@"Thanks" ofType:@"rtf"]];
    
    [thanksPanel makeKeyAndOrderFront:self];
    
    [NSApp addWindowsItem:thanksPanel title:@"Thanks" filename:NO];
}

@end
