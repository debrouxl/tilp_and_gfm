#include "../src/cb_misc.h"
#include "../src/cb_calc.h"
#include "../src/struct.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;
extern struct screenshot ti_screen;

#import "MenuController.h"

@implementation MenuController

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

- (IBAction)probeLink:(id)sender
{
    // unusable atm.
    //cb_probe_cable();
}

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

    if (cb_screen_capture() != 0)
        return;
    
    [screendumpWindow makeKeyAndOrderFront:self];
    
    bitmap = [[NSData alloc] initWithBytes:ti_screen.img.bitmap length:strlen(ti_screen.img.bitmap)];
    [bitmap autorelease];
    
    screen = [[NSImage alloc] initWithData:bitmap];
    [screen autorelease];
    
    [screendumpImage setImage:screen];
}

- (IBAction)getDirlist:(id)sender
{
    cb_dirlist();
}

- (IBAction)doRestore:(id)sender
{
    // FIXME OS X
    // we need a fileselection here (NSOpenPanel)
    // then call cb_send_backup(char *filename) from cb_calc.c
}

- (IBAction)doBackup:(id)sender
{
    // FIXME OS X : hmmm... there should be a fileselection
    // at some point inside cb_receive_backup()...
    // that would be NSSavePanel
    cb_receive_backup();
}


// functions 2

- (IBAction)sendFLASHApp:(id)sender
{
    // FIXME OS X
    // use a fileselection here
    // then call cb_send_flash_app(char *filename) from cb_calc.c
}

- (IBAction)sendAMS:(id)sender
{
    // FIXME OS X
    // use a fileselection here
    // then call cb_send_flash_os(char *filename) from cb_calc.c
}

- (IBAction)receiveFLASHApp:(id)sender
{
    // FIXME OS X
    // I didn't find this one yet...
    // OK it's not implemented... ROMAIN !! I'm gonna LART you !
}

- (IBAction)getIDList:(id)sender
{
    cb_id_list();
}

- (IBAction)romDump:(id)sender
{
    // FIXME OS X
    // we need a fileselection here
    // then call cb_ams_to_rom(char *filename) from cb_calc.c
}

- (IBAction)romVersion:(id)sender
{
    cb_rom_version();
}

- (IBAction)installShell:(id)sender
{
    // FIXME OS X
    // I didn't find this one yet...
}


// window

- (IBAction)newWindow:(id)sender
{
    // FIXME OS X
    // a bit of Cocoa coding is required here. Later.
    // could be tricky... see Cocoa's docs.
}


// help

- (IBAction)showThanks:(id)sender
{
    [thanksPanelText readRTFDFromFile:[[NSBundle mainBundle] pathForResource:@"Thanks" ofType:@"rtf"]];
    
    [thanksPanel makeKeyAndOrderFront:self];
}

@end
