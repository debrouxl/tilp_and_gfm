#include "../src/cb_misc.h"
#include "../src/cb_calc.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

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
    // FIXME OS X : I didn't find this one yet...
}

- (IBAction)getScreen:(id)sender
{
    cb_screen_capture();
}

- (IBAction)getDirlist:(id)sender
{
    cb_dirlist();
}

- (IBAction)doRestore:(id)sender
{
    // FIXME OS X
    // we need a fileselection here
    // then call cb_send_backup(char *filename) from cb_calc.c
}

- (IBAction)doBackup:(id)sender
{
    // FIXME OS X : hmmm... there should be a fileselection
    // at some point inside cb_receive_backup()...
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
}


// help

- (IBAction)showThanks:(id)sender
{
    [thanksPanelText readRTFDFromFile:[[NSBundle mainBundle] pathForResource:@"Thanks" ofType:@"rtf"]];
    
    [thanksPanel makeKeyAndOrderFront:self];
}

@end
